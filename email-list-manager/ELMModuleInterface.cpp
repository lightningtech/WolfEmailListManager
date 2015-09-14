/*
 * ELMModuleInterface.cpp
 *
 *  Created on: 30 de jul. de 2015
 *      Author: amides
 */

#include "ELMModuleInterface.h"
#include "processingThreadCore/UtilsHeaders.hpp"

ELMModuleInterface::ELMModuleInterface()
					:startJobs(0),endedJobs(0),callBackObject(0)
{
	threadsNumber = boost::thread::hardware_concurrency();
	manager = new ConsumersManager(threadsNumber,this);

	outputList = new std::list<std::string>();
	outPutRejectedemails = new std::vector<std::string>();
	_vectorIn = new std::vector<std::string>();
	countriesDomains = new std::vector<std::string>();
	_listIn = new std::list<std::string>();

	delList = new std::vector<std::string>();
    domainList = new std::vector<std::string>();

	MaskParameters = 0;
}

ELMModuleInterface::~ELMModuleInterface()
{
	delete manager;
	delete outputList;
	delete outPutRejectedemails;
	delete countriesDomains;
	delete _vectorIn;
	delete _listIn;
	delete delList;
	delete domainList;
}

void ELMModuleInterface::extractAndClean(PyObject * inputList,int maximumCharactersRejectAddress,
											  bool allowEmbeddedSpacesInAOL,bool noDuplicateDomains,bool rejectLongDomains,
											  PyObject * countryDomains,bool sortByUserName,bool sortByDomain,
											  bool removeDuplicates,bool lastJob,PyObject* callBackObject)
{
  this->lastJob = lastJob;

  _vectorIn->reserve(200000);
  Python2CUtils::toVector(inputList,_vectorIn);

  if( !startJobs )
  {
	countriesDomains->clear();
	Python2CUtils::toVector(countryDomains,countriesDomains);
  }

  this->callBackObject = callBackObject;

  if( MaskParameters == 0 || startJobs == 0)
  {
	  MaskParameters = (allowEmbeddedSpacesInAOL) ? MaskParameters|ALLOW_EMBEDDED_SPACES_AOL : MaskParameters|0;
	  MaskParameters = (noDuplicateDomains) ? MaskParameters|NO_DUPLICATE_DOMAINS : MaskParameters|0;
	  MaskParameters = (rejectLongDomains) ? MaskParameters|REJECT_LONG_DOMAINS : MaskParameters|0;
	  MaskParameters = (removeDuplicates) ? MaskParameters|REMOVE_DUPLICATES : MaskParameters|0;
	  MaskParameters = (sortByUserName) ? MaskParameters|SORT_BY_USERNAME : MaskParameters|0;
	  MaskParameters = (sortByDomain) ? MaskParameters|SORT_BY_DOMAIN : MaskParameters|0;
  }

  startJobs++;
  manager->extractAndClean(_vectorIn,maximumCharactersRejectAddress,
		 	 	 	 	  MaskParameters,countriesDomains);
}

void ELMModuleInterface::endingCurrentJob( const std::list<std::string> &outPutList,
		  	  	  	  	  	  	  	  	   const std::vector<std::string> &rejectedList,
										   unsigned int errorCode,
	   	   	  	  	  	  	  	  	  	   std::string description )
{
	long retvalue = 0;

	int localEndedJob = 0;
	int localStartJob = 0;
	int localLastJob = false;

	{
		boost::mutex::scoped_lock lock(_localStatusVarMutex);
		endedJobs++;
		localEndedJob = endedJobs;
		localStartJob = startJobs;
		localLastJob = lastJob;

		_set.insert(outPutList.begin(),outPutList.end());
		outPutRejectedemails->insert(outPutRejectedemails->end(),
								     rejectedList.begin(),rejectedList.end());
	}

	if( localEndedJob == localStartJob*threadsNumber
			&& localLastJob == true )
	{
		std::cout << "callback  ... " << std::endl;

		PyGILState_STATE gstate;
		gstate = PyGILState_Ensure();

		endedJobs = startJobs = 0;

		PyObject* oList = Python2CUtils::toPythonList(_set);
		PyObject* rejectedEmailsList = Python2CUtils::toPythonList(outPutRejectedemails);

		_set.clear();
		outPutRejectedemails->clear();

	    if( PyList_CheckExact(oList) &&
	    		PyList_CheckExact(rejectedEmailsList))
		{
			PyObject* argsList = Py_BuildValue("(OOis)",oList,rejectedEmailsList,errorCode,description.c_str());

			PyObject * result = PyEval_CallObject(this->callBackObject, argsList);

			if (result  )
			{
				retvalue = PyLong_AsLong(result);
				std::cout << "callback result check resultValue:  ... " << retvalue << std::endl;

			}

			Py_DECREF(argsList);
			Py_DECREF(result);
		}
		else{
			std::cout << "Callback no enviado porque no son listas ... " << std::endl;
		}
		PyGILState_Release(gstate);
	}
}

void ELMModuleInterface::mergeEmailLists(PyObject* toMergeList,PyObject* hostList,
					 	 	 	 	 	 PyObject* callback)
{
   if(_vectorIn->size())
	   _vectorIn->clear();

   Python2CUtils::toVector(toMergeList,_vectorIn);

   if( _listIn->size() )
	   _listIn->clear();

   Python2CUtils::toList(hostList,_listIn);

   this->callBackObject = callback;
   manager->mergeEmailLists(_vectorIn,_listIn);
}

void ELMModuleInterface::endingMergeListJob(unsigned int errorCode,
	   	   	  	  	  	  	  	  	  	  	std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(_listIn);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(Ois)",pyList,errorCode,description.c_str());
		PyObject * result = PyEval_CallObject(this->callBackObject,argList);

		if (result  )
		{
			returnValue = PyLong_AsLong(result);
			std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(result);
		Py_DECREF(argList);

	}
	PyGILState_Release(gstate);
}

void ELMModuleInterface::deleteEmailListElements(PyObject* masterList,PyObject* deleteList,
								 	 	 	     PyObject* ToDelDomainList,
			 	 	 	 	 	                 bool orderByDomain,bool md5SuppresionListEnabled,
												 PyObject* callback)
{
	Python2CUtils::toVector(deleteList,delList);
	Python2CUtils::toVector(ToDelDomainList,domainList);
	Python2CUtils::toList(masterList,_listIn);

	if( outPutRejectedemails->size() )
		outPutRejectedemails->clear();

	this->callBackObject = callback;
	manager->deleteEmailListElements(_listIn,delList,domainList,
			outPutRejectedemails,orderByDomain,md5SuppresionListEnabled);
}

void ELMModuleInterface::ListElementsDeleteEnd(unsigned int errorCode,
											   std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(_listIn);
	PyObject* erasedListElements = Python2CUtils::toPythonList(outPutRejectedemails);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(OOis)",pyList,erasedListElements,errorCode,description.c_str());

		PyObject * result = PyEval_CallObject(this->callBackObject,argList);
		if (result  )
		{
			returnValue = PyLong_AsLong(result);
			std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(argList);
		Py_DECREF(result);
	}

	PyGILState_Release(gstate);
}


void ELMModuleInterface::keepAddresses(PyObject* endingLines,
									   PyObject* filterStrings,
									   PyObject* emailList,
									   PyObject* callback)
{
	numberKeepJobs = threadsNumber;
	std::vector<std::string> * endLines = new std::vector<std::string>();
	vector<string> * fStrings = new std::vector<std::string>();
	//todo eliminar esta memoria en algun momento.

	Python2CUtils::toVector(endingLines,endLines);
	Python2CUtils::toVector(filterStrings,fStrings);
	Python2CUtils::toVector(emailList,_vectorIn);
	this->callBackObject = callback;

	manager->keepAddress(endLines,fStrings,_vectorIn);
}


void ELMModuleInterface::keepAddressesEnd( std::vector<std::string> emailList,
		   	   	   	   	   	   	   	       std::vector<std::string>* erasedList, unsigned int errorCode,
										   std::string description )
{
	int localNumberKeepJobs = 0;

	{
		boost::mutex::scoped_lock lock(_localStatusVarMutex);
		if(numberKeepJobs == threadsNumber)
		{
			_vectorIn->clear();
			outPutRejectedemails->clear();
		}
		numberKeepJobs--;
		localNumberKeepJobs = numberKeepJobs;

		for(std::size_t i = 0; i < emailList.size();i++ )
			_vectorIn->push_back(emailList[i]);
	}


	if(localNumberKeepJobs == 0 )
	{
		outPutRejectedemails = erasedList;
		PyGILState_STATE gstate;
	    gstate = PyGILState_Ensure();
	    long returnValue = 0;

	    PyObject* pyList = Python2CUtils::toPythonList(_vectorIn);
	    PyObject* erasedListElements = Python2CUtils::toPythonList(outPutRejectedemails);
	    if(PyList_CheckExact(pyList))
	    {
	    	PyObject * argList = Py_BuildValue("(OOis)",pyList,erasedListElements,errorCode,description.c_str());

	    	PyObject * result = PyEval_CallObject(this->callBackObject,argList);
	    	if (result  )
	    	{
	    		returnValue = PyLong_AsLong(result);
	    		std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
	    	}

	    	Py_DECREF(argList);
	    	Py_DECREF(result);
	    }

	    PyGILState_Release(gstate);
	}

}


void ELMModuleInterface::sampleAddresses(PyObject* inputList,int sampleIndicator,
						 	 	 	 	 int numberElements,string filterWord,
										 PyObject* callback)
{
	this->callBackObject = callback;
	Python2CUtils::toVector(inputList,_vectorIn);
	manager->sampleAddresses(_vectorIn,sampleIndicator,
							 numberElements,filterWord);
}

void ELMModuleInterface::sampleAddressEnded(std::vector<std::string> sampleOutput,unsigned int errorCode,
											std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(&sampleOutput);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(Ois)",pyList,errorCode,description.c_str());
		PyObject * result = PyEval_CallObject(this->callBackObject,argList);
		if (result  )
		{
			returnValue = PyLong_AsLong(result);
			std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(argList);
		Py_DECREF(result);
	}

	PyGILState_Release(gstate);
}


void ELMModuleInterface::separateList(PyObject* inputList,int functionCode,
					  	  	  	  	  int modeCode,PyObject* domainList,
									  unsigned long long randomPackageSize,
									  PyObject* callback)
{
    Python2CUtils::toVector(inputList,_vectorIn);
	Python2CUtils::toVector(domainList,this->domainList);
	this->callBackObject = callback;

	manager->separateList(_vectorIn,functionCode,modeCode,this->domainList,randomPackageSize);
}

void ELMModuleInterface::separateListEnded(const std::set<std::string> &outputSet,
										   bool lastList,
										   unsigned int errorCode,
										   std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(outputSet);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(Oiis)",pyList,lastList,errorCode,"OK");
		PyObject * result = PyEval_CallObject(this->callBackObject,argList);
		Py_DECREF(argList);
		if (result  )
		{
			returnValue = PyLong_AsLong(result);
			//std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(result);
	}

	PyGILState_Release(gstate);
}

void ELMModuleInterface::seedAddresses(	PyObject* inputList,
										int functionCode,
										int numberOfTimes,
										PyObject* toSeedAddresses,
										PyObject* callback)
{
	Python2CUtils::toList(inputList,_listIn);
    Python2CUtils::toVector(toSeedAddresses,_vectorIn);//address to seed
	this->callBackObject = callback;

	manager->seedAddresses(_listIn,_vectorIn,numberOfTimes,functionCode);
}


void ELMModuleInterface::seedAddressesEnded(unsigned int errorCode,
					    					std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(_listIn);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(Ois)",pyList,errorCode,description.c_str());
		PyObject * result = PyEval_CallObject(this->callBackObject,argList);
		if (result  )
		{
			returnValue = PyLong_AsLong(result);
			std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(argList);
		Py_DECREF(result);
	}

	PyGILState_Release(gstate);
}

void ELMModuleInterface::splitAddresses(PyObject* inputList,
										int functionCode,
										int numberElements,/*this is n on function code context*/
										PyObject* callback)
{
	Python2CUtils::toVector(inputList,_vectorIn);
	this->callBackObject = callback;

	manager->splitAddressesList(_vectorIn,functionCode,
								numberElements);
}

void ELMModuleInterface::splitAddressesEnded(std::vector<std::string> result,
											 unsigned int errorCode,
											 std::string description)
{
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	long returnValue = 0;

	PyObject* pyList = Python2CUtils::toPythonList(&result);
	if(PyList_CheckExact(pyList))
	{
		PyObject * argList = Py_BuildValue("(Ois)",pyList,errorCode,description.c_str());
		PyObject * result = PyEval_CallObject(this->callBackObject,argList);
		if (result)
		{
			returnValue = PyLong_AsLong(result);
			std::cout << "callback result check resultValue:  ... " << returnValue << std::endl;
		}

		Py_DECREF(argList);
		Py_DECREF(result);
	}

	PyGILState_Release(gstate);
}








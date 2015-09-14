/*
 * ELMModuleInterface.h
 *
 *  Created on: 30 de jul. de 2015
 *      Author: amides
 */

#ifndef ELMMODULEINTERFACE_H_
#define ELMMODULEINTERFACE_H_

#include "processingThreadCore/ConsumersManager.h"
#include "FinishedCurrentJobHandler.hpp"
#include <set>

struct DLLM_LOCAL CompareDomainUserName
{
	bool operator()(std::string a,std::string b)
	{
		std::string domainA = NetworkUtils::getDomainFromEmail(a);
		std::string domainB = NetworkUtils::getDomainFromEmail(b);

		if( domainA.compare(domainB) < 0 )
		{
			return true;
		}
		else if( domainA.compare(domainB) > 0 )
		{
			return false;
		}

		return (a.compare(b) < 0);//comienza desde el principio, portanto seria por el nombre.
	};
};

struct DLLM_LOCAL CompareDomain
{
	bool operator()(std::string a,std::string b)
	{
		std::string domainA = NetworkUtils::getDomainFromEmail(a);
		std::string domainB = NetworkUtils::getDomainFromEmail(b);

		return ( domainA.compare(domainB) < 0 );
	};
};

class DLLM_LOCAL ELMModuleInterface : public FinishedCurrentJobHandler
{
public:
	ELMModuleInterface();
	virtual ~ELMModuleInterface();

	void extractAndClean(PyObject * inputList,int maximumCharactersRejectAddress,
							  bool allowEmbeddedSpacesInAOL,bool noDuplicateDomains,bool rejectLongDomains,
							  PyObject * countryDomains,bool sortByUserName,bool sortByDomain,
							  bool removeDuplicates,bool lastJob,PyObject * callBackObject);


	void mergeEmailLists(PyObject* toMergeList,PyObject* hostList,
						 PyObject* callback);


	void deleteEmailListElements(PyObject* masterList,PyObject* deleteList,
								 PyObject* ToDelDomainList,
			 	 	 	 	 	 bool orderByDomain,bool md5SuppresionListEnabled,PyObject* callback);

	void keepAddresses(PyObject* endingLines,
					   PyObject* filterStrings,
					   PyObject* emailList,
					   PyObject* callback);

	void sampleAddresses(PyObject* inputList,int sampleIndicator,
						 int numberElements,string filterWord,PyObject* callback);


	void separateList(PyObject* inputList,int functionCode,
					  int modeCode,PyObject* domainList,
					  unsigned long long randomPackageSize,
					  PyObject* callback);

	void seedAddresses(	PyObject* inputList,
					    int functionCode,
			            int numberOfTimes,
						PyObject* toSeedAddresses,
						PyObject* callback);

	void splitAddresses(PyObject* inputList,
						int functionCode,
						int numberElements,/*this is n on function code context*/
						PyObject* callback);


	/*Callback que se llamara el terminar los trabajos de la funcionalidad.
	 * */
	void endingCurrentJob(const std::list<std::string> &outPutList,
			  	  	  	  const std::vector<std::string> &rejectedList,
						  unsigned int errorCode,
						  std::string description = std::string("") );

	/*Se llamara al terminar de mezclar las listas de entrada
	 * */
	void endingMergeListJob(  unsigned int errorCode,
			   	   	   	   	  std::string description = std::string(""));

	/*Se llama al terminar de eliminar las direcciones.
	 * */
	void ListElementsDeleteEnd( unsigned int errorCode,
								std::string description = std::string("") );

	void keepAddressesEnd( std::vector<std::string> emailList,
			   	   	   	   std::vector<std::string>* erasedList,
						   unsigned int errorCode,
						   std::string description = std::string(""));

	void sampleAddressEnded(std::vector<std::string> sampleOutput,unsigned int errorCode,
							std::string description = std::string(""));

	void separateListEnded( const std::set<std::string> &outputSet,
							bool lastList,unsigned int errorCode,
							std::string description = std::string(""));

	void seedAddressesEnded(unsigned int errorCode,
					   	    std::string description = std::string(""));

	void splitAddressesEnded(std::vector<std::string> result,
							 unsigned int errorCode,
							 std::string description = std::string(""));

private:

	std::vector<std::string> * _vectorIn;
	std::list<std::string>* _listIn;

	std::vector<std::string> * outPutemails;
	std::vector<std::string> * outPutRejectedemails;
	std::vector<std::string> * countriesDomains;

	std::vector<std::string> * delList;
	std::vector<std::string> * domainList;
	std::list<std::string>* outputList;

	ConsumersManager * manager;
	int numberKeepJobs;

	bool lastJob;
	int startJobs;
	int endedJobs;
	int threadsNumber;
	PyObject * callBackObject;
	boost::mutex _localStatusVarMutex;
	char MaskParameters;

	int functionCode;/*Para separate List*/
	int modeCode;/*Para separate List*/

	std::set<std::string,CompareUsername> _set;
};

#endif /* ELMMODULEINTERFACE_H_ */

/*
 * elm.cpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */
#include "ELMModuleInterface.h"
#include "processingThreadCore/UtilsHeaders.hpp"
using namespace std;

static ELMModuleInterface elmApi;

static PyObject* extractAndCleanInitialize(PyObject* self, PyObject* args) {

    PyObject * a1; //inputFiles
    int a2; //maximumCharactersRejectAddress;
    bool a3; //allowEmbeddedSpacesInAOL;
    bool a4; //noDuplicateDomains;
    bool a5; //rejectLongDomains;
    PyObject * a6; //countryDomains;
    bool a7; //sortByUserName;
    bool a8; //sortByDomain;
    bool a9; //removeDuplicates;
    PyObject * callBackObject;//metodo que llamara la lib al estar listo el trabajo.
    bool a12;//debe venir en true cuando es la ultima lista a analizar.Luego de este se recibira el callback terminado.

    if (! PyArg_ParseTuple( args, "O!ibbbO!bbbbO:set_callback",&PyList_Type,&a1, &a2, &a3, &a4, &a5,&PyList_Type,&a6,
    						&a7, &a8, &a9,&a12,&callBackObject)) {
        printf("No match the params");
        return NULL;
    }
    else {
			if( PyCallable_Check(callBackObject))
			{
				// Make sure the GIL has been created since we need to acquire it in our
				// callback to safely call into the python application.
				if (! PyEval_ThreadsInitialized()) {
					PyEval_InitThreads();
				}

				Py_XINCREF(callBackObject);
				elmApi.extractAndClean(a1,a2,a3,a4,a5,a6,a7,a8,a9,a12,callBackObject);
			}
    }
    Py_RETURN_NONE;
}

static PyObject* mergeEmailList(PyObject* self,PyObject* args)
{
	PyObject* toMergeList;
	PyObject* hostList;
	PyObject* callback;

	if( !PyArg_ParseTuple(args,"O!O!O:set_callback",&PyList_Type,&toMergeList,
						  &PyList_Type,&hostList,&callback))
	{
		printf("No match the params");
		return NULL;
	}
	else{

		if( PyCallable_Check(callback))
		{
			// Make sure the GIL has been created since we need to acquire it in our
			// callback to safely call into the python application.
			if (! PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.mergeEmailLists(toMergeList,hostList,callback);
		}
	}

	Py_RETURN_NONE;
}

static PyObject* deleteEmailListElements(PyObject* self,PyObject* args)
{
  PyObject* mList;
  PyObject* deleteList;
  PyObject* toDeleteDomains;
  bool sortResultByDomain;
  bool md5SuppresionListEnabled;/**Indica que la lista de eliminacion es una supressed List md5*/
  PyObject* callback;

  if( !PyArg_ParseTuple(args,"O!O!O!bbO:set_callback",&PyList_Type,&mList,
		  	  	  	    &PyList_Type,&deleteList,&PyList_Type,&toDeleteDomains,
						&sortResultByDomain,&md5SuppresionListEnabled,&callback)){
		printf("No match the params");
		return NULL;
  }
  else{
		if(PyCallable_Check(callback))
		{
			// Make sure the GIL has been created since we need to acquire it in our
			// callback to safely call into the python application.
			if (! PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.deleteEmailListElements(mList,deleteList,toDeleteDomains,
											   sortResultByDomain,md5SuppresionListEnabled,callback);
		}
  }

	Py_RETURN_NONE;
}

static PyObject* keepAddresses(PyObject* self,PyObject* args)
{
	PyObject* endingLines;
	PyObject* filterStrings;
	PyObject* emailList;
	PyObject* callback;

	if( !PyArg_ParseTuple(args,"O!O!O!O:set_callback",&PyList_Type,&endingLines,
						&PyList_Type,&filterStrings,&PyList_Type,&emailList,
						&callback)){
		printf("No match the params");
		return NULL;
	}
	else{
		if( PyCallable_Check(callback))
		{
			// Make sure the GIL has been created since we need to acquire it in our
			// callback to safely call into the python application.
			if (! PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.keepAddresses(endingLines,filterStrings,emailList,callback);
		}
	}

	Py_RETURN_NONE;
}

static PyObject* sampleAddresses(PyObject* self,PyObject* args)
{
	PyObject* inputList;
	int sampleIndicator;//si es 0 significa opcion de escojer, n elements que cumplan con x word restriction
						// 1 es ramdom n elements.
						//si es 2 es n consecutivas que cumplan con x words.
	int numberElements;
	char* filterWord;
	PyObject* callback;

	if(!PyArg_ParseTuple(args,"O!iisO:set_callback",&PyList_Type,&inputList,
							&sampleIndicator,&numberElements,&filterWord,
							&callback)){
		printf("No match the params");
		return NULL;
	}
	else{
		if( PyCallable_Check(callback))
		{
			if (!PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			std::cout << "sampleAddresses(PyObject* self,PyObject* args)... " << std::endl;
			elmApi.sampleAddresses(inputList,sampleIndicator,numberElements,std::string(filterWord),callback);
		}
	}

	Py_RETURN_NONE;
}

static PyObject* separateList( PyObject* self, PyObject* args )
{
	PyObject* inputList;
	int functionCode;
	/*de  a 4. codigos de funcion.
	 * 1-separate files for each domain
	 * 2-separate list for each country code(last element of domain)
	 * 3-random packets size
	 * 4-just random output file
	 */
	int modeCode;
	/*de 1 a 5. codigos para el modo.
	 * 1-domain sort.
	 * 2-domain sort with De-Dup(delete duplicated elements)
	 * 3-domain randomize
	 * 4-domain randomize and randomize the rest elements list//no tenido en cuenta
	 * 5-randomize whole file
	 */
	PyObject* domainList;
	int randomPackageSize;
	PyObject* callback;

	if( !PyArg_ParseTuple(args,"O!iiO!iO:set_callback",&PyList_Type,&inputList,
			&functionCode,&modeCode,&PyList_Type,&domainList,&randomPackageSize,&callback)){
		printf("No match the params");
		return NULL;
	}
	else{
		if( PyCallable_Check(callback))
		{
			if (!PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.separateList(inputList,functionCode,modeCode,domainList,randomPackageSize,callback);
		}
	}

	Py_RETURN_NONE;
}

static PyObject* seedAddresses(PyObject* self,PyObject* args)
{
	PyObject* inputList;
	int functionCode;
	/*de 0 a 3. codigos de funcion.
	 * 0-seed at uniform interval( x number of times to seed )
	 * 1-seed at random interval (x number of times to seed)
	 * 2-seed at x number of addresses (x number of elements before seed just one time)
	 */
	int numberOfTimes;/*this is x element*/
	PyObject* toSeedAddresses;
	PyObject* callback;

	if( !PyArg_ParseTuple(args,"O!iiO!O:set_callback",&PyList_Type,&inputList,
			&functionCode,&numberOfTimes,&PyList_Type,&toSeedAddresses,&callback)){
		printf("No match the params");
		return NULL;
	}
	else{
		if( PyCallable_Check(callback))
		{
			if (!PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.seedAddresses(inputList,functionCode,numberOfTimes,toSeedAddresses,callback);
		}
	}

	Py_RETURN_NONE;
}

static PyObject* splitAddressesList(PyObject* self, PyObject* args)
{
	PyObject* inputList;
	int functionCode;
	/*de 0 a 1. codigos de funcion.
	 * 0-split for n addresses by output list
	 * 1-split between n output lists
	 */
	int numberElements;/*this is n on function code context*/
	PyObject* callback;

	if( !PyArg_ParseTuple(args,"O!iiO:set_callback",&PyList_Type,&inputList,
			&functionCode,&numberElements,&callback)){
		printf("No match the params");
		return NULL;
	}
	else{
		if( PyCallable_Check(callback))
		{
			if (! PyEval_ThreadsInitialized()) {
				PyEval_InitThreads();
			}

			Py_XINCREF(callback);
			elmApi.splitAddresses(inputList,functionCode,numberElements,callback);
		}
	}

	Py_RETURN_NONE;
}


static PyMethodDef elmMethods[] = {
     {"extractAndClean", extractAndCleanInitialize, METH_VARARGS, "Extract And Clean"},
	 {"mergeEmailList", mergeEmailList, METH_VARARGS, "Merge Email List"},
	 {"deleteEmailListElements",deleteEmailListElements, METH_VARARGS, "Delete Email List Elements"},
	 {"keepAddresses",keepAddresses, METH_VARARGS, "Keep Addresses"},
	 {"sampleAddresses",sampleAddresses, METH_VARARGS, "Sample Addresses"},
	 {"separateList",separateList, METH_VARARGS, "Separate List"},
	 {"seedAddresses",seedAddresses, METH_VARARGS, "Seed Addresses"},
	 {"splitAddressesList",splitAddressesList,METH_VARARGS, "Split Addresses List"},
     {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef elmmodule = {
   PyModuleDef_HEAD_INIT,
   "elm",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   elmMethods
};

PyMODINIT_FUNC PyInit_elm(void)
{
  return PyModule_Create(&elmmodule);
}



#include <Python.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include "NetworkUtils.hpp"

using std::string;
using std::vector;

struct DLLM_LOCAL CompareUsername
{
	bool operator()(std::string a,std::string b)
	{
		return (a.compare(b) < 0);
	};
};

struct DLLM_LOCAL ListCompare{
	bool operator()(std::string a,std::string b)
	{
		return (a.compare(b) < 0);
	}
};

class DLLM_LOCAL Python2CUtils {
    public:
	    Python2CUtils(){};
	    ~Python2CUtils(){};
        static string toString(PyObject * object);
        static void toVector(PyObject * theList,std::vector<std::string> * result,bool sorted=false);
        static void toList(PyObject * theList,std::list<std::string> * result,bool sorted=false);
        static PyObject * toPythonList(vector<string>* theVector);
        static PyObject * toPythonList(std::list<string>* theList);
        static PyObject * toPythonList(const std::set<string,CompareUsername>& _set);
        static PyObject * toPythonList(const std::set<string>& _set);//comparacion inherente
        static int listSize(PyObject * theList);
        static string getItemFromList(PyObject * theList, int index);
        static PyObject* toCallbacParameterList(PyObject* output,PyObject* rejectedOutput );

};

#include "Python2CUtils.hpp"
#include <iostream>
string Python2CUtils::toString(PyObject * object) {
	return std::string(PyUnicode_AsUTF8(object));
}

int Python2CUtils::listSize(PyObject * theList) {
    return PyList_Size(theList);
}

string Python2CUtils::getItemFromList(PyObject * theList, int index) {
    PyObject * object = PyList_GetItem(theList, index);
    return Python2CUtils::toString(object);
}

void Python2CUtils::toVector(PyObject * theList,std::vector<std::string> * result,
							 bool sorted)
{
	if(result && PyList_Check(theList))
	{
		if(result->size())
			result->clear();

		for (int i=0; i<Python2CUtils::listSize(theList); i++) {
			result->push_back(Python2CUtils::getItemFromList(theList, i));
		}
		if (sorted) {
			sort(result->begin(), result->end());
		}
	}

}

void Python2CUtils::toList(PyObject * theList,
						   std::list<std::string> * result,
						   bool sorted)
{
	if(result && PyList_Check(theList))
	{
		if( result->size() )
			result->clear();

		for (int i=0; i<Python2CUtils::listSize(theList); i++) {
			result->push_back(Python2CUtils::getItemFromList(theList, i));
		}

		if (sorted) {
			ListCompare compareObj;
			result->sort(compareObj);
		}
	}
}


PyObject * Python2CUtils::toPythonList(vector<string>* theVector)
{
    PyObject *pyList, *item;
    int i;
    pyList = PyList_New(theVector->size());
    if (pyList != NULL) {
      for (i=0; i<theVector->size(); i++) {
    	  std::string element = theVector->at(i);
    	  item = PyUnicode_DecodeUTF8(element.c_str(),element.size(),NULL);
          PyList_SET_ITEM(pyList, i, item);
      }
    }
    return pyList;
}

PyObject * Python2CUtils::toPythonList(std::list<string>* theList)
{
	PyObject *pyList = 0, *item = 0;
	int i = 0;
	pyList = PyList_New(theList->size());

	if (pyList != NULL)
	{
		std::list<std::string>::iterator iter;
		for(iter = theList->begin();iter != theList->end();++iter)
		{
			item = PyUnicode_DecodeUTF8((*iter).c_str(),(*iter).size(),NULL);
			PyList_SET_ITEM(pyList, i, item);
			i++;
		}
	}
	return pyList;
}

PyObject * Python2CUtils::toPythonList(const std::set<string,CompareUsername>& _set)
{
	PyObject *pyList = 0, *item = 0;
	int i = 0;
	pyList = PyList_New(_set.size());

	if (pyList != NULL)
	{
		std::set<std::string,CompareUsername>::iterator iter;
		for(iter = _set.begin();iter != _set.end();++iter)
		{
			item = PyUnicode_DecodeUTF8((*iter).c_str(),(*iter).size(),NULL);
			PyList_SET_ITEM(pyList, i, item);
			i++;
		}
	}
	return pyList;
}

PyObject * Python2CUtils::toPythonList(const std::set<string>& _set)
{
	PyObject *pyList = 0, *item = 0;
	int i = 0;
	pyList = PyList_New(_set.size());

	if (pyList != NULL)
	{
		std::set<std::string>::iterator iter;
		for(iter = _set.begin();iter != _set.end();++iter)
		{
			item = PyUnicode_DecodeUTF8((*iter).c_str(),(*iter).size(),NULL);
			PyList_SET_ITEM(pyList, i, item);
			i++;
		}
	}
	return pyList;
}

PyObject* Python2CUtils::toCallbacParameterList(PyObject* output,PyObject* rejectedOutput )
{
	PyObject* result = PyList_New(2);
	PyList_SET_ITEM(result,0,output);
	PyList_SET_ITEM(result,1,rejectedOutput);

	return PyList_AsTuple(result);
}








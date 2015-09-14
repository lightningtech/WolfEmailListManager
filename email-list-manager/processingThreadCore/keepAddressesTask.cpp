/*
 * keepAddressesTask.cpp
 *
 *  Created on: 11 de ago. de 2015
 *      Author: amides
 */

#include "keepAddressesTask.h"

boost::mutex keepAddressesTask::_mutex;

keepAddressesTask::keepAddressesTask() {

}

keepAddressesTask::~keepAddressesTask() {
}

void keepAddressesTask::execute()
{
	std::vector<std::string> goodValues;
	for( size_t i = start; i < end; i++ )
	{
		if(!checkEndingLines(emailList[i])
			&& !checkingFilterStrings(emailList[i]))
		{
			boost::mutex::scoped_lock lock(_mutex);
			erasedAddresses->push_back(emailList[i]);
		}
		else{
			goodValues.push_back(emailList[i]);
		}
	}
	handler->keepAddressesEnd(goodValues,erasedAddresses,OK);
}

bool keepAddressesTask::checkEndingLines(std::string address)
{
	unsigned int pos = 0;
	unsigned int sizeEnding = 0;

	std::vector<std::string>::iterator iter;

	{
		boost::mutex::scoped_lock lock(_mutex);
		for(iter = endingLines->begin();iter != endingLines->end(); ++iter)
		{
			std::string domain = (*iter);
			std::size_t found = address.rfind(domain);
			if(found != std::string::npos &&
					found + domain.size() == address.size()-1)
			{
				return true;
			}
		}
	}
	return false;
}

bool keepAddressesTask::checkingFilterStrings(std::string address)
{
	boost::mutex::scoped_lock lock(_mutex);
	for( std::size_t i = 0;i < filterStrings->size();i++ )
	{
		if(address.find(filterStrings->at(i)) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

void keepAddressesTask::setParameters(std::vector<std::string>* endingLines,
	    		   std::vector<std::string>* filterStrings,
				   std::vector<std::string>* erasedAddresses,
	               std::vector<std::string>* emailList,
				   FinishedCurrentJobHandler* handler,
				   int start,int end)
{
	this->endingLines = endingLines;
	this->emailList.assign(emailList->begin(),emailList->end());
	this->filterStrings = filterStrings;
	this->handler = handler;
	this->erasedAddresses = erasedAddresses;
	this->start = start;
	this->end = end;

}

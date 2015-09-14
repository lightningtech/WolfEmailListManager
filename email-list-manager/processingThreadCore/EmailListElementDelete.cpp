/*
 * EmailListElementDelete.cpp
 *
 *  Created on: 10 de ago. de 2015
 *      Author: amides
 */

#include "EmailListElementDelete.h"
#include <algorithm>

#include "../MD5Utility.h"
#include "../NetworkUtils.hpp"
#include <set>

EmailListElementDelete::EmailListElementDelete()
						:masterList(0),
						 delList(0),
					     domainList(0),
					     sortResult(false),
						 md5SuppresionListEnabled(false),
						 handler(0),
						 erasedElementsList(0)
{

}

EmailListElementDelete::~EmailListElementDelete() {
}

void EmailListElementDelete::setParameters( std::list<std::string>* masterList,
											std::vector<std::string>* delList,
											std::vector<std::string>* domainList,
											std::vector<std::string>* erasedElementsList,
											bool sortResult,
											bool md5SuppresionListEnabled,
											FinishedCurrentJobHandler * handler)
{
	this->masterList = masterList;
	this->delList = delList;
	this->domainList = domainList;
	this->sortResult = sortResult;
	this->handler = handler;
	this->erasedElementsList = erasedElementsList;
	this->md5SuppresionListEnabled = md5SuppresionListEnabled;
}

void EmailListElementDelete::execute()
{
	std::list<std::string>::iterator listIter;
	std::list<std::string>::iterator delPosIter;
	std::vector<std::string>::iterator vectorIter;

	if( md5SuppresionListEnabled )
	{
		deleteElementsBySuppressionList();
	}
	else
	{
		for( vectorIter = delList->begin();vectorIter != delList->end();++vectorIter )
		{
			std::string e((*vectorIter));
			masterList->remove(e);
		}//end first for
	}

	for(vectorIter = domainList->begin();vectorIter != domainList->end();++vectorIter)
	{
		std::string domain((*vectorIter));
		for(listIter = masterList->begin();listIter != masterList->end();++listIter)
		{
			std::string masterEleDomain(NetworkUtils::getDomainFromEmail(*listIter));
			if(!domain.compare(masterEleDomain))
			{
				delPosIter = listIter;
				listIter--;
				erasedElementsList->push_back(*delPosIter);
				masterList->erase(delPosIter);
			}
		}
	}

	if(sortResult)
	{
		masterList->sort(EmailListElementDelete::compare);
	}
	handler->ListElementsDeleteEnd(OK);
}

void EmailListElementDelete::deleteElementsBySuppressionList()
{
	std::list<std::string>::iterator listIter;
	std::list<std::string>::iterator delIter;
	std::vector<std::string>::iterator vecIter;

	std::set<std::string> suppressionList;
	std::set<std::string>::iterator setIter;

	suppressionList.insert(delList->begin(),delList->end());

	for(listIter = masterList->begin();listIter != masterList->end(); ++listIter)
	{
		std::string _md5 = md5(*listIter);
		//vecIter = std::find(delList->begin(),delList->end(),_md5);
		setIter = suppressionList.find(_md5);

		if( setIter != suppressionList.end())
		{
			delIter = listIter;
			listIter--;

			erasedElementsList->push_back(*delIter);
			masterList->erase(delIter);
		}
	}
}

bool EmailListElementDelete::compare(std::string a,std::string b)
{
	std::string domaina = NetworkUtils::getDomainFromEmail(a);
	std::string domainb = NetworkUtils::getDomainFromEmail(b);

	return (domaina.compare(domainb) < 0);
}




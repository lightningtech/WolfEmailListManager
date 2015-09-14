/*
 * MergeEmailListTask.cpp
 *
 *  Created on: 6 de ago. de 2015
 *      Author: amides
 */

#include "MergeEmailListTask.h"
#include <iostream>

MergeEmailListTask::MergeEmailListTask()
{

}

MergeEmailListTask::~MergeEmailListTask()
{

}

void MergeEmailListTask::execute()
{
	std::list<std::string>::iterator it;
	for( std::size_t i = 0; i < toMergeList->size(); i++ )
	{
		std::string merging(toMergeList->at(i));
		for(it = hostList->begin(); it != hostList->end(); it++)
		{
			if( !(*it).compare(merging))
			{
				break;
			}
		}//end inside for
		hostList->push_back(merging);
	}
	handler->endingMergeListJob(OK);
}

void MergeEmailListTask::setParameters( std::vector<std::string>* toMergeList,
										std::list<std::string>* hostList,
										FinishedCurrentJobHandler * handler )
{
	this->toMergeList = toMergeList;
	this->hostList = hostList;
    this->handler = handler;
}

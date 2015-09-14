/*
 * SeedAddressesTask.cpp
 *
 *  Created on: 20 de ago. de 2015
 *      Author: amides
 */

#include "SeedAddressesTask.h"
#include <cstdlib>

SeedAddressesTask::SeedAddressesTask()
				:inputList(0),
				 toSeedAddresses(0),
			     numberOfTimes(0),
				 functionCode(0),
				 handler(0)
{

}

SeedAddressesTask::~SeedAddressesTask()
{
}

void SeedAddressesTask::incrementListIter( std::list<std::string>::iterator &iter,
										   const int numberPositions )
{
	int n = numberPositions;
	while( n > 0)
	{
		iter++;
		n--;
	}
}

void SeedAddressesTask::seedUniformInterval()
{
	int slides = inputList->size() / numberOfTimes;
	std::list<std::string>::iterator iter = inputList->begin();

	while(numberOfTimes > 0)
	{
		incrementListIter(iter,slides);
		inputList->insert(iter,toSeedAddresses->begin(),
						  toSeedAddresses->end());
		numberOfTimes--;
	}
}

void SeedAddressesTask::seedRandomInterval()
{
	std::list<std::string>::iterator iter = inputList->begin();
	std::size_t size = inputList->size();
	int slides = 0;

	while(numberOfTimes > 0)
	{
		slides = rand()%size;
		incrementListIter(iter,slides);
		inputList->insert(iter,toSeedAddresses->begin(),
						  toSeedAddresses->end());
		iter = inputList->begin();
		numberOfTimes--;
	}
}

void SeedAddressesTask::seedAtNaddresses()
{
	std::list<std::string>::iterator iter = inputList->begin();
	incrementListIter(iter,numberOfTimes);
	inputList->insert(iter,toSeedAddresses->begin(),
					  toSeedAddresses->end());
}

void SeedAddressesTask::execute()
{
	bool suported = true;
	switch(functionCode)
	{
		case 0:
		{
			//seed at uniform interval( x number of times to seed )
			seedUniformInterval();
		}
		break;
		case 1:
		{
			//seed at random interval (x number of times to seed)
			seedRandomInterval();
		}
		break;
		case 2:
		{
			//seed at x number of addresses
			seedAtNaddresses();
		}
		break;
		default:
		{
			suported = false;
			handler->seedAddressesEnded(FunctionCodeErr,std::string("Function Code not supported"));
		}
		break;
	}

	if( suported )
	{
		handler->seedAddressesEnded(OK);
	}
}

void SeedAddressesTask::setParameters( std::list<std::string> * inputList,
						std::vector<std::string>* toSeedAddresses,
						int numberOfTimes,
						int functionCode,
						FinishedCurrentJobHandler * handler )
{
	this->inputList = inputList;
	this->toSeedAddresses = toSeedAddresses;
	this->numberOfTimes = numberOfTimes;
	this->functionCode = functionCode;
	this->handler = handler;
}

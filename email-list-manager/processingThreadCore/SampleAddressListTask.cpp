/*
 * SampleAddressListTask.cpp
 *
 *  Created on: 14 de ago. de 2015
 *      Author: amides
 */

#include "SampleAddressListTask.h"
#include <cstdlib>
#include <iostream>

SampleAddressListTask::SampleAddressListTask()
							:inputList(0),indicator(-1),
							 numberOfSamples(0),
							 startingAtAddress(""),
							 handler(0)

{

}

SampleAddressListTask::~SampleAddressListTask()
{
}

int SampleAddressListTask::getNMatchElements()
{
	if( (unsigned long)numberOfSamples <= inputList->size()
			&& startingAtAddress.size() > 0)
	{
		for(std::size_t i;i < inputList->size(); i++ )
		{
			std::string element( inputList->at(i));
			unsigned int pos = element.find(startingAtAddress);

			if( pos != std::string::npos && pos == 0 )//at start
			{
				outputList.push_back( element );
				numberOfSamples --;

				if(numberOfSamples == 0)
				{
					return 0;//error OK
				}
			}
		}
	}
	else if( !startingAtAddress.size())
	{
		std::vector<std::string>::iterator iter = inputList->begin();
		iter += numberOfSamples;
		outputList.assign(inputList->begin(),iter);
		return 0;
	}

	return 1;///no se cumplio por error
}

int SampleAddressListTask::getRamdonElements()
{
	if( (unsigned long)numberOfSamples <= inputList->size())
	{
		std::size_t iSize = inputList->size();
		for(long i = 0; i < numberOfSamples; i++)
		{
			int randPos = rand() % iSize;
			randPos = (randPos == 0) ? 0 : randPos-1;
			outputList.push_back( inputList->at(randPos) );
		}

		return 0;
	}

	return 1;
}

int SampleAddressListTask::getConsecutiveNElements()
{
	if( (unsigned long)numberOfSamples <= inputList->size()
			&& startingAtAddress.size() > 0)
	{
		long startCount = 0;
		std::vector<std::string>::iterator iter = inputList->begin();
		std::vector<std::string>::iterator iter2 = inputList->begin();

		for(std::size_t i = 0; i < inputList->size();i++ )
		{
			std::string element( inputList->at(i));
			unsigned int pos = element.find(startingAtAddress);

			if( pos != std::string::npos && pos == 0 )//at start
			{
				startCount++;
				if( startCount >= numberOfSamples )
				{
					iter += (i-startCount+1);
					iter2 += (i+1);
					outputList.assign(iter,iter2);
					return 0;
				}
			}
			else if( startCount > 0 )
			{
				startCount = 0;
			}
		}
	}
	else if( !startingAtAddress.size())
	{
		std::vector<std::string>::iterator iter = inputList->begin();
		iter += numberOfSamples;
		outputList.assign(inputList->begin(),iter);
		return 0;
	}

	return 1;
}

void SampleAddressListTask::execute()
{
	std::cout << "SampleAddressListTask::execute() ... " << std::endl;
	int error = 0;
	switch( indicator )
	{
		case 0:
		{
			std::cout << "SampleAddressListTask::execute() 11111111111 ... " << std::endl;
			int error = getNMatchElements();
		}
		break;
		case 1:
		{
			int error = getRamdonElements();
		}
		break;
		case 2:
		{
			int error = getConsecutiveNElements();
		}break;
		default:break;
	}

	handler->sampleAddressEnded(outputList,error);
}


void SampleAddressListTask::setParameters(	std::vector<std::string> * inputList,
											int indicator,
											long numberOfSamples,
											std::string startingAtAddress,
											FinishedCurrentJobHandler* handler )
{
	this->inputList = inputList;
	this->indicator = indicator;
	this->numberOfSamples = numberOfSamples;
	this->startingAtAddress = startingAtAddress;
	this->handler = handler;
}

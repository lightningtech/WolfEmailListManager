/*
 * SplitAddressesTask.cpp
 *
 *  Created on: 20 de ago. de 2015
 *      Author: amides
 */

#include "SplitAddressesTask.h"
#include <iostream>

SplitAddressesTask::SplitAddressesTask()
					:inputList(0),
					 functionCode(0),
					 n(0),
					 handler(0)
{

}

SplitAddressesTask::~SplitAddressesTask()
{
}

std::vector<std::string> SplitAddressesTask::splitByAddressesNumber(std::size_t start)
{
	std::vector<std::string>::iterator startIter = inputList->begin();
	std::vector<std::string>::iterator endIter = inputList->begin();

	startIter += start;

	if( start + n >= inputList->size() )
	{
		endIter = inputList->end();
	}
	else
	{
		endIter += (start + n);
	}


	std::vector<std::string> result(n);
	result.assign(startIter,endIter);
	return result;
}

std::vector<std::string> SplitAddressesTask::splitByListNumber(std::size_t start,
															   std::size_t numberOfElements)
{
	std::vector<std::string>::iterator startIter = inputList->begin();
	std::vector<std::string>::iterator endIter = inputList->begin();

	startIter += start;
	int calculatedEnd = start + numberOfElements;
	if(calculatedEnd >= inputList->size())
	{
		int excedent = calculatedEnd-inputList->size();
		calculatedEnd -= excedent;
	}

	endIter += calculatedEnd;

	std::vector<std::string> result( calculatedEnd - start + 1 );
	result.assign(startIter,endIter);
	return result;
}


void SplitAddressesTask::execute()
{
	switch( functionCode )
	{
		case 0:
		{
			//aqui n es la cantidad de direcciones x lista
			if((unsigned int)n <= inputList->size())
			{
				int parts = inputList->size() / n;//parts es numero de listas
				int rest = inputList->size() % n;
				std::size_t increment = 0;

				if(rest != 0)
				{
					parts++;
				}

				while( parts > 0 )
				{
					handler->splitAddressesEnded(splitByAddressesNumber(increment),OK);
					increment += n;
					parts--;
				}
			}
			else
			{
				std::vector<std::string> result;
				handler->splitAddressesEnded(result,WrongSizeParametersErr,
										     std::string("N larger than vector size"));
			}
		}
		break;
		case 1:
		{
			//aqui n es la cantidad de listas de salida
			int numberOfElements = inputList->size() / n; //numberOfElements elementos en una lista
			int  rest = inputList->size() % n;
			int cycleEntry = n;
			int start = 0;

			std::vector<std::string> result;

			while( cycleEntry > 0)
			{
				if( cycleEntry == 1 && rest > 0 )
				{
					numberOfElements += rest;
				}

				std::cout << " numberOfElements ... " << numberOfElements <<""
						" rest "<< rest<< '\n';
				result = splitByListNumber(start,numberOfElements);
				handler->splitAddressesEnded(result,OK);

				start += numberOfElements;
				cycleEntry--;
			}
		}
		break;
	}
}

void SplitAddressesTask::setParameters( std::vector<std::string>* inputList,
										int functionCode,
										int n,
										FinishedCurrentJobHandler * handler)
{
	this->functionCode = functionCode;
	this->inputList = inputList;
	this->n = n;
	this->handler = handler;
}

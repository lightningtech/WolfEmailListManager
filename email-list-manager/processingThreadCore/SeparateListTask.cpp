/*
 * SeparateListTask.cpp
 *
 *  Created on: 18 de ago. de 2015
 *      Author: amides
 */

#include "SeparateListTask.h"
#include "../NetworkUtils.hpp"
#include <algorithm>

SeparateListTask::SeparateListTask()
					:input(0),
   	 	 	 	     functionCode(0),
					 modeCode(0),
					 domainSeparateList(0),
					 randomPacketSize(0),
					 handler(0)
{

}

SeparateListTask::~SeparateListTask()
{

}

void SeparateListTask::getEmailsByDomain(std::map<std::string,std::set<std::string> > &_mapSetResult)
{
	std::vector<std::string> leftEmails;
	std::map< std::string,std::set<std::string> >::iterator _iter;

	for( std::size_t i = 0; i < domainSeparateList->size() ; i++ )
	{
		std::set<std::string> insideSet;
		std::string domain(domainSeparateList->at(i));
		size_t pos = domain.find('@');

		if( pos != std::string::npos )
		{
			domain = domain.substr(pos+1);
		}

		_mapSetResult.insert(std::make_pair(domain,insideSet));
	}

	for( std::size_t i = 0; i < input->size() ; i++ )
	{
		std::string email(input->at(i));
		std::string listDomain( NetworkUtils::getDomainFromEmail(email) );

		_iter = _mapSetResult.find(listDomain);
		if(_iter == _mapSetResult.end())
		{
			leftEmails.push_back(email);
		}
		else
		{
			_iter->second.insert(email);
		}
	}//end for

	*input = leftEmails;
}


void SeparateListTask::getEmailsByCountryCode(std::map<std::string,std::set<std::string> > &_mapSetResult)
{
	std::string countryCode;
	bool founded = false;

	std::map<std::string,std::set<std::string> >::iterator mapSetIter;
	for( std::size_t i = 0;i<input->size();i++ )
	{
		std::string currentEmail(input->at(i));
		countryCode = NetworkUtils::getCountryCode(currentEmail);
		mapSetIter = _mapSetResult.find(countryCode);

		if( mapSetIter == _mapSetResult.end())
		{
			std::set<std::string> codeSet;
			codeSet.insert(currentEmail);
			_mapSetResult.insert( std::make_pair(countryCode,codeSet));
		}
		else
		{
			mapSetIter->second.insert(currentEmail);
		}
	}
}

void SeparateListTask::getRandomPacketsOf(const unsigned long long start,
									      std::set<std::string> &result)
{
	unsigned long long final = start+randomPacketSize;

	if( final >= input->size() )
	{
		final = input->size();
	}

	for( std::size_t i = start; i < final ; i++)
	{
		result.insert(input->at(i));
	}
}

void SeparateListTask::execute()
{
	int joinCode = functionCode * 10 + modeCode;
	std::map<std::string,std::set<std::string> >::iterator _iter;
	std::map<std::string,std::set<std::string> > _mapSetResult;


	switch( joinCode )
	{
	  case 11:case 12:case 13:
	  {
		  getEmailsByDomain(_mapSetResult);
		  bool last = false;
		  std::size_t n = 1;

		  for(_iter=_mapSetResult.begin();_iter != _mapSetResult.end();++_iter )
		  {
			  if( n == _mapSetResult.size() )
			  {
				  last = true;
			  }

			  n++;
			  handler->separateListEnded(_iter->second,last,OK);
		  }
	  }break;
	  case 21:case 22:case 23:
	  {
		  getEmailsByCountryCode(_mapSetResult); //always is deDup and sort
		  bool last = false;
		  std::size_t n = 1;

		  for(_iter=_mapSetResult.begin();_iter != _mapSetResult.end();++_iter )
		  {
			  if( n == _mapSetResult.size() )
			  {
				  last = true;
			  }

			  n++;
			  handler->separateListEnded(_iter->second,last,OK);
		  }
	  }break;
	  case 31:case 32:case 33:
	  {
		  int numberPackages = input->size()/randomPacketSize;
		  if(input->size()%randomPacketSize != 0 )
			  numberPackages++;

		  std::set<std::string> _set;
		  unsigned long long start = 0;
		  bool last = false;

		  for(int i = 0; i < numberPackages;i++)
		  {
			  last = (i == numberPackages-1) ? true : false;
			  getRandomPacketsOf(start,_set);
			  start += randomPacketSize;

			  handler->separateListEnded(_set,last,OK);
			  _set.clear();
		  }
	  }break;
	  case 45://random el archivo para output
	  {
		  std::set<std::string> _set;
		  _set.insert(input->begin(),input->end());

		  handler->separateListEnded(_set,true,OK);
	  }break;
	  default:
	  {
		  std::cout << " Codigos insertados invalidos "<<"\n\n";
		  std::set<std::string> _set;
		  handler->separateListEnded(_set,true,FunctionCodeErr,
				  	  	  	  	  	 std::string("Codigos no validos"));
	  }
	  break;
	}//end switch case

}//end execute

void SeparateListTask::setParameters(std::vector<std::string>* input,
					   	   	   	     int functionCode,int modeCode,
									 std::vector<std::string>* domainSeparateList,
									 unsigned long long randomPacketSize,
									 FinishedCurrentJobHandler* handler)
{
	this->input = input;
	this->functionCode = functionCode;

	this->modeCode = modeCode;

	this->domainSeparateList = domainSeparateList;
	this->randomPacketSize = randomPacketSize;
	this->handler = handler;
}

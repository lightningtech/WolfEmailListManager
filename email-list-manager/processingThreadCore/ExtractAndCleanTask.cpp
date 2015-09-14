/*
 * ExtractAndCleanTask.cpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#include "ExtractAndCleanTask.h"
#include "UtilsHeaders.hpp"
#include <boost/thread/mutex.hpp>

ExtractAndCleanTask::ExtractAndCleanTask()
					:emailListVector(0)
{

}

ExtractAndCleanTask::~ExtractAndCleanTask()
{
	if( emailListVector )
		delete emailListVector;
}

void ExtractAndCleanTask::setParameters(std::vector<std::string> *pemails,
					   int maximumCharactersRejectAddress,char CONFIG_PARAMETERS_FLAG,
					   std::vector<std::string> &cDomains,
					   std::vector<std::string> * insertedDomains,
					   boost::mutex * insertedDomainmutex,
					   boost::mutex * handlerMutex,
					   FinishedCurrentJobHandler * handler)
{
	this->emailListVector = pemails;
	this->maximumCharactersRejectAddress = maximumCharactersRejectAddress;
	this->CONFIG_PARAMETERS_FLAG = CONFIG_PARAMETERS_FLAG;
	this->countryDomains = cDomains;
	this->insertedDomainmutex = insertedDomainmutex;
	this->insertedDomains = insertedDomains;
	this->handler = handler;
	this->handlerMutex = handlerMutex;

	allowEmbeddedS = (this->CONFIG_PARAMETERS_FLAG & ALLOW_EMBEDDED_SPACES_AOL) ? true : false;
	notDuplicateDomains = (this->CONFIG_PARAMETERS_FLAG & NO_DUPLICATE_DOMAINS) ? true : false;
	rejectLongDomains = (this->CONFIG_PARAMETERS_FLAG & REJECT_LONG_DOMAINS ) ? true : false;
	removeDuplicates = (this->CONFIG_PARAMETERS_FLAG & REMOVE_DUPLICATES ) ? true : false;
}

void ExtractAndCleanTask::execute()
{
	std::cout << " Start....... "<< '\n';
	std::string email = "";
	std::string domain = "";
	bool invalidNoCountryDomain = false;
	bool invalidCountryDomain = false;
	std::vector<std::string>::iterator vectIter;
	std::vector<std::string>::iterator auxIter;

	bool validEmailRegex = false;
	std::size_t vecSize = emailListVector->size();

	for( std::size_t i = 0; i < vecSize; i++)
	{
		email = emailListVector->at(i);
 	    validEmailRegex = NetworkUtils::isValidEmail(email,maximumCharactersRejectAddress,allowEmbeddedS);

		if( validEmailRegex )
		{
			email = NetworkUtils::validateEmail(email);
			domain = NetworkUtils::getCountryCode(email);

			if(domain.size() > 0)
			{
				vectIter = std::find(countryDomains.begin(),countryDomains.end(), domain);
				invalidNoCountryDomain = ((vectIter != countryDomains.end())&&
									(std::count(domain.begin(), domain.end(), '.') >= 2));
				invalidCountryDomain = ((vectIter != countryDomains.end()) &&
									   (std::count(domain.begin(), domain.end(), '.') >= 3));
			}

			if (notDuplicateDomains)
			{
				{
					boost::mutex::scoped_lock lock(*insertedDomainmutex);
					vectIter = std::find(insertedDomains->begin(),insertedDomains->end(),domain);
					auxIter = insertedDomains->end();
				}

				if( vectIter != auxIter )
				{
					outputVectorRejectedAddresses.push_back(email);
					continue;
				}
			}

			if( rejectLongDomains && (invalidNoCountryDomain || invalidCountryDomain) )
			{
				outputVectorRejectedAddresses.push_back(email);
				continue;
			}

			this->outputVector.push_back(email);

			insertedDomainmutex->lock();
				this->insertedDomains->push_back(domain);
			insertedDomainmutex->unlock();
		}
		else{
			outputVectorRejectedAddresses.push_back(email);
		}
	}//end for

	countryDomains.clear();
	std::cout << " Fin....... "<< '\n';

	boost::mutex::scoped_lock lock(*handlerMutex);
	handler->endingCurrentJob(outputVector,outputVectorRejectedAddresses,OK);//codigo 0 significa OK.

	outputVector.clear();
	outputVectorRejectedAddresses.clear();
}









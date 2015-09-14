/*
 * ExtractAndCleanTask.h
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_EXTRACTANDCLEANTASK_H_
#define PROCESSINGTHREADCORE_EXTRACTANDCLEANTASK_H_

#include "AbstractJobTask.hpp"
#include <boost/thread.hpp>
#include "../Python2CUtils.hpp"
#include "../FinishedCurrentJobHandler.hpp"

class DLLM_LOCAL ExtractAndCleanTask : public AbstractJobTask
{
public:
	ExtractAndCleanTask();

	virtual ~ExtractAndCleanTask();

	void setParameters(std::vector<std::string> *pemails,
					   int maximumCharactersRejectAddress,char CONFIG_PARAMETERS_FLAG,
					   std::vector<std::string> &cDomains,
					   std::vector<std::string> * insertedDomains,
					   boost::mutex * insertedDomainmutex,
					   boost::mutex * handlerMutex,
					   FinishedCurrentJobHandler * handler);

	void execute();

private:
	std::vector<std::string> *emailListVector;

	bool allowEmbeddedS;
	bool notDuplicateDomains;
	bool rejectLongDomains;
	bool removeDuplicates;

	int maximumCharactersRejectAddress;
	char CONFIG_PARAMETERS_FLAG;
	std::vector<std::string> countryDomains;
	std::list<std::string> outputVector;
	std::vector<std::string> outputVectorRejectedAddresses;
	std::vector<std::string> * insertedDomains;
	boost::mutex * insertedDomainmutex;
	boost::mutex * handlerMutex;
	FinishedCurrentJobHandler * handler;
};

#endif /* PROCESSINGTHREADCORE_EXTRACTANDCLEANTASK_H_ */

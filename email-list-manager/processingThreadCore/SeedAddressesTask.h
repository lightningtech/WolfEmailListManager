/*
 * SeedAddressesTask.h
 *
 *  Created on: 20 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_SEEDADDRESSESTASK_H_
#define PROCESSINGTHREADCORE_SEEDADDRESSESTASK_H_

#include "../FinishedCurrentJobHandler.hpp"
#include "AbstractJobTask.hpp"
#include "../Errors.hpp"

class DLLM_LOCAL SeedAddressesTask: public AbstractJobTask
{
public:
	SeedAddressesTask();
	virtual ~SeedAddressesTask();

	void execute();
	void setParameters( std::list<std::string> * inputList,
						std::vector<std::string>* toSeedAddresses,
						int numberOfTimes,
						int functionCode,
						FinishedCurrentJobHandler * handler );

private:
	std::list<std::string> * inputList;
	std::vector<std::string>* toSeedAddresses;
	int numberOfTimes;
	int functionCode;
	FinishedCurrentJobHandler * handler;

	void seedUniformInterval();

	void seedRandomInterval();

	void seedAtNaddresses();

	void incrementListIter( std::list<std::string>::iterator &iter,
						    const int numberPositions );
};

#endif /* PROCESSINGTHREADCORE_SEEDADDRESSESTASK_H_ */

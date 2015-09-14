/*
 * SplitAddressesTask.h
 *
 *  Created on: 20 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_SPLITADDRESSESTASK_H_
#define PROCESSINGTHREADCORE_SPLITADDRESSESTASK_H_

#include "AbstractJobTask.hpp"
#include "../FinishedCurrentJobHandler.hpp"
#include "../Errors.hpp"

class DLLM_LOCAL SplitAddressesTask : public AbstractJobTask
{
public:
	SplitAddressesTask();
	virtual ~SplitAddressesTask();

	void execute();
	void setParameters(std::vector<std::string>* inputList,
						int functionCode,
						int n,
						FinishedCurrentJobHandler * handler);

private:

	std::vector<std::string>* inputList;
	int functionCode;
	int n;
	FinishedCurrentJobHandler * handler;

	std::vector<std::string> splitByAddressesNumber(std::size_t start);
	std::vector<std::string> splitByListNumber(std::size_t start,std::size_t numberOfElements);
};

#endif /* PROCESSINGTHREADCORE_SPLITADDRESSESTASK_H_ */

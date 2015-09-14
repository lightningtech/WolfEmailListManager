/*
 * SampleAddressListTask.h
 *
 *  Created on: 14 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_SAMPLEADDRESSLISTTASK_H_
#define PROCESSINGTHREADCORE_SAMPLEADDRESSLISTTASK_H_

#include "AbstractJobTask.hpp"
#include "../FinishedCurrentJobHandler.hpp"

class DLLM_LOCAL SampleAddressListTask : public AbstractJobTask
{
public:
	SampleAddressListTask();
	virtual ~SampleAddressListTask();

	void execute();
	void setParameters(	std::vector<std::string> * inputList,
						int indicator,
						long numberOfSamples,
						std::string startingAtAddress,
						FinishedCurrentJobHandler* handler);

private:
	int getNMatchElements();

	int getRamdonElements();

	int getConsecutiveNElements();

	std::vector<std::string> * inputList;
	std::vector<std::string> outputList;
	int indicator;
	long numberOfSamples;
	std::string startingAtAddress;
	FinishedCurrentJobHandler* handler;
};

#endif /* PROCESSINGTHREADCORE_SAMPLEADDRESSLISTTASK_H_ */

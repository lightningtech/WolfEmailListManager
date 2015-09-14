/*
 * SeparateListTask.h
 *
 *  Created on: 18 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_SEPARATELISTTASK_H_
#define PROCESSINGTHREADCORE_SEPARATELISTTASK_H_

#include "../FinishedCurrentJobHandler.hpp"
#include "AbstractJobTask.hpp"

class DLLM_LOCAL SeparateListTask : public AbstractJobTask
{
public:
	SeparateListTask();
	virtual ~SeparateListTask();

	void execute();

	void setParameters(std::vector<std::string>* input,
					   int functionCode,int modeCode,
					   std::vector<std::string>* domainSeparateList,
					   unsigned long long randomPacketSize,
					   FinishedCurrentJobHandler* handler);

private:
	std::vector<std::string>* input;
	int functionCode;
	int modeCode;
	std::vector<std::string>* domainSeparateList;
	FinishedCurrentJobHandler* handler;
	unsigned long long randomPacketSize;

	void getEmailsByCountryCode(std::map< std::string,std::set<std::string> > &_mapSetResult);

	void getEmailsByDomain(std::map< std::string,std::set<std::string> > &_mapSetResult);

	void getRandomPacketsOf(const unsigned long long start,
							std::set<std::string> &result);
};

#endif /* PROCESSINGTHREADCORE_SEPARATELISTTASK_H_ */

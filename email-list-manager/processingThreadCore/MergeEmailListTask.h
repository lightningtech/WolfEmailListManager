/*
 * MergeEmailListTask.h
 *
 *  Created on: 6 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_MERGEEMAILLISTTASK_H_
#define PROCESSINGTHREADCORE_MERGEEMAILLISTTASK_H_

#include "AbstractJobTask.hpp"
#include "../FinishedCurrentJobHandler.hpp"
#include <vector>
#include <list>
#include <string>

class DLLM_LOCAL MergeEmailListTask : public AbstractJobTask
{
public:
	MergeEmailListTask();
	virtual ~MergeEmailListTask();

	void execute();

	void setParameters( std::vector<std::string>* toMergeList,
						std::list<std::string>* hostList,
						FinishedCurrentJobHandler * handler);

private:
	std::vector<std::string>* toMergeList;
	std::list<std::string>* hostList;
    FinishedCurrentJobHandler * handler;
};

#endif /* PROCESSINGTHREADCORE_MERGEEMAILLISTTASK_H_ */

/*
 * EmailListElementDelete.h
 *
 *  Created on: 10 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_EMAILLISTELEMENTDELETE_H_
#define PROCESSINGTHREADCORE_EMAILLISTELEMENTDELETE_H_

#include "../FinishedCurrentJobHandler.hpp"
#include "AbstractJobTask.hpp"

class DLLM_LOCAL EmailListElementDelete : public AbstractJobTask
{
public:
	EmailListElementDelete();
	virtual ~EmailListElementDelete();

	void execute();
	void setParameters( std::list<std::string>* masterList,
						std::vector<std::string>* delList,
						std::vector<std::string>* domainList,
						std::vector<std::string>* erasedElementsList,
						bool sortResult,
						bool md5SuppresionListEnabled,
						FinishedCurrentJobHandler * handler);
private:
	std::list<std::string>* masterList;
	std::vector<std::string>* delList;
	std::vector<std::string>* domainList;
	bool sortResult;
	bool md5SuppresionListEnabled;
	FinishedCurrentJobHandler * handler;
	std::vector<std::string>* erasedElementsList;

	static bool compare(std::string a,std::string b);
	void deleteElementsBySuppressionList();
};

#endif /* PROCESSINGTHREADCORE_EMAILLISTELEMENTDELETE_H_ */

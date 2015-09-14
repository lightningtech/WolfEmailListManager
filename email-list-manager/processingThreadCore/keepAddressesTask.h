/*
 * keepAddressesTask.h
 *
 *  Created on: 11 de ago. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_KEEPADDRESSESTASK_H_
#define PROCESSINGTHREADCORE_KEEPADDRESSESTASK_H_

#include "AbstractJobTask.hpp"
#include <boost/thread.hpp>

#include "../FinishedCurrentJobHandler.hpp"
class DLLM_LOCAL keepAddressesTask : public AbstractJobTask
{
public:
	keepAddressesTask();
	virtual ~keepAddressesTask();

	void execute();
	void setParameters(std::vector<std::string>* endingLines,
		    		   std::vector<std::string>* filterStrings,
					   std::vector<std::string>* erasedAddresses,
		               std::vector<std::string>* emailList,
					   FinishedCurrentJobHandler* handler,int start,int end);
private:

	std::vector<std::string>* endingLines;
    std::vector<std::string>* filterStrings;
	std::vector<std::string> emailList;
	std::vector<std::string>* erasedAddresses;
	FinishedCurrentJobHandler* handler;
	int start;
	int end;

	bool checkEndingLines(std::string address);
	bool checkingFilterStrings(std::string address);

	static boost::mutex _mutex;
};

#endif /* PROCESSINGTHREADCORE_KEEPADDRESSESTASK_H_ */




/*
 * ConsumersManager.h
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_CONSUMERSMANAGER_H_
#define PROCESSINGTHREADCORE_CONSUMERSMANAGER_H_

#include "Consumer.h"
#include "ExtractAndCleanTask.h"
#include "MergeEmailListTask.h"
#include "EmailListElementDelete.h"
#include "SampleAddressListTask.h"

class DLLM_LOCAL ConsumersManager
{
public:
	ConsumersManager(int threadsNumber,FinishedCurrentJobHandler * handler );

	virtual ~ConsumersManager();

	void extractAndClean( std::vector<std::string> *pemails,
						  int maximumCharactersRejectAddress,char CONFIG_PARAMETERS_FLAG,
						  std::vector<std::string> * cDomains);

	void mergeEmailLists(std::vector<std::string> *toMergeList,
						 std::list<std::string> *hostList);

	void deleteEmailListElements(std::list<std::string>* masterList,
								 std::vector<std::string>* deleteList,
								 std::vector<std::string>* deleteDomainList,
								 std::vector<std::string>* erasedElements,
								 bool sort,bool md5SuppresionListEnabled );

	void keepAddress( std::vector<std::string>* endingLines,
					  std::vector<std::string>* filterStrings,
					  std::vector<std::string>* emailList);

	void sampleAddresses(std::vector<std::string>* input,
						 int sampleIndicator,
						 int numberElements,string filterWord);

	void separateList(std::vector<std::string>* input,int functionCode,
			 		  int modeCode,std::vector<std::string>* domainList,
					  unsigned long long randomPackageSize);

	void seedAddresses(std::list<std::string>* input,
					   std::vector<std::string>* toSeedAddresses,
					   int numberOfTimes,
					   int functionCode);

	void splitAddressesList(std::vector<std::string>* inputList,
							int functionCode,
							int n);

private:
	int threadsNumber;
	std::queue<AbstractJobTask*> taskQueue;
	boost::mutex queueAccesMutex;
	boost::condition_variable_any condition;

    std::vector<std::string> insertedDomains;
    boost::mutex countryDomainmutex;
    boost::mutex insertedDomainmutex;
    boost::mutex validEmailmutex;
    boost::mutex handlerMutex;

    std::vector<Consumer*> consumersVector;
    FinishedCurrentJobHandler * handler;
};

#endif /* PROCESSINGTHREADCORE_CONSUMERSMANAGER_H_ */

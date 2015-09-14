/*
 * ConsumersManager.cpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#include "ConsumersManager.h"
#include "keepAddressesTask.h"
#include "SeparateListTask.h"
#include "SeedAddressesTask.h"
#include "SplitAddressesTask.h"


ConsumersManager::ConsumersManager(int threadsNumber,FinishedCurrentJobHandler * handler)
									:handler(handler),threadsNumber(threadsNumber)
{
	Consumer * myThread = 0;
	for (int i = 0; i < this->threadsNumber;i++ )
	{
		myThread = new Consumer(&taskQueue,&queueAccesMutex,&condition);
		consumersVector.push_back(myThread);
		myThread->excecute();
	}
}

ConsumersManager::~ConsumersManager()
{

}

void ConsumersManager::extractAndClean( std::vector<std::string> *pemails,
			             int maximumCharactersRejectAddress,char CONFIG_PARAMETERS_FLAG,
						 std::vector<std::string> * cDomains )
{
	std::size_t rest = pemails->size() % threadsNumber;
	std::size_t elemtsByConsumer = pemails->size() / threadsNumber;
	std::size_t startPositions = 0;
	std::size_t realIncrementElements = 0;

	ExtractAndCleanTask * extractTask = 0;
	std::size_t size = consumersVector.size();

	std::vector<std::string> * mInput = 0;

	std::vector<std::string>::iterator startIter = pemails->begin();
	std::vector<std::string>::iterator endIter = pemails->begin();

	std::cout <<" Start assignament of task parameters"<< "\n";
	for( std::size_t i = 0;i < size ; i++ )
	{
		extractTask = new ExtractAndCleanTask();
		realIncrementElements = (rest)?1:0;

		if (rest)
			rest--;

		std::size_t finalPos = startPositions + elemtsByConsumer+realIncrementElements;

		startIter += startPositions;
		endIter += finalPos;

		mInput = new std::vector<std::string>();
		mInput->assign(startIter,endIter);

		extractTask->setParameters(mInput,maximumCharactersRejectAddress,CONFIG_PARAMETERS_FLAG,
									*cDomains,&insertedDomains,&insertedDomainmutex,&handlerMutex,
									handler);

		startIter = pemails->begin();
		endIter = pemails->begin();


		{
			boost::mutex::scoped_lock lock(queueAccesMutex);
			taskQueue.push(extractTask);
		}

		startPositions = finalPos;
	}

	std::cout <<" End assignament of task parameters"<< "\n";
	cDomains->clear();
	pemails->clear();
	std::cout << " sending signal to consummer ... " <<'\n';
	condition.notify_all();
}


void ConsumersManager::mergeEmailLists(std::vector<std::string> *toMergeList,
				     	 	 	 	   std::list<std::string> *hostList)
{
	MergeEmailListTask * mergeTask = new MergeEmailListTask();
	mergeTask->setParameters(toMergeList,hostList,handler);

	taskQueue.push(mergeTask);
	condition.notify_one();
}


void ConsumersManager::deleteEmailListElements(std::list<std::string>* masterList,
							 	 	 	 	   std::vector<std::string>* deleteList,
							                   std::vector<std::string>* deleteDomainList,
											   std::vector<std::string>* erasedElements,
											   bool sort,bool md5SuppresionListEnabled )
{
	EmailListElementDelete * deleteTask = new EmailListElementDelete();
	deleteTask->setParameters(masterList,deleteList,deleteDomainList,
							  erasedElements,sort,md5SuppresionListEnabled,handler);

	{
		boost::mutex::scoped_lock lock(queueAccesMutex);
		taskQueue.push(deleteTask);
		condition.notify_one();
	}
}

void ConsumersManager::keepAddress( std::vector<std::string>* endingLines,
								    std::vector<std::string>* filterStrings,
								    std::vector<std::string>* emailList)
{
	int rest = emailList->size() % threadsNumber;
	int elemtsByConsumer = emailList->size() / threadsNumber;

	int startPositions = 0;
	int realIncrementElements = 0;
	int finalPos = 0;

	keepAddressesTask * task = 0;
	for( int i = 0; i < threadsNumber ; i++ )
	{
		if (rest)
			rest--;

		finalPos = startPositions + elemtsByConsumer+realIncrementElements;

		task = new keepAddressesTask();
		task->setParameters(endingLines,filterStrings,
							new std::vector<std::string>(),
							emailList,handler,startPositions,finalPos);

		startPositions = finalPos;
		taskQueue.push(task);
	}

	condition.notify_all();
}


void ConsumersManager::sampleAddresses(  std::vector<std::string>* input,
										 int sampleIndicator,
										 int numberElements,string filterWord)
{
	SampleAddressListTask* task = new SampleAddressListTask();
	task->setParameters(input,sampleIndicator,numberElements,filterWord,handler);

	taskQueue.push(task);
	condition.notify_one();
}

void ConsumersManager::separateList(  std::vector<std::string>* input,int functionCode,
									  int modeCode,std::vector<std::string>* domainList,
									  unsigned long long randomPackageSize )
{
	SeparateListTask * task = new SeparateListTask;
	task->setParameters(input,functionCode,modeCode,domainList,randomPackageSize,handler);

	taskQueue.push(task);
	condition.notify_one();
}

void ConsumersManager::seedAddresses(std::list<std::string>* input,
									 std::vector<std::string>* toSeedAddresses,
									 int numberOfTimes,
									 int functionCode)
{
	SeedAddressesTask* task = new SeedAddressesTask;
	task->setParameters(input,toSeedAddresses,numberOfTimes,functionCode,handler);

	taskQueue.push(task);
	condition.notify_one();
}

void ConsumersManager::splitAddressesList(	std::vector<std::string>* inputList,
											int functionCode,
											int n)
{
	SplitAddressesTask* task = new SplitAddressesTask;
	task->setParameters(inputList,functionCode,n,handler);

	taskQueue.push(task);
	condition.notify_one();
}



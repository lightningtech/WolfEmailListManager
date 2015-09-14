/*
 * Consumer.h
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_CONSUMER_H_
#define PROCESSINGTHREADCORE_CONSUMER_H_

#include <queue>
#include "UtilsHeaders.hpp"
#include "AbstractJobTask.hpp"
#include <boost/thread.hpp>


class DLLM_LOCAL Consumer
{
public:
	Consumer(std::queue<AbstractJobTask*> * taskQueue,
			  boost::mutex * queueMutex,
			  boost::condition_variable_any * condition);

	virtual ~Consumer();

	void excecute();

private:
	void run();
	std::queue<AbstractJobTask*> * taskQueue;

	boost::mutex * queueMutex;
	boost::condition_variable_any * condition;
	boost::thread *_thread;
};

#endif /* PROCESSINGTHREADCORE_CONSUMER_H_ */

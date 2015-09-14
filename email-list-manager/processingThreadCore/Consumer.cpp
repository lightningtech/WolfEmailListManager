/*
 * Consumer.cpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#include "Consumer.h"
#include <iostream>

Consumer::Consumer( std::queue<AbstractJobTask*> * taskQueue,
					boost::mutex * queueMutex,
					boost::condition_variable_any * condition)
					:taskQueue(taskQueue),queueMutex(queueMutex),condition(condition),
					 _thread(0)
{

}

Consumer::~Consumer()
{

}

void Consumer::run()
{
	AbstractJobTask * currentJob = 0;


	while(!boost::this_thread::interruption_requested())
	{
		{
			boost::unique_lock<boost::mutex> lock(*queueMutex);
			while( !taskQueue->size() )
			{
				condition->wait(lock);
			}

			std::cout << " condition received on consumer, task size: " << taskQueue->size() << std::endl;
			currentJob = taskQueue->front();
			if(currentJob)
			{
				taskQueue->pop();
			}
		}

		if(currentJob)
		{
			currentJob->execute();
			delete currentJob;
		}
	}
}

void Consumer::excecute()
{
	if( !_thread )
	 _thread = new boost::thread(&Consumer::run,this);
}


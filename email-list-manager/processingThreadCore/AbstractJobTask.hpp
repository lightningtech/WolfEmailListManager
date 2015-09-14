/*
 * AbstractJobTask.hpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_ABSTRACTJOBTASK_HPP_
#define PROCESSINGTHREADCORE_ABSTRACTJOBTASK_HPP_

#include <vector>
#include <list>
#include <string>
#include "../Errors.hpp"
#include "../DLLModuleMacro.hpp"

class DLLM_LOCAL AbstractJobTask
{
public:
	AbstractJobTask(){};
	virtual ~AbstractJobTask(){};
	virtual void execute()=0;
};




#endif /* PROCESSINGTHREADCORE_ABSTRACTJOBTASK_HPP_ */

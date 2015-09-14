/*
 * FinishedCurrentJobHandler.hpp
 *
 *  Created on: 30 de jul. de 2015
 *      Author: amides
 */

#ifndef FINISHEDCURRENTJOBHANDLER_HPP_
#define FINISHEDCURRENTJOBHANDLER_HPP_

#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include "DLLModuleMacro.hpp"

class DLLM_LOCAL FinishedCurrentJobHandler
{
public:
	FinishedCurrentJobHandler(){};
	virtual ~FinishedCurrentJobHandler(){};

	virtual void endingCurrentJob(const std::list<std::string> &outPutList,
								  const std::vector<std::string> &rejectedList,
								  unsigned int errorCode,
			                      std::string description = std::string("")) = 0;

	virtual void endingMergeListJob( unsigned int errorCode,
									 std::string description = std::string("") ) = 0;

	virtual void ListElementsDeleteEnd(unsigned int errorCode,
									   std::string description = std::string("")) = 0;

	virtual void keepAddressesEnd( std::vector<std::string> emailList,
								   std::vector<std::string>* erasedList,unsigned int errorCode,
								   std::string description = std::string("") ) = 0;

	virtual void sampleAddressEnded(std::vector<std::string> sampleOutput,
									unsigned int errorCode,
									std::string description = std::string("") ) = 0;

	virtual void separateListEnded( const std::set<std::string> &outputSet,
									bool lastList,
									unsigned int errorCode,
									std::string description = std::string("")) = 0;

	virtual void seedAddressesEnded(unsigned int errorCode,
							   std::string description = std::string("")) = 0;

	virtual void splitAddressesEnded(std::vector<std::string> result,
									 unsigned int errorCode,
			   	   	   	   	   	   	 std::string description = std::string("")) = 0;
};

#endif /* FINISHEDCURRENTJOBHANDLER_HPP_ */

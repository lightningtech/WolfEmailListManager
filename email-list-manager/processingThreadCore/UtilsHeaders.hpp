/*
 * UtilsHeaders.hpp
 *
 *  Created on: 29 de jul. de 2015
 *      Author: amides
 */

#ifndef PROCESSINGTHREADCORE_UTILSHEADERS_HPP_
#define PROCESSINGTHREADCORE_UTILSHEADERS_HPP_

#include <Python.h>


const char ALLOW_EMBEDDED_SPACES_AOL = 0x01;
const char NO_DUPLICATE_DOMAINS = 0x02;
const char REJECT_LONG_DOMAINS = 0x04;
const char REMOVE_DUPLICATES = 0x08;
const char SORT_BY_USERNAME = 0x10;//sobre el resultado final
const char SORT_BY_DOMAIN = 0x20;//sobre el resultado final

const char ALL_SETTED = ALLOW_EMBEDDED_SPACES_AOL|NO_DUPLICATE_DOMAINS|REJECT_LONG_DOMAINS|
		SORT_BY_USERNAME|SORT_BY_DOMAIN|REMOVE_DUPLICATES;

#endif /* PROCESSINGTHREADCORE_UTILSHEADERS_HPP_ */

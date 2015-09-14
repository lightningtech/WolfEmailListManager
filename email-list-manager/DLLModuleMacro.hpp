/*
 * DLLModuleMacro.hpp
 *
 *  Created on: 28 de ago. de 2015
 *      Author: amides
 */

#ifndef DLLMODULEMACRO_HPP_
#define DLLMODULEMACRO_HPP_


#if defined(_WIN32) || defined(_WIN64)
  #ifdef DLL_ELM
    #define DLLM_EXPORTS __declspec(dllexport)
  #else
    #define DLLM_EXPORTS __declspec(dllimport)
  #endif
	#define DLLM_LOCAL
#else
	#define DLLM_EXPORTS
	#define DLLM_LOCAL  __attribute__ ((visibility("internal")))
#endif


#endif /* DLLMODULEMACRO_HPP_ */

//=====================================================================
// Copyright 2007-2016 (c), Advanced Micro Devices, Inc. All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file 
/// 
//=====================================================================
/**
 *  @file     calcl.h
 *  @brief    CAL Compiler Interface Header
 *  @version  1.00.0 Beta
 */


#ifndef __CALCL_H__
#define __CALCL_H__

#include "cal.h"

#ifdef __cplusplus
extern "C" {
#define CALAPI
#else
#define CALAPI extern
#endif

#ifdef _WIN32
#define CALAPIENTRY  __stdcall
#else
#define CALAPIENTRY
#endif

/** Kernel source code language */
typedef enum CALlanguageEnum {
    CAL_LANGUAGE_IL=1,               /**< IL text */
} CALlanguage;

/** Kernel source code type */
typedef enum CALCLprogramTypeEnum {
    CAL_PROGRAM_TYPE_PS,              /**< GPU pixel program text */
    CAL_PROGRAM_TYPE_CS               /**< GPU compute program text */
} CALCLprogramType;

typedef void (*CALLogFunction)(const char* msg);  /**< Callback function for dissassembler */

/*============================================================================
 * CAL Compiler Interface
 *============================================================================*/

/**
 * @fn calclGetVersion(CALuint* major, CALuint* minor, CALuint* imp)
 *
 * @brief Retrieve the CAL compiler version that is loaded
 *
 * CAL version is in the form of API_Major.API_Minor.Implementation where
 * "API_Major" is the major version number of the CAL API. "API_Minor" is the
 * minor version number of the CAL API. "Implementation" is the implementation
 * instance of the supplied API version number.
 *
 * @return Returns CAL_RESULT_OK on success.
 *
 * @sa calInit calShutdown
 *
 */
CALAPI CALresult CALAPIENTRY calclGetVersion(CALuint* major, CALuint* minor, CALuint* imp);

/**
 * @fn calclCompile(CALobject* obj, CALlanguage language, const CALchar* source, CALtarget target)
 *
 * @brief Compile source into an object
 *
 * CAL compiler function. Compile a source language string to the specified target device
 * and return a compiled object.
 *
 * @param obj (out) - created object
 * @param language (in) - source language designation.
 * @param source (in) - string containing kernel source code.
 * @param target (in) - machine target.
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclLink calclFreeObject calclFreeImage
 */
CALAPI CALresult CALAPIENTRY calclCompile(CALobject* obj, CALlanguage language, const CALchar* source, CALtarget target);

/**
 * @fn calclLink(CALimage* image, CALobject* obj, CALuint objCount)
 *
 * @brief Link a list of objects into an image
 *
 * CAL compiler function. Link a list of individual objects into a full image.
 *
 * @param image (out) - created image
 * @param obj (in) - list of objects.
 * @param objCount (in) - number of objects
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclCompile calclFreeObject calclFreeImage
 */
CALAPI CALresult CALAPIENTRY calclLink(CALimage* image, CALobject* obj, CALuint objCount);

/**
 * @fn calclFreeObject(CALobject obj)
 *
 * @brief Free a CALobject
 *
 * CAL compiler function. Frees a CALobject generated by calCompile
 *
 * @param obj (in) - object to free.
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclCompile calclFreeImage
 */
CALAPI CALresult CALAPIENTRY calclFreeObject(CALobject obj);

/**
 * @fn calclFreeImage(CALimage image)
 *
 * @brief Free a CALimage
 *
 * CAL compiler function. Frees a CALimage generated by calLink
 *
 * @param image (in) - image to free.
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclLink
 */
CALAPI CALresult CALAPIENTRY calclFreeImage(CALimage image);


/**
 * @fn calclDisassembleImage(const CALimage image, CALLogFunction logfunc)
 *
 * @brief Disassemble a CAL image.
 *
 * CAL compiler function. Disassembles the CAL image, outputing on a line by line bases to the supplied log function.
 *
 * @param image (in) - image to disassemble.
 * @param logfunc (in) - user supplied function to invoke for each line of disassembly.
 *
 * @return No return
 *
 * @sa calclCompile calclLink
 */
CALAPI void CALAPIENTRY calclDisassembleImage(const CALimage image, CALLogFunction logfunc);

/**
 * @fn calclAssembleObject(CALobject* obj, CALCLprogramType type, const CALchar* source, CALtarget target)
 *
 * @brief Assemble source into an object
 *
 * CAL compiler function. Assemble a source language string to the specified target device
 * and return a compiled object.
 *
 * @param obj (out) - created object
 * @param type (in) - source program type.
 * @param source (in) - string containing kernel source code.
 * @param target (in) - machine target.
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclLink calclFreeObject calclFreeImage
 */
CALAPI CALresult CALAPIENTRY calclAssembleObject(CALobject* obj, CALCLprogramType type, const CALchar* source, CALtarget target);

/**
 * @fn calclDisassembleObject(const CALobject* obj, CALLogFunction logfunc)
 *
 * @brief Disassemble a CAL object source into an object
 *
 * CAL compiler function. Disassembles the CAL object, outputing on a line by line bases to the supplied log function.
 *
 * @param obj (in) - object to disassemble.
 * @param logfunc (in) - user supplied function to invoke for each line of disassembly.
 *
 * @return No return
 *
 * @sa calclAssemble calclLink
 */
CALAPI void CALAPIENTRY calclDisassembleObject(const CALobject* obj, CALLogFunction logfunc);

/**
 * @fn calclImageGetSize(CALuint* size, CALimage image)
 *
 * @brief Return the size of the buffer needed for use with calclImageWrite.
 *
 * CAL compiler function. Determines the size of the buffer that needs to be
 * allocated for use with calclImageWrite.
 *
 * @param size (out) - returned size
 * @param image (in) - image whose size is computed
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclImageWrite
 */
CALAPI CALresult CALAPIENTRY calclImageGetSize(CALuint* size, CALimage image);

/**
 * @fn calclImageWrite(CALvoid* buffer, CALuint size, CALimage image)
 *
 * @brief Serialize the supplied CALimage to the supplied buffer.
 *
 * CAL compiler function.  Serializes the contents of the CALimage image to
 * the supplied buffer.  The buffer should be allocated by the user and must
 * be at least as big as the value returned by calclImageGetSize.  The size
 * parameter indicates the size of the supplied buffer and is used to check
 * for buffer overrun.
 *
 * @param buffer (out) - buffer to serialize into
 * @param size (in) - size of allocated buffer
 * @param image (in) - image to serialize
 *
 * @return Returns CAL_RESULT_OK on success, CAL_RESULT_ERROR if there was an error.
 *
 * @sa calclImageGetSize
 */
CALAPI CALresult CALAPIENTRY calclImageWrite(CALvoid* buffer, CALuint size, CALimage image);

/**
 * @fn calclGetErrorString(void)
 *
 * @brief Return details about current error state
 *
 * calGetErrorString returns a text string containing details about the last
 * returned error condition. Calling calGetErrorString does not effect the
 * error state.
 *
 * @return Returns a null terminated string detailing the error condition
 *
 */
CALAPI const CALchar* CALAPIENTRY calclGetErrorString(void);

#ifdef __cplusplus
}      /* extern "C" { */
#endif


#endif /* __CALCL_H__ */



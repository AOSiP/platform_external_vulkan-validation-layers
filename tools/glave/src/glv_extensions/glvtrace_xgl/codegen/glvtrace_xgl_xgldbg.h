/* THIS FILE IS GENERATED.  DO NOT EDIT. */

/*
 * XGL
 *
 * Copyright (C) 2014 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "xgl.h"
#include "xglDbg.h"

void AttachHooks_xgldbg();
void DetachHooks_xgldbg();

#ifdef WIN32
#define __HOOKED_xglDbgSetValidationLevel hooked_xglDbgSetValidationLevel
#define __HOOKED_xglDbgRegisterMsgCallback hooked_xglDbgRegisterMsgCallback
#define __HOOKED_xglDbgUnregisterMsgCallback hooked_xglDbgUnregisterMsgCallback
#define __HOOKED_xglDbgSetMessageFilter hooked_xglDbgSetMessageFilter
#define __HOOKED_xglDbgSetObjectTag hooked_xglDbgSetObjectTag
#define __HOOKED_xglDbgSetGlobalOption hooked_xglDbgSetGlobalOption
#define __HOOKED_xglDbgSetDeviceOption hooked_xglDbgSetDeviceOption
#define __HOOKED_xglCmdDbgMarkerBegin hooked_xglCmdDbgMarkerBegin
#define __HOOKED_xglCmdDbgMarkerEnd hooked_xglCmdDbgMarkerEnd
#elif defined(__linux__)
#define __HOOKED_xglDbgSetValidationLevel xglDbgSetValidationLevel
#define __HOOKED_xglDbgRegisterMsgCallback xglDbgRegisterMsgCallback
#define __HOOKED_xglDbgUnregisterMsgCallback xglDbgUnregisterMsgCallback
#define __HOOKED_xglDbgSetMessageFilter xglDbgSetMessageFilter
#define __HOOKED_xglDbgSetObjectTag xglDbgSetObjectTag
#define __HOOKED_xglDbgSetGlobalOption xglDbgSetGlobalOption
#define __HOOKED_xglDbgSetDeviceOption xglDbgSetDeviceOption
#define __HOOKED_xglCmdDbgMarkerBegin xglCmdDbgMarkerBegin
#define __HOOKED_xglCmdDbgMarkerEnd xglCmdDbgMarkerEnd
#endif

// Hooked function prototypes

GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgSetValidationLevel(XGL_DEVICE device, XGL_VALIDATION_LEVEL validationLevel);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgRegisterMsgCallback(XGL_DBG_MSG_CALLBACK_FUNCTION pfnMsgCallback, void* pUserData);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgUnregisterMsgCallback(XGL_DBG_MSG_CALLBACK_FUNCTION pfnMsgCallback);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgSetMessageFilter(XGL_DEVICE device, int32_t msgCode, XGL_DBG_MSG_FILTER filter);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgSetObjectTag(XGL_BASE_OBJECT object, size_t tagSize, const void* pTag);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgSetGlobalOption(XGL_DBG_GLOBAL_OPTION dbgOption, size_t dataSize, const void* pData);
GLVTRACER_EXPORT XGL_RESULT XGLAPI __HOOKED_xglDbgSetDeviceOption(XGL_DEVICE device, XGL_DBG_DEVICE_OPTION dbgOption, size_t dataSize, const void* pData);
GLVTRACER_EXPORT void XGLAPI __HOOKED_xglCmdDbgMarkerBegin(XGL_CMD_BUFFER cmdBuffer, const char* pMarker);
GLVTRACER_EXPORT void XGLAPI __HOOKED_xglCmdDbgMarkerEnd(XGL_CMD_BUFFER cmdBuffer);
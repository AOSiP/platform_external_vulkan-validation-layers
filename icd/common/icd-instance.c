/*
 * XGL
 *
 * Copyright (C) 2014-2015 LunarG, Inc.
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
 *
 * Authors:
 *   Chia-I Wu <olv@lunarg.com>
 */

#define _ISOC11_SOURCE /* for aligned_alloc() */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "icd-instance.h"

static void * XGLAPI default_alloc(void *user_data, size_t size,
                                   size_t alignment,
                                   XGL_SYSTEM_ALLOC_TYPE allocType)
{
    if (alignment <= 1) {
        return malloc(size);
    } else if (u_is_pow2(alignment)) {
        if (alignment < sizeof(void *)) {
            assert(u_is_pow2(sizeof(void*)));
            alignment = sizeof(void *);
        }

        size = (size + alignment - 1) & ~(alignment - 1);

        return aligned_alloc(alignment, size);
    }
    else {
        return NULL;
    }
}

static void XGLAPI default_free(void *user_data, void *ptr)
{
    free(ptr);
}

struct icd_instance *icd_instance_create(const XGL_APPLICATION_INFO *app_info,
                                         const XGL_ALLOC_CALLBACKS *alloc_cb)
{
    static const XGL_ALLOC_CALLBACKS default_alloc_cb = {
        .pfnAlloc = default_alloc,
        .pfnFree = default_free,
    };
    struct icd_instance *instance;
    const char *name;
    size_t len;

    if (!alloc_cb)
        alloc_cb = &default_alloc_cb;

    instance = alloc_cb->pfnAlloc(alloc_cb->pUserData, sizeof(*instance), 0,
            XGL_SYSTEM_ALLOC_API_OBJECT);
    if (!instance)
        return NULL;

    memset(instance, 0, sizeof(*instance));

    name = (app_info->pAppName) ? app_info->pAppName : "unnamed";
    len = strlen(name);
    instance->name = alloc_cb->pfnAlloc(alloc_cb->pUserData, len + 1, 0,
            XGL_SYSTEM_ALLOC_INTERNAL);
    if (!instance->name) {
        alloc_cb->pfnFree(alloc_cb->pUserData, instance);
        return NULL;
    }

    memcpy(instance->name, name, len);
    instance->name[len] = '\0';

    instance->alloc_cb = *alloc_cb;

    return instance;
}

void icd_instance_destroy(struct icd_instance *instance)
{
    struct icd_instance_logger *logger;

    for (logger = instance->loggers; logger; logger = logger->next) {
        struct icd_instance_logger *next = logger->next;

        icd_instance_free(instance, logger);
        logger = next;
    }

    icd_instance_free(instance, instance->name);
    icd_instance_free(instance, instance);
}

XGL_RESULT icd_instance_set_bool(struct icd_instance *instance,
                                 XGL_DBG_GLOBAL_OPTION option, bool yes)
{
    XGL_RESULT res = XGL_SUCCESS;

    switch (option) {
    case XGL_DBG_OPTION_DEBUG_ECHO_ENABLE:
        instance->debug_echo_enable = yes;
        break;
    case XGL_DBG_OPTION_BREAK_ON_ERROR:
        instance->break_on_error = yes;
        break;
    case XGL_DBG_OPTION_BREAK_ON_WARNING:
        instance->break_on_warning = yes;
        break;
    default:
        res = XGL_ERROR_INVALID_VALUE;
        break;
    }

    return res;
}

XGL_RESULT icd_instance_add_logger(struct icd_instance *instance,
                                   XGL_DBG_MSG_CALLBACK_FUNCTION func,
                                   void *user_data)
{
    struct icd_instance_logger *logger;

    for (logger = instance->loggers; logger; logger = logger->next) {
        if (logger->func == func)
            break;
    }

    if (!logger) {
        logger = icd_instance_alloc(instance, sizeof(*logger), 0,
                XGL_SYSTEM_ALLOC_DEBUG);
        if (!logger)
            return XGL_ERROR_OUT_OF_MEMORY;

        logger->func = func;
        logger->next = instance->loggers;
        instance->loggers = logger;
    }

    logger->user_data = user_data;

    return XGL_SUCCESS;
}

XGL_RESULT icd_instance_remove_logger(struct icd_instance *instance,
                                      XGL_DBG_MSG_CALLBACK_FUNCTION func)
{
    struct icd_instance_logger *logger, *prev;

    for (prev = NULL, logger = instance->loggers; logger;
         prev = logger, logger = logger->next) {
        if (logger->func == func)
            break;
    }

    if (!logger)
        return XGL_ERROR_INVALID_POINTER;

    if (prev)
        prev->next = logger->next;
    else
        instance->loggers = logger->next;

    icd_instance_free(instance, logger);

    return XGL_SUCCESS;
}

void icd_instance_log(const struct icd_instance *instance,
                      XGL_DBG_MSG_TYPE msg_type,
                      XGL_VALIDATION_LEVEL validation_level,
                      XGL_BASE_OBJECT src_object,
                      size_t location, int32_t msg_code,
                      const char *msg)
{
    const struct icd_instance_logger *logger;

    if (instance->debug_echo_enable || !instance->loggers) {
        fputs(msg, stderr);
        fputc('\n', stderr);
    }

    for (logger = instance->loggers; logger; logger = logger->next) {
        logger->func(msg_type, validation_level, src_object, location,
                msg_code, msg, logger->user_data);
    }

    switch (msg_type) {
    case XGL_DBG_MSG_ERROR:
        if (instance->break_on_error)
            abort();
        /* fall through */
    case XGL_DBG_MSG_WARNING:
        if (instance->break_on_warning)
            abort();
        break;
    default:
        break;
    }
}
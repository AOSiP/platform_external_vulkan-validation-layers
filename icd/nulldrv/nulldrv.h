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

#ifndef NULLDRV_H
#define NULLDRV_H 
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <xgl.h>
#include <xglDbg.h>
#include <xglIcd.h>

#if defined(PLATFORM_LINUX)
#include <xglWsiX11Ext.h>
#else
#include <xglWsiWinExt.h>
#endif

#include "icd.h"
#include "icd-alloc.h"

#include "icd-format.h"
#include "icd-utils.h"

struct nulldrv_base {
    void *loader_data;
    uint32_t magic;
    XGL_RESULT (*get_info)(struct nulldrv_base *base, int type1,
                           size_t *size, void *data);
};

struct nulldrv_obj {
    struct nulldrv_base base;
};

struct nulldrv_base *nulldrv_base_create(struct nulldrv_dev *dev,
                                     size_t obj_size,
                                     XGL_DBG_OBJECT_TYPE type1);

enum nulldrv_ext_type {
   NULLDRV_EXT_WSI_X11,
   NULLDRV_EXT_WSI_WINDOWS,
   NULLDRV_EXT_COUNT,
   NULLDRV_EXT_INVALID = NULLDRV_EXT_COUNT,
};


struct nulldrv_instance {
    struct nulldrv_obj obj;
};

struct nulldrv_gpu {
    void *loader_data;
};

struct nulldrv_dev {
     struct nulldrv_base base;
     bool exts[NULLDRV_EXT_COUNT];
     struct nulldrv_desc_pool *desc_pool;
     struct nulldrv_queue *queues[1];
};

struct nulldrv_layout {
   enum nulldrv_layout_aux_type aux;
};

struct nulldrv_desc_pool {
    uint32_t surface_desc_size;
    uint32_t sampler_desc_size;
};


struct nulldrv_queue {
    struct nulldrv_base base;
    struct nulldrv_dev *dev;
};

struct nulldrv_rt_view {
    struct nulldrv_obj obj;
};

struct nulldrv_fence {
    struct nulldrv_obj obj;
};

struct nulldrv_img {
    struct nulldrv_obj obj;
    XGL_IMAGE_TYPE type;
    int32_t depth;
    uint32_t mip_levels;
    uint32_t array_size;
    XGL_FLAGS usage;
    XGL_IMAGE_FORMAT_CLASS format_class;
    uint32_t samples;
    size_t total_size;
};

struct nulldrv_mem {
    struct nulldrv_base base;
    struct nulldrv_bo *bo;
    XGL_GPU_SIZE size;
};

struct nulldrv_ds_view {
    struct nulldrv_obj obj;
    struct nulldrv_img *img;
    uint32_t array_size;
};

struct nulldrv_sampler {
    struct nulldrv_obj obj;
};

struct nulldrv_img_view {
    struct nulldrv_obj obj;
    struct nulldrv_img *img;
    float min_lod;
    uint32_t cmd_len;
};

struct nulldrv_buf {
    struct nulldrv_obj obj;
    XGL_GPU_SIZE size;
    XGL_FLAGS usage;
};

struct nulldrv_desc_layout {
    struct nulldrv_obj obj;
};

struct nulldrv_shader {
    struct nulldrv_obj obj;

};


struct nulldrv_pipeline {
    struct nulldrv_obj obj;
    struct nulldrv_dev *dev;
};

struct nulldrv_dynamic_vp {
    struct nulldrv_obj obj;
};

struct nulldrv_dynamic_rs {
    struct nulldrv_obj obj;
};

struct nulldrv_dynamic_cb {
    struct nulldrv_obj obj;
};

struct nulldrv_dynamic_ds {
    struct nulldrv_obj obj;
};

struct nulldrv_cmd {
    struct nulldrv_obj obj;
};

struct nulldrv_desc_region {
    struct nulldrv_obj obj;
    struct nulldrv_dev *dev;
};

struct nulldrv_desc_set {
    struct nulldrv_obj obj;
    struct nulldrv_desc_pool *pool;
    const struct nulldrv_desc_layout *layout;
};

struct nulldrv_framebuffer {
    struct nulldrv_obj obj;
};

struct nulldrv_render_pass {
    struct nulldrv_obj obj;
};

struct nulldrv_buf_view {
    struct nulldrv_obj obj;

    struct nulldrv_buf *buf;

    /* SURFACE_STATE */
    uint32_t cmd[8];
    uint32_t fs_cmd[8];
    uint32_t cmd_len;
};

#endif /* NULLDRV_H */
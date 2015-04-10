//
// File: vulkan.h
//
/*
** Copyright (c) 2014-2015 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#ifndef __VULKAN_H__
#define __VULKAN_H__

#define VK_MAKE_VERSION(major, minor, patch) \
    ((major << 22) | (minor << 12) | patch)

#include "vk_platform.h"

// Vulkan API version supported by this file
#define VK_API_VERSION VK_MAKE_VERSION(0, 72, 0)

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*
***************************************************************************************************
*   Core Vulkan API
***************************************************************************************************
*/

#ifdef __cplusplus
    #define VK_DEFINE_HANDLE(_obj) struct _obj##_T {char _dummy;}; typedef _obj##_T* _obj;
    #define VK_DEFINE_SUBCLASS_HANDLE(_obj, _base) struct _obj##_T : public _base##_T {}; typedef _obj##_T* _obj;
#else // __cplusplus
    #define VK_DEFINE_HANDLE(_obj) typedef void* _obj;
    #define VK_DEFINE_SUBCLASS_HANDLE(_obj, _base) typedef void* _obj;
#endif // __cplusplus

VK_DEFINE_HANDLE(VkInstance)
VK_DEFINE_HANDLE(VkPhysicalGpu)
VK_DEFINE_HANDLE(VkBaseObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDevice, VkBaseObject)
VK_DEFINE_SUBCLASS_HANDLE(VkQueue, VkBaseObject)
VK_DEFINE_SUBCLASS_HANDLE(VkGpuMemory, VkBaseObject)
VK_DEFINE_SUBCLASS_HANDLE(VkObject, VkBaseObject)
VK_DEFINE_SUBCLASS_HANDLE(VkBuffer, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkBufferView, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkImage, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkImageView, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkColorAttachmentView, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDepthStencilView, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkShader, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkPipeline, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkSampler, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDescriptorSet, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDescriptorSetLayout, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDescriptorSetLayoutChain, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDescriptorPool, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDynamicStateObject, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDynamicVpState, VkDynamicStateObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDynamicRsState, VkDynamicStateObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDynamicCbState, VkDynamicStateObject)
VK_DEFINE_SUBCLASS_HANDLE(VkDynamicDsState, VkDynamicStateObject)
VK_DEFINE_SUBCLASS_HANDLE(VkCmdBuffer, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkFence, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkSemaphore, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkEvent, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkQueryPool, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkFramebuffer, VkObject)
VK_DEFINE_SUBCLASS_HANDLE(VkRenderPass, VkObject)

#define VK_MAX_PHYSICAL_GPUS       16
#define VK_MAX_PHYSICAL_GPU_NAME   256

#define VK_LOD_CLAMP_NONE       MAX_FLOAT
#define VK_LAST_MIP_OR_SLICE    0xffffffff

#define VK_TRUE  1
#define VK_FALSE 0

#define VK_NULL_HANDLE 0

// This macro defines INT_MAX in enumerations to force compilers to use 32 bits
// to represent them. This may or may not be necessary on some compilers. The
// option to compile it out may allow compilers that warn about missing enumerants
// in switch statements to be silenced.
#define VK_MAX_ENUM(T) T##_MAX_ENUM = 0x7FFFFFFF

// ------------------------------------------------------------------------------------------------
// Enumerations


typedef enum VkMemoryPriority_
{
    VK_MEMORY_PRIORITY_UNUSED                               = 0x0,
    VK_MEMORY_PRIORITY_VERY_LOW                             = 0x1,
    VK_MEMORY_PRIORITY_LOW                                  = 0x2,
    VK_MEMORY_PRIORITY_NORMAL                               = 0x3,
    VK_MEMORY_PRIORITY_HIGH                                 = 0x4,
    VK_MEMORY_PRIORITY_VERY_HIGH                            = 0x5,

    VK_MEMORY_PRIORITY_BEGIN_RANGE                          = VK_MEMORY_PRIORITY_UNUSED,
    VK_MEMORY_PRIORITY_END_RANGE                            = VK_MEMORY_PRIORITY_VERY_HIGH,
    VK_NUM_MEMORY_PRIORITY                                  = (VK_MEMORY_PRIORITY_END_RANGE - VK_MEMORY_PRIORITY_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkMemoryPriority_)
} VkMemoryPriority;

typedef enum VkImageLayout_
{
    VK_IMAGE_LAYOUT_UNDEFINED                               = 0x00000000,   // Implicit layout an image is when its contents are undefined due to various reasons (e.g. right after creation)
    VK_IMAGE_LAYOUT_GENERAL                                 = 0x00000001,   // General layout when image can be used for any kind of access
    VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL                = 0x00000002,   // Optimal layout when image is only used for color attachment read/write
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL        = 0x00000003,   // Optimal layout when image is only used for depth/stencil attachment read/write
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL         = 0x00000004,   // Optimal layout when image is used for read only depth/stencil attachment and shader access
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL                = 0x00000005,   // Optimal layout when image is used for read only shader access
    VK_IMAGE_LAYOUT_CLEAR_OPTIMAL                           = 0x00000006,   // Optimal layout when image is used only for clear operations
    VK_IMAGE_LAYOUT_TRANSFER_SOURCE_OPTIMAL                 = 0x00000007,   // Optimal layout when image is used only as source of transfer operations
    VK_IMAGE_LAYOUT_TRANSFER_DESTINATION_OPTIMAL            = 0x00000008,   // Optimal layout when image is used only as destination of transfer operations

    VK_IMAGE_LAYOUT_BEGIN_RANGE                             = VK_IMAGE_LAYOUT_UNDEFINED,
    VK_IMAGE_LAYOUT_END_RANGE                               = VK_IMAGE_LAYOUT_TRANSFER_DESTINATION_OPTIMAL,
    VK_NUM_IMAGE_LAYOUT                                     = (VK_IMAGE_LAYOUT_END_RANGE - VK_IMAGE_LAYOUT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageLayout_)
} VkImageLayout;

typedef enum VkPipeEvent_
{
    VK_PIPE_EVENT_TOP_OF_PIPE                               = 0x00000001,   // Set event before the GPU starts processing subsequent command
    VK_PIPE_EVENT_VERTEX_PROCESSING_COMPLETE                = 0x00000002,   // Set event when all pending vertex processing is complete
    VK_PIPE_EVENT_LOCAL_FRAGMENT_PROCESSING_COMPLETE        = 0x00000003,   // Set event when all pending fragment shader executions are complete, within each fragment location
    VK_PIPE_EVENT_FRAGMENT_PROCESSING_COMPLETE              = 0x00000004,   // Set event when all pending fragment shader executions are complete
    VK_PIPE_EVENT_GRAPHICS_PIPELINE_COMPLETE                = 0x00000005,   // Set event when all pending graphics operations are complete
    VK_PIPE_EVENT_COMPUTE_PIPELINE_COMPLETE                 = 0x00000006,   // Set event when all pending compute operations are complete
    VK_PIPE_EVENT_TRANSFER_COMPLETE                         = 0x00000007,   // Set event when all pending transfer operations are complete
    VK_PIPE_EVENT_GPU_COMMANDS_COMPLETE                     = 0x00000008,   // Set event when all pending GPU work is complete

    VK_PIPE_EVENT_BEGIN_RANGE                               = VK_PIPE_EVENT_TOP_OF_PIPE,
    VK_PIPE_EVENT_END_RANGE                                 = VK_PIPE_EVENT_GPU_COMMANDS_COMPLETE,
    VK_NUM_PIPE_EVENT                                       = (VK_PIPE_EVENT_END_RANGE - VK_PIPE_EVENT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPipeEvent_)
} VkPipeEvent;

typedef enum VkWaitEvent_
{
    VK_WAIT_EVENT_TOP_OF_PIPE                               = 0x00000001,   // Wait event before the GPU starts processing subsequent commands
    VK_WAIT_EVENT_BEFORE_RASTERIZATION                      = 0x00000002,   // Wait event before rasterizing subsequent primitives

    VK_WAIT_EVENT_BEGIN_RANGE                               = VK_WAIT_EVENT_TOP_OF_PIPE,
    VK_WAIT_EVENT_END_RANGE                                 = VK_WAIT_EVENT_BEFORE_RASTERIZATION,
    VK_NUM_WAIT_EVENT                                       = (VK_WAIT_EVENT_END_RANGE - VK_WAIT_EVENT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkWaitEvent_)
} VkWaitEvent;

typedef enum VkMemoryOutputFlags_
{
    VK_MEMORY_OUTPUT_CPU_WRITE_BIT                          = 0x00000001,   // Controls output coherency of CPU writes
    VK_MEMORY_OUTPUT_SHADER_WRITE_BIT                       = 0x00000002,   // Controls output coherency of generic shader writes
    VK_MEMORY_OUTPUT_COLOR_ATTACHMENT_BIT                   = 0x00000004,   // Controls output coherency of color attachment writes
    VK_MEMORY_OUTPUT_DEPTH_STENCIL_ATTACHMENT_BIT           = 0x00000008,   // Controls output coherency of depth/stencil attachment writes
    VK_MEMORY_OUTPUT_COPY_BIT                               = 0x00000010,   // Controls output coherency of copy operations
    VK_MAX_ENUM(VkMemoryOutputFlags_)
} VkMemoryOutputFlags;

typedef enum VkMemoryInputFlags_
{
    VK_MEMORY_INPUT_CPU_READ_BIT                            = 0x00000001,   // Controls input coherency of CPU reads
    VK_MEMORY_INPUT_INDIRECT_COMMAND_BIT                    = 0x00000002,   // Controls input coherency of indirect command reads
    VK_MEMORY_INPUT_INDEX_FETCH_BIT                         = 0x00000004,   // Controls input coherency of index fetches
    VK_MEMORY_INPUT_VERTEX_ATTRIBUTE_FETCH_BIT              = 0x00000008,   // Controls input coherency of vertex attribute fetches
    VK_MEMORY_INPUT_UNIFORM_READ_BIT                        = 0x00000010,   // Controls input coherency of uniform buffer reads
    VK_MEMORY_INPUT_SHADER_READ_BIT                         = 0x00000020,   // Controls input coherency of generic shader reads
    VK_MEMORY_INPUT_COLOR_ATTACHMENT_BIT                    = 0x00000040,   // Controls input coherency of color attachment reads
    VK_MEMORY_INPUT_DEPTH_STENCIL_ATTACHMENT_BIT            = 0x00000080,   // Controls input coherency of depth/stencil attachment reads
    VK_MEMORY_INPUT_COPY_BIT                                = 0x00000100,   // Controls input coherency of copy operations
    VK_MAX_ENUM(VkMemoryInputFlags_)
} VkMemoryInputFlags;

typedef enum VkAttachmentLoadOp_
{
    VK_ATTACHMENT_LOAD_OP_LOAD                              = 0x00000000,
    VK_ATTACHMENT_LOAD_OP_CLEAR                             = 0x00000001,
    VK_ATTACHMENT_LOAD_OP_DONT_CARE                         = 0x00000002,

    VK_ATTACHMENT_LOAD_OP_BEGIN_RANGE                       = VK_ATTACHMENT_LOAD_OP_LOAD,
    VK_ATTACHMENT_LOAD_OP_END_RANGE                         = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    VK_NUM_ATTACHMENT_LOAD_OP                               = (VK_ATTACHMENT_LOAD_OP_END_RANGE - VK_ATTACHMENT_LOAD_OP_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkAttachmentLoadOp_)
} VkAttachmentLoadOp;

typedef enum VkAttachmentStoreOp_
{
    VK_ATTACHMENT_STORE_OP_STORE                            = 0x00000000,
    VK_ATTACHMENT_STORE_OP_RESOLVE_MSAA                     = 0x00000001,
    VK_ATTACHMENT_STORE_OP_DONT_CARE                        = 0x00000002,

    VK_ATTACHMENT_STORE_OP_BEGIN_RANGE                      = VK_ATTACHMENT_STORE_OP_STORE,
    VK_ATTACHMENT_STORE_OP_END_RANGE                        = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    VK_NUM_ATTACHMENT_STORE_OP                              = (VK_ATTACHMENT_STORE_OP_END_RANGE - VK_ATTACHMENT_STORE_OP_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkAttachmentStoreOp_)
} VkAttachmentStoreOp;

typedef enum VkImageType_
{
    VK_IMAGE_1D                                             = 0x00000000,
    VK_IMAGE_2D                                             = 0x00000001,
    VK_IMAGE_3D                                             = 0x00000002,

    VK_IMAGE_TYPE_BEGIN_RANGE                               = VK_IMAGE_1D,
    VK_IMAGE_TYPE_END_RANGE                                 = VK_IMAGE_3D,
    VK_NUM_IMAGE_TYPE                                       = (VK_IMAGE_TYPE_END_RANGE - VK_IMAGE_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageType_)
} VkImageType;

typedef enum VkImageTiling_
{
    VK_LINEAR_TILING                                        = 0x00000000,
    VK_OPTIMAL_TILING                                       = 0x00000001,

    VK_IMAGE_TILING_BEGIN_RANGE                             = VK_LINEAR_TILING,
    VK_IMAGE_TILING_END_RANGE                               = VK_OPTIMAL_TILING,
    VK_NUM_IMAGE_TILING                                     = (VK_IMAGE_TILING_END_RANGE - VK_IMAGE_TILING_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageTiling_)
} VkImageTiling;

typedef enum VkImageViewType_
{
    VK_IMAGE_VIEW_1D                                        = 0x00000000,
    VK_IMAGE_VIEW_2D                                        = 0x00000001,
    VK_IMAGE_VIEW_3D                                        = 0x00000002,
    VK_IMAGE_VIEW_CUBE                                      = 0x00000003,

    VK_IMAGE_VIEW_TYPE_BEGIN_RANGE                          = VK_IMAGE_VIEW_1D,
    VK_IMAGE_VIEW_TYPE_END_RANGE                            = VK_IMAGE_VIEW_CUBE,
    VK_NUM_IMAGE_VIEW_TYPE                                  = (VK_IMAGE_VIEW_TYPE_END_RANGE - VK_IMAGE_VIEW_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageViewType_)
} VkImageViewType;

typedef enum VkImageAspect_
{
    VK_IMAGE_ASPECT_COLOR                                   = 0x00000000,
    VK_IMAGE_ASPECT_DEPTH                                   = 0x00000001,
    VK_IMAGE_ASPECT_STENCIL                                 = 0x00000002,

    VK_IMAGE_ASPECT_BEGIN_RANGE                             = VK_IMAGE_ASPECT_COLOR,
    VK_IMAGE_ASPECT_END_RANGE                               = VK_IMAGE_ASPECT_STENCIL,
    VK_NUM_IMAGE_ASPECT                                     = (VK_IMAGE_ASPECT_END_RANGE - VK_IMAGE_ASPECT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageAspect_)
} VkImageAspect;

typedef enum VkChannelSwizzle_
{
    VK_CHANNEL_SWIZZLE_ZERO                                 = 0x00000000,
    VK_CHANNEL_SWIZZLE_ONE                                  = 0x00000001,
    VK_CHANNEL_SWIZZLE_R                                    = 0x00000002,
    VK_CHANNEL_SWIZZLE_G                                    = 0x00000003,
    VK_CHANNEL_SWIZZLE_B                                    = 0x00000004,
    VK_CHANNEL_SWIZZLE_A                                    = 0x00000005,

    VK_CHANNEL_SWIZZLE_BEGIN_RANGE                          = VK_CHANNEL_SWIZZLE_ZERO,
    VK_CHANNEL_SWIZZLE_END_RANGE                            = VK_CHANNEL_SWIZZLE_A,
    VK_NUM_CHANNEL_SWIZZLE                                  = (VK_CHANNEL_SWIZZLE_END_RANGE - VK_CHANNEL_SWIZZLE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkChannelSwizzle_)
} VkChannelSwizzle;

typedef enum VkDescriptorType_
{
    VK_DESCRIPTOR_TYPE_SAMPLER                              = 0x00000000,
    VK_DESCRIPTOR_TYPE_SAMPLER_TEXTURE                      = 0x00000001,
    VK_DESCRIPTOR_TYPE_TEXTURE                              = 0x00000002,
    VK_DESCRIPTOR_TYPE_TEXTURE_BUFFER                       = 0x00000003,
    VK_DESCRIPTOR_TYPE_IMAGE                                = 0x00000004,
    VK_DESCRIPTOR_TYPE_IMAGE_BUFFER                         = 0x00000005,
    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER                       = 0x00000006,
    VK_DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER                = 0x00000007,
    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC               = 0x00000008,
    VK_DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER_DYNAMIC        = 0x00000009,

    VK_DESCRIPTOR_TYPE_BEGIN_RANGE                          = VK_DESCRIPTOR_TYPE_SAMPLER,
    VK_DESCRIPTOR_TYPE_END_RANGE                            = VK_DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER_DYNAMIC,
    VK_NUM_DESCRIPTOR_TYPE                                  = (VK_DESCRIPTOR_TYPE_END_RANGE - VK_DESCRIPTOR_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkDescriptorType_)
} VkDescriptorType;

typedef enum VkDescriptorPoolUsage_
{
    VK_DESCRIPTOR_POOL_USAGE_ONE_SHOT                       = 0x00000000,
    VK_DESCRIPTOR_POOL_USAGE_DYNAMIC                        = 0x00000001,

    VK_DESCRIPTOR_POOL_USAGE_BEGIN_RANGE                    = VK_DESCRIPTOR_POOL_USAGE_ONE_SHOT,
    VK_DESCRIPTOR_POOL_USAGE_END_RANGE                      = VK_DESCRIPTOR_POOL_USAGE_DYNAMIC,
    VK_NUM_DESCRIPTOR_POOL_USAGE                            = (VK_DESCRIPTOR_POOL_USAGE_END_RANGE - VK_DESCRIPTOR_POOL_USAGE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkDescriptorPoolUsage_)
} VkDescriptorPoolUsage;

typedef enum VkDescriptorUpdateMode_
{
    VK_DESCRIPTOR_UDPATE_MODE_COPY                          = 0x00000000,
    VK_DESCRIPTOR_UPDATE_MODE_FASTEST                       = 0x00000001,

    VK_DESCRIPTOR_UPDATE_MODE_BEGIN_RANGE                   = VK_DESCRIPTOR_UDPATE_MODE_COPY,
    VK_DESCRIPTOR_UPDATE_MODE_END_RANGE                     = VK_DESCRIPTOR_UPDATE_MODE_FASTEST,
    VK_NUM_DESCRIPTOR_UPDATE_MODE                           = (VK_DESCRIPTOR_UPDATE_MODE_END_RANGE - VK_DESCRIPTOR_UPDATE_MODE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkDescriptorUpdateMode_)
} VkDescriptorUpdateMode;

typedef enum VkDescriptorSetUsage_
{
    VK_DESCRIPTOR_SET_USAGE_ONE_SHOT                        = 0x00000000,
    VK_DESCRIPTOR_SET_USAGE_STATIC                          = 0x00000001,

    VK_DESCRIPTOR_SET_USAGE_BEGIN_RANGE                     = VK_DESCRIPTOR_SET_USAGE_ONE_SHOT,
    VK_DESCRIPTOR_SET_USAGE_END_RANGE                       = VK_DESCRIPTOR_SET_USAGE_STATIC,
    VK_NUM_DESCRIPTOR_SET_USAGE                             = (VK_DESCRIPTOR_SET_USAGE_END_RANGE - VK_DESCRIPTOR_SET_USAGE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkDescriptorSetUsage_)
} VkDescriptorSetUsage;

typedef enum VkQueryType_
{
    VK_QUERY_OCCLUSION                                      = 0x00000000,
    VK_QUERY_PIPELINE_STATISTICS                            = 0x00000001,

    VK_QUERY_TYPE_BEGIN_RANGE                               = VK_QUERY_OCCLUSION,
    VK_QUERY_TYPE_END_RANGE                                 = VK_QUERY_PIPELINE_STATISTICS,
    VK_NUM_QUERY_TYPE                                       = (VK_QUERY_TYPE_END_RANGE - VK_QUERY_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkQueryType_)
} VkQueryType;

typedef enum VkTimestampType_
{
    VK_TIMESTAMP_TOP                                        = 0x00000000,
    VK_TIMESTAMP_BOTTOM                                     = 0x00000001,

    VK_TIMESTAMP_TYPE_BEGIN_RANGE                           = VK_TIMESTAMP_TOP,
    VK_TIMESTAMP_TYPE_END_RANGE                             = VK_TIMESTAMP_BOTTOM,
    VK_NUM_TIMESTAMP_TYPE                                   = (VK_TIMESTAMP_TYPE_END_RANGE - VK_TIMESTAMP_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(_VK_TIMESTEAMP_TYPE)
} VkTimestampType;

typedef enum VkBorderColorType_
{
    VK_BORDER_COLOR_OPAQUE_WHITE                            = 0x00000000,
    VK_BORDER_COLOR_TRANSPARENT_BLACK                       = 0x00000001,
    VK_BORDER_COLOR_OPAQUE_BLACK                            = 0x00000002,

    VK_BORDER_COLOR_TYPE_BEGIN_RANGE                        = VK_BORDER_COLOR_OPAQUE_WHITE,
    VK_BORDER_COLOR_TYPE_END_RANGE                          = VK_BORDER_COLOR_OPAQUE_BLACK,
    VK_NUM_BORDER_COLOR_TYPE                                = (VK_BORDER_COLOR_TYPE_END_RANGE - VK_BORDER_COLOR_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkBorderColorType_)
} VkBorderColorType;

typedef enum VkPipelineBindPoint_
{
    VK_PIPELINE_BIND_POINT_COMPUTE                          = 0x00000000,
    VK_PIPELINE_BIND_POINT_GRAPHICS                         = 0x00000001,

    VK_PIPELINE_BIND_POINT_BEGIN_RANGE                      = VK_PIPELINE_BIND_POINT_COMPUTE,
    VK_PIPELINE_BIND_POINT_END_RANGE                        = VK_PIPELINE_BIND_POINT_GRAPHICS,
    VK_NUM_PIPELINE_BIND_POINT                              = (VK_PIPELINE_BIND_POINT_END_RANGE - VK_PIPELINE_BIND_POINT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPipelineBindPoint_)
} VkPipelineBindPoint;

typedef enum VkStateBindPoint_
{
    VK_STATE_BIND_VIEWPORT                                  = 0x00000000,
    VK_STATE_BIND_RASTER                                    = 0x00000001,
    VK_STATE_BIND_COLOR_BLEND                               = 0x00000002,
    VK_STATE_BIND_DEPTH_STENCIL                             = 0x00000003,

    VK_STATE_BIND_POINT_BEGIN_RANGE                         = VK_STATE_BIND_VIEWPORT,
    VK_STATE_BIND_POINT_END_RANGE                           = VK_STATE_BIND_DEPTH_STENCIL,
    VK_NUM_STATE_BIND_POINT                                 = (VK_STATE_BIND_POINT_END_RANGE - VK_STATE_BIND_POINT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkStateBindPoint_)
} VkStateBindPoint;

typedef enum VkPrimitiveTopology_
{
    VK_TOPOLOGY_POINT_LIST                                  = 0x00000000,
    VK_TOPOLOGY_LINE_LIST                                   = 0x00000001,
    VK_TOPOLOGY_LINE_STRIP                                  = 0x00000002,
    VK_TOPOLOGY_TRIANGLE_LIST                               = 0x00000003,
    VK_TOPOLOGY_TRIANGLE_STRIP                              = 0x00000004,
    VK_TOPOLOGY_TRIANGLE_FAN                                = 0x00000005,
    VK_TOPOLOGY_LINE_LIST_ADJ                               = 0x00000006,
    VK_TOPOLOGY_LINE_STRIP_ADJ                              = 0x00000007,
    VK_TOPOLOGY_TRIANGLE_LIST_ADJ                           = 0x00000008,
    VK_TOPOLOGY_TRIANGLE_STRIP_ADJ                          = 0x00000009,
    VK_TOPOLOGY_PATCH                                       = 0x0000000a,

    VK_PRIMITIVE_TOPOLOGY_BEGIN_RANGE                       = VK_TOPOLOGY_POINT_LIST,
    VK_PRIMITIVE_TOPOLOGY_END_RANGE                         = VK_TOPOLOGY_PATCH,
    VK_NUM_PRIMITIVE_TOPOLOGY                               = (VK_PRIMITIVE_TOPOLOGY_END_RANGE - VK_PRIMITIVE_TOPOLOGY_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPrimitiveTopology_)
} VkPrimitiveTopology;

typedef enum VkIndexType_
{
    VK_INDEX_8                                              = 0x00000000,
    VK_INDEX_16                                             = 0x00000001,
    VK_INDEX_32                                             = 0x00000002,

    VK_INDEX_TYPE_BEGIN_RANGE                               = VK_INDEX_8,
    VK_INDEX_TYPE_END_RANGE                                 = VK_INDEX_32,
    VK_NUM_INDEX_TYPE                                       = (VK_INDEX_TYPE_END_RANGE - VK_INDEX_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkIndexType_)
} VkIndexType;

typedef enum VkTexFilter_
{
    VK_TEX_FILTER_NEAREST                                   = 0,
    VK_TEX_FILTER_LINEAR                                    = 1,

    VK_TEX_FILTER_BEGIN_RANGE                               = VK_TEX_FILTER_NEAREST,
    VK_TEX_FILTER_END_RANGE                                 = VK_TEX_FILTER_LINEAR,
    VK_NUM_TEX_FILTER                                       = (VK_TEX_FILTER_END_RANGE - VK_TEX_FILTER_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkTexFilter_)
} VkTexFilter;

typedef enum VkTexMipmapMode_
{
    VK_TEX_MIPMAP_BASE                                      = 0,        // Always choose base level
    VK_TEX_MIPMAP_NEAREST                                   = 1,        // Choose nearest mip level
    VK_TEX_MIPMAP_LINEAR                                    = 2,        // Linear filter between mip levels

    VK_TEX_MIPMAP_BEGIN_RANGE                               = VK_TEX_MIPMAP_BASE,
    VK_TEX_MIPMAP_END_RANGE                                 = VK_TEX_MIPMAP_LINEAR,
    VK_NUM_TEX_MIPMAP                                       = (VK_TEX_MIPMAP_END_RANGE - VK_TEX_MIPMAP_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkTexMipmapMode_)
} VkTexMipmapMode;

typedef enum VkTexAddress_
{
    VK_TEX_ADDRESS_WRAP                                     = 0x00000000,
    VK_TEX_ADDRESS_MIRROR                                   = 0x00000001,
    VK_TEX_ADDRESS_CLAMP                                    = 0x00000002,
    VK_TEX_ADDRESS_MIRROR_ONCE                              = 0x00000003,
    VK_TEX_ADDRESS_CLAMP_BORDER                             = 0x00000004,

    VK_TEX_ADDRESS_BEGIN_RANGE                              = VK_TEX_ADDRESS_WRAP,
    VK_TEX_ADDRESS_END_RANGE                                = VK_TEX_ADDRESS_CLAMP_BORDER,
    VK_NUM_TEX_ADDRESS                                      = (VK_TEX_ADDRESS_END_RANGE - VK_TEX_ADDRESS_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkTexAddress_)
} VkTexAddress;

typedef enum VkCompareFunc_
{
    VK_COMPARE_NEVER                                        = 0x00000000,
    VK_COMPARE_LESS                                         = 0x00000001,
    VK_COMPARE_EQUAL                                        = 0x00000002,
    VK_COMPARE_LESS_EQUAL                                   = 0x00000003,
    VK_COMPARE_GREATER                                      = 0x00000004,
    VK_COMPARE_NOT_EQUAL                                    = 0x00000005,
    VK_COMPARE_GREATER_EQUAL                                = 0x00000006,
    VK_COMPARE_ALWAYS                                       = 0x00000007,

    VK_COMPARE_FUNC_BEGIN_RANGE                             = VK_COMPARE_NEVER,
    VK_COMPARE_FUNC_END_RANGE                               = VK_COMPARE_ALWAYS,
    VK_NUM_COMPARE_FUNC                                     = (VK_COMPARE_FUNC_END_RANGE - VK_COMPARE_FUNC_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkCompareFunc_)
} VkCompareFunc;

typedef enum VkFillMode_
{
    VK_FILL_POINTS                                          = 0x00000000,
    VK_FILL_WIREFRAME                                       = 0x00000001,
    VK_FILL_SOLID                                           = 0x00000002,

    VK_FILL_MODE_BEGIN_RANGE                                = VK_FILL_POINTS,
    VK_FILL_MODE_END_RANGE                                  = VK_FILL_SOLID,
    VK_NUM_FILL_MODE                                        = (VK_FILL_MODE_END_RANGE - VK_FILL_MODE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkFillMode_)
} VkFillMode;

typedef enum VkCullMode_
{
    VK_CULL_NONE                                            = 0x00000000,
    VK_CULL_FRONT                                           = 0x00000001,
    VK_CULL_BACK                                            = 0x00000002,
    VK_CULL_FRONT_AND_BACK                                  = 0x00000003,

    VK_CULL_MODE_BEGIN_RANGE                                = VK_CULL_NONE,
    VK_CULL_MODE_END_RANGE                                  = VK_CULL_FRONT_AND_BACK,
    VK_NUM_CULL_MODE                                        = (VK_CULL_MODE_END_RANGE - VK_CULL_MODE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkCullMode_)
} VkCullMode;

typedef enum VkFaceOrientation_
{
    VK_FRONT_FACE_CCW                                       = 0x00000000,
    VK_FRONT_FACE_CW                                        = 0x00000001,

    VK_FACE_ORIENTATION_BEGIN_RANGE                         = VK_FRONT_FACE_CCW,
    VK_FACE_ORIENTATION_END_RANGE                           = VK_FRONT_FACE_CW,
    VK_NUM_FACE_ORIENTATION                                 = (VK_FACE_ORIENTATION_END_RANGE - VK_FACE_ORIENTATION_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkFaceOrientation_)
} VkFaceOrientation;

typedef enum VkProvokingVertexConvention_
{
    VK_PROVOKING_VERTEX_FIRST                               = 0x00000000,
    VK_PROVOKING_VERTEX_LAST                                = 0x00000001,

    VK_PROVOKING_VERTEX_BEGIN_RANGE                         = VK_PROVOKING_VERTEX_FIRST,
    VK_PROVOKING_VERTEX_END_RANGE                           = VK_PROVOKING_VERTEX_LAST,
    VK_NUM_PROVOKING_VERTEX_CONVENTION                      = (VK_PROVOKING_VERTEX_END_RANGE - VK_PROVOKING_VERTEX_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkProvokingVertexConvention_)
} VkProvokingVertexConvention;

typedef enum VkCoordinateOrigin_
{
    VK_COORDINATE_ORIGIN_UPPER_LEFT                         = 0x00000000,
    VK_COORDINATE_ORIGIN_LOWER_LEFT                         = 0x00000001,

    VK_COORDINATE_ORIGIN_BEGIN_RANGE                        = VK_COORDINATE_ORIGIN_UPPER_LEFT,
    VK_COORDINATE_ORIGIN_END_RANGE                          = VK_COORDINATE_ORIGIN_LOWER_LEFT,
    VK_NUM_COORDINATE_ORIGIN                                = (VK_COORDINATE_ORIGIN_END_RANGE - VK_COORDINATE_ORIGIN_END_RANGE + 1),
    VK_MAX_ENUM(VkCoordinateOrigin_)
} VkCoordinateOrigin;

typedef enum VkDepthMode_
{
    VK_DEPTH_MODE_ZERO_TO_ONE                               = 0x00000000,
    VK_DEPTH_MODE_NEGATIVE_ONE_TO_ONE                       = 0x00000001,

    VK_DEPTH_MODE_BEGIN_RANGE                               = VK_DEPTH_MODE_ZERO_TO_ONE,
    VK_DEPTH_MODE_END_RANGE                                 = VK_DEPTH_MODE_NEGATIVE_ONE_TO_ONE,
    VK_NUM_DEPTH_MODE                                       = (VK_DEPTH_MODE_END_RANGE - VK_DEPTH_MODE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkDepthMode_)
} VkDepthMode;

typedef enum VkBlend_
{
    VK_BLEND_ZERO                                           = 0x00000000,
    VK_BLEND_ONE                                            = 0x00000001,
    VK_BLEND_SRC_COLOR                                      = 0x00000002,
    VK_BLEND_ONE_MINUS_SRC_COLOR                            = 0x00000003,
    VK_BLEND_DEST_COLOR                                     = 0x00000004,
    VK_BLEND_ONE_MINUS_DEST_COLOR                           = 0x00000005,
    VK_BLEND_SRC_ALPHA                                      = 0x00000006,
    VK_BLEND_ONE_MINUS_SRC_ALPHA                            = 0x00000007,
    VK_BLEND_DEST_ALPHA                                     = 0x00000008,
    VK_BLEND_ONE_MINUS_DEST_ALPHA                           = 0x00000009,
    VK_BLEND_CONSTANT_COLOR                                 = 0x0000000a,
    VK_BLEND_ONE_MINUS_CONSTANT_COLOR                       = 0x0000000b,
    VK_BLEND_CONSTANT_ALPHA                                 = 0x0000000c,
    VK_BLEND_ONE_MINUS_CONSTANT_ALPHA                       = 0x0000000d,
    VK_BLEND_SRC_ALPHA_SATURATE                             = 0x0000000e,
    VK_BLEND_SRC1_COLOR                                     = 0x0000000f,
    VK_BLEND_ONE_MINUS_SRC1_COLOR                           = 0x00000010,
    VK_BLEND_SRC1_ALPHA                                     = 0x00000011,
    VK_BLEND_ONE_MINUS_SRC1_ALPHA                           = 0x00000012,

    VK_BLEND_BEGIN_RANGE                                    = VK_BLEND_ZERO,
    VK_BLEND_END_RANGE                                      = VK_BLEND_ONE_MINUS_SRC1_ALPHA,
    VK_NUM_BLEND                                            = (VK_BLEND_END_RANGE - VK_BLEND_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkBlend_)
} VkBlend;

typedef enum VkBlendFunc_
{
    VK_BLEND_FUNC_ADD                                       = 0x00000000,
    VK_BLEND_FUNC_SUBTRACT                                  = 0x00000001,
    VK_BLEND_FUNC_REVERSE_SUBTRACT                          = 0x00000002,
    VK_BLEND_FUNC_MIN                                       = 0x00000003,
    VK_BLEND_FUNC_MAX                                       = 0x00000004,

    VK_BLEND_FUNC_BEGIN_RANGE                               = VK_BLEND_FUNC_ADD,
    VK_BLEND_FUNC_END_RANGE                                 = VK_BLEND_FUNC_MAX,
    VK_NUM_BLEND_FUNC                                       = (VK_BLEND_FUNC_END_RANGE - VK_BLEND_FUNC_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkBlendFunc_)
} VkBlendFunc;

typedef enum VkStencilOp_
{
    VK_STENCIL_OP_KEEP                                      = 0x00000000,
    VK_STENCIL_OP_ZERO                                      = 0x00000001,
    VK_STENCIL_OP_REPLACE                                   = 0x00000002,
    VK_STENCIL_OP_INC_CLAMP                                 = 0x00000003,
    VK_STENCIL_OP_DEC_CLAMP                                 = 0x00000004,
    VK_STENCIL_OP_INVERT                                    = 0x00000005,
    VK_STENCIL_OP_INC_WRAP                                  = 0x00000006,
    VK_STENCIL_OP_DEC_WRAP                                  = 0x00000007,

    VK_STENCIL_OP_BEGIN_RANGE                               = VK_STENCIL_OP_KEEP,
    VK_STENCIL_OP_END_RANGE                                 = VK_STENCIL_OP_DEC_WRAP,
    VK_NUM_STENCIL_OP                                       = (VK_STENCIL_OP_END_RANGE - VK_STENCIL_OP_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkStencilOp_)
} VkStencilOp;

typedef enum VkLogicOp_
{
    VK_LOGIC_OP_COPY                                        = 0x00000000,
    VK_LOGIC_OP_CLEAR                                       = 0x00000001,
    VK_LOGIC_OP_AND                                         = 0x00000002,
    VK_LOGIC_OP_AND_REVERSE                                 = 0x00000003,
    VK_LOGIC_OP_AND_INVERTED                                = 0x00000004,
    VK_LOGIC_OP_NOOP                                        = 0x00000005,
    VK_LOGIC_OP_XOR                                         = 0x00000006,
    VK_LOGIC_OP_OR                                          = 0x00000007,
    VK_LOGIC_OP_NOR                                         = 0x00000008,
    VK_LOGIC_OP_EQUIV                                       = 0x00000009,
    VK_LOGIC_OP_INVERT                                      = 0x0000000a,
    VK_LOGIC_OP_OR_REVERSE                                  = 0x0000000b,
    VK_LOGIC_OP_COPY_INVERTED                               = 0x0000000c,
    VK_LOGIC_OP_OR_INVERTED                                 = 0x0000000d,
    VK_LOGIC_OP_NAND                                        = 0x0000000e,
    VK_LOGIC_OP_SET                                         = 0x0000000f,

    VK_LOGIC_OP_BEGIN_RANGE                                 = VK_LOGIC_OP_COPY,
    VK_LOGIC_OP_END_RANGE                                   = VK_LOGIC_OP_SET,
    VK_NUM_LOGIC_OP                                         = (VK_LOGIC_OP_END_RANGE - VK_LOGIC_OP_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkLogicOp_)
} VkLogicOp;

typedef enum VkSystemAllocType_
{
    VK_SYSTEM_ALLOC_API_OBJECT                              = 0x00000000,
    VK_SYSTEM_ALLOC_INTERNAL                                = 0x00000001,
    VK_SYSTEM_ALLOC_INTERNAL_TEMP                           = 0x00000002,
    VK_SYSTEM_ALLOC_INTERNAL_SHADER                         = 0x00000003,
    VK_SYSTEM_ALLOC_DEBUG                                   = 0x00000004,

    VK_SYSTEM_ALLOC_BEGIN_RANGE                             = VK_SYSTEM_ALLOC_API_OBJECT,
    VK_SYSTEM_ALLOC_END_RANGE                               = VK_SYSTEM_ALLOC_DEBUG,
    VK_NUM_SYSTEM_ALLOC_TYPE                                = (VK_SYSTEM_ALLOC_END_RANGE - VK_SYSTEM_ALLOC_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkSystemAllocType_)
} VkSystemAllocType;

typedef enum VkPhysicalGpuType_
{
    VK_GPU_TYPE_OTHER                                       = 0x00000000,
    VK_GPU_TYPE_INTEGRATED                                  = 0x00000001,
    VK_GPU_TYPE_DISCRETE                                    = 0x00000002,
    VK_GPU_TYPE_VIRTUAL                                     = 0x00000003,

    VK_PHYSICAL_GPU_TYPE_BEGIN_RANGE                        = VK_GPU_TYPE_OTHER,
    VK_PHYSICAL_GPU_TYPE_END_RANGE                          = VK_GPU_TYPE_VIRTUAL,
    VK_NUM_PHYSICAL_GPU_TYPE                                = (VK_PHYSICAL_GPU_TYPE_END_RANGE - VK_PHYSICAL_GPU_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPhysicalGpuType_)
} VkPhysicalGpuType;

typedef enum VkPhysicalGpuInfoType_
{
    // Info type for vkGetGpuInfo()
    VK_INFO_TYPE_PHYSICAL_GPU_PROPERTIES                    = 0x00000000,
    VK_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE                   = 0x00000001,
    VK_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES              = 0x00000002,
    VK_INFO_TYPE_PHYSICAL_GPU_MEMORY_PROPERTIES             = 0x00000003,

    VK_INFO_TYPE_PHYSICAL_GPU_BEGIN_RANGE                   = VK_INFO_TYPE_PHYSICAL_GPU_PROPERTIES,
    VK_INFO_TYPE_PHYSICAL_GPU_END_RANGE                     = VK_INFO_TYPE_PHYSICAL_GPU_MEMORY_PROPERTIES,
    VK_NUM_INFO_TYPE_PHYSICAL_GPU                           = (VK_INFO_TYPE_PHYSICAL_GPU_END_RANGE - VK_INFO_TYPE_PHYSICAL_GPU_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPhysicalGpuInfoType_)
} VkPhysicalGpuInfoType;

typedef enum VkFormatInfoType_
{
    // Info type for vkGetFormatInfo()
    VK_INFO_TYPE_FORMAT_PROPERTIES                          = 0x00000000,

    VK_INFO_TYPE_FORMAT_BEGIN_RANGE                         = VK_INFO_TYPE_FORMAT_PROPERTIES,
    VK_INFO_TYPE_FORMAT_END_RANGE                           = VK_INFO_TYPE_FORMAT_PROPERTIES,
    VK_NUM_INFO_TYPE_FORMAT                                  = (VK_INFO_TYPE_FORMAT_END_RANGE - VK_INFO_TYPE_FORMAT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkFormatInfoType_)
} VkFormatInfoType;

typedef enum VkSubresourceInfoType_
{
    // Info type for vkGetImageSubresourceInfo()
    VK_INFO_TYPE_SUBRESOURCE_LAYOUT                         = 0x00000000,

    VK_INFO_TYPE_SUBRESOURCE_BEGIN_RANGE                    = VK_INFO_TYPE_SUBRESOURCE_LAYOUT,
    VK_INFO_TYPE_SUBRESOURCE_END_RANGE                      = VK_INFO_TYPE_SUBRESOURCE_LAYOUT,
    VK_NUM_INFO_TYPE_SUBRESOURCE                            = (VK_INFO_TYPE_SUBRESOURCE_END_RANGE - VK_INFO_TYPE_SUBRESOURCE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkSubresourceInfoType_)
} VkSubresourceInfoType;

typedef enum VkObjectInfoType_
{
    // Info type for vkGetObjectInfo()
    VK_INFO_TYPE_MEMORY_ALLOCATION_COUNT                    = 0x00000000,
    VK_INFO_TYPE_MEMORY_REQUIREMENTS                        = 0x00000001,
    VK_INFO_TYPE_BUFFER_MEMORY_REQUIREMENTS                 = 0x00000002,
    VK_INFO_TYPE_IMAGE_MEMORY_REQUIREMENTS                  = 0x00000003,

    VK_INFO_TYPE_BEGIN_RANGE                                = VK_INFO_TYPE_MEMORY_ALLOCATION_COUNT,
    VK_INFO_TYPE_END_RANGE                                  = VK_INFO_TYPE_IMAGE_MEMORY_REQUIREMENTS,
    VK_NUM_INFO_TYPE                                        = (VK_INFO_TYPE_END_RANGE - VK_INFO_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkObjectInfoType_)
} VkObjectInfoType;

typedef enum VkValidationLevel_
{
    VK_VALIDATION_LEVEL_0                                   = 0x00000000,
    VK_VALIDATION_LEVEL_1                                   = 0x00000001,
    VK_VALIDATION_LEVEL_2                                   = 0x00000002,
    VK_VALIDATION_LEVEL_3                                   = 0x00000003,
    VK_VALIDATION_LEVEL_4                                   = 0x00000004,

    VK_VALIDATION_LEVEL_BEGIN_RANGE                         = VK_VALIDATION_LEVEL_0,
    VK_VALIDATION_LEVEL_END_RANGE                           = VK_VALIDATION_LEVEL_4,
    VK_NUM_VALIDATION_LEVEL                                 = (VK_VALIDATION_LEVEL_END_RANGE - VK_VALIDATION_LEVEL_BEGIN_RANGE + 1),

    VK_MAX_ENUM(VkValidationLevel_)
} VkValidationLevel;

// ------------------------------------------------------------------------------------------------
// Error and return codes

typedef enum VkResult_
{
    // Return codes for successful operation execution (> = 0)
    VK_SUCCESS                                              = 0x0000000,
    VK_UNSUPPORTED                                          = 0x0000001,
    VK_NOT_READY                                            = 0x0000002,
    VK_TIMEOUT                                              = 0x0000003,
    VK_EVENT_SET                                            = 0x0000004,
    VK_EVENT_RESET                                          = 0x0000005,

    // Error codes (negative values)
    VK_ERROR_UNKNOWN                                        = -(0x00000001),
    VK_ERROR_UNAVAILABLE                                    = -(0x00000002),
    VK_ERROR_INITIALIZATION_FAILED                          = -(0x00000003),
    VK_ERROR_OUT_OF_MEMORY                                  = -(0x00000004),
    VK_ERROR_OUT_OF_GPU_MEMORY                              = -(0x00000005),
    VK_ERROR_DEVICE_ALREADY_CREATED                         = -(0x00000006),
    VK_ERROR_DEVICE_LOST                                    = -(0x00000007),
    VK_ERROR_INVALID_POINTER                                = -(0x00000008),
    VK_ERROR_INVALID_VALUE                                  = -(0x00000009),
    VK_ERROR_INVALID_HANDLE                                 = -(0x0000000A),
    VK_ERROR_INVALID_ORDINAL                                = -(0x0000000B),
    VK_ERROR_INVALID_MEMORY_SIZE                            = -(0x0000000C),
    VK_ERROR_INVALID_EXTENSION                              = -(0x0000000D),
    VK_ERROR_INVALID_FLAGS                                  = -(0x0000000E),
    VK_ERROR_INVALID_ALIGNMENT                              = -(0x0000000F),
    VK_ERROR_INVALID_FORMAT                                 = -(0x00000010),
    VK_ERROR_INVALID_IMAGE                                  = -(0x00000011),
    VK_ERROR_INVALID_DESCRIPTOR_SET_DATA                    = -(0x00000012),
    VK_ERROR_INVALID_QUEUE_TYPE                             = -(0x00000013),
    VK_ERROR_INVALID_OBJECT_TYPE                            = -(0x00000014),
    VK_ERROR_UNSUPPORTED_SHADER_IL_VERSION                  = -(0x00000015),
    VK_ERROR_BAD_SHADER_CODE                                = -(0x00000016),
    VK_ERROR_BAD_PIPELINE_DATA                              = -(0x00000017),
    VK_ERROR_TOO_MANY_MEMORY_REFERENCES                     = -(0x00000018),
    VK_ERROR_NOT_MAPPABLE                                   = -(0x00000019),
    VK_ERROR_MEMORY_MAP_FAILED                              = -(0x0000001A),
    VK_ERROR_MEMORY_UNMAP_FAILED                            = -(0x0000001B),
    VK_ERROR_INCOMPATIBLE_DEVICE                            = -(0x0000001C),
    VK_ERROR_INCOMPATIBLE_DRIVER                            = -(0x0000001D),
    VK_ERROR_INCOMPLETE_COMMAND_BUFFER                      = -(0x0000001E),
    VK_ERROR_BUILDING_COMMAND_BUFFER                        = -(0x0000001F),
    VK_ERROR_MEMORY_NOT_BOUND                               = -(0x00000020),
    VK_ERROR_INCOMPATIBLE_QUEUE                             = -(0x00000021),
    VK_ERROR_NOT_SHAREABLE                                  = -(0x00000022),
    VK_MAX_ENUM(_VK_RESULT_CODE)
} VkResult;

// ------------------------------------------------------------------------------------------------
// Vulkan format definitions

typedef enum VkVertexInputStepRate_
{
    VK_VERTEX_INPUT_STEP_RATE_VERTEX                        = 0x0,
    VK_VERTEX_INPUT_STEP_RATE_INSTANCE                      = 0x1,
    VK_VERTEX_INPUT_STEP_RATE_DRAW                          = 0x2,  //Optional

    VK_VERTEX_INPUT_STEP_RATE_BEGIN_RANGE                   = VK_VERTEX_INPUT_STEP_RATE_VERTEX,
    VK_VERTEX_INPUT_STEP_RATE_END_RANGE                     = VK_VERTEX_INPUT_STEP_RATE_DRAW,
    VK_NUM_VERTEX_INPUT_STEP_RATE                           = (VK_VERTEX_INPUT_STEP_RATE_END_RANGE - VK_VERTEX_INPUT_STEP_RATE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkVertexInputStepRate_)
} VkVertexInputStepRate;

typedef enum VkFormat_
{
    VK_FMT_UNDEFINED                                        = 0x00000000,
    VK_FMT_R4G4_UNORM                                       = 0x00000001,
    VK_FMT_R4G4_USCALED                                     = 0x00000002,
    VK_FMT_R4G4B4A4_UNORM                                   = 0x00000003,
    VK_FMT_R4G4B4A4_USCALED                                 = 0x00000004,
    VK_FMT_R5G6B5_UNORM                                     = 0x00000005,
    VK_FMT_R5G6B5_USCALED                                   = 0x00000006,
    VK_FMT_R5G5B5A1_UNORM                                   = 0x00000007,
    VK_FMT_R5G5B5A1_USCALED                                 = 0x00000008,
    VK_FMT_R8_UNORM                                         = 0x00000009,
    VK_FMT_R8_SNORM                                         = 0x0000000A,
    VK_FMT_R8_USCALED                                       = 0x0000000B,
    VK_FMT_R8_SSCALED                                       = 0x0000000C,
    VK_FMT_R8_UINT                                          = 0x0000000D,
    VK_FMT_R8_SINT                                          = 0x0000000E,
    VK_FMT_R8_SRGB                                          = 0x0000000F,
    VK_FMT_R8G8_UNORM                                       = 0x00000010,
    VK_FMT_R8G8_SNORM                                       = 0x00000011,
    VK_FMT_R8G8_USCALED                                     = 0x00000012,
    VK_FMT_R8G8_SSCALED                                     = 0x00000013,
    VK_FMT_R8G8_UINT                                        = 0x00000014,
    VK_FMT_R8G8_SINT                                        = 0x00000015,
    VK_FMT_R8G8_SRGB                                        = 0x00000016,
    VK_FMT_R8G8B8_UNORM                                     = 0x00000017,
    VK_FMT_R8G8B8_SNORM                                     = 0x00000018,
    VK_FMT_R8G8B8_USCALED                                   = 0x00000019,
    VK_FMT_R8G8B8_SSCALED                                   = 0x0000001A,
    VK_FMT_R8G8B8_UINT                                      = 0x0000001B,
    VK_FMT_R8G8B8_SINT                                      = 0x0000001C,
    VK_FMT_R8G8B8_SRGB                                      = 0x0000001D,
    VK_FMT_R8G8B8A8_UNORM                                   = 0x0000001E,
    VK_FMT_R8G8B8A8_SNORM                                   = 0x0000001F,
    VK_FMT_R8G8B8A8_USCALED                                 = 0x00000020,
    VK_FMT_R8G8B8A8_SSCALED                                 = 0x00000021,
    VK_FMT_R8G8B8A8_UINT                                    = 0x00000022,
    VK_FMT_R8G8B8A8_SINT                                    = 0x00000023,
    VK_FMT_R8G8B8A8_SRGB                                    = 0x00000024,
    VK_FMT_R10G10B10A2_UNORM                                = 0x00000025,
    VK_FMT_R10G10B10A2_SNORM                                = 0x00000026,
    VK_FMT_R10G10B10A2_USCALED                              = 0x00000027,
    VK_FMT_R10G10B10A2_SSCALED                              = 0x00000028,
    VK_FMT_R10G10B10A2_UINT                                 = 0x00000029,
    VK_FMT_R10G10B10A2_SINT                                 = 0x0000002A,
    VK_FMT_R16_UNORM                                        = 0x0000002B,
    VK_FMT_R16_SNORM                                        = 0x0000002C,
    VK_FMT_R16_USCALED                                      = 0x0000002D,
    VK_FMT_R16_SSCALED                                      = 0x0000002E,
    VK_FMT_R16_UINT                                         = 0x0000002F,
    VK_FMT_R16_SINT                                         = 0x00000030,
    VK_FMT_R16_SFLOAT                                       = 0x00000031,
    VK_FMT_R16G16_UNORM                                     = 0x00000032,
    VK_FMT_R16G16_SNORM                                     = 0x00000033,
    VK_FMT_R16G16_USCALED                                   = 0x00000034,
    VK_FMT_R16G16_SSCALED                                   = 0x00000035,
    VK_FMT_R16G16_UINT                                      = 0x00000036,
    VK_FMT_R16G16_SINT                                      = 0x00000037,
    VK_FMT_R16G16_SFLOAT                                    = 0x00000038,
    VK_FMT_R16G16B16_UNORM                                  = 0x00000039,
    VK_FMT_R16G16B16_SNORM                                  = 0x0000003A,
    VK_FMT_R16G16B16_USCALED                                = 0x0000003B,
    VK_FMT_R16G16B16_SSCALED                                = 0x0000003C,
    VK_FMT_R16G16B16_UINT                                   = 0x0000003D,
    VK_FMT_R16G16B16_SINT                                   = 0x0000003E,
    VK_FMT_R16G16B16_SFLOAT                                 = 0x0000003F,
    VK_FMT_R16G16B16A16_UNORM                               = 0x00000040,
    VK_FMT_R16G16B16A16_SNORM                               = 0x00000041,
    VK_FMT_R16G16B16A16_USCALED                             = 0x00000042,
    VK_FMT_R16G16B16A16_SSCALED                             = 0x00000043,
    VK_FMT_R16G16B16A16_UINT                                = 0x00000044,
    VK_FMT_R16G16B16A16_SINT                                = 0x00000045,
    VK_FMT_R16G16B16A16_SFLOAT                              = 0x00000046,
    VK_FMT_R32_UINT                                         = 0x00000047,
    VK_FMT_R32_SINT                                         = 0x00000048,
    VK_FMT_R32_SFLOAT                                       = 0x00000049,
    VK_FMT_R32G32_UINT                                      = 0x0000004A,
    VK_FMT_R32G32_SINT                                      = 0x0000004B,
    VK_FMT_R32G32_SFLOAT                                    = 0x0000004C,
    VK_FMT_R32G32B32_UINT                                   = 0x0000004D,
    VK_FMT_R32G32B32_SINT                                   = 0x0000004E,
    VK_FMT_R32G32B32_SFLOAT                                 = 0x0000004F,
    VK_FMT_R32G32B32A32_UINT                                = 0x00000050,
    VK_FMT_R32G32B32A32_SINT                                = 0x00000051,
    VK_FMT_R32G32B32A32_SFLOAT                              = 0x00000052,
    VK_FMT_R64_SFLOAT                                       = 0x00000053,
    VK_FMT_R64G64_SFLOAT                                    = 0x00000054,
    VK_FMT_R64G64B64_SFLOAT                                 = 0x00000055,
    VK_FMT_R64G64B64A64_SFLOAT                              = 0x00000056,
    VK_FMT_R11G11B10_UFLOAT                                 = 0x00000057,
    VK_FMT_R9G9B9E5_UFLOAT                                  = 0x00000058,
    VK_FMT_D16_UNORM                                        = 0x00000059,
    VK_FMT_D24_UNORM                                        = 0x0000005A,
    VK_FMT_D32_SFLOAT                                       = 0x0000005B,
    VK_FMT_S8_UINT                                          = 0x0000005C,
    VK_FMT_D16_UNORM_S8_UINT                                = 0x0000005D,
    VK_FMT_D24_UNORM_S8_UINT                                = 0x0000005E,
    VK_FMT_D32_SFLOAT_S8_UINT                               = 0x0000005F,
    VK_FMT_BC1_RGB_UNORM                                    = 0x00000060,
    VK_FMT_BC1_RGB_SRGB                                     = 0x00000061,
    VK_FMT_BC1_RGBA_UNORM                                   = 0x00000062,
    VK_FMT_BC1_RGBA_SRGB                                    = 0x00000063,
    VK_FMT_BC2_UNORM                                        = 0x00000064,
    VK_FMT_BC2_SRGB                                         = 0x00000065,
    VK_FMT_BC3_UNORM                                        = 0x00000066,
    VK_FMT_BC3_SRGB                                         = 0x00000067,
    VK_FMT_BC4_UNORM                                        = 0x00000068,
    VK_FMT_BC4_SNORM                                        = 0x00000069,
    VK_FMT_BC5_UNORM                                        = 0x0000006A,
    VK_FMT_BC5_SNORM                                        = 0x0000006B,
    VK_FMT_BC6H_UFLOAT                                      = 0x0000006C,
    VK_FMT_BC6H_SFLOAT                                      = 0x0000006D,
    VK_FMT_BC7_UNORM                                        = 0x0000006E,
    VK_FMT_BC7_SRGB                                         = 0x0000006F,
    VK_FMT_ETC2_R8G8B8_UNORM                                = 0x00000070,
    VK_FMT_ETC2_R8G8B8_SRGB                                 = 0x00000071,
    VK_FMT_ETC2_R8G8B8A1_UNORM                              = 0x00000072,
    VK_FMT_ETC2_R8G8B8A1_SRGB                               = 0x00000073,
    VK_FMT_ETC2_R8G8B8A8_UNORM                              = 0x00000074,
    VK_FMT_ETC2_R8G8B8A8_SRGB                               = 0x00000075,
    VK_FMT_EAC_R11_UNORM                                    = 0x00000076,
    VK_FMT_EAC_R11_SNORM                                    = 0x00000077,
    VK_FMT_EAC_R11G11_UNORM                                 = 0x00000078,
    VK_FMT_EAC_R11G11_SNORM                                 = 0x00000079,
    VK_FMT_ASTC_4x4_UNORM                                   = 0x0000007A,
    VK_FMT_ASTC_4x4_SRGB                                    = 0x0000007B,
    VK_FMT_ASTC_5x4_UNORM                                   = 0x0000007C,
    VK_FMT_ASTC_5x4_SRGB                                    = 0x0000007D,
    VK_FMT_ASTC_5x5_UNORM                                   = 0x0000007E,
    VK_FMT_ASTC_5x5_SRGB                                    = 0x0000007F,
    VK_FMT_ASTC_6x5_UNORM                                   = 0x00000080,
    VK_FMT_ASTC_6x5_SRGB                                    = 0x00000081,
    VK_FMT_ASTC_6x6_UNORM                                   = 0x00000082,
    VK_FMT_ASTC_6x6_SRGB                                    = 0x00000083,
    VK_FMT_ASTC_8x5_UNORM                                   = 0x00000084,
    VK_FMT_ASTC_8x5_SRGB                                    = 0x00000085,
    VK_FMT_ASTC_8x6_UNORM                                   = 0x00000086,
    VK_FMT_ASTC_8x6_SRGB                                    = 0x00000087,
    VK_FMT_ASTC_8x8_UNORM                                   = 0x00000088,
    VK_FMT_ASTC_8x8_SRGB                                    = 0x00000089,
    VK_FMT_ASTC_10x5_UNORM                                  = 0x0000008A,
    VK_FMT_ASTC_10x5_SRGB                                   = 0x0000008B,
    VK_FMT_ASTC_10x6_UNORM                                  = 0x0000008C,
    VK_FMT_ASTC_10x6_SRGB                                   = 0x0000008D,
    VK_FMT_ASTC_10x8_UNORM                                  = 0x0000008E,
    VK_FMT_ASTC_10x8_SRGB                                   = 0x0000008F,
    VK_FMT_ASTC_10x10_UNORM                                 = 0x00000090,
    VK_FMT_ASTC_10x10_SRGB                                  = 0x00000091,
    VK_FMT_ASTC_12x10_UNORM                                 = 0x00000092,
    VK_FMT_ASTC_12x10_SRGB                                  = 0x00000093,
    VK_FMT_ASTC_12x12_UNORM                                 = 0x00000094,
    VK_FMT_ASTC_12x12_SRGB                                  = 0x00000095,
    VK_FMT_B4G4R4A4_UNORM                                   = 0x00000096,
    VK_FMT_B5G5R5A1_UNORM                                   = 0x00000097,
    VK_FMT_B5G6R5_UNORM                                     = 0x00000098,
    VK_FMT_B5G6R5_USCALED                                   = 0x00000099,
    VK_FMT_B8G8R8_UNORM                                     = 0x0000009A,
    VK_FMT_B8G8R8_SNORM                                     = 0x0000009B,
    VK_FMT_B8G8R8_USCALED                                   = 0x0000009C,
    VK_FMT_B8G8R8_SSCALED                                   = 0x0000009D,
    VK_FMT_B8G8R8_UINT                                      = 0x0000009E,
    VK_FMT_B8G8R8_SINT                                      = 0x0000009F,
    VK_FMT_B8G8R8_SRGB                                      = 0x000000A0,
    VK_FMT_B8G8R8A8_UNORM                                   = 0x000000A1,
    VK_FMT_B8G8R8A8_SNORM                                   = 0x000000A2,
    VK_FMT_B8G8R8A8_USCALED                                 = 0x000000A3,
    VK_FMT_B8G8R8A8_SSCALED                                 = 0x000000A4,
    VK_FMT_B8G8R8A8_UINT                                    = 0x000000A5,
    VK_FMT_B8G8R8A8_SINT                                    = 0x000000A6,
    VK_FMT_B8G8R8A8_SRGB                                    = 0x000000A7,
    VK_FMT_B10G10R10A2_UNORM                                = 0x000000A8,
    VK_FMT_B10G10R10A2_SNORM                                = 0x000000A9,
    VK_FMT_B10G10R10A2_USCALED                              = 0x000000AA,
    VK_FMT_B10G10R10A2_SSCALED                              = 0x000000AB,
    VK_FMT_B10G10R10A2_UINT                                 = 0x000000AC,
    VK_FMT_B10G10R10A2_SINT                                 = 0x000000AD,

    VK_FMT_BEGIN_RANGE                                      = VK_FMT_UNDEFINED,
    VK_FMT_END_RANGE                                        = VK_FMT_B10G10R10A2_SINT,
    VK_NUM_FMT                                              = (VK_FMT_END_RANGE - VK_FMT_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkFormat_)
} VkFormat;

// Shader stage enumerant
typedef enum VkPipelineShaderStage_
{
    VK_SHADER_STAGE_VERTEX                                  = 0,
    VK_SHADER_STAGE_TESS_CONTROL                            = 1,
    VK_SHADER_STAGE_TESS_EVALUATION                         = 2,
    VK_SHADER_STAGE_GEOMETRY                                = 3,
    VK_SHADER_STAGE_FRAGMENT                                = 4,
    VK_SHADER_STAGE_COMPUTE                                 = 5,

    VK_SHADER_STAGE_BEGIN_RANGE                             = VK_SHADER_STAGE_VERTEX,
    VK_SHADER_STAGE_END_RANGE                               = VK_SHADER_STAGE_COMPUTE,
    VK_NUM_SHADER_STAGE                                     = (VK_SHADER_STAGE_END_RANGE - VK_SHADER_STAGE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkPipelineShaderStage_)
} VkPipelineShaderStage;

typedef enum VkShaderStageFlags_
{
    VK_SHADER_STAGE_FLAGS_VERTEX_BIT                        = 0x00000001,
    VK_SHADER_STAGE_FLAGS_TESS_CONTROL_BIT                  = 0x00000002,
    VK_SHADER_STAGE_FLAGS_TESS_EVALUATION_BIT               = 0x00000004,
    VK_SHADER_STAGE_FLAGS_GEOMETRY_BIT                      = 0x00000008,
    VK_SHADER_STAGE_FLAGS_FRAGMENT_BIT                      = 0x00000010,
    VK_SHADER_STAGE_FLAGS_COMPUTE_BIT                       = 0x00000020,

    VK_SHADER_STAGE_FLAGS_ALL                               = 0x7FFFFFFF,
    VK_MAX_ENUM(VkShaderStageFlags_)
} VkShaderStageFlags;

// Structure type enumerant
typedef enum VkStructureType_
{
    VK_STRUCTURE_TYPE_APPLICATION_INFO                      = 0,
    VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO                    = 1,
    VK_STRUCTURE_TYPE_MEMORY_ALLOC_INFO                     = 2,
    VK_STRUCTURE_TYPE_MEMORY_OPEN_INFO                      = 4,
    VK_STRUCTURE_TYPE_PEER_MEMORY_OPEN_INFO                 = 5,
    VK_STRUCTURE_TYPE_BUFFER_VIEW_ATTACH_INFO               = 6,
    VK_STRUCTURE_TYPE_IMAGE_VIEW_ATTACH_INFO                = 7,
    VK_STRUCTURE_TYPE_EVENT_WAIT_INFO                       = 8,
    VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO                = 9,
    VK_STRUCTURE_TYPE_COLOR_ATTACHMENT_VIEW_CREATE_INFO     = 10,
    VK_STRUCTURE_TYPE_DEPTH_STENCIL_VIEW_CREATE_INFO        = 11,
    VK_STRUCTURE_TYPE_SHADER_CREATE_INFO                    = 12,
    VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO          = 13,
    VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO                   = 14,
    VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO     = 15,
    VK_STRUCTURE_TYPE_DYNAMIC_VP_STATE_CREATE_INFO          = 16,
    VK_STRUCTURE_TYPE_DYNAMIC_RS_STATE_CREATE_INFO          = 17,
    VK_STRUCTURE_TYPE_DYNAMIC_CB_STATE_CREATE_INFO          = 18,
    VK_STRUCTURE_TYPE_DYNAMIC_DS_STATE_CREATE_INFO          = 19,
    VK_STRUCTURE_TYPE_CMD_BUFFER_CREATE_INFO                = 20,
    VK_STRUCTURE_TYPE_EVENT_CREATE_INFO                     = 21,
    VK_STRUCTURE_TYPE_FENCE_CREATE_INFO                     = 22,
    VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO                 = 23,
    VK_STRUCTURE_TYPE_SEMAPHORE_OPEN_INFO                   = 24,
    VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO                = 25,
    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO     = 26,
    VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO         = 27,
    VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_CREATE_INFO     = 28,
    VK_STRUCTURE_TYPE_PIPELINE_IA_STATE_CREATE_INFO         = 29,
    VK_STRUCTURE_TYPE_PIPELINE_TESS_STATE_CREATE_INFO       = 30,
    VK_STRUCTURE_TYPE_PIPELINE_VP_STATE_CREATE_INFO         = 31,
    VK_STRUCTURE_TYPE_PIPELINE_RS_STATE_CREATE_INFO         = 32,
    VK_STRUCTURE_TYPE_PIPELINE_MS_STATE_CREATE_INFO         = 33,
    VK_STRUCTURE_TYPE_PIPELINE_CB_STATE_CREATE_INFO         = 34,
    VK_STRUCTURE_TYPE_PIPELINE_DS_STATE_CREATE_INFO         = 35,
    VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO                     = 36,
    VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO                    = 37,
    VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO               = 38,
    VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO               = 39,
    VK_STRUCTURE_TYPE_CMD_BUFFER_BEGIN_INFO                 = 40,
    VK_STRUCTURE_TYPE_CMD_BUFFER_GRAPHICS_BEGIN_INFO        = 41,
    VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO               = 42,
    VK_STRUCTURE_TYPE_LAYER_CREATE_INFO                     = 43,
    VK_STRUCTURE_TYPE_PIPELINE_BARRIER                      = 44,
    VK_STRUCTURE_TYPE_MEMORY_BARRIER                        = 45,
    VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER                 = 46,
    VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER                  = 47,
    VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO           = 48,
    VK_STRUCTURE_TYPE_UPDATE_SAMPLERS                       = 49,
    VK_STRUCTURE_TYPE_UPDATE_SAMPLER_TEXTURES               = 50,
    VK_STRUCTURE_TYPE_UPDATE_IMAGES                         = 51,
    VK_STRUCTURE_TYPE_UPDATE_BUFFERS                        = 52,
    VK_STRUCTURE_TYPE_UPDATE_AS_COPY                        = 53,
    VK_STRUCTURE_TYPE_MEMORY_ALLOC_BUFFER_INFO              = 54,
    VK_STRUCTURE_TYPE_MEMORY_ALLOC_IMAGE_INFO               = 55,
    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                  = 56,

    VK_STRUCTURE_TYPE_BEGIN_RANGE                           = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    VK_STRUCTURE_TYPE_END_RANGE                             = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,

    VK_NUM_STRUCTURE_TYPE                                   = (VK_STRUCTURE_TYPE_END_RANGE - VK_STRUCTURE_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkStructureType_)
} VkStructureType;

// ------------------------------------------------------------------------------------------------
// Flags

// Device creation flags
typedef enum VkDeviceCreateFlags_
{
    VK_DEVICE_CREATE_VALIDATION_BIT                         = 0x00000001,
    VK_DEVICE_CREATE_MGPU_IQ_MATCH_BIT                      = 0x00000002,
    VK_MAX_ENUM(VkDeviceCreateFlags_)
} VkDeviceCreateFlags;

// Queue capabilities
typedef enum VkQueueFlags_
{
    VK_QUEUE_GRAPHICS_BIT                                   = 0x00000001,   // Queue supports graphics operations
    VK_QUEUE_COMPUTE_BIT                                    = 0x00000002,   // Queue supports compute operations
    VK_QUEUE_DMA_BIT                                        = 0x00000004,   // Queue supports DMA operations
    VK_QUEUE_EXTENDED_BIT                                   = 0x40000000,   // Extended queue
    VK_MAX_ENUM(VkQueueFlags_)
} VkQueueFlags;

// memory properties passed into vkAllocMemory().
typedef enum VkMemoryPropertyFlags_
{
    VK_MEMORY_PROPERTY_GPU_ONLY                             = 0x00000000,   // If not set, then allocate memory on device (GPU)
    VK_MEMORY_PROPERTY_CPU_VISIBLE_BIT                      = 0x00000001,
    VK_MEMORY_PROPERTY_CPU_GPU_COHERENT_BIT                 = 0x00000002,
    VK_MEMORY_PROPERTY_CPU_UNCACHED_BIT                     = 0x00000004,
    VK_MEMORY_PROPERTY_CPU_WRITE_COMBINED_BIT               = 0x00000008,
    VK_MEMORY_PROPERTY_PREFER_CPU_LOCAL                     = 0x00000010,   // all else being equal, prefer CPU access
    VK_MEMORY_PROPERTY_SHAREABLE_BIT                        = 0x00000020,
    VK_MAX_ENUM(VkMemoryPropertyFlags_)
} VkMemoryPropertyFlags;

typedef enum VkMemoryType_
{
    VK_MEMORY_TYPE_OTHER                                    = 0x00000000,   // device memory that is not any of the others
    VK_MEMORY_TYPE_BUFFER                                   = 0x00000001,   // memory for buffers and associated information
    VK_MEMORY_TYPE_IMAGE                                    = 0x00000002,   // memory for images and associated information

    VK_MEMORY_TYPE_BEGIN_RANGE                              = VK_MEMORY_TYPE_OTHER,
    VK_MEMORY_TYPE_END_RANGE                                = VK_MEMORY_TYPE_IMAGE,
    VK_NUM_MEMORY_TYPE                                      = (VK_MEMORY_TYPE_END_RANGE - VK_MEMORY_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkMemoryType_)
} VkMemoryType;

// Buffer and buffer allocation usage flags
typedef enum VkBufferUsageFlags_
{
    VK_BUFFER_USAGE_GENERAL                                 = 0x00000000,   // no special usage
    VK_BUFFER_USAGE_SHADER_ACCESS_READ_BIT                  = 0x00000001,   // Shader read (e.g. TBO, image buffer, UBO, SSBO)
    VK_BUFFER_USAGE_SHADER_ACCESS_WRITE_BIT                 = 0x00000002,   // Shader write (e.g. image buffer, SSBO)
    VK_BUFFER_USAGE_SHADER_ACCESS_ATOMIC_BIT                = 0x00000004,   // Shader atomic operations (e.g. image buffer, SSBO)
    VK_BUFFER_USAGE_TRANSFER_SOURCE_BIT                     = 0x00000008,   // used as a source for copies
    VK_BUFFER_USAGE_TRANSFER_DESTINATION_BIT                = 0x00000010,   // used as a destination for copies
    VK_BUFFER_USAGE_UNIFORM_READ_BIT                        = 0x00000020,   // Uniform read (UBO)
    VK_BUFFER_USAGE_INDEX_FETCH_BIT                         = 0x00000040,   // Fixed function index fetch (index buffer)
    VK_BUFFER_USAGE_VERTEX_FETCH_BIT                        = 0x00000080,   // Fixed function vertex fetch (VBO)
    VK_BUFFER_USAGE_SHADER_STORAGE_BIT                      = 0x00000100,   // Shader storage buffer (SSBO)
    VK_BUFFER_USAGE_INDIRECT_PARAMETER_FETCH_BIT            = 0x00000200,   // Can be the source of indirect parameters (e.g. indirect buffer, parameter buffer)
    VK_BUFFER_USAGE_TEXTURE_BUFFER_BIT                      = 0x00000400,   // texture buffer (TBO)
    VK_BUFFER_USAGE_IMAGE_BUFFER_BIT                        = 0x00000800,   // image buffer (load/store)
    VK_MAX_ENUM(VkBufferUsageFlags_)
} VkBufferUsageFlags;

// Buffer flags
typedef enum VkBufferCreateFlags_
{
    VK_BUFFER_CREATE_SHAREABLE_BIT                          = 0x00000001,
    VK_BUFFER_CREATE_SPARSE_BIT                             = 0x00000002,
    VK_MAX_ENUM(VkBufferCreateFlags_)
} VkBufferCreateFlags;

typedef enum VkBufferViewType_
{
    VK_BUFFER_VIEW_RAW                                      = 0x00000000,   // Raw buffer without special structure (e.g. UBO, SSBO, indirect and parameter buffers)
    VK_BUFFER_VIEW_TYPED                                    = 0x00000001,   // Typed buffer, format and channels are used (TBO, image buffer)

    VK_BUFFER_VIEW_TYPE_BEGIN_RANGE                         = VK_BUFFER_VIEW_RAW,
    VK_BUFFER_VIEW_TYPE_END_RANGE                           = VK_BUFFER_VIEW_TYPED,
    VK_NUM_BUFFER_VIEW_TYPE                                 = (VK_BUFFER_VIEW_TYPE_END_RANGE - VK_BUFFER_VIEW_TYPE_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkBufferViewType_)
} VkBufferViewType;


// Images memory allocations can be used for resources of a given format class.
typedef enum VkImageFormatClass_
{
    VK_IMAGE_FORMAT_CLASS_128_BITS                          = 1,  // color formats
    VK_IMAGE_FORMAT_CLASS_96_BITS                           = 2,
    VK_IMAGE_FORMAT_CLASS_64_BITS                           = 3,
    VK_IMAGE_FORMAT_CLASS_48_BITS                           = 4,
    VK_IMAGE_FORMAT_CLASS_32_BITS                           = 5,
    VK_IMAGE_FORMAT_CLASS_24_BITS                           = 6,
    VK_IMAGE_FORMAT_CLASS_16_BITS                           = 7,
    VK_IMAGE_FORMAT_CLASS_8_BITS                            = 8,
    VK_IMAGE_FORMAT_CLASS_128_BIT_BLOCK                     = 9,  // 128-bit block compressed formats
    VK_IMAGE_FORMAT_CLASS_64_BIT_BLOCK                      = 10, // 64-bit block compressed formats
    VK_IMAGE_FORMAT_CLASS_D32                               = 11, // D32_SFLOAT
    VK_IMAGE_FORMAT_CLASS_D24                               = 12, // D24_UNORM
    VK_IMAGE_FORMAT_CLASS_D16                               = 13, // D16_UNORM
    VK_IMAGE_FORMAT_CLASS_S8                                = 14, // S8_UINT
    VK_IMAGE_FORMAT_CLASS_D32S8                             = 15, // D32_SFLOAT_S8_UINT
    VK_IMAGE_FORMAT_CLASS_D24S8                             = 16, // D24_UNORM_S8_UINT
    VK_IMAGE_FORMAT_CLASS_D16S8                             = 17, // D16_UNORM_S8_UINT
    VK_IMAGE_FORMAT_CLASS_LINEAR                            = 18, // used for pitch-linear (transparent) textures

    VK_IMAGE_FORMAT_CLASS_BEGIN_RANGE                       = VK_IMAGE_FORMAT_CLASS_128_BITS,
    VK_IMAGE_FORMAT_CLASS_END_RANGE                         = VK_IMAGE_FORMAT_CLASS_LINEAR,
    VK_NUM_IMAGE_FORMAT_CLASS                               = (VK_IMAGE_FORMAT_CLASS_END_RANGE - VK_IMAGE_FORMAT_CLASS_BEGIN_RANGE + 1),
    VK_MAX_ENUM(VkImageFormatClass_)
} VkImageFormatClass;

// Image and image allocation usage flags
typedef enum VkImageUsageFlags_
{
    VK_IMAGE_USAGE_GENERAL                                  = 0x00000000,   // no special usage
    VK_IMAGE_USAGE_SHADER_ACCESS_READ_BIT                   = 0x00000001,   // shader read (e.g. texture, image)
    VK_IMAGE_USAGE_SHADER_ACCESS_WRITE_BIT                  = 0x00000002,   // shader write (e.g. image)
    VK_IMAGE_USAGE_SHADER_ACCESS_ATOMIC_BIT                 = 0x00000004,   // shader atomic operations (e.g. image)
    VK_IMAGE_USAGE_TRANSFER_SOURCE_BIT                      = 0x00000008,   // used as a source for copies
    VK_IMAGE_USAGE_TRANSFER_DESTINATION_BIT                 = 0x00000010,   // used as a destination for copies
    VK_IMAGE_USAGE_TEXTURE_BIT                              = 0x00000020,   // opaque texture (2d, 3d, etc.)
    VK_IMAGE_USAGE_IMAGE_BIT                                = 0x00000040,   // opaque image (2d, 3d, etc.)
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT                     = 0x00000080,   // framebuffer color attachment
    VK_IMAGE_USAGE_DEPTH_STENCIL_BIT                        = 0x00000100,   // framebuffer depth/stencil
    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT                 = 0x00000200,   // image data not needed outside of rendering.
    VK_MAX_ENUM(VkImageUsageFlags_)
} VkImageUsageFlags;

// Image flags
typedef enum VkImageCreateFlags_
{
    VK_IMAGE_CREATE_INVARIANT_DATA_BIT                      = 0x00000001,
    VK_IMAGE_CREATE_CLONEABLE_BIT                           = 0x00000002,
    VK_IMAGE_CREATE_SHAREABLE_BIT                           = 0x00000004,
    VK_IMAGE_CREATE_SPARSE_BIT                              = 0x00000008,
    VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT                      = 0x00000010,   // Allows image views to have different format than the base image
    VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT                     = 0x00000020,   // Allows creating image views with cube type from the created image
    VK_MAX_ENUM(VkImageCreateFlags_)
} VkImageCreateFlags;

// Depth-stencil view creation flags
typedef enum VkDepthStencilViewCreateFlags_
{
    VK_DEPTH_STENCIL_VIEW_CREATE_READ_ONLY_DEPTH_BIT        = 0x00000001,
    VK_DEPTH_STENCIL_VIEW_CREATE_READ_ONLY_STENCIL_BIT      = 0x00000002,
    VK_MAX_ENUM(VkDepthStencilViewCreateFlags_)
} VkDepthStencilViewCreateFlags;

// Pipeline creation flags
typedef enum VkPipelineCreateFlags_
{
    VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT             = 0x00000001,
    VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT                = 0x00000002,
    VK_MAX_ENUM(VkPipelineCreateFlags_)
} VkPipelineCreateFlags;

// Fence creation flags
typedef enum VkFenceCreateFlags_
{
    VK_FENCE_CREATE_SIGNALED_BIT                            = 0x00000001,
    VK_MAX_ENUM(VkFenceCreateFlags_)
} VkFenceCreateFlags;

// Semaphore creation flags
typedef enum VkSemaphoreCreateFlags_
{
    VK_SEMAPHORE_CREATE_SHAREABLE_BIT                       = 0x00000001,
    VK_MAX_ENUM(VkSemaphoreCreateFlags_)
} VkSemaphoreCreateFlags;

// Format capability flags
typedef enum VkFormatFeatureFlags_
{
    VK_FORMAT_IMAGE_SHADER_READ_BIT                         = 0x00000001,
    VK_FORMAT_IMAGE_SHADER_WRITE_BIT                        = 0x00000002,
    VK_FORMAT_IMAGE_COPY_BIT                                = 0x00000004,
    VK_FORMAT_MEMORY_SHADER_ACCESS_BIT                      = 0x00000008,
    VK_FORMAT_COLOR_ATTACHMENT_WRITE_BIT                    = 0x00000010,
    VK_FORMAT_COLOR_ATTACHMENT_BLEND_BIT                    = 0x00000020,
    VK_FORMAT_DEPTH_ATTACHMENT_BIT                          = 0x00000040,
    VK_FORMAT_STENCIL_ATTACHMENT_BIT                        = 0x00000080,
    VK_FORMAT_MSAA_ATTACHMENT_BIT                           = 0x00000100,
    VK_FORMAT_CONVERSION_BIT                                = 0x00000200,
    VK_MAX_ENUM(VkFormatFeatureFlags_)
} VkFormatFeatureFlags;

// Query flags
typedef enum VkQueryControlFlags_
{
    VK_QUERY_IMPRECISE_DATA_BIT                             = 0x00000001,
    VK_MAX_ENUM(VkQueryControlFlags_)
} VkQueryControlFlags;

// GPU compatibility flags
typedef enum VkGpuCompatibilityFlags_
{
    VK_GPU_COMPAT_ASIC_FEATURES_BIT                         = 0x00000001,
    VK_GPU_COMPAT_IQ_MATCH_BIT                              = 0x00000002,
    VK_GPU_COMPAT_PEER_TRANSFER_BIT                         = 0x00000004,
    VK_GPU_COMPAT_SHARED_MEMORY_BIT                         = 0x00000008,
    VK_GPU_COMPAT_SHARED_SYNC_BIT                           = 0x00000010,
    VK_GPU_COMPAT_SHARED_GPU0_DISPLAY_BIT                   = 0x00000020,
    VK_GPU_COMPAT_SHARED_GPU1_DISPLAY_BIT                   = 0x00000040,
    VK_MAX_ENUM(VkGpuCompatibilityFlags_)
} VkGpuCompatibilityFlags;

// Command buffer building flags
typedef enum VkCmdBufferBuildFlags_
{
    VK_CMD_BUFFER_OPTIMIZE_GPU_SMALL_BATCH_BIT              = 0x00000001,
    VK_CMD_BUFFER_OPTIMIZE_PIPELINE_SWITCH_BIT              = 0x00000002,
    VK_CMD_BUFFER_OPTIMIZE_ONE_TIME_SUBMIT_BIT              = 0x00000004,
    VK_CMD_BUFFER_OPTIMIZE_DESCRIPTOR_SET_SWITCH_BIT        = 0x00000008,
    VK_MAX_ENUM(VkCmdBufferBuildFlags_)
} VkCmdBufferBuildFlags;

// ------------------------------------------------------------------------------------------------
// Vulkan structures

typedef struct VkOffset2D_
{
    int32_t                                     x;
    int32_t                                     y;
} VkOffset2D;

typedef struct VkOffset3D_
{
    int32_t                                     x;
    int32_t                                     y;
    int32_t                                     z;
} VkOffset3D;

typedef struct VkExtent2D_
{
    int32_t                                     width;
    int32_t                                     height;
} VkExtent2D;

typedef struct VkExtent3D_
{
    int32_t                                     width;
    int32_t                                     height;
    int32_t                                     depth;
} VkExtent3D;

typedef struct VkViewport_
{
    float                                       originX;
    float                                       originY;
    float                                       width;
    float                                       height;
    float                                       minDepth;
    float                                       maxDepth;
} VkViewport;

typedef struct VkRect_
{
    VkOffset2D                                  offset;
    VkExtent2D                                  extent;
} VkRect;

typedef struct VkChannelMapping_
{
    VkChannelSwizzle                            r;
    VkChannelSwizzle                            g;
    VkChannelSwizzle                            b;
    VkChannelSwizzle                            a;
} VkChannelMapping;

typedef struct VkPhysicalGpuProperties_
{
    uint32_t                                    apiVersion;
    uint32_t                                    driverVersion;
    uint32_t                                    vendorId;
    uint32_t                                    deviceId;
    VkPhysicalGpuType                           gpuType;
    char                                        gpuName[VK_MAX_PHYSICAL_GPU_NAME];
    VkGpuSize                                   maxInlineMemoryUpdateSize;
    uint32_t                                    maxBoundDescriptorSets;
    uint32_t                                    maxThreadGroupSize;
    uint64_t                                    timestampFrequency;
    bool32_t                                    multiColorAttachmentClears;
    uint32_t                                    maxDescriptorSets;              // at least 2?
    uint32_t                                    maxViewports;                   // at least 16?
    uint32_t                                    maxColorAttachments;            // at least 8?
} VkPhysicalGpuProperties;

typedef struct VkPhysicalGpuPerformance_
{
    float                                       maxGpuClock;
    float                                       aluPerClock;
    float                                       texPerClock;
    float                                       primsPerClock;
    float                                       pixelsPerClock;
} VkPhysicalGpuPerformance;

typedef struct VkGpuCompatibilityInfo_
{
    VkFlags                                     compatibilityFlags; // VkGpuCompatibilityFlags
} VkGpuCompatibilityInfo;

typedef struct VkApplicationInfo_
{
    VkStructureType                             sType;              // Type of structure. Should be VK_STRUCTURE_TYPE_APPLICATION_INFO
    const void*                                 pNext;              // Next structure in chain
    const char*                                 pAppName;
    uint32_t                                    appVersion;
    const char*                                 pEngineName;
    uint32_t                                    engineVersion;
    uint32_t                                    apiVersion;
} VkApplicationInfo;

typedef void* (VKAPI *PFN_vkAllocFunction)(
    void*                                       pUserData,
    size_t                                      size,
    size_t                                      alignment,
    VkSystemAllocType                           allocType);

typedef void (VKAPI *PFN_vkFreeFunction)(
    void*                                       pUserData,
    void*                                       pMem);

typedef struct VkAllocCallbacks_
{
    void*                                       pUserData;
    PFN_vkAllocFunction                         pfnAlloc;
    PFN_vkFreeFunction                          pfnFree;
} VkAllocCallbacks;

typedef struct _VkDeviceQueueCreateInfo
{
    uint32_t                                    queueNodeIndex;
    uint32_t                                    queueCount;
} VkDeviceQueueCreateInfo;

typedef struct _VkDeviceCreateInfo
{
    VkStructureType                             sType;                      // Should be VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure
    uint32_t                                    queueRecordCount;
    const VkDeviceQueueCreateInfo*              pRequestedQueues;
    uint32_t                                    extensionCount;
    const char*const*                           ppEnabledExtensionNames;
    VkValidationLevel                           maxValidationLevel;
    VkFlags                                     flags;                      // VkDeviceCreateFlags
} VkDeviceCreateInfo;

typedef struct _VkInstanceCreateInfo
{
    VkStructureType                           sType;                      // Should be VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure
    const VkApplicationInfo*                  pAppInfo;
    const VkAllocCallbacks*                   pAllocCb;
    uint32_t                                    extensionCount;
    const char*const*                           ppEnabledExtensionNames;    // layer or extension name to be enabled
} VkInstanceCreateInfo;

// can be added to VkDeviceCreateInfo or VkInstanceCreateInfo via pNext
typedef struct _VkLayerCreateInfo
{
    VkStructureType                             sType;                      // Should be VK_STRUCTURE_TYPE_LAYER_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure
    uint32_t                                    layerCount;
    const char *const*                          ppActiveLayerNames;         // layer name from the layer's vkEnumerateLayers())
} VkLayerCreateInfo;

typedef struct VkPhysicalGpuQueueProperties_
{
    VkFlags                                     queueFlags;                 // VkQueueFlags
    uint32_t                                    queueCount;
    uint32_t                                    maxAtomicCounters;
    bool32_t                                    supportsTimestamps;
    uint32_t                                    maxMemReferences;           // Tells how many memory references can be active for the given queue
} VkPhysicalGpuQueueProperties;

typedef struct VkPhysicalGpuMemoryProperties_
{
    bool32_t                                    supportsMigration;
    bool32_t                                    supportsPinning;
} VkPhysicalGpuMemoryProperties;

typedef struct _VkMemoryAllocInfo
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_MEMORY_ALLOC_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkGpuSize                                   allocationSize;             // Size of memory allocation
    VkFlags                                     memProps;                   // VkMemoryPropertyFlags
    VkMemoryType                                memType;
    VkMemoryPriority                            memPriority;
} VkMemoryAllocInfo;

// This structure is included in the VkMemoryAllocInfo chain
// for memory regions allocated for buffer usage.
typedef struct _VkMemoryAllocBufferInfo
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_MEMORY_ALLOC_BUFFER_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkFlags                                     usage;                      // VkBufferUsageFlags
} VkMemoryAllocBufferInfo;

// This structure is included in the VkMemoryAllocInfo chain
// for memory regions allocated for image usage.
typedef struct _VkMemoryAllocImageInfo
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_MEMORY_ALLOC_IMAGE_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkFlags                                     usage;                      // VkImageUsageFlags
    VkImageFormatClass                          formatClass;
    uint32_t                                    samples;
} VkMemoryAllocImageInfo;

typedef struct VkMemoryOpenInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_MEMORY_OPEN_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkGpuMemory                                 sharedMem;
} VkMemoryOpenInfo;

typedef struct VkPeerMemoryOpenInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_PEER_MEMORY_OPEN_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkGpuMemory                                 originalMem;
} VkPeerMemoryOpenInfo;

typedef struct VkMemoryRequirements_
{
    VkGpuSize                                   size;                       // Specified in bytes
    VkGpuSize                                   alignment;                  // Specified in bytes
    VkGpuSize                                   granularity;                // Granularity on which vkBindObjectMemoryRange can bind sub-ranges of memory specified in bytes (usually the page size)
    VkFlags                                     memProps;                   // VkMemoryPropertyFlags
    VkMemoryType                                memType;
} VkMemoryRequirements;

typedef struct VkBufferMemoryRequirements_
{
    VkFlags                                     usage;                      // VkBufferUsageFlags
} VkBufferMemoryRequirements;

typedef struct VkImageMemoryRequirements_
{
    VkFlags                                     usage;                      // VkImageUsageFlags
    VkImageFormatClass                          formatClass;
    uint32_t                                    samples;
} VkImageMemoryRequirements;

typedef struct VkFormatProperties_
{
    VkFlags                                     linearTilingFeatures;      // VkFormatFeatureFlags
    VkFlags                                     optimalTilingFeatures;     // VkFormatFeatureFlags
} VkFormatProperties;

typedef struct VkBufferViewAttachInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_BUFFER_VIEW_ATTACH_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkBufferView                                view;
} VkBufferViewAttachInfo;

typedef struct VkImageViewAttachInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_IMAGE_VIEW_ATTACH_INFO
    const void*                                 pNext;                      // Pointer to next structure
    VkImageView                                 view;
    VkImageLayout                               layout;
} VkImageViewAttachInfo;

typedef struct VkUpdateSamplers_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_UPDATE_SAMPLERS
    const void*                                 pNext;                      // Pointer to next structure
    uint32_t                                    binding;                    // Binding of the sampler (array)
    uint32_t                                    arrayIndex;                 // First element of the array to update or zero otherwise
    uint32_t                                    count;                      // Number of elements to update
    const VkSampler*                            pSamplers;
} VkUpdateSamplers;

typedef struct VkSamplerImageViewInfo_
{
    VkSampler                                   sampler;
    const VkImageViewAttachInfo*                pImageView;
} VkSamplerImageViewInfo;

typedef struct VkUpdateSamplerTextures_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_UPDATE_SAMPLER_TEXTURES
    const void*                                 pNext;                      // Pointer to next structure
    uint32_t                                    binding;                    // Binding of the combined texture sampler (array)
    uint32_t                                    arrayIndex;                 // First element of the array to update or zero otherwise
    uint32_t                                    count;                      // Number of elements to update
    const VkSamplerImageViewInfo*               pSamplerImageViews;
} VkUpdateSamplerTextures;

typedef struct VkUpdateImages_
{
    VkStructureType                             sType;                     // Must be VK_STRUCTURE_TYPE_UPDATE_IMAGES
    const void*                                 pNext;                     // Pointer to next structure
    VkDescriptorType                            descriptorType;
    uint32_t                                    binding;                   // Binding of the image (array)
    uint32_t                                    arrayIndex;                // First element of the array to update or zero otherwise
    uint32_t                                    count;                     // Number of elements to update
    const VkImageViewAttachInfo*                pImageViews;
} VkUpdateImages;

typedef struct VkUpdateBuffers_
{
    VkStructureType                             sType;                    // Must be VK_STRUCTURE_TYPE_UPDATE_BUFFERS
    const void*                                 pNext;                    // Pointer to next structure
    VkDescriptorType                            descriptorType;
    uint32_t                                    binding;                  // Binding of the buffer (array)
    uint32_t                                    arrayIndex;               // First element of the array to update or zero otherwise
    uint32_t                                    count;                    // Number of elements to update
    const VkBufferViewAttachInfo*               pBufferViews;
} VkUpdateBuffers;

typedef struct VkUpdateAsCopy_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_UPDATE_AS_COPY
    const void*                                 pNext;                      // Pointer to next structure
    VkDescriptorType                            descriptorType;
    VkDescriptorSet                             descriptorSet;
    uint32_t                                    binding;
    uint32_t                                    arrayElement;
    uint32_t                                    count;
} VkUpdateAsCopy;

typedef struct _VkBufferCreateInfo
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure.
    VkGpuSize                                   size;                       // Specified in bytes
    VkFlags                                     usage;                      // VkBufferUsageFlags
    VkFlags                                     flags;                      // VkBufferCreateFlags
} VkBufferCreateInfo;

typedef struct _VkBufferViewCreateInfo
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure.
    VkBuffer                                    buffer;
    VkBufferViewType                            viewType;
    VkFormat                                    format;                     // Optionally specifies format of elements
    VkGpuSize                                   offset;                     // Specified in bytes
    VkGpuSize                                   range;                      // View size specified in bytes
} VkBufferViewCreateInfo;

typedef struct VkImageSubresource_
{
    VkImageAspect                               aspect;
    uint32_t                                    mipLevel;
    uint32_t                                    arraySlice;
} VkImageSubresource;

typedef struct VkImageSubresourceRange_
{
    VkImageAspect                               aspect;
    uint32_t                                    baseMipLevel;
    uint32_t                                    mipLevels;
    uint32_t                                    baseArraySlice;
    uint32_t                                    arraySize;
} VkImageSubresourceRange;

typedef struct VkEventWaitInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_EVENT_WAIT_INFO
    const void*                                 pNext;                      // Pointer to next structure.

    uint32_t                                    eventCount;                 // Number of events to wait on
    const VkEvent*                              pEvents;                    // Array of event objects to wait on

    VkWaitEvent                                 waitEvent;                  // Pipeline event where the wait should happen

    uint32_t                                    memBarrierCount;            // Number of memory barriers
    const void**                                ppMemBarriers;              // Array of pointers to memory barriers (any of them can be either VkMemoryBarrier, VkBufferMemoryBarrier, or VkImageMemoryBarrier)
} VkEventWaitInfo;

typedef struct VkPipelineBarrier_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_PIPELINE_BARRIER
    const void*                                 pNext;                      // Pointer to next structure.

    uint32_t                                    eventCount;                 // Number of events to wait on
    const VkPipeEvent*                          pEvents;                    // Array of pipeline events to wait on

    VkWaitEvent                                 waitEvent;                  // Pipeline event where the wait should happen

    uint32_t                                    memBarrierCount;            // Number of memory barriers
    const void**                                ppMemBarriers;              // Array of pointers to memory barriers (any of them can be either VkMemoryBarrier, VkBufferMemoryBarrier, or VkImageMemoryBarrier)
} VkPipelineBarrier;

typedef struct VkMemoryBarrier_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_MEMORY_BARRIER
    const void*                                 pNext;                      // Pointer to next structure.

    VkFlags                                     outputMask;                 // Outputs the barrier should sync (see VkMemoryOutputFlags)
    VkFlags                                     inputMask;                  // Inputs the barrier should sync to (see VkMemoryInputFlags)
} VkMemoryBarrier;

typedef struct VkBufferMemoryBarrier_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER
    const void*                                 pNext;                      // Pointer to next structure.

    VkFlags                                     outputMask;                 // Outputs the barrier should sync (see VkMemoryOutputFlags)
    VkFlags                                     inputMask;                  // Inputs the barrier should sync to (see VkMemoryInputFlags)

    VkBuffer                                    buffer;                     // Buffer to sync

    VkGpuSize                                   offset;                     // Offset within the buffer to sync
    VkGpuSize                                   size;                       // Amount of bytes to sync
} VkBufferMemoryBarrier;

typedef struct VkImageMemoryBarrier_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER
    const void*                                 pNext;                      // Pointer to next structure.

    VkFlags                                     outputMask;                 // Outputs the barrier should sync (see VkMemoryOutputFlags)
    VkFlags                                     inputMask;                  // Inputs the barrier should sync to (see VkMemoryInputFlags)

    VkImageLayout                               oldLayout;                  // Current layout of the image
    VkImageLayout                               newLayout;                  // New layout to transition the image to

    VkImage                                     image;                      // Image to sync

    VkImageSubresourceRange                     subresourceRange;           // Subresource range to sync
} VkImageMemoryBarrier;

typedef struct VkImageCreateInfo_
{
    VkStructureType                             sType;                      // Must be VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO
    const void*                                 pNext;                      // Pointer to next structure.
    VkImageType                                 imageType;
    VkFormat                                    format;
    VkExtent3D                                  extent;
    uint32_t                                    mipLevels;
    uint32_t                                    arraySize;
    uint32_t                                    samples;
    VkImageTiling                               tiling;
    VkFlags                                     usage;                      // VkImageUsageFlags
    VkFlags                                     flags;                      // VkImageCreateFlags
} VkImageCreateInfo;

typedef struct VkPeerImageOpenInfo_
{
    VkImage                                     originalImage;
} VkPeerImageOpenInfo;

typedef struct VkSubresourceLayout_
{
    VkGpuSize                                   offset;                 // Specified in bytes
    VkGpuSize                                   size;                   // Specified in bytes
    VkGpuSize                                   rowPitch;               // Specified in bytes
    VkGpuSize                                   depthPitch;             // Specified in bytes
} VkSubresourceLayout;

typedef struct VkImageViewCreateInfo_
{
    VkStructureType                             sType;                  // Must be VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO
    const void*                                 pNext;                  // Pointer to next structure
    VkImage                                     image;
    VkImageViewType                             viewType;
    VkFormat                                    format;
    VkChannelMapping                            channels;
    VkImageSubresourceRange                     subresourceRange;
    float                                       minLod;
} VkImageViewCreateInfo;

typedef struct VkColorAttachmentViewCreateInfo_
{
    VkStructureType                             sType;                  // Must be VK_STRUCTURE_TYPE_COLOR_ATTACHMENT_VIEW_CREATE_INFO
    const void*                                 pNext;                  // Pointer to next structure
    VkImage                                     image;
    VkFormat                                    format;
    uint32_t                                    mipLevel;
    uint32_t                                    baseArraySlice;
    uint32_t                                    arraySize;
    VkImage                                     msaaResolveImage;
    VkImageSubresourceRange                     msaaResolveSubResource;
} VkColorAttachmentViewCreateInfo;

typedef struct VkDepthStencilViewCreateInfo_
{
    VkStructureType                             sType;                  // Must be VK_STRUCTURE_TYPE_DEPTH_STENCIL_VIEW_CREATE_INFO
    const void*                                 pNext;                  // Pointer to next structure
    VkImage                                     image;
    uint32_t                                    mipLevel;
    uint32_t                                    baseArraySlice;
    uint32_t                                    arraySize;
    VkImage                                     msaaResolveImage;
    VkImageSubresourceRange                     msaaResolveSubResource;
    VkFlags                                     flags;                  // VkDepthStencilViewCreateFlags
} VkDepthStencilViewCreateInfo;

typedef struct VkColorAttachmentBindInfo_
{
    VkColorAttachmentView                       view;
    VkImageLayout                               layout;
} VkColorAttachmentBindInfo;

typedef struct VkDepthStencilBindInfo_
{
    VkDepthStencilView                          view;
    VkImageLayout                               layout;
} VkDepthStencilBindInfo;

typedef struct VkBufferCopy_
{
    VkGpuSize                                   srcOffset;              // Specified in bytes
    VkGpuSize                                   destOffset;             // Specified in bytes
    VkGpuSize                                   copySize;               // Specified in bytes
} VkBufferCopy;

typedef struct VkImageMemoryBindInfo_
{
    VkImageSubresource                          subresource;
    VkOffset3D                                  offset;
    VkExtent3D                                  extent;
} VkImageMemoryBindInfo;

typedef struct VkImageCopy_
{
    VkImageSubresource                          srcSubresource;
    VkOffset3D                                  srcOffset;
    VkImageSubresource                          destSubresource;
    VkOffset3D                                  destOffset;
    VkExtent3D                                  extent;
} VkImageCopy;

typedef struct VkImageBlit_
{
    VkImageSubresource                          srcSubresource;
    VkOffset3D                                  srcOffset;
    VkExtent3D                                  srcExtent;
    VkImageSubresource                          destSubresource;
    VkOffset3D                                  destOffset;
    VkExtent3D                                  destExtent;
} VkImageBlit;

typedef struct VkBufferImageCopy_
{
    VkGpuSize                                 bufferOffset;           // Specified in bytes
    VkImageSubresource                        imageSubresource;
    VkOffset3D                                 imageOffset;           // Specified in pixels for both compressed and uncompressed images
    VkExtent3D                                 imageExtent;           // Specified in pixels for both compressed and uncompressed images
} VkBufferImageCopy;

typedef struct VkImageResolve_
{
    VkImageSubresource                        srcSubresource;
    VkOffset2D                                 srcOffset;
    VkImageSubresource                        destSubresource;
    VkOffset2D                                 destOffset;
    VkExtent2D                                 extent;
} VkImageResolve;

typedef struct VkShaderCreateInfo_
{
    VkStructureType                             sType;              // Must be VK_STRUCTURE_TYPE_SHADER_CREATE_INFO
    const void*                                 pNext;              // Pointer to next structure
    size_t                                      codeSize;           // Specified in bytes
    const void*                                 pCode;
    VkFlags                                    flags;              // Reserved
} VkShaderCreateInfo;

typedef struct VkDescriptorSetLayoutBinding_
{
    VkDescriptorType                          descriptorType;
    uint32_t                                    count;
    VkFlags                                    stageFlags;         // VkShaderStageFlags
    const VkSampler*                           pImmutableSamplers;
} VkDescriptorSetLayoutBinding;

typedef struct VkDescriptorSetLayoutCreateInfo_
{
    VkStructureType                             sType;             // Must be VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO
    const void*                                 pNext;             // Pointer to next structure
    uint32_t                                    count;             // Number of bindings in the descriptor set layout
    const VkDescriptorSetLayoutBinding*     pBinding;          // Array of descriptor set layout bindings
} VkDescriptorSetLayoutCreateInfo;

typedef struct VkDescriptorTypeCount_
{
    VkDescriptorType                          type;
    uint32_t                                    count;
} VkDescriptorTypeCount;

typedef struct VkDescriptorPoolCreateInfo_
{
    VkStructureType                             sType;              // Must be VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO
    const void*                                 pNext;              // Pointer to next structure
    uint32_t                                    count;
    const VkDescriptorTypeCount*             pTypeCount;
} VkDescriptorPoolCreateInfo;

typedef struct VkLinkConstBuffer_
{
    uint32_t                                    bufferId;
    size_t                                      bufferSize;
    const void*                                 pBufferData;
} VkLinkConstBuffer;

typedef struct VkSpecializationMapEntry_
{
    uint32_t                                    constantId;         // The SpecConstant ID specified in the BIL
    uint32_t                                    offset;             // Offset of the value in the data block
} VkSpecializationMapEntry;

typedef struct VkSpecializationInfo_
{
    uint32_t                                    mapEntryCount;
    const VkSpecializationMapEntry*          pMap;               // mapEntryCount entries
    const void*                                 pData;
} VkSpecializationInfo;

typedef struct VkPipelineShader_
{
    VkPipelineShaderStage                    stage;
    VkShader                                   shader;
    uint32_t                                    linkConstBufferCount;
    const VkLinkConstBuffer*                 pLinkConstBufferInfo;
    const VkSpecializationInfo*               pSpecializationInfo;
} VkPipelineShader;

typedef struct VkComputePipelineCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkPipelineShader                          cs;
    VkFlags                                    flags;      // VkPipelineCreateFlags
    VkDescriptorSetLayoutChain              setLayoutChain;
    uint32_t                                    localSizeX;
    uint32_t                                    localSizeY;
    uint32_t                                    localSizeZ;

} VkComputePipelineCreateInfo;

typedef struct VkVertexInputBindingDescription_
{
    uint32_t                                    binding;        // Vertex buffer binding id
    uint32_t                                    strideInBytes;  // Distance between vertices in bytes (0  = no advancement)

    VkVertexInputStepRate                   stepRate;       // Rate at which binding is incremented
} VkVertexInputBindingDescription;

typedef struct VkVertexInputAttributeDescription_
{
    uint32_t                                    location;       // location of the shader vertex attrib
    uint32_t                                    binding;        // Vertex buffer binding id

    VkFormat                                   format;         // format of source data

    uint32_t                                    offsetInBytes;  // Offset of first element in bytes from base of vertex
} VkVertexInputAttributeDescription;

typedef struct VkPipelineVertexInputCreateInfo_
{
    VkStructureType                             sType;          // Should be VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_CREATE_INFO
    const void*                                 pNext;          // Pointer to next structure

    uint32_t                                    bindingCount;   // number of bindings
    const VkVertexInputBindingDescription*  pVertexBindingDescriptions;

    uint32_t                                    attributeCount; // number of attributes
    const VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
} VkPipelineVertexInputCreateInfo;

typedef struct VkPipelineIaStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_IA_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkPrimitiveTopology                       topology;
    bool32_t                                    disableVertexReuse;         // optional
    bool32_t                                    primitiveRestartEnable;
    uint32_t                                    primitiveRestartIndex;      // optional (GL45)
} VkPipelineIaStateCreateInfo;

typedef struct VkPipelineTessStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_TESS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    patchControlPoints;
} VkPipelineTessStateCreateInfo;

typedef struct VkPipelineVpStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_VP_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    numViewports;
    VkCoordinateOrigin                        clipOrigin;                 // optional (GL45)
    VkDepthMode                               depthMode;                  // optional (GL45)
} VkPipelineVpStateCreateInfo;

typedef struct VkPipelineRsStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_RS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    bool32_t                                    depthClipEnable;
    bool32_t                                    rasterizerDiscardEnable;
    bool32_t                                    programPointSize;           // optional (GL45)
    VkCoordinateOrigin                        pointOrigin;                // optional (GL45)
    VkProvokingVertexConvention              provokingVertex;            // optional (GL45)
    VkFillMode                                fillMode;                   // optional (GL45)
    VkCullMode                                cullMode;
    VkFaceOrientation                         frontFace;
} VkPipelineRsStateCreateInfo;

typedef struct VkPipelineMsStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_MS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    samples;
    bool32_t                                    multisampleEnable;          // optional (GL45)
    bool32_t                                    sampleShadingEnable;        // optional (GL45)
    float                                       minSampleShading;           // optional (GL45)
    VkSampleMask                              sampleMask;
} VkPipelineMsStateCreateInfo;

typedef struct VkPipelineCbAttachmentState_
{
    bool32_t                                    blendEnable;
    VkFormat                                   format;
    VkBlend                                    srcBlendColor;
    VkBlend                                    destBlendColor;
    VkBlendFunc                               blendFuncColor;
    VkBlend                                    srcBlendAlpha;
    VkBlend                                    destBlendAlpha;
    VkBlendFunc                               blendFuncAlpha;
    uint8_t                                     channelWriteMask;
} VkPipelineCbAttachmentState;

typedef struct VkPipelineCbStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_CB_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    bool32_t                                    alphaToCoverageEnable;
    bool32_t                                    logicOpEnable;
    VkLogicOp                                 logicOp;
    uint32_t                                    attachmentCount;    // # of pAttachments
    const VkPipelineCbAttachmentState*      pAttachments;
} VkPipelineCbStateCreateInfo;

typedef struct VkStencilOpState_
{
    VkStencilOp                               stencilFailOp;
    VkStencilOp                               stencilPassOp;
    VkStencilOp                               stencilDepthFailOp;
    VkCompareFunc                             stencilFunc;
} VkStencilOpState;

typedef struct VkPipelineDsStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_DS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkFormat                                   format;
    bool32_t                                    depthTestEnable;
    bool32_t                                    depthWriteEnable;
    VkCompareFunc                             depthFunc;
    bool32_t                                    depthBoundsEnable;          // optional (depth_bounds_test)
    bool32_t                                    stencilTestEnable;
    VkStencilOpState                         front;
    VkStencilOpState                         back;
} VkPipelineDsStateCreateInfo;

typedef struct VkPipelineShaderStageCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkPipelineShader                          shader;
} VkPipelineShaderStageCreateInfo;

typedef struct VkGraphicsPipelineCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkFlags                                    flags;      // VkPipelineCreateFlags
    VkDescriptorSetLayoutChain              pSetLayoutChain;
} VkGraphicsPipelineCreateInfo;

typedef struct VkSamplerCreateInfo_
{
    VkStructureType                             sType;          // Must be VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO
    const void*                                 pNext;          // Pointer to next structure
    VkTexFilter                               magFilter;      // Filter mode for magnification
    VkTexFilter                               minFilter;      // Filter mode for minifiation
    VkTexMipmapMode                          mipMode;        // Mipmap selection mode
    VkTexAddress                              addressU;
    VkTexAddress                              addressV;
    VkTexAddress                              addressW;
    float                                       mipLodBias;
    uint32_t                                    maxAnisotropy;
    VkCompareFunc                             compareFunc;
    float                                       minLod;
    float                                       maxLod;
    VkBorderColorType                        borderColorType;
} VkSamplerCreateInfo;

typedef struct VkDynamicVpStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_DYNAMIC_VP_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    viewportAndScissorCount;  // number of entries in pViewports and pScissors
    const VkViewport*                          pViewports;
    const VkRect*                              pScissors;
} VkDynamicVpStateCreateInfo;

typedef struct VkDynamicRsStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_DYNAMIC_RS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    float                                       depthBias;
    float                                       depthBiasClamp;
    float                                       slopeScaledDepthBias;
    float                                       pointSize;          // optional (GL45) - Size of points
    float                                       pointFadeThreshold; // optional (GL45) - Size of point fade threshold
    float                                       lineWidth;          // optional (GL45) - Width of lines
} VkDynamicRsStateCreateInfo;

typedef struct VkDynamicCbStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_DYNAMIC_CB_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    float                                       blendConst[4];
} VkDynamicCbStateCreateInfo;

typedef struct VkDynamicDsStateCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_DYNAMIC_DS_STATE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    float                                       minDepth;               // optional (depth_bounds_test)
    float                                       maxDepth;               // optional (depth_bounds_test)
    uint32_t                                    stencilReadMask;
    uint32_t                                    stencilWriteMask;
    uint32_t                                    stencilFrontRef;
    uint32_t                                    stencilBackRef;
} VkDynamicDsStateCreateInfo;

typedef struct VkCmdBufferCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_CMD_BUFFER_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    queueNodeIndex;
    VkFlags                                    flags;
} VkCmdBufferCreateInfo;

typedef struct VkCmdBufferBeginInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_CMD_BUFFER_BEGIN_INFO
    const void*                                 pNext;      // Pointer to next structure

    VkFlags                                    flags;      // VkCmdBufferBuildFlags
} VkCmdBufferBeginInfo;

typedef struct VkRenderPassBegin_
{
    VkRenderPass                              renderPass;
    VkFramebuffer                              framebuffer;
} VkRenderPassBegin;

typedef struct VkCmdBufferGraphicsBeginInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_CMD_BUFFER_GRAPHICS_BEGIN_INFO
    const void*                                 pNext;      // Pointer to next structure

    VkRenderPassBegin                        renderPassContinue;  // Only needed when a render pass is split across two command buffers
} VkCmdBufferGraphicsBeginInfo;

// Union allowing specification of floating point or raw color data. Actual value selected is based on image being cleared.
typedef union VkClearColorValue_
{
    float                                       floatColor[4];
    uint32_t                                    rawColor[4];
} VkClearColorValue;

typedef struct VkClearColor_
{
    VkClearColorValue                        color;
    bool32_t                                    useRawValue;
} VkClearColor;

typedef struct VkRenderPassCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure

    VkRect                                     renderArea;
    uint32_t                                    colorAttachmentCount;
    VkExtent2D                                 extent;
    uint32_t                                    sampleCount;
    uint32_t                                    layers;
    const VkFormat*                            pColorFormats;
    const VkImageLayout*                      pColorLayouts;
    const VkAttachmentLoadOp*                pColorLoadOps;
    const VkAttachmentStoreOp*               pColorStoreOps;
    const VkClearColor*                       pColorLoadClearValues;
    VkFormat                                   depthStencilFormat;
    VkImageLayout                             depthStencilLayout;
    VkAttachmentLoadOp                       depthLoadOp;
    float                                       depthLoadClearValue;
    VkAttachmentStoreOp                      depthStoreOp;
    VkAttachmentLoadOp                       stencilLoadOp;
    uint32_t                                    stencilLoadClearValue;
    VkAttachmentStoreOp                      stencilStoreOp;
} VkRenderPassCreateInfo;

typedef struct VkEventCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_EVENT_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkFlags                                    flags;      // Reserved
} VkEventCreateInfo;

typedef struct VkFenceCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_FENCE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkFenceCreateFlags                       flags;      // VkFenceCreateFlags
} VkFenceCreateInfo;

typedef struct VkSemaphoreCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    uint32_t                                    initialCount;
    VkFlags                                    flags;      // VkSemaphoreCreateFlags
} VkSemaphoreCreateInfo;

typedef struct VkSemaphoreOpenInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_SEMAPHORE_OPEN_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkSemaphore                                sharedSemaphore;
} VkSemaphoreOpenInfo;

typedef struct VkPipelineStatisticsData_
{
    uint64_t                                    fsInvocations;            // Fragment shader invocations
    uint64_t                                    cPrimitives;              // Clipper primitives
    uint64_t                                    cInvocations;             // Clipper invocations
    uint64_t                                    vsInvocations;            // Vertex shader invocations
    uint64_t                                    gsInvocations;            // Geometry shader invocations
    uint64_t                                    gsPrimitives;             // Geometry shader primitives
    uint64_t                                    iaPrimitives;             // Input primitives
    uint64_t                                    iaVertices;               // Input vertices
    uint64_t                                    tcsInvocations;           // Tessellation control shader invocations
    uint64_t                                    tesInvocations;           // Tessellation evaluation shader invocations
    uint64_t                                    csInvocations;            // Compute shader invocations
} VkPipelineStatisticsData;

typedef struct VkQueryPoolCreateInfo_
{
    VkStructureType                             sType;      // Must be VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO
    const void*                                 pNext;      // Pointer to next structure
    VkQueryType                               queryType;
    uint32_t                                    slots;
} VkQueryPoolCreateInfo;

typedef struct VkFramebufferCreateInfo_
{
    VkStructureType                             sType;  // Must be VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO
    const void*                                 pNext;  // Pointer to next structure

    uint32_t                                    colorAttachmentCount;
    const VkColorAttachmentBindInfo*        pColorAttachments;
    const VkDepthStencilBindInfo*           pDepthStencilAttachment;

    uint32_t                                    sampleCount;
    uint32_t                                    width;
    uint32_t                                    height;
    uint32_t                                    layers;
} VkFramebufferCreateInfo;

typedef struct VkDrawIndirectCmd_
{
    uint32_t                                    vertexCount;
    uint32_t                                    instanceCount;
    uint32_t                                    firstVertex;
    uint32_t                                    firstInstance;
} VkDrawIndirectCmd;

typedef struct VkDrawIndexedIndirectCmd_
{
    uint32_t                                    indexCount;
    uint32_t                                    instanceCount;
    uint32_t                                    firstIndex;
    int32_t                                     vertexOffset;
    uint32_t                                    firstInstance;
} VkDrawIndexedIndirectCmd;

typedef struct VkDispatchIndirectCmd_
{
    uint32_t                                    x;
    uint32_t                                    y;
    uint32_t                                    z;
} VkDispatchIndirectCmd;

// ------------------------------------------------------------------------------------------------
// API functions
typedef VkResult (VKAPI *PFN_vkCreateInstance)(const VkInstanceCreateInfo* pCreateInfo, VkInstance* pInstance);
typedef VkResult (VKAPI *PFN_vkDestroyInstance)(VkInstance instance);
typedef VkResult (VKAPI *PFN_vkEnumerateGpus)(VkInstance instance, uint32_t maxGpus, uint32_t* pGpuCount, VkPhysicalGpu* pGpus);
typedef VkResult (VKAPI *PFN_vkGetGpuInfo)(VkPhysicalGpu gpu, VkPhysicalGpuInfoType infoType, size_t* pDataSize, void* pData);
typedef void *    (VKAPI *PFN_vkGetProcAddr)(VkPhysicalGpu gpu, const char * pName);
typedef VkResult (VKAPI *PFN_vkCreateDevice)(VkPhysicalGpu gpu, const VkDeviceCreateInfo* pCreateInfo, VkDevice* pDevice);
typedef VkResult (VKAPI *PFN_vkDestroyDevice)(VkDevice device);
typedef VkResult (VKAPI *PFN_vkGetExtensionSupport)(VkPhysicalGpu gpu, const char* pExtName);
typedef VkResult (VKAPI *PFN_vkEnumerateLayers)(VkPhysicalGpu gpu, size_t maxLayerCount, size_t maxStringSize, size_t* pOutLayerCount, char* const* pOutLayers, void* pReserved);
typedef VkResult (VKAPI *PFN_vkGetDeviceQueue)(VkDevice device, uint32_t queueNodeIndex, uint32_t queueIndex, VkQueue* pQueue);
typedef VkResult (VKAPI *PFN_vkQueueSubmit)(VkQueue queue, uint32_t cmdBufferCount, const VkCmdBuffer* pCmdBuffers, VkFence fence);
typedef VkResult (VKAPI *PFN_vkQueueAddMemReference)(VkQueue queue, VkGpuMemory mem);
typedef VkResult (VKAPI *PFN_vkQueueRemoveMemReference)(VkQueue queue, VkGpuMemory mem);
typedef VkResult (VKAPI *PFN_vkQueueWaitIdle)(VkQueue queue);
typedef VkResult (VKAPI *PFN_vkDeviceWaitIdle)(VkDevice device);
typedef VkResult (VKAPI *PFN_vkAllocMemory)(VkDevice device, const VkMemoryAllocInfo* pAllocInfo, VkGpuMemory* pMem);
typedef VkResult (VKAPI *PFN_vkFreeMemory)(VkGpuMemory mem);
typedef VkResult (VKAPI *PFN_vkSetMemoryPriority)(VkGpuMemory mem, VkMemoryPriority priority);
typedef VkResult (VKAPI *PFN_vkMapMemory)(VkGpuMemory mem, VkFlags flags, void** ppData);
typedef VkResult (VKAPI *PFN_vkUnmapMemory)(VkGpuMemory mem);
typedef VkResult (VKAPI *PFN_vkPinSystemMemory)(VkDevice device, const void* pSysMem, size_t memSize, VkGpuMemory* pMem);
typedef VkResult (VKAPI *PFN_vkGetMultiGpuCompatibility)(VkPhysicalGpu gpu0, VkPhysicalGpu gpu1, VkGpuCompatibilityInfo* pInfo);
typedef VkResult (VKAPI *PFN_vkOpenSharedMemory)(VkDevice device, const VkMemoryOpenInfo* pOpenInfo, VkGpuMemory* pMem);
typedef VkResult (VKAPI *PFN_vkOpenSharedSemaphore)(VkDevice device, const VkSemaphoreOpenInfo* pOpenInfo, VkSemaphore* pSemaphore);
typedef VkResult (VKAPI *PFN_vkOpenPeerMemory)(VkDevice device, const VkPeerMemoryOpenInfo* pOpenInfo, VkGpuMemory* pMem);
typedef VkResult (VKAPI *PFN_vkOpenPeerImage)(VkDevice device, const VkPeerImageOpenInfo* pOpenInfo, VkImage* pImage, VkGpuMemory* pMem);
typedef VkResult (VKAPI *PFN_vkDestroyObject)(VkObject object);
typedef VkResult (VKAPI *PFN_vkGetObjectInfo)(VkBaseObject object, VkObjectInfoType infoType, size_t* pDataSize, void* pData);
typedef VkResult (VKAPI *PFN_vkBindObjectMemory)(VkObject object, uint32_t allocationIdx, VkGpuMemory mem, VkGpuSize offset);
typedef VkResult (VKAPI *PFN_vkBindObjectMemoryRange)(VkObject object, uint32_t allocationIdx, VkGpuSize rangeOffset,VkGpuSize rangeSize, VkGpuMemory mem, VkGpuSize memOffset);
typedef VkResult (VKAPI *PFN_vkBindImageMemoryRange)(VkImage image, uint32_t allocationIdx, const VkImageMemoryBindInfo* bindInfo, VkGpuMemory mem, VkGpuSize memOffset);
typedef VkResult (VKAPI *PFN_vkCreateFence)(VkDevice device, const VkFenceCreateInfo* pCreateInfo, VkFence* pFence);
typedef VkResult (VKAPI *PFN_vkResetFences)(VkDevice device, uint32_t fenceCount, VkFence* pFences);
typedef VkResult (VKAPI *PFN_vkGetFenceStatus)(VkFence fence);
typedef VkResult (VKAPI *PFN_vkWaitForFences)(VkDevice device, uint32_t fenceCount, const VkFence* pFences, bool32_t waitAll, uint64_t timeout);
typedef VkResult (VKAPI *PFN_vkCreateSemaphore)(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, VkSemaphore* pSemaphore);
typedef VkResult (VKAPI *PFN_vkQueueSignalSemaphore)(VkQueue queue, VkSemaphore semaphore);
typedef VkResult (VKAPI *PFN_vkQueueWaitSemaphore)(VkQueue queue, VkSemaphore semaphore);
typedef VkResult (VKAPI *PFN_vkCreateEvent)(VkDevice device, const VkEventCreateInfo* pCreateInfo, VkEvent* pEvent);
typedef VkResult (VKAPI *PFN_vkGetEventStatus)(VkEvent event);
typedef VkResult (VKAPI *PFN_vkSetEvent)(VkEvent event);
typedef VkResult (VKAPI *PFN_vkResetEvent)(VkEvent event);
typedef VkResult (VKAPI *PFN_vkCreateQueryPool)(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, VkQueryPool* pQueryPool);
typedef VkResult (VKAPI *PFN_vkGetQueryPoolResults)(VkQueryPool queryPool, uint32_t startQuery, uint32_t queryCount, size_t* pDataSize, void* pData);
typedef VkResult (VKAPI *PFN_vkGetFormatInfo)(VkDevice device, VkFormat format, VkFormatInfoType infoType, size_t* pDataSize, void* pData);
typedef VkResult (VKAPI *PFN_vkCreateBuffer)(VkDevice device, const VkBufferCreateInfo* pCreateInfo, VkBuffer* pBuffer);
typedef VkResult (VKAPI *PFN_vkCreateBufferView)(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, VkBufferView* pView);
typedef VkResult (VKAPI *PFN_vkCreateImage)(VkDevice device, const VkImageCreateInfo* pCreateInfo, VkImage* pImage);
typedef VkResult (VKAPI *PFN_vkGetImageSubresourceInfo)(VkImage image, const VkImageSubresource* pSubresource, VkSubresourceInfoType infoType, size_t* pDataSize, void* pData);
typedef VkResult (VKAPI *PFN_vkCreateImageView)(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, VkImageView* pView);
typedef VkResult (VKAPI *PFN_vkCreateColorAttachmentView)(VkDevice device, const VkColorAttachmentViewCreateInfo* pCreateInfo, VkColorAttachmentView* pView);
typedef VkResult (VKAPI *PFN_vkCreateDepthStencilView)(VkDevice device, const VkDepthStencilViewCreateInfo* pCreateInfo, VkDepthStencilView* pView);
typedef VkResult (VKAPI *PFN_vkCreateShader)(VkDevice device, const VkShaderCreateInfo* pCreateInfo, VkShader* pShader);
typedef VkResult (VKAPI *PFN_vkCreateGraphicsPipeline)(VkDevice device, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipeline);
typedef VkResult (VKAPI *PFN_vkCreateGraphicsPipelineDerivative)(VkDevice device, const VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline basePipeline, VkPipeline* pPipeline);
typedef VkResult (VKAPI *PFN_vkCreateComputePipeline)(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, VkPipeline* pPipeline);
typedef VkResult (VKAPI *PFN_vkStorePipeline)(VkPipeline pipeline, size_t* pDataSize, void* pData);
typedef VkResult (VKAPI *PFN_vkLoadPipeline)(VkDevice device, size_t dataSize, const void* pData, VkPipeline* pPipeline);
typedef VkResult (VKAPI *PFN_vkLoadPipelineDerivative)(VkDevice device, size_t dataSize, const void* pData, VkPipeline basePipeline, VkPipeline* pPipeline);
typedef VkResult (VKAPI *PFN_vkCreateSampler)(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, VkSampler* pSampler);
typedef VkResult (VKAPI *PFN_vkCreateDescriptorSetLayout)(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayout* pSetLayout);
typedef VkResult (VKAPI *PFN_vkCreateDescriptorSetLayoutChain)(VkDevice device, uint32_t setLayoutArrayCount, const VkDescriptorSetLayout* pSetLayoutArray, VkDescriptorSetLayoutChain* pLayoutChain);
typedef VkResult (VKAPI *PFN_vkBeginDescriptorPoolUpdate)(VkDevice device, VkDescriptorUpdateMode updateMode);
typedef VkResult (VKAPI *PFN_vkEndDescriptorPoolUpdate)(VkDevice device, VkCmdBuffer cmd);
typedef VkResult (VKAPI *PFN_vkCreateDescriptorPool)(VkDevice device, VkDescriptorPoolUsage poolUsage, uint32_t maxSets, const VkDescriptorPoolCreateInfo* pCreateInfo, VkDescriptorPool* pDescriptorPool);
typedef VkResult (VKAPI *PFN_vkResetDescriptorPool)(VkDescriptorPool descriptorPool);
typedef VkResult (VKAPI *PFN_vkAllocDescriptorSets)(VkDescriptorPool descriptorPool, VkDescriptorSetUsage setUsage, uint32_t count, const VkDescriptorSetLayout* pSetLayouts, VkDescriptorSet* pDescriptorSets, uint32_t* pCount);
typedef void      (VKAPI *PFN_vkClearDescriptorSets)(VkDescriptorPool descriptorPool, uint32_t count, const VkDescriptorSet* pDescriptorSets);
typedef void      (VKAPI *PFN_vkUpdateDescriptors)(VkDescriptorSet descriptorSet, uint32_t updateCount, const void** pUpdateArray);
typedef VkResult (VKAPI *PFN_vkCreateDynamicViewportState)(VkDevice device, const VkDynamicVpStateCreateInfo* pCreateInfo, VkDynamicVpState* pState);
typedef VkResult (VKAPI *PFN_vkCreateDynamicRasterState)(VkDevice device, const VkDynamicRsStateCreateInfo* pCreateInfo, VkDynamicRsState* pState);
typedef VkResult (VKAPI *PFN_vkCreateDynamicColorBlendState)(VkDevice device, const VkDynamicCbStateCreateInfo* pCreateInfo, VkDynamicCbState* pState);
typedef VkResult (VKAPI *PFN_vkCreateDynamicDepthStencilState)(VkDevice device, const VkDynamicDsStateCreateInfo* pCreateInfo, VkDynamicDsState* pState);
typedef VkResult (VKAPI *PFN_vkCreateCommandBuffer)(VkDevice device, const VkCmdBufferCreateInfo* pCreateInfo, VkCmdBuffer* pCmdBuffer);
typedef VkResult (VKAPI *PFN_vkBeginCommandBuffer)(VkCmdBuffer cmdBuffer, const VkCmdBufferBeginInfo* pBeginInfo);
typedef VkResult (VKAPI *PFN_vkEndCommandBuffer)(VkCmdBuffer cmdBuffer);
typedef VkResult (VKAPI *PFN_vkResetCommandBuffer)(VkCmdBuffer cmdBuffer);
typedef void      (VKAPI *PFN_vkCmdBindPipeline)(VkCmdBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);
typedef void      (VKAPI *PFN_vkCmdBindDynamicStateObject)(VkCmdBuffer cmdBuffer, VkStateBindPoint stateBindPoint, VkDynamicStateObject state);
typedef void      (VKAPI *PFN_vkCmdBindDescriptorSets)(VkCmdBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkDescriptorSetLayoutChain layoutChain, uint32_t layoutChainSlot, uint32_t count, const VkDescriptorSet* pDescriptorSets, const uint32_t* pUserData);
typedef void      (VKAPI *PFN_vkCmdBindIndexBuffer)(VkCmdBuffer cmdBuffer, VkBuffer buffer, VkGpuSize offset, VkIndexType indexType);
typedef void      (VKAPI *PFN_vkCmdBindVertexBuffer)(VkCmdBuffer cmdBuffer, VkBuffer buffer, VkGpuSize offset, uint32_t binding);
typedef void      (VKAPI *PFN_vkCmdDraw)(VkCmdBuffer cmdBuffer, uint32_t firstVertex, uint32_t vertexCount, uint32_t firstInstance, uint32_t instanceCount);
typedef void      (VKAPI *PFN_vkCmdDrawIndexed)(VkCmdBuffer cmdBuffer, uint32_t firstIndex, uint32_t indexCount, int32_t vertexOffset, uint32_t firstInstance, uint32_t instanceCount);
typedef void      (VKAPI *PFN_vkCmdDrawIndirect)(VkCmdBuffer cmdBuffer, VkBuffer buffer, VkGpuSize offset, uint32_t count, uint32_t stride);
typedef void      (VKAPI *PFN_vkCmdDrawIndexedIndirect)(VkCmdBuffer cmdBuffer, VkBuffer buffer, VkGpuSize offset, uint32_t count, uint32_t stride);
typedef void      (VKAPI *PFN_vkCmdDispatch)(VkCmdBuffer cmdBuffer, uint32_t x, uint32_t y, uint32_t z);
typedef void      (VKAPI *PFN_vkCmdDispatchIndirect)(VkCmdBuffer cmdBuffer, VkBuffer buffer, VkGpuSize offset);
typedef void      (VKAPI *PFN_vkCmdCopyBuffer)(VkCmdBuffer cmdBuffer, VkBuffer srcBuffer, VkBuffer destBuffer, uint32_t regionCount, const VkBufferCopy* pRegions);
typedef void      (VKAPI *PFN_vkCmdCopyImage)(VkCmdBuffer cmdBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage destImage, VkImageLayout destImageLayout, uint32_t regionCount, const VkImageCopy* pRegions);
typedef void      (VKAPI *PFN_vkCmdBlitImage)(VkCmdBuffer cmdBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage destImage, VkImageLayout destImageLayout, uint32_t regionCount, const VkImageBlit* pRegions);
typedef void      (VKAPI *PFN_vkCmdCopyBufferToImage)(VkCmdBuffer cmdBuffer, VkBuffer srcBuffer, VkImage destImage, VkImageLayout destImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions);
typedef void      (VKAPI *PFN_vkCmdCopyImageToBuffer)(VkCmdBuffer cmdBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer destBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions);
typedef void      (VKAPI *PFN_vkCmdCloneImageData)(VkCmdBuffer cmdBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage destImage, VkImageLayout destImageLayout);
typedef void      (VKAPI *PFN_vkCmdUpdateBuffer)(VkCmdBuffer cmdBuffer, VkBuffer destBuffer, VkGpuSize destOffset, VkGpuSize dataSize, const uint32_t* pData);
typedef void      (VKAPI *PFN_vkCmdFillBuffer)(VkCmdBuffer cmdBuffer, VkBuffer destBuffer, VkGpuSize destOffset, VkGpuSize fillSize, uint32_t data);
typedef void      (VKAPI *PFN_vkCmdClearColorImage)(VkCmdBuffer cmdBuffer, VkImage image, VkImageLayout imageLayout, VkClearColor color, uint32_t rangeCount, const VkImageSubresourceRange* pRanges);
typedef void      (VKAPI *PFN_vkCmdClearDepthStencil)(VkCmdBuffer cmdBuffer, VkImage image, VkImageLayout imageLayout, float depth, uint32_t stencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges);
typedef void      (VKAPI *PFN_vkCmdResolveImage)(VkCmdBuffer cmdBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage destImage, VkImageLayout destImageLayout, uint32_t rectCount, const VkImageResolve* pRects);
typedef void      (VKAPI *PFN_vkCmdSetEvent)(VkCmdBuffer cmdBuffer, VkEvent event, VkPipeEvent pipeEvent);
typedef void      (VKAPI *PFN_vkCmdResetEvent)(VkCmdBuffer cmdBuffer, VkEvent event, VkPipeEvent pipeEvent);
typedef void      (VKAPI *PFN_vkCmdWaitEvents)(VkCmdBuffer cmdBuffer, const VkEventWaitInfo* pWaitInfo);
typedef void      (VKAPI *PFN_vkCmdPipelineBarrier)(VkCmdBuffer cmdBuffer, const VkPipelineBarrier* pBarrier);
typedef void      (VKAPI *PFN_vkCmdBeginQuery)(VkCmdBuffer cmdBuffer, VkQueryPool queryPool, uint32_t slot, VkFlags flags);
typedef void      (VKAPI *PFN_vkCmdEndQuery)(VkCmdBuffer cmdBuffer, VkQueryPool queryPool, uint32_t slot);
typedef void      (VKAPI *PFN_vkCmdResetQueryPool)(VkCmdBuffer cmdBuffer, VkQueryPool queryPool, uint32_t startQuery, uint32_t queryCount);
typedef void      (VKAPI *PFN_vkCmdWriteTimestamp)(VkCmdBuffer cmdBuffer, VkTimestampType timestampType, VkBuffer destBuffer, VkGpuSize destOffset);
typedef void      (VKAPI *PFN_vkCmdInitAtomicCounters)(VkCmdBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, uint32_t startCounter, uint32_t counterCount, const uint32_t* pData);
typedef void      (VKAPI *PFN_vkCmdLoadAtomicCounters)(VkCmdBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, uint32_t startCounter, uint32_t counterCount, VkBuffer srcBuffer, VkGpuSize srcOffset);
typedef void      (VKAPI *PFN_vkCmdSaveAtomicCounters)(VkCmdBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, uint32_t startCounter, uint32_t counterCount, VkBuffer destBuffer, VkGpuSize destOffset);
typedef VkResult (VKAPI *PFN_vkCreateFramebuffer)(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, VkFramebuffer* pFramebuffer);
typedef VkResult (VKAPI *PFN_vkCreateRenderPass)(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, VkRenderPass* pRenderPass);
typedef void      (VKAPI *PFN_vkCmdBeginRenderPass)(VkCmdBuffer cmdBuffer, const VkRenderPassBegin* pRenderPassBegin);
typedef void      (VKAPI *PFN_vkCmdEndRenderPass)(VkCmdBuffer cmdBuffer, VkRenderPass renderPass);

#ifdef VK_PROTOTYPES

// GPU initialization

VkResult VKAPI vkCreateInstance(
    const VkInstanceCreateInfo*             pCreateInfo,
    VkInstance*                               pInstance);

VkResult VKAPI vkDestroyInstance(
    VkInstance                                 instance);

VkResult VKAPI vkEnumerateGpus(
    VkInstance                                 instance,
    uint32_t                                    maxGpus,
    uint32_t*                                   pGpuCount,
    VkPhysicalGpu*                            pGpus);

VkResult VKAPI vkGetGpuInfo(
    VkPhysicalGpu                             gpu,
    VkPhysicalGpuInfoType                   infoType,
    size_t*                                     pDataSize,
    void*                                       pData);

void * VKAPI vkGetProcAddr(
    VkPhysicalGpu                             gpu,
    const char*                                 pName);

// Device functions

VkResult VKAPI vkCreateDevice(
    VkPhysicalGpu                             gpu,
    const VkDeviceCreateInfo*                pCreateInfo,
    VkDevice*                                  pDevice);

VkResult VKAPI vkDestroyDevice(
    VkDevice                                   device);

// Extension discovery functions

VkResult VKAPI vkGetExtensionSupport(
    VkPhysicalGpu                             gpu,
    const char*                                 pExtName);

// Layer discovery functions

VkResult VKAPI vkEnumerateLayers(
    VkPhysicalGpu                             gpu,
    size_t                                      maxLayerCount,
    size_t                                      maxStringSize,
    size_t*                                     pOutLayerCount,
    char* const*                                pOutLayers,
    void*                                       pReserved);

// Queue functions

VkResult VKAPI vkGetDeviceQueue(
    VkDevice                                   device,
    uint32_t                                    queueNodeIndex,
    uint32_t                                    queueIndex,
    VkQueue*                                   pQueue);

VkResult VKAPI vkQueueSubmit(
    VkQueue                                    queue,
    uint32_t                                    cmdBufferCount,
    const VkCmdBuffer*                        pCmdBuffers,
    VkFence                                    fence);

VkResult VKAPI vkQueueAddMemReference(
    VkQueue                                    queue,
    VkGpuMemory                               mem);

VkResult VKAPI vkQueueRemoveMemReference(
    VkQueue                                    queue,
    VkGpuMemory                               mem);

VkResult VKAPI vkQueueWaitIdle(
    VkQueue                                    queue);

VkResult VKAPI vkDeviceWaitIdle(
    VkDevice                                   device);

// Memory functions

VkResult VKAPI vkAllocMemory(
    VkDevice                                   device,
    const VkMemoryAllocInfo*                 pAllocInfo,
    VkGpuMemory*                              pMem);

VkResult VKAPI vkFreeMemory(
    VkGpuMemory                               mem);

VkResult VKAPI vkSetMemoryPriority(
    VkGpuMemory                               mem,
    VkMemoryPriority                          priority);

VkResult VKAPI vkMapMemory(
    VkGpuMemory                               mem,
    VkFlags                                    flags,                // Reserved
    void**                                      ppData);

VkResult VKAPI vkUnmapMemory(
    VkGpuMemory                               mem);

VkResult VKAPI vkPinSystemMemory(
    VkDevice                                   device,
    const void*                                 pSysMem,
    size_t                                      memSize,
    VkGpuMemory*                              pMem);

// Multi-device functions

VkResult VKAPI vkGetMultiGpuCompatibility(
    VkPhysicalGpu                             gpu0,
    VkPhysicalGpu                             gpu1,
    VkGpuCompatibilityInfo*                  pInfo);

VkResult VKAPI vkOpenSharedMemory(
    VkDevice                                   device,
    const VkMemoryOpenInfo*                  pOpenInfo,
    VkGpuMemory*                              pMem);

VkResult VKAPI vkOpenSharedSemaphore(
    VkDevice                                   device,
    const VkSemaphoreOpenInfo*               pOpenInfo,
    VkSemaphore*                               pSemaphore);

VkResult VKAPI vkOpenPeerMemory(
    VkDevice                                    device,
    const VkPeerMemoryOpenInfo*                 pOpenInfo,
    VkGpuMemory*                                pMem);

VkResult VKAPI vkOpenPeerImage(
    VkDevice                                   device,
    const VkPeerImageOpenInfo*              pOpenInfo,
    VkImage*                                   pImage,
    VkGpuMemory*                              pMem);

// Generic API object functions

VkResult VKAPI vkDestroyObject(
    VkObject                                   object);

VkResult VKAPI vkGetObjectInfo(
    VkBaseObject                              object,
    VkObjectInfoType                         infoType,
    size_t*                                     pDataSize,
    void*                                       pData);

VkResult VKAPI vkBindObjectMemory(
    VkObject                                   object,
    uint32_t                                    allocationIdx,
    VkGpuMemory                               mem,
    VkGpuSize                                 memOffset);

VkResult VKAPI vkBindObjectMemoryRange(
    VkObject                                   object,
    uint32_t                                    allocationIdx,
    VkGpuSize                                 rangeOffset,
    VkGpuSize                                 rangeSize,
    VkGpuMemory                               mem,
    VkGpuSize                                 memOffset);

VkResult VKAPI vkBindImageMemoryRange(
    VkImage                                    image,
    uint32_t                                    allocationIdx,
    const VkImageMemoryBindInfo*            bindInfo,
    VkGpuMemory                               mem,
    VkGpuSize                                 memOffset);

// Fence functions

VkResult VKAPI vkCreateFence(
    VkDevice                                   device,
    const VkFenceCreateInfo*                 pCreateInfo,
    VkFence*                                   pFence);

VkResult VKAPI vkResetFences(
    VkDevice                                   device,
    uint32_t                                    fenceCount,
    VkFence*                                   pFences);

VkResult VKAPI vkGetFenceStatus(
    VkFence fence);

VkResult VKAPI vkWaitForFences(
    VkDevice                                   device,
    uint32_t                                    fenceCount,
    const VkFence*                             pFences,
    bool32_t                                    waitAll,
    uint64_t                                    timeout); // timeout in nanoseconds

// Queue semaphore functions

VkResult VKAPI vkCreateSemaphore(
    VkDevice                                   device,
    const VkSemaphoreCreateInfo*             pCreateInfo,
    VkSemaphore*                               pSemaphore);

VkResult VKAPI vkQueueSignalSemaphore(
    VkQueue                                    queue,
    VkSemaphore                                semaphore);

VkResult VKAPI vkQueueWaitSemaphore(
    VkQueue                                    queue,
    VkSemaphore                                semaphore);

// Event functions

VkResult VKAPI vkCreateEvent(
    VkDevice                                   device,
    const VkEventCreateInfo*                 pCreateInfo,
    VkEvent*                                   pEvent);

VkResult VKAPI vkGetEventStatus(
    VkEvent                                    event);

VkResult VKAPI vkSetEvent(
    VkEvent                                    event);

VkResult VKAPI vkResetEvent(
    VkEvent                                    event);

// Query functions

VkResult VKAPI vkCreateQueryPool(
    VkDevice                                   device,
    const VkQueryPoolCreateInfo*            pCreateInfo,
    VkQueryPool*                              pQueryPool);

VkResult VKAPI vkGetQueryPoolResults(
    VkQueryPool                               queryPool,
    uint32_t                                    startQuery,
    uint32_t                                    queryCount,
    size_t*                                     pDataSize,
    void*                                       pData);

// Format capabilities

VkResult VKAPI vkGetFormatInfo(
    VkDevice                                   device,
    VkFormat                                   format,
    VkFormatInfoType                         infoType,
    size_t*                                     pDataSize,
    void*                                       pData);

// Buffer functions

VkResult VKAPI vkCreateBuffer(
    VkDevice                                   device,
    const VkBufferCreateInfo*                pCreateInfo,
    VkBuffer*                                  pBuffer);

// Buffer view functions

VkResult VKAPI vkCreateBufferView(
    VkDevice                                   device,
    const VkBufferViewCreateInfo*           pCreateInfo,
    VkBufferView*                             pView);

// Image functions

VkResult VKAPI vkCreateImage(
    VkDevice                                   device,
    const VkImageCreateInfo*                 pCreateInfo,
    VkImage*                                   pImage);

VkResult VKAPI vkGetImageSubresourceInfo(
    VkImage                                    image,
    const VkImageSubresource*                 pSubresource,
    VkSubresourceInfoType                    infoType,
    size_t*                                     pDataSize,
    void*                                       pData);

// Image view functions

VkResult VKAPI vkCreateImageView(
    VkDevice                                   device,
    const VkImageViewCreateInfo*            pCreateInfo,
    VkImageView*                              pView);

VkResult VKAPI vkCreateColorAttachmentView(
    VkDevice                                   device,
    const VkColorAttachmentViewCreateInfo* pCreateInfo,
    VkColorAttachmentView*                   pView);

VkResult VKAPI vkCreateDepthStencilView(
    VkDevice                                   device,
    const VkDepthStencilViewCreateInfo*    pCreateInfo,
    VkDepthStencilView*                      pView);

// Shader functions

VkResult VKAPI vkCreateShader(
    VkDevice                                   device,
    const VkShaderCreateInfo*                pCreateInfo,
    VkShader*                                  pShader);

// Pipeline functions

VkResult VKAPI vkCreateGraphicsPipeline(
    VkDevice                                   device,
    const VkGraphicsPipelineCreateInfo*     pCreateInfo,
    VkPipeline*                                pPipeline);

VkResult VKAPI vkCreateGraphicsPipelineDerivative(
    VkDevice                                   device,
    const VkGraphicsPipelineCreateInfo*     pCreateInfo,
    VkPipeline                                 basePipeline,
    VkPipeline*                                pPipeline);

VkResult VKAPI vkCreateComputePipeline(
    VkDevice                                   device,
    const VkComputePipelineCreateInfo*      pCreateInfo,
    VkPipeline*                                pPipeline);

VkResult VKAPI vkStorePipeline(
    VkPipeline                                 pipeline,
    size_t*                                     pDataSize,
    void*                                       pData);

VkResult VKAPI vkLoadPipeline(
    VkDevice                                   device,
    size_t                                      dataSize,
    const void*                                 pData,
    VkPipeline*                                pPipeline);

VkResult VKAPI vkLoadPipelineDerivative(
    VkDevice                                   device,
    size_t                                      dataSize,
    const void*                                 pData,
    VkPipeline                                 basePipeline,
    VkPipeline*                                pPipeline);

// Sampler functions

VkResult VKAPI vkCreateSampler(
    VkDevice                                   device,
    const VkSamplerCreateInfo*               pCreateInfo,
    VkSampler*                                 pSampler);

// Descriptor set functions

VkResult VKAPI vkCreateDescriptorSetLayout(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*  pCreateInfo,
    VkDescriptorSetLayout*                    pSetLayout);

VkResult VKAPI vkCreateDescriptorSetLayoutChain(
    VkDevice                                    device,
    uint32_t                                     setLayoutArrayCount,
    const VkDescriptorSetLayout*              pSetLayoutArray,
    VkDescriptorSetLayoutChain*              pLayoutChain);

VkResult VKAPI vkBeginDescriptorPoolUpdate(
    VkDevice                                    device,
    VkDescriptorUpdateMode                    updateMode);

VkResult VKAPI vkEndDescriptorPoolUpdate(
    VkDevice                                    device,
    VkCmdBuffer                                cmd);

VkResult VKAPI vkCreateDescriptorPool(
    VkDevice                                    device,
    VkDescriptorPoolUsage                     poolUsage,
    uint32_t                                     maxSets,
    const VkDescriptorPoolCreateInfo*        pCreateInfo,
    VkDescriptorPool*                          pDescriptorPool);

VkResult VKAPI vkResetDescriptorPool(
    VkDescriptorPool                           descriptorPool);

VkResult VKAPI vkAllocDescriptorSets(
    VkDescriptorPool                           descriptorPool,
    VkDescriptorSetUsage                      setUsage,
    uint32_t                                     count,
    const VkDescriptorSetLayout*              pSetLayouts,
    VkDescriptorSet*                           pDescriptorSets,
    uint32_t*                                    pCount);

void VKAPI vkClearDescriptorSets(
    VkDescriptorPool                           descriptorPool,
    uint32_t                                     count,
    const VkDescriptorSet*                     pDescriptorSets);

void VKAPI vkUpdateDescriptors(
    VkDescriptorSet                            descriptorSet,
    uint32_t                                     updateCount,
    const void**                                 pUpdateArray);

// State object functions

VkResult VKAPI vkCreateDynamicViewportState(
    VkDevice                                   device,
    const VkDynamicVpStateCreateInfo*      pCreateInfo,
    VkDynamicVpState*                 pState);

VkResult VKAPI vkCreateDynamicRasterState(
    VkDevice                                   device,
    const VkDynamicRsStateCreateInfo*      pCreateInfo,
    VkDynamicRsState*                 pState);

VkResult VKAPI vkCreateDynamicColorBlendState(
    VkDevice                                   device,
    const VkDynamicCbStateCreateInfo*      pCreateInfo,
    VkDynamicCbState*                 pState);

VkResult VKAPI vkCreateDynamicDepthStencilState(
    VkDevice                                   device,
    const VkDynamicDsStateCreateInfo*      pCreateInfo,
    VkDynamicDsState*                 pState);

// Command buffer functions

VkResult VKAPI vkCreateCommandBuffer(
    VkDevice                                   device,
    const VkCmdBufferCreateInfo*            pCreateInfo,
    VkCmdBuffer*                              pCmdBuffer);

VkResult VKAPI vkBeginCommandBuffer(
    VkCmdBuffer                               cmdBuffer,
    const VkCmdBufferBeginInfo*             pBeginInfo);

VkResult VKAPI vkEndCommandBuffer(
    VkCmdBuffer                               cmdBuffer);

VkResult VKAPI vkResetCommandBuffer(
    VkCmdBuffer                               cmdBuffer);

// Command buffer building functions

void VKAPI vkCmdBindPipeline(
    VkCmdBuffer                               cmdBuffer,
    VkPipelineBindPoint                      pipelineBindPoint,
    VkPipeline                                 pipeline);

void VKAPI vkCmdBindDynamicStateObject(
    VkCmdBuffer                               cmdBuffer,
    VkStateBindPoint                         stateBindPoint,
    VkDynamicStateObject                     dynamicState);

void VKAPI vkCmdBindDescriptorSets(
    VkCmdBuffer                               cmdBuffer,
    VkPipelineBindPoint                      pipelineBindPoint,
    VkDescriptorSetLayoutChain              layoutChain,
    uint32_t                                    layoutChainSlot,
    uint32_t                                    count,
    const VkDescriptorSet*                    pDescriptorSets,
    const uint32_t    *                         pUserData);

void VKAPI vkCmdBindIndexBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   buffer,
    VkGpuSize                                 offset,
    VkIndexType                               indexType);

void VKAPI vkCmdBindVertexBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   buffer,
    VkGpuSize                                 offset,
    uint32_t                                    binding);

void VKAPI vkCmdDraw(
    VkCmdBuffer                               cmdBuffer,
    uint32_t                                    firstVertex,
    uint32_t                                    vertexCount,
    uint32_t                                    firstInstance,
    uint32_t                                    instanceCount);

void VKAPI vkCmdDrawIndexed(
    VkCmdBuffer                               cmdBuffer,
    uint32_t                                    firstIndex,
    uint32_t                                    indexCount,
    int32_t                                     vertexOffset,
    uint32_t                                    firstInstance,
    uint32_t                                    instanceCount);

void VKAPI vkCmdDrawIndirect(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   buffer,
    VkGpuSize                                 offset,
    uint32_t                                    count,
    uint32_t                                    stride);

void VKAPI vkCmdDrawIndexedIndirect(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   buffer,
    VkGpuSize                                 offset,
    uint32_t                                    count,
    uint32_t                                    stride);

void VKAPI vkCmdDispatch(
    VkCmdBuffer                               cmdBuffer,
    uint32_t                                    x,
    uint32_t                                    y,
    uint32_t                                    z);
void VKAPI vkCmdDispatchIndirect(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   buffer,
    VkGpuSize                                 offset);

void VKAPI vkCmdCopyBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   srcBuffer,
    VkBuffer                                   destBuffer,
    uint32_t                                    regionCount,
    const VkBufferCopy*                       pRegions);

void VKAPI vkCmdCopyImage(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    srcImage,
    VkImageLayout                             srcImageLayout,
    VkImage                                    destImage,
    VkImageLayout                             destImageLayout,
    uint32_t                                    regionCount,
    const VkImageCopy*                        pRegions);

void VKAPI vkCmdBlitImage(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    srcImage,
    VkImageLayout                             srcImageLayout,
    VkImage                                    destImage,
    VkImageLayout                             destImageLayout,
    uint32_t                                    regionCount,
    const VkImageBlit*                        pRegions);

void VKAPI vkCmdCopyBufferToImage(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   srcBuffer,
    VkImage                                    destImage,
    VkImageLayout                             destImageLayout,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                 pRegions);

void VKAPI vkCmdCopyImageToBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    srcImage,
    VkImageLayout                             srcImageLayout,
    VkBuffer                                   destBuffer,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                 pRegions);

void VKAPI vkCmdCloneImageData(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    srcImage,
    VkImageLayout                             srcImageLayout,
    VkImage                                    destImage,
    VkImageLayout                             destImageLayout);

void VKAPI vkCmdUpdateBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   destBuffer,
    VkGpuSize                                 destOffset,
    VkGpuSize                                 dataSize,
    const uint32_t*                             pData);

void VKAPI vkCmdFillBuffer(
    VkCmdBuffer                               cmdBuffer,
    VkBuffer                                   destBuffer,
    VkGpuSize                                 destOffset,
    VkGpuSize                                 fillSize,
    uint32_t                                    data);

void VKAPI vkCmdClearColorImage(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    image,
    VkImageLayout                             imageLayout,
    VkClearColor                              color,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*           pRanges);

void VKAPI vkCmdClearDepthStencil(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    image,
    VkImageLayout                             imageLayout,
    float                                       depth,
    uint32_t                                    stencil,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*           pRanges);

void VKAPI vkCmdResolveImage(
    VkCmdBuffer                               cmdBuffer,
    VkImage                                    srcImage,
    VkImageLayout                             srcImageLayout,
    VkImage                                    destImage,
    VkImageLayout                             destImageLayout,
    uint32_t                                    rectCount,
    const VkImageResolve*                     pRects);

void VKAPI vkCmdSetEvent(
    VkCmdBuffer                               cmdBuffer,
    VkEvent                                    event,
    VkPipeEvent                               pipeEvent);

void VKAPI vkCmdResetEvent(
    VkCmdBuffer                               cmdBuffer,
    VkEvent                                    event,
    VkPipeEvent                               pipeEvent);

void VKAPI vkCmdWaitEvents(
    VkCmdBuffer                               cmdBuffer,
    const VkEventWaitInfo*                   pWaitInfo);

void VKAPI vkCmdPipelineBarrier(
    VkCmdBuffer                               cmdBuffer,
    const VkPipelineBarrier*                  pBarrier);

void VKAPI vkCmdBeginQuery(
    VkCmdBuffer                               cmdBuffer,
    VkQueryPool                               queryPool,
    uint32_t                                    slot,
    VkFlags                                    flags);

void VKAPI vkCmdEndQuery(
    VkCmdBuffer                               cmdBuffer,
    VkQueryPool                               queryPool,
    uint32_t                                    slot);

void VKAPI vkCmdResetQueryPool(
    VkCmdBuffer                               cmdBuffer,
    VkQueryPool                               queryPool,
    uint32_t                                    startQuery,
    uint32_t                                    queryCount);

void VKAPI vkCmdWriteTimestamp(
    VkCmdBuffer                               cmdBuffer,
    VkTimestampType                           timestampType,
    VkBuffer                                   destBuffer,
    VkGpuSize                                 destOffset);

void VKAPI vkCmdInitAtomicCounters(
    VkCmdBuffer                               cmdBuffer,
    VkPipelineBindPoint                      pipelineBindPoint,
    uint32_t                                    startCounter,
    uint32_t                                    counterCount,
    const uint32_t*                             pData);

void VKAPI vkCmdLoadAtomicCounters(
    VkCmdBuffer                               cmdBuffer,
    VkPipelineBindPoint                      pipelineBindPoint,
    uint32_t                                    startCounter,
    uint32_t                                    counterCount,
    VkBuffer                                   srcBuffer,
    VkGpuSize                                 srcOffset);

void VKAPI vkCmdSaveAtomicCounters(
    VkCmdBuffer                               cmdBuffer,
    VkPipelineBindPoint                      pipelineBindPoint,
    uint32_t                                    startCounter,
    uint32_t                                    counterCount,
    VkBuffer                                   destBuffer,
    VkGpuSize                                 destOffset);

VkResult VKAPI vkCreateFramebuffer(
    VkDevice                                   device,
    const VkFramebufferCreateInfo*           pCreateInfo,
    VkFramebuffer*                             pFramebuffer);

VkResult VKAPI vkCreateRenderPass(
    VkDevice                                   device,
    const VkRenderPassCreateInfo*           pCreateInfo,
    VkRenderPass*                             pRenderPass);

void VKAPI vkCmdBeginRenderPass(
    VkCmdBuffer                               cmdBuffer,
    const VkRenderPassBegin*                 pRenderPassBegin);

void VKAPI vkCmdEndRenderPass(
    VkCmdBuffer                               cmdBuffer,
    VkRenderPass                              renderPass);

#endif // VK_PROTOTYPES

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // __VULKAN_H__
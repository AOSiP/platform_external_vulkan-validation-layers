// VK tests
//
// Copyright (C) 2014 LunarG, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef VKTESTBINDING_H
#define VKTESTBINDING_H

#include <vector>

#include "vulkan.h"

namespace vk_testing {

typedef void (*ErrorCallback)(const char *expr, const char *file, unsigned int line, const char *function);
void set_error_callback(ErrorCallback callback);

class PhysicalGpu;
class BaseObject;
class Object;
class DynamicStateObject;
class Device;
class Queue;
class GpuMemory;
class Fence;
class Semaphore;
class Event;
class QueryPool;
class Buffer;
class BufferView;
class Image;
class ImageView;
class ColorAttachmentView;
class DepthStencilView;
class Shader;
class Pipeline;
class PipelineDelta;
class Sampler;
class DescriptorSetLayout;
class DescriptorSetLayoutChain;
class DescriptorSetPool;
class DescriptorSet;
class DynamicVpStateObject;
class DynamicRsStateObject;
class DynamicMsaaStateObject;
class DynamicCbStateObject;
class DynamicDsStateObject;
class CmdBuffer;

class PhysicalGpu {
public:
    explicit PhysicalGpu(VkPhysicalGpu gpu) : gpu_(gpu) {}

    const VkPhysicalGpu &obj() const { return gpu_; }

    // vkGetGpuInfo()
    VkPhysicalGpuProperties properties() const;
    VkPhysicalGpuPerformance performance() const;
    VkPhysicalGpuMemoryProperties memory_properties() const;
    std::vector<VkPhysicalGpuQueueProperties> queue_properties() const;

    // vkGetProcAddr()
    void *get_proc(const char *name) const { return vkGetProcAddr(gpu_, name); }

    // vkGetExtensionSupport()
    bool has_extension(const char *ext) const { return (vkGetExtensionSupport(gpu_, ext) == VK_SUCCESS); }
    std::vector<const char *> extensions() const;

    // vkEnumerateLayers()
    std::vector<const char *> layers(std::vector<char> &buf) const;

    // vkGetMultiGpuCompatibility()
    VkGpuCompatibilityInfo compatibility(const PhysicalGpu &other) const;

private:
    VkPhysicalGpu gpu_;
};

class BaseObject {
public:
    const VkBaseObject &obj() const { return obj_; }
    bool initialized() const { return (obj_ != VK_NULL_HANDLE); }

    // vkGetObjectInfo()
    uint32_t memory_allocation_count() const;
    std::vector<VkMemoryRequirements> memory_requirements() const;

protected:
    explicit BaseObject() : obj_(VK_NULL_HANDLE), own_obj_(false) {}
    explicit BaseObject(VkBaseObject obj) : obj_(VK_NULL_HANDLE), own_obj_(false) { init(obj); }

    void init(VkBaseObject obj, bool own);
    void init(VkBaseObject obj) { init(obj, true); }

    void reinit(VkBaseObject obj, bool own);
    void reinit(VkBaseObject obj) { reinit(obj, true); }

    bool own() const { return own_obj_; }

private:
    // base objects are non-copyable
    BaseObject(const BaseObject &);
    BaseObject &operator=(const BaseObject &);

    VkBaseObject obj_;
    bool own_obj_;
};

class Object : public BaseObject {
public:
    const VkObject &obj() const { return reinterpret_cast<const VkObject &>(BaseObject::obj()); }

    // vkBindObjectMemory()
    void bind_memory(uint32_t alloc_idx, const GpuMemory &mem, VkGpuSize mem_offset);
    void unbind_memory(uint32_t alloc_idx);
    void unbind_memory();

    // vkBindObjectMemoryRange()
    void bind_memory(uint32_t alloc_idx, VkGpuSize offset, VkGpuSize size,
                     const GpuMemory &mem, VkGpuSize mem_offset);

    // Unless an object is initialized with init_no_mem(), memories are
    // automatically allocated and bound.  These methods can be used to get
    // the memories (for vkQueueAddMemReference), or to map/unmap the primary memory.
    std::vector<VkGpuMemory> memories() const;

    const void *map(VkFlags flags) const;
          void *map(VkFlags flags);
    const void *map() const { return map(0); }
          void *map()       { return map(0); }

    void unmap() const;

protected:
    explicit Object() : mem_alloc_count_(0), internal_mems_(NULL), primary_mem_(NULL), bound(false) {}
    explicit Object(VkObject obj) : mem_alloc_count_(0), internal_mems_(NULL), primary_mem_(NULL) { init(obj); }
    ~Object() { cleanup(); }

    void init(VkObject obj, bool own);
    void init(VkObject obj) { init(obj, true); }

    void reinit(VkObject obj, bool own);
    void reinit(VkObject obj) { init(obj, true); }

    // allocate and bind internal memories
    void alloc_memory(const Device &dev, bool for_linear_img, bool for_img);
    void alloc_memory(const Device &dev) { alloc_memory(dev, false, false); }
    void alloc_memory(const std::vector<VkGpuMemory> &mems);

private:
    void cleanup();

    uint32_t mem_alloc_count_;
    GpuMemory *internal_mems_;
    GpuMemory *primary_mem_;
    bool bound;
};

class DynamicStateObject : public Object {
public:
    const VkDynamicStateObject &obj() const { return reinterpret_cast<const VkDynamicStateObject &>(Object::obj()); }

protected:
    explicit DynamicStateObject() {}
    explicit DynamicStateObject(VkDynamicStateObject obj) : Object(obj) {}
};

template<typename T, class C>
class DerivedObject : public C {
public:
    const T &obj() const { return reinterpret_cast<const T &>(C::obj()); }

protected:
    typedef T obj_type;
    typedef C base_type;

    explicit DerivedObject() {}
    explicit DerivedObject(T obj) : C(obj) {}
};

class Device : public DerivedObject<VkDevice, BaseObject> {
public:
    explicit Device(VkPhysicalGpu gpu) : gpu_(gpu) {}
    ~Device();

    // vkCreateDevice()
    void init(const VkDeviceCreateInfo &info);
    void init(bool enable_layers); // all queues, all extensions, etc
    void init() { init(false); };

    const PhysicalGpu &gpu() const { return gpu_; }

    // vkGetDeviceQueue()
    const std::vector<Queue *> &graphics_queues() { return queues_[GRAPHICS]; }
    const std::vector<Queue *> &compute_queues() { return queues_[COMPUTE]; }
    const std::vector<Queue *> &dma_queues() { return queues_[DMA]; }
    uint32_t graphics_queue_node_index_;

    struct Format {
        VkFormat format;
        VkImageTiling tiling;
        VkFlags features;
    };
    // vkGetFormatInfo()
    VkFormatProperties format_properties(VkFormat format);
    const std::vector<Format> &formats() const { return formats_; }

    // vkDeviceWaitIdle()
    void wait();

    // vkWaitForFences()
    VkResult wait(const std::vector<const Fence *> &fences, bool wait_all, uint64_t timeout);
    VkResult wait(const Fence &fence) { return wait(std::vector<const Fence *>(1, &fence), true, (uint64_t) -1); }

    // vkBeginDescriptorPoolUpdate()
    // vkEndDescriptorPoolUpdate()
    void begin_descriptor_pool_update(VkDescriptorUpdateMode mode);
    void end_descriptor_pool_update(CmdBuffer &cmd);

private:
    enum QueueIndex {
        GRAPHICS,
        COMPUTE,
        DMA,
        QUEUE_COUNT,
    };

    void init_queues();
    void init_formats();

    PhysicalGpu gpu_;

    std::vector<Queue *> queues_[QUEUE_COUNT];
    std::vector<Format> formats_;
};

class Queue : public DerivedObject<VkQueue, BaseObject> {
public:
    explicit Queue(VkQueue queue) : DerivedObject(queue) {}

    // vkQueueSubmit()
    void submit(const std::vector<const CmdBuffer *> &cmds, Fence &fence);
    void submit(const CmdBuffer &cmd, Fence &fence);
    void submit(const CmdBuffer &cmd);

    // vkQueueAddMemReference()
    // vkQueueRemoveMemReference()
    void add_mem_references(const std::vector<VkGpuMemory> &mem_refs);
    void remove_mem_references(const std::vector<VkGpuMemory> &mem_refs);

    // vkQueueWaitIdle()
    void wait();

    // vkQueueSignalSemaphore()
    // vkQueueWaitSemaphore()
    void signal_semaphore(Semaphore &sem);
    void wait_semaphore(Semaphore &sem);
};

class GpuMemory : public DerivedObject<VkGpuMemory, BaseObject> {
public:
    ~GpuMemory();

    // vkAllocMemory()
    void init(const Device &dev, const VkMemoryAllocInfo &info);
    // vkPinSystemMemory()
    void init(const Device &dev, size_t size, const void *data);
    // vkOpenSharedMemory()
    void init(const Device &dev, const VkMemoryOpenInfo &info);
    // vkOpenPeerMemory()
    void init(const Device &dev, const VkPeerMemoryOpenInfo &info);

    void init(VkGpuMemory mem) { BaseObject::init(mem, false); }

    // vkSetMemoryPriority()
    void set_priority(VkMemoryPriority priority);

    // vkMapMemory()
    const void *map(VkFlags flags) const;
          void *map(VkFlags flags);
    const void *map() const { return map(0); }
          void *map()       { return map(0); }

    // vkUnmapMemory()
    void unmap() const;

    static VkMemoryAllocInfo alloc_info(const VkMemoryRequirements &reqs,
                  const VkMemoryAllocInfo *next_info);
};

class Fence : public DerivedObject<VkFence, Object> {
public:
    // vkCreateFence()
    void init(const Device &dev, const VkFenceCreateInfo &info);

    // vkGetFenceStatus()
    VkResult status() const { return vkGetFenceStatus(obj()); }

    static VkFenceCreateInfo create_info(VkFenceCreateFlags flags);
    static VkFenceCreateInfo create_info();
};

class Semaphore : public DerivedObject<VkSemaphore, Object> {
public:
    // vkCreateSemaphore()
    void init(const Device &dev, const VkSemaphoreCreateInfo &info);
    // vkOpenSharedSemaphore()
    void init(const Device &dev, const VkSemaphoreOpenInfo &info);

    static VkSemaphoreCreateInfo create_info(uint32_t init_count, VkFlags flags);
};

class Event : public DerivedObject<VkEvent, Object> {
public:
    // vkCreateEvent()
    void init(const Device &dev, const VkEventCreateInfo &info);

    // vkGetEventStatus()
    // vkSetEvent()
    // vkResetEvent()
    VkResult status() const { return vkGetEventStatus(obj()); }
    void set();
    void reset();

    static VkEventCreateInfo create_info(VkFlags flags);
};

class QueryPool : public DerivedObject<VkQueryPool, Object> {
public:
    // vkCreateQueryPool()
    void init(const Device &dev, const VkQueryPoolCreateInfo &info);

    // vkGetQueryPoolResults()
    VkResult results(uint32_t start, uint32_t count, size_t size, void *data);

    static VkQueryPoolCreateInfo create_info(VkQueryType type, uint32_t slot_count);
};

class Buffer : public DerivedObject<VkBuffer, Object> {
public:
    explicit Buffer() {}
    explicit Buffer(const Device &dev, const VkBufferCreateInfo &info) { init(dev, info); }
    explicit Buffer(const Device &dev, VkGpuSize size) { init(dev, size); }

    // vkCreateBuffer()
    void init(const Device &dev, const VkBufferCreateInfo &info);
    void init(const Device &dev, VkGpuSize size) { init(dev, create_info(size, 0)); }
    void init_no_mem(const Device &dev, const VkBufferCreateInfo &info);

    static VkBufferCreateInfo create_info(VkGpuSize size, VkFlags usage);

    VkBufferMemoryBarrier buffer_memory_barrier(VkFlags output_mask, VkFlags input_mask,
                                                 VkGpuSize offset, VkGpuSize size) const
    {
        VkBufferMemoryBarrier barrier = {};
        barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
        barrier.buffer = obj();
        barrier.outputMask = output_mask;
        barrier.inputMask = input_mask;
        barrier.offset = offset;
        barrier.size = size;
        return barrier;
    }
private:
    VkBufferCreateInfo create_info_;
};

class BufferView : public DerivedObject<VkBufferView, Object> {
public:
    // vkCreateBufferView()
    void init(const Device &dev, const VkBufferViewCreateInfo &info);
};

class Image : public DerivedObject<VkImage, Object> {
public:
    explicit Image() : format_features_(0) {}
    explicit Image(const Device &dev, const VkImageCreateInfo &info) : format_features_(0) { init(dev, info); }

    // vkCreateImage()
    void init(const Device &dev, const VkImageCreateInfo &info);
    void init_no_mem(const Device &dev, const VkImageCreateInfo &info);
    // vkOpenPeerImage()
    void init(const Device &dev, const VkPeerImageOpenInfo &info, const VkImageCreateInfo &original_info);

    // vkBindImageMemoryRange()
    void bind_memory(uint32_t alloc_idx, const VkImageMemoryBindInfo &info,
                     const GpuMemory &mem, VkGpuSize mem_offset);

    // vkGetImageSubresourceInfo()
    VkSubresourceLayout subresource_layout(const VkImageSubresource &subres) const;

    bool transparent() const;
    bool copyable() const { return (format_features_ & VK_FORMAT_IMAGE_COPY_BIT); }

    VkImageSubresourceRange subresource_range(VkImageAspect aspect) const { return subresource_range(create_info_, aspect); }
    VkExtent3D extent() const { return create_info_.extent; }
    VkExtent3D extent(uint32_t mip_level) const { return extent(create_info_.extent, mip_level); }
    VkFormat format() const {return create_info_.format;}

    VkImageMemoryBarrier image_memory_barrier(VkFlags output_mask, VkFlags input_mask,
                                                  VkImageLayout old_layout,
                                                  VkImageLayout new_layout,
                                                  const VkImageSubresourceRange &range) const
    {
        VkImageMemoryBarrier barrier = {};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.outputMask = output_mask;
        barrier.inputMask = input_mask;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.image = obj();
        barrier.subresourceRange = range;
        return barrier;
    }

    static VkImageCreateInfo create_info();
    static VkImageSubresource subresource(VkImageAspect aspect, uint32_t mip_level, uint32_t array_slice);
    static VkImageSubresource subresource(const VkImageSubresourceRange &range, uint32_t mip_level, uint32_t array_slice);
    static VkImageSubresourceRange subresource_range(VkImageAspect aspect, uint32_t base_mip_level, uint32_t mip_levels,
                                                                                  uint32_t base_array_slice, uint32_t array_size);
    static VkImageSubresourceRange subresource_range(const VkImageCreateInfo &info, VkImageAspect aspect);
    static VkImageSubresourceRange subresource_range(const VkImageSubresource &subres);

    static VkExtent2D extent(int32_t width, int32_t height);
    static VkExtent2D extent(const VkExtent2D &extent, uint32_t mip_level);
    static VkExtent2D extent(const VkExtent3D &extent);

    static VkExtent3D extent(int32_t width, int32_t height, int32_t depth);
    static VkExtent3D extent(const VkExtent3D &extent, uint32_t mip_level);

private:
    void init_info(const Device &dev, const VkImageCreateInfo &info);

    VkImageCreateInfo create_info_;
    VkFlags format_features_;
};

class ImageView : public DerivedObject<VkImageView, Object> {
public:
    // vkCreateImageView()
    void init(const Device &dev, const VkImageViewCreateInfo &info);
};

class ColorAttachmentView : public DerivedObject<VkColorAttachmentView, Object> {
public:
    // vkCreateColorAttachmentView()
    void init(const Device &dev, const VkColorAttachmentViewCreateInfo &info);
};

class DepthStencilView : public DerivedObject<VkDepthStencilView, Object> {
public:
    // vkCreateDepthStencilView()
    void init(const Device &dev, const VkDepthStencilViewCreateInfo &info);
};

class Shader : public DerivedObject<VkShader, Object> {
public:
    // vkCreateShader()
    void init(const Device &dev, const VkShaderCreateInfo &info);
    VkResult init_try(const Device &dev, const VkShaderCreateInfo &info);

    static VkShaderCreateInfo create_info(size_t code_size, const void *code, VkFlags flags);
};

class Pipeline : public DerivedObject<VkPipeline, Object> {
public:
    // vkCreateGraphicsPipeline()
    void init(const Device &dev, const VkGraphicsPipelineCreateInfo &info);
    // vkCreateGraphicsPipelineDerivative()
    void init(const Device &dev, const VkGraphicsPipelineCreateInfo &info, const VkPipeline basePipeline);
    // vkCreateComputePipeline()
    void init(const Device &dev, const VkComputePipelineCreateInfo &info);
    // vkLoadPipeline()
    void init(const Device&dev, size_t size, const void *data);
    // vkLoadPipelineDerivative()
    void init(const Device&dev, size_t size, const void *data, VkPipeline basePipeline);

    // vkStorePipeline()
    size_t store(size_t size, void *data);
};

class Sampler : public DerivedObject<VkSampler, Object> {
public:
    // vkCreateSampler()
    void init(const Device &dev, const VkSamplerCreateInfo &info);
};

class DescriptorSetLayout : public DerivedObject<VkDescriptorSetLayout, Object> {
public:
    // vkCreateDescriptorSetLayout()
    void init(const Device &dev, const VkDescriptorSetLayoutCreateInfo &info);
};

class DescriptorSetLayoutChain : public DerivedObject<VkDescriptorSetLayoutChain, Object> {
public:
    // vkCreateDescriptorSetLayoutChain()
    void init(const Device &dev, const std::vector<const DescriptorSetLayout *> &layouts);
};

class DescriptorPool : public DerivedObject<VkDescriptorPool, Object> {
public:
    // vkCreateDescriptorPool()
    void init(const Device &dev, VkDescriptorPoolUsage usage,
              uint32_t max_sets, const VkDescriptorPoolCreateInfo &info);

    // vkResetDescriptorPool()
    void reset();

    // vkAllocDescriptorSets()
    std::vector<DescriptorSet *> alloc_sets(VkDescriptorSetUsage usage, const std::vector<const DescriptorSetLayout *> &layouts);
    std::vector<DescriptorSet *> alloc_sets(VkDescriptorSetUsage usage, const DescriptorSetLayout &layout, uint32_t count);
    DescriptorSet *alloc_sets(VkDescriptorSetUsage usage, const DescriptorSetLayout &layout);

    // vkClearDescriptorSets()
    void clear_sets(const std::vector<DescriptorSet *> &sets);
    void clear_sets(DescriptorSet &set) { clear_sets(std::vector<DescriptorSet *>(1, &set)); }
};

class DescriptorSet : public DerivedObject<VkDescriptorSet, Object> {
public:
    explicit DescriptorSet(VkDescriptorSet set) : DerivedObject(set) {}

    // vkUpdateDescriptors()
    void update(const std::vector<const void *> &update_array);

    static VkUpdateSamplers update(uint32_t binding, uint32_t index, uint32_t count, const VkSampler *samplers);
    static VkUpdateSamplers update(uint32_t binding, uint32_t index, const std::vector<VkSampler> &samplers);

    static VkUpdateSamplerTextures update(uint32_t binding, uint32_t index, uint32_t count, const VkSamplerImageViewInfo *textures);
    static VkUpdateSamplerTextures update(uint32_t binding, uint32_t index, const std::vector<VkSamplerImageViewInfo> &textures);

    static VkUpdateImages update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count, const VkImageViewAttachInfo *views);
    static VkUpdateImages update(VkDescriptorType type, uint32_t binding, uint32_t index, const std::vector<VkImageViewAttachInfo> &views);

    static VkUpdateBuffers update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count, const VkBufferViewAttachInfo *views);
    static VkUpdateBuffers update(VkDescriptorType type, uint32_t binding, uint32_t index, const std::vector<VkBufferViewAttachInfo> &views);

    static VkUpdateAsCopy update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count, const DescriptorSet &set);

    static VkBufferViewAttachInfo attach_info(const BufferView &view);
    static VkImageViewAttachInfo attach_info(const ImageView &view, VkImageLayout layout);
};

class DynamicVpStateObject : public DerivedObject<VkDynamicVpState, DynamicStateObject> {
public:
    // vkCreateDynamicViewportState()
    void init(const Device &dev, const VkDynamicVpStateCreateInfo &info);
};

class DynamicRsStateObject : public DerivedObject<VkDynamicRsState, DynamicStateObject> {
public:
    // vkCreateDynamicRasterState()
    void init(const Device &dev, const VkDynamicRsStateCreateInfo &info);
};

class DynamicCbStateObject : public DerivedObject<VkDynamicCbState, DynamicStateObject> {
public:
    // vkCreateDynamicColorBlendState()
    void init(const Device &dev, const VkDynamicCbStateCreateInfo &info);
};

class DynamicDsStateObject : public DerivedObject<VkDynamicDsState, DynamicStateObject> {
public:
    // vkCreateDynamicDepthStencilState()
    void init(const Device &dev, const VkDynamicDsStateCreateInfo &info);
};

class CmdBuffer : public DerivedObject<VkCmdBuffer, Object> {
public:
    explicit CmdBuffer() {}
    explicit CmdBuffer(const Device &dev, const VkCmdBufferCreateInfo &info) { init(dev, info); }

    // vkCreateCommandBuffer()
    void init(const Device &dev, const VkCmdBufferCreateInfo &info);

    // vkBeginCommandBuffer()
    void begin(const VkCmdBufferBeginInfo *info);
    void begin(VkRenderPass renderpass_obj, VkFramebuffer framebuffer_obj);
    void begin();

    // vkEndCommandBuffer()
    // vkResetCommandBuffer()
    void end();
    void reset();

    static VkCmdBufferCreateInfo create_info(uint32_t queueNodeIndex);
};

inline const void *Object::map(VkFlags flags) const
{
    return (primary_mem_) ? primary_mem_->map(flags) : NULL;
}

inline void *Object::map(VkFlags flags)
{
    return (primary_mem_) ? primary_mem_->map(flags) : NULL;
}

inline void Object::unmap() const
{
    if (primary_mem_)
        primary_mem_->unmap();
}

inline VkMemoryAllocInfo GpuMemory::alloc_info(const VkMemoryRequirements &reqs,
                                const VkMemoryAllocInfo *next_info)
{
    VkMemoryAllocInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOC_INFO;
    if (next_info != NULL)
        info.pNext = (void *) next_info;

    info.allocationSize = reqs.size;
    info.memProps = reqs.memProps;
    info.memType = reqs.memType;
    info.memPriority = VK_MEMORY_PRIORITY_NORMAL;
    return info;
}

inline VkBufferCreateInfo Buffer::create_info(VkGpuSize size, VkFlags usage)
{
    VkBufferCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    info.size = size;
    info.usage = usage;
    return info;
}

inline VkFenceCreateInfo Fence::create_info(VkFenceCreateFlags flags)
{
    VkFenceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.flags = flags;
    return info;
}

inline VkFenceCreateInfo Fence::create_info()
{
    VkFenceCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return info;
}

inline VkSemaphoreCreateInfo Semaphore::create_info(uint32_t init_count, VkFlags flags)
{
    VkSemaphoreCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.initialCount = init_count;
    info.flags = flags;
    return info;
}

inline VkEventCreateInfo Event::create_info(VkFlags flags)
{
    VkEventCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
    info.flags = flags;
    return info;
}

inline VkQueryPoolCreateInfo QueryPool::create_info(VkQueryType type, uint32_t slot_count)
{
    VkQueryPoolCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    info.queryType = type;
    info.slots = slot_count;
    return info;
}

inline VkImageCreateInfo Image::create_info()
{
    VkImageCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.extent.width = 1;
    info.extent.height = 1;
    info.extent.depth = 1;
    info.mipLevels = 1;
    info.arraySize = 1;
    info.samples = 1;
    return info;
}

inline VkImageSubresource Image::subresource(VkImageAspect aspect, uint32_t mip_level, uint32_t array_slice)
{
    VkImageSubresource subres = {};
    subres.aspect = aspect;
    subres.mipLevel = mip_level;
    subres.arraySlice = array_slice;
    return subres;
}

inline VkImageSubresource Image::subresource(const VkImageSubresourceRange &range, uint32_t mip_level, uint32_t array_slice)
{
    return subresource(range.aspect, range.baseMipLevel + mip_level, range.baseArraySlice + array_slice);
}

inline VkImageSubresourceRange Image::subresource_range(VkImageAspect aspect, uint32_t base_mip_level, uint32_t mip_levels,
                                                                                     uint32_t base_array_slice, uint32_t array_size)
{
    VkImageSubresourceRange range = {};
    range.aspect = aspect;
    range.baseMipLevel = base_mip_level;
    range.mipLevels = mip_levels;
    range.baseArraySlice = base_array_slice;
    range.arraySize = array_size;
    return range;
}

inline VkImageSubresourceRange Image::subresource_range(const VkImageCreateInfo &info, VkImageAspect aspect)
{
    return subresource_range(aspect, 0, info.mipLevels, 0, info.arraySize);
}

inline VkImageSubresourceRange Image::subresource_range(const VkImageSubresource &subres)
{
    return subresource_range(subres.aspect, subres.mipLevel, 1, subres.arraySlice, 1);
}

inline VkExtent2D Image::extent(int32_t width, int32_t height)
{
    VkExtent2D extent = {};
    extent.width = width;
    extent.height = height;
    return extent;
}

inline VkExtent2D Image::extent(const VkExtent2D &extent, uint32_t mip_level)
{
    const int32_t width  = (extent.width  >> mip_level) ? extent.width  >> mip_level : 1;
    const int32_t height = (extent.height >> mip_level) ? extent.height >> mip_level : 1;
    return Image::extent(width, height);
}

inline VkExtent2D Image::extent(const VkExtent3D &extent)
{
    return Image::extent(extent.width, extent.height);
}

inline VkExtent3D Image::extent(int32_t width, int32_t height, int32_t depth)
{
    VkExtent3D extent = {};
    extent.width = width;
    extent.height = height;
    extent.depth = depth;
    return extent;
}

inline VkExtent3D Image::extent(const VkExtent3D &extent, uint32_t mip_level)
{
    const int32_t width  = (extent.width  >> mip_level) ? extent.width  >> mip_level : 1;
    const int32_t height = (extent.height >> mip_level) ? extent.height >> mip_level : 1;
    const int32_t depth  = (extent.depth  >> mip_level) ? extent.depth  >> mip_level : 1;
    return Image::extent(width, height, depth);
}

inline VkShaderCreateInfo Shader::create_info(size_t code_size, const void *code, VkFlags flags)
{
    VkShaderCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SHADER_CREATE_INFO;
    info.codeSize = code_size;
    info.pCode = code;
    info.flags = flags;
    return info;
}

inline VkBufferViewAttachInfo DescriptorSet::attach_info(const BufferView &view)
{
    VkBufferViewAttachInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_ATTACH_INFO;
    info.view = view.obj();
    return info;
}

inline VkImageViewAttachInfo DescriptorSet::attach_info(const ImageView &view, VkImageLayout layout)
{
    VkImageViewAttachInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_ATTACH_INFO;
    info.view = view.obj();
    info.layout = layout;
    return info;
}

inline VkUpdateSamplers DescriptorSet::update(uint32_t binding, uint32_t index, uint32_t count, const VkSampler *samplers)
{
    VkUpdateSamplers info = {};
    info.sType = VK_STRUCTURE_TYPE_UPDATE_SAMPLERS;
    info.binding = binding;
    info.arrayIndex = index;
    info.count = count;
    info.pSamplers = samplers;
    return info;
}

inline VkUpdateSamplers DescriptorSet::update(uint32_t binding, uint32_t index, const std::vector<VkSampler> &samplers)
{
    return update(binding, index, samplers.size(), &samplers[0]);
}

inline VkUpdateSamplerTextures DescriptorSet::update(uint32_t binding, uint32_t index, uint32_t count, const VkSamplerImageViewInfo *textures)
{
    VkUpdateSamplerTextures info = {};
    info.sType = VK_STRUCTURE_TYPE_UPDATE_SAMPLER_TEXTURES;
    info.binding = binding;
    info.arrayIndex = index;
    info.count = count;
    info.pSamplerImageViews = textures;
    return info;
}

inline VkUpdateSamplerTextures DescriptorSet::update(uint32_t binding, uint32_t index, const std::vector<VkSamplerImageViewInfo> &textures)
{
    return update(binding, index, textures.size(), &textures[0]);
}

inline VkUpdateImages DescriptorSet::update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count,
                                               const VkImageViewAttachInfo *views)
{
    VkUpdateImages info = {};
    info.sType = VK_STRUCTURE_TYPE_UPDATE_IMAGES;
    info.descriptorType = type;
    info.binding = binding;
    info.arrayIndex = index;
    info.count = count;
    info.pImageViews = views;
    return info;
}

inline VkUpdateImages DescriptorSet::update(VkDescriptorType type, uint32_t binding, uint32_t index,
                                               const std::vector<VkImageViewAttachInfo> &views)
{
    return update(type, binding, index, views.size(), &views[0]);
}

inline VkUpdateBuffers DescriptorSet::update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count,
                                                const VkBufferViewAttachInfo *views)
{
    VkUpdateBuffers info = {};
    info.sType = VK_STRUCTURE_TYPE_UPDATE_BUFFERS;
    info.descriptorType = type;
    info.binding = binding;
    info.arrayIndex = index;
    info.count = count;
    info.pBufferViews = views;
    return info;
}

inline VkUpdateBuffers DescriptorSet::update(VkDescriptorType type, uint32_t binding, uint32_t index,
                                                const std::vector<VkBufferViewAttachInfo> &views)
{
    return update(type, binding, index, views.size(), &views[0]);
}

inline VkUpdateAsCopy DescriptorSet::update(VkDescriptorType type, uint32_t binding, uint32_t index, uint32_t count, const DescriptorSet &set)
{
    VkUpdateAsCopy info = {};
    info.sType = VK_STRUCTURE_TYPE_UPDATE_AS_COPY;
    info.descriptorType = type;
    info.binding = binding;
    info.arrayElement = index;
    info.count = count;
    info.descriptorSet = set.obj();
    return info;
}

inline VkCmdBufferCreateInfo CmdBuffer::create_info(uint32_t queueNodeIndex)
{
    VkCmdBufferCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_CMD_BUFFER_CREATE_INFO;
    info.queueNodeIndex = queueNodeIndex;
    return info;
}

}; // namespace vk_testing

#endif // VKTESTBINDING_H
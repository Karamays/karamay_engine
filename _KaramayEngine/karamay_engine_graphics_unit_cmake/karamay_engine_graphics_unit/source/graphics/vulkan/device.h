#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"

class device_memory;
class buffer;
class buffer_view;
class image;
class image_view;
class sampler;
class acceleration_structure;
class descriptor_set;
class descriptor_set_layout;
class framebuffer;
class pipeline_cache;
class pipeline_layout;
class graphics_pipeline;
class mesh_pipeline;
class compute_pipeline;
class ray_tracing_pipeline;
class shader_module;
class command_pool;
class render_pass;
class physical_device;

#define device_khr_func(func_name)\
PFN_##func_name##(vkGetDeviceProcAddr(_device.handle(), #func_name))\

class device final : public vulkan_object<VkDevice>
{
public:

	device();

	device(const device&) = delete;
	device& operator=(const device&) = delete;

	~device();

public:

	bool allocate(physical_device* entity) noexcept;

	void deallocate() noexcept;

public:

	void get_descriptor_set_layout_support(VkDescriptorSetLayoutSupport& support) noexcept;

	bool wait() noexcept;

};

#endif
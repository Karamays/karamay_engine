#include "device.h"
#include "device_object/buffer.h"
#include "device_object/buffer_view.h"
#include "device_object/image.h"
#include "device_object/image_view.h"
#include "device_object/command_pool.h"
#include "device_object/pooled_object/command_buffer.h"
#include "device_object/pooled_object/descriptor_set.h"
#include "device_object/descriptor_set_layout.h"
#include "device_object/acceleration_structure.h"
#include "device_object/device_memory.h"
#include "device_object/framebuffer.h"
#include "device_object/pipeline.h"
#include "device_object/pipeline_cache.h"
#include "device_object/pipeline_layout.h"
#include "device_object/render_pass.h"
#include "device_object/sampler.h"
#include "device_object/shader_module.h"

bool device::wait() noexcept
{
	vkDeviceWaitIdle(_handle);

	return true;
}

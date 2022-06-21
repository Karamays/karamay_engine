#include "fence.h"

vk_fence::vk_fence(device& dev) : device_object(dev)
{
}

vk_fence::~vk_fence()
{
	deallocate();
}

bool vk_fence::allocate() noexcept
{
	VkFenceCreateInfo _create_info;
	_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	return vkCreateFence(_dev.handle(), &_create_info, nullptr, &_handle);
}

void vk_fence::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyFence(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void vk_fence::wait(bool wait_all, uint64 timeout) noexcept
{
	if (_handle)
	{
		vkWaitForFences(_dev.handle(), 1, &_handle, wait_all, timeout);
	}
}

void vk_fence::reset() noexcept
{
	if (_handle)
	{
		vkResetFences(_dev.handle(), 1, &_handle);
	}
}

bool vk_fence::is_signaled() noexcept
{
	if (!_handle)
	{
		return false;
	}

	return vkGetFenceStatus(_dev.handle(), _handle) == VkResult::VK_SUCCESS;
}

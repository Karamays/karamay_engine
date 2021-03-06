#include "physical_device.h"

physical_device::physical_device(VkPhysicalDevice new_handle)
{
    _handle = new_handle;
}

physical_device::~physical_device()
{
}

void physical_device::enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkEnumerateDeviceExtensionProperties(_handle, player_name.c_str(), &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkEnumerateDeviceExtensionProperties(_handle, player_name.c_str(), &_count, properties.data());
}

void physical_device::enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkEnumerateDeviceLayerProperties(_handle, &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkEnumerateDeviceLayerProperties(_handle, &_count, properties.data());
}

void physical_device::get_features(VkPhysicalDeviceFeatures& features) noexcept
{
    vkGetPhysicalDeviceFeatures(_handle, &features);
}

void physical_device::get_properties(VkPhysicalDeviceProperties& properties) noexcept
{
    vkGetPhysicalDeviceProperties(_handle, &properties);
}

void physical_device::get_queue_family_properties(std::vector<VkQueueFamilyProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, properties.data());
}

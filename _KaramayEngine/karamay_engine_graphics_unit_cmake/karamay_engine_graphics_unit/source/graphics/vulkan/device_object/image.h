#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class command_buffer;
class buffer;

class image final :public device_object<VkImage>
{

public:

	image(device& dev);

	~image() override;

private:

	VkImageLayout _layout;

public:

	VkImageLayout layout() const noexcept { return _layout; }

public:

	bool allocate();

	void deallocate();

public:

	void copy_to(command_buffer* recorder, image* dst, const std::vector<VkImageCopy>& regions);

	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferImageCopy>& regions);

	void blit_to(command_buffer* recorder, image* dst, const std::vector<VkImageBlit>& regions, VkFilter filter);

	void resolve_to(command_buffer* recorder, image* dst, const std::vector<VkImageResolve>& regions);

	void clear(command_buffer* recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void clear(command_buffer* recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges);

};

#endif
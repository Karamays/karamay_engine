#pragma once
#include "graphics/buffer/gl_buffer.h"

struct gl_shader_storage_buffer_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};


class gl_shader_storage_buffer
{

public:

	gl_shader_storage_buffer();

	virtual ~gl_shader_storage_buffer();

public:

	void fill()
	{

	}



	auto get_binding_info()
	{
		return gl_shader_storage_buffer_binding_info();
	}

private:

	void _generate_template_code()
	{
		std::regex pattern("layout (binding = 0, std430) buffer my_vertices {}");
	}

};


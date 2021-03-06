#include "gl_vertex_array.h"
#include "graphics/buffer/gl_buffer.h"

gl_vertex_array::gl_vertex_array(std::shared_ptr<gl_vertex_array_descriptor> descriptor)
{
	glCreateVertexArrays(1, &_handle);

	_descriptor = descriptor;

	if (_descriptor && _descriptor->is_dirty())
	{
		_fill();
	}
}

bool gl_vertex_array::is_pointer_enabled(std::uint32_t index)
{
	bind();
	GLint _is_enabled = GL_FALSE;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
	unbind();
	return _is_enabled;
}

std::uint32_t gl_vertex_array::get_attribute_components_num(std::uint32_t index)
{
	bind();
	GLint _num = 0;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
	unbind();
	return _num;
}

std::string gl_vertex_array::get_attribute_component_type(std::uint32_t index)
{
	bind();
	GLint _num = 0;
	glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &_num);
	unbind();

	switch (_num)
	{
	case GL_BYTE: return "BYTE";
	case GL_UNSIGNED_BYTE: return "UNSIGNED BYTE";
	case GL_SHORT: return "SHORT";
	case GL_UNSIGNED_SHORT: return "UNSIGNED SHORT";
	case GL_INT: return "INT";
	case GL_UNSIGNED_INT: return "UNSIGNED INT";
	case GL_FLOAT: return "FLOAT";
	case GL_DOUBLE: return "DOUBLE";
	default: return "";
		break;
	}
}

void* gl_vertex_array::get_mapped_data()
{
	if (_buffer)
		return _buffer->map(gl_buffer_enum::access::READ_WRITE);
	return nullptr;
}

const std::int32_t gl_vertex_array::get_size() const
{
	return _buffer->get_size();
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}

void gl_vertex_array::bind()
{
	glBindVertexArray(_handle);
}

void gl_vertex_array::unbind()
{
	glBindVertexArray(0);
}

void gl_vertex_array::enable_pointers()
{
	if (_descriptor)
	{
		const std::size_t _size = _descriptor->get_layouts().size();

		for (std::uint32_t i = 0; i < _size; ++i)
		{
			glEnableVertexAttribArray(i);
		}
	}
}

void gl_vertex_array::disable_pointers()
{
	if (_descriptor)
	{
		const std::size_t _size = _descriptor->get_layouts().size();

		for (std::uint32_t i = 0; i < _size; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}
}

void gl_vertex_array::_bind_buffer()
{
	if (_buffer)
		glBindBuffer(GL_ARRAY_BUFFER, _buffer->get_handle());
}

void gl_vertex_array::_unbind_buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl_vertex_array::_fill()
{
	if (_descriptor)
	{
		const auto _stream_size = _descriptor->get_stream_size();
		_buffer = std::make_shared<gl_buffer>();
		_buffer->allocate(_stream_size);
		_buffer->fill(0, _stream_size, _descriptor->get_stream());

		bind(); _bind_buffer();

		const auto& _layouts = _descriptor->get_layouts();
		const std::uint32_t _max_index_num = static_cast<std::uint32_t>(_layouts.size());
		std::size_t _offset = 0;

		for (std::uint32_t _index = 0; _index < _max_index_num; ++_index)
		{
			const auto& _layout = _layouts[_index];
			const auto _normalized = _layout.normalized;

			const auto _component_type_enum = _layout.components_type_enum;
			const auto _components_num = _layout.components_num;
			const auto _attribute_size = _layout.attrib_size;
			const auto _attributes_num = _layout.attribs_num;

			const auto _divisor = _layout.divisor;

			if (_normalized) // integers -> normalized floats
			{
				if (_component_type_enum == GL_BYTE || _component_type_enum == GL_UNSIGNED_BYTE ||
					_component_type_enum == GL_SHORT || _component_type_enum == GL_UNSIGNED_SHORT ||
					_component_type_enum == GL_INT || _component_type_enum == GL_UNSIGNED_INT)
				{
					glVertexAttribPointer(_index,
						_components_num,
						_component_type_enum, GL_TRUE,
						_attribute_size,
						reinterpret_cast<const void*>(_offset));
				}
			}
			else { // original integers
				if (_component_type_enum == GL_BYTE || _component_type_enum == GL_UNSIGNED_BYTE ||
					_component_type_enum == GL_SHORT || _component_type_enum == GL_UNSIGNED_SHORT ||
					_component_type_enum == GL_INT || _component_type_enum == GL_UNSIGNED_INT)
				{
					glVertexAttribIPointer(_index,
						_components_num,
						_component_type_enum,
						_attribute_size,
						reinterpret_cast<const void*>(_offset));
				}
				else if (_component_type_enum == GL_HALF_FLOAT || _component_type_enum == GL_FLOAT ||
					_component_type_enum == GL_FIXED) // original floats
				{
					glVertexAttribPointer(_index,
						_components_num,
						_component_type_enum, GL_FALSE,
						_attribute_size,
						reinterpret_cast<const void*>(_offset));
				}
				else if (_component_type_enum == GL_DOUBLE) // original doubles
				{
					glVertexAttribLPointer(_index,
						_components_num,
						_component_type_enum,
						_attribute_size,
						reinterpret_cast<const void*>(_offset));
				}
			}

			glVertexAttribDivisor(_index, _divisor);

			_offset += static_cast<std::size_t>(_attributes_num) * _attribute_size;
		}

		_unbind_buffer(); unbind();
	}

#ifdef _DEBUG
	const std::size_t _size = _descriptor->get_layouts().size();
	for (std::size_t i = 0; i < _size; ++i)
	{
		std::cout << "pointer [" << i << "] " << is_pointer_enabled(static_cast<std::uint32_t>(i)) << std::endl;
		std::cout << "attribute components num: " << get_attribute_components_num(static_cast<std::uint32_t>(i)) << std::endl;
		std::cout << "attribute components type: " << get_attribute_component_type(static_cast<std::uint32_t>(i)) << std::endl;
	}
#endif
}

const void* gl_vertex_array_descriptor::get_stream() const
{
	return _stream.data();
}

const std::size_t gl_vertex_array_descriptor::get_stream_size() const
{
	return _stream.size();
}

const std::vector<gl_vertex_attribute_layout> gl_vertex_array_descriptor::get_layouts() const
{
	return _layouts;
}

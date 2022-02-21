#include "gl_program.h"

void gl_program::_install()
{
	_bind_vertex_array();
	_bind_element_array_buffer();
	_bind_transform_feedback();
	_bind_uniform_buffers();
	_bind_shader_storage_buffers();
	_bind_atomic_counter_buffers();
	_bind_framebuffer();
	_bind_textures(); 
}

void gl_program::_enable()
{
	glUseProgram(_handle);

	std::cout << "[program is enabled.]" << std::endl;
}

void gl_program::_disable()
{
	glUseProgram(0);

	std::cout << "[program is disabled.]" << std::endl;
}

void gl_program::_uninstall()
{
	/*_unbind_framebuffer();
	_unbind_vertex_array();
	_unbind_element_array_buffer();
	_unbind_transform_feedback();
	_unbind_uniform_buffers();
	_unbind_shader_storage_buffers();
	_unbind_atomic_counter_buffers();*/
}

inline void gl_program::_set_transform_feedback_varyings()
{
	//if (_transform_feedback)
	//{
	//	// set program's transform feedback output vars, then relink program
	//	const auto& varyings = _transform_feedback->get_varyings();
	//	if (varyings.size() > 0)
	//	{
	//		//glTransformFeedbackVaryings(_handle, static_cast<GLsizei>(varyings.size()), varyings.data(), static_cast<GLenum>(gl_buffer_mode::INTERLEAVED));
	//		glLinkProgram(_handle);
	//	}
	//}
}

inline void gl_program::_bind_vertex_array()
{

}

inline void gl_program::_bind_element_array_buffer()
{
//	if (_element_array_buffer) {
//		// bind it into context
//		_element_array_buffer->bind();
//
//#ifdef _DEBUG
//		std::cout << "[element array buffers is bound.]" << std::endl;
//#endif
//	}
}

inline void gl_program::_bind_transform_feedback()
{

}

inline void gl_program::_bind_uniform_buffers()
{
//	const std::size_t max_i = _uniform_buffers.size() > GL_MAX_UNIFORM_BUFFER_BINDINGS 
//		? GL_MAX_UNIFORM_BUFFER_BINDINGS : _uniform_buffers.size();
//
//	for (std::int32_t i = 0; i < max_i; ++i)
//	{
//		if (auto uniform_buffer = _uniform_buffers[i])
//		{
//			if (uniform_buffer)
//			{
////			    // bind uniform buffers to context binding
////				uniform_buffer->bind(i);
////				// bind program uniform index to context binding
////				std::uint32_t _uniform_block_index = glGetUniformBlockIndex(_handle, uniform_buffer->get_block_name().c_str());
////				glUniformBlockBinding(_handle, _uniform_block_index, i);
////#ifdef _DEBUG
////				std::cout << "[ uniform block index: "<< _uniform_block_index <<".]" << std::endl;
////#endif
//
//			}
//		}
//	}
}

inline void gl_program::_bind_shader_storage_buffers()
{
//	const std::size_t max_i = _shader_storage_buffers.size() > GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 
//		? GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS : _shader_storage_buffers.size();
//
//	for (std::int32_t i = 0; i < max_i; ++i)
//	{
//		if (auto shader_storage_buffer = _shader_storage_buffers[i])
//		{
//			if (shader_storage_buffer)
//			{
////				// bind buffers to context
////				shader_storage_buffer->bind(i);
////				// bind program to context
////				const GLuint _index = glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, shader_storage_buffer->get_descriptor()->get_block_name().c_str());
////				glShaderStorageBlockBinding(_handle, _index, i);
////
////#ifdef _DEBUG
////				std::cout << "[ " << i << " shader storage buffers is bound.]" << std::endl;
////#endif // DEBUG
//			}
//		}
//	}
}

inline void gl_program::_bind_atomic_counter_buffers()
{
//	const std::size_t max_i
//		= _atomic_counter_buffers.size() > GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS ? GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS : _atomic_counter_buffers.size();
//
//	for (std::int32_t i = 0; i < max_i; ++i)
//	{
//		if (auto atomic_counter_buffer = _atomic_counter_buffers[i])
//		{
//			if (atomic_counter_buffer)
//			{
////				// bind buffers to context
////				atomic_counter_buffer->bind(i);
////#ifdef _DEBUG
////				std::cout << "[ " << i << " atomic counter buffers is bound.]" << std::endl;
////#endif // DEBUG
//				
//			}
//		}
//	}
}

inline void gl_program::_bind_framebuffer()
{
		
}
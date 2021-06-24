#pragma once
#include "graphics/glo/gl_object.h"

class gl_program;



namespace gl_program_pipeline_enum
{

}

class gl_program_pipeline : public gl_object
{
public:

	gl_program_pipeline();
	
	virtual ~gl_program_pipeline();

public:
	virtual void construct() {}

	virtual void render(std::float_t delta_time) {}


protected:

	void attach_program(GLbitfield stages, std::shared_ptr<gl_program> program);


	// discard 划定的区域外的片段 剪裁测试
	static void enable_scissor_test();
	static void disable_scissor_test();
	// 设置所有窗口的剪裁盒，包括多窗口模式下
	static void set_scissor_box(GLint x, GLint y, GLsizei width, GLsizei height);
	static void set_scissor_box(GLint x, GLint y, GLsizei width, GLsizei height, GLuint viewport_index);

	// 模板测试
	static void enable_stencil_test();
	static void disable_stencil_test();
	
	static void set_stencil_mask(GLuint mask);
	
	static void set_stencil_function(GLenum func, GLint stencil_value, GLuint mask);
	static void set_stencil_function(GLenum front_func, GLenum back_func, GLint stencil_value, GLuint mask);

	static void set_stencil_operation(GLenum fail, GLenum z_fail, GLenum z_pass);
	static void set_stencil_operation(GLenum face, GLenum sfail, GLenum dp_fail, GLenum dp_pass);

	// 深度测试
	static void enable_depth_test();
	static void disable_depth_test();
	static void set_depth()
	{
		//glDepthFunc()
	}

	static void enable_occlusion_query()
	{
		
	}
	

	

public:
	void bind();

	void unbind();
};


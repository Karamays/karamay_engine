#include "gl_shader_toy_renderer.h"
#include "graphics/glsl/program/glsl_graphics_pipeline_program.h"
#include "engine/karamay_engine.h"

gl_shader_toy_renderer* gl_shader_toy_renderer::_instance = nullptr;

bool gl_shader_toy_renderer::initialize() noexcept
{
	
	return false;
}

bool gl_shader_toy_renderer::attach() noexcept
{
	// check renderer state : detached
	if (!_attached)
	{
		// load the renderer template instance

		auto _rti = _load_rti(
			karamay_engine::get_engine_root() + "shaders/renderers/shader_toy/shader_toy.rti"
		);

		if (!_rti)
		{
			return false;
		}

		auto _it = _rti->name_to_graphics_pipeline.find("shader_toy_gpp");
		if (_it == _rti->name_to_graphics_pipeline.cend())
		{
			return false;
		}
		auto _vp = _it->second;

		// construct gpp
		_main_graphics_pipeline = std::make_unique<gl_graphics_pipeline>();
		if (!_main_graphics_pipeline || !_main_graphics_pipeline->load(_vp))
		{
			return false;
		}
		
		{
			_main_graphics_pipeline->rasterizer.enable_multisample = true;
			_main_graphics_pipeline->rasterizer.enable_sample_shading = true;
			_main_graphics_pipeline->rasterizer.sample_shading_rate = 1.1f;
			_main_graphics_pipeline->rasterizer.enable_line_smooth = true;
			_main_graphics_pipeline->rasterizer.enable_polygon_smooth = true;
			_main_graphics_pipeline->rasterizer.enable_polygon_offset_fill = true;
			_main_graphics_pipeline->rasterizer.cull_face.enable = false;

			_main_graphics_pipeline->fragment_preprocessor.scissor_test.enable = false;
			_main_graphics_pipeline->fragment_preprocessor.scissor_test.rectangle.x = 100;
			_main_graphics_pipeline->fragment_preprocessor.scissor_test.rectangle.y = 100;
			_main_graphics_pipeline->fragment_preprocessor.scissor_test.rectangle.width = 900;
			_main_graphics_pipeline->fragment_preprocessor.scissor_test.rectangle.height = 900;
			
			_main_graphics_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
			_main_graphics_pipeline->fragment_preprocessor.multisample_fragment_operations.inverted = true;
			_main_graphics_pipeline->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
			_main_graphics_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

			_main_graphics_pipeline->fragment_postprocessor.stencil_test.enable = false;
			_main_graphics_pipeline->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
			_main_graphics_pipeline->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
			_main_graphics_pipeline->fragment_postprocessor.depth_test.enable = false;
			_main_graphics_pipeline->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
			_main_graphics_pipeline->fragment_postprocessor.enable_framebuffer_srgb = false; // if true -> more lighter
			_main_graphics_pipeline->fragment_postprocessor.enable_dither = true;
		}
		
		auto _fb = _main_graphics_pipeline->invoke_feedback();
		if (_fb)
		{
		}

		auto _rt = _main_graphics_pipeline->invoke_render_target();
		if (!_rt) return false;
		_rt->set_default();

		_attached = true;
		return true;
	}
	return false;
}

bool gl_shader_toy_renderer::hibernate() noexcept
{
	_awake = false;
	return true;
}

void gl_shader_toy_renderer::render(float delta_time) noexcept
{
	if (_attached && _awake)
	{
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
#ifdef _DEBUG
		if (!_main_graphics_pipeline) throw std::exception("mesh pipeline must not be null");
#endif
		_acc_time += delta_time * 2;

		_main_graphics_pipeline->enable();
		glUniform1f(glGetUniformLocation(_main_graphics_pipeline->invoke_program()->get_handle(), "iTime"), _acc_time);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		_main_graphics_pipeline->draw_with_query(gl_query(gl_query_type::TIMESTAMP),
			[](gl_graphics_pipeline& pipeline)
			{
				
			}
		);

		_main_graphics_pipeline->disable();
	}
}

bool gl_shader_toy_renderer::wake() noexcept
{
	_awake = true;
	return false;
}

bool gl_shader_toy_renderer::detach() noexcept
{
	if(_attached)
	{
		_main_graphics_pipeline.release();
		_attached = false;
		return true;
	}
	return false;
}

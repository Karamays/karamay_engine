#pragma once
#include "gl_renderer.h"

class gl_pbr_std_renderer : public gl_renderer
{

	virtual void construct() override
	{
		// global resource
		{
			std::shared_ptr<gl_default_framebuffer> final_framebuffer;
			std::shared_ptr<gl_framebuffer> framebuffer0;
			std::shared_ptr<gl_framebuffer> framebuffer1;
			std::shared_ptr<gl_framebuffer> framebuffer2;

			auto program0 = std::make_shared<gl_program>();
			auto program1 = std::make_shared<gl_program>();
			auto program2 = std::make_shared<gl_program>();


			_final_framebuffer = final_framebuffer;
			_framebuffers_map.emplace("framebuffer0", framebuffer0);
			_framebuffers_map.emplace("framebuffer1", framebuffer1);
			_framebuffers_map.emplace("framebuffer2", framebuffer2);

			_programs_map.emplace("geom_handler", program0);
			_programs_map.emplace("deferred_lighting_handler", program1);
			_programs_map.emplace("post_handler", program2);
		}

		// subpass 0
		{
			auto program0 = _programs_map.find("geom_handler")->second;
			if (program0) {
				program0->construct({ "PBRMesh.vert", "PBRMesh.tesc", "PBRMesh.tese", "PBRMesh.geom", "PBRMesh.frag" });
			}
		}
	}


	virtual void initialize() override
	{
		// update and call program0
		{
			auto program0 = _programs_map.find("geom_handler")->second;
			if (program0)
			{
				{
					program0->set_framebuffer(_framebuffers_map.find("framebuffer0")->second);
				}

				{
					program0->set_vertex_array(std::make_shared<gl_vertex_array>());
					program0->set_element_array_buffer(std::make_shared<gl_buffer>());
				}

				{
					program0->set_uniform_matrix_4x4f("model_matrix", glm::fmat4(0.0f));
					program0->set_uniform_matrix_4x4f("view_matrix", glm::fmat4(0.0f));
					program0->set_uniform_matrix_4x4f("projection_matrix", glm::fmat4(0.0f));
					program0->set_uniform_3f("base_color", { 0.0f, 0.2f, 0.5f });
					program0->set_uniform_1d("scale", glm::dvec1(2.0));
				}

				{
					program0->set_texture_2d(0, "albedo_map", std::make_shared<gl_texture_2d>());
					program0->set_texture_2d(1, "metallic_map", std::make_shared<gl_texture_2d>());
					program0->set_texture_2d(2, "roughness_map", std::make_shared<gl_texture_2d>());
					program0->set_texture_2d(3, "normal_map", std::make_shared<gl_texture_2d>());
					program0->set_texture_2d(4, "displacement_map", std::make_shared<gl_texture_2d>());
				}

				{
					program0->set_uniform_buffer(0, "material", std::make_shared<gl_buffer>());
					program0->set_uniform_buffer(1, "light", std::make_shared<gl_buffer>());

				}

				{
					program0->set_shader_storage_buffer(0, "cached_light_volume", std::make_shared<gl_buffer>());
				}

				{
					program0->set_atomic_count_buffer(0, std::make_shared<gl_buffer>());
				}

				program0->enable();
				// call draw commands


				// end draw commands
				program0->disable();
			}

		}
	}

	virtual void render(std::float_t delta_time) override
	{

	}


};


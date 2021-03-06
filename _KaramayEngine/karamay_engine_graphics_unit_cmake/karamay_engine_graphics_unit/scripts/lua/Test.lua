---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by Regicide Ji.
--- DateTime: 2021/9/17 23:17
---

--gl_renderer_clazz = {
--    __call = function(t, ...)
--        print("new instance")
--        return setmetatable({}, gl_renderer_clazz)
--    end,
--
--    __index = {
--        pipelines = {
--            "vertex_processing_pipeline",
--            "deferred_lighting_pipeline",
--        },
--
--        test = function(...)
--            print(...)
--        end
--    },
--
--    __newindex = nil,
--
--    __tostring = function(t)
--        return "gl_renderer"
--    end,
--
--}
--
--gl_renderer = setmetatable({}, gl_renderer_clazz)
--
--local renderer0 = gl_renderer("/renderers/static_mesh_renderer")
--local renderer1 = gl_renderer("/renderers/static_mesh_renderer")
--
--print(renderer0)
--print(renderer1)

--gl_renderer = setmetatable({}, gl_renderer_clazz);

--local test = {
--    __index = self,
--
--    TestGetA = function()  end,
--    TestSetA = function()  end,
--    __gc = function()  end
--}
--
--local testInstance = setmetatable({"userdata"}, test)


--local test1 = CTest()
--local test2 = CTest()
--print('test2 value is : ' .. test2:get())
--test2:set()
--local test3 = test1:finish(test2)
--print('test2 value is : ' .. test2:get())
--print('test3 value is : ' .. test3:get())
--
--
--
--local gl_static_mesh_renderer = gl_renderer()
--
--if gl_static_mesh_renderer:load("/static_mesh_renderer") then
--	print("xxxxxx")
--end
--
--
--
--function gl_static_mesh_renderer:build( ... )
--
--	local _graphics_pipeline = gl_graphics_pipeline()
--	_graphics_pipeline:load("/static_mesh_renderer")
--	_graphics_pipeline:set_enable_depth_test(true)
--	_graphics_pipeline:set_enable_stencil_test(false)
--	_graphics_pipeline:set_enable_scissor_test(false)
--	_graphics_pipeline:set_blend_func()
--
--	local _compute_pipeline = gl_compute_pipeline()
--	_compute_pipeline:load("/static_mesh_renderer")
--end
--
--function gl_static_mesh_renderer:render( delta_time )
--	local _compute_pipeline = self.renderer_builder.compute_pipeline("mat_pipeline")
--	local _graphics_pipeline = self.renderer_builder.graphics_pipeline("mesh_pipeline")
--
--	if(delta_time < 0) then return end
--
--	_compute_pipeline:enable()
--
--	for i=1,10 do
--		_compute_pipeline:dispatch(i, i+1, i+3)
--	end
--
--	for k,v in pairs(table_name) do
--	print(k,v)
--	end
--
--	for i,v in ipairs(table_name) do
--	print(i,v)
--    end
--
--	_compute_pipeline:disable()
--
--	_graphics_pipeline:enable()
--	for i, v in ipairs() do
--		_graphics_pipeline:syncable_draw_arrays(0, 1024)
--	end
--	_graphics_pipeline:disable()
--
--end


local test = CTest()
test:set(14)
local x = test:get()

local t =
{
	1,2,3,4,5,6,7
}

test:set_array(t)

local at = test:get_array()

for i, v in pairs(at) do
	print(i..","..v)
end




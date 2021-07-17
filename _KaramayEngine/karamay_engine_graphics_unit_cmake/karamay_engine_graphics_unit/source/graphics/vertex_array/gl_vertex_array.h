#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include <utility>

#include "graphics/glo/gl_object.h"
#include "graphics/type/glsl.h"

class gl_buffer;

class gl_attribute_component
{
public:
    enum class type : GLenum
    {
        UNKNOWN = 0,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE
    };

    static std::string to_string(type component_type)
    {
        switch(component_type)
        {
            case type::INT: return "INT";
            case type::UINT: return "UINT";
            case type::FLOAT: return "FLOAT";
            case type::DOUBLE: return "DOUBLE";
            default: return "UNKNOWN";
        }
    }

    static type to_enum(const std::string& component_type)
    {
        if(component_type == "INT") return type::INT;
        if(component_type == "UINT") return type::UINT;
        if(component_type == "FLOAT") return type::FLOAT;
        if(component_type == "DOUBLE") return type::DOUBLE;
        return type::UNKNOWN;
    }

    static GLenum to_GLenum(type component_type)
    {
        return static_cast<GLenum>(component_type);
    }

    static std::uint32_t get_size(type component_type)
    {
        switch (component_type) {
            case type::INT: return sizeof(std::int32_t);
            case type::UINT: return sizeof(std::uint32_t);
            case type::FLOAT: return sizeof(std::float_t);
            case type::DOUBLE: return sizeof(std::double_t);
            default: return 0;
        }
    }
};

class gl_attribute
{
    enum class type
    {
        UINT,UVEC2,UVEC3,UVEC4,
        INT,IVEC2,IVEC3,IVEC4,
        FLOAT,VEC2,VEC3,VEC4,
        DOUBLE,DVEC2,DVEC3,DVEC4,

        MAT2X2,MAT2X3,MAT2X4,MAT3X2,MAT3X3,MAT3X4,MAT4X2,MAT4X3,MAT4X4,
        DMAT2X2,DMAT2X3,DMAT2X4,DMAT3X2,DMAT3X3,DMAT3X4,DMAT4X2,DMAT4X3,DMAT4X4,
    };

    static std::pair<gl_attribute_component::type, std::uint32_t> get_component_layout(gl_attribute::type attribute_type)
    {
        switch (attribute_type) {

            case type::UINT:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::UVEC2:
                return std::make_pair(gl_attribute_component::type::UINT, 2);
            case type::UVEC3:
                return std::make_pair(gl_attribute_component::type::UINT, 3);
            case type::UVEC4:
                return std::make_pair(gl_attribute_component::type::UINT, 4);
            case type::INT:
                return std::make_pair(gl_attribute_component::type::INT, 1);
            case type::IVEC2:
                return std::make_pair(gl_attribute_component::type::INT, 2);
            case type::IVEC3:
                return std::make_pair(gl_attribute_component::type::INT, 3);
            case type::IVEC4:
                return std::make_pair(gl_attribute_component::type::INT, 4);
            case type::FLOAT:
                return std::make_pair(gl_attribute_component::type::FLOAT, 1);
            case type::VEC2:
                return std::make_pair(gl_attribute_component::type::FLOAT, 2);
            case type::VEC3:
                return std::make_pair(gl_attribute_component::type::FLOAT, 3);
            case type::VEC4:
                return std::make_pair(gl_attribute_component::type::FLOAT, 4);
            case type::DOUBLE:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 1);
            case type::DVEC2:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 2);
            case type::DVEC3:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 3);
            case type::DVEC4:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 4);
            case type::MAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
        }
    }
};


struct gl_attribute_descriptor
{
    std::string type_name;
    std::string attribute_name;
};

struct gl_instance_attribute_descriptor
{
    std::string type_name;
    std::string attribute_name;
    std::uint32_t divisor;
};

struct gL_attribute_list_anchor
{
    std::string attribute_name;
    std::uint32_t attributes_count;
    std::int64_t offset;
    std::int64_t size;
    const glsl_transparent_clazz* _clazz;
};

/*
 * Dynamic Storage : if required capacity is not enough,
 *
 *
 * [          ] [vertex0] [vertex1] [vertex2] [vertexN]
 * [attribute0] [       ] [       ] [      ] [.......]
 * [attribute1] [       ] [       ] [      ] [.......]
 * [attribute2] [       ] [       ] [      ] [.......]
 * [attributeN] [       ] [       ] [      ] [.......]
 *
 *
 *
 * */
class gl_vertex_array final : public gl_object
{

public:

    gl_vertex_array(const std::vector<gl_attribute_descriptor>& attribute_descriptors, const std::vector<gl_instance_attribute_descriptor>& instance_attribute_descriptors) :
                    _vertices_count(0),
                    _instances_count(0),
                    _memory_size(0)
    {
        glCreateVertexArrays(1, &_handle);

        _generate_attributes_layout();

    }

    ~gl_vertex_array() override;

public:

    /*
     * Range of type [bytes]
     * Anchor way [bytes offset, bytes size]
     * */
    void update(std::int64_t offset, std::uint8_t* byte_stream, std::int64_t byte_stream_size) noexcept;

    /*
     * Range of type [bytes]
     * Anchor way [attribute_name, bytes offset]
     * */
    void update(const std::string& attribute_name,
                std::int64_t offset, std::uint8_t* byte_stream, std::int64_t byte_stream_size) noexcept;

public:

    /*
     * Anchor [attribute_name, attribute_index] -> Range [specific attribute collection]
     * Update [GLSL_TRANSPARENT_T]
     * */
    template<typename GLSL_TRANSPARENT_T>
    void update(const std::string& attribute_name, std::uint32_t attribute_index, std::vector<GLSL_TRANSPARENT_T>& values) noexcept
    {

    }

public:

    void update(){}

public:

    void reallocate_attributes(std::uint32_t new_vertices_count);

    void reallocate_instance_attributes(const std::vector<std::pair<std::string, std::uint32_t>>&);

private:

    std::uint32_t _vertices_count, _instances_count;

    std::int64_t _memory_size;

    std::shared_ptr<gl_buffer> _buffer;

    std::unordered_map<std::string, gL_attribute_list_anchor> _attributes_layout;

private:

    void _generate_attributes_layout()
    {

    }

    void _set_vertex_pointers(gl_attribute_component::type attribute_component_type, std::uint32_t  index, std::uint32_t components_count,std::uint32_t attribute_size, std::uint32_t offset);

    void _reallocate();

    std::uint8_t _check_memory_layout(const std::pair<std::uint32_t, std::uint32_t>& memory_layout);

    void _update_attribute(const std::string& attribute_name, std::uint32_t vertex_index, const std::vector<std::uint8_t>& stream);

    void _bind_buffer();

    void _unbind_buffer();

public:

	void bind();

	void unbind();

	void enable_pointers();

	void disable_pointers();

public:
	// default false
	bool is_pointer_enabled(std::uint32_t index);
	// default is 4
	std::uint32_t get_attribute_components_num(std::uint32_t index);
	// default is GL_FLOAT
	std::string get_attribute_component_type(std::uint32_t index);

	void* get_mapped_data();

	[[nodiscard]] const std::int32_t get_size() const;


private:

    template<typename T>
    gl_attribute_component::type _get_component_type()
    {
        return gl_attribute_component::type::UNKNOWN;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::i32vec4::value_type>()
    {
        return gl_attribute_component::type::INT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::ui32vec4::value_type>()
    {
        return gl_attribute_component::type::UINT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::f32vec4::value_type>()
    {
        return gl_attribute_component::type::FLOAT;
    }

    template<>
    gl_attribute_component::type _get_component_type<typename glv::f64vec4::value_type>()
    {
        return gl_attribute_component::type::DOUBLE;
    }


};

#endif

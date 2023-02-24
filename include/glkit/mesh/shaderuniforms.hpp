#pragma once

#include <glkit/core/shaderuniform.hpp>


namespace glkit::mesh::shader_config
{

class ShaderUniformHandler_c
{
public:
    core::Uniform_Vector4f_c Color;

    core::Uniform_Matrix4f_c Model;
    core::Uniform_Matrix4f_c Camera;
    core::Uniform_Matrix4f_c Projection;
    
private:
    inline ShaderUniformHandler_c() :
        Color("myColor"),
        Model("model"),
        Camera("view"),
        Projection("projection")
    {}

};

} // namespace glkit::mesh::shader_config
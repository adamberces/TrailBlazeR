#pragma once

#include <memory>
#include <vector>


// Forward declarations for pointer types
class ShaderProgram_c;
class VertexArrayObject_c;
struct ShaderSourceList_s;

class GLMesh_i
{
    std::unique_ptr<ShaderProgram_c> ShaderProgram;
    std::unique_ptr<VertexArrayObject_c> VertexArrayObject;

    unsigned int NumberOfElements;

protected:
    virtual void constructVertexData() = 0;

    virtual void draw()
    {
        sp->use();
        vao->bind();
        glDrawElements(GL_TRIANGLES, NumberOfElements, GL_UNSIGNED_INT, 0);
    }

    virtual void constructVertexArrayObject
        (std::vector<float>& vertices, std::vector<unsigned int>& indices)
    {
        VertexArrayObject = std::make_uniqe VertexArrayObject_c<float>();
        VertexArrayObject->copyVertexData(vertices, indices);
        VertexArrayObject->setVertexAttribute(0, 3);
    }

    virtual void constructShaderProgram(ShaderSourceList_s& ssl)
    {
        ShaderSourceList_s test;
        test.FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl";
        test.VertexShaderPath = "./assets/shaders/v_simple.glsl";
        ShaderProgram = new ShaderProgram_c(test);
    }
 
    GLMesh_i(ShaderSourceList_s* shaderSourceList) :
        ShaderProgram_c(nullptr),
        VertexArrayObject_c(nullptr),
        NumberOfElements(0)
    {
        constructShaderProgram(shaderSourceList);
        constructVertexArrayObject
    }
};
#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

#include <glkit/core/globject.hpp>


namespace glkit::core::buffers
{

/////////////////////////////////////////////////////////////////////////////////////////
// Type safe wrappers of OpenGL array buffer types and usage

enum class ArrayBufferType_e
{
    ArrayBuffer = GL_ARRAY_BUFFER,
    ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
};

enum class ArrayBufferUsage_e
{
    StaticDraw = GL_STATIC_DRAW,
    DynamicDraw = GL_DYNAMIC_DRAW
};


/////////////////////////////////////////////////////////////////////////////////////////
// Helper function
// Sanity check: test if we have a vertex array object bound
void checkVertexArrayBinding()
{
    int vao_id = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao_id);
    if (vao_id == 0)
    {
        throw std::runtime_error("ArrayBuffer_c error: please bind a Vertex Array Object"
            "before binding an Array Buffer!");
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Class representing a GL Array Buffer
// Designed as per the RAII principles, glDeleteBuffers is automatically called to free
// resources when the object lifetime is over.

template<typename BufferDataType>
class ArrayBuffer_c : public GLObject_i
{
    ArrayBufferType_e Type;
    ArrayBufferUsage_e Usage;
    
public:
    inline void bindAndCopy(std::vector<BufferDataType> data)
    {
        checkVertexArrayBinding();

        // Bind buffer to the current VAO and copy data
        glBindBuffer(static_cast<unsigned int>(Type), Id);
        glBufferData(static_cast<unsigned int>(Type),
                     data.size() * sizeof(BufferDataType), data.data(),
                     static_cast<unsigned int>(Usage));
    }

    // Binds and generates a buffer to be used with glBufferSubData
    inline void bindEmptyBuffer(std::size_t data_count)
    {
        checkVertexArrayBinding();

        // Bind buffer to the current VAO and copy data
        glBindBuffer(static_cast<unsigned int>(Type), Id);
        glBufferData(static_cast<unsigned int>(Type),
                     data_count * sizeof(BufferDataType), NULL,
                     static_cast<unsigned int>(Usage));
    }

    inline void bindAndCopySubData(std::vector<BufferDataType> data)
    {
        glBindBuffer(static_cast<unsigned int>(Type), Id);
        glBufferSubData(static_cast<unsigned int>(Type), 0
                     data.size() * sizeof(BufferDataType), data.data());
        glBindBuffer(static_cast<unsigned int>(Type), 0);
    }

    inline void unbind() const
    {
        glBindBuffer(static_cast<unsigned int>(Type), 0); 
    }

    ArrayBuffer_c
        (ArrayBufferType_e type, ArrayBufferUsage_e usage) :
        Type(type),
        Usage(usage)
    {
        glGenBuffers(1, &Id);
    }

    ~ArrayBuffer_c()
    {
        glDeleteBuffers(1, &Id);
    }
};

} // namespace glkit::core::buffers
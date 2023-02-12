#pragma once

#include "globject.hpp"

#include <vector>
#include <algorithm>


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
// Class representing a GL Array Buffer
// Designed as per the RAII principles, glDeleteBuffers is automatically called to free
// resources when the object lifetime is over.

template<typename BufferDataType>
class ArrayBuffer_c : public GLObject_i
{
    ArrayBufferType_e Type;
    ArrayBufferUsage_e Usage;

public:
    void bindAndCopy(std::vector<BufferDataType> data)
    {
        // Sanity check: test if we have a vertex array object bound
        int vao_id = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao_id);
        if (vao_id == 0)
        {
            throw std::runtime_error("Please bind a Vertex Array Object"
                "before binding an Array Buffer!");
        }

        // Bind buffer to the current VAO and copy data
        glBindBuffer(static_cast<unsigned int>(Type), Id);
        glBufferData(static_cast<unsigned int>(Type),
                     data.size() * sizeof(BufferDataType), data.data(),
                     static_cast<unsigned int>(Usage));
    }

    void unbind() const
    {
        glBindBuffer(static_cast<unsigned int>(Type), 0); 
    }

    explicit ArrayBuffer_c
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
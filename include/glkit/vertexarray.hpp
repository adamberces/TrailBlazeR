#pragma once

#include "globject.hpp"
#include "arraybuffer.hpp"

#include <vector>
#include <memory>


/////////////////////////////////////////////////////////////////////////////////////////
// Helper metafunctions for convient use of glVertexAttribPointer's type parameter

template<typename T>
struct buffer_data_type_traits
{};

template<>
struct buffer_data_type_traits<float>
{
    static constexpr int type = GL_FLOAT;
};

template<>
struct buffer_data_type_traits<int>
{
    static constexpr int type = GL_INT;
};

template<>
struct buffer_data_type_traits<unsigned int>
{
    static constexpr int type = GL_UNSIGNED_INT;
};


/////////////////////////////////////////////////////////////////////////////////////////
// Class representing a GL Vetrex Array Object
// Designed as per the RAII principles, glDeleteVertexArrays is automatically called
// to free resources when the object lifetime is over.

template<typename BufferDataType>
class VertexArrayObject_c : public GLObject_i
{
    template<typename T>
    using ArrayBufferPtr_t = std::unique_ptr<ArrayBuffer_c<T>>;

    template<typename T>
    using ArrayBufferPtrContainer_t = std::vector<ArrayBufferPtr_t<T>>;

    ArrayBufferPtrContainer_t<BufferDataType> VertexBuffers;
    ArrayBufferPtrContainer_t<unsigned int> ElementBuffers;

public:
    inline void copyVertexData
        (std::vector<BufferDataType>& vertexData,
         std::vector<unsigned int>& elementData)
    {
        bind();

        VertexBuffers.emplace_back
            (new ArrayBuffer_c<BufferDataType>
             (ArrayBufferType_e::ArrayBuffer,
              ArrayBufferUsage_e::StaticDraw));
        VertexBuffers.back()->bindAndCopy(vertexData);

        ElementBuffers.emplace_back
            (new ArrayBuffer_c<unsigned int>
             (ArrayBufferType_e::ElementArrayBuffer,
              ArrayBufferUsage_e::StaticDraw));
        ElementBuffers.back()->bindAndCopy(elementData);

        unbind();
    }

    // Note, for convience, currently only tightly packed arrays
    // are accepted, so we only need to set the index and the size
    inline void setVertexAttribute(size_t index, size_t size)
    {
        bind();
        glVertexAttribPointer(index, size,
            buffer_data_type_traits<BufferDataType>::type,
            GL_FALSE, size * sizeof(BufferDataType), (void*)0);
        glEnableVertexAttribArray(index);
        unbind();
    }

    inline void bind() const
    {
        glBindVertexArray(Id);
    }

    inline void unbind() const
    {
        glBindVertexArray(0);
    }

    VertexArrayObject_c()
    {
        glGenVertexArrays(1, &Id);
    }

    ~VertexArrayObject_c()
    {
        glDeleteVertexArrays(1, &Id);
    }
};

#pragma once

#include "globject.hpp"
#include "arraybuffer.hpp"

#include <vector>
#include <memory>


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
    using ArrayBufferPtrContainer_t =  std::vector<ArrayBufferPtr_t<T>>;

    ArrayBufferPtrContainer_t<BufferDataType> VertexBuffers;
    ArrayBufferPtrContainer_t<unsigned int> ElementBuffers;
    
public:
    void bindAndCopy
        (std::vector<BufferDataType>& vertexData,
         std::vector<unsigned int>& elementData)
    {
        glBindVertexArray(Id);
    }

    void unbind() const
    {
        glBindVertexArray(0);
    }

    ArrayBuffer_c()
    {
        glGenVertexArrays(1, &Id);
    }

    ~ArrayBuffer_c()
    {
        glDeleteVertexArrays(1, &Id);
    }
};

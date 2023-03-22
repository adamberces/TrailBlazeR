#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include <glkit/core/globject.hpp>
#include <glkit/core/buffers/arraybuffer.hpp>


namespace glkit::core::buffers
{

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
// Class representing a GL Vertex Array Object
// Designed as per the RAII principles, glDeleteVertexArrays is automatically called
// to free resources when the object lifetime is over.

template<typename BufferDataType>
class DynamicVertexArrayObject_c : public StaticVertexArrayObject_c
{
    void allocateBuffer(std::size_t data_count, ArrayBufferType_e type)
    {
        bind();

        if (data_count == 0)
        {
            throw std::runtime_error("DynamicVertexArrayObject_c::allocateVertexBuffer: "
                "data_count can't be zero!");
        }

        VertexBuffers.emplace_back
            (new ArrayBuffer_c<BufferDataType>
             (type, ArrayBufferUsage_e::DynamicDraw));
        VertexBuffers.back()->bindEmptyBuffer(data_count);
        
        unbind();
    }

public:
    void allocateVertexBuffer(std::size_t data_count)
    {
       allocateBuffer(ArrayBufferType_e::ArrayBuffer);
    }
    
    void allocateElementArrayBuffer(std::size_t data_count)
    {
        allocateBuffer(ArrayBufferType_e::ElementArrayBuffer);
    }

    virtual inline void copyVertexData 
        (const std::vector<BufferDataType>& vertexData,
         const std::vector<unsigned int>& elementData) override
    {
        bind();

        if (vertexData.empty())
        {
            throw std::runtime_error("StaticVertexArrayObject_c::copyVertexData: "
                "vertexData can't be empty!");
        }

        VertexBuffers.back()->bindAndCopySubData(vertexData);

        if (!(ElementBuffers.empty()))
        {
            ElementBuffers.back()->bindAndCopySubData(elementData);
        }
        
        unbind();
    }
};

template<typename BufferDataType>
class StaticVertexArrayObject_c : public GLObject_i
{
protected:
    template<typename T>
    using ArrayBufferPtr_t = std::unique_ptr<ArrayBuffer_c<T>>;

    template<typename T>
    using ArrayBufferPtrContainer_t = std::vector<ArrayBufferPtr_t<T>>;

    ArrayBufferPtrContainer_t<BufferDataType> VertexBuffers;
    ArrayBufferPtrContainer_t<unsigned int> ElementBuffers;

public:
    // Copies a pair of vertex and element position data to the
    // GPU and assigns them to the current Vertex Array Object
    virtual inline void copyVertexData
        (const std::vector<BufferDataType>& vertexData,
         const std::vector<unsigned int>& elementData)
    {
        bind();

        if (vertexData.empty())
        {
            throw std::runtime_error("StaticVertexArrayObject_c::copyVertexData: "
                "vertexData can't be empty!");
        }
        VertexBuffers.emplace_back
            (new ArrayBuffer_c<BufferDataType>
             (ArrayBufferType_e::ArrayBuffer,
              ArrayBufferUsage_e::StaticDraw));
        VertexBuffers.back()->bindAndCopy(vertexData);

        if (!(elementData.empty()))
        {
            ElementBuffers.emplace_back
                (new ArrayBuffer_c<unsigned int>
                (ArrayBufferType_e::ElementArrayBuffer,
                ArrayBufferUsage_e::StaticDraw));
            ElementBuffers.back()->bindAndCopy(elementData);
        }
        
        unbind();
    }

    // Stores vertex attributes in the Vertex Array Object
    // for the given location
    inline void setVertexAttribute
        (size_t location, size_t component_count,
         size_t stride, size_t offset)
    {
        bind();
        glVertexAttribPointer(location, component_count,
            buffer_data_type_traits<BufferDataType>::type,
            GL_FALSE,
            stride * sizeof(BufferDataType),
            (void*)(offset * sizeof(BufferDataType)));
        glEnableVertexAttribArray(location);
        unbind();
    }

    // Overload for convience, when no additional offset is needed
    inline void setVertexAttribute
        (size_t location, size_t component_count, size_t stride)
    {
        setVertexAttribute(location, component_count, stride, 0);
    }


    // Overload for convience, when the struct is tightly packed
    // and also no additional offset is needed
    inline void setVertexAttribute(size_t location, size_t component_count)
    {
        setVertexAttribute
            (location, component_count,
             component_count);
    }

    inline void bind() const
    {
        glBindVertexArray(Id);
    }

    inline void unbind() const
    {
        glBindVertexArray(0);
    }

    inline StaticVertexArrayObject_c()
    {
        glGenVertexArrays(1, &Id);
    }

    inline ~StaticVertexArrayObject_c()
    {
        glDeleteVertexArrays(1, &Id);
    }
};

} // namespace glkit::core::buffers

#include <glkit/core/buffers/vertexarray.hpp>


namespace glkit::core::buffers
{

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class representing a GL Vertex Array Object, to be used dynamically (copies calls glBufferSubData)
/// Designed as per the RAII principles, glDeleteVertexArrays is automatically called
/// to free resources when the object lifetime is over.

template<typename BufferDataType>
class DynamicVertexArrayObject_c : public StaticVertexArrayObject_c<BufferDataType>
{
    void allocateBuffer(std::size_t data_count, ArrayBufferType_e type)
    {
        this->bind();

        if (data_count == 0)
        {
            throw std::runtime_error("DynamicVertexArrayObject_c::allocateVertexBuffer: "
                "data_count can't be zero!");
        }

        this->VertexBuffers.emplace_back
            (new ArrayBuffer_c<BufferDataType>
             (type, ArrayBufferUsage_e::DynamicDraw));
        this->VertexBuffers.back()->bindEmptyBuffer(data_count);
        
        this->unbind();
    }

public:
    void allocateVertexBuffer(std::size_t data_count)
    {
        allocateBuffer(data_count, ArrayBufferType_e::ArrayBuffer);
    }
    
    void allocateElementArrayBuffer(std::size_t data_count)
    {
        allocateBuffer(data_count, ArrayBufferType_e::ElementArrayBuffer);
    }

    virtual inline void copyVertexData 
        (const std::vector<BufferDataType>& vertexData,
         const std::vector<unsigned int>& elementData) override
    {
        this->bind();

        if (vertexData.empty())
        {
            throw std::runtime_error("StaticVertexArrayObject_c::copyVertexData: "
                "vertexData can't be empty!");
        }

        this->VertexBuffers.back()->bindAndCopySubData(vertexData);

        if (!(this->ElementBuffers.empty()))
        {
            this->ElementBuffers.back()->bindAndCopySubData(elementData);
        }
        
       this->unbind();
    }
};

} // namespace glkit::core::buffers

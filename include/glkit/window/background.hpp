#pragma once

#include <string>
#include <glkit/mesh/glkmesh.hpp>


namespace glkit::window
{

/////////////////////////////////////////////////////////////////////////////////////////
// A background object is basically a special case of a GLKMesh, which will result in
// a fixed, 2D rectangle to be rendered behind the whole scene

class GLKBackgound_c : public mesh::GLKMesh_i
{      
    GLuint TextureID;
    std::string FileName;

public:
    void activateTexture() const;
    void draw() const override;

private:
    std::pair<GLKMesh_i::vertex_vector_t,
        GLKMesh_i::element_vector_t> constructVertexData();

    virtual void initialize(const vertex_vector_t&,
        const element_vector_t&) override;

public:
    GLKBackgound_c(std::string fileName);
};

} // namespace glkit::window

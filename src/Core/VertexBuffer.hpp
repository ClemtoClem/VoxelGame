#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <GL/glew.h>

class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    ~VertexBuffer() {
        glDeleteBuffers(1, &_rendererID);
    }

    void bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    }

    void unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    unsigned int _rendererID;
};

#endif // VERTEX_BUFFER_HPP

#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include "VertexBuffer.hpp"

class VertexArray {
public:
    VertexArray() {
        glGenVertexArrays(1, &_rendererID);
    }

    ~VertexArray() {
        glDeleteVertexArrays(1, &_rendererID);
    }

    void bind() const {
        glBindVertexArray(_rendererID);
    }

    void unbind() const {
        glBindVertexArray(0);
    }

    void addBuffer(const VertexBuffer& vb, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const {
        bind();
        vb.bind();
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

private:
    unsigned int _rendererID;
};

#endif // VERTEX_ARRAY_HPP

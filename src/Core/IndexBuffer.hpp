#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include <GL/glew.h>

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* data, unsigned int count)
        : _count(count) {
        glGenBuffers(1, &_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    ~IndexBuffer() {
        glDeleteBuffers(1, &_rendererID);
    }

    void bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    }

    void unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline unsigned int getCount() const { return _count; }

private:
    unsigned int _rendererID;
    unsigned int _count;
};

#endif // INDEX_BUFFER_HPP

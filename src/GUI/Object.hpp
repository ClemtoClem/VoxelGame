#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <atomic>

class  Object {
public:
    /// Default constructor
    Object() { }

    /// Copy constructor
    Object(const Object &) : _refCount(0) {}

    /// Return the current reference count
    int getRefCount() const { return _refCount; };

    /// Increase the object's reference count by one
    void incRef() const { ++_refCount; }

    void decRef(bool dealloc = true) const noexcept;
protected:
    /**
     * @brief Virtual protected deconstructor.
     */
    virtual ~Object();
private:
    mutable std::atomic<int> _refCount { 0 };
};

template <typename T> class SharedPtr {
public:
    /// Create a ``nullptr``-valued reference
    SharedPtr() { }

    /// Construct a reference from a pointer
    SharedPtr(T *ptr) : _ptr(ptr) {
        if (_ptr)
            ((Object *) _ptr)->incRef();
    }

    /// Copy constructor
    SharedPtr(const SharedPtr &r) : _ptr(r._ptr) {
        if (_ptr)
            ((Object *) _ptr)->incRef();
    }

    /// Move constructor
    SharedPtr(SharedPtr &&r) noexcept : _ptr(r._ptr) {
        r._ptr = nullptr;
    }

    /// Destroy this reference
    ~SharedPtr() {
        if (_ptr)
            ((Object *) _ptr)->decRef();
    }

    /// Move another reference into the current one
    SharedPtr& operator=(SharedPtr&& r) noexcept {
        if (&r != this) {
            if (_ptr)
                ((Object *) _ptr)->decRef();
            _ptr = r._ptr;
            r._ptr = nullptr;
        }
        return *this;
    }

    /// Overwrite this reference with another reference
    SharedPtr& operator=(const SharedPtr& r) noexcept {
        if (_ptr != r._ptr) {
            if (r._ptr)
                ((Object *) r._ptr)->incRef();
            if (_ptr)
                ((Object *) _ptr)->decRef();
            _ptr = r._ptr;
        }
        return *this;
    }

    /// Overwrite this reference with a pointer to another object
    SharedPtr& operator=(T *ptr) noexcept {
        if (_ptr != ptr) {
            if (ptr)
                ((Object *) ptr)->incRef();
            if (_ptr)
                ((Object *) _ptr)->decRef();
            _ptr = ptr;
        }
        return *this;
    }

    /// Compare this reference with another reference
    bool operator==(const SharedPtr &r) const { return _ptr == r._ptr; }

    /// Compare this reference with another reference
    bool operator!=(const SharedPtr &r) const { return _ptr != r._ptr; }

    /// Compare this reference with a pointer
    bool operator==(const T* ptr) const { return _ptr == ptr; }

    /// Compare this reference with a pointer
    bool operator!=(const T* ptr) const { return _ptr != ptr; }

    /// Access the object referenced by this reference
    T* operator->() { return _ptr; }

    /// Access the object referenced by this reference
    const T* operator->() const { return _ptr; }

    /// Return a C++ reference to the referenced object
    T& operator*() { return *_ptr; }

    /// Return a const C++ reference to the referenced object
    const T& operator*() const { return *_ptr; }

    /// Return a pointer to the referenced object
    operator T* () { return _ptr; }

    /// Return a const pointer to the referenced object
    T* get() { return _ptr; }

    /// Return a pointer to the referenced object
    const T* get() const { return _ptr; }

    /// Check if the object is defined
    operator bool() const { return _ptr != nullptr; }
private:
    T *_ptr = nullptr;
};


#endif // OBJECT_HPP
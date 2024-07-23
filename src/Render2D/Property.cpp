#include "Property.hpp"
#include <stdexcept>

namespace Render2D {

Property::Property(const Value &value, std::function<void(const Value &)> updateFunction, Access access)
    : _value(value), _access(access), _modified(false), _updateFunction(updateFunction) {}

const Property::Value &Property::getValue() const {
    if (_access == Access::READ_WRITE || _access == Access::READ_ONLY) {
        return _value;
    } else {
        throw std::runtime_error("Property is write-only");
    }
}

void Property::setValue(const Property::Value &value) {
    if (_access == Access::READ_WRITE || _access == Access::WRITE_ONLY) {
        _value = value;
        _modified = true;
    } else {
        throw std::runtime_error("Property is read-only");
    }
}

bool Property::isReadable() const {
    return _access == Access::READ_ONLY || _access == Access::READ_WRITE;
}

bool Property::isWritable() const {
    return _access == Access::WRITE_ONLY || _access == Access::READ_WRITE;
}

bool Property::isModified() const {
    return _modified;
}

void Property::resetModified() {
    _modified = false;
}

void Property::update() {
    if (_updateFunction && _modified) {
        _updateFunction(_value);
        _modified = false;
    }
}

} // namespace Render2D

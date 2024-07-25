#include "Property.hpp"

// Constructor
template <typename T, typename ValueType>
Property<T, ValueType>::Property(const std::string &name, Access access, const ValueType &value)
    : _name(name), _access(access), _value(value) {}

// Destructor
template <typename T, typename ValueType>
Property<T, ValueType>::~Property() {}

// Get property name
template <typename T, typename ValueType>
const std::string &Property<T, ValueType>::getName() const {
    return _name;
}

// Get property value
template <typename T, typename ValueType>
ValueType &Property<T, ValueType>::getValue() {
    return _value;
}

// Set property value
template <typename T, typename ValueType>
void Property<T, ValueType>::setValue(ValueType value) {
    _value = value;
}

// Get access type
template <typename T, typename ValueType>
typename BaseProperty::Access Property<T, ValueType>::getAccess() const {
    return _access;
}

// Check if property is readable
template <typename T, typename ValueType>
bool Property<T, ValueType>::isReadable() const {
    return _access == Access::READ_ONLY || _access == Access::READ_WRITE;
}

// Check if property is writable
template <typename T, typename ValueType>
bool Property<T, ValueType>::isWritable() const {
    return _access == Access::WRITE_ONLY || _access == Access::READ_WRITE;
}

// Convert property to string
template <typename T, typename ValueType>
std::string Property<T, ValueType>::toString() const {
    std::stringstream ss;
    ss << _value;
    return ss.str();
}
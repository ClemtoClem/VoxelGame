#ifndef WIDGET_INL
#define WIDGET_INL

#include "Widget.hpp"

namespace Render2D {

template <typename T>
bool Widget::setProperty(const std::string &property_name, const T &value) {
    auto it = _properties.find(property_name);
    if (it != _properties.end()) {
        std::shared_ptr<Property<T, T>> prop = std::dynamic_pointer_cast<Property<T, T>>(it->second);
        if (prop) {
            prop->setValue(value);
            return true;
        }
    }
    return false;
}

template <typename T>
T &Widget::getProperty(const std::string &property_name) {
    auto it = _properties.find(property_name);
    if (it != _properties.end()) {
        std::shared_ptr<Property<T, T>> prop = std::dynamic_pointer_cast<Property<T, T>>(it->second);
        if (prop) {
            return prop->getValue();
        }
    }
    throw CustomException("Property not found or type mismatch");
}

template <typename T>
void Widget::createProperty(const std::string &name, BaseProperty::Access access, T &value) {
    auto property = std::make_shared<Property<T, T>>(name, access, value);
    _properties[name] = property;
}

} // namespace Render2D

#endif // WIDGET_INL

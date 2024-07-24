#include "Property.hpp"
#include "../Core/CustomException.hpp"

namespace Render2D {

Property::Property(const Value& default_value, Access access, std::function<void(const Value&)> setterFunction, std::function<Value(void)> getterFunction, bool authorize_reset)
 : _default_value(default_value), _access(access), _setterFunction(setterFunction), _getterFunction(getterFunction), _authorize_reset(authorize_reset) {
	if (isWritable() && _setterFunction == nullptr) {
		THROW_CUSTOM_EXCEPTION(Error, "Set function is null for write property");
	}
	if (isReadable() && _getterFunction == nullptr) {
		THROW_CUSTOM_EXCEPTION(Error, "Get function is null for read property");
	}
}

Property::Value Property::getValue() const {
    if (isReadable()) {
        return _getterFunction();
    } else {
        THROW_CUSTOM_EXCEPTION(Warning, "Property is write-only");
    }
}

void Property::setValue(const Property::Value &value) {
	if (isWritable()) {
		_setterFunction(value);
	} else {
		THROW_CUSTOM_EXCEPTION(Warning, "Property is read-only");
	}
}

void Property::reset() {
	if (_authorize_reset && isWritable()) {
		_setterFunction(_default_value);
	}
}

bool Property::isReadable() const {
	return _access == Access::READ_ONLY || _access == Access::READ_WRITE;
}

bool Property::isWritable() const {
	return _access == Access::WRITE_ONLY || _access == Access::READ_WRITE;
}

void Property::setParameters(const Value &default_value, Access access, std::function<void(const Value &)> setterFunction, std::function<Value(void)> getterFunction, bool authorize_reset) {
	_default_value = default_value;
	_access = access;
	_setterFunction = setterFunction;
	_getterFunction = getterFunction;
	_authorize_reset = authorize_reset;
	if (isWritable() && _setterFunction == nullptr) {
		THROW_CUSTOM_EXCEPTION(Error, "Set function is null for write property");
	}
	if (isReadable() && _getterFunction == nullptr) {
		THROW_CUSTOM_EXCEPTION(Error, "Get function is null for read property");
	}
}

void Property::setDefaultValue(const Value &default_value)
{
    _default_value = default_value;
}

void Property::setAccess(Access access) {
	_access = access;
}

void Property::setSetterFunction(std::function<void(const Value&)> setterFunction) {
	_setterFunction = setterFunction;
}

void Property::setGetterFunction(std::function<Value(void)> getterFunction) {
	_getterFunction = getterFunction;
}

} // namespace Render2D
#include "Property.hpp"
#include <stdexcept>

namespace Render2D {

Property::Property(const Value& default_value, Access access, std::function<void(const Value&)> setFunction, std::function<Value(const Value&)> getFunction)
 : _default_value(default_value), _access(access), _setFunction(setFunction), _getFunction(getFunction) {
	if (isWritable() && _setFunction == nullptr) {
		throw std::runtime_error("Set function is null for write property");
	}
	if (isReadable() && _getFunction == nullptr) {
		throw std::runtime_error("Get function is null for read property");
	}
}

const Property::Value &Property::getValue() const {
	if (_access == Access::READ_WRITE || _access == Access::READ_ONLY) {
		_getFunction(_value);
	} else {
		throw std::runtime_error("Property is write-only");
	}
}

void Property::setValue(const Property::Value &value) {
	if (_access == Access::READ_WRITE || _access == Access::WRITE_ONLY) {
		_setFunction(value);
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

} // namespace Render2D
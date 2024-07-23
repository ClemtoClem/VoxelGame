

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <variant>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "../Core/Color.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Font.hpp"
#include <functional>

namespace Render2D {

class Property {
public:
    enum class Access {
        READ_ONLY,
        WRITE_ONLY,
        READ_WRITE
    };
    using Value = std::variant<int, unsigned int, float, glm::vec2, Color, std::shared_ptr<Texture>, std::shared_ptr<Font>>;

    Property(const Value& value, std::function<void(const Value&)> updateFunction = nullptr, Access acces = Access::READ_WRITE)
        : _value(value), _acces(acces), _modified(false), _updateFunction(updateFunction) {}

    const Value& getValue() const {
        if (_acces == Access::READ_WRITE || _acces == Access::READ_ONLY) {
            return _value;
        } else {
            throw std::runtime_error("Property is read-only");
        }
    }

    void setValue(const Value& value) {
        if (_acces == Access::READ_WRITE || _acces == Access::WRITE_ONLY) {
            _value = value;
            _modified = true;
        } else {
            throw std::runtime_error("Property is write-only");
        }
    }

    bool isReadable() const {
        return (_acces == Access::READ_ONLY) || (_acces == Access::READ_WRITE);
    }

    bool isWritable() const {
        return (acces == Access::WRITE_ONLY) || (_acces == Access::READ_WRITE);
    }

    bool isModified() const {
        return _modified;
    }

    void resetModified() {
        _modified = false;
    }

    void update() {
        if (_updateFunction && _modified) {
            _updateFunction(_value);
            _modified = false;
        }
    }

private:
    Value _value;
    Access _acces;
    bool _modified;
    std::function<void(const Value&)> _updateFunction;
};

}

#endif // PROPERTY_HPP

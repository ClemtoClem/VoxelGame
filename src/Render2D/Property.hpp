

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <variant>
#include <string>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "../Core/Texture.hpp"
#include "../Core/Font.hpp"

namespace Render2D {

class Property {
public:
    enum class Access {
        READ_ONLY,
        WRITE_ONLY,
        READ_WRITE
    };

    using Value = std::variant<int, unsigned int, float, std::string, glm::vec2, glm::vec3, glm::vec4, TexturePtr, FontPtr>;

    Property(const Value& default_value, Access access, std::function<void(const Value&)> setterFunction, std::function<Value(void)> getterFunction = nullptr, bool authorize_reset = true);

    Value getValue() const;
    void setValue(const Value& value);
    void reset();

    bool isReadable() const;
    bool isWritable() const;

    void setParameters(const Value& default_value, Access access, std::function<void(const Value&)> setterFunction, std::function<Value(void)> getterFunction = nullptr, bool authorize_reset = true);
	void setDefaultValue(const Value& default_value);
	void setAccess(Access access);
	void setSetterFunction(std::function<void(const Value&)> setterFunction);
	void setGetterFunction(std::function<Value(void)> getterFunction);

private:
    Value _default_value;
    Access _access;
    std::function<void(const Value&)> _setterFunction;
    std::function<Value(void)> _getterFunction;
    bool _authorize_reset;
};

} // namespace Render2D

#endif // PROPERTY_HPP


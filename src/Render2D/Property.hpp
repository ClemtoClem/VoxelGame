

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <variant>
#include <string>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "../Core/Color.hpp"
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

    using Value = std::variant<int, unsigned int, float, glm::vec2, glm::vec3, glm::vec4, std::shared_ptr<Texture>, std::shared_ptr<Font>>;

    Property(const Value& value, std::function<void(const Value&)> updateFunction = nullptr, Access access = Access::READ_WRITE);

    const Value& getValue() const;
    void setValue(const Value& value);

    bool isReadable() const;
    bool isWritable() const;
    bool isModified() const;

    void resetModified();
    void update();

private:
    Value _value;
    Access _access;
    bool _modified;
    std::function<void(const Value&)> _updateFunction;
};

} // namespace Render2D

#endif // PROPERTY_HPP


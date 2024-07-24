

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

	Property(const Value& default_value, Access access, std::function<void(const Value&)> setFunction, std::function<Value(const Value&)> getFunction);

	const Value& getValue() const;
	void setValue(const Value& value);

	bool isReadable() const;
	bool isWritable() const;

private:
	Value _default_value;
	Access _access;
	std::function<void(const Value&)> _setFunction;
	std::function<Value(const Value&)> _getFunction;
};

} // namespace Render2D

#endif // PROPERTY_HPP

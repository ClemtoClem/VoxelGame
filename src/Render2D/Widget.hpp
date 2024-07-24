/**
 *  __    __ _     _            _   
 * / / /\ \ (_) __| | __ _  ___| |_ 
 * \ \/  \/ / |/ _` |/ _` |/ _ \ __|
 *  \  /\  /| | (_| | (_| |  __/ |_ 
 *   \/  \/ |_|\__,_|\__, |\___|\__|
 *                   |___/		  
 * 
 * @file Widget.cpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 */

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>
#include <memory>
#include <map>
#include <variant>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include "../Core/CustomException.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Font.hpp"
#include "../Core/Shader.hpp"
#include "Property.hpp"

namespace Render2D {

class Widget : public std::enable_shared_from_this<Widget> {
public:
	Widget(const std::string &name, std::shared_ptr<Widget> parent = nullptr);
	virtual ~Widget();
	
	const std::string &getName() const;

	virtual void initDefaultProperties();
	virtual void reset();

	void createProperty(const std::string &property_name, const Property::Value &default_value, Property::Access access, std::function<void(const Property::Value&)> setterFunction, std::function<Property::Value(void)> getterFunction = nullptr, bool authorize_reset = true);
	bool setProperty(const std::string &property_name, const Property::Value &value);
	Property::Value getProperty(const std::string &property_name);
	bool hasProperty(const std::string &property_name);
	bool resetProperty(const std::string &property_name);
	void resetProperties();

	void setPosition(const glm::vec2 &vec);
	void setSize(const glm::vec2 &vec);
	void setRotatePoint(const glm::vec2 &vec);
	void setAngle(float degree);
	void setEnable(bool state);

	glm::vec2 getPosition() const;
	glm::vec2 getSize() const;
	glm::vec2 getCenter() const;
	glm::vec2 rotatePoint() const;
	float getAngle() const;
	bool isEnable() const;

	void addChild(std::shared_ptr<Widget> child);
	size_t getNumberOfChildren() const;
	std::shared_ptr<Widget> getChild(const std::string &name);
	std::shared_ptr<Widget> findWidget(const std::string &path);
	void setParent(std::shared_ptr<Widget> parent);
	bool hasParent() const;
	std::shared_ptr<Widget> getParent() const;
	std::shared_ptr<Widget> detachChild(const std::string &name);
	void deleteChild(const std::string &name);
	void deleteChildren();

	virtual void handleEvent(const SDL_Event& evt) = 0;
	virtual void update(float dt) = 0;
	virtual void render(const Shader &shader2D) const = 0;

protected:
	void handleEventChildren(const SDL_Event &evt);
	void updateChildren(float dt);
	void renderChildren(const Shader &shader2D) const;

	std::shared_ptr<Widget> _parent;
	std::vector<std::shared_ptr<Widget>> _children;

	std::string _name;
	glm::vec2 _position;
	glm::vec2 _size;
	glm::vec2 _rotatePoint;
	float _angle;
	bool _enable;

	std::map<std::string, Property> _properties;
};

using WidgetPtr = std::shared_ptr<Widget>;

} // namespace Render2D

#endif // WIDGET_HPP

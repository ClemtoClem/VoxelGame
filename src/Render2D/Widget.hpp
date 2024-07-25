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
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include "../Core/CustomException.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Property.hpp"

namespace Render2D {

class Widget : public std::enable_shared_from_this<Widget> {
public:
	Widget(const std::string &name, std::shared_ptr<Widget> parent = nullptr);
	virtual ~Widget();
	
	const std::string &getName() const;

	virtual void initProperties();
	virtual void reset();

	/// @brief Set the property value
	template <typename T>
	bool setProperty(const std::string &property_name, const T &value);

	/// @brief Get the property value
	template <typename T>
	T &getProperty(const std::string &property_name);

	/// @brief Check if widget has a property
	bool hasProperty(const std::string &property_name);

	/// @brief Add a child widget
	void addChild(std::shared_ptr<Widget> child);

	/// @brief Get the child widget by name
	std::shared_ptr<Widget> getChild(const std::string &name);

	/// Get number of children
	size_t getNumberOfChildren() const;
	
	/// @brief Find a widget by path
	std::shared_ptr<Widget> findWidget(const std::string &path);

	/// @brief Set the parent widget
	void setParent(std::shared_ptr<Widget> parent);

	/// @brief Check if widget has a parent
	bool hasParent() const;

	/// @brief Get the parent widget
	std::shared_ptr<Widget> getParent() const;

	/// @brief Detach a child widget by name
	std::shared_ptr<Widget> detachChild(const std::string &name);

	/// @brief Delete a child widget by name
	void deleteChild(const std::string &name);

	/// @brief Delete all children
	void deleteChildren();

	virtual void handleEvent(const SDL_Event& evt) = 0;
	virtual void update(float dt) = 0;
	virtual void render(const Shader &shader2D) const = 0;

protected:
	template <typename T>
	void createProperty(const std::string &name, BaseProperty::Access access, T &value);

	void handleEventChildren(const SDL_Event &evt);
	void updateChildren(float dt);
	void renderChildren(const Shader &shader2D) const;

	std::shared_ptr<Widget> _parent;
	std::vector<std::shared_ptr<Widget>> _children;

	std::string _name;
	std::unordered_map<std::string, std::shared_ptr<BaseProperty>> _properties;
};

using WidgetPtr = std::shared_ptr<Widget>;

} // namespace Render2D

#endif // WIDGET_HPP

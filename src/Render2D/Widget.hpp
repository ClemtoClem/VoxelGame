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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "../Core/CustomException.hpp"
#include "../Core/Shader.hpp"
#include "../Core/Node.hpp"

namespace Render2D {

class Widget : public Node {
public:
	Widget(const std::string &name, std::shared_ptr<Widget> parent = nullptr,
		const glm::vec2 &position = glm::vec2(0.0f), const glm::vec2 &scale = glm::vec2(1.0f), float rotation = 0.0f, const glm::vec2 &rotateOrigin = glm::vec2(0.5f));

	virtual ~Widget();

	/// @brief Initialize the widget
	/// @note This function must be called in the derived function
	/// @retval true If the widget is initialized
	virtual bool initialize();

/* -------- PROPERTIES -------- */

	/// @brief Set position of the widget
	/// @param[in] position New position
	virtual void setPosition(const glm::vec2 &position);

	/// @brief Set size of the widget
	/// @param[in] scale New size
	virtual void setScale(const glm::vec2 &scale);

	/// @brief Set rotation around the origin of the widget
	/// @param[in] rotation New rotation
	virtual void setRotate(float rotation);

	/// @brief Set rotation origin of the widget
	/// @param[in] origin New rotation origin
	virtual void setRotateOrigin(const glm::vec2 &origin);

	/// @brief Enable or disable the widget
	virtual void setEnable(bool enable);

	/// @brief Get position of the widget
	/// @retval glm::vec2 Position
	virtual glm::vec2 getPosition() const;

	/// @brief Get absolute position of the widget
	/// @return glm::vec2 Absolute position
	virtual glm::vec2 getAbsolutePosition() const;

	/// @brief Get size of the widget
	/// @retval glm::vec2 Size
	virtual glm::vec2 getScale() const;

	/// @brief Get rotation of the widget
	/// @retval float Rotation
	virtual float getRotate() const;

	/// @brief Get rotation origin of the widget
	/// @retval glm::vec2 Rotation origin
	virtual glm::vec2 getRotateOrigin() const;

	/// @brief Get enable status of the widget
	/// @retval bool Enable status
	virtual bool isEnable() const;


/* ------ BOUNDING BOX ------- */

	/// @brief Get the transformed bounding box
	/// @returns std::array<glm::vec2, 4> Transformed bounding box
	std::array<glm::vec2, 4> getTransformedBoundingBox() const;

	/// @brief Check if the bounding box of the widget overlaps with another widget
	/// @param[in] widget Widget to check
	/// @retval bool True if the bounding box overlaps, false otherwise
	bool overlapsWith(const Widget &widget) const;

	/// @brief Check if the widget contains a point
	/// @param[in] point Point to check
	/// @retval bool True if the point is inside the widget, false otherwise
	bool containsPoint(const glm::vec2 &point) const;

protected:

	/// @brief Update the transform matrix
	/// @details Update the transform matrix if needed
	/// @note This function must be called in the derived function 'void update(float dt)'
	void updateTransform();

	/// @brief Axis-Aligned Bounding Box (AABB) from corners
	/// @param[in] corners Corners of the AABB
	/// @retval glm::vec4 AABB
	glm::vec4 getAABB(const std::array<glm::vec2, 4> &corners) const;

public:

/* --------- EVENTS ---------- */

	/// @brief Handle an event
	/// @param[in] evt Event
	virtual void handleEvent(SDL_Event& evt) = 0;

	bool isHovered() const;

	bool isSelected() const;

/* -------- UPDATING --------- */

	/// @brief Update the widget
	/// @param[in] dt Delta time
	virtual void update(float dt) = 0;

/* -------- RENDERING -------- */

	/// @brief Render the widget
	/// @param[in] shader2D Shader
	virtual void render(const Shader &shader2D) const = 0;

protected:

	glm::vec2 _position;
	glm::vec2 _scale;
	float _angle;
	glm::vec2 _rotateOrigin;
	bool _enabled;

	glm::mat4 _transform;
	bool _needs_update_transform;

	bool _is_hovered;
	bool _is_init;

	GLuint _vao, _vbo;

	void handleEventChildren(SDL_Event& evt);
	void updateChildren(float dt);
	void renderChildren(const Shader &shader2D) const;
};

using WidgetPtr = std::shared_ptr<Widget>;

} // namespace Render2D

#endif // WIDGET_HPP

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
#include "../Core/Texture.hpp"
#include "../Core/Font.hpp"
#include "../Core/Shader.hpp"
#include "Property.hpp"

namespace Render2D {

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(const std::string &name, std::shared_ptr<Widget> parent = nullptr);
    virtual ~Widget();

    virtual void initDefaultProperties();
    virtual void reset() = 0;

    void setProperty(const std::string &property_name, const Property::Value &value, std::function<void(const Property::Value&)> updateFunction = nullptr, Property::Access access = Property::Access::READ_WRITE);
    bool hasProperty(const std::string &property_name);
    Property::Value getProperty(const std::string &property_name);

    void position(const glm::vec2 &vec);
    void position(float x, float y);
    glm::vec2 position() const;

    void size(const glm::vec2 &vec);
    void size(float w, float h);
    glm::vec2 size() const;

    glm::vec2 center() const;

    void rotatePoint(const glm::vec2 &vec);
    glm::vec2 rotatePoint() const;

    void angle(float degree);
    float angle() const;

    void enable(bool state);
    bool enable() const;

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

    virtual void handleEvent(SDL_Event& evt) = 0;
    virtual void update(float dt) = 0;
    virtual void render(const Shader &shader2D) const = 0;

protected:
    void handleEventChildren(const SDL_Event &evt);
    void updateChildren(float dt);
    void renderChildren(const Shader &shader2D) const;

    void updateProperties();

    std::shared_ptr<Widget> _parent;
    std::vector<std::shared_ptr<Widget>> _children;

    glm::vec2 _position;
    glm::vec2 _size;
    glm::vec2 _rotatePoint;
    float _angle;
    bool _enable;

    std::map<std::string, Property> _properties;
};

} // namespace Render2D

#endif // WIDGET_HPP
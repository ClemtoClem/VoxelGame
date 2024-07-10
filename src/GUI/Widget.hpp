/**
 *  __    __ _     _            _   
 * / / /\ \ (_) __| | __ _  ___| |_ 
 * \ \/  \/ / |/ _` |/ _` |/ _ \ __|
 *  \  /\  /| | (_| | (_| |  __/ |_ 
 *   \/  \/ |_|\__,_|\__, |\___|\__|
 *                   |___/          
 * 
 * @file Widget.cpp
 * @author ClemtoClem
 * @date 09/07/2024
 */

#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Widget {
public:
    Widget();
    virtual ~Widget();

    virtual void handleEvent(SDL_Event& evt) = 0;
    virtual void update(float dt) = 0;
    virtual void render() const = 0;

    void setPosition(const glm::vec2& position);
    void setSize(const glm::vec2& size);

    void setColor(const glm::vec4& color);
    glm::vec4 getColor() const;

    void setBackgroundColor(const glm::vec4& color);
    glm::vec4 getBackgroundColor() const;

    void setHoverBackgroundColor(const glm::vec4& color);
    glm::vec4 getHoverBackgroundColor() const;

    void setBorderColor(const glm::vec4& color);
    glm::vec4 getBorderColor() const;

    void setBorderWidth(float width);
    float getBorderWidth() const;

protected:
    glm::vec2 _position;
    glm::vec2 _size;
    glm::vec4 _color = glm::vec4(1.0f);                 // Default text color: white
    glm::vec4 _backgroundColor = glm::vec4(0.0f);       // Default background color: black
    glm::vec4 _hoverBackgroundColor = glm::vec4(0.0f);  // Default hover background color: black
    glm::vec4 _borderColor = glm::vec4(1.0f);           // Default border color: white
    float _borderWidth = 0.0f;                          // Default border width: 0 (no border)
};

#endif // WIDGET_HPP

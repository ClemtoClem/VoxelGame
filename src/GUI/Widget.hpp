/**
 *  __    __ _     _            _   
 * / / /\ \ (_) __| | __ _  ___| |_ 
 * \ \/  \/ / |/ _` |/ _` |/ _ \ __|
 *  \  /\  /| | (_| | (_| |  __/ |_ 
 *   \/  \/ |_|\__,_|\__, |\___|\__|
 *                   |___/          
 * 
 * @file Widget.cpp
 * @author @ClemtoClem
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
    void setPosition(float x, float y) {
        setPosition(glm::vec2(x, y));
    }
    glm::vec2 getPosition() const;

    void setSize(const glm::vec2& size);
    void setSize(float width, float height) {
        setSize(glm::vec2(width, height));
    }
    glm::vec2 getSize() const;

    void setColor(const glm::vec4& color);
    void setColor(float r, float g, float b, float a) {
        setColor(glm::vec4(r, g, b, a));
    }
    glm::vec4 getColor() const;

    void setHoverColor(const glm::vec4& color);
    void setHoverColor(float r, float g, float b, float a) {
        setHoverColor(glm::vec4(r, g, b, a));
    }
    glm::vec4 getHoverColor() const;

    void setBackgroundColor(const glm::vec4& color);
    void setBackgroundColor(float r, float g, float b, float a) {
        setBackgroundColor(glm::vec4(r, g, b, a));
    }
    glm::vec4 getBackgroundColor() const;

    void setHoverBackgroundColor(const glm::vec4& color);
    void setHoverBackgroundColor(float r, float g, float b, float a) {
        setHoverBackgroundColor(glm::vec4(r, g, b, a));
    }
    glm::vec4 getHoverBackgroundColor() const;

    void setBorderColor(const glm::vec4& color);
    void setBorderColor(float r, float g, float b, float a) {
        setBorderColor(glm::vec4(r, g, b, a));
    }
    glm::vec4 getBorderColor() const;

    void setBorderWidth(float width);
    float getBorderWidth() const;

    void setVisible(bool visible);
    bool isVisible() const;

protected:
    glm::vec2 _position;
    glm::vec2 _size;
    glm::vec4 _color = glm::vec4(1.0f);                 // Default text color: white
    glm::vec4 _hoverColor = glm::vec4(1.0f);            // Default hover text color: white
    glm::vec4 _backgroundColor = glm::vec4(0.0f);       // Default background color: black
    glm::vec4 _hoverBackgroundColor = glm::vec4(0.0f);  // Default hover background color: black
    glm::vec4 _borderColor = glm::vec4(1.0f);           // Default border color: white
    float _borderWidth = 0.0f;                          // Default border width: 0 (no border)
    bool _isHovered = false;                            // Default hover state: false
    bool _visible = true;                             // Default visibility: true
};

#endif // WIDGET_HPP

#ifndef GUI_HPP
#define GUI_HPP

#include "Widget.hpp"
#include "../Shader.hpp"
#include <vector>
#include <memory>

class GUI {
public:
    GUI();
    ~GUI();

    bool init();

    void setScreenSize(int width, int height);

    void reset();

    void addWidget(std::shared_ptr<Widget> widget);

    void handleEvent(SDL_Event& evt);

    void update(float dt);
    
    void render() const;

private:
    void initRenderData();
    
    std::shared_ptr<Shader> _shader2D;
    GLuint _vao, _vbo;

    std::vector<std::shared_ptr<Widget>> _widgets;
    int _screenWidth;
    int _screenHeight;

};

#endif // GUI_HPP

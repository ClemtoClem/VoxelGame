#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Widget.hpp"
#include <functional>
#include <string>
#include <memory>

class Button : public Widget {
public:
	Button(const std::string &name, const std::string& fontPath, int fontSize, const std::string& text, const glm::vec4& backgroundColor, const glm::vec4& textColor);
	~Button();

	std::shared_ptr<Widget> getTextWidget() const;

	void setCallback(std::function<void()> callback);
	virtual void handleEvent(SDL_Event& evt) override;
	virtual void update(float dt) override;
	virtual void render(const Shader &shader2D) const override;

private:
	std::function<void()> _callback;
	std::shared_ptr<Widget> _textWidget;
};

#endif // BUTTON_HPP


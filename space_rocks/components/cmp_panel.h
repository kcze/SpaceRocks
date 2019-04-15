#pragma once

#include "components.h"
#include <ecm.h>

class PanelComponent : public Component {
public:
	PanelComponent() = delete;
	explicit PanelComponent(Entity* p, const sf::Vector2f anchor, const float interval = 0.0f);

	void update(double dt) override;
	void render() override { }

	void addButton(const std::string text, std::function<void()> function);
	std::shared_ptr<Entity> addText(const std::string text, const float size = 32.0f);
	std::shared_ptr<Entity> addText(std::function<std::string()>, const float size = 32.0f);
	void executeButton();
	void pointerPrevious();
	void pointerNext();
	void updatePositions();

	~PanelComponent();

private:
	std::shared_ptr<Entity> _buttonPointer;
	std::shared_ptr<Entity> _currentButton;
	std::vector<std::shared_ptr<Entity>> _buttons;
	std::vector<std::shared_ptr<Entity>> _elements;
	sf::Vector2f _anchor;
	Scene* _panelScene;

	float _interval;
};

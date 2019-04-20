#pragma once
#include "..\game.h"
#include "components.h"
#include <ecm.h>

class PanelComponent : public Component {
public:
	PanelComponent() = delete;
	explicit PanelComponent(Entity* p, const sf::Vector2f anchor, const float interval = 0.0f, const bool horizontal = false);

	void update(double dt) override;
	void render() override { }

	void addButton(const std::string text, std::function<void()> function);
	std::shared_ptr<Entity> addText(const std::string text, const float size = 40.0f);
	std::shared_ptr<Entity> addText(std::function<std::string()>, const float size = 40.0f);
	void executeButton();
	void pointerPrevious();
	void pointerNext();
	void updatePositions();
	void setVisible(bool visible);

	~PanelComponent();

private:
	std::shared_ptr<Entity> _buttonPointer;
	std::shared_ptr<Entity> _currentButton;
	std::vector<std::shared_ptr<Entity>> _buttons;
	std::vector<std::shared_ptr<Entity>> _elements;
	sf::Vector2f _anchor;
	bool _horizontal;// false = vertical
	Scene* _panelScene;

	float _interval;
};

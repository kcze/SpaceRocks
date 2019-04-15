#pragma once

#include "components.h"
#include <ecm.h>

class PanelComponent : public Component {
public:
	PanelComponent() = delete;
	explicit PanelComponent(Entity* p, const float interval);

	void update(double dt) override;
	void render() override { }

	void addButton(const std::string text, std::function<void()> function);
	std::shared_ptr<Entity> addText(const std::string text);
	std::shared_ptr<Entity> addText(const std::string text, std::function<std::string()>);
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

	Scene* _panelScene;

	float _interval;
};
#pragma once

#include "engine.h"
#include "..\input.h"

class MenuScene : public Scene, public InputEvents {
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void load() override;

	void onKeyPressed(Keyboard::Key key) override;
	void onTextEntered(std::string text) override;

	void update(const double& dt) override;

};

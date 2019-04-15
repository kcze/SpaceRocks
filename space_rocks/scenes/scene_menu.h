#pragma once

#include "engine.h"
#include "..\input.h"

class MenuScene : public Scene, public InputEvents {
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void Load() override;

	void onKeyPressed(Keyboard::Key key) override;

	void Update(const double& dt) override;
};

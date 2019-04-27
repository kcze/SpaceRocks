#pragma once

#include "engine.h"
#include "..\input.h"
#include "..\files.h"

// Menu scene
class MenuScene : public Scene, public InputEvents {
public:
	MenuScene() = default;
	~MenuScene() override = default;

	void load() override;

	void onKeyPressed(std::variant<Keyboard::Key, unsigned int> k) override;
	void onTextEntered(std::string text) override;
	static void gotoGame();

	void update(const double& dt) override;

};

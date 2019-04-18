#pragma once

#include "engine.h"
#include "..\input.h"

class GameScene : public Scene, public InputEvents {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void createEdges();
  void playerDeath();
  void roundStart();
  void onKeyPressed(Keyboard::Key key) override;

  void update(const double& dt) override;

};

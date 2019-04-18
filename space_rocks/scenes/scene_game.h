#pragma once

#include "engine.h"

class GameScene : public Scene {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void createEdges();
  void playerDeath();
  void roundStart();

  void update(const double& dt) override;
};

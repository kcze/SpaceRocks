#pragma once

#include "engine.h"

class GameScene : public Scene {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void createEdges();

  void update(const double& dt) override;
};

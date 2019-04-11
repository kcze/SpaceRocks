#pragma once

#include "engine.h"

class GameScene : public Scene {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void Load() override;

  void SpawnAsteroid();

  void Update(const double& dt) override;
};

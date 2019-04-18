#pragma once

#include "engine.h"

class GameScene : public Scene {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void spawnEnemy(unsigned int id, unsigned int dir);
  void createEdges();
  void playerDeath();
  void roundwaveStart();
  void spawnWave();

  void update(const double& dt) override;
};


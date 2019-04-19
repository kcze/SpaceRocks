#pragma once

#include "engine.h"
#include "..\input.h"

class GameScene : public Scene, public InputEvents {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void spawnEnemy(unsigned int id, unsigned int dir);
  void createEdges();
  void playerDeath();
  void onKeyPressed(Keyboard::Key key) override;
  void roundwaveStart();
  void spawnWave();

  void update(const double& dt) override;
};


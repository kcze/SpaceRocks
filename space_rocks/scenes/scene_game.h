#pragma once

#include "engine.h"
#include "..\input.h"

// Game scene
class GameScene : public Scene, public InputEvents {
public:
	GameScene() = default;
  ~GameScene() override = default;

  void load() override;

  void spawnAsteroid();
  void spawnEnemy(unsigned int id, unsigned int dir);
  void createEdges();
  void playerDeath();
  void onKeyPressed(std::variant<Keyboard::Key, unsigned int> k) override;
  void roundwaveStart();
  void spawnWave();
  void destroyAll();
  static void gotoMenu();

  void update(const double& dt) override;
  void onTextEntered(std::string text);
};


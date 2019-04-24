#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;
bool suppressPlayerControl;
std::shared_ptr<Entity> player1;

int main() {
	Engine::start(GAMEX, GAMEY, "Space Rocks", &menuScene);
}
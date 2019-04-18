#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;
bool suppressPlayerControl;

int main() {
	Engine::start(GAMEX, GAMEY, "Space Rocks", &menuScene);
}
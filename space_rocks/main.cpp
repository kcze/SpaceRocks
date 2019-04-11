#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;

int main() {
	Engine::Start(GAMEX, GAMEY, "Space Rocks", &menuScene);
}
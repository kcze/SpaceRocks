#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;

int main() {
	Engine::Start(1280, 720, "Space Rocks", &menuScene);
}
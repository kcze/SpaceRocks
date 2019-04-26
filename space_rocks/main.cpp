#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menuScene;
GameScene gameScene;
bool suppressPlayerControl;
std::shared_ptr<Entity> player1;
std::multimap<unsigned int, std::string> highscores;

int main() {
	Engine::start(GAMEX, GAMEY, "Space Rocks", &menuScene);
}
#include "scene_game.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "maths.h"

using namespace std;
using namespace sf;

void GameScene::Load() {
	cout << "Game Scene Load \n";
	{
		auto txt = makeEntity();
	}
	setLoaded(true);
}

void GameScene::Update(const double& dt) {
	 

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		cout << "Game Scene " << dt << "\n";
	}
	
	Scene::Update(dt);
}

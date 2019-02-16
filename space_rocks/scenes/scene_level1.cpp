#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "maths.h"

using namespace std;
using namespace sf;

void Level1Scene::Load() {
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
		    "Platformer\nPress Space to Start");
	}
	setLoaded(true);
}

void Level1Scene::Update(const double& dt) {
	 

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		//Engine::ChangeScene(&level1);
		cout << "Menu Update " << dt << "\n";
	}
	
	Scene::Update(dt);
}

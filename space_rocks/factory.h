#pragma once

#include "Box2D/Box2D.h"
#include "system_physics.h"
#include "engine.h"
#include "game.h"
#include "ecm.h"

// Holds information about collider shape and texture for objects
struct ObjectData
{
	std::vector<b2Vec2 > _coords;// Collider vertex points
	std::shared_ptr<sf::Texture> _tex;// Texture
	sf::IntRect _texRect;
};

// Parent class for factories
class Factory {
protected:
	static const float PSI4;
	static const float PSI8;
	static const float PSI16;
};
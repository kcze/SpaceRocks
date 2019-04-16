#pragma once

#include "Box2D/Box2D.h"
#include <SFML/System/Vector2.hpp>

namespace Physics {
void initialise();
void shutdown();
void update(const double&);

std::shared_ptr<b2World> getWorld();

const float physicsScale = 30.0f;
const float physicsScaleInv = 1.0f / physicsScale;

const sf::Vector2f bv2ToSv2(const b2Vec2& in, bool scale = true);
const b2Vec2 sv2ToBv2(const sf::Vector2f& in, bool scale = true);
const sf::Vector2f invertHeight(const sf::Vector2f& in);
} // namespace Physics

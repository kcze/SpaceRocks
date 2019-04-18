#include "cmp_player.h"
#include "..\input.h"
#include <stdio.h>

PlayerComponent::PlayerComponent(Entity* p, const int player) : Component(p)
{
	_player = player;
	_shipComponent = _parent->getComponents<ShipComponent>()[0];
}

void PlayerComponent::update(double dt)
{
	if (Input::isKeyDown(Input::KeyCode::P1_THRUST))
	{
		_shipComponent->thrust(dt);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_LEFT))
	{
		_shipComponent->rotate(false);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_RIGHT))
	{
		_shipComponent->rotate(true);
	}
	if (Input::isKeyDown(Input::KeyCode::P1_FIRE))
	{
		_shipComponent->shoot();
	}
}
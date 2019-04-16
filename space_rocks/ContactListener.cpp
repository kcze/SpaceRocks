#include "ContactListener.h"

//Contact Listener
void myContactListener::BeginContact(b2Contact* contact)
{
	b2Filter filterA = contact->GetFixtureA()->GetFilterData();
	b2Filter filterB = contact->GetFixtureB()->GetFilterData();

	b2Vec2 posA = contact->GetFixtureA()->GetBody()->GetPosition();
	b2Vec2 posB = contact->GetFixtureB()->GetBody()->GetPosition();

	auto entityA = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
	auto entityB = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

	//Bullet x Object Collisions
	if (filterA.groupIndex == 1 ^ filterB.groupIndex == 1)
	{
		//Make bullet always A
		if (filterB.groupIndex == 1)
		{
			std::swap(filterA, filterB);
			std::swap(posA, posB);
			std::swap(entityA, entityB);
		}

		//Damage object
		entityB->get_components<DestructibleComponent>()[0]->damage(
			entityA->get_components<BulletComponent>()[0]->getDamage()
		);
		//Destroy bullet
		entityA->get_components<DestructibleComponent>()[0]->damage(10.0f);
	}

	//Player x Object Collisions
	if (filterA.categoryBits == PLAYER_SHIP ^ filterB.categoryBits == PLAYER_SHIP)
	{
		//Make player ship always A
		if (filterB.categoryBits == PLAYER_SHIP)
		{
			std::swap(filterA, filterB);
			std::swap(posA, posB);
			std::swap(entityA, entityB);
		}

		//If bullet, do nothing (as bullet impact already creates particles)
		if (filterB.groupIndex == 1)
			return;

		//Particle burst to show where collision has happened and inform them of damage
		//std::function<void()> toCall = std::bind(&entityA->get_components<DestructibleComponent>()[0]->particleBurst, entityA->getPosition(), 5, 30.0f);
		//entityA->get_components<DestructibleComponent>()[0]->setToCall(toCall);
		//Damage player
		entityA->get_components<DestructibleComponent>()[0]->damage(1.0f);
	}

}

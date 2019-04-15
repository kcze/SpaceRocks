#include "ContactListener.h"

//Contact Listener
void myContactListener::BeginContact(b2Contact* contact)
{
	b2Filter filterA = contact->GetFixtureA()->GetFilterData();
	b2Filter filterB = contact->GetFixtureB()->GetFilterData();

	const b2Vec2 posA = contact->GetFixtureA()->GetBody()->GetPosition();
	const b2Vec2 posB = contact->GetFixtureB()->GetBody()->GetPosition();

	auto entityA = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
	auto entityB = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

	//Bullet collisions
	if (filterA.groupIndex == 1)
	{
		//Bullet x Asteroid
		if (filterB.categoryBits == ASTEROIDS)
		{
			//Damage asteroid by 1														TODO: Set damage to bullet damage value
			entityB->get_components<DestructibleComponent>()[0]->damage(1.0f);
			//Destroy bullet
			entityA->get_components<DestructibleComponent>()[0]->damage(10.0f);
		}
	}
	else if (filterB.groupIndex == 1)
	{
		//Bullet x Asteroid
		if (filterA.categoryBits == ASTEROIDS)
		{
			//Damage asteroid by 1														TODO: Set damage to bullet damage value
			entityA->get_components<DestructibleComponent>()[0]->damage(1.0f);
			//Destroy bullet
			entityB->get_components<DestructibleComponent>()[0]->damage(10.0f);
		}
	}

}

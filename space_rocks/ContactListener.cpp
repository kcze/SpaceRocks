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
}

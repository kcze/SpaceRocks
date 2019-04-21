#include "contact_listener.h"

std::default_random_engine rndG((int)time(NULL));
std::uniform_real_distribution<float> zeroOne(0.0f, 1.0f);

//Contact Listener
void MyContactListener::BeginContact(b2Contact* contact)
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
		entityB->getComponents<DestructibleComponent>()[0]->damage(
			entityA->getComponents<BulletComponent>()[0]->getDamage()
		);

		//If player, play sound
		if(filterB.categoryBits == PLAYER_SHIP)
			audioManager.playSound("player_hurt");

		//Else if Player Bullet x Asteroid/Ship and Object was destroyed
		else if (filterA.categoryBits == PLAYER_BULLET && (filterB.categoryBits == ASTEROIDS || filterB.categoryBits == ENEMY_SHIP) && 
			entityB->getComponents<DestructibleComponent>()[0]->getHp() <= 0.0f)
		{
			//Coin drop
			if (zeroOne(rndG) < entityB->getComponents<DestructibleComponent>()[0]->getCoinChance())
			{
				player1->getComponents<PlayerComponent>()[0]->addCoins(entityB->getComponents<DestructibleComponent>()[0]->getCoinValue());
				audioManager.playSound("pickup_coin");
			}
		}


		//Destroy bullet
		entityA->getComponents<DestructibleComponent>()[0]->damage(10.0f);
	}

	//Bullet x Bullet Collisions
	else if (filterA.groupIndex == 1 && filterB.groupIndex == 1)
	{
		//Destroy bullets
		audioManager.playSound("bullet_x_bullet");
		entityA->getComponents<DestructibleComponent>()[0]->damage(10.0f);
		entityB->getComponents<DestructibleComponent>()[0]->damage(10.0f);
	}

	//Player x Object Collisions
	else if (filterA.categoryBits == PLAYER_SHIP ^ filterB.categoryBits == PLAYER_SHIP)
	{
		//Make player ship always A
		if (filterB.categoryBits == PLAYER_SHIP)
		{
			std::swap(filterA, filterB);
			std::swap(posA, posB);
			std::swap(entityA, entityB);
		}

		//If bullet, do nothing (as bullet impact already creates particles)
		//TODO: Else should stop this running anyway
		if (filterB.groupIndex == 1)
			return;

		//Particle burst to show where collision has happened and inform them of damage
		//std::function<void()> toCall = std::bind(&entityA->get_components<DestructibleComponent>()[0]->particleBurst, entityA->getPosition(), 5, 30.0f);
		//entityA->get_components<DestructibleComponent>()[0]->setToCall(toCall);

		//Damage player
		entityA->getComponents<DestructibleComponent>()[0]->damage(1.0f);

		//Damage enemy ship
		if(filterB.categoryBits == ENEMY_SHIP)
			entityB->getComponents<DestructibleComponent>()[0]->damage(1.0f);

		//Damage asteroid ship
		if (filterB.categoryBits == ASTEROIDS)
			entityB->getComponents<DestructibleComponent>()[0]->damage(1.0f);

		//Play audio
		audioManager.playSound("player_hurt");
	}
}

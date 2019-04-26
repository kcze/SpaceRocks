#include "particle_factory.h"

std::map < unsigned int, ObjectData > ParticleFactory::_objectData =
{
	//Circle
	{1,
		{
			{
				//No Collider
			},
			{
				Resources::load<sf::Texture>("particles.png")
			},
			{
				sf::IntRect(0, 0, 16, 16)
			}
		}
	},
	//Triangle
	{2,
		{
			{
				//No Collider
			},
			{
				Resources::load<sf::Texture>("particles.png")
			},
			{
				sf::IntRect(16, 0, 16, 16)
			}
		}
	},
	//Diamond
	{3,
		{
			{
				//No Collider
			},
			{
				Resources::load<sf::Texture>("particles.png")
			},
			{
				sf::IntRect(32, 0, 16, 16)
			}
		}
	},
	//Square
	{4,
		{
			{
				//No Collider
			},
			{
				Resources::load<sf::Texture>("particles.png")
			},
			{
				sf::IntRect(48, 0, 16, 16)
			}
		}
	}, 
};

std::shared_ptr<Entity> ParticleFactory::makeParticle(unsigned int type)
{
	//Make entity
	std::shared_ptr<Entity> particle = gameScene.makeEntity();

	// Physics
	{
		//No collider required, just velocity
		auto phys = particle->addComponent<PhysicsComponent>(true, sf::Vector2f(16.0f, 16.0f));
	}

	// Sprite
	{
		auto sprite = particle->addComponent<SpriteComponent>();
		sprite->setTexure(_objectData[type]._tex);
		sprite->setTextureRect(_objectData[type]._texRect);
		sprite->setAnchor(sf::Vector2f(0.5f, 0.5f));
	}

	//Destructible
	{
		auto des = particle->addComponent<DestructibleComponent>(FLT_MIN, 0, 2.0f); //hp is identifier
	}

	return particle;
}

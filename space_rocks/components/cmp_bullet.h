#pragma once
#include <ecm.h>

struct Bullet {
	float _damage;
	unsigned int _id;
};

class BulletComponent : public Component {
protected:
  float _lifetime;
  float _damage;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, float lifetime, float damage);
  float getDamage();
  BulletComponent() = delete;
};

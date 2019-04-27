#pragma once
#include <ecm.h>

// Bullet data
struct Bullet {
	float _damage;
	unsigned int _id;
};

// Component for bullets
class BulletComponent : public Component {
protected:
  float _damage;

public:
  void update(double dt) override;
  void render() override {}
  explicit BulletComponent(Entity* p, float damage);
  float getDamage();
  BulletComponent() = delete;
  ~BulletComponent() override = default;
};

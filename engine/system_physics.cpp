
#include "system_physics.h"
#include "Box2D/Box2D.h"

using namespace std;
using namespace sf;

namespace Physics {
static shared_ptr<b2World> world;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

void initialise() {
  b2Vec2 gravity(0.0f, 0.0f);
  // Construct a world object, which will hold and simulate the rigid
  // bodies.
  world.reset(new b2World(gravity));
}

void shutdown() { world.reset(); }

void update(const double& dt) {
  world->Step((float)dt, velocityIterations, positionIterations);
}

std::shared_ptr<b2World> getWorld() { return world; }

const Vector2f bv2ToSv2(const b2Vec2& in, bool scale) {
  if (scale) {
    return Vector2f((in.x * physicsScale), (in.y * physicsScale));
  } else {
    return Vector2f(in.x, in.y);
  }
}

const b2Vec2 sv2ToBv2(const Vector2f& in, bool scale) {
  if (scale) {
    return b2Vec2((in.x * physicsScaleInv), (in.y * physicsScaleInv));
  } else {
    return b2Vec2(in.x, in.y);
  }
}

const Vector2f invertHeight(const Vector2f& in) {
  return Vector2f(in.x, 720 - in.y);
}
} // namespace Physics
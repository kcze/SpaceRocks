#include "cmp_physics.h"
#include "system_physics.h"
#include "maths.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::update(double dt) {
	//Enforce speedlimit
	float currentSpeed = sf::length(getVelocity());
	if (currentSpeed > _maxSpeed)
		setVelocity((_maxSpeed / currentSpeed) * getVelocity());


  _parent->setPosition(invertHeight(bv2ToSv2(_body->GetPosition())));
  _parent->setRotation((180 / b2_pi) * _body->GetAngle());
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
                                   const Vector2f& size)
    : Component(p), _dynamic(dyn) {

  b2BodyDef BodyDef;
  // Is Dynamic(moving), or static(Stationary)
  BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
  BodyDef.position = sv2ToBv2(invertHeight(p->getPosition()));
  BodyDef.userData = _parent;

  // Create the body
  _body = Physics::getWorld()->CreateBody(&BodyDef);
  _body->SetActive(true);

  _maxSpeed = 350.0f;

}

b2Body*  PhysicsComponent::getBody()
{
	return _body;
}

void PhysicsComponent::setFixtureDef(b2FixtureDef fix)
{
	//set properties
	fix.friction = _dynamic ? 0.1f : 0.8f;
	fix.restitution = .2;
	_body->SetSleepingAllowed(false);
	//Attach to body
	_fixture = _body->CreateFixture(&fix);
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
  _body->SetTransform(sv2ToBv2(invertHeight(v)), _body->GetAngle()); 
}

void PhysicsComponent::setAngle(const float angle) {
	_body->SetTransform(_body->GetPosition(), angle);
}


const sf::Vector2f PhysicsComponent::getVelocity() const {
  return bv2ToSv2(_body->GetLinearVelocity(), true);
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
  _body->SetLinearVelocity(sv2ToBv2(v, true));
}

void PhysicsComponent::setAngularVelocity(const float a) {
	_body->SetAngularVelocity(a);
}

void PhysicsComponent::dump()
{
	_body->Dump();
}

void PhysicsComponent::setLinearDampening(float f)
{
	_body->SetLinearDamping(f);
}

void PhysicsComponent::setAngularDampening(float f) {

	_body->SetAngularDamping(f);
}



b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
  auto a = Physics::getWorld();
  _body->SetActive(false);
  Physics::getWorld()->DestroyBody(_body);
  // delete _body;
  _body = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
  auto a = b2Vec2(i.x, i.y * -1.0f);
  _body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::impulseRelative(sf::Vector2f& i) {
	double deg = rad2deg(_body->GetAngle());
	sf::Vector2f v = rotate(i, deg);
	auto a = b2Vec2(v.x, v.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
  auto vel = _body->GetLinearVelocity();
  vel.x *= i.x;
  vel.y *= i.y;
  _body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
  b2Contact* bc;
  return isTouching(pc, bc);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc,
                                  b2Contact const* bc) const {
  const auto _otherFixture = pc.getFixture();
  const auto& w = *Physics::getWorld();
  const auto contactList = w.GetContactList();
  const auto clc = w.GetContactCount();
  for (int32 i = 0; i < clc; i++) {
    const auto& contact = (contactList[i]);
    if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
                                  contact.GetFixtureA() == _otherFixture) ||
                                 (contact.GetFixtureA() == _otherFixture &&
                                  contact.GetFixtureA() == _fixture))) {
      bc = &contact;
      return true;
    }
  }
  return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
  std::vector<const b2Contact const*> ret;

  b2ContactEdge* edge = _body->GetContactList();
  while (edge != NULL) {
    const b2Contact* contact = edge->contact;
    if (contact->IsTouching()) {
      ret.push_back(contact);
    }
    edge = edge->next;
  }

  return ret;
}

void PhysicsComponent::setRestitution(float r) {
  _fixture->SetRestitution(r);
}

#pragma once

#include "ecm.h"
#include "cmp_ship.h"

class PlayerComponent : public Component {

public:
	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, const int player);

	void render() override { }
	void update(double dt) override;

	~PlayerComponent() override = default;

protected:
	int _player;
	std::shared_ptr<ShipComponent> _shipComponent;

};
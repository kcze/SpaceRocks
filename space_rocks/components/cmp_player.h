#pragma once

#include "ecm.h"
#include "cmp_ship.h"

class PlayerComponent : public Component {

public:
	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, const int player);

	void render() override { }
	void update(double dt) override;

	int getCoins() { return _coins; }
	void setCoins(int c) { _coins = c; }
	void addCoins(int c) { _coins += c; }
	void removeCoins(int c) { _coins -= c; }

	~PlayerComponent() override = default;

protected:
	int _player;
	int _coins;
	std::shared_ptr<ShipComponent> _shipComponent;

};
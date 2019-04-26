#pragma once

#include "ecm.h"
#include "cmp_ship.h"

class PlayerComponent : public Component {

public:
	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p, const int player);

	void render() override { }
	void update(double dt) override;
	//Money
	int getCoins() { return _coins; }
	void setCoins(int c) { _coins = c; }
	void addCoins(int c) { _coins += c; }
	void removeCoins(int c) { _coins -= c; }
	bool tryPurchase(int cost);
	//Upgrades
	void tryUpgradeDamage();
	void tryUpgradeROF();
	//Score
	unsigned int getScore() { return _score; }
	void addScore(unsigned int s) { _score += s; }


	~PlayerComponent() override;

protected:
	int _player;
	int _coins = 0;
	unsigned int _score = 0;
	std::shared_ptr<ShipComponent> _shipComponent;
};
#pragma once

#include <ecm.h>
#include "components.h"

// Controls enemy behaviour
class AiComponent : public Component {
protected:
	std::shared_ptr<ShipComponent> _shipComponent;
	std::vector<std::shared_ptr<Entity>> _players;
	std::shared_ptr<Entity> _target;

public:
	AiComponent() = delete;
	explicit AiComponent(Entity* p);

	void update(double dt) override;
	void render() override {}

	~AiComponent() override;
};

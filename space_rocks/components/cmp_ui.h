#pragma once

#include <functional>
#include "components.h"
#include <ecm.h>

class UiComponent : public Component {
public:
	UiComponent() = delete;
	explicit UiComponent(Entity* p);

	void update(double dt) override;
	void render() override { }

	std::function<void()> buttonExecute;
	std::function<std::string()> textUpdate;

	~UiComponent() = default;
};
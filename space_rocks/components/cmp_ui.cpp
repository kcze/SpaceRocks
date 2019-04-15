#include "cmp_ui.h"

UiComponent::UiComponent(Entity* const p)
	: Component(p) { }

void UiComponent::update(double dt) { 
	if (textUpdate != NULL)
		_parent->get_components<TextComponent>()[0]->setText(textUpdate());
}


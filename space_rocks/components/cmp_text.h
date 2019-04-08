#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(double dt) override;

  void render() override;

  ~TextComponent() override = default;

  void SetText(const std::string& str);

  void TextComponent::SetAlignment(int i);

  void TextComponent::SetSize(unsigned int size);

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
  int _alignment;
};

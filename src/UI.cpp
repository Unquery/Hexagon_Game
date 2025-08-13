//
// Created by Unquery on 2025-08-13.
//

#include "UI.h"

sf::Text makeText(const sf::Font& font, const std::string& str, unsigned size,
                  sf::Color color, sf::Vector2f pos, sf::Uint32 style) {
    sf::Text t;

    t.setFont(font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    t.setStyle(style);
    t.setString(str);
    t.setPosition(pos);

    return t;
}

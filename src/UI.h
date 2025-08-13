//
// Created by Unquery on 2025-08-13.
//

#ifndef UI_H
#define UI_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

sf::Text makeText(const sf::Font& font, const std::string& str, unsigned size,
                  sf::Color color, sf::Vector2f pos, sf::Uint32 style = sf::Text::Regular);

#endif //UI_H

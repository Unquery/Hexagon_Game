//
// Created by Unquery on 2025-08-13.
//

#ifndef GAME_H
#define GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Board.h"

class Game {
public:
    int run();

private:
    bool withPlayer_ = false;
    bool play_ = false;
    std::string winner_;

    static void setUpMenu(const sf::Sprite &bg, sf::RenderWindow &menu, const sf::Text& player, const sf::Text& computer, const sf::Text& name,
                   const sf::Text& exitBtn, const sf::Text& bestLbl);

    void showMenu(sf::Font& font, const sf::Sprite& bg,
                  std::array<int, 6>& scores, sf::Text& scoreText);

    void showResults(sf::Font& font, const sf::Sprite& bg) const;

    void endGame(std::array<int, cfg::BEST_SCORES + 1> &scores, sf::RenderWindow &window, int countRed, int countBlue);

};

#endif //GAME_H

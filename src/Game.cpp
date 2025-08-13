//
// Created by Unquery on 2025-08-13.
//
#include "Game.h"
#include "Config.h"
#include "UI.h"
#include "Score.h"
#include <algorithm>
#include <iostream>

void Game::setUpMenu(const sf::Sprite &bg, sf::RenderWindow &menu, const sf::Text& player, const sf::Text& computer,
                     const sf::Text& name, const sf::Text& exitBtn, const sf::Text& bestLbl) {
    menu.clear();
    menu.draw(bg);
    menu.draw(player);
    menu.draw(computer);
    menu.draw(name);
    menu.draw(exitBtn);
    menu.draw(bestLbl);
}

void Game::showMenu(sf::Font& font, const sf::Sprite& bg,
                    std::array<int,6>& scores, sf::Text& scoreText) {

    sf::RenderWindow menu(sf::VideoMode(cfg::WINDOW_W, cfg::WINDOW_H), "Menu");

    auto player   = makeText(font, "PVP",     50, sf::Color::Green, {250.f, 300.f}, sf::Text::Bold);
    auto computer = makeText(font, "PVE",     50, sf::Color::Green, {450.f, 300.f}, sf::Text::Bold);
    auto name     = makeText(font, "Hexagon",100, sf::Color::Red,   {200.f, 100.f}, sf::Text::Italic);
    auto exitBtn  = makeText(font, "EXIT",    50, sf::Color::Green, {630.f, 500.f}, sf::Text::Bold);
    auto bestLbl  = makeText(font, "Best Scores", 30, sf::Color::Blue, {40.f, 360.f}, sf::Text::Bold);

    while (menu.isOpen()) {
        sf::Event e{};
        while (menu.pollEvent(e)) {
            if (e.type == sf::Event::Closed) menu.close();
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f m = menu.mapPixelToCoords(sf::Mouse::getPosition(menu));
                if (player.getGlobalBounds().contains(m))   { withPlayer_ = true;  play_ = true; menu.close(); }
                else if (computer.getGlobalBounds().contains(m)) { withPlayer_ = false; play_ = true; menu.close(); }
                else if (exitBtn.getGlobalBounds().contains(m))  { menu.close(); }
            }
        }

        setUpMenu(bg, menu, player, computer, name, exitBtn, bestLbl);

        float y = 400.f;
        for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) {
            scoreText.setPosition({100.f, y});
            scoreText.setString(std::to_string(scores[i]));
            menu.draw(scoreText);
            y += 35.f;
        }

        menu.display();
    }
}

void Game::showResults(sf::Font& font, const sf::Sprite& bg) const {
    if (winner_.empty()) return;
    sf::RenderWindow result(sf::VideoMode(cfg::WINDOW_W, cfg::WINDOW_H), "Results");
    auto resultsTxt = makeText(font, winner_, 70, sf::Color::Green, {120.f, 195.f}, sf::Text::Bold);
    auto exitBtn    = makeText(font, "EXIT",  50, sf::Color::Green, {630.f, 500.f}, sf::Text::Bold);

    while (result.isOpen()) {
        sf::Event e{};
        while (result.pollEvent(e)) {
            if (e.type == sf::Event::Closed) result.close();
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f m = result.mapPixelToCoords(sf::Mouse::getPosition(result));
                if (exitBtn.getGlobalBounds().contains(m)) result.close();
            }
        }
        result.clear();
        result.draw(bg);
        result.draw(resultsTxt);
        result.draw(exitBtn);
        result.display();
    }
}

void Game::endGame(std::array<int, cfg::BEST_SCORES + 1> &scores, sf::RenderWindow &window, int countRed, int countBlue) {
    if (countRed > countBlue) {
        winner_ = "Red is the Winner!\nWith the score " +
                  std::to_string(countRed); scores[cfg::BEST_SCORES] = countRed;
    }
    else if (countRed < countBlue) {
        winner_ = "Blue is the Winner!\nWith the score " +
                  std::to_string(countBlue); scores[cfg::BEST_SCORES] = countBlue;
    }
    else {
        winner_ = "It is a Tie!"; scores[cfg::BEST_SCORES] = countRed;
    }
    window.close();
}

int Game::run() {

    sf::Font font;
    sf::Texture texture;

    font.loadFromFile(cfg::FONT_PATH);
    texture.loadFromFile(cfg::SPACE_IMG);

    sf::Sprite space(texture);

    std::array<int, cfg::BEST_SCORES + 1> scores{};
    {
        auto best = readBestScores();
        for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) scores[i] = best[i];
        scores[cfg::BEST_SCORES] = 0;
    }

    sf::Text scoreText = makeText(font, "", 30, sf::Color::Blue, {100.f, 400.f}, sf::Text::Bold);
    showMenu(font, space, scores, scoreText);
    if (!play_) return 0;

    // HUD
    sf::RenderWindow window(sf::VideoMode(cfg::WINDOW_W, cfg::WINDOW_H), "Game");
    auto blueTxt = makeText(font, "0", 50, sf::Color::Blue, {680.f, 500.f}, sf::Text::Bold);
    auto redTxt  = makeText(font, "0", 50, sf::Color::Red,  {680.f, 440.f}, sf::Text::Bold);
    auto exitBtn = makeText(font, "EXIT", 50, sf::Color::Green, {100.f, 500.f}, sf::Text::Bold);

    Board board;

    std::vector<Hexagon*> painted;
    int toMove = 1;
    Hexagon tempPrev(cfg::HEX_RADIUS, 0);
    Hexagon* prevHex = &tempPrev;

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) if (e.type == sf::Event::Closed) window.close();

        window.clear();
        window.draw(space);

        int countRed = 0, countBlue = 0;
        bool finished = false;
        board.placeAndDraw(window, countRed, countBlue, finished);


        if (!finished) {
            finished = true;
            int L = -2, hexNum = 0;
            for (const auto& layer : board.playLayers()) {
                L++; hexNum = 0;
                if (L != -1 && L != 0 && L != 10 && L != 11) {
                    for (const auto& hex : layer) {
                        if (hex && hex->team() == toMove) {
                            auto surr = board.toPaintH(L, hexNum);
                            for (auto* c : surr) { if (c && !c->hasTeam()) { finished = false; break; } }
                        }
                        if (!finished) break;
                        ++hexNum;
                    }
                }
                if (!finished) break;
            }
        }

        if (finished) {
            endGame(scores, window, countRed, countBlue);
        }

        blueTxt.setString(std::to_string(countBlue));
        redTxt.setString(std::to_string(countRed));

        window.draw(blueTxt);
        window.draw(redTxt);
        window.draw(exitBtn);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f m = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (exitBtn.getGlobalBounds().contains(m)) { window.close(); }
            else {
                int L = -2, hexNum = 0;
                for (const auto& layer : board.playLayers()) {
                    L++;
                    hexNum = 0;
                    if (L != -1 && L != 0 && L != 10 && L != 11) {
                        for (const auto& hex : layer) {
                            if (hex) {
                                const auto pos = hex->getPosition();
                                const float r = hex->getRadius();
                                sf::FloatRect rect(pos.x, pos.y, r * 2.f - 5.f, r * 2.f - 5.f);
                                if (rect.contains(m) && (hex->team() == toMove || hex->isOutlined())) {
                                    if (hex->isOutlined()) {
                                        hex->setTeam(prevHex->team());
                                        if (!hex->isGreen()) {
                                            prevHex->setTeam(0);
                                        }
                                        for (auto* h : painted) h->clearOutline();
                                        painted.clear();
                                        auto cap = board.toCapture(L, hexNum);
                                        for (auto* c : cap) if (c && c->hasTeam()) c->setTeam(hex->team());
                                        toMove *= -1;
                                    } else {
                                        for (auto* h : painted) h->clearOutline();
                                        painted.clear();
                                        prevHex = hex;
                                        auto options = board.toPaintH(L, hexNum);
                                        for (std::size_t i = 0; i < options.size(); ++i) {
                                            if (options[i]) {
                                                if (i < 6) options[i]->setOutlineGreen();
                                                else       options[i]->setOutlineYellow();
                                                painted.push_back(options[i]);
                                            }
                                        }
                                    }

                                    if (!withPlayer_ && toMove == -1) {
                                        int NumberLayer = -2, ChoiceLayer = 0, ChoiceNum = 0, hexIdx = 0;
                                        toMove *= -1;
                                        Hexagon* location = nullptr;
                                        Hexagon* choice = nullptr;
                                        int bestPotential = -1;
                                        bool toCopyChoice = false;
                                        bool toCopy = false;

                                        for (const auto& layerC : board.playLayers()) {
                                            NumberLayer++; hexIdx = 0;
                                            if (NumberLayer != -1 && NumberLayer != 0 && NumberLayer != 10 && NumberLayer != 11) {
                                                for (const auto& blueH : layerC) {
                                                    if (blueH && blueH->team() == -1) {
                                                        auto surrounding = board.toPaintH(NumberLayer, hexIdx);
                                                        for (int j = 0; j < (int)surrounding.size(); ++j) {
                                                            toCopy = false;
                                                            auto* s = surrounding[j];
                                                            if (s && !s->hasTeam()) {
                                                                auto posIdx = board.getPos(NumberLayer, hexIdx, j);
                                                                auto cap = board.toCapture(posIdx[0], posIdx[1]);
                                                                if (j < 6) toCopy = true;

                                                                int potential = 0;
                                                                for (auto* c : cap) if (c && c->team() == 1) ++potential;

                                                                if (potential >= bestPotential) {
                                                                    location = const_cast<Hexagon*>(blueH);
                                                                    choice = s;
                                                                    ChoiceLayer = posIdx[0];
                                                                    ChoiceNum = posIdx[1];
                                                                    toCopyChoice = toCopy;
                                                                    bestPotential = potential;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    ++hexIdx;
                                                }
                                            }
                                        }
                                        if (choice) {
                                            if (toCopyChoice) choice->setTeam(-1);
                                            else { if (location) location->setTeam(0); choice->setTeam(-1); }
                                            auto cap = board.toCapture(ChoiceLayer, ChoiceNum);
                                            for (auto* c : cap) if (c && c->team() == 1) c->setTeam(-1);
                                        }
                                    }
                                }
                            }
                            ++hexNum;
                        }
                    }
                }
            }
        }

        window.display();
    }

    if (scores[cfg::BEST_SCORES] <= 0) scores[cfg::BEST_SCORES] = 1;
    auto all = scores;
    std::sort(all.begin(), all.end(), std::greater<int>());
    std::array<int, cfg::BEST_SCORES> top{};
    for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) top[i] = all[i];
    writeBestScores(top);

    showResults(font, space);
    return 0;
}

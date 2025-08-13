//
// Created by Unquery on 2025-08-13.
//

#ifndef HEXAGON_H
#define HEXAGON_H

#pragma once
#include <SFML/Graphics.hpp>

class Hexagon {
    sf::CircleShape shape_;
    int team_{0};
    bool outlined_{false};
    bool greenOutline_{false};

    static sf::Color colorForTeam(int team);

public:
    Hexagon(float radius, int team);

    void setPos(float x, float y);

    const sf::CircleShape& getShape() const;

    float getRadius() const;

    const sf::Vector2f& getPosition() const;

    int team() const;

    bool hasTeam() const;

    void setTeam(int t);

    void setOutlineGreen();

    void setOutlineYellow();

    void clearOutline();

    bool isOutlined() const;

    bool isGreen() const;
};

#endif //HEXAGON_H

//
// Created by Unquery on 2025-08-13.
//

#include "Hexagon.h"

static sf::Color colorFor(int team) {
    switch (team) {
        case  1: return {255, 0, 0};
        case -1: return {0, 0, 255};
        default: return {255, 255, 255};
    }
}

sf::Color Hexagon::colorForTeam(int team) { return colorFor(team); }

Hexagon::Hexagon(float radius, int team) : team_(team) {
    shape_ = sf::CircleShape(radius, 6);
    shape_.setFillColor(colorForTeam(team_));
}

void Hexagon::setPos(float x, float y) { shape_.setPosition({x, y}); }

const sf::CircleShape& Hexagon::getShape() const { return shape_; }

float Hexagon::getRadius() const { return shape_.getRadius(); }

const sf::Vector2f& Hexagon::getPosition() const { return shape_.getPosition(); }

int Hexagon::team() const { return team_; }

bool Hexagon::hasTeam() const { return team_ != 0; }

void Hexagon::setTeam(int t) { team_ = t; shape_.setFillColor(colorForTeam(team_)); }

void Hexagon::setOutlineGreen() {
    if (team_ == 0) {
        shape_.setOutlineColor(sf::Color(0, 255, 0));
        shape_.setOutlineThickness(3.f);
        outlined_ = true; greenOutline_ = true;
    }
}

void Hexagon::setOutlineYellow() {
    if (team_ == 0) {
        shape_.setOutlineColor(sf::Color(255, 244, 0));
        shape_.setOutlineThickness(3.f);
        outlined_ = true; greenOutline_ = false;
    }
}

void Hexagon::clearOutline() { shape_.setOutlineThickness(0.f); outlined_ = false; greenOutline_ = false; }

bool Hexagon::isOutlined() const { return outlined_; }

bool Hexagon::isGreen()    const { return greenOutline_; }

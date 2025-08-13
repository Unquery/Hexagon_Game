//
// Created by Unquery on 2025-08-13.
//

#ifndef BOARD_H
#define BOARD_H

#pragma once
#include <array>
#include <vector>
#include "Hexagon.h"
#include "Config.h"

class Board {
public:
    Board();
    void placeAndDraw(sf::RenderTarget& target, int& redCount, int& blueCount,
                      bool& finished) const;

    std::array<Hexagon*, 18> toPaintH(int layerNum, int hexNum);
    std::array<Hexagon*,  6> toCapture(int layerNum, int hexNum);
    static std::array<int, 2>       getPos(int PrevLayer, int PrevNum, int CurrNum);

    const std::array<std::array<Hexagon*,13>, 9>& drawLayers() const { return drawLayers_; }
    const std::array<std::array<Hexagon*,13>,13>& playLayers() const { return playLayers_; }

private:
    std::array<Hexagon*,13> layer02_{}, layer01_{}, layer1_{}, layer2_{}, layer3_{}, layer4_{}, layer5_{},
                            layer6_{}, layer7_{}, layer8_{}, layer9_{}, layer10_{}, layer11_{};
    std::array<std::array<Hexagon*, 13>, 9>  drawLayers_{};
    std::array<std::array<Hexagon*, 13>, 13> playLayers_{};
};


#endif //BOARD_H

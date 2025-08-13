//
// Created by Unquery on 2025-08-13.
//
#include "Board.h"
#include <SFML/Graphics.hpp>

Board::Board() {
    layer02_.fill(nullptr);
    layer01_.fill(nullptr);
    layer10_.fill(nullptr);
    layer11_.fill(nullptr);

    layer1_  = {nullptr,nullptr,new Hexagon(cfg::HEX_RADIUS,1),  new Hexagon(cfg::HEX_RADIUS,0),
                new Hexagon(cfg::HEX_RADIUS,0), new Hexagon(cfg::HEX_RADIUS,0),
                new Hexagon(cfg::HEX_RADIUS,-1),nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

    layer2_  = {nullptr,nullptr,new Hexagon(cfg::HEX_RADIUS,0), new Hexagon(cfg::HEX_RADIUS,0),
                new Hexagon(cfg::HEX_RADIUS,0), new Hexagon(cfg::HEX_RADIUS,0),
                new Hexagon(cfg::HEX_RADIUS,0), new Hexagon(cfg::HEX_RADIUS,0),
                nullptr,nullptr,nullptr,nullptr,nullptr};

    layer3_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), nullptr, nullptr, nullptr, nullptr};

    layer4_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0), nullptr,
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), nullptr, nullptr, nullptr};

    layer5_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS, -1), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), nullptr, new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 1), nullptr, nullptr};

    layer6_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                nullptr, new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0), nullptr, nullptr};

    layer7_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), nullptr, nullptr};

    layer8_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0), nullptr, nullptr};

    layer9_  = {nullptr, nullptr, new Hexagon(cfg::HEX_RADIUS,  1), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, 0), new Hexagon(cfg::HEX_RADIUS, 0),
                new Hexagon(cfg::HEX_RADIUS, -1), nullptr, nullptr};

    drawLayers_ = {layer1_, layer2_, layer3_, layer4_, layer5_, layer6_, layer7_, layer8_, layer9_};
    playLayers_ = {layer02_, layer01_, layer1_, layer2_, layer3_, layer4_, layer5_, layer6_, layer7_, layer8_, layer9_, layer10_, layer11_};
}

void Board::placeAndDraw(sf::RenderTarget& target, int& countRed, int& countBlue, bool& finished) const {
    finished = true;
    int layerNum = 0;
    float xHex = cfg::HEX_X_START;
    float yHex = 100.f;
    float count = 0.f;
    countRed = 0;
    countBlue = 0;

    for (const auto& layer : drawLayers_) {
        layerNum++;
        for (const auto& hex : layer) {
            if (hex) {
                hex->setPos(xHex, yHex);
                target.draw(hex->getShape());
                if (!hex->hasTeam()) {
                    finished = false;
                } else {
                    if (hex->team() == 1) ++countRed; else ++countBlue;
                }
            }
            xHex += cfg::HEX_STEP_X;
        }
        yHex += cfg::HEX_STEP_Y;
        if (layerNum >= 5) { count--; xHex = cfg::HEX_X_START - (cfg::HEX_OFFSET * count); }
        else               { count++; xHex = cfg::HEX_X_START - (cfg::HEX_OFFSET * count); }
    }
}

std::array<int, 2> Board::getPos(int PrevLayer, int PrevNum, int CurrNum) {
    if (PrevLayer == 1 || PrevLayer == 2 || PrevLayer == 3) {
        switch (CurrNum) {
            case 0:  return {PrevLayer, PrevNum - 1};
            case 1:  return {PrevLayer, PrevNum + 1};
            case 2:  return {PrevLayer + 1, PrevNum};
            case 3:  return {PrevLayer + 1, PrevNum + 1};
            case 4:  return {PrevLayer - 1, PrevNum};
            case 5:  return {PrevLayer - 1, PrevNum - 1};
            case 6:  return {PrevLayer + 2, PrevNum};
            case 7:  return {PrevLayer + 2, PrevNum + 1};
            case 8:  return {PrevLayer + 2, PrevNum + 2};
            case 9:  return {PrevLayer + 1, PrevNum - 1};
            case 10: return {PrevLayer + 1, PrevNum + 2};
            case 11: return {PrevLayer, PrevNum - 2};
            case 12: return {PrevLayer, PrevNum + 2};
            case 13: return {PrevLayer - 1, PrevNum - 2};
            case 14: return {PrevLayer - 1, PrevNum + 1};
            case 15: return {PrevLayer - 2, PrevNum - 2};
            case 16: return {PrevLayer - 2, PrevNum - 1};
            case 17: return {PrevNum - 2, PrevNum};
            default: return {0, 0};
        }
    }
    if (PrevLayer == 4) {
        switch (CurrNum) {
            case 0:  return {PrevLayer, PrevNum - 1};
            case 1:  return {PrevLayer, PrevNum + 1};
            case 2:  return {PrevLayer + 1, PrevNum};
            case 3:  return {PrevLayer + 1, PrevNum + 1};
            case 4:  return {PrevLayer - 1, PrevNum};
            case 5:  return {PrevLayer - 1, PrevNum - 1};
            case 6:  return {PrevLayer + 2, PrevNum - 1};
            case 7:  return {PrevLayer + 2, PrevNum};
            case 8:  return {PrevLayer + 2, PrevNum + 1};
            case 9:  return {PrevLayer + 1, PrevNum - 1};
            case 10: return {PrevLayer + 1, PrevNum + 2};
            case 11: return {PrevLayer, PrevNum - 2};
            case 12: return {PrevLayer, PrevNum + 2};
            case 13: return {PrevLayer - 1, PrevNum - 2};
            case 14: return {PrevLayer - 1, PrevNum + 1};
            case 15: return {PrevLayer - 2, PrevNum - 2};
            case 16: return {PrevLayer - 2, PrevNum - 1};
            case 17: return {PrevNum - 2, PrevNum};
            default: return {0, 0};
        }
    }
    if (PrevLayer == 5) {
        switch (CurrNum) {
            case 0:  return {PrevLayer, PrevNum - 1};
            case 1:  return {PrevLayer, PrevNum + 1};
            case 2:  return {PrevLayer + 1, PrevNum - 1};
            case 3:  return {PrevLayer + 1, PrevNum};
            case 4:  return {PrevLayer - 1, PrevNum};
            case 5:  return {PrevLayer - 1, PrevNum - 1};
            case 6:  return {PrevLayer + 2, PrevNum - 2};
            case 7:  return {PrevLayer + 2, PrevNum - 1};
            case 8:  return {PrevLayer + 2, PrevNum};
            case 9:  return {PrevLayer + 1, PrevNum - 2};
            case 10: return {PrevLayer + 1, PrevNum + 1};
            case 11: return {PrevLayer, PrevNum - 2};
            case 12: return {PrevLayer, PrevNum + 2};
            case 13: return {PrevLayer - 1, PrevNum - 2};
            case 14: return {PrevLayer - 1, PrevNum + 1};
            case 15: return {PrevLayer - 2, PrevNum - 2};
            case 16: return {PrevLayer - 2, PrevNum - 1};
            case 17: return {PrevNum - 2, PrevNum};
            default: return {0, 0};
        }
    }
    if (PrevLayer == 6) {
        switch (CurrNum) {
            case 0:  return {PrevLayer, PrevNum - 1};
            case 1:  return {PrevLayer, PrevNum + 1};
            case 2:  return {PrevLayer + 1, PrevNum};
            case 3:  return {PrevLayer + 1, PrevNum - 1};
            case 4:  return {PrevLayer - 1, PrevNum + 1};
            case 5:  return {PrevLayer - 1, PrevNum};
            case 6:  return {PrevLayer + 2, PrevNum - 2};
            case 7:  return {PrevLayer + 2, PrevNum - 1};
            case 8:  return {PrevLayer + 2, PrevNum};
            case 9:  return {PrevLayer + 1, PrevNum - 2};
            case 10: return {PrevLayer + 1, PrevNum + 1};
            case 11: return {PrevLayer, PrevNum - 2};
            case 12: return {PrevLayer, PrevNum + 2};
            case 13: return {PrevLayer - 1, PrevNum - 1};
            case 14: return {PrevLayer - 1, PrevNum + 2};
            case 15: return {PrevLayer - 2, PrevNum - 1};
            case 16: return {PrevLayer - 2, PrevNum};
            case 17: return {PrevNum - 2, PrevNum + 1};
            default: return {0, 0};
        }
    }
    if (PrevLayer == 7 || PrevLayer == 8 || PrevLayer == 9) {
        switch (CurrNum) {
            case 0:  return {PrevLayer, PrevNum - 1};
            case 1:  return {PrevLayer, PrevNum + 1};
            case 2:  return {PrevLayer + 1, PrevNum};
            case 3:  return {PrevLayer + 1, PrevNum - 1};
            case 4:  return {PrevLayer - 1, PrevNum + 1};
            case 5:  return {PrevLayer - 1, PrevNum};
            case 6:  return {PrevLayer + 2, PrevNum - 2};
            case 7:  return {PrevLayer + 2, PrevNum - 1};
            case 8:  return {PrevLayer + 2, PrevNum};
            case 9:  return {PrevLayer + 1, PrevNum - 2};
            case 10: return {PrevLayer + 1, PrevNum + 1};
            case 11: return {PrevLayer, PrevNum - 2};
            case 12: return {PrevLayer, PrevNum + 2};
            case 13: return {PrevLayer - 1, PrevNum - 1};
            case 14: return {PrevLayer - 1, PrevNum + 2};
            case 15: return {PrevLayer - 2, PrevNum};
            case 16: return {PrevLayer - 2, PrevNum + 1};
            case 17: return {PrevNum - 2, PrevNum + 2};
            default: return {0, 0};
        }
    }
    return {0, 0};
}

std::array<Hexagon*, 18> Board::toPaintH(int layerNum, int hexNum) {
    if (layerNum == 1) {
        return {layer1_[hexNum - 1], layer1_[hexNum + 1],
                layer2_[hexNum], layer2_[hexNum + 1],
                layer01_[hexNum], layer01_[hexNum - 1],
                layer3_[hexNum], layer3_[hexNum + 1], layer3_[hexNum + 2],
                layer2_[hexNum - 1], layer2_[hexNum + 2],
                layer1_[hexNum - 2], layer1_[hexNum + 2],
                layer01_[hexNum - 2], layer01_[hexNum + 1],
                layer02_[hexNum], layer02_[hexNum + 1], layer02_[hexNum + 2]};
    }
    if (layerNum == 2) {
        return {layer2_[hexNum - 1], layer2_[hexNum + 1],
                layer3_[hexNum], layer3_[hexNum + 1],
                layer1_[hexNum], layer1_[hexNum - 1],
                layer4_[hexNum], layer4_[hexNum + 1], layer4_[hexNum + 2],
                layer3_[hexNum - 1], layer3_[hexNum + 2],
                layer2_[hexNum - 2], layer2_[hexNum + 2],
                layer1_[hexNum - 2], layer1_[hexNum + 1],
                layer01_[hexNum], layer01_[hexNum + 1], layer01_[hexNum + 2]};
    }
    if (layerNum == 3) {
        return {layer3_[hexNum - 1], layer3_[hexNum + 1],
                layer4_[hexNum], layer4_[hexNum + 1],
                layer2_[hexNum], layer2_[hexNum - 1],
                layer5_[hexNum], layer5_[hexNum + 1], layer5_[hexNum + 2],
                layer4_[hexNum - 1], layer4_[hexNum + 2],
                layer3_[hexNum - 2], layer3_[hexNum + 2],
                layer2_[hexNum - 2], layer2_[hexNum + 1],
                layer1_[hexNum - 2], layer1_[hexNum - 1], layer1_[hexNum]};
    }
    if (layerNum == 4) {
        return {layer4_[hexNum - 1], layer4_[hexNum + 1],
                layer5_[hexNum], layer5_[hexNum + 1],
                layer3_[hexNum], layer3_[hexNum - 1],
                layer6_[hexNum - 1], layer6_[hexNum], layer6_[hexNum + 1],
                layer5_[hexNum - 1], layer5_[hexNum + 2],
                layer4_[hexNum - 2], layer4_[hexNum + 2],
                layer3_[hexNum - 2], layer3_[hexNum + 1],
                layer2_[hexNum - 2], layer2_[hexNum - 1], layer2_[hexNum]};
    }
    if (layerNum == 5) {
        return {layer5_[hexNum - 1], layer5_[hexNum + 1],
                layer6_[hexNum - 1], layer6_[hexNum],
                layer4_[hexNum], layer4_[hexNum - 1],
                layer7_[hexNum - 2], layer7_[hexNum - 1], layer7_[hexNum],
                layer6_[hexNum - 2], layer6_[hexNum + 1],
                layer5_[hexNum - 2], layer5_[hexNum + 2],
                layer4_[hexNum - 2], layer4_[hexNum + 1],
                layer3_[hexNum - 2], layer3_[hexNum - 1], layer3_[hexNum]};
    }
    if (layerNum == 6) {
        return {layer6_[hexNum - 1], layer6_[hexNum + 1],
                layer7_[hexNum], layer7_[hexNum - 1],
                layer5_[hexNum + 1], layer5_[hexNum],
                layer8_[hexNum - 2], layer8_[hexNum - 1], layer8_[hexNum],
                layer7_[hexNum - 2], layer7_[hexNum + 1],
                layer6_[hexNum - 2], layer6_[hexNum + 2],
                layer5_[hexNum - 1], layer5_[hexNum + 2],
                layer4_[hexNum - 1], layer4_[hexNum], layer4_[hexNum + 1]};
    }
    if (layerNum == 7) {
        return {layer7_[hexNum - 1], layer7_[hexNum + 1],
                layer8_[hexNum], layer8_[hexNum - 1],
                layer6_[hexNum + 1], layer6_[hexNum],
                layer9_[hexNum - 2], layer9_[hexNum - 1], layer9_[hexNum],
                layer8_[hexNum - 2], layer8_[hexNum + 1],
                layer7_[hexNum - 2], layer7_[hexNum + 2],
                layer6_[hexNum - 1], layer6_[hexNum + 2],
                layer5_[hexNum], layer5_[hexNum + 1], layer5_[hexNum + 2]};
    }
    if (layerNum == 8) {
        return {layer8_[hexNum - 1], layer8_[hexNum + 1],
                layer9_[hexNum], layer9_[hexNum - 1],
                layer7_[hexNum + 1], layer7_[hexNum],
                layer10_[hexNum - 2], layer10_[hexNum - 1], layer10_[hexNum],
                layer9_[hexNum - 2], layer9_[hexNum + 1],
                layer8_[hexNum - 2], layer8_[hexNum + 2],
                layer7_[hexNum - 1], layer7_[hexNum + 2],
                layer6_[hexNum], layer6_[hexNum + 1], layer6_[hexNum + 2]};
    }
    if (layerNum == 9) {
        return {layer9_[hexNum - 1], layer9_[hexNum + 1],
                layer10_[hexNum], layer10_[hexNum - 1],
                layer8_[hexNum + 1], layer8_[hexNum],
                layer11_[hexNum - 2], layer11_[hexNum - 1], layer11_[hexNum],
                layer10_[hexNum - 2], layer10_[hexNum + 1],
                layer9_[hexNum - 2], layer9_[hexNum + 2],
                layer8_[hexNum - 1], layer8_[hexNum + 2],
                layer7_[hexNum], layer7_[hexNum + 1], layer7_[hexNum + 2]};
    }
    return {};
}

std::array<Hexagon*, 6> Board::toCapture(int layerNum, int hexNum) {
    if (layerNum == 1) {
        return {layer1_[hexNum - 1], layer1_[hexNum + 1],
                layer2_[hexNum], layer2_[hexNum + 1],
                layer01_[hexNum], layer01_[hexNum - 1]};
    }
    if (layerNum == 2) {
        return {layer2_[hexNum - 1], layer2_[hexNum + 1],
                layer3_[hexNum], layer3_[hexNum + 1],
                layer1_[hexNum], layer1_[hexNum - 1]};
    }
    if (layerNum == 3) {
        return {layer3_[hexNum - 1], layer3_[hexNum + 1],
                layer4_[hexNum], layer4_[hexNum + 1],
                layer2_[hexNum], layer2_[hexNum - 1]};
    }
    if (layerNum == 4) {
        return {layer4_[hexNum - 1], layer4_[hexNum + 1],
                layer5_[hexNum], layer5_[hexNum + 1],
                layer3_[hexNum], layer3_[hexNum - 1]};
    }
    if (layerNum == 5) {
        return {layer5_[hexNum - 1], layer5_[hexNum + 1],
                layer6_[hexNum - 1], layer6_[hexNum],
                layer4_[hexNum], layer4_[hexNum - 1]};
    }
    if (layerNum == 6) {
        return {layer6_[hexNum - 1], layer6_[hexNum + 1],
                layer7_[hexNum], layer7_[hexNum - 1],
                layer5_[hexNum + 1], layer5_[hexNum]};
    }
    if (layerNum == 7) {
        return {layer7_[hexNum - 1], layer7_[hexNum + 1],
                layer8_[hexNum], layer8_[hexNum - 1],
                layer6_[hexNum + 1], layer6_[hexNum]};
    }
    if (layerNum == 8) {
        return {layer8_[hexNum - 1], layer8_[hexNum + 1],
                layer9_[hexNum], layer9_[hexNum - 1],
                layer7_[hexNum + 1], layer7_[hexNum]};
    }
    if (layerNum == 9) {
        return {layer9_[hexNum - 1], layer9_[hexNum + 1],
                layer10_[hexNum], layer10_[hexNum - 1],
                layer8_[hexNum + 1], layer8_[hexNum]};
    }
    return {};
}




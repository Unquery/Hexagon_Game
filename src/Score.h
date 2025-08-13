//
// Created by Unquery on 2025-08-13.
//

#ifndef SCORE_H
#define SCORE_H

#pragma once
#include <array>
#include "Config.h"

std::array<int, cfg::BEST_SCORES> readBestScores();

void writeBestScores(const std::array<int, cfg::BEST_SCORES>& top);

#endif //SCORE_H

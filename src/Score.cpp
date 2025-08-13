//
// Created by Unquery on 2025-08-13.
//

#include "Score.h"
#include <fstream>
#include <iostream>

std::array<int, cfg::BEST_SCORES> readBestScores() {
    std::array<int, cfg::BEST_SCORES> top{};

    for (auto& v : top) {
        v = 0;
    }

    std::ifstream in(cfg::SCORE_TXT);

    if (!in) {
        std::ofstream out(cfg::SCORE_TXT);
        for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) {
            out << 0 << "\n";
        }
        return top;
    }

    for (std::size_t i = 0; i < cfg::BEST_SCORES && in; ++i) {
        in >> top[i];
    }

    return top;
}

void writeBestScores(const std::array<int, cfg::BEST_SCORES>& top) {
    std::ofstream out(cfg::SCORE_TXT, std::ios::trunc);
    for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) {
        std::cout << top[i] << "\n";
    }
    for (std::size_t i = 0; i < cfg::BEST_SCORES; ++i) out << top[i] << "\n";
    out.close();
}

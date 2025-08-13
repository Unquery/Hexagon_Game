//
// Created by Unquery on 2025-08-13.
//

#ifndef CONFIG_H
#define CONFIG_H

#pragma once
#include <filesystem>
#include <string>

namespace cfg {
    constexpr unsigned WINDOW_W = 800;
    constexpr unsigned WINDOW_H = 600;

    constexpr float HEX_RADIUS = 25.f;
    constexpr float HEX_STEP_X = 48.f;
    constexpr float HEX_STEP_Y = 41.f;
    constexpr float HEX_X_START = 200.f;
    constexpr float HEX_OFFSET = 23.3f;

    const std::string PROJECT_DIR = std::filesystem::path(__FILE__).parent_path().parent_path().string();
    const std::string ASSETS_DIR   = PROJECT_DIR + R"(/assets/)";
    const std::string FONT_PATH    = ASSETS_DIR + R"(Fonts/Catalina Village demo.ttf)";
    const std::string SPACE_IMG    = ASSETS_DIR + "space.jpg";
    const std::string SCORE_TXT    = ASSETS_DIR + "scores.txt";

    constexpr std::size_t BEST_SCORES = 5;
}
#endif //CONFIG_H
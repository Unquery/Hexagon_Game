# Hexagon_Game
Hexagon game created using SMFL lib in C++, that allows to play in PvP or PvE format

## Tech stack 💻
* **Language:** C++17 (or later)
* **Framework:** [SFML 2.6.2+](https://www.sfml-dev.org/)
* **Build:** CMake 3.21+
  
## Before play ⏪
* Include your font in Fonts folder before playing
* Update the font path in Config.h

## How to play 🧐
* Players move one by one
* Player can move by one or two cells
* If player moves be one cell, the hexagon is duplicated. If by two cells, it is not duplicated
* When you move, the surrouding hexagons, if they are enemy hexagons, are become yours
* Wins the player with the most hexagons, when there is no possible moves

## Features ✨
* Game allows to play with another player or with computer
* Computer counts all possible moves and choces the best each turn

## Gameplay PvP 👥
https://github.com/user-attachments/assets/3dd93cd3-62f2-48ec-946e-edb195a1f2e9

## Gameplay PvE 🤖
https://github.com/user-attachments/assets/2cc46602-d707-4b51-8fc5-0c21b78538a4


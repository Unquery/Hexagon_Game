# Hexagon_Game
Hexagon game created using SMFL lib in C++, that allows to play in PvP or PvE format

## Tech stack
* **Language:** C++17 (or later)
* **Framework:** [SFML 2.6+](https://www.sfml-dev.org/)
* **Build:** CMake 3.20+
  
## Before play
* Include your font in Fonts folder before playing

## How to play
* Players move one by one
* Player can move by one or two cells
* If player moves be one cell, the hexagon is duplicated. If by two cells, it is not duplicated
* When you move, the surrouding hexagons, if they are enemy hexagons, are become yours
* Wins the player with the most hexagons, when there is no possible moves

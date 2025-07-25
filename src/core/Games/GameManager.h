#pragma once
#include "Game.h"

class GameManager {
public:
  GameManager();

  void loadGame(Game *game);

private:
  unsigned player1Score = 0, player2Score = 0;
};

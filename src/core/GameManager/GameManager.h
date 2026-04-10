#pragma once
#include "../RenderWindow/RenderWindow.h"

class GameManager {
public:
  GameManager();
  void render();

private:
  void setUI();

  unsigned player1Score = 0, player2Score = 0;
  RenderWindow _renderer = RenderWindow(60);
};

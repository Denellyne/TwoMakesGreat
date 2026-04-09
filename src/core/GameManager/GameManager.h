#pragma once
#include "../RenderWindow/RenderWindow.h"
#include <print>

class GameManager {
public:
  GameManager();
  void setUI() {

    std::println("Adding UI elements");
    this->renderer.pushUITexture(
        Entity("../res/background.png", this->renderer.getRenderer()));
    std::println("Added all UI elements");
  }
  void render() { this->renderer.render(); }

private:
  unsigned player1Score = 0, player2Score = 0;
  RenderWindow renderer = RenderWindow(60);
};

#pragma once
#include "../RenderWindow/RenderWindow.h"
#include "../RenderWindow/UI/Counter.h"

class GameManager {
public:
  GameManager();
  void render() {

    bool isRunning = true;
    while (isRunning) {
      this->renderer.render(&isRunning);
      player1Score++;
      player2Score++;
    }
  }

private:
  unsigned player1Score = 0, player2Score = 0;
  RenderWindow renderer = RenderWindow(60);
  void setUI() {

    this->renderer.clearUI();
    this->renderer.clearEntities();
    this->renderer.pushUITexture(
        new Entity("../res/bg/menu.png", this->renderer.getRenderer()));
    this->renderer.pushUITexture(new Counter(
        "../res/ui/counter.jpg", this->renderer.getRenderer(),
        this->renderer.getTTF(), {30, 10}, {100, 50}, &player1Score));
    this->renderer.pushUITexture(new Counter(
        "../res/ui/counter.jpg", this->renderer.getRenderer(),
        this->renderer.getTTF(), {400, 10}, {100, 50}, &player2Score));
  }
};

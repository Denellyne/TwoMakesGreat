#include "GameManager.h"
#include "../RenderWindow/UI/Counter.h"
#include <print>

GameManager::GameManager() {

  std::println("Initializing Game Manager");
  this->setUI();
  this->render();
}

void GameManager::render() {

  bool isRunning = true;
  while (isRunning) {
    this->_renderer.render(&isRunning);
    player1Score++;
    player2Score++;
  }
}

void GameManager::setUI() {

  this->_renderer.clearUI();
  this->_renderer.clearEntities();
  this->_renderer.pushUITexture(std::make_shared<Entity>(
      "../res/bg/menu.png", this->_renderer.getRenderer()));
  this->_renderer.pushUITexture(std::make_shared<Counter>(
      Counter("../res/ui/counter.jpg", this->_renderer.getRenderer(),
              this->_renderer.getTTF(), {30, 10}, {100, 50}, &player1Score)));
  this->_renderer.pushUITexture(std::make_shared<Counter>(
      Counter("../res/ui/counter.jpg", this->_renderer.getRenderer(),
              this->_renderer.getTTF(), {900, 10}, {100, 50}, &player2Score)));
}

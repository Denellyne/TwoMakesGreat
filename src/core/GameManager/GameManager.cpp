#include "GameManager.h"
#include <print>

GameManager::GameManager() {

  std::println("Initializing Game Manager");
  this->setUI();
  this->render();
}

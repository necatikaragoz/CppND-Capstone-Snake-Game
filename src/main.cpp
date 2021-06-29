#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


static std::shared_ptr<Renderer> pRenderer;
static std::shared_ptr<Controller> pController;
static std::unique_ptr<Game> pGame;

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  pRenderer = std::make_shared<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  pController = std::make_shared<Controller>();
  pGame       = std::make_unique<Game>(kGridWidth, kGridHeight);
  pGame.get()->Run(pController, pRenderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << pGame.get()->GetScore() << "\n";
  std::cout << "Size: " << pGame.get()->GetSize() << "\n";
  return 0;
}
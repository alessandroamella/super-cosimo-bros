#include "gamemanager/gamemanager.hpp"

int main() {
    GameManager game_manager;
    game_manager.begin();
    game_manager.cleanup();

    return 0;
}
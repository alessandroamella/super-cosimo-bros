#include "layout11.hpp"

Room* layout11() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 30; i++) {
        floor.push(7);
    }
    for (int i = GAME_WIDTH - 30; i < GAME_WIDTH; i++) {
        floor.push(26);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    Platform _platform1((Position){.x = 0, .y = 20}, (Position){.x = 60, .y = 23});
    Platform _platform2((Position){.x = 39, .y = 15}, (Position){.x = 69, .y = 18});
    Platform _platform3((Position){.x = 55, .y = 11}, (Position){.x = 82, .y = 14});
    Platform _platform4((Position){.x = 67, .y = 21}, (Position){.x = 97, .y = 24});



    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);


    StaticBox start_region = StaticBox((Position){.x = 0, .y = 23}, (Position){.x = 10, .y = 28});
    StaticBox end_region = StaticBox((Position){.x = 110, .y = 26}, (Position){.x = 120, .y = 31});

    Room* layout11 = new Room(11, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout11;
}
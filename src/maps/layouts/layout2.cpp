#include "layout2.hpp"

Room* layout2() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 100; i++) {
        floor.push(2);
    }
    for (int i = GAME_WIDTH - 100; i < GAME_WIDTH - 85; i++) {
        floor.push(4);
    }
    for (int i = GAME_WIDTH - 85; i < GAME_WIDTH - 70; i++) {
        floor.push(6);
    }
    for (int i = GAME_WIDTH - 70; i < GAME_WIDTH - 55; i++) {
        floor.push(8);
    }
    for (int i = GAME_WIDTH - 55; i < GAME_WIDTH - 40; i++) {
        floor.push(10);
    }
    for (int i = GAME_WIDTH - 40; i < GAME_WIDTH; i++) {
        floor.push(25);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;
    Platform _platform1((Position){.x = 5, .y = 15}, (Position){.x = 75, .y = 17});
    Platform _platform2((Position){.x = 25, .y = 23}, (Position){.x = 35, .y = 24});
    Platform _platform3((Position){.x = 36, .y = 26}, (Position){.x = 55, .y = 27});
    Platform _platform4((Position){.x = 56, .y = 29}, (Position){.x = 87, .y = 30});

    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);

    StaticBox start_region = StaticBox((Position){.x = 1, .y = 3}, (Position){.x = 7, .y = 6});
    StaticBox end_region = StaticBox((Position){.x = 111, .y = 30}, (Position){.x = 121, .y = 32});

    Room* layout2 = new Room(2, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout2;
}
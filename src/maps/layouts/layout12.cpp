#include "layout12.hpp"

Room* layout12() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 30; i++) {
        floor.push(1);
    }
    for (int i = GAME_WIDTH - 30; i < GAME_WIDTH; i++) {
        floor.push(26);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    Platform _platform1((Position){.x = 5, .y = 7}, (Position){.x = 20, .y = 26});
    Platform _platform2((Position){.x = 20, .y = 7}, (Position){.x = 50, .y = 12});

    Platform _platform3((Position){.x = 78, .y = 2}, (Position){.x = 90, .y = 3});
    Platform _platform4((Position){.x = 68, .y = 5}, (Position){.x = 80, .y = 6});
    Platform _platform5((Position){.x = 55, .y = 9}, (Position){.x = 70, .y = 10});
    Platform _platform6((Position){.x = 68, .y = 13}, (Position){.x = 80, .y = 14});
    Platform _platform7((Position){.x = 78, .y = 17}, (Position){.x = 90, .y = 18});
    Platform _platform8((Position){.x = 88, .y = 21}, (Position){.x = 100, .y = 22});



    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);
    platforms.push(_platform5);
    platforms.push(_platform6);
    platforms.push(_platform7);
    platforms.push(_platform8);


    StaticBox start_region = StaticBox((Position){.x = 5, .y = 26}, (Position){.x = 15, .y = 31});
    StaticBox end_region = StaticBox((Position){.x = 110, .y = 26}, (Position){.x = 120, .y = 31});

    Room* layout12 = new Room(12, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout12;
}
#include "layout6.hpp"

Room* layout6() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH; i++) {
        floor.push(1);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    // FLOORS
    Platform _platform1((Position){.x = 15, .y = 27}, (Position){.x = 115, .y = 29});
    Platform _platform2((Position){.x = 0, .y = 22}, (Position){.x = 74, .y = 24});
    Platform _platform3((Position){.x = 77, .y = 22}, (Position){.x = 130, .y = 24});
    Platform _platform4((Position){.x = 0, .y = 16}, (Position){.x = 14, .y = 18});
    Platform _platform5((Position){.x = 17, .y = 16}, (Position){.x = 28, .y = 18});
    Platform _platform6((Position){.x = 31, .y = 16}, (Position){.x = 55, .y = 18});
    Platform _platform7((Position){.x = 58, .y = 16}, (Position){.x = 130, .y = 18});
    Platform _platform8((Position){.x = 15, .y = 7}, (Position){.x = 115, .y = 9});




    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);
    platforms.push(_platform5);
    platforms.push(_platform6);
    platforms.push(_platform7);
    platforms.push(_platform8);


    StaticBox start_region = StaticBox((Position){.x = 60, .y = 29}, (Position){.x = 70, .y = 33});
    StaticBox end_region = StaticBox((Position){.x = 5, .y = 0}, (Position){.x = 15, .y = 5});

    Room* layout6 = new Room(6, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout6;
}
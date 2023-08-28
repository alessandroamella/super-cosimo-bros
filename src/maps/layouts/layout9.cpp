#include "layout9.hpp"

Room* layout9() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 125; i++) {
        floor.push(14);
    }
    for (int i = GAME_WIDTH - 125; i < GAME_WIDTH - 120; i++) {
        floor.push(10);
    }
    for (int i = GAME_WIDTH - 120; i < GAME_WIDTH - 115; i++) {
        floor.push(6);
    }
    for (int i = GAME_WIDTH - 115; i < GAME_WIDTH - 110; i++) {
        floor.push(2);
    }
    for (int i = GAME_WIDTH - 110; i < GAME_WIDTH; i++) {
        floor.push(1);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    Platform _platform1((Position){.x = 15, .y = 10}, (Position){.x = 19, .y = 33});
    Platform _platform2((Position){.x = 5, .y = 19}, (Position){.x = 15, .y = 20});
    Platform _platform3((Position){.x = 19, .y = 10}, (Position){.x = 95, .y = 12});
    Platform _platform4((Position){.x = 95, .y = 10}, (Position){.x = 99, .y = 25});
    Platform _platform5((Position){.x = 19, .y = 14}, (Position){.x = 50, .y = 15});
    Platform _platform6((Position){.x = 45, .y = 17}, (Position){.x = 95, .y = 18});
    Platform _platform7((Position){.x = 73, .y = 20}, (Position){.x = 95, .y = 22});
    Platform _platform8((Position){.x = 19, .y = 25}, (Position){.x = 40, .y = 27});


    Platform _platform9((Position){.x = 99, .y = 24}, (Position){.x = 105, .y = 25});
    Platform _platform10((Position){.x = 99, .y = 20}, (Position){.x = 110, .y = 21});
    Platform _platform11((Position){.x = 99, .y = 16}, (Position){.x = 115, .y = 17});
    Platform _platform12((Position){.x = 99, .y = 12}, (Position){.x = 120, .y = 13});

    Platform _platform13((Position){.x = 0, .y = 27}, (Position){.x = 15, .y = 29});
    Platform _platform14((Position){.x = 45, .y = 25}, (Position){.x = 74, .y = 27});


    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);
    platforms.push(_platform5);
    platforms.push(_platform6);
    platforms.push(_platform7);
    platforms.push(_platform8);
    platforms.push(_platform9);
    platforms.push(_platform10);
    platforms.push(_platform11);
    platforms.push(_platform12);
    platforms.push(_platform13);
    platforms.push(_platform14);


    StaticBox start_region = StaticBox((Position){.x = 20, .y = 27}, (Position){.x = 30, .y = 32});
    StaticBox end_region = StaticBox((Position){.x = 5, .y = 22}, (Position){.x = 15, .y = 27});

    Room* layout9 = new Room(9, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout9;
}
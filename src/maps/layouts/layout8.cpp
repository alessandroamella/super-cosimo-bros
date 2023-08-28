#include "layout8.hpp"

Room* layout8() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH; i++) {
        floor.push(1);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    Platform _platform1((Position){.x = 15, .y = 10}, (Position){.x = 19, .y = 31});
    Platform _platform2((Position){.x = 19, .y = 10}, (Position){.x = 112, .y = 12});
    Platform _platform3((Position){.x = 19, .y = 29}, (Position){.x = 42, .y = 31});
    Platform _platform4((Position){.x = 42, .y = 16}, (Position){.x = 46, .y = 31});
    Platform _platform5((Position){.x = 46, .y = 29}, (Position){.x = 97, .y = 31});
    Platform _platform6((Position){.x = 108, .y = 12}, (Position){.x = 112, .y = 31});
    Platform _platform7((Position){.x = 112, .y = 29}, (Position){.x = 130, .y = 31});

    Platform _platform8((Position){.x = 70, .y = 15}, (Position){.x = 108, .y = 17});
    Platform _platform9((Position){.x = 82, .y = 19}, (Position){.x = 108, .y = 21});
    Platform _platform10((Position){.x = 94, .y = 23}, (Position){.x = 108, .y = 25});


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


    StaticBox start_region = StaticBox((Position){.x = 25, .y = 22}, (Position){.x = 35, .y = 27});
    StaticBox end_region = StaticBox((Position){.x = 100, .y = 1}, (Position){.x = 110, .y = 6});

    Room* layout8 = new Room(8, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout8;
}
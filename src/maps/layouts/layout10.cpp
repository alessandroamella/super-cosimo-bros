#include "layout10.hpp"

Room* layout10() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 60; i++) {
        floor.push(10);
    }
    for (int i = GAME_WIDTH - 60; i < GAME_WIDTH - 55; i++) {
        floor.push(30);
    }
    for (int i = GAME_WIDTH - 55; i < GAME_WIDTH; i++) {
        floor.push(7);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;

    // Platform Mix
    Platform _platform1((Position){.x = 25, .y = 12}, (Position){.x = 40, .y = 13});
    Platform _platform2((Position){.x = 50, .y = 14}, (Position){.x = 65, .y = 15});
    Platform _platform3((Position){.x = 31, .y = 15}, (Position){.x = 45, .y = 16});
    Platform _platform4((Position){.x = 0, .y = 17}, (Position){.x = 32, .y = 18});
    Platform _platform5((Position){.x = 60, .y = 17}, (Position){.x = 66, .y = 18});
    Platform _platform6((Position){.x = 37, .y = 18}, (Position){.x = 41, .y = 19});
    Platform _platform7((Position){.x = 43, .y = 22}, (Position){.x = 61, .y = 23});
    Platform _platform8((Position){.x = 15, .y = 24}, (Position){.x = 33, .y = 25});
    Platform _platform9((Position){.x = 32, .y = 26}, (Position){.x = 55, .y = 27});
    Platform _platform10((Position){.x = 19, .y = 30}, (Position){.x = 32, .y = 31});
    Platform _platform11((Position){.x = 44, .y = 31}, (Position){.x = 51, .y = 32});
    Platform _platform12((Position){.x = 53, .y = 30}, (Position){.x = 65, .y = 31});
    Platform _platform13((Position){.x = 67, .y = 27}, (Position){.x = 70, .y = 28});
    
    // Second "part"
    Platform _platform14((Position){.x = 85, .y = 25}, (Position){.x = 130, .y = 26});
    Platform _platform15((Position){.x = 80, .y = 22}, (Position){.x = 100, .y = 23});
    Platform _platform16((Position){.x = 95, .y = 18}, (Position){.x = 115, .y = 19});
    Platform _platform17((Position){.x = 88, .y = 14}, (Position){.x = 107, .y = 15});
    Platform _platform18((Position){.x = 78, .y = 10}, (Position){.x = 98, .y = 11});


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
    platforms.push(_platform15);
    platforms.push(_platform16);
    platforms.push(_platform17);
    platforms.push(_platform18);


    StaticBox start_region = StaticBox((Position){.x = 0, .y = 10}, (Position){.x = 10, .y = 15});
    StaticBox end_region = StaticBox((Position){.x = 110, .y = 26}, (Position){.x = 120, .y = 31});

    Room* layout10 = new Room(10, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout10;
}
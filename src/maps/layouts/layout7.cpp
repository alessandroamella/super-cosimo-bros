#include "layout7.hpp"

Room* layout7() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 60; i++) {
        floor.push(1);
    }
    for (int i = GAME_WIDTH - 60; i < GAME_WIDTH - 55; i++) {
        floor.push(7);
    }
    for (int i = GAME_WIDTH - 55; i < GAME_WIDTH - 50; i++) {
        floor.push(5);
    }
    for (int i = GAME_WIDTH - 50; i < GAME_WIDTH - 45; i++) {
        floor.push(3);
    }
    for (int i = GAME_WIDTH - 45; i < GAME_WIDTH; i++) {
        floor.push(1);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;

    // FLOORS
    Platform _platform1((Position){.x = 90, .y = 27}, (Position){.x = 104, .y = 29});
    Platform _platform2((Position){.x = 35, .y = 30}, (Position){.x = 90, .y = 32});
    Platform _platform3((Position){.x = 86, .y = 27}, (Position){.x = 90, .y = 30});
    Platform _platform4((Position){.x = 15, .y = 18}, (Position){.x = 35, .y = 20});
    Platform _platform5((Position){.x = 30, .y = 15}, (Position){.x = 60, .y = 17});
    Platform _platform6((Position){.x = 55, .y = 12}, (Position){.x = 80, .y = 14});
    Platform _platform7((Position){.x = 0, .y = 9}, (Position){.x = 99, .y = 11});
    Platform _platform8((Position){.x = 104, .y = 23}, (Position){.x = 129, .y = 25});
    Platform _platform9((Position){.x = 100, .y = 23}, (Position){.x = 104, .y = 27});


    // COOL ARROW
    // Base
    Platform _platform10((Position){.x = 30, .y = 25}, (Position){.x = 42, .y = 26});
    // Ends
    Platform _platform11((Position){.x = 38, .y = 22}, (Position){.x = 41, .y = 23});
    Platform _platform12((Position){.x = 40, .y = 23}, (Position){.x = 43, .y = 24});
    Platform _platform13((Position){.x = 42, .y = 24}, (Position){.x = 45, .y = 25});
    Platform _platform14((Position){.x = 43, .y = 25}, (Position){.x = 47, .y = 26});
    Platform _platform15((Position){.x = 42, .y = 26}, (Position){.x = 45, .y = 27});
    Platform _platform16((Position){.x = 40, .y = 27}, (Position){.x = 43, .y = 28});
    Platform _platform17((Position){.x = 38, .y = 28}, (Position){.x = 41, .y = 29});

    // Helper (to not get softlocked)
    Platform _platform18((Position){.x = 2, .y = 14}, (Position){.x = 13, .y = 17});

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

    StaticBox start_region = StaticBox((Position){.x = 114, .y = 36}, (Position){.x = 124, .y = 37});
    StaticBox end_region = StaticBox((Position){.x = 0, .y = 1}, (Position){.x = 10, .y = 6});

    Room* layout7 = new Room(7, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout7;
}
#include "layout4.hpp"

Room* layout4() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 117; i++) {
        floor.push(31);
    }
    for (int i = GAME_WIDTH - 117; i < GAME_WIDTH; i++) {
        floor.push(5);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;

    // FIRST STAIRCASE
    Platform _platform1((Position){.x = 15, .y = 15}, (Position){.x = 25, .y = 21});
    Platform _platform2((Position){.x = 25, .y = 15}, (Position){.x = 30, .y = 23});
    Platform _platform3((Position){.x = 30, .y = 15}, (Position){.x = 35, .y = 25});
    Platform _platform4((Position){.x = 35, .y = 15}, (Position){.x = 40, .y = 27});
    Platform _platform5((Position){.x = 40, .y = 15}, (Position){.x = 45, .y = 29});
    Platform _platform6((Position){.x = 45, .y = 15}, (Position){.x = 50, .y = 31});

    // LOSER STAIRCASE
    Platform _platform7((Position){.x = 65, .y = 8}, (Position){.x = 75, .y = 9});
    Platform _platform8((Position){.x = 60, .y = 11}, (Position){.x = 70, .y = 12});
    Platform _platform9((Position){.x = 65, .y = 14}, (Position){.x = 75, .y = 15});
    Platform _platform10((Position){.x = 60, .y = 17}, (Position){.x = 70, .y = 18});
    Platform _platform11((Position){.x = 65, .y = 20}, (Position){.x = 75, .y = 21});
    Platform _platform12((Position){.x = 60, .y = 23}, (Position){.x = 70, .y = 24});
    Platform _platform13((Position){.x = 65, .y = 26}, (Position){.x = 75, .y = 27});
    Platform _platform14((Position){.x = 60, .y = 29}, (Position){.x = 73, .y = 30});

    // EXTRA WALLS
    Platform _platform15((Position){.x = 15, .y = 7}, (Position){.x = 55, .y = 13});
    Platform _platform16((Position){.x = 55, .y = 7}, (Position){.x = 60, .y = 31});
    Platform _platform17((Position){.x = 75, .y = 7}, (Position){.x = 80, .y = 31});
    Platform _platform18((Position){.x = 84, .y = 28}, (Position){.x = GAME_WIDTH, .y = 31});
    Platform _littlestep((Position){.x = 53, .y = 30}, (Position){.x = 55, .y = 31});

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
    platforms.push(_littlestep);

    StaticBox start_region = StaticBox((Position){.x = 15, .y = 29}, (Position){.x = 25, .y = 32});
    StaticBox end_region = StaticBox((Position){.x = 120, .y = 31}, (Position){.x = 125, .y = 36});

    Room* layout4 = new Room(4, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout4;
}
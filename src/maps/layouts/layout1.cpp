#include "layout1.hpp"

Room* layout1() {
    // LAYOUT 1 È LO STESSO DELLA PROVA DEL MAIN

    // Define floor heights for layout 1
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 50; i++) {
        floor.push(2);
    }
    for (int i = GAME_WIDTH - 50; i < GAME_WIDTH - 20; i++) {
        floor.push(5);
    }
    for (int i = GAME_WIDTH - 20; i < GAME_WIDTH; i++) {
        floor.push(3);
    }

    // Define ceiling heights for layout 1
    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    // Create platform instances for layout 1
    List<Platform> platforms;

    Platform _platform1((Position){.x = 111, .y = 9}, (Position){.x = 120, .y = 12});
    Platform _platform2((Position){.x = 60, .y = 10}, (Position){.x = 78, .y = 12});
    Platform _platform3((Position){.x = 65, .y = 15}, (Position){.x = 69, .y = 19});
    Platform _platform4((Position){.x = 40, .y = 20}, (Position){.x = 57, .y = 23});

    platforms.push(_platform1);
    platforms.push(_platform2);
    platforms.push(_platform3);
    platforms.push(_platform4);

    StaticBox start_region = StaticBox((Position){.x = 1, .y = 3}, (Position){.x = 7, .y = 6});
    // StaticBox end_region = StaticBox((Position){.x = 44, .y = 27}, (Position){.x = 54, .y = 30});
    // TODO debug
    StaticBox end_region = StaticBox((Position){.x = 20, .y = 5}, (Position){.x = 26, .y = 8});

    Room* layout1 = new Room(1, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout1;
}
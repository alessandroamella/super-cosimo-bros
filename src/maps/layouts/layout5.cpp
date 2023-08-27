#include "layout5.hpp"

Room* layout5() {
    List<int> floor;
    for (int i = 0; i < GAME_WIDTH - 115; i++) {
        floor.push(20);
    }
    for (int i = GAME_WIDTH - 115; i < GAME_WIDTH - 60; i++) {
        floor.push(1);
    }
    for (int i = GAME_WIDTH - 60; i < GAME_WIDTH - 50; i++) {
        floor.push(3);
    }
    for (int i = GAME_WIDTH - 50; i < GAME_WIDTH - 40; i++) {
        floor.push(6);
    }
    for (int i = GAME_WIDTH - 40; i < GAME_WIDTH - 30; i++) {
        floor.push(9);
    }
    for (int i = GAME_WIDTH - 30; i < GAME_WIDTH - 20; i++) {
        floor.push(12);
    }
    for (int i = GAME_WIDTH - 20; i < GAME_WIDTH; i++) {
        floor.push(15);
    }

    List<int> ceiling;
    for (int i = 0; i < GAME_WIDTH; i++) {
        ceiling.push(GAME_HEIGHT - 1);
    }

    List<Platform> platforms;


    // MIRRORED STAIRS
    Platform _platform1((Position){.x = 40, .y = 15}, (Position){.x = 45, .y = 26});
    Platform _platform2((Position){.x = 45, .y = 15}, (Position){.x = 50, .y = 23});
    Platform _platform3((Position){.x = 50, .y = 15}, (Position){.x = 55, .y = 20});
    Platform _platform4((Position){.x = 55, .y = 15}, (Position){.x = 65, .y = 17});
    Platform _platform5((Position){.x = 65, .y = 15}, (Position){.x = 70, .y = 20});
    Platform _platform6((Position){.x = 70, .y = 15}, (Position){.x = 75, .y = 23});
    Platform _platform7((Position){.x = 75, .y = 15}, (Position){.x = 80, .y = 26});

    //REGULAR PLATFORMS
    Platform _platform8((Position){.x = 0, .y = 26}, (Position){.x = 39, .y = 27});
    Platform _platform9((Position){.x = 83, .y = 26}, (Position){.x = 90, .y = 27});
    Platform _fromceiling((Position){.x = 59, .y = 19}, (Position){.x = 61, .y = 33});


    //COOL ARROW
    //Base
    Platform _platform10((Position){.x = 30, .y = 7}, (Position){.x = 42, .y = 8});
    //Ends
    Platform _platform11((Position){.x = 38, .y = 4}, (Position){.x = 41, .y = 5});
    Platform _platform12((Position){.x = 40, .y = 5}, (Position){.x = 43, .y = 6});
    Platform _platform13((Position){.x = 42, .y = 6}, (Position){.x = 45, .y = 7});
    Platform _platform14((Position){.x = 43, .y = 7}, (Position){.x = 47, .y = 8});
    Platform _platform15((Position){.x = 42, .y = 8}, (Position){.x = 45, .y = 9});
    Platform _platform16((Position){.x = 40, .y = 9}, (Position){.x = 43, .y = 10});
    Platform _platform17((Position){.x = 38, .y = 10}, (Position){.x = 41, .y = 11});


    //SEMI-STAIRS
    Platform _platform18((Position){.x = 100, .y = 18}, (Position){.x = 115, .y = 19});
    Platform _platform19((Position){.x = 85, .y = 22}, (Position){.x = 105, .y = 23});



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
    platforms.push(_platform19);
    platforms.push(_fromceiling);


    StaticBox start_region = StaticBox((Position){.x = 0, .y = 20}, (Position){.x = 10, .y = 25});
    StaticBox end_region = StaticBox((Position){.x = 0, .y = 27}, (Position){.x = 10, .y = 32});

    Room* layout5 = new Room(5, floor, ceiling, platforms, GAME_WIDTH, GAME_HEIGHT, start_region, end_region);

    return layout5;
}
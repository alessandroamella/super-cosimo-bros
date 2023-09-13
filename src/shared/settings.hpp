#ifndef _SETTINGS_HPP_
#define _SETTINGS_HPP_

#define GAME_WIDTH 130
#define GAME_HEIGHT 38

#define TICK_INTERVAL 0.075f

#define PLAYER_STARTING_HEALTH 50
#define PLAYER_MAX_HEALTH 100
#define PLAYER_STARTING_COINS 50
#define PLAYER_MAX_COINS 99

#define ENEMY_STARTING_HEALTH 10

#define RIGIDBODY_STARTING_VEL_X 0
#define RIGIDBODY_STARTING_VEL_Y 0

#define MAX_ABS_X_VEL 7
#define MAX_JUMP_VEL 4
#define MAX_FALL_VEL -2

#define QUIT_KEY 'q'
#define QUIT_SHOP_KEY 'q'

#define PLAYER_NAME "GAETANO"

#define PLAYER_JUMP_VEL 3
#define PLAYER_WALK_VEL 2
#define PLAYER_RUN_VEL 3

#define ENEMY_VEL 1
#define PROJECTILE_VEL 3

#define ENEMY_DAMAGE 10

#define HEART_HEALTH_INCREASE 30

#define PLAYER_RENDER_CHARACTER "@"
#define PLAYER_POWERUP_RENDER_CHARACTER "&"
#define PLAYER_GUN_RENDER_CHARACTER "@"
#define ENEMY_RENDER_CHARACTER "E"
#define POWERUP_RENDER_DISABLED_CHARACTER "X"

#define MIN_NUMBER_OF_COINS 2
#define COINS_RENDER_DIGITS 2

#define PLAYER_DAMAGED_TOTAL_TICKS 8
#define PLAYER_DAMAGED_BLINK_TICKS 2

#define PLAYER_START_POS_OFFSET 5
#define ENEMY_DISTANCE_FROM_START 20
#define POWERUP_DISTANCE_FROM_START 10

#define STAR_POWERUP_DURATION_SECONDS 10
#define PROJECTILE_DELAY_MS 300
#define PROJECTILE_RENDER_CHARACTER "-"

#define ENEMY_SHOOTING_MIN_DIFFICULTY 5

#define ENEMY_SHOOTING_MIN_DELAY_SEC 1
#define ENEMY_SHOOTING_MAX_DELAY_SEC 10

#define ENEMY_SPAWN_TRIES 10

#define PROJECTILE_DAMAGE 10

#define STARTING_DIFFICULTY 1

#define RENDER_TEXT_Y_PADDING 3
#define RENDER_TEXT_X_PADDING 10

enum class EntityType {
    StaticEntity,
    RigidEntity,
    Powerup,
    Mushroom,
    Star,
    Heart,
    Coin,
    Gun,
    Player,
    Enemy,
    None,
};

enum class Direction {
    Left,
    Right,
};

struct Buyable {
    EntityType type;
    char symbol;
    const char* name;
    int price;
};

enum class ShopControls {
    Left = 'a',
    Right = 'd',
    Buy = ' ',
    Quit = QUIT_SHOP_KEY
};

enum class PlayerJumpPhase {
    Up1 = 0,    // salta in alto 1^ volta
    Up2 = 1,    // salta in alto 2^ volta
    Stall = 2,  // stallo a mezzaria
};

enum class PlayerControls {
    Jump = (int)' ',
    WalkLeft = (int)'a',
    WalkRight = (int)'d',
    RunLeft = 1,   // CTRL + A = 1
    RunRight = 4,  // CTRL + S = 4
    Shoot = (int)'e'
};

#define STR_BUF 32
#define SHOP_BOX_WIDTH 16

#endif  // _SETTINGS_HPP_
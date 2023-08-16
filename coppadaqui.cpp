#include <ncurses.h> /* ncurses.h includes stdio.h */
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>  // for string class
#include <thread>
#include <vector>

struct GameStates {
    int gameRunning;
    int menuOpen;
};

struct Position {
    float x;
    float y;
    float z;
};

char getkbch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

bool isValid(Position pos, int numRows, int numCols) {
    if (0 <= pos.x && pos.x < numCols) {
        if (0 <= pos.y && pos.y < numRows) {
            return true;
        }
    }
    return false;
}

bool isValid(int row, int col, int numRows, int numCols) {
    if (0 <= col && col < numCols) {
        if (0 <= row && row < numRows) {
            return true;
        }
    }
    return false;
}

class RenderableObject {
   private:
    char* model;
    Position pos;

   public:
    RenderableObject(char model, float x, float y, float z) {
        this->model = new char[1];
        this->model[0] = model;
        pos.x = x;
        pos.y = y;
        pos.z = z;
    }
    RenderableObject(char model, Position pos) {
        *this->model = model;
        this->pos = pos;
    }
    char* getModel(void) {
        return model;
    }
    float getX(void) {
        return pos.x;
    }
    float getY(void) {
        return pos.y;
    }
    float getZ(void) {
        return pos.z;
    }
    Position getPos(void) {
        return pos;
    }
    void setModel(char model) {
        *this->model = model;
    }
    void setX(float x) {
        pos.x = x;
    }
    void setY(float y) {
        pos.y = y;
    }
    void setZ(float z) {
        pos.z = z;
    }
    void setPos(Position pos) {
        this->pos = pos;
    }

    void render(void) {
        move(pos.y, pos.x);
        printw(model);
    }
};

class Character : public RenderableObject {
   private:
    std::string name;

    int health;
    int mana;
    int hunger;
    float xVel;
    float yVel;

   public:
    Character(std::string name, char model, int x, int y, int z) : RenderableObject(model, x, y, z) {
        this->name = name;
        health = 100;
        mana = 50;
        hunger = 100;
        xVel = 0.f;
        yVel = 0.f;
    }
    Character(std::string name, char model, int health, int mana, int hunger, float xVel, float yVel, int x, int y, int z) : RenderableObject(model, x, y, z) {
        this->name = name;
        this->health = health;
        this->mana = mana;
        this->hunger = hunger;
        this->xVel = xVel;
        this->yVel = yVel;
    }
    Character(std::string name, char model, Position pos) : RenderableObject(model, pos) {
        this->name = name;
        health = 100;
        mana = 50;
        hunger = 100;
        xVel = 0.f;
        yVel = 0.f;
    }
    Character(std::string name, char model, int health, int mana, int hunger, float xVel, float yVel, Position pos) : RenderableObject(model, pos) {
        this->name = name;
        this->health = health;
        this->mana = mana;
        this->hunger = hunger;
        this->xVel = xVel;
        this->yVel = yVel;
    }

    std::string getName(void) {
        return name;
    }

    int getHealth(void) {
        return health;
    }
    int getMana(void) {
        return mana;
    }
    int getHunger(void) {
        return hunger;
    }
    float getXVel(void) {
        return xVel;
    }
    float getYVel(void) {
        return yVel;
    }

    void setName(std::string name) {
        this->name = name;
    }
    void setHealth(int health) {
        this->health = health;
    }
    void setMana(int mana) {
        this->mana = mana;
    }
    void setHunger(int hunger) {
        this->hunger = hunger;
    }
    void setXVel(float xVel) {
        this->xVel = xVel;
    }
    void setYVel(float yVel) {
        this->yVel = yVel;
    }

    void render(void) {
        move((int)getY(), (int)getX());

        int healthColor;
        int hungerColor;

        if (health > 70) {
            healthColor = COLOR_GREEN;
        } else if (health > 30) {
            healthColor = COLOR_YELLOW;
        }

        else {
            healthColor = COLOR_RED;
        }

        if (hunger > 50) {
            // init_color(COLOR_MAGENTA, 0, 0, 0);
            hungerColor = COLOR_BLACK;
        } else {
            // int hungerAmount = 50 - hunger;
            // init_color(COLOR_MAGENTA, (int)(1000.f* ((float)hungerAmount/50.f)), 0, (int)(1000.f* ((float)hungerAmount/50.f)));
            hungerColor = COLOR_MAGENTA;
        }

        init_pair(1, healthColor, hungerColor);

        attron(COLOR_PAIR(1));

        printw(getModel());
        /*
        char* hungerStr = (char*) malloc(10*sizeof(char));
        sprintf(hungerStr, "%d", hunger);

        printw(hungerStr);
        */
        attroff(COLOR_PAIR(1));
    }

    void renderFullStats(int numRows, int numCols) {
        char* cPrint;

        if (isValid((int)getY() - 8, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
            move((int)getY() - 8, ((int)getX()) - ((int)name.length() / 2 + 2));

            for (int i = 0; i < ((int)name.length() / 2 + 2) * 2; i++) {
                printw("=");
            }
        }

        if (isValid((int)getY() - 7, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
            move((int)getY() - 7, ((int)getX()) - ((int)name.length() / 2 + 2));
            printw("|");
            move((int)getY() - 7, ((int)getX()) + ((int)name.length() / 2 + 2));
            printw("|");
        }
        if (isValid((int)getY() - 6, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
            move((int)getY() - 6, ((int)getX()) - ((int)name.length() / 2 + 2));
            printw("| ");
            cPrint = &name[0u];
            printw(cPrint);
        }

        if (isValid((int)getY() - 6, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
            move((int)getY() - 6, ((int)getX()) - ((int)name.length() / 2 + 2));
            printw("| ");
            cPrint = &name[0u];
            printw(cPrint);
        }

        std::stringstream number;

        int firstPartLen = 11;

        if (((int)name.length() / 2 + 2) * 2 - firstPartLen > 1) {
            if (isValid((int)getY() - 5, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
                move((int)getY() - 5, ((int)getX()) - ((int)name.length() / 2 + 2));
                number.precision(((int)name.length()) - firstPartLen);
                number << hunger;

                printw("| Hunger = ");
                std::string tmp = number.str();
                tmp.resize(((int)name.length() / 2 + 2) * 2);
                cPrint = &tmp[0u];
                printw(cPrint);
                if (isValid((int)getY() - 5, ((int)getX()) + ((int)name.length() / 2 + 2), numRows, numCols)) {
                    move((int)getY() - 5, ((int)getX()) + ((int)name.length() / 2 + 2));
                    printw("|");
                }
            }

        }

        else {
            if (isValid((int)getY() - 5, ((int)getX()) - ((int)name.length() / 2 + 2), numRows, numCols)) {
                move((int)getY() - 5, ((int)getX()) - ((int)name.length() / 2 + 2));
                printw("|");
            }
            if (isValid((int)getY() - 5, ((int)getX()) + ((int)name.length() / 2 + 2), numRows, numCols)) {
                move((int)getY() - 5, ((int)getX()) + ((int)name.length() / 2 + 2));
                printw("|");
            }
        }

        // TODO char*

        for (int i = 0; i < (int)name.length(); i++) {
        }
    }

    void moveCharacter(void) {
        setX(getX() + xVel);
        setY(getY() + yVel);
    }

    void collide(int numRows, int numCols) {
        Position newPos = getNewPosition();
        if (newPos.y > numRows) {
            float overshoot = newPos.y - numRows;
            setY(numRows - overshoot);
            setYVel(-yVel * 0.9f);
        }
        if (newPos.y < 0) {
            float overshoot = -newPos.y;
            setY(overshoot);
            setYVel(-yVel * 0.9f);
        }
        if (newPos.x > numCols) {
            float overshoot = newPos.x - numCols;
            setX(numCols - overshoot);
            setXVel(-xVel * 0.9f);
        }
        if (newPos.x < 0) {
            float overshoot = -newPos.x;
            setX(overshoot);
            setXVel(-xVel * 0.9f);
        }
    }

    Position getNewPosition(void) {
        float newX = getX() + xVel;
        float newY = getY() + yVel;
        float newZ = 0.f;
        return Position{newX, newY, newZ};
    }
};

void* keyboardThreadFunc(std::vector<Character>* actors, std::string actorToControl, int* gameRunning) {
    char keyPress;
    int i = 0;
    while (1) {
        keyPress = getkbch();
        int actorIndex = 0;
        for (int i = 0; i < (*actors).size(); i++) {
            if ((*actors)[i].getName().compare(actorToControl) == 0) {
                actorIndex = i;
            }
        }

        if (keyPress == 'w') {  // TODO Add jetpack fuel
            (*actors)[actorIndex].setYVel((*actors)[actorIndex].getYVel() - 0.1);
        } else if (keyPress == 'a') {
            (*actors)[actorIndex].setXVel((*actors)[actorIndex].getXVel() - 0.1);
        }

        else if (keyPress == 's') {
            (*actors)[actorIndex].setYVel((*actors)[actorIndex].getYVel() + 0.1);
        }

        else if (keyPress == 'd') {
            (*actors)[actorIndex].setXVel((*actors)[actorIndex].getXVel() + 0.1);
        }

        // 27 for esc key
        else if (keyPress == 27) {
            *gameRunning = 0;
        }
        // (m)enu
        else if (keyPress == 'm') {
        }
    }
    exit(1);
}

void gravity(Character& character) {
    character.setYVel(character.getYVel() + 0.01);
}

int main() {
    Character hero = Character(std::string("Jessica"), 'J', 46.f, 12.f, 3.f);

    Character matt = Character(std::string("Matt"), 'M', 35.f, 15.f, 3.f);
    Character ihab = Character(std::string("Ihab"), 'I', 15.f, 20.f, 3.f);

    Character oreo = Character(std::string("   Oreo   "), 'O', 23.f, 14.f, 3.f);
    Character caramel = Character(std::string("Caramel"), 'C', 40.f, 9.f, 3.f);

    std::vector<Character> actors;

    actors.push_back(hero);

    actors.push_back(matt);
    actors.push_back(ihab);

    actors.push_back(oreo);
    actors.push_back(caramel);

    int gameRunning;

    std::thread t[1];
    std::string actorToControl = "Matt";
    t[0] = std::thread(keyboardThreadFunc, &actors, actorToControl, &gameRunning);

    initscr();
    clear();
    refresh();
    int numRows, numCols;
    getmaxyx(stdscr, numRows, numCols);

    start_color(); /* Start color 			*/

    std::string screen;

    gameRunning = 1;
    while (gameRunning) {
        screen.clear();

        getmaxyx(stdscr, numRows, numCols);
        for (int i = 0; i < numRows; i++) {
            for (int k = 0; k < numCols; k++) {
                screen.push_back(',');
            }
        }

        clear();
        char* cScreen = &screen[0u];
        move(0, 0);
        printw(cScreen);

        int numCharacters = actors.size();

        for (int i = 0; i < numCharacters; i++) {
            gravity(actors[i]);
            if (isValid(actors[i].getNewPosition(), numRows, numCols)) {
                actors[i].moveCharacter();
            } else {
                if (actors[i].getName().find("Oreo") != std::string::npos) {
                    actors[i].setHunger(actors[i].getHunger() - 23);
                }
                actors[i].collide(numRows, numCols);
            }
        }
        for (int i = 0; i < numCharacters; i++) {
            if (isValid(actors[i].getPos(), numRows, numCols)) {
                actors[i].render();
                actors[i].renderFullStats(numRows, numCols);
            }
        }

        move(0, 0);
        refresh();
        usleep(16000);
    }

    clear();
    move(0, 0);

    printw("\n\n\n");
    printw("\nPress any key to exit the game...");
    refresh();
    getch();
    endwin();

    return 0;
}

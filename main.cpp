#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

const bool DEBUG_MODE = 0;

struct Settings {
    int size_x = 5;
    int size_y = 10;
    int mines = 50;
};

// model
class Map {
private:
    std::vector<bool> mine;
    std::vector<int> state; // 0 - closed, 1 - oppened, 2 - flag
    Settings set;

    int cell(int x, int y) {
        return y * set.size_x + x;
    }

    void create_vectors() {
        auto m_size = set.size_x * set.size_y;
        mine.resize(m_size);
        state.resize(m_size);
    }

    void create_mines() {
        int mines_planted = 0;
        while (mines_planted <= set.mines) {
            int rand_cell = rand() % (set.size_x * set.size_y);
            if (mine[rand_cell] == 0) {
                mine[rand_cell] = 1;
                mines_planted++;
            }
        }
    }

    void clear_mines() {
        for (int i = 0; i < mine.size(); i++) mine[i] = false;
    }

    void clear_map() {
        for (int i = 0; i < state.size(); i++) state[i] = 0;
    }

    void flag(int x, int y) {
        state[cell(x, y)] = 2;
    }

public:
    void create(Settings _set) {
        set = _set;
        create_vectors();
        clear_map();
        clear_mines();
        create_mines();
    }

    void flag(int x, int y) {
        state[cell(x, y)] = 2;
    }

    
};

// view
class ConsoleDrawer {
private:
    std::vector<bool> mine;
    std::vector<int> state; // 0 - closed, 1 - oppened, 2 - flag
    Settings set;

    int cell(int x, int y) {
        return y * set.size_x + x;
    }
public:
    void custom(Settings _set) {
        set = _set;
    }

    void update(std::vector<bool> _mine, std::vector<int> _state) {
        mine = _mine;
        state = _state;
    }

    void draw() {
        for (int y = 0; y < set.size_y; y++) {
            for (int x = 0; x < set.size_x; x++) {
                std::cout << state[cell(x, y)] << "[" << mine[cell(x, y)] << ']\t';
            }
            std::cout << std::endl;
        }
    }
};

// controller
class ConsoleController {
private:
    std::vector<std::string> command;

public:
    void use() {
        std::string input;
        std::getline(std::cin, input);

        std::stringstream ss(input);

        std::string buffer;
        while (ss >> buffer) command.push_back(buffer);

        if (command[0] == "flag") std::cout << command[0];
    }
};

class Game {
private:
    Map map;
    ConsoleDrawer drawer;
    ConsoleController controller;
    Settings set;

    int tick() {
        std::string input;
        std::cin >> input;
        if (input == "stop") return -1;
        //else controller.use();

        else {
            
        }

        //controller.manipulate();
        //map.update();
        //drawer.draw();

        return 0;
    }

public:
    Game(Settings _set) {
        set = _set;
        set.mines = (set.size_x * set.size_y) * set.mines / 100;
        drawer.custom(set);

        map.create(set);
        drawer.draw();
        //while (tick() == 0) {}
    }
};

int main() {
    Settings set;
    if (!DEBUG_MODE) {
        std::cout << "size x: ";
        std::cin >> set.size_x;
        std::cout << "size y: ";
        std::cin >> set.size_y;
        std::cout << "mines percent: ";
        std::cin >> set.mines;
    }
 
    Game game(set);
    return 0;
}
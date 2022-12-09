#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <thread>

const int KNOT_COUNT = 10;

using namespace std;

struct pos
{
    int x;
    int y;

    int distance(pos other)
    {
        int dx = abs(x - other.x);
        int dy = abs(y - other.y);

        int min = std::min(dx, dy);
        int max = std::max(dx, dy);

        int diagonalSteps = min;
        int straightSteps = max - min;

        return sqrt(2) * diagonalSteps + straightSteps;
    }

    int operator==(const pos &other) const
    {
        return x == other.x && y == other.y;
    }

    pos operator+(const pos &other) const
    {
        return {x + other.x, y + other.y};
    }

    pos operator-(const pos &other) const
    {
        return {x - other.x, y - other.y};
    }
};

struct rope
{
    pos H;
    pos T;
    rope *next;
    std::vector<pos> visited;

    void move(char direction, int distance)
    {
        std::vector<pos> positions = {};

        for (int i = 0; i < distance; i++)
        {
            switch (direction)
            {
            case 'U':
                H.y++;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x;
                    T.y = H.y - 1;
                    if (next == nullptr)
                        break;

                    next->move('U', max(T.y - next->H.y, 0));
                    next->move('L', max(next->H.x - T.x, 0));
                    next->move('R', max(T.x - next->H.x, 0));
                }
                break;
            case 'D':
                H.y--;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x;
                    T.y = H.y + 1;
                    if (next == nullptr)
                        break;

                    next->move('D', max(next->H.y - T.y, 0));
                    next->move('L', max(next->H.x - T.x, 0));
                    next->move('R', max(T.x - next->H.x, 0));
                }
                break;
            case 'L':
                H.x--;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x + 1;
                    T.y = H.y;
                    if (next == nullptr)
                        break;

                    next->move('L', max(next->H.x - T.x, 0));
                    next->move('U', max(T.y - next->H.y, 0));
                    next->move('D', max(next->H.y - T.y, 0));
                }
                break;
            case 'R':
                H.x++;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x - 1;
                    T.y = H.y;
                    if (next == nullptr)
                        break;

                    next->move('R', max(T.x - next->H.x, 0));
                    next->move('U', max(T.y - next->H.y, 0));
                    next->move('D', max(next->H.y - T.y, 0));
                }
                break;
            }

            if (std::find(visited.begin(), visited.end(), pos(T)) == visited.end())
                positions.push_back(pos(T));
        }

        visited.insert(visited.end(), positions.begin(), positions.end());
    }
};

void print_rope(rope *r)
{
    int add = 50;
    printf("\033[2J");
    rope *end = r;
    while (end->next != nullptr)
    {
        // position the cursor
        printf("\033[%i;%if", end->H.y + add, end->H.x + add);
        printf("H");

        end = end->next;
    }

    printf("\033[%i;%if", end->T.y + add, end->T.x + add);
    printf("T");
}

int main(int argc, char *argv[])
{

    // Loading our file

    if (!filesystem::exists("day9"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    ifstream input("day9");

    // Rope generation
    rope root = {{0, 0}, {0, 0}};
    rope *current = &root;
    for (int i = 0; i < KNOT_COUNT; i++)
    {
        rope *r = new rope;
        r->H = {0, 0};
        r->T = {0, 0};
        r->next = nullptr;

        current->next = r;
        current = r;
    }

    string line;
    while (getline(input, line))
    {
        char direction;
        int distance;

        sscanf(line.c_str(), "%c %i", &direction, &distance);
        printf("Moving... %c %i\n", direction, distance);

        // We move the rope
        root.move(direction, distance);
        //print_rope(&root);
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    printf("\033[0;0H");

    // We get the end of the rope
    rope *end = &root;
    while (end->next != nullptr)
    {
        printf("Current knot: H:%i;%i, T:%i;%i\n", end->H.x, end->H.y, end->T.x, end->T.y);
        end = end->next;
    }

    printf("Visited %i positions\n", end->visited.size());

    return 0;
}
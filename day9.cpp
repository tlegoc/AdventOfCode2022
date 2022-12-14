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

    int distance(const pos other)
    {
        return max(abs(x - other.x), abs(y - other.y));
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

//I decided to go with chained ropes instead of having a list.
//I could've done it with a list, but I wanted to try something new
//Each node records its tail position (by calling record_pos())
struct rope
{
    pos H;
    pos T;
    rope *previous;
    rope *next;
    std::vector<pos> visited;

    void move(char direction, int distance)
    {
        //We need to move one by one else we'll get only straigth lines
        //Which shouldn't always be the case
        for (int i = 0; i < distance; i++)
        {
            switch (direction)
            {
            case 'U':
                H.y++;
                break;
            case 'D':
                H.y--;
                break;
            case 'L':
                H.x--;
                break;
            case 'R':
                H.x++;
                break;
            }

            // Moving the tail
            rope *current = this;
            while (current != nullptr)
            {
                if (current->H.distance(current->T) > 1)
                {
                    // Place the tail behind the head
                    //This didn't work. I'm leaving it as is
                    //So I can find why later
                    /*
                    if (abs(current->H.x - current->T.x) > abs(current->H.y - current->T.y))
                    {
                        if (current->H.x - current->T.x > 0)
                        {
                            current->T.x = current->H.x - 1;
                            current->T.y = current->H.y;
                        }
                        else
                        {
                            current->T.x = current->H.x + 1;
                            current->T.y = current->H.y;
                        }
                    }
                    else
                    {
                        if (current->H.y - current->T.y > 0)
                        {
                            current->T.y = current->H.y - 1;
                            current->T.x = current->H.x;
                        }
                        else
                        {
                            current->T.y = current->H.y + 1;
                            current->T.x = current->H.x;
                        }
                    }*/

                    //Implementation from https://github.com/vss2sn/advent_of_code/blob/master/2022/cpp/day_09b.cpp
                    int deltaX = current->H.x - current->T.x;
                    int deltaY = current->H.y - current->T.y;

                    if (std::abs(deltaX) == 2 && std::abs(deltaY) == 0)
                    {
                        current->T.x += deltaX / 2;
                    }
                    else if (std::abs(deltaX) == 2 && std::abs(deltaY) == 1)
                    {
                        current->T.x += deltaX / 2;
                        current->T.y += deltaY;
                    }
                    else if (std::abs(deltaX) == 0 && std::abs(deltaY) == 2)
                    {
                        current->T.y += deltaY / 2;
                    }
                    else if (std::abs(deltaX) == 1 && std::abs(deltaY) == 2)
                    {
                        current->T.x += deltaX;
                        current->T.y += deltaY / 2;
                    }
                    else if (std::abs(deltaX) == 2 && std::abs(deltaY) == 2)
                    {
                        current->T.x += deltaX / 2;
                        current->T.y += deltaY / 2;
                    }
                }

                // Moving the head of the next rope to the tail of the current one
                if (current->next != nullptr)
                    current->next->H = pos(current->T);

                //Recording
                current->record_pos();

                current = current->next;
            }

            record_pos();
        }
    }

    void record_pos()
    {
        //unique_set gave me weird result, had to add a constructor to ropes
        //But it wasn't really necessary so instead I just add this line
        if (std::find(visited.begin(), visited.end(), pos(T)) == visited.end())
            visited.push_back(pos(T));
    }
};

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
    //Why -2 ? Because by creating a rope we already have 2 knots, the head and the tail
    for (int i = 0; i < KNOT_COUNT - 2; i++)
    {
        rope *next = new rope();
        next->previous = current;
        current->next = next;
        current = next;
    }


    //Reading instructions
    string line;
    while (getline(input, line))
    {
        char direction;
        int distance;

        sscanf(line.c_str(), "%c %i", &direction, &distance);

        // We move the rope
        root.move(direction, distance);
    }

    //Display visited count for each knot
    rope *end = &root;
    int i = 1;
    while (end != nullptr)
    {
        printf("Knot %i: H:%i;%i, T:%i;%i Visit:%i\n", i++, end->H.x, end->H.y, end->T.x, end->T.y, end->visited.size());
        end = end->next;
    }

    return 0;
}
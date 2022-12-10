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

struct rope
{
    pos H;
    pos T;
    rope *previous;
    rope *next;
    std::vector<pos> visited;

    void move(char direction, int distance)
    {
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
                    }
                }

                if (current->next != nullptr)
                    current->next->H = pos(current->T);

                current->record_pos();

                current = current->next;
            }

            record_pos();
        }
    }

    void record_pos()
    {
        if (std::find(visited.begin(), visited.end(), pos(T)) == visited.end())
            visited.push_back(pos(T));
    }
};

void print_rope(rope *r)
{
    printf("\033[2J");
    rope *end = r;
    while (true)
    {
        // position the cursor
        printf("\033[%i;%if", end->H.y + 130, end->H.x + 200);
        printf("H");

        if (end->next == nullptr)
            break;
        
        end = end->next;
    }

    printf("\033[%i;%if", end->T.y + 130, end->T.x + 200);
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
    for (int i = 1; i < KNOT_COUNT - 1; i++)
    {
        rope *next = new rope();
        next->previous = current;
        current->next = next;
        current = next;
    }

    string line;
    while (getline(input, line))
    {
        char direction;
        int distance;

        sscanf(line.c_str(), "%c %i", &direction, &distance);

        // We move the rope
        root.move(direction, distance);
        /*
        printf("\033[2J");
        //print_rope(&root);
        printf("\033[0;0f");
        printf("Moving... %c %i: tail %i:%i, head %i:%i, d %i\n", direction, distance, root.T.x, root.T.y, root.H.x, root.H.y, root.H.distance(root.T));
        //std::this_thread::sleep_for(std::chrono::milliseconds(40));
        */
    }

    printf("\033[2J");
    printf("\033[0;0f");

    // We get the end of the rope
    rope *end = &root;
    int i = 1;
    while (end != nullptr)
    {
        printf("Knot %i: H:%i;%i, T:%i;%i Visit:%i\n", i++, end->H.x, end->H.y, end->T.x, end->T.y, end->visited.size());
        end = end->next;
    }

    return 0;
}
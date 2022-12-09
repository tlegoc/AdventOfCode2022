#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <cmath>

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
};

struct rope
{
    pos H;
    pos T;

    vector<pos> move(char direction, int distance)
    {
        vector<pos> positions;

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
                }
                break;
            case 'D':
                H.y--;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x;
                    T.y = H.y + 1;
                }
                break;
            case 'L':
                H.x--;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x + 1;
                    T.y = H.y;
                }
                break;
            case 'R':
                H.x++;
                if (H.distance(T) >= 2)
                {
                    T.x = H.x - 1;
                    T.y = H.y;
                }
                break;
            }

            positions.push_back(pos(T));
        }
        return positions;
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

    rope r = {{0, 0}, {0, 0}};


    vector<pos> visited = {};

    int visited_count = 0;
    string line;
    while (getline(input, line))
    {
        char direction;
        int distance;

        sscanf(line.c_str(), "%c %u", &direction, &distance);
        printf("Moving %c %i\n", direction, distance);

        // We move the rope
        vector<pos> positions = r.move(direction, distance);

        // We mark the positions as visited
        for (pos p : positions)
        {
            bool already_visited = false;
            for (pos pv : visited)
            {
                if (p == pv)
                {
                    already_visited = true;
                    break;
                }
            }

            if (!already_visited) {
                visited_count++;
                visited.push_back(pos(p));
            }

            printf("Visited position %i %i (already visited %b)\n", p.x, p.y, already_visited);
        }
    }

    printf("Visited %i positions\n", visited_count);

    return 0;
}
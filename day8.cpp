#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("day8"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day8");

    char c = 0;
    std::vector<std::vector<int>> forest = {{}};

    while (input.get(c))
    {
        if (c == '\n')
            forest.push_back({});
        else if (isdigit(c))
            forest.back().push_back(c - '0');
        else
            throw std::runtime_error("Invalid character");
    }

    //For some obscure reason lines 3 to 13 are detected as 99+ in length,
    //Even tho it is clearly not (as seen in debug mode, etc).
    //So I store the true size here, just in case
    int size_x = forest[0].size();
    int size_y = forest.size();

    printf("Forest size: %d x %d\n", forest.size(), forest[0].size());
    std::vector<std::vector<bool>> visible = std::vector<std::vector<bool>>(forest.size(), std::vector<bool>(forest[0].size(), false));

    
    //Left and right
    for (int i = 0; i < size_y; i++)
    {
        int biggest = -1;
        for (int j = 0; j < size_x; j++)
        {
            visible[i][j] = visible[i][j] || forest[i][j] > biggest;

            if (forest[i][j] > biggest)
                biggest = forest[i][j];
        }

        biggest = -1;
        for (int j = size_x - 1; j >= 0; j--)
        {
            visible[i][j] = visible[i][j] || forest[i][j] > biggest;

            if (forest[i][j] > biggest)
                biggest = forest[i][j];
        }
    }

    //Up and down
    for (int j = 0; j < size_x; j++)
    {
        int biggest = -1;
        for (int i = 0; i < size_y; i++)
        {
            visible[i][j] = visible[i][j] || forest[i][j] > biggest;

            if (forest[i][j] > biggest)
                biggest = forest[i][j];
        }

        biggest = -1;
        for (int i = size_y - 1; i >= 0; i--)
        {
            visible[i][j] = visible[i][j] || forest[i][j] > biggest;

            if (forest[i][j] > biggest)
                biggest = forest[i][j];
        }
    }

    //We could do this in the main loop but eh, this is easier to read
    int visible_count = 0;
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            visible_count += visible[i][j] ? 1 : 0;
        }
    }
    printf("Visible count: %d\n", visible_count);

    /*

        PART 2

    */

    long biggest_score = 0;

    // For each tree we will look up and down
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            int tree_size = forest[y][x];
            long score = 1;

            int view_distance = 0;

            // Right
            for (int j = x + 1; j < size_x; j++)
            {
                view_distance++;
                if (forest[y][j] >= tree_size)
                    break;
            }

            score *= view_distance;
            view_distance = 0;

            // Left
            for (int j = x - 1; j >= 0; j--)
            {
                view_distance++;
                if (forest[y][j] >= tree_size)
                    break;
            }

            score *= view_distance;
            view_distance = 0;

            // Up
            for (int i = y + 1; i < size_y; i++)
            {
                view_distance++;
                if (forest[i][x] >= tree_size)
                    break;
            }

            score *= view_distance;
            view_distance = 0;

            // Down
            for (int i = y - 1; i >= 0; i--)
            {
                view_distance++;
                if (forest[i][x] >= tree_size)
                    break;
            }

            score *= view_distance;

            biggest_score = std::max(biggest_score, score);
        }
    }

    printf("Biggest score: %d\n", biggest_score);

    return 0;
}
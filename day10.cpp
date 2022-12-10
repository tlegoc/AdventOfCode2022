#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("day10"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day10");

    std::string line;
    std::vector<int> strengths;

    int current_cycle = 1;
    int X = 1;
    int display_X = 0;
    int display_cycle = 1;
    std::string display = "";
    while (std::getline(input, line))
    {
        char command[4];
        int param = 0;
        std::sscanf(line.c_str(), "%s %d", command, &param);

        if (line == "noop")
        {
            strengths.push_back(X * current_cycle);
            printf("noop: X:%d, cycle:%d, strength:%d\n", X, current_cycle, X * current_cycle);
            current_cycle++;
            if (display_X >= X - 1 && display_X <= X + 1)
            {
                display += "#";
            }
            else
            {
                display += ".";
            }
            display_X++;

            if (display_X > 40)
            {
                display_X = 1;
                display += "\n";
            }
        }
        else
        {
            strengths.push_back(X * current_cycle);
            printf("addx step1: X:%d, cycle:%d, strength:%d\n", X, current_cycle, X * current_cycle);
            current_cycle++;
            if (display_X >= X - 1 && display_X <= X + 1)
            {
                display += "#";
            }
            else
            {
                display += ".";
            }
            display_X++;

            if (display_X > 40)
            {
                display_X = 1;
                display += "\n";
            }
            strengths.push_back(X * current_cycle);
            printf("addx step2: X:%d, cycle:%d, strength:%d\n", X, current_cycle, X * current_cycle);
            current_cycle++;
            if (display_X >= X - 1 && display_X <= X + 1)
            {
                display += "#";
            }
            else
            {
                display += ".";
            }
            display_X++;

            if (display_X > 40)
            {
                display_X = 1;
                display += "\n";
            }
            X += param;
        }
    }

    int sum = 0;
    int cycles[] = {20, 60, 100, 140, 180, 220};

    for (auto cycle : cycles)
    {
        sum += strengths[cycle - 1];
    }

    printf("sum: %d\n", sum);
    printf("Screen:\n");
    printf("%s", display.c_str());
    return 0;
}
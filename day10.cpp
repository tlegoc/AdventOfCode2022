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

    int cycle_add = 0;
    int cycle = 1;
    int X_add = 0;
    int X = 1;
    int display_X = 0;
    std::string display = "";
    while (std::getline(input, line))
    {
        char command[4];
        int param = 0;
        std::sscanf(line.c_str(), "%s %d", command, &param);

        if (line == "noop")
        {
            strengths.push_back(X * cycle);
            printf("noop: X:%d, cycle:%d, strength:%d\n", X, cycle, X * cycle);
            X_add = 0;
            cycle_add = 1;
        }
        else
        {
            strengths.push_back(X * cycle);
            printf("addx step1: X:%d, cycle:%d, strength:%d\n", X, cycle, X * cycle);
            strengths.push_back(X * (cycle + 1));
            printf("addx step2: X:%d, cycle:%d, strength:%d\n", X, cycle + 1, X * (cycle + 1));
            X_add = param;
            cycle_add = 2;
        }

        while (cycle_add > 0) {
            if (display_X >= X - 1 && display_X <= X + 1) {
                display += "#";
            } else {
                display += " ";
            }
            display_X++;

            if (display_X >= 40) {
                display_X = 0;
                display += "\n";
            }

            cycle++;
            cycle_add--;
        }

        X += X_add;
    }

    int sum = 0;
    int notable_cycles[] = {20, 60, 100, 140, 180, 220};

    for (auto cycle : notable_cycles)
    {
        sum += strengths[cycle - 1];
    }

    printf("sum: %d\n", sum);
    printf("Screen:\n");
    printf("%s", display.c_str());
    return 0;
}
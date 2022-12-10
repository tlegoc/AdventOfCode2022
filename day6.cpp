#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cmath>
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{

    // Loading our file
    if (!std::filesystem::exists("day6"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day6");

    char x = 'c';
    std::vector<char> data;

    while (input >> x)
    {
        data.push_back(x);
    }

    int processed_count = 0;
    for (int i = 0; i < data.size() - 3; i++)
    {
        bool found = true;
        for (int j = 0; j < 4; j++)
        {
            int c = count(data.begin() + i, data.begin() + i + 4, data[i + j]);
            found = c == 1 && found;
        }

        if (found)
        {
            printf("First 4 different characters appear at %i (%c%c%c%c)\n", processed_count + 4, data[i], data[i + 1], data[i + 2], data[i + 3]);
            break;
        }

        processed_count++;
    }

    int processed_count_message = 0;
    for (int i = 0; i < data.size() - 13; i++)
    {
        bool found = true;
        for (int j = 0; j < 14; j++)
        {
            int c = count(data.begin() + i, data.begin() + i + 14, data[i + j]);
            found = c == 1 && found;
        }

        if (found)
        {
            printf("First 14 different characters appear at %i\n", processed_count_message + 14);
            break;
        }

        processed_count_message++;
    }

    return 0;
}
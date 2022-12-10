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
        std::vector<char> temp = std::vector<char>(data[i], data[i + 3]);

        // Why doing a loop when you can ctrl+c ctrl+v
        for (int j = 0; j < temp.size(); j++)
        {
            int c = count(temp.begin(), temp.end(), data[i + j]);
            if (c != 1) break;
            printf("First 4 different characters appear at %i (%c%c%c%c)\n", processed_count + 4, data[i], data[i + 1], data[i + 2], data[i + 3]);
        }
        
        processed_count++;
    }

    int processed_count_message = 0;
    for (int i = 0; i < data.size() - 13; i++)
    {
        std::vector<char> temp = std::vector<char>(data[i], data[i + 13]);

        // Why doing a loop when you can ctrl+c ctrl+v
        for (int j = 0; j < temp.size(); j++)
        {
            int c = count(temp.begin(), temp.end(), data[i + j]);
            if (c != 1) break;
            printf("First 14 different characters appear at %i\n", processed_count + 14);
        }

        processed_count_message++;
    }

    return 0;
}
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

    /*
     * I'm bruteforcing this one. I might come back later and find a more elegant way of doing it (with maths and division I believe)
     * but it'll do for now
     */

    int processed_count = 0;
    for (int i = 0; i < data.size() - 3; i++)
    {
        std::vector<char> temp = {data[i], data[i + 1], data[i + 2], data[i + 3]};

        int count1 = count(temp.begin(), temp.end(), data[i]);
        int count2 = count(temp.begin(), temp.end(), data[i + 1]);
        int count3 = count(temp.begin(), temp.end(), data[i + 2]);
        int count4 = count(temp.begin(), temp.end(), data[i + 3]);

        if (count1 == 1 && count2 == 1 && count3 == 1 && count4 == 1)
        {
            printf("First 4 different characters appear at %i (%c%c%c%c)\n", processed_count + 4, data[i], data[i + 1], data[i + 2], data[i + 3]);
            break;
        }
        processed_count++;
    }

    int processed_count_message = 0;
    for (int i = 0; i < data.size() - 13; i++)
    {
        std::vector<char> temp = {data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4], data[i + 5], data[i + 6], data[i + 7], data[i + 8], data[i + 9], data[i + 10], data[i + 11], data[i + 12], data[i + 13]};

        int count1 = count(temp.begin(), temp.end(), data[i]);
        int count2 = count(temp.begin(), temp.end(), data[i + 1]);
        int count3 = count(temp.begin(), temp.end(), data[i + 2]);
        int count4 = count(temp.begin(), temp.end(), data[i + 3]);
        int count5 = count(temp.begin(), temp.end(), data[i + 4]);
        int count6 = count(temp.begin(), temp.end(), data[i + 5]);
        int count7 = count(temp.begin(), temp.end(), data[i + 6]);
        int count8 = count(temp.begin(), temp.end(), data[i + 7]);
        int count9 = count(temp.begin(), temp.end(), data[i + 8]);
        int count10 = count(temp.begin(), temp.end(), data[i + 9]);
        int count11 = count(temp.begin(), temp.end(), data[i + 10]);
        int count12 = count(temp.begin(), temp.end(), data[i + 11]);
        int count13 = count(temp.begin(), temp.end(), data[i + 12]);
        int count14 = count(temp.begin(), temp.end(), data[i + 13]);

        if (count1 == 1 && count2 == 1 && count3 == 1 && count4 == 1 && count5 == 1 && count6 == 1 && count7 == 1 && count8 == 1 && count9 == 1 && count10 == 1 && count11 == 1 && count12 == 1 && count13 == 1 && count14 == 1)
        {
            printf("First 14 different characters appear at %i\n", processed_count_message + 14);
            break;
        }
        processed_count_message++;
    }

    return 0;
}
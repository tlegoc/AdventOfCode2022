#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <map>

using namespace std;

int get_priority(char c)
{
    return islower(c) ? c - 'a' + 1 : c - 'A' + 27;
}

int main(int argc, char *argv[])
{

    // Loading our file

    if (!filesystem::exists("day3"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    ifstream input("day3");

    string x, y, z = "";
    vector<string> data;

    int total_group_priority = 0;

    while (input >> x >> y >> z)
    {
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);

        /*

            Finding common letter

        */
        for (char c : x)
        {
            if (y.find(c) != string::npos && z.find(c) != string::npos)
            {
                int priority = get_priority(c);
                total_group_priority += priority;
                break;
            }
        }
    }

    printf("Total group priority: %i\n", total_group_priority);



    /*

        Finding priority

    */
    int total_priority = 0;

    for (auto rucksack : data)
    {
        string lower_half = rucksack.substr(0, rucksack.length() / 2);
        string upper_half = rucksack.substr(rucksack.length() / 2, rucksack.length() - 1);

        for (char c : lower_half)
        {
            if (upper_half.find(c) != string::npos)
            {
                int priority = get_priority(c);
                total_priority += priority;
                break;
            }
        }
    }

    printf("Total priority: %d\n", total_priority);

    return 0;
}

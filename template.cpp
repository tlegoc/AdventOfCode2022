#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("input"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("input");

    int prev, x, sum, count = 0;
    std::vector<int> data;

    while (input >> x)
    {
        data.push_back(x);
    }

    /*

        CODE HERE

    */

    printf("Hello World\n");

    return 0;
}
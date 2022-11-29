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

    int x = 0;
    std::vector<int> data;

    while (input >> x)
    {
        data.push_back(x);
    }

    /*

        CODE HERE

    */
   
    for (auto i : data)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
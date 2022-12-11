#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

enum operation_type
{
    ADD,
    MULTIPLY,
    SUBTRACT,
    DIVIDE
};

struct Monkey
{
    std::vector<int> starting_items;
    operation_type operation;
    int operation_arg;
    int test;
    int monkey_true;
    int monkey_false;
};

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("day11"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day11");

    std::vector<Monkey> monkeys;

    while (!input.eof())
    {
        Monkey monkey;
        std::string line;
        std::getline(input, line);
        printf("%s\n", line.c_str());

        break;
    }

    return 0;
}
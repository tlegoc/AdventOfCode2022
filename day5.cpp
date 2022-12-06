#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

// Little display function
// Will show the stacks horizontally cause I ain't got time
void display_crates(std::vector<std::vector<char>> crates)
{
    for (auto crate : crates)
    {
        printf("Crate: ");
        for (auto c : crate)
            printf(" [%c]", c);

        printf("\n");
    }
}

int main(int argc, char *argv[])
{

    // Loading our file
    if (!std::filesystem::exists("day5"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day5");

    // Load the first ten lines
    std::vector<std::vector<char>> crates(9);

    int i = 0;
    while (i < 10)
    {
        std::string line;
        std::getline(input, line);

        // For each crate
        for (int j = 1; j < line.length(); j += 4)
        {
            char c = line[j];

            // Check if it's really a crate
            if (isalpha(c))
                crates[(j - 1) / 4].insert(crates[(j - 1) / 4].begin(), c);
        }
        i++;
    }

    // Moving operations
    while (input.good())
    {
        std::string line = "";
        std::getline(input, line);
        int quantity, from, to;
        sscanf(line.c_str(), "move %d from %d to %d", &quantity, &from, &to);

        // Indexes are 1 based
        from--;
        to--;

        // For part one just do a loop and push_back/pop_back
        crates[to].insert(crates[to].end(), crates[from].end() - quantity, crates[from].end());

        // We remove the crates we moved
        for (int j = 0; j < quantity; j++)
            crates[from].pop_back();
    }

    display_crates(crates);

    printf("Last crate of each stack: ");
    for (auto crate : crates)
        printf("%c", crate.back());

    printf("\n");

    return 0;
}

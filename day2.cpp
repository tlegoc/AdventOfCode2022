#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("day2"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day2");

    char x, y = 0;

    int points = 0;

    while (input >> x && input >> y)
    {
        //I hate this
        switch (y)
        {
        case 'X':
            points += 0;
            switch (x)
            {
            case 'A':
                points += 3;
                break;
            case 'B':
                points += 1;
                break;
            case 'C':
                points += 2;
            default:
                break;
            }
            break;
        case 'Y':
            points += 3;
            switch (x)
            {
            case 'A':
                points += 1;
                break;
            case 'B':
                points += 2;
                break;
            case 'C':
                points += 3;
            default:
                break;
            }
            break;
        case 'Z':
            points += 6;
            switch (x)
            {
            case 'A':
                points += 2;
                break;
            case 'B':
                points += 3;
                break;
            case 'C':
                points += 1;
            default:
                break;
            }
            break;

        default:
            printf("Shouldn't be here\n");
            break;
        }
    }

    printf("Your points will be %i\n", points);

    return 0;
}
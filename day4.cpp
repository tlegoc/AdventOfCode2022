#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

#include "helpers.h"

int main(int argc, char *argv[])
{

    // Loading our file

    if (!std::filesystem::exists("day4"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day4");

    std::string s = "";


    int self_contained_ranges = 0;
    int overlapping_ranges = 0;

    while (input >> s)
    {
        int A1, A2, B1, B2;

        const char* c = s.c_str();
        sscanf(c, "%d-%d,%d-%d", &A1, &A2, &B1, &B2);

        
        //Ugly but works, I tried to be fast instead of being optimised and clean
        if (A1 <= B1 && A2 >= B2)
            self_contained_ranges++;
        else if (B1 <= A1 && B2 >= A2)
            self_contained_ranges++;

        //Could easily be reduced
        if (A1 <= B1 && A2 >= B1)
            overlapping_ranges++;
        else if (A1 <= B2 && A2 >= B2)
            overlapping_ranges++;
        else if (A1 <= B1 && A2 >= B2)
            overlapping_ranges++;
        else if (B1 <= A1 && B2 >= A2)
            overlapping_ranges++;
    }

    printf("%i pairs contains themselves\n", self_contained_ranges);
    printf("%i pairs overlaps\n", overlapping_ranges);

    return 0;
}
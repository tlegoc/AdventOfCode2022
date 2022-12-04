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
        std::string first_pair;
        std::string second_pair;

        split_string(s, ',', &first_pair, &second_pair);

        //Fp stands for first pair, h for head, t for tail
        std::string fp_h;
        std::string fp_t;
        split_string(first_pair, '-', &fp_h, &fp_t);
        printf("fp_h: %s, fp_t: %s -- ", fp_h.c_str(), fp_t.c_str());

        //Sp stands for second pair, h for head, t for tail
        std::string sp_h;
        std::string sp_t;
        split_string(second_pair, '-', &sp_h, &sp_t);
        printf("sp_h: %s, sp_t: %s\n", sp_h.c_str(), sp_t.c_str());

        //Ugly but works, I tried to be fast instead of being optimised and clean
        if (stoi(fp_h) <= stoi(sp_h) && stoi(fp_t) >= stoi(sp_t))
            self_contained_ranges++;
        else if (stoi(sp_h) <= stoi(fp_h) && stoi(sp_t) >= stoi(fp_t))
            self_contained_ranges++;

        //Could easily be reduced
        if (stoi(fp_h) <= stoi(sp_h) && stoi(fp_t) >= stoi(sp_h))
            overlapping_ranges++;
        else if (stoi(fp_h) <= stoi(sp_t) && stoi(fp_t) >= stoi(sp_t))
            overlapping_ranges++;
        else if (stoi(fp_h) <= stoi(sp_h) && stoi(fp_t) >= stoi(sp_t))
            overlapping_ranges++;
        else if (stoi(sp_h) <= stoi(fp_h) && stoi(sp_t) >= stoi(fp_t))
            overlapping_ranges++;
    }

    printf("%i pairs contains themselves\n", self_contained_ranges);
    printf("%i pairs overlaps\n", overlapping_ranges);

    return 0;
}
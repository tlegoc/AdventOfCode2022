#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <bits/stdc++.h>

int main(int argc, char const *argv[])
{
    if (!std::filesystem::exists("day1"))
    {
        std::cout << "Input file not found" << std::endl;
        return 1;
    }

    std::ifstream input("day1");

    int x = 0;
    std::vector<int> data;

    while (input >> x)
    {
        data.push_back(x);
    }

    std::vector<int> gnomes = {0};

    //The input file will need to be modified first
    //My input method doesn't handle anything besides numbers so
    //I can't know when we skipped a line and started a new block
    //So I just replace every \n\n by \n-1\n
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == -1)
        {
            gnomes.push_back(0);
        }
        else
        {
            gnomes[gnomes.size() - 1] += data[i];
        }
    }

    //Note: the first version found the second and third biggest by 
    //Seeing if the biggest gnome was not the biggest and if so
    //third_biggest = second_biggest
    //second_biggest = biggest
    //biggest = current
    //
    //Obviously this solution isn't correct because if a gnome was
    //Bigger than the second but not the first, it would be ignored
    //For some weird reason it still gave me the right answer ???
    //So here is the correct solution

    //AOC only asks for the calories, not the index of the gnome
    //So why bother making a loop
    sort(gnomes.begin(), gnomes.end());

    int biggest = gnomes.size() - 1;
    int second_biggest = gnomes.size() - 2;
    int third_biggest = gnomes.size() - 3;

    printf("Biggest gnome: %i (calories: %i)\n", biggest, gnomes[biggest]);
    printf("2nd Biggest gnome: %i (calories: %i)\n", second_biggest, gnomes[second_biggest]);
    printf("3rd Biggest gnome: %i (calories: %i)\n", third_biggest, gnomes[third_biggest]);
    printf("Total: %i\n", gnomes[biggest] + gnomes[second_biggest] + gnomes[third_biggest]);

    return 0;
}
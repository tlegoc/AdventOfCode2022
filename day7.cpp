/*

    For some reason this one doesn't work on windows??
    I would love to know why, don't hesitate to do a push request

*/





#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <bits/stdc++.h>

const long TOTAL_SPACE = 70000000;
const long NECESSARY_SPACE = 30000000;

struct file
{
    std::string name;
    long size;
};

struct folder
{
    std::string name;
    std::vector<folder *> subfolders;
    folder *parent_folder;
    std::vector<file *> files;

    bool contain_folder(std::string name)
    {
        for (auto subfolder : subfolders)
            if (subfolder->name == name)
                return true;

        return false;
    }

    bool contain_file(std::string name)
    {
        for (auto file : files)
            if (file->name == name)
                return true;

        return false;
    }

    folder *get_subfolder(std::string name)
    {
        for (auto subfolder : subfolders)
            if (subfolder->name == name)
                return subfolder;

        return nullptr;
    }

    long get_folder_size()
    {
        long size = 0;
        for (auto file : files)
            size += file->size;

        for (auto subfolder : subfolders)
            size += subfolder->get_folder_size();

        return size;
    }

    std::vector<long> get_filtered_size(long filter_size = 100000)
    {
        std::vector<long> sizes;

        for (auto subfolder : subfolders)
        {
            std::vector<long> subfolder_sizes = subfolder->get_filtered_size(filter_size);
            for (auto subfolder_size : subfolder_sizes)
                sizes.push_back(subfolder_size);
        }

        long folder_size = get_folder_size();
        if (folder_size <= filter_size)
            sizes.push_back(folder_size);

        return sizes;
    }

    std::vector<long> get_all_sizes()
    {

        std::vector<long> sizes;

        for (auto subfolder : subfolders)
        {
            std::vector<long> subfolder_sizes = subfolder->get_all_sizes();
            for (auto subfolder_size : subfolder_sizes)
                sizes.push_back(subfolder_size);
        }

        long folder_size = get_folder_size();
        sizes.push_back(folder_size);

        return sizes;
    }

    void printf_folder(int depth = 0)
    {
        for (int i = 0; i < depth; i++)
        {
            printf("-");
        }
        printf("%s\n", this->name.c_str());
        for (auto subfolder : this->subfolders)
            subfolder->printf_folder(depth + 1);

        for (auto file : this->files)
        {
            for (int i = 0; i < depth + 1; i++)
                printf(" ");

            printf("%s %ld\n", file->name.c_str(), file->size);
        }
    }
};

int main(int argc, char *argv[])
{
    // Loading our file
    if (!std::filesystem::exists("day7"))
    {
        printf("input file does not exist\n");
        return 1;
    }

    std::ifstream input("day7");

    std::string line = "";

    folder *root_folder = nullptr;
    folder *current_folder = nullptr;
    while (input.good())
    {
        std::string name;
        char temp_name[256];
        long size;

        std::getline(input, line);

        // CD COMMAND
        if (sscanf(line.c_str(), "$ cd %s", temp_name) == 1)
        {
            name = std::string(temp_name);

            // cd root and cd back
            if (name == "/" && root_folder != nullptr)
            {
                current_folder = root_folder;
                continue;
            }
            else if (name == "..")
            {
                current_folder = current_folder->parent_folder;
                continue;
            }

            // If we haven't created the root.
            // Done only once
            if (root_folder == nullptr)
            {
                printf("Creating root folder\n");
                root_folder = new folder{std::string(name), {}, {}};
                current_folder = root_folder;
            }
            // Most cases will end up here
            else
            {
                // Move into folder if it was already created
                if (current_folder != nullptr && current_folder->contain_folder(name))
                {
                    current_folder = current_folder->get_subfolder(name);
                    continue;
                }

                // If not create then move
                current_folder->subfolders.push_back(new folder{std::string(name), {}, {}});
                current_folder->subfolders.back()->parent_folder = current_folder;
                current_folder = current_folder->subfolders.back();
            }
        }
        // LS COMMAND
        else if (line == "$ ls")
        {
            std::string ls_line;
            while (input.good())
            {
                // getline consume the current position so we store the last position
                std::streampos pos = input.tellg();
                std::getline(input, ls_line);

                if (ls_line[0] == '$')
                {
                    // If it's not a dir/file line we go back and
                    // Do everything again, because it's a new command
                    input.seekg(pos);
                    break;
                }

                // If it's a dir
                if (sscanf(ls_line.c_str(), "dir %s", temp_name) == 1)
                {
                    // Create the folder if it doesn"t exist
                    if (current_folder->contain_folder(temp_name))
                        continue;

                    current_folder->subfolders.push_back(new folder{std::string(temp_name), {}, {}});
                    current_folder->subfolders.back()->parent_folder = current_folder;
                }
                // If it's a file
                else if (sscanf(ls_line.c_str(), "%ld %s", &size, temp_name) == 2)
                {
                    // Create the file if it doesn't exist
                    if (current_folder->contain_file(temp_name))
                        continue;

                    current_folder->files.push_back(new file{std::string(temp_name), size});
                }
            }
        }
    }

    root_folder->printf_folder();

    // This function just return the size of all folders
    // That are smaller than the filter size
    std::vector<long> sizes = root_folder->get_filtered_size(100000);

    // Add them together (could do sum but didn't work ??)
    long total_filtered_size = 0;
    for (auto size : sizes)
        total_filtered_size += size;

    // Same as get_filtered_size but without filter
    std::vector<long> all_sizes = root_folder->get_all_sizes();
    sort(all_sizes.begin(), all_sizes.end());

    long taken_space = root_folder->get_folder_size();

    // Find the folder to delete
    long size_index = 0;
    while (size_index < all_sizes.size() && TOTAL_SPACE - taken_space + all_sizes[size_index] < NECESSARY_SPACE)
        size_index++;

    printf("--------------------\n");
    printf("Total size: %ld\n", root_folder->get_folder_size());
    printf("Total filtered size: %ld\n", total_filtered_size);
    printf("Disk usage: %ld (%f)\n", taken_space, (double)taken_space / TOTAL_SPACE);
    printf("Available: %ld\n", TOTAL_SPACE - taken_space);
    printf("You can delete a folder of size %ld to perform the update\n", all_sizes[size_index]);

    return 0;
}
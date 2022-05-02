#include <iostream>
#include <chrono>
#include "datatable.hpp"
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<unsigned int> distribution(0, 2 ^ 32 - 1);

int main(int argc, char **argv)
{
    DataTable<unsigned int> dt_u32;
    bool temp = false;
    unsigned int rand = 0;

    auto start = std::chrono::high_resolution_clock::now();
    dt_u32.fromCSV("ui_5000_5000.csv");
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Loading\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
    {
        for (auto row : *dt_u32.table)
        {
            for (auto col : row)
            {
                rand = distribution(generator);
                if (col < rand)
                {
                    temp = true;
                }
                else
                {
                    temp = false;
                }
            }
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Worse\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 100 << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
    {
        for (auto row : *dt_u32.table)
        {
            for (auto col : row)
            {
                temp = col < distribution(generator);
            }
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Better\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() / 100 << "ms\n";

    return 0;
}
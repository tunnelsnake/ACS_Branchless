#include <iostream>
#include <chrono>
#include "datatable.hpp"

bool convertU32ToBool(unsigned int * t) {
    return *t < 2001916101;
}

std::vector<bool> convertVU32ToVBool(std::vector<unsigned int> & v) {
    std::vector<bool> ret;
    for (int index = 0; index < v.size(); index++) {
        ret.push_back( v[index] < 2001916101);
    }
    return ret;
}

int main(int argc, char ** argv) {
    DataTable<unsigned int> dt_u32;
    DataTable<int> dt_s32;
    DataTable<float> dt_f32;
    DataTable<double> dt_f64;
    DataTable<std::string> dt_str;
    DataTable<char> dt_char;

    /* Test Loading CSVs with the correct data type */
    // Load ints from CSV
    // Unsigned
    std::cout << "Load an integer CSV:" << std::endl;
    dt_u32.fromCSV("data/ui_10_2.csv");
    dt_u32.print();
    std::cout << "\n";

    // Signed
    std::cout << "Load a signed integer CSV:" << std::endl;
    dt_s32.fromCSV("data/si_10_2.csv");
    dt_s32.print();
    std::cout << "\n";

    // Load floats from CSV
    std::cout << "Load a floating point CSV" << std::endl;
    dt_f32.fromCSV("data/f_10_2.csv");
    dt_f32.print();
    std::cout << "\n";

    // Load floats as doubles from CSV
    std::cout << "Load a double float CSV" << std::endl;
    dt_f64.fromCSV("data/f_10_2.csv");
    dt_f64.print();
    std::cout << "\n";

    // Load strings from CSV
    std::cout << "Load a string CSV" << std::endl;
    dt_str.fromCSV("data/str_10_2.csv");
    dt_str.print();
    std::cout << "\n";

    // Load chars from CSV
    std::cout << "Load a char CSV" << std::endl;
    dt_char.fromCSV("data/chr_10_2.csv");
    dt_char.print();
    std::cout << "\n";

    /* Cleanup */
    dt_u32.clear();
    dt_s32.clear();
    dt_f32.clear();
    dt_f64.clear();
    dt_str.clear();

    /* Weirder stuff with loading CSVs */
    // Load Float and double from an integer file (Defined Behavior)
    std::cout << "Floats and Doubles from int file:" << std::endl;
    dt_f32.fromCSV("data/ui_10_2.csv");
    dt_f32.print();
    dt_f64.fromCSV("data/ui_10_2.csv");
    dt_f64.print();
    std::cout << "\n";

    // Load Integer from float file (Defined Behavior)
    // Float file has signs in it, only do signed conversion.
    std::cout << "Load integer from float file:" << std::endl;
    dt_s32.fromCSV("data/f_10_2.csv");
    dt_s32.print();
    std::cout << "\n";

    // Try to load strings from integers and floats (Defined Behavior)
    std::cout << "Load strings from float file:" << std::endl;
    dt_str.fromCSV("data/f_10_2.csv");
    dt_str.print();
    std::cout << "\n";

    std::cout << "Load strings from int file:" << std::endl;
    dt_str.clear();
    dt_str.fromCSV("data/ui_10_2.csv");
    dt_str.print();
    std::cout << "\n";

    // Try to load integers from strings (Undefined Behavior)
    std::cout << "Load (unsigned) integers from strings:" << std::endl;
    dt_u32.fromCSV("data/str_10_2.csv");
    dt_u32.print();
    std::cout << "\n";

    std::cout << "Load (signed) integers from strings:" << std::endl;
    dt_s32.clear();
    dt_s32.fromCSV("data/str_10_2.csv");
    dt_s32.print();
    std::cout << "\n";

    // Try to load chars from integers and floats (Undefined Behavior)
    std::cout << "Load char from integers (much larger):" << std::endl;
    dt_char.clear();
    dt_char.fromCSV("data/ui_10_2.csv");
    dt_char.print();
    std::cout << "\n";
    std::cout << std::flush;

    /* Test the map function */

    dt_u32.clear();
    dt_u32.fromCSV("data/ui_5000_5000.csv");

    // Time a sequential map (no OpenMP)
    auto start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    dt_u32.map(&convertU32ToBool);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Map in sequence\t\t: " <<  std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";


    // Time a parallel map (OpenMP)
    start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    dt_u32.map_parallel(&convertU32ToBool);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Map in parallel\t\t: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";



    // Time a row map operation
    start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    // Do a row map.
    dt_u32.mapRows(&convertVU32ToVBool);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Row Map (sequence)\t: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";

    // Time a row map operation
    start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    // Do a row map.
    dt_u32.mapRowsParallel(&convertVU32ToVBool);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Row Map (parallel)\t: " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";

    return 0;
}
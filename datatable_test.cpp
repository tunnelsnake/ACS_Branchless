#include <iostream>
#include <chrono>
#include "datatable.hpp"
#include <random>


std::string & upperCaseNaive(std::string & s) {
    for (int i = 0; i < s.size(); i++) {
        if ( 0x60 < s[i] < 0x7b ) {
            s[i] = s[i] - 0x20;
        }
    }
    return s;
}

std::string & upperCaseBranchless(std::string & s) {
    for (int i = 0; i < s.size(); i++) {

        // Branch-Free / No-Lookup 
        // toupper() for ASCII-only 
        const int ConvertVal = 'A' - 'a'; 
        // Bits to Shift Arithmetic to Right : 9 == (char-bits + 1) 
        const int AsrBits = 9; 

        int c=(int) s[i]; 
        //if( (('a'-1)<c) && (c<('z'+1)) ) { c += 'A'-'a'; } 
        int LowerBound = ('a'-1) - c; 
        int UpperBound = c - ('z' + 1); 
        int BranchFreeMask = (LowerBound & UpperBound)>>AsrBits;
        c = c + (BranchFreeMask & ConvertVal); 
        s[i] = (char) c; 
    }
    return s;
}

#include <emmintrin.h>
#include <immintrin.h>

inline __m128i upcase_si128(__m128i src) {
    // The above 2 paragraphs were comments here
    __m128i rangeshift = _mm_sub_epi8(src, _mm_set1_epi8('a'+128));
    __m128i nomodify   = _mm_cmpgt_epi8(rangeshift, _mm_set1_epi8(-128 + 25));  // 0:lower case   -1:anything else (upper case or non-alphabetic).  25 = 'z' - 'a'

    __m128i flip  = _mm_andnot_si128(nomodify, _mm_set1_epi8(0x20));            // 0x20:lcase    0:non-lcase

    // just mask the XOR-mask so elements are XORed with 0 instead of 0x20
    return          _mm_xor_si128(src, flip);
    // it's easier to xor with 0x20 or 0 than to AND with ~0x20 or 0xFF
}


std::string & upperCaseSIMD(std::string & s) {
    unsigned int count = s.size();
    __m128i * str_base = (__m128i *) s.data();
    for (int i = 0; i < count / 16; i++) {
        __m128i * strloc = (__m128i *) (((void *) str_base) + i * 16);
        // Pack into m128is, which is 128/8 = 16
        __m128i s = _mm_loadu_si128(strloc);
        s = upcase_si128(s);
        _mm_store_si128(strloc, s);
    }
    return s;
}

std::default_random_engine generator;
std::uniform_int_distribution<unsigned int> distribution(0, 2^32 - 1);

// int foo(int i) __attribute__((optimize("-O3")));
// bool unpredictableComparision(unsigned int * t) __attribute__((optimize("-O0"))) {
bool unpredictableComparision(unsigned int * t) {

    if (*t < distribution(generator)) {
        return true;
    }
    else {
        return false;
    }
}

bool betterComparison(unsigned int * t) {
    return *t < distribution(generator);
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

    #ifdef TEST_CSV

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
    #endif

    /* Test the map function */

    // dt_u32.clear();
    // dt_u32.fromCSV("data/ui_5000_5000.csv");

    // // Time a sequential map (no OpenMP)
    // auto start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // for (int i = 0; i < 20; i++) {
    //     dt_u32.map(&unpredictableComparision);
    // }
    // auto finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Map in sequence\t\t: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";


    // // Time a parallel map (OpenMP)
    // start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // dt_u32.map_parallel(&unpredictableComparision);
    // finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Map in parallel\t\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";

    // // Time a sequential map (no OpenMP)
    // start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // for (int i = 0; i < 20; i++) {
    //     dt_u32.map(&betterComparison);
    // }
    // finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Map in sequence\t\t: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";


    // // Time a parallel map (OpenMP)
    // start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // dt_u32.map_parallel(&betterComparison);
    // finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Map in parallel\t\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";


    // // Time a row map operation
    // start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // // Do a row map.
    // dt_u32.mapRows(&convertVU32ToVBool);
    // finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Row Map (sequence)\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";

    // // Time a row map operation
    // start = std::chrono::high_resolution_clock::now();
    // // operation to be timed ...
    // // Do a row map.
    // dt_u32.mapRowsParallel(&convertVU32ToVBool);
    // finish = std::chrono::high_resolution_clock::now();
    // std::cout << "Row Map (parallel)\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";

    dt_str.clear();
    dt_str.fromCSV("data/str_1000_1000.csv");
    dt_str.mapInPlace(&upperCaseNaive);

        // Time a row map operation
    auto start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    // Do a row map.
    for (int i = 0; i < 50; i++)
    dt_str.mapInPlace(&upperCaseNaive);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Row Map (naive)\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";

    // Time a row map operation
    start = std::chrono::high_resolution_clock::now();
    // operation to be timed ...
    // Do a row map.
    for (int i = 0; i < 50; i++)
    dt_str.mapInPlace(&upperCaseBranchless);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Row Map (Branchless)\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";

    for (int i = 0; i < 50; i++)
    dt_str.mapInPlace(&upperCaseSIMD);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Row Map (SIMD)\t: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() / 50 << "ms\n";


    return 0;


}
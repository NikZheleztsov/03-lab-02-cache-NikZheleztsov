/* Copyright 2021 Nikita Zheleztsov */

#include <cstdlib>
#include <ctime>
// all enums are here
#include "./investigate.h"
#include <iostream>
#include <memory>
#include "./misc.h"
#include <vector>

/*
 * L1 = 32KiB
 * L2 = 512KiB
 * L3 = 4096KiB
 */

std::unique_ptr<std::ostream> out;

int main(int argc, char* argv[])
{
    // parsing command line arguments
    try {
        parse_cma(argc, argv);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "test_cache [-o <output_file]"
            << std::endl;
        return 1;
    }

    int arr_size = lev_5;
    int* test_array = new int[arr_size];
    uint32_t seed = 5000;

    for (int i = 0; i < arr_size; ++i)
        test_array[i] = rand_r(&seed);

    for (int i = -1; i < 2; ++i)
    {
        Investigation temp(test_array, static_cast<Travel_order>(i));
        *out << temp.get_report();
    }

    delete[] test_array;
    return 0;
}

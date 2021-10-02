#ifndef INVESTIGATE_H
#define INVESTIGATE_H
#include <chrono>
#include <string>
#include <vector>

enum Size_of_vector
{
    // L1
    lev_1 = 4096,       // 16 * 1024 / 4
    lev_2 = 8192,       // 32 * 1024 / 4

    // L2
    lev_3 = 131072,     // 512 * 1024 / 4

    // L3
    lev_4 = 1048576,    // 4096 * 1024 / 4

    // RAM
    lev_5 = 1572864,    // 4096 * 1.5 * 1024 / 4
};

enum Travel_order
{
    reverse_order = -1,
    random_order,
    direct_order,
};

class Experiment
{
    size_t buffer_size;
    std::chrono::duration<int, std::nano> duration;

public:
    explicit Experiment(int* begin, 
        int* end, Travel_order&);
    std::string get_data();
};

class Investigation
{
    std::string travel_order;
    std::vector<std::pair<unsigned, Experiment>> experiments;

public:
    Investigation() {}
    explicit Investigation(int*, Travel_order);
    Investigation& operator = (Investigation&&);
    std::string get_report();
};

#endif // INVESTIGATE_H

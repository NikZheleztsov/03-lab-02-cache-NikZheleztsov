/* Copyright 2021 Nikita Zheleztsov */

#include <ctime>
#include "./investigate.h"
#include <iostream>
#include <memory>
#include <string>

///////////////////
// Investigation //
///////////////////

Investigation::Investigation(int* arr,
        Travel_order order)
{
    switch (order)
    {
        case direct_order:
            travel_order = "direct";
            break;

        case reverse_order:
            travel_order = "reverse";
            break;

        case random_order:
            travel_order = "random";
    }

    Size_of_vector sizes[5] = {lev_1, lev_2,
        lev_3, lev_4, lev_5};

    experiments.reserve(5);
    for (int i = 0; i < 5; ++i)
        experiments.push_back(std::make_pair(i, Experiment(
                        arr, arr + sizes[i], order)));
}

Investigation& Investigation::operator= (Investigation&& other)
{
    travel_order = std::move(other.travel_order);
    experiments = std::move(other.experiments);
    return *this;
}

std::string Investigation::get_report()
{
    std::string report("investigation:\n    travel_order: \"");
    report += travel_order + '"' + '\n' + "    experiments:\n";
    for (auto x : experiments)
    {
        report += "    - experiment:\n        number: "
            + std::to_string(x.first + 1) + '\n';
        report += x.second.get_data();
    }

    report += "\n\n";
    return report;
}

///////////////////
//   Experiment  //
///////////////////

Experiment::Experiment(int* begin,
        int* end, Travel_order& order)
{
    // Buffer size
    buffer_size = (end - begin) * 4 / 1024;

    // Cache heating
    [[maybe_unused]] int k = 0;
    for (auto temp = begin; temp - end < 0; temp += 16)
        k = *temp;

    int* temp;
    order != reverse_order ? temp = begin : temp = end;
    
    std::chrono::time_point<std::chrono::steady_clock> time_start, time_end;
    if (order == direct_order)
    {
        time_start = std::chrono::steady_clock::now();
        for (size_t index = 0; index < 1000; ++index,
                temp += (end - begin) / 1000)
            k = *temp;
        time_end = std::chrono::steady_clock::now();

    } else if (order == reverse_order) {
        time_start = std::chrono::steady_clock::now();
        for (size_t index = 0; index < 1000; ++index,
                temp -= (end - begin) / 1000)
            k = *temp;
        time_end = std::chrono::steady_clock::now();

    } else {
        std::vector<int> random(1000);
        uint32_t seed = 1000;
        for (int i = 1; i < 1000; ++i)
            random[i] = rand_r(&seed) % (end - begin);

        time_start = std::chrono::steady_clock::now();
        for (size_t index = 0; index < 1000; ++index)
            k = *(begin + random[index]);
        time_end = std::chrono::steady_clock::now();
    }

    duration = std::chrono::duration_cast
        <std::chrono::nanoseconds>(time_end - time_start) / 1000;
}

std::string Experiment::get_data()
{
    std::string data("        input_data:\n\          buffer_size: ");

    data += std::to_string(buffer_size) + "KiB\n"
        + "\        results:\n          duration: "
        + std::to_string(duration.count()) + "ns\n";

   return data;
}

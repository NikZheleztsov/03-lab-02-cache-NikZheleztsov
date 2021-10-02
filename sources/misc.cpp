#include <iostream>
#include <memory>
#include <fstream>

extern std::unique_ptr<std::ostream> out;

void parse_cma(int argc, char* argv[])
{
    if (argc > 1)
    {
        bool is_ok = false;
        for (int i = 0; i < argc; ++i)
        {
            if (std::string(argv[i]) == "-h") {
                std::cout << "test_cache [-o <output_file]\n";
                exit(0);

            } else if (std::string(argv[i]) == "-o") {
                out = std::unique_ptr<std::ostream>
                    (new std::ofstream(argv[i + 1]));
                is_ok = true;
            }
        }

        if (!is_ok)
            throw std::invalid_argument
                ("Error while parsing the arguments");
    }

    if (out == nullptr)
        out = std::unique_ptr<std::ostream>
            (new std::ostream(std::cout.rdbuf()));
}

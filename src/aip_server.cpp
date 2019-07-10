#include <iostream>
#include "aip.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Requires 2 arguments metadata.json filepath and model.pt filepath." << std::endl;
        return 1;
    }

    std::string metadata_filepath = argv[1];
    std::string model_filepath = argv[2];

    if (!aip::file_exists(metadata_filepath))
    {
        std::cout << "File does not exist: " << metadata_filepath << std::endl;
        return 1;
    }

    if (!aip::file_exists(model_filepath))
    {
        std::cout << "File does not exist: " << model_filepath << std::endl;
        return 1;
    }

    auto metadata = aip::read_metadata(metadata_filepath);
    aip::metadata_info(metadata);

    aip::torch_test();

    return 0;
}
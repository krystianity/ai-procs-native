#include <iostream>
#include <torch/torch.h>
#include "./deps/json.hpp"

using json = nlohmann::json;

namespace aip
{

bool file_exists(std::string file_path)
{
    std::ifstream ifile(file_path.c_str());
    return (bool)ifile;
}

json read_metadata(std::string file_path)
{
    std::ifstream i(file_path);
    json j;
    i >> j;
    return j;
}

void metadata_info(json metadata)
{
    std::cout << metadata["version"] << std::endl;
    std::cout << metadata["options"]["model_type"] << std::endl;
}

void torch_test()
{
    torch::Tensor tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;
}
} // namespace aip
#include <iostream>
#include <torch/script.h>
#include <zmq.hpp>
#include <string>
#include <unistd.h>
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

torch::jit::script::Module load_torch_model(std::string file_path)
{
    torch::jit::script::Module model = torch::jit::load(file_path.c_str());

    bool in_training = model.is_training();
    bool is_optimized = model.is_optimized();
    std::cout << "Model loaded." << std::endl;
    std::cout << "Training mode: " << in_training << std::endl;
    std::cout << "Optimized: " << in_training << std::endl;

    return model;
}

void run_zmq_server()
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5560");

    while (true)
    {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv(&request);
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        zmq::message_t reply(5);
        memcpy((void *)reply.data(), "World", 5);
        socket.send(reply);
    }
}
} // namespace aip

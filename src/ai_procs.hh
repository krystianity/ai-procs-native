#include <iostream>
#include <vector>

double aip_normalize(int value, int min, int max)
{
    return ((double)value - (double)min) / ((double)max - (double)min);
}

int aip_denormalize(double normalized, int min, int max)
{
    return (int)(normalized * ((double)max - (double)min) + (double)min);
}

struct aip_VectorMetadata
{
    int min;
    int max;
};

aip_VectorMetadata aip_get_vector_metadata(std::vector<int> vec)
{
    if (vec.size() <= 0)
    {
        return aip_VectorMetadata{0, 0};
    }

    int min_value = vec.at(0);
    int max_value = vec.at(0);
    for (auto const &value : vec)
    {
        if (max_value < value)
        {
            max_value = value;
        }

        if (min_value > value)
        {
            min_value = value;
        }
    }

    return aip_VectorMetadata{min_value, max_value};
}

std::vector<double> aip_normalize_vector(std::vector<int> vec, aip_VectorMetadata meta)
{
    std::vector<double> r_vec;

    for (auto const &value : vec)
    {
        r_vec.push_back(aip_normalize(value, meta.min, meta.max));
    }

    return r_vec;
}

std::vector<int> aip_denormalize_vector(std::vector<double> vec, aip_VectorMetadata meta)
{
    std::vector<int> r_vec;

    for (auto const &value : vec)
    {
        r_vec.push_back(aip_denormalize(value, meta.min, meta.max));
    }

    return r_vec;
}

void aip_test_vector()
{
    std::vector<int> t_vec;
    t_vec.push_back(100);
    t_vec.push_back(75);
    t_vec.push_back(50);
    t_vec.push_back(10);
    t_vec.push_back(1);

    auto meta = aip_get_vector_metadata(t_vec);
    auto n_vec = aip_normalize_vector(t_vec, meta);
    auto dn_vec = aip_denormalize_vector(n_vec, meta);

    std::cout << "t_vec:0 = " << t_vec.at(1) << std::endl;
    std::cout << "n_vec:0 = " << n_vec.at(1) << std::endl;
    std::cout << "dn_vec:0 = " << dn_vec.at(1) << std::endl;
}

void aip_test()
{
    aip_test_vector();
}
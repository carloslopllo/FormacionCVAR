#include "reader.hpp"

std::vector<double> readDouble (std::istream& ptr) {

    std::vector<double> res;
    double addNum;

    while(ptr >> addNum)
    {
        res.push_back(addNum);
    }

    return res;
}
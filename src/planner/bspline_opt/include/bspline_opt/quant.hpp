#ifndef QUANT_HPP
#define QUANT_HPP

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

std::pair<double, double> min_max(double* input, int length){
    std::pair<double, double> result;
    std::pair<double*, double*> result_temp;

    result_temp = std::minmax_element(input, input+length);
    result = std::make_pair(*result_temp.first, *result_temp.second);

    return result;
}

std::pair<double, double> quantize_fix(double input, double max_value, double min_value, int bitwidth){
    std::pair<double, double> result;
    double abs_max =  std::max(max_value,-min_value);
    // // copy input
    // double* input_clone = NULL;
    // input_clone = new double[length];
    // for(int j=0; j<length; j++){
    //     input_clone[j] = input[j];
    // }

    int i = 0;
    double scale = 1;
    for(i = 0; abs_max > 1;i++){
        abs_max = abs_max / 2;
        scale = scale * 2;
    }
    
    input = input / scale;
    int bitpoint = bitwidth - 2;
    input = input * pow(2.0, bitpoint);
    input = floor(input + 0.5);
    input = std::clamp(input, -pow(2.0, bitwidth-1), pow(2.0, bitwidth-1)-1);

    input = pow(2.0, -bitpoint) * round(input) * scale;
    result = std::make_pair(input, scale);
    return result;
}

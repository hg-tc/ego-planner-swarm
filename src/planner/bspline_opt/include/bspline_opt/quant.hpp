#ifndef QUANT_HPP
#define QUANT_HPP

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

inline double get_scale(double* input, int length){
    std::pair<double*, double*> result_temp;

    result_temp = std::minmax_element(input, input+length);
    double abs_max =  std::max(*result_temp.second, -*result_temp.first);

    int i = 0;
    double scale = 1;
    for(i = 0; (abs_max > 1 || abs_max <= 0.5) && (abs_max != 0);i++){
        if(abs_max > 1){
            abs_max = abs_max / 2;
            scale = scale * 2;
        }
        else{
            abs_max = abs_max * 2;
            scale = scale / 2;
        }
        
    }

    return scale;
}
inline double get_scale(double input){
    double abs_max = abs(input);

    int i = 0;
    double scale = 1;
    for(i = 0; (abs_max > 1 || abs_max <= 0.5) && (abs_max != 0);i++){
        if(abs_max > 1){
            abs_max = abs_max / 2;
            scale = scale * 2;
        }
        else{
            abs_max = abs_max * 2;
            scale = scale / 2;
        }
        // cout <<"abs_i "<< abs_max << " "<< i << endl;
    }

    return scale;
}

inline double quantize_fix(double input, double scale, int bitwidth){
    // std::pair<double, double> result;
    double result;
    
    input = input / scale;
    int bitpoint = bitwidth - 3;
    input = input * pow(2.0, bitpoint);
    input = floor(input + 0.5);
    // input = std::clamp(input, -pow(2.0, bitwidth-1), pow(2.0, bitwidth-1)-1);
    if(input < -pow(2.0, bitwidth-1)){
        input = -pow(2.0, bitwidth-1);
    }else if(input > pow(2.0, bitwidth-1)-1){
        input = pow(2.0, bitwidth-1)-1;
    }else{
        input = input;
    }

    input = pow(2.0, -bitpoint) * round(input) * scale;
    // result = std::make_pair(input, scale);
    result = input;
    return result;
}
inline double* quantize_fix(double* input, int length, double scale, int bitwidth){
    // std::pair<double, double> result;
    double* result;
    for(int i=0; i<length; i++){
        input[i] = input[i] / scale;
        int bitpoint = bitwidth - 2;
        input[i] = input[i] * pow(2.0, bitpoint);
        input[i] = floor(input[i] + 0.5);
        // input = std::clamp(input, -pow(2.0, bitwidth-1), pow(2.0, bitwidth-1)-1);
        if(input[i] < -pow(2.0, bitwidth-1)){
            input[i] = -pow(2.0, bitwidth-1);
        }else if(input[i] > pow(2.0, bitwidth-1)-1){
            input[i] = pow(2.0, bitwidth-1)-1;
        }else{
            input[i] = input[i];
        }

        input[i] = pow(2.0, -bitpoint) * round(input[i]) * scale;
    }
    
    // result = std::make_pair(input, scale);
    result = input;
    return result;
}
#endif
#ifndef NORMALIZATION_PARAMETERS_H
#define NORMALIZATION_PARAMETERS_H

class Normalization_parameters {
public:
    float min;
    float max;
    float dx_step;
    float dy_step;
    Normalization_parameters(const float max, const float min, const float dx, const float dy);
};

#endif // NORMALIZATION_PARAMETERS_H

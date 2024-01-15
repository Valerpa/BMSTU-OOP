#include "normalization_parameters.h"

Normalization_parameters::Normalization_parameters(const float max, const float min, const float dx, const float dy) {
    this->min = min;
    this->max = max;
    this->dx_step = dx;
    this->dy_step = dy;
}

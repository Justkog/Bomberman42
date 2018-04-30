#ifndef BE_CORE_MATH_HPP
# define BE_CORE_MATH_HPP 1

#include <cmath>

#ifndef M_TORADIANS
    #define M_TORADIANS(x) (x * M_PI / 180.0)
#endif

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"
#include "Matrix4x4.hpp"
#include "Operator.hpp"

#endif
#ifndef __GEOMETRY_COMMON_H_INCLUDED__
#define __GEOMETRY_COMMON_H_INCLUDED__

#include <math.h>

#define PI                                                 3.141593f
#define PI_OVER_180                                        (PI / 180.0f)

#define DEG_TO_RAD(x)                                      ((x) * PI_OVER_180)
#define RAD_TO_DEG(x)                                      ((x) * (1.0f / (PI_OVER_180)))

#define TOLERANCE                                          0.00001f
#define IS_CLOSE_ENOUGH(a, b)                              (fabs((a - b) / ((b == 0.0f) ? 1.0f : b)) < EPSILON)

#define EPSILON                                            0.0005f

#define ISPOWEROF2(x)                                      (((x) != 0) && !((x) & ((x) - 1)))

#endif

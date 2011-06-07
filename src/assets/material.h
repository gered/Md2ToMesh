#ifndef __ASSETS_MATERIAL_H_INCLUDED__
#define __ASSETS_MATERIAL_H_INCLUDED__

#include "../common.h"
#include <string>
#include "color.h"

#define RGB_32(r, g, b, a)                                 ((b)|((g) << 8)|((r) << 16)|((a) << 24))
#define RGB_24(r, g, b)                                    ((b)|((g) << 8)|((r) << 16))
#define RGB_32_f(r, g, b, a)                               RGB_32((int)((r) * 255), (int)((g) * 255), (int)((b) * 255), (int)((a) * 255))
#define RGB_24_f(r, g, b)                                  RGB_24((int)((r) * 255), (int)((g) * 255), (int)((b) * 255))

class Material
{
public:
	std::string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	float shininess;
	float opacity;
};

#endif
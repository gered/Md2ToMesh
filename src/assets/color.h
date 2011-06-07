#ifndef __ASSETS_COLOR_H_INCLUDED__
#define __ASSETS_COLOR_H_INCLUDED__

#include "../common.h"

#define COLOR_ALPHA_TRANSPARENT 0.0f
#define COLOR_ALPHA_OPAQUE 1.0f

class Color
{
public:
	Color()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = COLOR_ALPHA_OPAQUE;
	}

	Color(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
		a = COLOR_ALPHA_OPAQUE;
	}

	Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	uint32_t ToInt()
	{
		return ((uint32_t)(a * 255) << 24) | ((uint32_t)(r * 255) << 16) | ((uint32_t)(g * 255) << 8) | (uint32_t)(b * 255);
	}

	static uint32_t ToInt(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	static uint32_t ToInt(float r, float g, float b, float a)
	{
		return ((int)(a * 255) << 24) | ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
	}

	static void FromInt(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a)
	{
		*a = (color & 0xff000000) >> 24;
		*r = (color & 0x00ff0000) >> 16;
		*g = (color & 0x0000ff00) >> 8;
		*b = (color & 0x000000ff);
	}

	static void FromInt(uint32_t color, float *r, float *g, float *b, float *a)
	{
		*a = ((float)((color & 0xff000000) >> 24)) / 255;
		*r = ((float)((color & 0x00ff0000) >> 16)) / 255;
		*g = ((float)((color & 0x0000ff00) >> 8)) / 255;
		*b = ((float)((color & 0x000000ff))) / 255;
	}

	static Color FromInt(uint32_t color)
	{
		Color out;
		FromInt(color, &out.r, &out.g, &out.b, &out.a);
		return out;
	}

	float r;
	float g;
	float b;
	float a;
};

#endif

#pragma once

#include <iostream>
#include <raylib.h>

Color interpolateColor(Color color_start, Color color_end, int value, int max_value) {
	const uint8_t r = color_start.r + (color_end.r - color_start.r) * value / (float)max_value;
	const uint8_t g = color_start.g + (color_end.g - color_start.g) * value / (float)max_value;
	const uint8_t b = color_start.b + (color_end.b - color_start.b) * value / (float)max_value;

	return Color{ r, g, b, 255 };
}



Color getColorAtPos(int x, int y, Color display_color, int dim) {
	Color color_horizontal = interpolateColor(WHITE, display_color, x, dim);
	Color color_vertical = interpolateColor(color_horizontal, BLACK, y, dim);
	return color_vertical;
}



bool inBound(Vector2 pos, int dim) {
	return pos.x >= 0 && pos.x < dim && pos.y >= 0 && pos.y < dim;
}



Texture2D createRGBTexture(Color display_color, int dim) {
	Image temp_rgb_image = GenImageColor(dim, dim, WHITE);

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			Color pixel_color = getColorAtPos(i, j, display_color, dim);
			ImageDrawPixel(&temp_rgb_image, i, j, pixel_color);
		}
	}

	return LoadTextureFromImage(temp_rgb_image);
}



Color getOppositeColor(Color color) {
	const uint8_t r = UINT8_MAX - color.r;
	const uint8_t g = UINT8_MAX - color.g;
	const uint8_t b = UINT8_MAX - color.b;

	return Color{ r, g, b, 255 };
}



template <typename T>
T clampValue(T value, T max, T min) {
	return __max(__min(max, value), min);
}
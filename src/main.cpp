#include <iostream>
#include <raylib.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <array>

#include "helper.h"

// Signatures
void handleEvents();
void update();
void render();
void changeDisplayColor(Color new_color);

constexpr int DIM = 600;
constexpr int X_OFFSET = DIM + 10;

Texture2D rgb_texture;

Color display_color{ 255, 0, 0, 255 };
Color selected_color = display_color;

bool isMouseButtonDown = false;
Vector2 cursor_pos{ DIM / 2, DIM / 2 };

int main() {

	// DIM = RGB, 200 = Info pannel
	InitWindow(DIM + 200, DIM, "RGB Picker");

	rgb_texture = createRGBTexture(display_color, DIM);

	while (!WindowShouldClose()) {
		handleEvents();
		update();
		render();
	}

	return EXIT_SUCCESS;
}




void handleEvents() {

	// Pick color
	if(isMouseButtonDown) selected_color = getColorAtPos(cursor_pos.x, cursor_pos.y, display_color, DIM);

	// Change color
	switch (GetKeyPressed()) {
	case KEY_ONE:
		changeDisplayColor({ 255, 0, 0, 255 }); // RED
		break;
	case KEY_TWO:
		changeDisplayColor({ 0, 255, 0, 255 }); // GREEN
		break;
	case KEY_THREE:
		changeDisplayColor({ 0, 0, 255, 255 }); // BLUE
		break;
	case KEY_FOUR:
		changeDisplayColor({ 255, 255, 0, 255 }); // YELLOW
		break;
	case KEY_FIVE:
		changeDisplayColor({ 255, 105, 0, 255 }); // ORANGE
		break;
	case KEY_SIX:
		changeDisplayColor({ 153, 0, 153, 255 }); // PURPLE
		break;
	case KEY_SEVEN:
		changeDisplayColor({ 255, 255, 255, 255 }); // WHITE
		break;
	case KEY_EIGHT:
		changeDisplayColor({ 0, 0, 0, 255 }); // BLACK
		break;
	}
}



void update() {
	isMouseButtonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	Vector2 mouse_pos = GetMousePosition();

	if (isMouseButtonDown) {
		if(inBound(cursor_pos, DIM)) cursor_pos = mouse_pos;

		cursor_pos = Vector2{ (float)clampValue<int>(cursor_pos.x, DIM - 1, 0), (float)clampValue<int>(cursor_pos.y, DIM - 1, 0) };
	}

	std::string title = "RGB Picker, FPS: " + std::to_string(GetFPS());
	SetWindowTitle(title.c_str());
}



void render() {
	BeginDrawing();
	ClearBackground(BLACK);

		// ---------- RGB COLOR PICKER ---------- //
		DrawTexture(rgb_texture, 0, 0, WHITE); // RGB Texture
		DrawCircleLines(cursor_pos.x, cursor_pos.y, 5, getOppositeColor(selected_color)); // Color Cursor

		// ---------- INFO TAB ---------- //
		constexpr Color info_tab_color{255, 255, 255, 255};

		DrawRectangle(DIM, 0, 200, DIM, BLACK); // Info Tab Background
		DrawLine(DIM, 0, DIM, DIM, info_tab_color); // Info Tab Separating line
		DrawRectangleRounded(Rectangle{ X_OFFSET, 10, 180, 180 }, .1f, 0, selected_color); // Square of Selected Color
		DrawRectangleRoundedLines(Rectangle{ X_OFFSET, 10, 180, 180 }, .1f, 0, 1, info_tab_color); // Square's Outline of Selected Color

		// Text of Selected Color RGB
		std::string selected_color_r = "r: " + std::to_string(selected_color.r);
		DrawText(selected_color_r.c_str(), X_OFFSET + 5, 205, 20, info_tab_color);

		std::string selected_color_g = "g: " + std::to_string(selected_color.g);
		DrawText(selected_color_g.c_str(), X_OFFSET + 5 + 60, 205, 20, info_tab_color);

		std::string selected_color_b = "b: " + std::to_string(selected_color.b);
		DrawText(selected_color_b.c_str(), X_OFFSET + 5 + 120, 205, 20, info_tab_color);

		// Text of Selected Color Hex
		std::stringstream str_stream;
		str_stream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)selected_color.r;
		str_stream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)selected_color.g;
		str_stream << std::hex << std::setw(2) << std::setfill('0') << std::uppercase << (int)selected_color.b;
		std::string hex_code = "Hex: 0x" + str_stream.str();
		DrawText(hex_code.c_str(), X_OFFSET + 5, 230, 25, info_tab_color);

		// Keybinds Help Text
		const char* key_help = "'1' = Red \n\n'2' = Green \n\n'3' = Blue \n\n'4' = Yellow \n\n'5' = Orange \n\n'6' = Purple \n\n'7' = White \n\n'8' = Black";
		DrawText(key_help, X_OFFSET + 5, 270, 25, info_tab_color);

	EndDrawing();
}



void changeDisplayColor(Color new_color) {
	display_color = new_color;
	selected_color = getColorAtPos(cursor_pos.x, cursor_pos.y, display_color, DIM);

	UnloadTexture(rgb_texture);
	rgb_texture = createRGBTexture(new_color, DIM);
}



void WinMain() {
	main();
}
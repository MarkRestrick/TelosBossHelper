#pragma once

#include "window.h"
#include <string>

class DrawRect : public Window
{

	public:
		DrawRect(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a);
		DrawRect(const Window &window, int w, int h, int x, int y, const std::string &image_path);
		~DrawRect();

		void draw() const;
		

	protected:
		int m_w, m_h;
		int m_x, m_y;
		int m_r, m_g, m_b, m_a;
		SDL_Texture *m_texture = nullptr;
		SDL_Rect m_ClippedRect = { -1, -1, -1, -1 };
};
#include "drawrect.h"
#include <SDL_image.h>
#include <iostream>


DrawRect::DrawRect(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a) :
	Window(window), m_w(w), m_h(h), m_x(x), m_y(y), m_r(r), m_g(g), m_b(b), m_a(a)
{

}

DrawRect::DrawRect(const Window &window, int w, int h, int x, int y, const std::string &image_path) :
	Window(window), m_w(w), m_h(h), m_x(x), m_y(y)
{
	auto surface = IMG_Load(image_path.c_str());
	if (!surface)
	{
		std::cerr << "Failed to create surface.  \n" << image_path.c_str();
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	if (!m_texture)
	{
		std::cerr << "Failed to create texture \n";
	}

	SDL_FreeSurface(surface);
}

DrawRect::~DrawRect()
{
	SDL_DestroyTexture(m_texture);

}

void DrawRect::draw() const
{
	/*
	SDL_Rect screenRectangle = { 0, 0, 300, 300 };
	SDL_Rect imageRectangle = { m_w, m_h, m_x, m_y };
	*/

	SDL_Rect rect = { m_x, m_y, m_w, m_h };
	SDL_Rect surger = { 0, 77, 308, 55 };
	
	if (m_texture)
	{
		if (m_ClippedRect.x == -1)
		{
			SDL_RenderCopy(m_renderer, m_texture, NULL, &rect);
		}
		else
		{
			SDL_RenderCopy(m_renderer, m_texture, &m_ClippedRect, &surger);
		}
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, m_a);
		SDL_RenderFillRect(m_renderer, &rect);
	}
	


	//SDL_RenderCopy(m_renderer, m_texture, &screenRectangle, &imageRectangle);  //Add image to renderer
}

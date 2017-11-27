#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Window
{
public:
	Window(const std::string &title, int width, int height);
	~Window();

	void pollEvents();
	void clear() const;
	inline bool isClosed() const { return m_closed; }

private:
	bool init();

	std::string m_title;
	int m_width = 300;
	int m_height = 300;

	bool m_closed = false;

protected:
	SDL_Window *m_window = nullptr;
	SDL_Renderer *m_renderer = nullptr;
	//SDL_Texture *m_texture = nullptr;
	//SDL_Texture *LoadTexture(std::string file);

};
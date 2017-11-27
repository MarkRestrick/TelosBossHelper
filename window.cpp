#include "window.h"

Window::Window(const std::string &title, int width, int height)
{
	m_title = title;
	m_width = width;
	m_height = height;

	if (!init())
	{
		printf("Init failed");
		m_closed = true;
	}

	//m_texture = LoadTexture("RedAnima.png");
	//SDL_Event e;
	/*
	if (m_texture == nullptr)
	{
		printf("Couldn't load image");
	}

	SDL_Rect screenRectangle = { 0, 0, m_width, m_height };
	SDL_Rect imageRectangle = { 0, 0, 100, 100 };
	

	SDL_RenderClear(m_renderer); //Clear renderer

	SDL_RenderCopy(m_renderer, m_texture, &screenRectangle, &imageRectangle);  //Add image to renderer

	SDL_RenderPresent(m_renderer); //Render it

	
	while (!m_closed)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				m_closed = true;
				break;
			default:
				break;
			}
		}
									 //SDL_FillRect(screen, NULL, bgColor);
									 //SDL_UpdateWindowSurface(window);
	}
	*/

}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	m_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

void Window::pollEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type) 
		{
		case SDL_QUIT:
			m_closed = true;
			break;
		default:
			break;
		}
	}
}

void Window::clear() const
{
	SDL_RenderPresent(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 200, 128);
	SDL_RenderClear(m_renderer);
	/*
	SDL_Rect screenRectangle = { 0, 0, m_width, m_height };
	SDL_Rect imageRectangle = { 0, 0, 100, 100 };
	SDL_RenderCopy(m_renderer, m_texture, &screenRectangle, &imageRectangle);  //Add image to renderer
	*/


	
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_ALWAYS_ON_TOP);

	if (m_window == NULL)
	{
		printf("Window could not be created! SDL_Erorr: %s\n", SDL_GetError());
		return false;
	}

	//screen = SDL_GetWindowSurface(window);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == NULL)
	{
		printf("We were not able to create the renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) != imgFlags))
	{
		printf("SDL_image could not be initialised! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

/*
SDL_Texture* Window::LoadTexture(std::string file)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface*loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load the image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create the texture from %s! SDL_Error: %s\n", file.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
*/
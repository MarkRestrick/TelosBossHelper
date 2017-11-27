#include "ScreenChecker.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "window.h"
#include "drawrect.h"
#include "AnimatedRect.h"
#include "Timer.h"

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;
bool Initialize();
void Close();
bool m_GielinorFlag = false;
float m_GielinorTime;

bool m_noPhaseLastFrame = true;
bool m_Phase1LastFrame = false;
bool m_Phase2LastFrame = false;
bool m_Phase3LastFrame = false;
bool m_Phase4LastFrame = false;
bool m_Phase5LastFrame = false;

bool m_P1Tendril = false;
bool m_P1Gielinor = false;
bool m_P1Stun = false;

bool m_P2Stun = false;
bool m_P2Virus = false;
bool m_P2Gielinor = false;
bool m_P2Tendril = false;

bool m_P3Stun = false;
bool m_P3Virus = false;
bool m_P3Gielinor = false;

bool m_P4Stun = false;
bool m_P4Bomb = false;
bool m_P4Gielinor = false;

bool redVir = false; //Used to switch from Stun to Red Virus in P2 Transition

Timer* m_P2TransitionTimer;

SDL_Window* window = NULL;
//SDL_Surface* screen = NULL;
SDL_Texture* LoadTexture(std::string file);
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;



const int FRAME_RATE = 60;

ScreenChecker Screen;

int main(int argc, char *argv[])
{

	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);
	//Hides the console window :D

	m_P2TransitionTimer = Timer::Instance();

	Window window("Telos Boss Helper", 309, 288);
	DrawRect RVirus(window, 309, 288, 0, 0, "Images/BG.jpg");
	DrawRect TENDRILSNEXT(window, 150, 70, 152, 7, "Images/Tendrils.png");
	DrawRect STUNNEXT(window, 150, 70, 152, 7, "Images/Stun.png");
	DrawRect GIELINORNEXT(window, 150, 70, 152, 7, "Images/Uppercut.png");
	//DrawRect MAGICBARRAGENEXT(window, 150, 70, 152, 7, "MAGICBARRAGENEXT.png");
	DrawRect BVIRUSNEXT(window, 150, 70, 152, 7, "Images/BVirNext.png");
	DrawRect RVIRUSNEXT(window, 150, 70, 152, 7, "Images/RVirNext.png");
	DrawRect ABOMBNEXT(window, 150, 70, 152, 7, "Images/Bomb.png");

	DrawRect BLACKVIRUS(window, 81, 73, 38, 132, "Images/BVirus.png");
	DrawRect REDVIRUS(window, 81, 73, 38, 132, "Images/RVirus.png");
	DrawRect GREENVIRUS(window, 81, 73, 38, 132, "Images/GVirus.png");

	DrawRect GREENANIMA(window, 102, 73, 178, 132, "Images/GreenAnima.png");
	DrawRect BLACKANIMA(window, 102, 73, 178, 132, "Images/BlackAnima.png");
	DrawRect REDANIMA(window, 102, 73, 178, 132, "Images/RedAnima.png");

	//DrawRect MAGICBARRPHASE(window, 139, 74, 161, 226, "MAGICBARRAGE.png");
	DrawRect STUNPHASE(window, 150, 70, 152, 210, "Images/Stun.png");
	DrawRect TENDRILPHASE(window, 150, 70, 152, 210, "Images/Tendrils.png");
	DrawRect REDVIRUSPHASE(window, 150, 70, 152, 210, "Images/RVirNext.png");
	DrawRect GIELINORPHASE(window, 150, 70, 152, 210, "Images/Uppercut.png");
	DrawRect ANIMABOMBPHASE(window, 150, 70, 152, 210, "Images/Bomb.png");
	DrawRect P5PHASE(window, 150, 70, 152, 210, "Images/Phase5N.png");


	AnimatedRect rect(window, "Images/SurgeTimer2.png", 0, 0, 308, 55, 17, 2.8f, AnimatedRect::vertical, 0, 0);
	while (!window.isClosed())
	{
		//m_P2TransitionTimer->Update();
		
		

		Screen.Update();
		RVirus.draw();

		if (Screen.GetPhase() == 1)
		{
			if (!m_noPhaseLastFrame && m_Phase2LastFrame || !m_noPhaseLastFrame && m_Phase3LastFrame || !m_noPhaseLastFrame && m_Phase4LastFrame || !m_noPhaseLastFrame && m_Phase4LastFrame)
			{
				//If we're back, reset everything
				m_noPhaseLastFrame = true;

				m_noPhaseLastFrame = true;
				m_Phase1LastFrame = false;
				m_Phase2LastFrame = false;
				m_Phase3LastFrame = false;
				m_Phase4LastFrame = false;
				m_Phase5LastFrame = false;

				m_P1Tendril = false;
				m_P1Gielinor = false;
				m_P1Stun = false;

				m_P2Stun = false;
				m_P2Virus = false;
				m_P2Gielinor = false;
				m_P2Tendril = false;

				m_P3Stun = false;
				m_P3Virus = false;
				m_P3Gielinor = false;

				m_P4Stun = false;
				m_P4Bomb = false;
				m_P4Gielinor = false;

				redVir = false;

			}
			if (m_noPhaseLastFrame)
			{
				m_P1Stun = true;
				m_noPhaseLastFrame = false;
			}

			if (Screen.GetGAnima())
			{
				GREENANIMA.draw();
			}

			if (Screen.GetTendrils())
			{
				m_P1Stun = false;
				m_P1Tendril = true;
				
			}

			if (Screen.GetHoldStill() || Screen.GetPhase1Start())
			{
				m_P1Gielinor = false;
				m_P1Stun = true;
				
			}


			if (Screen.GetGielinor())
			{

				m_P1Gielinor = true;
				m_P1Tendril = false;

			}

			m_Phase1LastFrame = true;


			if (m_P1Tendril == true)
			{
				GIELINORNEXT.draw();
				//MAGICBARRPHASE.draw(); Can't track magic barrage, pretending it doesn't exist
				STUNPHASE.draw();
			}

			if (m_P1Gielinor == true)
			{
				STUNNEXT.draw();
				STUNPHASE.draw();
				rect.Update();
			}
			else
			{
				rect.TimerReset();
			}

			if (m_P1Stun == true)
			{
				TENDRILSNEXT.draw();
				TENDRILPHASE.draw();
			}

		}







		if (Screen.GetPhase() == 2)
		{

			m_Phase2LastFrame = true;

			if (m_Phase1LastFrame)
			{
				m_Phase1LastFrame = false;

				if (m_P1Gielinor)
				{
					m_P2Tendril = true;
				}

				if (m_P1Stun)
				{
					m_P2Gielinor = true;
				}

				if (m_P1Tendril)
				{
					m_P2Tendril = true;
				}
			}

			if (Screen.GetBAnima())
			{
				BLACKANIMA.draw();
			}



			if (Screen.GetTendrils())
			{
				m_P2Tendril = true;
				m_P2Gielinor = false;

			}


			if (Screen.GetHoldStill())
			{
				m_P2Stun = true;
				m_P2Tendril = false;
			}

			if (Screen.GetBVirus() || Screen.GetAnimaCleanse())
			{
				if (Screen.GetBVirus())
				{
					BLACKVIRUS.draw();
				}
				m_P2Virus = true;
				m_P2Stun = false;

			}

			if (Screen.GetGielinor())
			{
				if (m_P2Tendril == false)//Catching errors from tendril being active at the same time
				{
					m_P2Gielinor = true;
					m_P2Virus = false;
				}
				
			}


			if (m_P2Stun == true)
			{
				BVIRUSNEXT.draw();
				REDVIRUSPHASE.draw();
			}

			if (m_P2Virus == true)
			{
				GIELINORNEXT.draw();
				GIELINORPHASE.draw();
			}

			if (m_P2Gielinor == true)
			{
				rect.Update();
				TENDRILSNEXT.draw();
				GIELINORPHASE.draw();
			}
			else
			{
				rect.TimerReset();
			}

			if (m_P2Tendril == true)
			{
				STUNNEXT.draw();
				if (m_P2TransitionTimer->DeltaTime() <= 4.5f)
				{
					
					STUNPHASE.draw();
				}
				else
				{
					REDVIRUSPHASE.draw();
				}
			}
			else
			{
				m_P2TransitionTimer->Reset();
				redVir = false;
			}

			if (m_P2Tendril == true)
			{
				if (!redVir)
				{
					m_P2TransitionTimer->Update();

					if (m_P2TransitionTimer->DeltaTime() >= 4.6f)
					{
						redVir = true;
					}
				}

				if (redVir)
				{
					REDVIRUSPHASE.draw();
				}

			}

		}

		if (Screen.GetPhase() == 3)
		{

			m_Phase3LastFrame = true;

			if (m_Phase2LastFrame)
			{
				m_Phase2LastFrame = false;
				if (m_P2Tendril)
				{
					m_P3Gielinor = true;
				}

				if (m_P2Stun || m_P2Virus || m_P2Gielinor)
				{
					m_P3Virus = true;
				}
			}

			if (Screen.GetRAnima())
			{
				REDANIMA.draw();
			}

			if (Screen.getRVirus() || Screen.GetAnimaCleanse())
			{
				if (Screen.getRVirus())
				{
					REDVIRUS.draw();
				}
				m_P3Virus = true;
				m_P3Stun = false;
			}

			if (Screen.GetGielinor())
			{
				m_P3Gielinor = true;
				m_P3Virus = false;
			}

			if (Screen.GetHoldStill() || Screen.GetPhase1Start())
			{
				m_P3Stun = true;
				m_P3Gielinor = false;

			}

			if (m_P3Stun)
			{
				RVIRUSNEXT.draw();
				ANIMABOMBPHASE.draw();
			}

			if (m_P3Virus)
			{
				GIELINORNEXT.draw();
				STUNPHASE.draw();
			}

			if (m_P3Gielinor)
			{
				rect.Update();
				STUNNEXT.draw();
				GIELINORPHASE.draw();
			}
			else
			{
				rect.TimerReset();
			}





		}

		if (Screen.GetPhase() == 4)
		{
			m_Phase4LastFrame = true;

			if (m_Phase3LastFrame)
			{
				if (m_P3Stun)
				{
					m_P4Gielinor = true;
				}

				if (m_P3Virus)
				{
					m_P4Bomb = true;
				}

				if (m_P3Gielinor)
				{
					m_P4Gielinor = true;
				}

				m_Phase3LastFrame = false;
			}

			if (Screen.GetGielinor())
			{
				m_P4Gielinor = true;
				m_P4Stun = false;
			}

			if (Screen.GetABomb())
			{
				m_P4Bomb = true;
				m_P4Gielinor = false;
			}

			if (Screen.GetHoldStill())
			{
				m_P4Stun = true;
				m_P4Bomb = false;

			}

			if (m_P4Gielinor)
			{
				rect.Update();
				ABOMBNEXT.draw();
				P5PHASE.draw();
			}
			else
			{
				rect.TimerReset();
			}

			if (m_P4Bomb)
			{
				STUNNEXT.draw();
				P5PHASE.draw();
			}

			if (m_P4Stun)
			{
				GIELINORNEXT.draw();
				P5PHASE.draw();
			}



		}
		
		if (Screen.GetPhase() == 5)
		{
			m_Phase5LastFrame = true;

			if (Screen.getRVirus())
			{
				REDVIRUS.draw();
			}

			if (Screen.getGVirus())
			{
				GREENVIRUS.draw();
			}

			if (Screen.GetBVirus())
			{
				BLACKVIRUS.draw();
			}

			if (Screen.GetGAnima())
			{
				GREENANIMA.draw();
			}

			if (Screen.GetBAnima())
			{
				BLACKANIMA.draw();
			}


			if (Screen.GetRAnima())
			{
				REDANIMA.draw();
			}

		}

		rect.draw();
		window.pollEvents();
		window.clear();
		if (rect.GetTimerDelta() > 5.0f)
		{
			rect.TimerReset();
		}
	}

	

	/*
	if (!Initialize())
	{
		printf("Could not initialize!\n");
		return -1;
	}

	texture = LoadTexture("RedAnima.png");
	
	if (texture == NULL)
	{
		printf("Failed to load the image");
		//return -1;
	}

	bool exit = false;
	SDL_Event e;

	SDL_Rect screenRectangle = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect imageRectangle = { 0, 0, 100, 100 };

	

	//Uint32 bgColor = SDL_MapRGB(screen->format, 0, 0, 0);

	while (!exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				exit = true;
				break;
			default:
				break;
			}
		}

		SDL_RenderClear(renderer); //Clear renderer

		SDL_RenderCopy(renderer, texture, &screenRectangle, &imageRectangle);  //Add image to renderer

		SDL_RenderPresent(renderer); //Render it


		//SDL_FillRect(screen, NULL, bgColor);
		//SDL_UpdateWindowSurface(window);
	}

	Close();

	return 0;
	*/
	//std::getchar();

	return 0;
}

bool Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("My SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Erorr: %s\n", SDL_GetError());
		return false;
	}

	//screen = SDL_GetWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		printf("We were not able to create the renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) != imgFlags))
	{
		printf("SDL_image could not be initialised! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

void Close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	IMG_Quit();
	SDL_Quit();
	//Timer::Release();
	//mainTimer = NULL;
}

SDL_Texture* LoadTexture(std::string file)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface*loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load the image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create the texture from %s! SDL_Error: %s\n", file.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void PhaseOne()
{

}
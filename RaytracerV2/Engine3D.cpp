#include "pch.h"
#include "Engine3D.h"


bool Engine3D::m_isRunning = false;
int Engine3D::m_screenWidth = 0;
int Engine3D::m_screenHeight = 0;

SDL_Window* Engine3D::m_window = nullptr;
SDL_Texture* Engine3D::m_texture = nullptr;
SDL_Renderer* Engine3D::m_renderer = nullptr;
unsigned int* Engine3D::m_pixelData = nullptr;

void Engine3D::Initialize(int screenWidth, int screenHeight)
{
	Engine3D::m_screenWidth = screenWidth;
	Engine3D::m_screenHeight = screenHeight;

	Engine3D::m_pixelData = new unsigned int[Engine3D::m_screenWidth * Engine3D::m_screenHeight];

	Engine3D::m_isRunning = true;

	assert(!SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize: %s\n", SDL_GetError());
	Engine3D::m_window = SDL_CreateWindow(
		"RayTracerV2",
		SDL_WINDOWPOS_CENTERED_DISPLAY(1),
		SDL_WINDOWPOS_CENTERED_DISPLAY(1),
		Engine3D::m_screenWidth,
		Engine3D::m_screenHeight,
		SDL_WINDOW_ALLOW_HIGHDPI
	);

	assert(Engine3D::m_window, "Failed to create SDL window: %s\n", SDL_GetError());

	Engine3D::m_renderer = SDL_CreateRenderer(Engine3D::m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	assert(Engine3D::m_renderer, "Failed to create SDL renderer: %s\n", SDL_GetError());

	Engine3D::m_texture = SDL_CreateTexture(Engine3D::m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, Engine3D::m_screenWidth, Engine3D::m_screenHeight);
	assert(Engine3D::m_texture, "Failed to create SDL texture: %s\n", SDL_GetError());
}

void Engine3D::Run()
{
	Engine3D::Update();
	Engine3D::Render();
}

void Engine3D::Stop()
{
	Engine3D::m_isRunning = false;
	SDL_DestroyWindow(Engine3D::m_window);
	delete m_pixelData;
}

void Engine3D::HandleSDLEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Engine3D::Stop();
			break;
		}
	}
}

void Engine3D::Update()
{
	Engine3D::m_pixelData[(10 * Engine3D::m_screenWidth) + 5] = 0x0;

	SDL_UpdateTexture(Engine3D::m_texture, nullptr, Engine3D::m_pixelData, Engine3D::m_screenWidth * 4);
}

void Engine3D::Render()
{
	
	SDL_RenderCopyEx(Engine3D::m_renderer, Engine3D::m_texture, nullptr, nullptr, 0.0, nullptr, SDL_FLIP_NONE);
	SDL_RenderPresent(Engine3D::m_renderer);
}

#pragma once

class Engine3D
{
private:
	Engine3D();
	~Engine3D() = default;

public:
	static void Initialize(int, int);
	static void Run();
	static void Stop();

	static void HandleSDLEvents();
public:
	static bool IsRunning() { return m_isRunning; };

private:
	static void Update();
	static void Render();

private:
	static bool m_isRunning;
	static int m_screenWidth;
	static int m_screenHeight;

	static SDL_Window* m_window;
	static SDL_Texture* m_texture;
	static SDL_Renderer* m_renderer;
	static unsigned int* m_pixelData;
};
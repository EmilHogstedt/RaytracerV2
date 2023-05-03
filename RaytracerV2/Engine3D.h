#pragma once

static class Engine3D
{
public:
	Engine3D() : m_isRunning{ true }{}
	~Engine3D() = default;

public:
	void Initialize();
	void Run();
	void Stop();

public:
	bool IsRunning() { return m_isRunning; };

private:
	void Update();
	void Render();

private:
	bool m_isRunning;
};
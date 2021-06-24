#pragma once
#include "public/glfw_win64.h"
#include "public/stl.h"

class glfw_window
{
	using MonitorMode = std::pair<GLFWmonitor*, const GLFWvidmode*>;

public:

	void load_context();

	void tick(float DeltaTime);

public:
	void show();

	void hide();
	
	void maximize();
	
	void minimize();
	
	void restore();
	
	void switch_windowed(int UpperLeftX, int UpperLeftY, int Width, int Height);
	
	void SwitchFullScreen();
	
	virtual bool IsFullScreen();

	std::uint32_t get_framebuffer_width() { return _framebuffer_width; }

	std::uint32_t get_framebuffer_height() { return _framebuffer_height; }

public:

	std::pair<size_t, size_t> GetPrimaryMonitorPhysicalSize();

private:

	void set_callback();

	void set_input_mode();

	std::int32_t _framebuffer_width, _framebuffer_height;


	MonitorMode PrimaryMonitorMode;

	std::vector<MonitorMode> OtherMonitorModes;

	bool is_full_screen;

	GLFWwindow* _window;

	std::string _title;

	std::uint32_t _windowed_width, _windowed_height;

};

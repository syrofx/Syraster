#pragma once

#include <SDL3/SDL.h>
#include <string_view>

namespace sfr 
{
	class Application
	{
	public:
		Application(const std::string_view& title, std::size_t width, std::size_t height);
		~Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		Application(Application&&) = default;
		Application& operator=(Application&&) = default;

		void run();

	protected:
		void update();
		void render();
		void handleEvents();

	private:
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		std::string_view mTitle;
		std::size_t mWidth;
		std::size_t mHeight;
		bool mQuit;
	};
};
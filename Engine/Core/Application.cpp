#include "Application.h"
#include <stdexcept>

using namespace sfr;

Application::Application(const std::string_view& title, std::size_t width, std::size_t height) : 
	mWindow{nullptr},
	mRenderer{nullptr},
	mWidth{width},
	mHeight{height},
    mQuit{false},
    mTitle{ title } {
    SDL_SetAppMetadata("Syraster", "1.0", "com.syraster.engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer(mTitle.data(), mWidth, mHeight, 0, &mWindow, &mRenderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
}

Application::~Application() {
    if (mRenderer) SDL_DestroyRenderer(mRenderer);
    if (mWindow) SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void sfr::Application::run() {
    while (!mQuit) {
        handleEvents();
        update();
    }
}

void sfr::Application::update() {
    const double now = ((double)SDL_GetTicks()) / 1000.0;
    const float red = (float)(0.5 + 0.5 * SDL_sin(now));
    const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(mRenderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void sfr::Application::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            mQuit = true;
        }
    }
}

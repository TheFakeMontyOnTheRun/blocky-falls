#include <set>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "Vipper/Vipper.h"
#include "CSDLRenderer.h"

#include "Modules/Gameplay/Gameplay.h"
#include "Modules/TitleScreen/TitleScreen.h"

std::shared_ptr<Vipper::IRouter> nextRouter;
std::shared_ptr<Vipper::IPresenter> presenter;
std::shared_ptr<Vipper::IRouter> router;
std::vector<std::shared_ptr<Vipper::IRouter>> routers;
std::shared_ptr<BlockyFalls::CSDLRenderer> renderer;

void tick() {

	if (nextRouter != nullptr) {
		if (router != nullptr) {
			router->onRelinquishFocus();
			if (!router->isFinished()) {
				routers.push_back(router);
			}

		}
		router = nextRouter;
		router->onFocus();
		nextRouter = nullptr;
	}

	presenter = router->getPresenter();
	presenter->present();

	renderer->update();
	renderer->render();

	nextRouter = router->route();

	if (router->isFinished() && nextRouter == nullptr) {

		nextRouter = routers.back();
		routers.pop_back();
	}

	if (nextRouter == router) {
		renderer->shutdown();
		exit(0);
	}
}

int main(int argc, char **argv) {

	renderer = std::make_shared<BlockyFalls::CSDLRenderer>();

	auto titleScreenRouter = std::make_shared<BlockyFalls::CTitleScreenRouter>(renderer);

	titleScreenRouter->initWithDefaults();

	nextRouter = titleScreenRouter;
	presenter = titleScreenRouter->getPresenter();

#ifdef __EMSCRIPTEN__
	  emscripten_set_main_loop( tick, 30, 1 );
#else
	while (true) {
		tick();
		SDL_Delay(33);
	}
#endif

	renderer->shutdown();
	return 0;
}

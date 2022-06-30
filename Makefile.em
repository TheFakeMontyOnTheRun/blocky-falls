CC = emcc
CXX = em++

LDFLAGS =  -O3 -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_SDL=1 --preload-file res  --use-preload-plugins -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 --shell-file ./minimal.html

CXXFLAGS=-g -c -O3 \
             -Iinclude        \
	$(SDL_INCLUDE)                                       \
	-fomit-frame-pointer                                 \
	-fno-exceptions                                      \
	-ffast-math

MENU_TARGET=index.html

MENU_OBJ = SDLVersion/main.o SDLVersion/CSDLRenderer.o src/Modules/TitleScreen/Interactor/CTitleScreenInteractor.o \
src/Modules/TitleScreen/Presenter/CTitleScreenPresenter.o src/Modules/TitleScreen/Router/CTitleScreenRouter.o \
src/Modules/TitleScreen/View/CRect.o src/Modules/TitleScreen/View/CPlayButton.o \
src/Modules/TitleScreen/View/CTitleScreenView.o src/Vipper/IRenderer.o src/Vipper/IEntity.o src/Vipper/IView.o \
src/Vipper/IInteractor.o src/Vipper/IPresenter.o src/Vipper/IRouter.o src/Vipper/CLerp.o  \
src/Vipper/CAnimation.o src/Modules/Gameplay/Entities/CColumn.o src/Modules/Gameplay/Entities/CLevel.o \
src/Modules/Gameplay/Entities/CGameSession.o src/Modules/Gameplay/Presenter/CGameplayPresenter.o \
src/Modules/Gameplay/Presenter/CLevelPresenter.o src/Modules/Gameplay/Router/CGameplayRouter.o \
src/Modules/Gameplay/View/CGameplayView.o src/Modules/Gameplay/View/CBlockAnimationHelper.o \
src/Modules/Gameplay/Interactor/CGameplayInteractor.o \
src/Modules/HighScoresScreen/View/CHighScoresScreenView.o \
src/Modules/HighScoresScreen/Interactor/CHighScoresScreenInteractor.o \
src/Modules/HighScoresScreen/Presenter/CHighScoresScreenPresenter.o \
src/Modules/HighScoresScreen/Router/CHighScoresScreenRouter.o \


$(MENU_TARGET):	$(MENU_OBJ)
	$(CXX) -o$(MENU_TARGET) $(MENU_OBJ) $(LDFLAGS)

all:   $(MENU_TARGET)

serve: $(MENU_TARGET)
	python3 -m http.server

clean:
	rm -f game.html game.wasm game.data game.js game.html.mem
	rm -f $(MENU_OBJ)

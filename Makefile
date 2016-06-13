CXX = clang++

SDL_LIB = -L/usr/lib -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
SDL_INCLUDE = -I/usr/local/include `sdl-config --cflags --libs`

CXXFLAGS = -std=c++0x -O2 -g -Wall -fno-exceptions -Weffc++ $(SDL_INCLUDE) -Iinclude 
OBJS = SDLVersion/main.o SDLVersion/CSDLRenderer.o src/Modules/TitleScreen/Interactor/CTitleScreenInteractor.o \
src/Modules/TitleScreen/Presenter/CTitleScreenPresenter.o src/Modules/TitleScreen/Router/CTitleScreenRouter.o \
src/Modules/TitleScreen/View/CRect.o src/Modules/TitleScreen/View/CPlayButton.o \
src/Modules/TitleScreen/View/CTitleScreenView.o src/Vipper/IRenderer.o src/Vipper/IEntity.o src/Vipper/IView.o \
src/Vipper/IInteractor.o src/Vipper/IPresenter.o src/Vipper/IRouter.o src/Vipper/CLerp.o  \
src/Vipper/CAnimation.o src/Modules/Gameplay/Entities/CColumn.o src/Modules/Gameplay/Entities/CLevel.o \
src/Modules/Gameplay/Entities/CGameSession.o src/Modules/Gameplay/Presenter/CGameplayPresenter.o \
src/Modules/Gameplay/Presenter/CLevelPresenter.o src/Modules/Gameplay/Router/CGameplayRouter.o \
src/Modules/Gameplay/View/CGameplayView.o src/Modules/Gameplay/View/CBlockAnimationHelper.o \
src/Modules/Gameplay/Interactor/CGameplayInteractor.o
LIBS = $(SDL_LIB)
TARGET = blockyfalls

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:   $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

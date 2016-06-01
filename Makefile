CXX = clang++

SDL_LIB = -L/usr/lib -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer
SDL_INCLUDE = -I/usr/local/include `sdl-config --cflags --libs`

CXXFLAGS = -std=c++0x -O2 -g -Wall -fno-exceptions -fno-rtti -Bstatic -Weffc++ -fmessage-length=0 $(SDL_INCLUDE) -Iinclude -DSDL
OBJS = src/CActor.o src/CGame.o src/CLevel.o src/IMapElement.o src/Vec2i.o SDLVersion/main.o SDLVersion/CSDLRelativeRenderer.o
LIBS = $(SDL_LIB)
TARGET = wizard

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:   $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

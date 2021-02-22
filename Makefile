.PHONY: all debug release

all: debug release

EXE = zyfara.exe
SRC = src/*.cpp src/Vendor/imgui/*.cpp src/Vendor/FastNoise/*.cpp
CXXFLAGS = -Wall -Wextra -std=c++17 
SFMLFLAGS = -DSFML_STATIC -Ilib/SFML/include -Llib/SFML/lib
SFMLLIBS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype

debug: CXXFLAGS += -DDEBUG -g
debug: $(EXE)

release: CXXFLAGS += -mwindows -Ofast
release: $(EXE)

all: $(EXE)

$(EXE):
	$(CXX) $(CXXFLAGS) $(SRC) $(SFMLFLAGS) $(SFMLLIBS) -o $(EXE)

TARGET = 4opeenrij
SDL2LIBS = sdl2-config --libs
SDL2FLAGS =  sdl2-config --cflags
SDL2TTF = -lSDL2_ttf
SDL2MIXER = -lSDL2_mixer

all: spelbord.o spellus.o GUI.o
	gcc spelbord.o spellus.o GUI.o -o $(TARGET) $(SDL2LIBS) $(SDL2TTF) $(SDL2MIXER)
	make clean
	./$(TARGET) $(WIDTH) $(HEIGHT)
spellus.o: spellus.c GUI.h spelbord.h
	gcc spellus.c -c -o spellus.o $(SDL2FLAGS)

GUI.o: GUI.c GUI.h spelbord.h
	gcc GUI.c -c -o GUI.o $(SDL2FLAGS)

spelbord.o: spelbord.c spelbord.h
	gcc spelbord.c -c -o spelbord.o

clean:
	$(RM) *.o

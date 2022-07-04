CC = cc
CFLAGS = -g -Wall -W -pedantic -ansi -std=c99 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
TARGET = FlappyBird
OBJS = main.o game.o video.o background.o pipe.o score.o bird.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm $(OBJS) $(TARGET)

main.o: main.c game.h
game.o: game.c game.h video.h background.h pipe.h score.h bird.h
video.o: video.c video.h
background.o: background.c background.h object.h physics.h
pipe.o: pipe.c pipe.h object.h physics.h
score.o: score.c score.h object.h physics.h
bird.o: bird.c bird.h object.h physics.h

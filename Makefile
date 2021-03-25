CC := gcc
CFLAGS := `sdl-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL_image -lm
HDRS :=
SRCS := src/main.c src/game.c src/graphics.c src/logic.c
OBJS := $(SRCS:.c=.o)

EXEC := 2048.dge

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)


clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean

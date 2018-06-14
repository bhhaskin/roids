CXX=g++ -std=c++11
CFLAGS=
LDFLAGS=-L/usr/lib `pkg-config --libs allegro-5 allegro_dialog-5 allegro_image-5 allegro_primitives-5`
INCLUDE=-Isrc/. -I/usr/include/allegro5

OBJS=./src/util/SimpleLogger/simplog.o ./src/main.o
OUT=bin/game

all: game_rule

clean:
	rm -rf *.o bin/game

game_rule: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
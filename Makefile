CC=g++
DEFAULT_CFLAGS:=-std=c++11 -g -Wall -Wextra -pedantic
CFLAGS?=
CFLAGS += $(DEFAULT_CFLAGS)
OBJECTS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
OUT=bot

all: bot

bot: $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUT)

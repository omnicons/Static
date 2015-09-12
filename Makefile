CC=g++
DEFAULT_CFLAGS:=-I include/ -std=c++11 -g -Wall -Wextra -pedantic
CFLAGS?=
CFLAGS += $(DEFAULT_CFLAGS)
SDIR=src
IDIR=include
ODIR=obj
OBJECTS=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp))
OUT=bot

all: bot

bot: $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUT)

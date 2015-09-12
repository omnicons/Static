CC=g++
SDIR=src
IDIR=include
ODIR=obj
OUT=bot

DEFAULT_CFLAGS:=-I $(IDIR)/ -std=c++11 -g -Wall -Wextra -pedantic
CFLAGS?=
CFLAGS += $(DEFAULT_CFLAGS)
OBJECTS=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp))

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUT)

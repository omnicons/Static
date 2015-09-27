CC=g++
SDIR=src
IDIR=include
ODIR=obj
OUT=bot
MDIR=modules/src
MIDIR=modules/include
MOBJDIR=modules/obj

DEFAULT_CFLAGS:=-I $(IDIR)/ -I $(MIDIR)/ -std=c++11 -g -Wall -Wextra -pedantic
CFLAGS?=
CFLAGS += $(DEFAULT_CFLAGS)
OBJECTS=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp)) $(patsubst $(MDIR)/%.cpp,$(MOBJDIR)/%.o,$(wildcard $(MDIR)/*.cpp))

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(MOBJDIR)/%.o: $(MDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUT)

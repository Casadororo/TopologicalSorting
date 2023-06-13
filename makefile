CC = g++
TARGET = toposort
CPPFLAGS = `pkg-config libgvc --cflags` -Wall -g
LDLIBS = `pkg-config libgvc --libs`

# diretorios fonte
VPATH = src
objs = main.o

.PHONY: all clean purge

all: $(TARGET)

# ligacao
$(TARGET): $(objs)
	$(CC) $(objs) $(CPPFLAGS) $(LDLIBS) -o $(TARGET)

# compilacao
main.o:
# main.old.o: connection.h githyanki.h common.h


# limpeza
clean:
	-rm -f $(objs) *~
purge: clean
	-rm -f $(TARGET)
clean_images:
	-rm -f test/*.png

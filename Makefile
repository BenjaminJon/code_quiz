CC = g++
CFLAGS = -Wall
MODHEADER = bjb.h
MODSOURCE = main.cc bjb.cc
OBJFILES = main.o bjb.o
TARGET = bjbCodeTest

all: $(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

$(OBJFILES): $(MODSOURCE) $(MODHEADER)
	$(CC) $(CFLAGS) -c $(MODSOURCE)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

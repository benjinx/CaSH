CFLAGS  += -g -Wall -std=c11
LDFLAGS +=
LDLIBS  += -lreadline

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
TARGET  = CaSH

.PHONY: all
.DEFAULT: all
all: $(TARGET)

.PHONY: clean
clean:
		rm $(TARGET) *.o *.d

.PHONY: run
run:
		$(abspath $(TARGET))

.PHONY: gdb
gdb:
		gdb --args $(abspath $(TARGET))

.PHONY: valgrind
valgrind:
		valgrind $(abspath $(TARGET))

%.o: %.c
%.o: %.c %.d
		$(CC) $(CFLAGS) -MM -MP -MT $@ -o $*.d $<
		$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.d: ;
.PRECIOUS: %.d
-include $(patsubst %.c, %.d, $(SOURCES))
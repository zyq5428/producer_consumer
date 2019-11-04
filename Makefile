CC = gcc
CFLAGS = -g -lpthread

INCLUDES = $(wildcard ./*.h)
SOURCES = $(wildcard ./*.c)
INCLUDE_DIRS = -I./

TARGET = pro_con
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)

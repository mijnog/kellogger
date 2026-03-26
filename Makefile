CC = gcc
CFLAGS = -Wall -g

TARGET = kellogger
SRCS = kellogger.c keycodes.c find-keyboard.c daemonize.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

# make
# make clean (deletes the binary)

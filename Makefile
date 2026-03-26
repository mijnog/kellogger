CC = gcc
CFLAGS = -Wall -g

TARGET = kelogger
SRCS = kelogger.c keycodes.c daemonize.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

# make
# make clean (deletes the binary)

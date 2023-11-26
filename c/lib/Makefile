CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = ../mkkkkks.a
OBJS   = safe_alloc.o quick_text.o quick_loader.o \
	advanced_m3u.o

all: $(TARGET)
	ar r $(TARGET) $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)


%.o: %.c
	$(CC) -c $@ $< $(CFLAGS)

.PHONY: clean

CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include -I../lib
LDFLAGS       = -L/usr/local/lib
AR            = ar

TARGET = test_alloc.exe test_loader.exe test_text.exe \
	test_m3u.exe

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o

%.exe: %.o ../mkkkkks.a
	$(CC) -o $@ $(LDFLAGS) -L.. $< -l:mkkkkks.a

%.o: %.c
	$(CC) -c $@ $< $(CFLAGS)

.PHONY: clean

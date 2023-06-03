CC = x86_64-w64-mingw32-gcc
RC = x86_64-w64-mingw32-windres
CFLAGS = -mwindows
LDFLAGS = -lshlwapi

all: main.exe

main.exe: main.o resources.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

resources.o: resources.rc
	$(RC) -o $@ $<

clean:
	rm -f main.o resources.o main.exe
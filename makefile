CFLAGS=-g

all: todo todo64.exe todo32.exe

todo: todo.c platform_unix.o
	gcc -DPLATFORM='"platform_unix.h"' -o todo todo.c $(CFLAGS)

platform_unix.o: platform_unix.c platform_unix.h
	gcc -c platform_unix.c

todo64.exe: todo.c platform_windows64.o
	x86_64-w64-mingw32-gcc -DPLATFORM='"platform_windows.h"' -o todo64.exe todo.c $(CFLAGS)

platform_windows64.o: platform_windows.c platform_windows.h
	x86_64-w64-mingw32-gcc -c platform_windows.c

todo32.exe: todo.c platform_windows32.o
	i686-w64-mingw32-gcc -DPLATFORM='"platform_windows.h"' -o todo32.exe todo.c $(CFLAGS)

platform_windows32.o: platform_windows.c platform_windows.h
	i686-w64-mingw32-gcc -c platform_windows.c

clean: rm *.o

CFLAGS = -O0 -g
WFLAGS = -DPLATFORM='"platform_windows.h"'
LFLAGS = -DPLATFORM='"platform_unix.h"'

CCL = gcc
CCW32 = i686-w64-mingw32-gcc
CCW64 = x86_64-w64-mingw32-gcc

PREFL = linux_
PREFW32 = w32_
PREFW64 = w64_

SRCDIR = .
OBJDIR = $(SRCDIR)/obj
BINDIR = ../bin

_DEPS = platform_unix.h platform_windows.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS = todo.o platform_unix.o platform_windows.o
OBJSL = $(patsubst %,$(OBJDIR)/$(PREFL)%,$(_OBJS))
OBJSW32 = $(patsubst %,$(OBJDIR)/$(PREFW32)%,$(_OBJS))
OBJSW64 = $(patsubst %,$(OBJDIR)/$(PREFW64)%,$(_OBJS))

all: linux win32 win64

linux: $(OBJSL)
	$(CC) -o todo $^ $(CFLAGS) $(LFLAGS)

win32: $(OBJSW32)
	$(CCW32) -o todo32.exe $^ $(CFLAGS) $(WFLAGS)

win64: $(OBJSW64)
	$(CCW64) -o todo64.exe $^ $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFL)%.o: $(SRCDIR)/%.c $(DEPS)
	$(CCL) -c -o $@ $< $(CFLAGS) $(LFLAGS)

$(OBJDIR)/$(PREFW32)%.o: $(SRCDIR)/%.c $(DEPS)
	$(CCW32) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFW64)%.o: $(SRCDIR)/%.c $(DEPS)
	$(CCW64) -c -o $@ $< $(CFLAGS) $(WFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o

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

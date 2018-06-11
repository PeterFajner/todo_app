CFLAGS = -O3 -g -std=c99 -Wall -Wextra -Wpedantic
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


_DEPSL = platform_unix.h
_DEPSW = platform_windows.h
DEPSL = $(patsubst %,$(SRCDIR)/%,$(_DEPSL))
DEPSW = $(patsubst %,$(SRCDIR)/%,$(_DEPSW))

_OBJS = todo.o
_OBJSL = platform_unix.o
_OBJSW = platform_windows.o
OBJSL = $(patsubst %,$(OBJDIR)/$(PREFL)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFL)%,$(_OBJSL))
OBJSW32 = $(patsubst %,$(OBJDIR)/$(PREFW32)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFW32)%,$(_OBJSW))
OBJSW64 = $(patsubst %,$(OBJDIR)/$(PREFW64)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFW64)%,$(_OBJSW))

all: linux win32 win64

linux: $(OBJSL)
	$(CCL) -o $(BINDIR)/todo $^ $(CFLAGS) $(LFLAGS)
	
test: $(OBJSL)
	$(CCL) -o $(BINDIR)/todo $^ -Og -g -std=c99 -Wall -Wextra -Wpedantic $(LFLAGS)

win32: $(OBJSW32)
	$(CCW32) -o $(BINDIR)/todo32.exe $^ $(CFLAGS) $(WFLAGS)

win64: $(OBJSW64)
	$(CCW64) -o $(BINDIR)/todo64.exe $^ $(CFLAGS) $(WFLAGS)


$(OBJDIR)/$(PREFW64)todo.o: $(SRCDIR)/todo.c
	$(CCW64) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFW32)todo.o: $(SRCDIR)/todo.c
	$(CCW32) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFL)todo.o: $(SRCDIR)/todo.c
	$(CCL) -c -o $@ $< $(CFLAGS) $(LFLAGS)

$(OBJDIR)/$(PREFL)%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CCL) -c -o $@ $< $(CFLAGS) $(LFLAGS)

$(OBJDIR)/$(PREFW32)%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CCW32) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFW64)%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CCW64) -c -o $@ $< $(CFLAGS) $(WFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o

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

_OBJS = todo.o
_OBJSL = platform_unix.o
_OBJSW = platform_windows.o
OBJSL = $(patsubst %,$(OBJDIR)/$(PREFL)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFL)%,$(_OBJSL))
OBJSW32 = $(patsubst %,$(OBJDIR)/$(PREFW32)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFW32)%,$(_OBJSW))
OBJSW64 = $(patsubst %,$(OBJDIR)/$(PREFW64)%,$(_OBJS)) $(patsubst %,$(OBJDIR)/$(PREFW64)%,$(_OBJSW))

all: linux win32 win64

linux: $(OBJSL)
	$(CCL) -o $(BINDIR)/todo $^ $(CFLAGS) $(LFLAGS)

win32: $(OBJSW32)
	$(CCW32) -o $(BINDIR)/todo32.exe $^ $(CFLAGS) $(WFLAGS)

win64: $(OBJSW64)
	$(CCW64) -o $(BINDIR)/todo64.exe $^ $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFL)%.o: $(SRCDIR)/%.c $(SRCDIR)/linux/%.c $(SRCDIR)/%.h $(SRCDIR)/linux/%.h
	$(CCL) -c -o $@ $< $(CFLAGS) $(LFLAGS)

$(OBJDIR)/$(PREFW32)%.o: $(SRCDIR)/%.c $(SRCDIR)/windows/%.c $(SRCDIR)/%.h $(SRCDIR)/windows/%.h
	$(CCW32) -c -o $@ $< $(CFLAGS) $(WFLAGS)

$(OBJDIR)/$(PREFW64)%.o: $(SRCDIR)/%.c $(SRCDIR)/windows/%.c $(SRCDIR)/%.h $(SRCDIR)/windows/%.h
	$(CCW64) -c -o $@ $< $(CFLAGS) $(WFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o

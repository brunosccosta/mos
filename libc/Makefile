include ../make.directories
include ../make.cc.config

OBJS:=\
string/string.o \
stdlib/stdlib.o \

BINARIES=libk.a

all: $(BINARIES)

.PHONY: all clean install install-headers install-libs

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(BINARIES) $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o

install: install-libs

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

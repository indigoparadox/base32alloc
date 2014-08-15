
LIBS = base32alloc.so
SLIBS = $(patsubst %.so,%.a,$(LIBS))

CFLAGS += -DBSTRING
LDFLAGS += -lbstrlib

all: dynamic static

dynamic: $(LIBS)

static: $(SLIBS)

c-test: $(SLIBS)
	gcc -o ctest -static ctest.c -L. -lbase32alloc

b-test: $(SLIBS)
	gcc -o btest -static btest.c -L. -lbase32alloc -lbstrlib

vala-test: $(SLIBS)
	valac -C --vapidir=. --pkg base32alloc --Xcc -I. vtest.vala
	valac --vapidir=. --pkg base32alloc --Xcc -I. --Xcc -L. --Xcc -lbase32alloc vtest.vala
	#gcc -o test vtest.c -L. -lbase32

clean:
	rm *.so ; rm *.a ; rm *.o ; rm *test ; rm vtest.c

%.dynamic.o: %.c
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

%.static.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.so: %.dynamic.o
	$(CC) $(LDFLAGS) -shared -Wl,-soname,lib$@ -o lib$@ $<

%.a: %.static.o
	$(AR) rcs lib$@ $<



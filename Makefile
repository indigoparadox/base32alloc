
LIBS = base32.so

all: dynamic static

dynamic: $(LIBS)

static: $(patsubst %.so,%.a,$(LIBS))

c-test: base32.a
	gcc -o ctest -static ctest.c -L. -lbase32

vala-test: base32.a
	valac -C --vapidir=. --pkg base32 --Xcc -I. --Xcc -L. --Xcc -lbase32 vtest.vala
	valac --vapidir=. --pkg base32 --Xcc -I. --Xcc -L. --Xcc -lbase32 vtest.vala
	#gcc -o test vtest.c -L. -lbase32

clean:
	rm *.so ; rm *.a ; rm *.o ; rm *test ; rm vtest.c

%.dynamic.o: %.c
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

%.static.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.so: %.dynamic.o
	$(CC) -shared -Wl,-soname,lib$@ -o lib$@ $<

%.a: %.static.o
	$(AR) rcs lib$@ $<



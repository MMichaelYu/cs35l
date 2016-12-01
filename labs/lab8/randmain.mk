randmain: randcpuid.o randmain.o
	gcc $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randcpuid.o randmain.o

randlibhw.so: randlibhw.c
	gcc $(CFLAGS) randlibhw.c -fPIC -shared -o randlibhw.so

randlibsw.so: randlibsw.c
	gcc $(CFLAGS) randlibsw.c -fPIC -shared -o randlibsw.so

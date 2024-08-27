CC=g++

CFLAGS=-w -g -fcommon -fpermissive -no-pie
LFLAGS=-lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
LPATHS=-I/usr/include/GL -I/usr/include/GLFW -I/usr/include/glad -L/usr/lib64

SRCDIR=src
LIBDIR=lib
BINDIR=bin
SHDDIR=shd
TEXDIR=tex

OBJO=$(SRCDIR)/main.o $(LIBDIR)/glad.o $(LIBDIR)/stb_image.o $(SRCDIR)/windowdef.o $(SRCDIR)/shader.o $(SRCDIR)/mesh.o

TARGET=$(BINDIR)/wawacraft_evolved.elf

wawacraft_evolved: glad stb_image windowdef shader mesh main
	cp -r $(SHDDIR) $(BINDIR)
	cp -r $(TEXDIR) $(BINDIR)
	$(CC) $(OBJO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

main: $(SRCDIR)/main.cpp
	$(CC) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o $(CFLAGS) $(LFLAGS) -c

windowdef: $(SRCDIR)/windowdef.h $(SRCDIR)/windowdef.cpp
	$(CC) $(SRCDIR)/windowdef.cpp -o $(SRCDIR)/windowdef.o $(CFLAGS) $(LFLAGS) -c

shader: $(SRCDIR)/shader.h $(SRCDIR)/shader.cpp
	$(CC) $(SRCDIR)/shader.cpp -o $(SRCDIR)/shader.o $(CFLAGS) $(LFLAGS) -c

mesh: $(SRCDIR)/mesh.h $(SRCDIR)/mesh.cpp
	$(CC) $(SRCDIR)/mesh.cpp -o $(SRCDIR)/mesh.o $(CFLAGS) $(LFLAGS) -c

glad: $(LIBDIR)/glad.c
	$(CC) $(LIBDIR)/glad.c -o $(LIBDIR)/glad.o $(CFLAGS) $(LFLAGS) -c

stb_image: $(LIBDIR)/stb_image.h $(LIBDIR)/stb_image.cpp
	$(CC) $(LIBDIR)/stb_image.cpp -o $(LIBDIR)/stb_image.o $(CFLAGS) $(LFLAGS) -c

CC=g++

CFLAGS=-w -g -fcommon -fpermissive -no-pie
LFLAGS=-lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
LPATHS=-I/usr/include/GL -I/usr/include/GLFW -I/usr/include/glad -L/usr/lib64

SRCDIR=src
LIBDIR=lib
BINDIR=bin
SHDDIR=shd
TEXDIR=tex

LIBO=$(LIBDIR)/*.o
SRCO=$(SRCDIR)/*.o

TARGET=$(BINDIR)/wawacraft_evolved.elf

wawacraft_evolved: glad stb_image projection windowdef shader textures mesh object control main
	cp -r $(SHDDIR) $(BINDIR)
	cp -r $(TEXDIR) $(BINDIR)
	$(CC) $(LIBO) $(SRCO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

main: $(SRCDIR)/main.cpp
	$(CC) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o $(CFLAGS) $(LFLAGS) -c

windowdef: $(SRCDIR)/windowdef.h $(SRCDIR)/windowdef.cpp
	$(CC) $(SRCDIR)/windowdef.cpp -o $(SRCDIR)/windowdef.o $(CFLAGS) $(LFLAGS) -c

shader: $(SRCDIR)/shader.h $(SRCDIR)/shader.cpp
	$(CC) $(SRCDIR)/shader.cpp -o $(SRCDIR)/shader.o $(CFLAGS) $(LFLAGS) -c

mesh: $(SRCDIR)/mesh.h $(SRCDIR)/mesh.cpp
	$(CC) $(SRCDIR)/mesh.cpp -o $(SRCDIR)/mesh.o $(CFLAGS) $(LFLAGS) -c

textures: $(SRCDIR)/textures.h $(SRCDIR)/textures.cpp
	$(CC) $(SRCDIR)/textures.cpp -o $(SRCDIR)/textures.o $(CFLAGS) $(LFLAGS) -c

projection: $(SRCDIR)/projection.h $(SRCDIR)/projection.cpp
	$(CC) $(SRCDIR)/projection.cpp -o $(SRCDIR)/projection.o $(CFLAGS) $(LFLAGS) -c

object: $(SRCDIR)/object.h $(SRCDIR)/object.cpp
	$(CC) $(SRCDIR)/object.cpp -o $(SRCDIR)/object.o $(CFLAGS) $(LFLAGS) -c

control: $(SRCDIR)/control.h $(SRCDIR)/control.cpp
	$(CC) $(SRCDIR)/control.cpp -o $(SRCDIR)/control.o $(CFLAGS) $(LFLAGS) -c

glad: $(LIBDIR)/glad.c
	$(CC) $(LIBDIR)/glad.c -o $(LIBDIR)/glad.o $(CFLAGS) $(LFLAGS) -c

stb_image: $(LIBDIR)/stb_image.h $(LIBDIR)/stb_image.cpp
	$(CC) $(LIBDIR)/stb_image.cpp -o $(LIBDIR)/stb_image.o $(CFLAGS) $(LFLAGS) -c

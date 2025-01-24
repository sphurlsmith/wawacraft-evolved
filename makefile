CC=g++

CFLAGS=-w -g -fcommon -fpermissive -no-pie
LFLAGS=-lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
LPATHS=-I/usr/include/GL -I/usr/include/GLFW -I/usr/include/glad -L/usr/lib64

SRCDIR=src
LIBDIR=lib
BINDIR=bin
SHDDIR=shd
TEXDIR=tex

BINO=$(BINDIR)/*.o

TARGET=$(BINDIR)/wawacraft_evolved

wawacraft_evolved: glad stb_image mathlib windef control textures shader mesh render voxel main
	cp -r $(SHDDIR) $(BINDIR)
	cp -r $(TEXDIR) $(BINDIR)
	$(CC) $(BINO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

main: $(SRCDIR)/main.cpp
	$(CC) $(SRCDIR)/main.cpp -o $(BINDIR)/main.o $(CFLAGS) $(LFLAGS) -c

# source

windef: $(SRCDIR)/windef.cpp $(SRCDIR)/windef.h
	$(CC) $(SRCDIR)/windef.cpp -o $(BINDIR)/windef.o $(CFLAGS) $(LFLAGS) -c

render: $(SRCDIR)/render.cpp $(SRCDIR)/render.h
	$(CC) $(SRCDIR)/render.cpp -o $(BINDIR)/render.o $(CFLAGS) $(LFLAGS) -c

shader: $(SRCDIR)/shader.cpp $(SRCDIR)/shader.h
	$(CC) $(SRCDIR)/shader.cpp -o $(BINDIR)/shader.o $(CFLAGS) $(LFLAGS) -c

mesh: $(SRCDIR)/mesh.cpp $(SRCDIR)/mesh.h
	$(CC) $(SRCDIR)/mesh.cpp -o $(BINDIR)/mesh.o $(CFLAGS) $(LFLAGS) -c

textures: $(SRCDIR)/textures.cpp $(SRCDIR)/textures.h
	$(CC) $(SRCDIR)/textures.cpp -o $(BINDIR)/textures.o $(CFLAGS) $(LFLAGS) -c

control: $(SRCDIR)/control.cpp $(SRCDIR)/control.h
	$(CC) $(SRCDIR)/control.cpp -o $(BINDIR)/control.o $(CFLAGS) $(LFLAGS) -c

mathlib: $(SRCDIR)/mathlib.cpp $(SRCDIR)/mathlib.h
	$(CC) $(SRCDIR)/mathlib.cpp -o $(BINDIR)/mathlib.o $(CFLAGS) $(LFLAGS) -c

voxel: $(SRCDIR)/voxel.cpp $(SRCDIR)/voxel.h
	$(CC) $(SRCDIR)/voxel.cpp -o $(BINDIR)/voxel.o $(CFLAGS) $(LFLAGS) -c

# libraries

glad: $(LIBDIR)/glad.c
	$(CC) $(LIBDIR)/glad.c -o $(BINDIR)/glad.o $(CFLAGS) $(LFLAGS) -c

stb_image: $(LIBDIR)/stb_image.h $(LIBDIR)/stb_image.cpp
	$(CC) $(LIBDIR)/stb_image.cpp -o $(BINDIR)/stb_image.o $(CFLAGS) $(LFLAGS) -c

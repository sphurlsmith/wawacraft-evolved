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

TARGET=$(BINDIR)/wawacraft_evolved

wawacraft_evolved: glad stb_image main
	cp -r $(SHDDIR) $(BINDIR)
	cp -r $(TEXDIR) $(BINDIR)
	$(CC) $(LIBO) $(SRCO) -o $(TARGET) $(CFLAGS) $(LFLAGS)

main: $(SRCDIR)/main.cpp
	$(CC) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o $(CFLAGS) $(LFLAGS) -c

glad: $(LIBDIR)/glad.cI
	$(CC) $(LIBDIR)/glad.c -o $(LIBDIR)/glad.o $(CFLAGS) $(LFLAGS) -c

stb_image: $(LIBDIR)/stb_image.h $(LIBDIR)/stb_image.cpp
	$(CC) $(LIBDIR)/stb_image.cpp -o $(LIBDIR)/stb_image.o $(CFLAGS) $(LFLAGS) -c

CC=g++

CFLAGS=-w -g -fcommon -fpermissive -no-pie
LFLAGS=-lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl
LPATHS=-I/usr/include/GL -I/usr/include/GLFW -I/usr/include/glad -L/usr/lib64

SRCDIR=src
LIBDIR=lib
BINDIR=bin
SHDDIR=shd
TEXDIR=tex

OBJS=$(SRCDIR)/main.cpp $(LIBDIR)/glad.c $(LIBDIR)/stb_image.cpp $(SRCDIR)/windowdef.cpp $(SRCDIR)/shader.cpp $(SRCDIR)/mesh.cpp
OBJH=$(SRCDIR)/libs.h $(LIBDIR)/stb_image.h $(SRCDIR)/windowdef.h $(SRCDIR)/shader.h $(SRCDIR)/mesh.h

TARGET=$(BINDIR)/wawacraft_evolved.elf

wawacraft_evolved: $(OBJH) $(OBJS)
	cp -r $(SHDDIR) $(BINDIR)
	cp -r $(TEXDIR) $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)

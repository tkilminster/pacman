GLEWPATH = /modules/cs324/glew-1.11.0
INCDIRS= -I$(GLEWPATH)/include
LIBDIRS= -L/usr/X11R6/lib -L$(GLEWPATH)/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm  -lGLEW -lpng

CPPFLAGS= $(INCDIRS) -O3
CXXFLAGS = -O3 -std=c++11
LDFLAGS= $(CPPFLAGS) $(LIBDIRS) -Wl,-rpath,$(GLEWPATH)/lib

TARGETS = 

SRCS = 

OBJS =  $(SRCS:.cpp=.o)

CXX = g++

default: $(TARGETS)

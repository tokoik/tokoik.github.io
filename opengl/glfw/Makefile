TARGET	= プログラム名
SOURCES	= $(wildcard *.cpp)
HEADERS	= $(wildcard *.h)
OBJECTS	= $(patsubst %.cpp,%.o,$(SOURCES))
DEBUG	= -g -D_DEBUG
#DEBUG	= -O3
CXXFLAGS	= --std=c++0x -Wall $(DEBUG) -DX11 -I/usr/local/include
LDLIBS	= -lGL -lXi -lXinerama -lXrandr -lXxf86vm -lX11 -lrt -lpthread -lm -L/usr/local/lib -lGLEW -lglfw

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(TARGET).dep: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES) > $@

clean:
	-$(RM) $(TARGET) *.o *~ .*~ a.out core

-include $(TARGET).dep

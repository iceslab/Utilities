CXXFLAGS=-c -Wall -std=c++14
AR=ar
ARFLAGS=-rv
LDFLAGS=
SOURCES=Timer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Utilities.a

all: release

release: CXXFLAGS += -O3
release: $(SOURCES) $(EXECUTABLE)
	
debug: CXXFLAGS += -gfull
debug: $(SOURCES) $(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
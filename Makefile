
TARGET = gbasm
BUILDDIR = build

SOURCES = main.cpp \
		  asm.cpp \
		  Parser.cpp \
		  Load.cpp \
		  Instruction.cpp 

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

WARNINGS = -Wall -Werror -Wno-unused-function

LDFLAGS = 

CPPFLAGS = -g $(WARNINGS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(LDFLAGS) -o $@ $(OBJECTS)

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	g++ -c $(CPPFLAGS) $< -o $@

clean:
	rm -r build

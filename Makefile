PROJECT_NAME := VoxelGame
CC		:= g++
SRCDIR	:= src
BUILDDIR  := build
TARGET	:= $(PROJECT_NAME)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS	  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
CFLAGS	:= -Wall -D_GNU_SOURCE -g
LIB	   := $(shell sdl2-config --libs) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLEW -lGLU
INC	   := $(shell sdl2-config --cflags)

GREEN=`tput setaf 2`
RESET=`tput sgr0`

define print_green
	@echo "$(GREEN)$(1)$(RESET)"
endef

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

$(TARGET): $(BUILDDIR) $(OBJECTS)
	$(call print_green,"Linking object files...")
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIB)
	$(call print_green,"$(TARGET) has been created!")

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td)
	@cp $(@:.o=.td) $(@:.o=.d)
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		 -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d)
	@rm -f $(@:.o=.td)

-include $(DEPS)

.PHONY: clean all

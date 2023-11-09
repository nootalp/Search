OUTPUT = Search
CC = gcc
CFLAGS = -Wall -Os
SRCDIR = src
INCDIR = include
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
	# Fetch all source files. 
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
	# Pick up all file names in SOURCES and create objects and source files in the respective directories.
	
ifeq ($(OS), Windows_NT)
    EXECUTABLE_EXTENSION = .exe
    RM_OBJ = del /Q $(OBJDIR)\*.o
else
    EXECUTABLE_EXTENSION =
    RM_OBJ = rm -f $(OBJDIR)/*.o
endif

all: $(OUTPUT)
$(OUTPUT): $(OBJECTS)
	@echo Serving $@ binary:
	$(CC) $(CFLAGS) $(OBJECTS) -o $@$(EXECUTABLE_EXTENSION) -lregex

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Creating object: $@
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@
		
clean:
	$(RM_OBJ) $(OUTPUT)$(EXECUTABLE_EXTENSION)
	
run:
	./$(OUTPUT)$(EXECUTABLE_EXTENSION)

.PHONY: all clean run
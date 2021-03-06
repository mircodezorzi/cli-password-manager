IDIR = "/usr/include/boost/variant.hpp"
NAME = program
LIBS = -lncurses
CXX := g++

CFLAGS = -I$(IDIR)

all: build

%.o: %.cpp
	$(CXX) -c $< -o $@

tags:
	ctags -R .

build:
	@echo "** Building $(NAME)..."
	$(CXX) -o $(NAME) *.o $(LIBS) $(CFLAGS)

clean:
	@echo "** Removing object files and executables..."
	rm -f $(NAME) *.o

install:
	@echo '** Installing...'
	cp $(NAME) /usr/bin/

uninstall:
	@echo "** Uninstalling..."
	rm -f /usr/bin/$(NAME)

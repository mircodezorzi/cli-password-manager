NAME = program
LIBS = -lncurses
CXX := g++

all: program

%.o: %.cpp
	$(CXX) -c $< -o $@

program:
	@echo "** Building game..."
	$(CXX) -o $(NAME) *.o $(LIBS)

clean:
	@echo "** Removing object files and executables..."
	rm -f $(NAME) *.o

install:
	@echo '** Installing...'
	cp $(NAME) /usr/bin/

uninstall:
	@echo "** Uninstalling..."
	rm -f /usr/bin/$(NAME)

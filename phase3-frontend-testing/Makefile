CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Builds the Front End. The handout calls the program distribution-system.
distribution-system: src/*.cpp src/*.h
	$(CXX) $(CXXFLAGS) -o distribution-system src/*.cpp

# Removes the built program.
clean:
	rm -f distribution-system

.PHONY: clean

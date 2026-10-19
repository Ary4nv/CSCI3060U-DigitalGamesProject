CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Builds the Front End executable from every source file in src/.
frontend: src/*.cpp src/*.h
	$(CXX) $(CXXFLAGS) -o frontend src/*.cpp

# Removes the built executable.
clean:
	rm -f frontend

.PHONY: clean

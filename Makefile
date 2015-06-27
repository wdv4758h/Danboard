CXX = g++
CXXFLAGS = -std=c++14 -Wall -Ofast -march=native -pipe -flto
LIBRARIES = wiringPi
HEADERS = /usr/local/include
INCLUDES = $(foreach header, $(HEADERS), -I$(header))
LDFLAGS = -s $(foreach library, $(LIBRARIES), -l$(library))

danboard: bin
	$(CXX) $(CXXFLAGS) $(LDFLAGS) src/stepper.cpp -o bin/danboard_stepper

bin:
	mkdir -p bin

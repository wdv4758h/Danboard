CXX = g++
CXXFLAGS = -std=c++14 -Wall -Ofast -march=native -pipe -flto
PI_LIBRARIES = pthread wiringPi
CV_LIBRARIES = opencv_core opencv_imgproc opencv_objdetect opencv_highgui
HEADERS = /usr/local/include
INCLUDES = $(foreach header, $(HEADERS), -I$(header))
PI_LDFLAGS = -s $(foreach library, $(PI_LIBRARIES), -l$(library))
CV_LDFLAGS = -s $(foreach library, $(CV_LIBRARIES), -l$(library))

danboard: bin
#	$(CXX) $(CXXFLAGS) $(PI_LDFLAGS) src/stepper.cpp -o bin/danboard_stepper
	$(CXX) $(CXXFLAGS) $(CV_LDFLAGS) src/detect.cpp -o bin/danboard_detect

test: bin
	$(CXX) $(CXXFLAGS) $(PI_LDFLAGS) -I src/ test/stepper-8-motion.cpp -o bin/stepper-8-motion
	$(CXX) $(CXXFLAGS) $(CV_LDFLAGS) -I src/ test/face_detection.cpp -o bin/face_detection

bin:
	mkdir -p bin

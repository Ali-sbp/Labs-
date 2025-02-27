# Object files for tests
build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp

# Test object files
build/test_bounding_rect.o: tests/test_bounding_rect.cpp
	g++ -g -c -o build/test_bounding_rect.o tests/test_bounding_rect.cpp

build/test_rect_basic_methods.o: tests/test_rect_basic_methods.cpp
	g++ -g -c -o build/test_rect_basic_methods.o tests/test_rect_basic_methods.cpp

build/test_rect_operations.o: tests/test_rect_operations.cpp
	g++ -g -c -o build/test_rect_operations.o tests/test_rect_operations.cpp

build/test_rect_properties.o: tests/test_rect_properties.cpp
	g++ -g -c -o build/test_rect_properties.o tests/test_rect_properties.cpp

# Test executables
build/test_bounding_rect.out: build/test_bounding_rect.o build/rect.o
	g++ -g -o build/test_bounding_rect.out build/test_bounding_rect.o build/rect.o

build/test_rect_basic_methods.out: build/test_rect_basic_methods.o build/rect.o
	g++ -g -o build/test_rect_basic_methods.out build/test_rect_basic_methods.o build/rect.o

build/test_rect_operations.out: build/test_rect_operations.o build/rect.o
	g++ -g -o build/test_rect_operations.out build/test_rect_operations.o build/rect.o

build/test_rect_properties.out: build/test_rect_properties.o build/rect.o
	g++ -g -o build/test_rect_properties.out build/test_rect_properties.o build/rect.o

# Run all tests
test: build/test_bounding_rect.out build/test_rect_basic_methods.out build/test_rect_operations.out build/test_rect_properties.out
	./build/test_bounding_rect.out
	./build/test_rect_basic_methods.out
	./build/test_rect_operations.out
	./build/test_rect_properties.out

clean:
	rm -f build/*.o build/*.out

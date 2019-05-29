.PHONY: all clean

all: bin/main

BUILD_SRC := ./build/src
BUILD_TEST := ./build/test


bin/main: $(BUILD_SRC)/main.o $(BUILD_SRC)/matrix.o $(BUILD_SRC)/NeuralNetworks.o
	g++ -Wall -Werror $(BUILD_SRC)/main.o $(BUILD_SRC)/matrix.o $(BUILD_SRC)/NeuralNetworks.o -o bin/main

$(BUILD_SRC)/main.o: src/main.cpp
	g++ -Wall -Werror  -I thirdparty -c src/main.cpp -o $(BUILD_SRC)/main.o

$(BUILD_SRC)/matrix.o: src/matrix.cpp
	g++ -Wall -Werror -c src/matrix.cpp -o $(BUILD_SRC)/matrix.o

$(BUILD_SRC)/NeuralNetworks.o: src/NeuralNetworks.cpp
	g++ -Wall -Werror -c src/NeuralNetworks.cpp -o $(BUILD_SRC)/NeuralNetworks.o


test1: bin/test_matrix

bin/test_matrix: $(BUILD_TEST)/matrix.o $(BUILD_TEST)/test_matrix.o
	g++ -Wall -Werror $(BUILD_TEST)/matrix.o $(BUILD_TEST)/test_matrix.o -o bin/test_matrix

$(BUILD_TEST)/test_matrix.o: test/test_matrix.cpp
	g++ -Wall -Werror -c -I thirdparty -I src test/test_matrix.cpp -o $(BUILD_TEST)/test_matrix.o

$(BUILD_TEST)/matrix.o: src/matrix.cpp
	g++ -Wall -Werror -c src/matrix.cpp -o $(BUILD_TEST)/matrix.o


test2: bin/test_nn

bin/test_nn: $(BUILD_TEST)/test_nn1.o $(BUILD_TEST)/matrix1.o $(BUILD_TEST)/NeuralNetworks1.o
	g++ -Wall -Werror $(BUILD_TEST)/test_nn1.o $(BUILD_TEST)/NeuralNetworks1.o $(BUILD_TEST)/matrix1.o -o bin/test_nn

$(BUILD_TEST)/test_nn1.o: test/test_nn.cpp
	g++ -Wall -Werror -c -I thirdparty -I src test/test_nn.cpp -o $(BUILD_TEST)/test_nn1.o

$(BUILD_TEST)/matrix1.o: src/matrix.cpp
	g++ -Wall -Werror -c src/matrix.cpp -o $(BUILD_TEST)/matrix1.o

$(BUILD_TEST)/NeuralNetworks1.o: src/NeuralNetworks.cpp
	g++ -Wall -Werror -c src/NeuralNetworks.cpp -o $(BUILD_TEST)/NeuralNetworks1.o


run_tests: test1 test2
	bin/test_matrix
	bin/test_nn


clean:
	rm -rf $(BUILD_SRC)/*.o $(BUILD_TEST)/*.o bin/main bin/test_matrix bin/test_nn

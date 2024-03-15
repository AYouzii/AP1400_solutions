obj_path = ./objects
obj_files = $(patsubst %.cpp, ./objects/%.o, $(notdir $(wildcard ./src/*.cpp)))

GTEST_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googletest/include
GMOCK_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googlemock/include
GOOGLE_LIB_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/build/lib

main: $(obj_files)
	g++ $(obj_files) -L $(GOOGLE_LIB_PATH) -lgtest_main -lgtest -lpthread -o main
	@echo linking complete!

$(obj_path)/main.o: ./src/main.cpp ./include/bst.h $(GTEST_PATH)/gtest/gtest.h
	@echo compiling main.cpp ...
	g++ -I ./include -I $(GTEST_PATH) -c ./src/main.cpp -o $(obj_path)/main.o

$(obj_path)/bst.o: ./src/bst.cpp ./include/bst.h
	@echo compiling bst.cpp ...
	g++ -I ./include -c ./src/bst.cpp -o $(obj_path)/bst.o

$(obj_path)/unit_test.o: ./src/unit_test.cpp $(GTEST_PATH)/gtest/gtest.h $(GMOCK_PATH)/gmock/gmock.h ./include/bst.h
	@echo compiling unit_test.cpp ...
	g++ -I ./include -I $(GTEST_PATH) -I $(GMOCK_PATH) -c ./src/unit_test.cpp -o $(obj_path)/unit_test.o

.PHONY: clean
clean:
	@echo cleanning...
	del $(obj_path)/*.o
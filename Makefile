obj_path = ./objects
obj_files = $(patsubst %.cpp, ./objects/%.o, $(notdir $(wildcard ./src/*.cpp)))

main: $(obj_files)
	g++ $(obj_files) -L ./lib -lgtest_main -lgtest -lpthread -o main
	@echo linking complete!

debug:
	@echo $(obj_files)

$(obj_path)/main.o: ./src/main.cpp ./include/hw1.h ./include/gtest/gtest.h
	g++ -I ./include -I ./include/gtest -c ./src/main.cpp -o $(obj_path)/main.o
	@echo main.cpp compilation complete!

$(obj_path)/hw1.o: ./src/hw1.cpp ./include/hw1.h
	g++ -I ./include -c ./src/hw1.cpp -o $(obj_path)/hw1.o
	@echo hw1.cpp compilation complete!

$(obj_path)/unit_test.o: ./src/unit_test.cpp ./include/gtest/gtest.h ./include/gmock/gmock.h ./include/hw1.h
	g++ -I ./include -I ./include/gtest -I ./include/gmock -c ./src/unit_test.cpp -o $(obj_path)/unit_test.o
	@echo unit_test.cpp compilation complete!

.PHONY: clean
clean:
	@echo cleanning...
	del *.o
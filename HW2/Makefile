obj_path = ./objects
obj_files = $(patsubst %.cpp, ./objects/%.o, $(notdir $(wildcard ./src/*.cpp)))

main: $(obj_files)
	g++ $(obj_files) -L ./lib -lgtest_main -lgtest -lpthread -L D:\software\msys2\ucrt64\lib -lssl -lcrypto -o main
	@echo linking complete!

debug:
	@echo $(obj_files)

$(obj_path)/main.o: ./src/main.cpp ./include/client.h ./include/gtest/gtest.h ./include/server.h
	@echo compiling main.cpp ...
	g++ -I ./include ./include/gtest -c ./src/main.cpp -o $(obj_path)/main.o

$(obj_path)/client.o: ./src/client.cpp ./include/client.h
	@echo compiling client.cpp ...
	g++ -I ./include -c ./src/client.cpp -o $(obj_path)/client.o

$(obj_path)/crypto.o: ./src/crypto.cpp ./include/crypto.h
	@echo compiling crypto.cpp ...
	g++ -I ./include -c ./src/crypto.cpp -o $(obj_path)/crypto.o

$(obj_path)/server.o: ./src/server.cpp ./include/server.h
	@echo compiling server.cpp ...
	g++ -I ./include -c ./src/server.cpp -o $(obj_path)/server.o

$(obj_path)/unit_test.o: ./src/unit_test.cpp ./include/gtest/gtest.h ./include/gmock/gmock.h ./include/server.h ./include/client.h
	@echo compiling unit_test.cpp ...
	g++ -I ./include ./include/gtest ./include/gmock -c ./src/unit_test.cpp -o $(obj_path)/unit_test.o

.PHONY: clean
clean:
	@echo cleanning...
	del $(obj_path)/*.o
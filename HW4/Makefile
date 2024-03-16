obj_path = ./objects
obj_files = $(addprefix $(obj_path)/, main.o unit_test.o)


GTEST_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googletest/include
GMOCK_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googlemock/include
GOOGLE_LIB_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/build/lib

main: $(obj_files)
	g++ $(obj_files) -L $(GOOGLE_LIB_PATH) -lgtest_main -lgtest -lpthread -o main
	@echo linking complete!

$(obj_path)/main.o: ./src/main.cpp ./include/*.h ./include/*.hpp $(GTEST_PATH)/gtest/gtest.h
	@echo compiling main.cpp ...
	g++ -I ./include -I $(GTEST_PATH) -c ./src/main.cpp -o $(obj_path)/main.o

# $(obj_path)/shared_ptr.o: ./include/shared_ptr.hpp
# 	@echo compiling shared_ptr.hpp ...
# 	g++ -I ./include -c ./include/shared_ptr.hpp -o $(obj_path)/shared_ptr.o

# $(obj_path)/unique_ptr.o: ./include/unique_ptr.hpp
# 	@echo compiling unique_ptr.hpp ...
# 	g++ -I ./include -c ./include/unique_ptr.hpp -o $(obj_path)/unique_ptr.o

$(obj_path)/unit_test.o: ./src/unit_test.cpp $(GTEST_PATH)/gtest/gtest.h $(GMOCK_PATH)/gmock/gmock.h ./include/*.h ./include/*.hpp
	@echo compiling unit_test.cpp ...
	g++ -I ./include -I $(GTEST_PATH) -I $(GMOCK_PATH) -c ./src/unit_test.cpp -o $(obj_path)/unit_test.o

.PHONY: clean
clean:
	@echo cleanning...
	del $(obj_path)/*.o
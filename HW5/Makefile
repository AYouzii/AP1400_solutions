DIR_OBJ = ./objects
DIR_SRC = ./src
DIR_INCLUDE = ./include

obj_files = $(patsubst %.cpp, $(DIR_OBJ)/%.o, $(notdir $(wildcard $(DIR_SRC)/*.cpp)))

GTEST_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googletest/include
GMOCK_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/googlemock/include
GOOGLE_LIB_PATH = D:/software/googletest-1.14.0/googletest-1.14.0/build/lib

main: $(obj_files)
	@echo linking object files...
	g++ $^ -L $(GOOGLE_LIB_PATH) -lgtest_main -lgtest -lpthread -o $@

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cpp $(DIR_INCLUDE)/*.h $(GTEST_PATH)/gtest/gtest.h
	@echo compiling main.cpp...
	g++ -I $(DIR_INCLUDE) -I $(GTEST_PATH) -c $< -o $(DIR_OBJ)/main.o

$(DIR_OBJ)/unit_test.o: $(DIR_SRC)/unit_test.cpp $(DIR_INCLUDE)/*.h $(GTEST_PATH)/gtest/gtest.h $(GMOCK_PATH)/gmock/gmock.h
	@echo compiling unit_test.cpp...
	g++ -I $(DIR_INCLUDE) -I $(GTEST_PATH) -I $(GMOCK_PATH) -c $< -o $(DIR_OBJ)/unit_test.o

$(DIR_OBJ)/cappuccino.o: $(DIR_SRC)/cappuccino.cpp $(DIR_INCLUDE)/cappuccino.h
	@echo compiling cappuccino.cpp...
	g++ -I $(DIR_INCLUDE) -c $< -o $(DIR_OBJ)/cappuccino.o

$(DIR_OBJ)/espresso_based.o: $(DIR_SRC)/espresso_based.cpp $(DIR_INCLUDE)/espresso_based.h
	@echo compiling espresso_based.cpp...
	g++ -I $(DIR_INCLUDE) -c $< -o $(DIR_OBJ)/espresso_based.o

$(DIR_OBJ)/mocha.o: $(DIR_SRC)/mocha.cpp $(DIR_INCLUDE)/mocha.h
	@echo compiling mocha.cpp...
	g++ -I $(DIR_INCLUDE) -c $< -o $(DIR_OBJ)/mocha.o

.PHONY: clean
clean:
	@echo cleaning object files...
	-del $(DIR_OBJ)/*.o

CXX = g++
SRC = sorting.cpp
TARGET = sorting.exe

add:
	@echo Compiling $(SRC)...
	@$(CXX) $(SRC) -o $(TARGET)

clean:
	@echo Cleaning $(TARGET)
	@rm -f $(TARGET)
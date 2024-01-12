CC = g++
WFLAGS = -Wall -Wextra
CFLAGS = -g -I"include" $(WFLAGS)
LFLAGS = -L"lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_DIR = src
BUILD_DIR = build

TARGET = fish.exe
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	del /Q /F $(BUILD_DIR)\* $(TARGET)
	rmdir /Q /S $(BUILD_DIR)


run: $(TARGET)
	./$(TARGET)
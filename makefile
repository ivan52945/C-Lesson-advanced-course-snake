TARGET = snake

FLAGS = -Wall -std=c99 -lncurses -Iheaders

RELEASE_PREF = release
SRC_PREF = sources
OBJ_PREF = objects

SRC = $(wildcard $(SRC_PREF)/*.c)
OBJ = $(patsubst $(SRC_PREF)/%.c, $(OBJ_PREF)/%.o, $(SRC))

all: $(RELEASE_PREF)/$(TARGET)

$(RELEASE_PREF)/$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(RELEASE_PREF)/$(TARGET) $(FLAGS)

$(OBJ_PREF)/%.o: $(SRC_PREF)/%.c
	gcc -c $< -o $@ $(FLAGS)

clean:
	rm $(OBJ_PREF)/*
	rm $(RELEASE_PREF)/*
	del $(RELEASE_PREF)\\*.exe
	del $(OBJ_PREF)\\*.o

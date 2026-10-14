CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_ls
SRC = my_ls.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all
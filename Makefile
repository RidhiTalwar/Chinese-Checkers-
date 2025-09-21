CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I. -Imodel -Iview -Iutils

BIN = a.out

MODEL = model
VIEW = view
CTRL = controller
UTIL = utils

SRCS = \
  $(MODEL)/board.c \
  $(MODEL)/move.c \
  $(MODEL)/player.c \
  $(VIEW)/view.c \
  $(CTRL)/main.c \
  $(CTRL)/ai.c \
  $(UTIL)/utils.c

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)
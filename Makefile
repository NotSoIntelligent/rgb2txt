CC = gcc
CFLAGS = -Wall
OBJS = main.o rgb2txt.o
OUT = rgb2txt

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

clean:
	rm -f $(OBJS) $(OUT) ./*~

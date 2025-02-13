#Tchakounte Nzoumeni Yvan Landry (SM3201458)

CC = gcc
CFLAGS = -Wall -O2 -fopenmp
LDFLAGS = -lm

TARGET = raytracer
SRCS = main.c scene.c ppm.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

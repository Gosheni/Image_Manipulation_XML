# Sample Makefile

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra 

# Links together files needed to create executable
project: project.o ppm_io.o image_manip.o
	$(CC) -o project project.o ppm_io.o image_manip.o -lm

# Compiles mainFile.c to create mainFile.o
# Note that we list functions.h here as a file that
# main_file.c depends on, since main_file.c #includes it
project.o: project.c ppm_io.h image_manip.h
	$(CC) $(CFLAGS) -c project.c -g

# Compiles functions.c to create functions.o
# Note that we list functions.h here as a file that
# functions.c depends on, since functions.c #includes it
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c -g

image_manip.o: image_manip.c image_manip.h
	$(CC) $(CFLAGS) -c image_manip.c -g

# Removes all object files and the executable named main,
# so we can start fresh
clean:
	rm -f *.o main

###########################################################

# Checkerboard
checkerboard: checkerboard.o ppm_io.o
	$(CC) -o checkerboard checkerboard.o ppm_io.o

checkerboard.o: checkerboard.c ppm_io.h
	$(CC) $(CFLAGS) -c checkerboard.c -g

# img_cmp
img_cmp: img_cmp.o ppm_io.o
	$(CC) -o img_cmp img_cmp.o ppm_io.o

img_cmp.o: img_cmp.c ppm_io.h
	$(CC) $(CFLAGS) -c img_cmp.c -g

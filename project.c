//project.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.h"
#include "image_manip.h"

// Return (exit) codes
#define RC_SUCCESS            0
#define RC_MISSING_FILENAME   1
#define RC_OPEN_FAILED        2
#define RC_INVALID_PPM        3
#define RC_INVALID_OPERATION  4
#define RC_INVALID_OP_ARGS    5
#define RC_OP_ARGS_RANGE_ERR  6
#define RC_WRITE_FAILED       7
#define RC_UNSPECIFIED_ERR    8

void print_usage();

int main (int argc, char* argv[]) {

  // less than 2 command line args means that input or output filename
  // wasn't specified
  if (argc < 3) {
    fprintf(stderr, "Missing input/output filenames\n");
    print_usage();
    return RC_MISSING_FILENAME;
  }

  // make pointer to new image and open original file
  Image * new_image;
  FILE * orig = fopen(argv[1], "r");

  // input I/O error checker
  if (orig == NULL) {
    fprintf(stderr, "Input file I/O error\n");
    return RC_OPEN_FAILED;
  }

  // make image from original file
  Image * orig_image = read_ppm(orig);

  // input PPM error checker
  if (orig_image == NULL) {
    fprintf(stderr, "The Input file cannot be read as a PPM file\n");
    return RC_INVALID_PPM;
  }

  // choose which operation will be done and check if there are valid inputs
  if (strcmp(argv[3], "binarize") == 0) {
    if (argc != 5) {
      fprintf(stderr, "Incorrect number of arguments for the specified operation\n");
      return RC_INVALID_OP_ARGS;
    } else if (atoi(argv[4]) < 0 || atoi(argv[4]) > 255) {
      fprintf(stderr, "Invalid arguments for the specified operation\n");
      return RC_OP_ARGS_RANGE_ERR;
    }
    
    new_image = binarize(orig_image, atoi(argv[4]));
  } else if (strcmp(argv[3], "crop") == 0) {
    if (argc != 8) {
      fprintf(stderr, "Incorrect number of arguments for the specified operation\n");
      return RC_INVALID_OP_ARGS;
    } else if (atoi(argv[4]) < 0 || atoi(argv[4]) > orig_image->cols ||
               atoi(argv[5]) < 0 || atoi(argv[5]) > orig_image->rows ||
	       atoi(argv[6]) < 0 || atoi(argv[6]) > orig_image->cols || atoi(argv[6]) < atoi(argv[4]) ||
	       atoi(argv[7]) < 0 || atoi(argv[7]) > orig_image->rows || atoi(argv[7]) < atoi(argv[5])) {
      fprintf(stderr, "Invalid arguments for the specified operation\n");
      return RC_OP_ARGS_RANGE_ERR;
    }
	       
    new_image = crop(orig_image, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
  } else if (strcmp(argv[3], "zoom_in") == 0) {
    new_image = zoom_in(orig_image);
  } else if (strcmp(argv[3], "rotate-left") == 0) {
    new_image = rotate_left(orig_image);
  } else if (strcmp(argv[3], "pointilism") == 0) {
    new_image = pointilism(orig_image);
  } else if (strcmp(argv[3], "blur") == 0) {
    if (argc != 5) {
      fprintf(stderr, "Incorrect number of arguments for the specified operation\n");
      return RC_INVALID_OP_ARGS;
    } else if (atof(argv[4]) <= 0) {
      fprintf(stderr, "Invalid arguments for the specified operation\n");
      return RC_OP_ARGS_RANGE_ERR;
    }

    new_image = blur(orig_image, atof(argv[4]));
  } else { // no supported operations
    fprintf(stderr, "Unsupported image processing operations\n");
    return RC_INVALID_OPERATION;
  }

  // open new image file
  FILE * manip = fopen(argv[2], "w");

  // output I/O error
  if (manip == NULL) {
    fprintf(stderr, "Output file I/O error\n");
    return RC_WRITE_FAILED;
  }

  // write image to file
  int num_pixels = write_ppm(manip, new_image);

  // write_ppm error checker
  if (num_pixels == -1) {
    fprintf(stderr, "Output file I/O error\n");
    return RC_WRITE_FAILED;
  } else if (num_pixels != new_image->cols * new_image->rows) { // other error with image_manip.c
    fprintf(stderr, "Other errors not specified above\n");
    return RC_UNSPECIFIED_ERR;
  }

  // free new image and original image and close files
  free_image(&new_image);
  free_image(&orig_image);  
  fclose(orig);
  fclose(manip);
  
  return RC_SUCCESS;
}

void print_usage() {
  printf("USAGE: ./project <input-image> <output-image> <command-name> <command-args>\n");
  printf("SUPPORTED COMMANDS:\n");
  printf("   binarize <treshhold>\n");
  printf("   crop <top-lt-col> <top-lt-row> <bot-rt-col> <bot-rt-row>\n");
  printf("   zoom_in\n");
  printf("   rotate-left\n");
  printf("   pointilism\n");
  printf("   blur <sigma>\n");
}



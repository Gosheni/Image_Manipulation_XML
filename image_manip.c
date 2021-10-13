#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "image_manip.h"
#include "ppm_io.h"



/* HELPER for grayscale: (GIVEN)
 * convert a RGB pixel to a single grayscale intensity;
 * uses NTSC standard conversion
 */
unsigned char pixel_to_gray (const Pixel *p) {
  return (unsigned char)( (0.3 * (double)p->r) +
                          (0.59 * (double)p->g) +
                          (0.11 * (double)p->b) );
}


//______binarize______ (TODO)
/* convert image to black and white only based on threshold value
 */
Image * binarize(Image * im, int threshold) {
  // loop through each pixel in the array
  for (int i = 0; i < (im->rows * im->cols); i++) {
    // get pixel greyscale value
    unsigned char value = pixel_to_gray(&im->data[i]);

    // if value < threshold, r, g, and b = 0
    // else r, g, and b = 255
    if ((int) value < threshold) {
      im->data[i].r = 0;
      im->data[i].g = 0;
      im->data[i].b = 0;
    } else {
      im->data[i].r = 255;
      im->data[i].g = 255;
      im->data[i].b = 255;
    }
  }

  // return image
  return im; 
}

//______crop______ (TODO)
/* takes an image and points defining a bounding box,
 * and crops that box out of the image, returning a newly
 * created image containing just the cropped region
 */
Image * crop(Image * im, int top_col, int top_row, int bot_col, int bot_row) {
  int rows = bot_row - top_row;
  int cols = bot_col - top_col;

  Image * cropped = malloc(sizeof(Image));

  resize_image(&cropped, rows, cols);
  cropped->rows = rows;
  cropped->cols = cols;
  cropped->data = malloc(sizeof(Pixel) * rows * cols);

  int index = 0;
  
  for (int i = top_row; i < bot_row; i++) {
    for (int j = top_col; j < bot_col; j++) {
      cropped->data[index].r = im->data[j + i * cols].r;
      cropped->data[index].g = im->data[j + i * cols].g;
      cropped->data[index].b = im->data[j + i * cols].b;

      index++;
    }
  }
  
  return cropped;
}

//______blur______ (TODO)
/* apply a blurring filter to the image
 */
Image * blur(Image * im, int sigma) {
  return NULL; //REPLACE STUB
}

//______zoom_in______ (TODO)
/* "zoom in" an image, by duplicating each pixel into a 2x2 square of pixels
 */
Image * zoom_in(Image * im) {
  Image * zoomed = malloc(sizeof(Image));

  resize_image(&zoomed, im->rows * 2, im->cols * 2);
  zoomed->rows = im->rows * 2;
  zoomed->cols = im->cols * 2;
  zoomed->data = malloc(sizeof(Pixel) * (zoomed->rows * 2) * (zoomed->cols * 2));

  int index = 0;
  
  for (int i = 0; i < im->rows; i++) {
    for (int j = 0; j < im->cols; j++) {
      // edit top-left element in 2x2 square
      zoomed->data[index].r = im->data[j + i * im->cols].r;
      zoomed->data[index].g = im->data[j + i * im->cols].g;
      zoomed->data[index].b = im->data[j + i * im->cols].b;

      // edit top-right element in 2x2 square
      zoomed->data[index + 1].r = im->data[j + i * im->cols].r;
      zoomed->data[index + 1].g = im->data[j + i * im->cols].g;
      zoomed->data[index + 1].b = im->data[j + i * im->cols].b;

      // edit bottom-left element in 2x2 square
      zoomed->data[index + zoomed->cols].r = im->data[j + i * im->cols].r;
      zoomed->data[index + zoomed->cols].g = im->data[j + i * im->cols].g;
      zoomed->data[index + zoomed->cols].b = im->data[j + i * im->cols].b;

      // edit bottom-right element in 2x2 square
      zoomed->data[index + 1 + zoomed->cols].r = im->data[j + i * im->cols].r;
      zoomed->data[index + 1 + zoomed->cols].g = im->data[j + i * im->cols].g;
      zoomed->data[index + 1 + zoomed->cols].b = im->data[j + i * im->cols].b;     

      // go to next 2x2 square
      index += 2;
    }

    // go to next row of 2x2 squares
    index += zoomed->cols;
  }
  
  return zoomed;
}

// _______rotate-left________ (TODO)
/* rotate the input image counter-clockwise 90 degrees
 */
Image * rotate_left(Image * im) {
  //Make an image with reversed dimensions
  Image *copy = malloc(sizeof(Image));
  copy->data = malloc(sizeof(Pixel) * (im->rows) * (im->cols));
  copy->rows = im->cols;
  copy->cols = im->rows;

  //Store row and col values/Incrementing index
  int row = im->rows;
  int col = im->cols;
  int index = 0;

  //Reallocate image to match the rotated dimensions
  resize_image(&im, im->cols, im->rows);
  int temp = im->rows;
  im->rows = im->cols;
  im->cols = temp;

  //Loop to reinitialize rgb values of rotated im
  for (int i = col-1; i >= 0; i--) {
    for (int j = 0; j < row; j++){
      copy->data[index].r = im->data[i+j*col].r;
      copy->data[index].g = im->data[i+j*col].g;
      copy->data[index].b = im->data[i+j*col].b;

      index++;
    }
  }
  free_image(&im);

  return copy; //REPLACE STUB
}

// _______pointilism________ (TODO)
/* apply a painting like effect i.e. pointilism technique.
 */
Image * pointilism(Image * im) {
  return NULL; //REPLACE STUB
}


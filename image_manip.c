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
	 return NULL;
}

//______blur______ (TODO)
/* apply a blurring filter to the image
 */
Image * zoom_in(Image * im) {
  return NULL; //REPLACE STUB
}

//______zoom_in______ (TODO)
/* "zoom in" an image, by duplicating each pixel into a 2x2 square of pixels
 */
Image * rotate_left(Image * im) {
  //Copy im onto new Image copy
  Image *copy;
  *copy = *im;
  //Store row and col values/Incrementing index
  int row = copy->rows;
  int col = copy->cols;
  int index = 0;
  //Reallocate image to match the rotated dimensions
  resize_image(&im, im->cols, im->rows);
  //Loop to reinitialize rgb values of rotated im
  for (int i = col-1; i >= 0; i--) {
    for (int j = 0; j < row; j++){
      im->data[index].r = copy->data[i+j*col].r;
      im->data[index].g = copy->data[i+j*col].g;
      im->data[index].b = copy->data[i+j*col].b;

      index++;
    }
  }
  
  return im; //REPLACE STUB
}

// _______rotate-left________ (TODO)
/* rotate the input image counter-clockwise 90 degrees
 */
Image * pointilism(Image * im) {
  return NULL; //REPLACE STUB
}

// _______pointilism________ (TODO)
/* apply a painting like effect i.e. pointilism technique.
 */
Image * blur(Image * im, int sigma) {
  return NULL; //REPLACE STUB
}

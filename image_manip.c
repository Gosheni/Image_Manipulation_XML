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
  for (int i = 0; i < (im->rows * im->cols); i++) {
    unsigned char value = pixel_to_gray(&im->data[i]);
    if ((int) value < threshold) {
      printf("BLACK!!\n");
      im->data->r = 0;
      im->data->g = 0;
      im->data->b = 0;
    } else {
      im->data->r = 255;
      im->data->g = 255;
      im->data->b = 255;
    }

    //im->(data++);
  }
  printf("FINISHED\n");
  return im; //REPLACE STUB
}

//______crop______ (TODO)
/* takes an image and points defining a bounding box,
 * and crops that box out of the image, returning a newly
 * created image containing just the cropped region
 */
Image * crop(Image * im, int top_col, int top_row, int bot_col, int bot_row) {
  return NULL; //REPLACE STUB
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
  return NULL; //REPLACE STUB
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

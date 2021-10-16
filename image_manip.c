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

void make_gauss(double * gauss, int N, double sigma);
void filter_pixel(Image * im, int row, int col, double * gauss, int N);

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
  //int rows = bot_row - top_row + 1;
  //int cols = bot_col - top_col + 1;

  //Calculate size of the crop
  int rows = bot_row - top_row;
  int cols = bot_col - top_col;
  
  //Create new image cropped with adjusted size
  Image * cropped = malloc(sizeof(Image));

  cropped->data = malloc(sizeof(Pixel) * rows * cols);
  cropped->rows = rows;
  cropped->cols = cols;

  int index = 0;
  
  //Loop through original image and assign rgb values of im on to new image cropped
  for (int i = top_row; i < bot_row; i++) {
    for (int j = top_col; j < bot_col; j++) {
      cropped->data[index].r = im->data[j + i * im->cols].r;
      cropped->data[index].g = im->data[j + i * im->cols].g;
      cropped->data[index].b = im->data[j + i * im->cols].b;

      index++;
    }
  }

  //Free original image im
  free_image(&im);
  
  return cropped;
}

//______blur______ (TODO)
/* apply a blurring filter to the image
 */
Image * blur(Image * im, int sigma) {
  int len;
  
  if ((10 * sigma) % 2 == 0) len = 10 * sigma + 1;
  else len = 10 * sigma;

  double * gauss = malloc(sizeof(double) * len * len);
  
  make_gauss(gauss, len, sigma);
  
  for (int i = 0; i < im->rows; i++) {
    for (int j = 0; j < im->cols; j++) {
      filter_pixel(im, i, j, gauss, len);
    }
  }

  free(gauss);

  return im; 
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
  //Make another image with reversed dimensions as im
  Image *copy = malloc(sizeof(Image));
  copy->data = malloc(sizeof(Pixel) * (im->rows) * (im->cols));
  copy->rows = im->cols;
  copy->cols = im->rows;

  //Store row and col values/Incrementing index
  int row = im->rows;
  int col = im->cols;
  int index = 0;
  
  //Loop to assign rgb values of rotated im into new Image copy
  for (int i = col-1; i >= 0; i--) {
    for (int j = 0; j < row; j++){
      copy->data[index].r = im->data[i+j*col].r;
      copy->data[index].g = im->data[i+j*col].g;
      copy->data[index].b = im->data[i+j*col].b;

      index++;
    }
  }
  //Free image im
  free_image(&im);
  //return new image copy
  return copy;
}

// _______pointilism________ (TODO)
/* apply a painting like effect i.e. pointilism technique.
 */
Image * pointilism(Image * im) {
  //Random integer from 1 to 5
  int radius = (rand() % 5)+1;
  //Loop pointilism size*0.03 times to cover 3% of pixels
  for (int i = 0; i < im->rows * im->cols * 0.03; i++){
    //Pick random pixel
    int pix = rand() % (im->rows * im->cols);
    int col = pix % im->cols;
    int row = pix / im->cols;
    //Loop the pixels around the selected pixel within radius
    for (int j = row-radius; j < row+radius; j++){
      for (int k = col-radius; k < col+radius; k++){
	//Check for edge cases
	if (j < 0){
	  j = 0;
	}
	else if (k < 0){
	  k = 0;
	}
	else if (j >= im->rows || k >= im->cols){
	  continue;
	}
	//Color the pixel if it is within radius from the selected pixel
	else if ((abs(row-j) * abs(row-j) + abs(col-k) * abs(col-k)) < (radius * radius)){
	  im->data[j*im->cols+k].r = im->data[pix].r;
	  im->data[j*im->cols+k].g = im->data[pix].g;
	  im->data[j*im->cols+k].b = im->data[pix].b;
	}
      }
    }
  }

  return im; //REPLACE STUB
}

void make_gauss(double * gauss, int N, double sigma) {
  int center = N / 2;

  int dx; int dy;
  
  for (int i = 0; i < N; i++) {
    dy = abs(center - i);
    for (int j = 0; j < N; j++) {
      dx = abs(center - j);

      gauss[j + i * N] = (1.0 / (2.0 * PI * sq(sigma))) * exp( -(sq(dx) + sq(dy)) / (2 * sq(sigma)));
    }
  }
}

void filter_pixel(Image * im, int row, int col, double * gauss, int N) {
  double weights[3] = {0.0, 0.0, 0.0};
  
  // find filtered sum
  double filtered_sum = 0;
  for (int i = 0; i < N * N; i++) filtered_sum += gauss[i];

  int a = 0;
  
  for (int i = row - (N/2); i <= row + (N/2); i++){
    for (int j = col - (N/2); j <= col + (N/2); j++){
      if (i < 0 || j < 0 || i > im->rows || j > im->cols) {
	a++;
	continue;
      }
      weights[0] += (im->data[j + i * im->cols].r * gauss[a]);
      weights[1] += (im->data[j + i * im->cols].g * gauss[a]);
      weights[2] += (im->data[j + i * im->cols].b * gauss[a]);

      a++;
    }
  }

  weights[0] /= filtered_sum;
  weights[1] /= filtered_sum;
  weights[2] /= filtered_sum;

  im->data[col + row * im->cols].r = weights[0];
  im->data[col + row * im->cols].g = weights[1];
  im->data[col + row * im->cols].b = weights[2];    
}

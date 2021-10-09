#ifndef IMAGE_MANIP_H
#define IMAGE_MANIP_H

#include "ppm_io.h"

// store PI as a constant
#define PI 3.14159265358979323846

// macro to square a number
#define sq(X) ((X) * (X))

// macro to find the max of a number
#define MAX(a,b) ((a > b) ? (a) : (b))


/* HELPER for binarize:
 * convert a RGB pixel to a single grayscale intensity;
 * uses NTSC standard conversion
 */
unsigned char pixel_to_gray (const Pixel *p);

//___binarize___
/* convert image to black and white only based on threshold value
 */


//___crop___
/* crop the image given two corner pixel locations
 */


//___zoom_in___
/* "zoom in" an image, by duplicating each pixel into a 2x2 square of pixels
 */


//___rotate_left___
/* rotate the image 90 degrees to the left (counter-clockwise)
 */


//___pointilism___
/* apply painting-like pointilism technique to image
 */


//___blur___
/* apply a blurring filter to the image
 */


#endif

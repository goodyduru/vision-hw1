#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
    int i, j, k;
    float pixel;
    float sum = 0.0;
    // Sum all pixels
    for (i = 0; i < im.w; i++) {
        for (j = 0; j < im.h; j++) {
            for (k = 0; k < im.c; k++) {
                sum += get_pixel(im, i, j, k);
            }
        }
    }
    for (i = 0; i < im.w; i++) {
        for (j = 0; j < im.h; j++) {
            for (k = 0; k < im.c; k++) {
                pixel = get_pixel(im, i, j, k);
                set_pixel(im, i, j, k, pixel/sum);
            }
        }
    }
}

image make_box_filter(int w)
{
    int i, j, k;
    image blank_image =  make_image(w,w,1);
    for (i = 0; i < blank_image.w; i++) {
        for (j = 0; j < blank_image.h; j++) {
            for (k = 0; k < blank_image.c; k++) {
                set_pixel(blank_image, i, j, k, 1.0);
            }
        }
    }
    l1_normalize(blank_image);
    return blank_image;
}

image convolve_image(image im, image filter, int preserve)
{
    int i, j, k, f_i, f_j, offset_x, offset_y, channel;
    image final_image;
    float pixel = 0.0;
    offset_x = filter.w/2;
    offset_y = filter.h/2;
    if ( preserve == 1 ) {
        final_image = make_image(im.w, im.h, im.c);
    }
    else {
        final_image = make_image(im.w, im.h, 1);
    }
    for (i = 0; i < im.w; i++) {
        for (j = 0; j < im.h; j++) {
            for (k = 0; k < im.c; k++) {
                channel = ( filter.c > 1 ) ? k : 0;
                for (f_i = 0; f_i < filter.w; f_i++) {
                    for(f_j = 0; f_j < filter.h; f_j++) {
                        pixel += (get_pixel(filter, f_i, f_j, channel) * 
                                    get_pixel(im, i + f_i - offset_x, j + f_j - offset_y, k));
                    }
                }
                if ( preserve == 1 ) {
                    set_pixel(final_image, i, j, k, pixel);
                    pixel = 0.0;
                }
            }
            if ( preserve == 0 ) {
                set_pixel(final_image, i, j, 0, pixel);
                pixel = 0.0;
            }
        }
    }
    return final_image;
}

image make_highpass_filter()
{
    int i, j;
    image blank_image = make_image(3,3,1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if ( i == 1 || j == 1 ) {
                if ( i == 1 && j == 1 ) {
                    set_pixel(blank_image, i, j, 0, 4.0);
                }
                else {
                    set_pixel(blank_image, i, j, 0, -1.0);
                }
            }
            else {
                set_pixel(blank_image, i, j, 0, 0.0);
            }
        }
    }
    return blank_image;
}

image make_emboss_filter()
{
    int i, j;
    image blank_image = make_image(3,3,1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if ( i == 0 && j == 0 ) {
                set_pixel(blank_image, i, j, 0, -2.0);
            }
            else if ( (i == 1 && j == 0 ) || ( i == 0 && j == 1) ) {
                set_pixel(blank_image, i, j, 0, -1.0);
            }
            else if ( (i == 2 && j == 0 ) || ( i == 0 && j == 2) ) {
                set_pixel(blank_image, i, j, 0, 0.0);
            }
            else if ( i == 1 && j == 1 ) {
                set_pixel(blank_image, i, j, 0, 1.0);
            }
            else if ( (i == 1 && j == 2 ) || ( i == 2 && j == 1) ) {
                set_pixel(blank_image, i, j, 0, 1.0);
            }
            else {
                set_pixel(blank_image, i, j, 0, 2.0);
            }
        }
    }
    return blank_image;
}

image make_sharpen_filter()
{
    int i, j;
    image blank_image = make_image(3,3,1);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if ( i == 1 || j == 1 ) {
                if ( i == 1 && j == 1 ) {
                    set_pixel(blank_image, i, j, 0, 5.0);
                }
                else {
                    set_pixel(blank_image, i, j, 0, -1.0);
                }
            }
            else {
                set_pixel(blank_image, i, j, 0, 0.0);
            }
        }
    }
    return blank_image;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: Use preserve for sharpen filter.

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: Maybe emboss

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}

#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    return get_pixel(im, (int) round(x), (int) round(y), c);
}

image nn_resize(image im, int w, int h)
{
    int i, j, k;
    float a_x, a_y, b_x, b_y, pixel;
    image new_img = make_image(w, h, im.c);
    a_x = (float)im.w / w;
    b_x = -0.5 + 0.5 * a_x;
    a_y = (float)im.h / h;
    b_y = -0.5 + 0.5 * a_y;
    for ( i = 0; i < w; i++ ) {
        for ( j = 0; j < h; j++ ) {
            for ( k = 0; k < im.c; k++ ) {
                pixel = nn_interpolate(im, a_x * i + b_x, a_y * j + b_y, k);
                set_pixel(new_img, i, j, k, pixel);
            }
        }
    }
    return new_img;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}


#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    x = round(x);
    y = round(y);

    return get_pixel(im,x,y,c);
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image nn_resize = make_image(w,h,im.c);
    float x_rat = (float)(im.w)/w;
    float y_rat = (float)(im.h)/h;
    for(int k=0;k<im.c;k++){
        for(int j=0;j<h;j++){
            for(int i=0;i<w;i++){
                float x1 = (i+0.5) * (x_rat) - 0.5;
                float y1 = (j+0.5) * (y_rat) - 0.5;
                float a = nn_interpolate(im,x1,y1,k);
                set_pixel(nn_resize,i,j,k,a);
               }
        }
    }
    return nn_resize;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    float v1=get_pixel(im,floor(x),floor(y),c);
    float v2=get_pixel(im,ceil(x),floor(y),c);
    float v3=get_pixel(im,floor(x),ceil(y),c);
    float v4=get_pixel(im,ceil(x),ceil(y),c);
    float q1 = v1 * (ceil(x) - x) + v2 * (x - floor(x));
    float q2 = v3 * (ceil(x) - x) + v4 * (x - floor(x));
    float q  = q1 * (ceil(y) - y) + q2 * (y - floor(y));
    return q;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
     image bilinr_resize = make_image(w,h,im.c);
    float x_rat = (float)(im.w)/w;
    float y_rat = (float)(im.h)/h;
    for(int k=0;k<im.c;k++){
        for(int j=0;j<h;j++){
            for(int i=0;i<w;i++){
                float x1 = (i+0.5) * (x_rat) - 0.5;
                float y1 = (j+0.5) * (y_rat) - 0.5;
                float a = bilinear_interpolate(im,x1,y1,k);
                set_pixel(bilinr_resize,i,j,k,a);
               }
        }
    }
    return bilinr_resize;
}


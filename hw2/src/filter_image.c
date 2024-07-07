#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

void l1_normalize(image im)
{
 float aa = 0.0;
 for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
              aa += get_pixel(im,i,j,k) ;
            }
        }
 }
 if(aa!=0){
    for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
              im.data[i + j*im.w + k*im.w*im.h]= (get_pixel(im,i,j,k)/aa);
            }
        }
 }
}else{
     for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
              im.data[i + j*im.w + k*im.w*im.h]= (1.00/(im.h*im.w));
            }
        }
 }
}
}


image make_box_filter(int w)
{
   image box_filter = make_image(w,w,1);
   for(int i=0;i<(w*w);i++){
    box_filter.data[i] = 1;
   }
   l1_normalize(box_filter);
   return box_filter;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(filter.c == 1 || filter.c == im.c);
    image convo = make_image(im.w, im.h, im.c);
    if(preserve == 1){
    for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
                int z;
                float sum = 0.0;
                if (filter.c == 1){ 
                    z = 0;
                 }else{
                     z = k;
                 }
                for (int b = 0; b < filter.h; b++) {
                    for (int a = 0; a < filter.w; a++) {
                        int x = i - (filter.w / 2) + a;
                        int y = j - (filter.h / 2) + b;
                        sum = sum + get_pixel(filter, a, b, z) * get_pixel(im, x, y, k);
                    }
                }
                set_pixel(convo, i, j, k, sum);
            }
        }
    }
    return convo;
    }else{
        for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
                int z;
                float sum = 0.0;
                if (filter.c == 1){ 
                    z = 0;
                 }else{
                     z = k;
                 }
                for (int b = 0; b < filter.h; b++) {
                    for (int a = 0; a < filter.w; a++) {
                        int x = i - (filter.w / 2) + a;
                        int y = j - (filter.h / 2) + b;
                        sum = sum + get_pixel(filter, a, b, z) * get_pixel(im, x, y, k);
                    }
                }
                set_pixel(convo, i, j, k, sum);
            }
        }
        }
    image convo1 = make_image(im.w, im.h, 1);
    for (int w = 0; w < im.w; w++) {
      for (int h = 0; h < im.h; h++) {
        float sum1 = 0;
        for (int c = 0; c < im.c; c++) {
        sum1 += convo.data[w + h*im.w + im.w*im.h*c];
        }
        convo1.data[w + h*im.w] = sum1;
      }
    }
    return convo1;
    }
}



image make_highpass_filter()
{
    // TODO
    image highpass_filter = make_box_filter(3);
    highpass_filter.data[0] = 0;
    highpass_filter.data[1] = -1;
    highpass_filter.data[2] = 0;
    highpass_filter.data[3] = -1;
    highpass_filter.data[4] = 4;
    highpass_filter.data[5] = -1;
    highpass_filter.data[6] = 0;
    highpass_filter.data[7] = -1;
    highpass_filter.data[8] = 0;

    return highpass_filter;
}

image make_sharpen_filter()
{
    // TODO
    image sharpen_filter = make_box_filter(3);
    sharpen_filter.data[0] = 0;
    sharpen_filter.data[1] = -1;
    sharpen_filter.data[2] = 0;
    sharpen_filter.data[3] = -1;
    sharpen_filter.data[4] = 5;
    sharpen_filter.data[5] = -1;
    sharpen_filter.data[6] = 0;
    sharpen_filter.data[7] = -1;
    sharpen_filter.data[8] = 0;

    return sharpen_filter;
}

image make_emboss_filter()
{
    // TODO
    image emboss_filter = make_box_filter(3);
    emboss_filter.data[0] = -2;
    emboss_filter.data[1] = -1;
    emboss_filter.data[2] = 0;
    emboss_filter.data[3] = -1;
    emboss_filter.data[4] = 1;
    emboss_filter.data[5] = 1;
    emboss_filter.data[6] = 0;
    emboss_filter.data[7] = 1;
    emboss_filter.data[8] = 2;
    return emboss_filter;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    int a = (int)(6*sigma);
    if(a%2==0) a=a+1;
    else a=a+2;
    image gaussian_filter=make_box_filter(a);
        for (int j = 0; j < a; j++) {
            for (int i = 0; i < a; i++) {
                gaussian_filter.data[i+j*a]=((1/(2*3.14*sigma*sigma)))*exp(-(((i-(a/2)) * (i-(a/2)) + (j-(a/2)) * (j-(a/2)))/(2*sigma*sigma)));
            }
        }
        l1_normalize(gaussian_filter);
        return gaussian_filter;
}

image add_image(image a, image b)
{
    // TODO
    image add = make_image(a.w,a.h,a.c);
     for (int k = 0; k < a.c; k++) {
        for (int j = 0; j < a.h; j++) {
            for (int i = 0; i < a.w; i++) {
                add.data[i + j*a.w + k*a.w*a.h] = get_pixel(a,i,j,k) + get_pixel(b,i,j,k);
            }
        }
     }
      return add;
}

image sub_image(image a, image b)
{
    // TODO
     image sub = make_image(a.w,a.h,a.c);
     for (int k = 0; k < a.c; k++) {
        for (int j = 0; j < a.h; j++) {
            for (int i = 0; i < a.w; i++) {
                sub.data[i + j*a.w + k*a.w*a.h] = get_pixel(a,i,j,k) - get_pixel(b,i,j,k);
            }
        }
     }
      return sub;
}

image make_gx_filter()
{
    // TODO
    image gx_filter = make_box_filter(3);
    gx_filter.data[0] = -1;
    gx_filter.data[1] = 0;
    gx_filter.data[2] = 1;
    gx_filter.data[3] = -2;
    gx_filter.data[4] = 0;
    gx_filter.data[5] = 2;
    gx_filter.data[6] = -1;
    gx_filter.data[7] = 0;
    gx_filter.data[8] = 1;

    return gx_filter;
}

image make_gy_filter()
{
    // TODO
    image gy_filter = make_box_filter(3);
    gy_filter.data[0] = -1;
    gy_filter.data[1] = -2;
    gy_filter.data[2] = -1;
    gy_filter.data[3] = 0;
    gy_filter.data[4] = 0;
    gy_filter.data[5] = 0;
    gy_filter.data[6] = 1;
    gy_filter.data[7] = 2;
    gy_filter.data[8] = 1;

    return gy_filter;
   
}

void feature_normalize(image im)
{
    // TODO
    float max=im.data[0];
    float min=im.data[0];
        for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 1; i < im.w; i++) {
                if(max < get_pixel(im,i,j,k)){
                     max = get_pixel(im,i,j,k);
                }
                if(min > get_pixel(im,i,j,k)){
                    min = get_pixel(im,i,j,k);
                }
            }
        }
        }
        if(max != min){
            for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
              im.data[i + j*im.w + k*im.w*im.h]=((im.data[i + j*im.w + k*im.w*im.h] - min)/(max - min));
        }
        }
    }
        }else{
                        for (int k = 0; k < im.c; k++) {
        for (int j = 0; j < im.h; j++) {
            for (int i = 0; i < im.w; i++) {
              im.data[i + j*im.w + k*im.w*im.h]=0;
        }
        }
    }
  }
}

image *sobel_image(image im)
{
    // TODO
    image gx = make_gx_filter();
    image gy = make_gy_filter();
    image Gx= convolve_image(im, gx, 0);
    image Gy= convolve_image(im, gy, 0);
    image *sobel = calloc(2, sizeof(image));
    sobel[0]=make_image(im.w,im.h,1);
    sobel[1]=make_image(im.w,im.h,1);

    for (int i = 0; i < im.w * im.h; i++) {
        float magnitude = sqrtf(Gx.data[i]*Gx.data[i] + Gy.data[i]*Gy.data[i]);
        float gradient = atan2(Gy.data[i], Gx.data[i]);
        sobel[0].data[i] = magnitude;
        sobel[1].data[i] = gradient;
    }
    return sobel;
}


image colorize_sobel(image im)
{
    // TODO
image *cosob = sobel_image(im);
  feature_normalize(cosob[0]);
  feature_normalize(cosob[1]);
  image color = make_image(im.w, im.h, 3);
  for (int k= 0; k < color.c; k++) {
    for (int j = 0; j < color.h; j++) {
      for (int i = 0; i < color.w; i++) {
        if (k) {
          color.data[i+ j*im.w + k*im.w*im.h] = cosob[0].data[i + j*im.w];
        }
        else {
          color.data[i + j*im.w + k*im.w*im.h] = cosob[1].data[i + j*im.w];
        }
      }
    }
  }
  hsv_to_rgb(color);
  return convolve_image(color, make_gaussian_filter(1), 1);
}

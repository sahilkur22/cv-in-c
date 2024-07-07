#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    if(x<0){
        x=0;
    }
    if(x>=im.w){
        x=im.w-1;
    }
     if(y<0){
        y=0;
    }
    if(y>=im.h){
        y=im.h-1;
    }
     if(c<0){
        c=0;
    }
    if(c>=im.c){
        c=im.c-1;
    }
     int index=c*im.h*im.w + y*im.w + x;
    float pixel_value=im.data[index];
    return pixel_value;
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    if(x<0||x>=im.w||y<0||y>=im.h||c<0||c>=im.c){
        return;
    }else{
    int index=c*im.h*im.w + y*im.w + x;
    im.data[index]=v;
         }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for(int i=0;i<im.c;i++){
    for(int j=0;j<im.h;j++){
    for(int p=0;p<im.w;p++){
        copy.data[i*im.h*im.w + j*im.w + p]=im.data[i*im.h*im.w + j*im.w + p];
    }    
    }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int i=0;i<im.h;i++){
        for(int j=0;j<im.w;j++){
            gray.data[i*im.w+j]=0.299*im.data[i*im.w+j]  + 0.587*im.data[im.w*im.h+i*im.w+j]  + 0.114*im.data[2*im.w*im.h+i*im.w+j];
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int i=0;i<im.h;i++){
        for(int j=0;j<im.w;j++){
            im.data[c*im.h*im.w + i*im.w + j]+=v;
        }
    }
}

void clamp_image(image im)
{
    // TODO Fill this in
     for(int i=0;i<im.c;i++){
    for(int j=0;j<im.h;j++){
    for(int p=0;p<im.w;p++){
       if(im.data[i*im.h*im.w + j*im.w + p]<0){
        im.data[i*im.h*im.w + j*im.w + p]=0;
       }
        if(im.data[i*im.h*im.w + j*im.w + p]>1){
        im.data[i*im.h*im.w + j*im.w + p]=1;
       }
    }    
    }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    for(int i=0;i<im.h;i++){
        for(int j=0;j<im.w;j++){
            float r=im.data[i*im.w+j];
            float g=im.data[im.w*im.h+i*im.w+j];
            float b=im.data[2*im.w*im.h+i*im.w+j];
            float V=three_way_max(r,b,g);
            float m=three_way_min(r,b,g);
            float C=V-m;
            float S,H;
            if(V==0){
                 S=0;
            }else{
                 S=C/V;
            }
            if(C==0){
                H=0;
            }else if(V==r){
                H=(g-b)/C;
            }else if(V==g){
                H=(b-r)/C + 2;
            }else{
                H=(r-g)/C + 4;
            }
            if(H<0){
                H=H/6 +1;  
          }else{
            H/=6;
          }
          im.data[i*im.w+j]=H;
        im.data[im.w*im.h+i*im.w+j]=S;
        im.data[2*im.w*im.h+i*im.w+j]=V;
        }
    }

}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
   for(int i=0;i<im.h;i++){
        for(int j=0;j<im.w;j++){
            float H=im.data[i*im.w+j];
            float S=im.data[im.w*im.h+i*im.w+j];
            float V=im.data[2*im.w*im.h+i*im.w+j];
            float H1=H*6;
            float a=floor(H1);
            float f=H1-a;
            float C=V*S;
            float X1=V*(1-S*f);
            float X2=V*(1-S*(1-f));
            float r,b,g;
            float m=V-C;
            if(H1>=0 && H1<1){
             r=V;
             g=X2;
             b=m;
            }else if(H1>=1 && H1<2){
             r=X1;
             g=V;
             b=m;
            }else if(H1>=2 && H1<3){
             r=m;
             g=V;
             b=X2;
            }else if(H1>=3 && H1<4){
             r=m;
             g=X1;
             b=V;
            }else if(H1>=4 && H1<5){
             r=X2;
             g=m;
             b=V;
            }else{
             r=V;
             g=m;
             b=X1;
            }
            im.data[i*im.w+j]=r;
            im.data[im.w*im.h+i*im.w+j]=g;
            im.data[2*im.w*im.h+i*im.w+j]=b;

        }
   }
}

void scale_image(image im, int c, float v){
    for(int i=0;i<im.h;i++){
        for(int j=0;j<im.w;j++){
            im.data[c*im.h*im.w + i*im.w + j]=(v)* im.data[c*im.h*im.w + i*im.w + j];
        }
    }
}
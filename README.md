# cv-in-c

This repository contains the implementation of a Computer Vision (CV) Library in C under the project offered by Stamatics, IITK (based on the online course by [pjreddie](https://pjreddie.com/courses/computer-vision/)).

The library codebase is incremental (i.e. code of `hw1` is included in `hw2`)

## Directory Structure

The `hw1` and `hw2` submodules contain the implemented code, test results & further details respective to the following topics :

### [Homework 1: Fun with Color!] [based on](https://github.com/pjreddie/vision-hw0)

> This homework involves working with image processing in C, focusing on manipulating images through a provided library. The tasks include understanding the basic image structure and functions for loading, saving, and creating images. Mentees will implement functions for getting and setting pixel values with bounds checking and clamp padding, copying images, converting images to grayscale using weighted sums, shifting image colors, and clamping image values to ensure they remain within a specified range. Additionally, mentees will work with color space transformations, converting images between RGB and HSV formats, and optionally, improve image saturation adjustments by scaling instead of shifting. For extra credit, mentees can implement the RGB to HCL color space conversion for better perceptual accuracy.

### [Homework 2: Resizing and Filtering] [based on](https://github.com/pjreddie/vision-hw1)

> This assignment involves building upon your image processing library from Homework 1 to include image resizing, filtering, and hybrid image creation. The assignment focuses on implementing nearest-neighbor and bilinear interpolation methods for resizing images, creating and applying box and Gaussian filters for image convolution, and developing high-pass, sharpen, and emboss filters. Additionally, mentees will explore hybrid images by combining low and high-frequency components from different images, and implement Sobel filters to estimate image gradients and create a colorized representation.

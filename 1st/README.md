# Filters, convolutions, and cross-correlation

## Part 1. Convolutions

### Task #1

Implement `conv_nested` function that is a naive implementation of convolution which uses 4 nested for-loops. It takes an image `I` and a kernel `k` as inputs and outputs the convolved image `f○h` that has the same shape as the input image. Assume that pixels that outside of source images borders have intensity 0. Test your `conv_nested` function on a real image using gaussian kernel (3x3).
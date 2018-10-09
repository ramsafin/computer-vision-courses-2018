# Filters, convolutions, and cross-correlation

## Part 1. Convolutions

### Task #1

Implement `conv_nested` function that is a naive implementation of convolution which uses 4 nested for-loops. It takes an image `I` and a kernel `k` as inputs and outputs the convolved image `f○h` that has the same shape as the input image. Assume that pixels that outside of source images borders have intensity 0. Test your `conv_nested` function on a real image using gaussian kernel (3x3).

## Part 2. Cross-correlation

### Task #1

Cross-correlation can be used to look for templates in images. Implement finding the template on the shelf using cross-correlation.

`Note!` The template is located in the 1st row of the shelf (the 2nd element from the left).

`Question.` Is it able to detect the template correctly?
<details>
  <summary>Answer</summary>
  
  _No, it cannot properly detect the template._
  
  _However, found area is really close to the actual location of the template in the picture._
</details>

---

_Shelf_:
![shelf](pictures/shelf.png)

_Template_:

![template_cereals](pictures/template.jpg)

### Task #3 (optional)
In previous task try implementing zero-mean cross-correlation (subtract the mean value of the template so that it has zero mean).

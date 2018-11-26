# Periodic Noise Removal

#### This C++ program will remove the periodic noise that corrupts a given input image.
<br />

Consider the following image corrupted with 2D cosinal noise:

![boy_noisy.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/boy_noisy.png)

<br />

By first performing a Discrete Fourier Transformation on the image, the power spectrum density can be obtained which will isolate the points of interest in the image.

![boy_spec.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/boy_spec.png)

The image spectrum.

<br/>

![PSD.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/PSD.png)

The image PSD.


Though it's hard to see, there are 4 symmetrical white dots in both of the previous images that indicate the periodic noise corrupting our image. Using the image editing program Gimp, I manually located the xy-coordinates of these ponts and created a notch reject filter around these points using code. The location of the points of interest are more apparent in the filter.

![filter.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/filter.png)

The notch reject filter.

Now with the filter created, the filter is then multiplied with the DFT of the original image. After performing this multiplication the Inverse-DFT is performed and we have the resulting image:

![result.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/result.png)

# Periodic Noise Removal

#### This C++ program will remove the periodic noise that corrupts a given input image.
<br />

Consider the following image corrupted with 2D cosinal noise:

![boy_noisy.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/boy_noisy.png)

<br />

By first performing a Discrete Fourier Transformation on the image, the power spectrum density can be obtained which will isolate the points of interest in the image.

![boy_spec.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/boy_spec.png)
<br/>
The image spectrum.
![PSD.png](https://github.com/brandonmain/Image-Processing/blob/master/Frequency-Filtering/periodic-noise-removal/images/PSD.png)
<br/>
The image PSD.

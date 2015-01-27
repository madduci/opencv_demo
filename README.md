# OpenCV Examples - 1.0.0

### Authors / Contributors

**Michele Adduci**
, Research Associate @ 
Humboldt Universität zu Berlin - Computer Vision Dept.

Any additional contribution with demos and examples is welcome.

----------

### What is this repository for?

This repository contains examples related to Image Processing, as part of Computer Vision lectures of Winter Semester 2014/15,
directed by Prof. Dr. rer. nat. **R. Reulke**

----------

### What are the examples contained in this repository?

- **Basic Operations**
	- binarization - shows the thresholding functions applied to an image (Binary, Binary Inverted, Truncate, To Zero, To Zero Inverted)
	- conversions - shows some color conversions available in OpenCV (Grayscale, HSV, HLS, Lab, YUV)
	- dilation    - demonstrates the dilation operator
	- erosion     - demonstrates the erosion operator
	- smoothing   - shows the smoothing filters applied to an image (Median, Gaussian, Bilateral, Homogeneous)

----------

- **Feature Extraction**
	- BRISK
	- ORB
	- SIFT
	- SURF

----------

- **Image Processing**
	- canny_edge - shows the Canny Edge detector
	- gradients  - shows the available image gradients operations available in OpenCV (Sobel, Laplacian, Scharr)
	- histograms - shows the histograms of an image, changing brightness and contrast
	- watershed  - shows the watershed segmentation algorithm applied to an image

----------

- **Object Detection**
	- face_detection    - shows the Face Detection algorithm using Haar Cascade Feature Histograms	
	- template_matching - demonstrates the Template Matching using Histograms

----------
	
### What do I need to compile the examples? 

Tools/Dependencies needed:

* C++11 compiler - **Linux**: g++ (4.8+) / **MS Windows**: Visual Studio (2012+)
* CMake 2.8.11+
* OpenCV 2.4.8+ (stable or development version)

----------

### How do I compile and run the examples? 

#### Linux

##### Compile:
    mkdir ~/opencv_examples && cd ~/opencv_examples
    cmake -DCMAKE_BUILD_TYPE=Release /path/to/this/downloaded/repository
    make -j4 && make install

##### Run:
    cd ~/opencv_examples/install/bin/
	cv_binarization test_data/btor.jpg    

#### Windows

##### Compile:
Using CMake Gui, set source and build directories

Set the variable CMAKE_BUILD_TYPE to Release

Open **OpenCV Examples.sln** with MS Visual Studio and then press F7.

Select subproject *INSTALL* -> right click -> *Project Only* -> *Build Only INSTALL*

##### Run:
From command prompt (**Win+R** and then type **cmd.exe**)

    cd path\to\build\folder
	cd install\bin
	cv_binarization.exe test_data\btor.jpg
# EE569 Homework Assignment #1
# Date:        2019/1/21
# Name:        Jiazhi Li
# ID:          5715388761
# email:       jiazhil@usc.edu

CC: Visual Studio C++
LN: Visual Studio C++


1.	Structure of code
There are two classes used in the whole program. One is Imagedata which involves some function of image operation. The other one is Kernel which involves some function of filter operation. 
Imagedata.h involves the declaration of all imagedata function. And the definitions are in the Imagedata.cpp.
Kernel.h involves the declaration of all kernel function. And the definitions are in the Kernel.cpp.
What’s more, the main.cpp involves all allocations of different function to finish different missions followed by Homework guideline.



2.	How to compile
#Method A:
Use the Visual Studio to open Problem1.sln in Problem1 folder. In property manager, open the |Properties| for |Debug | x64| and change |Common Properties – Debugging – Command Arguments| in this format:
##Case 1: Image path
Input the image by the image path. Default height and width is 400, and default bytesperpixel is 1.
##Case 2: Image path 390 300
Input the image by the image path. Set height to be 300 and width to be 390. The default bytesperpixel is 1.
##Case 3: Image path 390 300 3
Input the image by the image path. Set height to be 300, width to be 390 and bytesperpixel to be 3.
After that, just use Debug | x64 to compile the code!!!
#Method B: 
If you don’t use Visual Studio, there are all C++ source code in C++ Source code folder. You can compile it with other compilers. 
After that, for window OS, use “win + R” and type “cmd” to open the command. Use “cd” to find and open the main.exe after compiling and link. Then type the command as above-mentioned in three formats. 



3.	More explanation
Error for “fopen” and “fopen_s” 
Solution: In property manager, open the Properties for Debug | x64 and change Common Properties – C/C++ - Preprocessor – Preprocessor Definitions, and add a new term “_CRT_SECURE_NO_DEPRECATE” to it. Then the problem is solved. 



4.	Other code
There are other MATLAB codes in Other MATLAB code folder.
#Plot_Uniform.m in Uniform folder
It is used to plot the figure about the relationship between window size N and PSNR for Uniform filter.
#Plot_Gaussian.m in Gaussian folder
It is used to plot the figure about the relationship between window size N and PSNR for Gaussian filter.
#main.m in Shot_noise_BM3D folder
Allocate some function for BM3D.
# Anscombe_forward.m 
# Anscombe_reverse_biased.m
# Anscombe_reverse_unbiased.m
It is used for Anscombe transformation and Anscombe inverse transformation.
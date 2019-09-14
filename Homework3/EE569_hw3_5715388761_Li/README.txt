# EE569 Homework Assignment #3
# Date:        2019/3/1
# Name:        Jiazhi Li
# ID:          5715388761
# email:       jiazhil@usc.edu

CC: Visual Studio C++
LN: Visual Studio C++


1.	Structure of code
There are four classes used in the whole program. The first one is Imagedata which involves some function of image operation. The second one is Kernel which involves some function of filter operation. The third is Algorithm which involves some helpful algorithm. The fourth is Patterntree to construct the pattern binary search tree.
Imagedata.h involves the declaration of all imagedata function. And the definitions are in the Imagedata.cpp.
Kernel.h involves the declaration of all kernel function. And the definitions are in the Kernel.cpp.
Algorithm.h involves the declaration of all algorithm. And the definitions are in the Kernel.cpp.
Patterntree.h involves the declaration of all patterntree algorithm. And the definitions are in the Patterntree.cpp.
What’s more, the main.cpp involves all allocations of different function to finish different missions followed by Homework guideline.



2.	How to compile
#Method A:
Use the Visual Studio to open Homework3.sln in Problem1 folder. In property manager, open the |Properties| for |Debug | x64| and change |Common Properties – Debugging – Command Arguments| in this format:
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
# Reverse_mapping_function.m in Mapping function for spatial warping folder
Figure out the reverse mapping function for spatial warping.
# Forward_mapping_function.m in Mapping function for spatial warping folder
FIgure out the forward mapping function for spatial warping.

Distortion_main.m in linear regression folder
Figure out the linear regression solution.

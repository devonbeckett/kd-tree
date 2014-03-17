CS 283 Final Project Using K-D Trees
====================================

Compile
-------

To compile run 'make server' or 'make hw4kdex'.

Run
---
To run the server, run './server [port] [files]' where [port] is the port number the server will bind to and [files] are all of the files that will be used to build the search tree of images. The formate used to request an image from the server is:

    [server address]:[port]/?f=getImageByClolor&c=[r]/[g]/[b]

where [r] is the decimal red value, [g] is the decimal green value, and [b] is the decimal blue value. Here is an example:

    http://tux64-13.cs.drexel.edu:8555/?f=getImageByColor&c=200/12/164

To run the image converter(hw4kdex) run './hw4kdex [source img] [columns] [rows] [images]' where [source img] is the image to be converted, [columns] are the number of 64 pixel wide columns are in the [source img], [rows] is the number of 64 pixel tall rows are in the [source img], and [files] are all of the files that will be used to build the search tree of images.

Dependencies
------------
This project relies of the following libraries:
* OpenCV
* OpenMP

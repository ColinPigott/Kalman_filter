# Kalman Filter Examples

## Introduction

These are C/C++ implementations of the Kalman filter examples on the following website:

                        https://www.kalmanfilter.net/default.aspx

## To Build

These examples have been built and tested on Ubuntu Linux.

The build instructions for each example are at the top of the source files.

**N.B. Files example09.cpp and example10.cpp use the eigne library and that has to be installed before these are built. During the build process, the location of this library is passed to the compiler. For the example09.cpp and example10.cpp, the location is:**

                        /home/linuxbox/eigen-3.4.0

**The eigen library installation details can be found at:**

                        https://eigen.tuxfamily.org/index.php?title=Main_Page


## Common Issues

Source files example09.cpp and example10.cpp do not build (see above section).

**Have you installed the eigen library first**(https://eigen.tuxfamily.org/index.php?title=Main_Page)?
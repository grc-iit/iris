
# Introduction

There is an ocean of available storage solutions in modern high performance and distributed systems. These solutions consist of Parallel File Systems (PFS) for the more traditional high-performance computing (HPC) systems and of Object Stores for emerging cloud environments. More often than not, these storage solutions are tied to specific APIs and data models and thus, bind developers, applications, and entire computing facilities to using certain interfaces. Each storage system is designed and optimized for certain applications but does not perform well for others. Furthermore, modern applications have become more and more complex consisting of a collection of phases with different computation and I/O requirements. In this paper, we propose a uni€ed storage access system, called IRIS (i.e., I/O Redirection via Integrated Storage). IRIS enables uni€ed data access and seamlessly bridges the semantic gap between file systems and object stores. With IRIS, emerging High-Performance Data Analytics software has capable and diverse I/O support. IRIS can bring us closer to the convergence of HPC and Cloud environments by combining the best storage subsystems from both worlds. Experimental results show that IRIS can grant more than 7x improvement in performance than existing solutions.

# Who uses

It is used for integrated storage access for FILE to Object or vice-versa

# How it works

- Iris contains a library (libiris) which transparently intercepts all POSIX and HDF5 calls.
    

# Dependencies

-   Cmake > 2.8
-   Gcc > 5.1
-   MPICH > 3.2
-   HDF5 > 8.1
-   libbson
-   MongoDB
-   OrangeFS
   

# Installation

## Cmake

`mkdir build && cd build`
`cmake ../`
`make -j8 && make install`

# Usage

## Library

Applications need to link their executable with libiris. Internally, Iris lib intercepts file operations (fopen,fclose, etc.) defined using POSIX and HDF5 calls of the applications.

# Running Tests

## Scripts

`./scripts/preparepfsData.sh`
`./scripts/mappingTests.sh`

# License:

# Acknowledgments:
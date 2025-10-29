#!/bin/sh
for i in cmake_install.cmake CMakeCache.txt Makefile; do rm cmake/.build/$i; done

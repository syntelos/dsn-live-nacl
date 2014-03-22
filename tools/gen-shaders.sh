#!/bin/bash

if javac -g GenerateShaders.java
then
    java GenerateShaders ../Shaders.h ../shaders
else
    exit 1
fi

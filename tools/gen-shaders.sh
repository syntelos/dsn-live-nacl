#!/bin/bash

if [ -f GenerateShaders.class -a GenerateShaders.class -nt GenerateShaders.java ]|| javac -g GenerateShaders.java
then
    java GenerateShaders ../Shaders.h ../shaders
else
    cat<<EOF
$0: Failed to compile GenerateShaders.java using
    javac -g GenerateShaders.java
EOF
    exit 1
fi

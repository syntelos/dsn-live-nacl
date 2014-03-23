#!/bin/bash

fv3_jar=$(ls fv3-*.jar)

if [ -n "${fv3_jar}" ]&&[ -f "${fv3_jar}" ]
then

    if [ -f GenerateFont.class -a GenerateFont.class -nt GenerateFont.java ]|| javac -cp "${fv3_jar}" -g GenerateFont.java
    then
        java  -cp ".:${fv3_jar}" GenerateFont futural ../FontFutural.h ../FontFutural.cc
    else
        cat<<EOF
$0: Failed to compile GenerateFont.java using
    javac -cp "${fv3_jar}" -g GenerateFont.java
EOF
        exit 1
    fi

else
    cat<<EOF>&2
Error missing fv3-X.Y.Z.jar
EOF
    exit 1
fi

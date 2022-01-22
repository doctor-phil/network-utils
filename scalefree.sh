#!/bin/bash

if [ "$1" != "" ]; then
    ./scalefree $1
else
    ./scalefree
fi

Rscript plotgraph.r >& /dev/null
xdg-open Rplots.pdf

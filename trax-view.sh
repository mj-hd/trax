#!/bin/sh

trax="./out/bin/trax"
trax_viewer="./trax-viewer/out/bin/trax-viewer"

if [ ! -e $trax ]; then
    make
fi

if [ ! -e $trax_viewer ]; then
    cd ./trax-viewer/
    make
    cd ../
fi

cd ./trax-viewer/
`../$trax $@ | ../$trax_viewer`
cd ../

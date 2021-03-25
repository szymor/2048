#!/bin/sh

cd ipk
cd data && tar cvzf ../data.tar.gz *
cd ../control && tar cvzf ../control.tar.gz *
cd .. && ar rv build.ipk control.tar.gz data.tar.gz debian-binary
rm data.tar.gz control.tar.gz
rm -rf ./data/home/retrofw/games/2048/assets ./data/home/retrofw/games/2048/2048.dge
mv build.ipk ..
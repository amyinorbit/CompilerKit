#!/usr/bin/env zsh

ROOT_DIR=$(pwd)
OUT_DIR=$ROOT_DIR
DOC_DIR=$ROOT_DIR/docs

INFO_FILE=version.txt

GIT_REV=$(git describe --tags --always)
# GIT_REV=$(git rev-parse --short --verify HEAD)
BUILD_ID="$(date +"%m%d")-$GIT_REV"
BUILD_ZIP="compilerkit"

echo $BUILD_ID > $INFO_FILE
echo "Packaging..."
cd $DOC_DIR
make
cd $OUT_DIR
zip -x ".*" -x "__MACOSX" -rq  $BUILD_ZIP \
    src/CompilerKit \
    $INFO_FILE \
    README.md \
    LICENSE \
    makefile \
    docs/*.html \
    docs/*.css
rm -f $INFO_FILE
cd $DOC_DIR
make clean

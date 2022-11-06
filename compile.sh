#!/bin/bash

file=""
lib=""

run_help() {
  make help;
  exit 1
}

while getopts f:l:h flag
  do
  case "${flag}" in
    f) file="file=${OPTARG}";;
    l) lib="lib=${OPTARG}";;
    h) run_help
  esac
done
if test -z ${file}; then
  echo "Flaga -f *nazwa pliku* jest wymagana!"
  exit 1
fi

make compile $file $lib

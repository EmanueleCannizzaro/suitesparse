#!/bin/bash

project="$(basename "$(dirname `pwd`)")"

find ./ -size  0 -name "*.out" |xargs -i rm {}
find ../matrix/ -name "*.rb" -printf "%f\n" | xargs -i `(printf "touch %s_%s.out\n" "${project}_i_demo" "{}")`
find ../matrix/ -name "*.rb" -printf "%f\n" | xargs -i `(printf "touch %s_%s.out\n" "${project}_l_demo" "{}")`





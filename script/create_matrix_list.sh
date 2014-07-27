#!/bin/bash

rm *.rb

find /media/emanuele/bc147eda-8133-4867-8b31-ef874031c80a/backup/localhost/htdocs/fea.org.uk/matrix/cise/all/ -size -4k -name "*.rb" -printf "%f\n" | xargs -i `printf "ln -s %s %s\n" "../../matrix/{}" "./"`

rm EternityII_A_b.rb
rm light_in_tissue_Q.rb

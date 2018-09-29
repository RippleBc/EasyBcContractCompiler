#!/bin/bash

NOWDATE=`date +%0Y%0m%0d%H%M`

rm -rf html
doxygen compiler.Doxyfile
tar czvf /tmp/html.tgz html

cd /tmp
cvs co compiler
tar czvf compiler-$NOWDATE.tgz compiler
rm -rf compiler

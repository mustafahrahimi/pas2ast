#!/bin/sh

for i in TestSuite/*.pas; do
	echo "testing $i"
	./parser <  $i
done

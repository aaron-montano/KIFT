#!/bin/sh

say -v Daniel Please type something to search

read F1
F=`echo $F1 | sed s/\ /+/g`

open "http://www.google.com/search?fulltext=Search&=Google&q=$F"

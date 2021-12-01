#/bin/bash
gcc `xml2-config --cflags` REP01.c address.c io.c -o REP01 `xml2-config --libs`;
./REP01;

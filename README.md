# Multiple Alignment Block Recognizer

## Requirements

 1. Unix-like environment
 2. EMBOSS development packages installed


## Build & Install

```
mkdir build
cd build
cmake ..
make
sudo make install
```

## Notice on EMBOSS integration

The software assumes EMBOSS installed in `/usr` prefix. In other case,
move `mabr.acd` into proper EMBOSS acd resources location.


## Command line options

```
Standard (Mandatory) qualifiers:
    [-alignment]    seqall      Sequence(s) filename and optional format, or
                                reference (input USA)

Additional (Optional) qualifiers:
    -datafile       matrixf     [EBLOSUM62 for protein, EDNAFULL for DNA]
                                Matrix file

Advanced (Unprompted) qualifiers:
    -tcol           float       [0.0] Conservative column score thereshold
                                float value (Number from -100.000 to 100.000)
    -trow           float       [0.0] Acceptable row score thereshold
                                float value (Number from -100.000 to 100.000)
    -tbcol          integer     [1] Maximum acceptable block width
                                integer value (Integer 1 or more)
    -tbr            integer     [1] Maximum acceptable block heiht
                                integer value (Integer 1 or more)
    -tbsquare       integer     [6] Maximum acceptable block square
                                integer value (Integer 1 or more)

General qualifiers:
    -help           boolean     Report command line options and exit. More
                                information on associated and general
                                qualifiers can be found with -help -verbose
```

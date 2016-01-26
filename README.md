# Multiple Alignment Block Recognizer

## Requirements

 1. Unix-like environment
 2. EMBOSS development packages installed


## Build & Install

```mkdir build
cd build
cmake ..
make
sudo make install
```

## Notice on EMBOSS integration

The software assumes EMBOSS installed in `/usr` prefix. In other case,
move `mabr.acd` into proper EMBOSS acd resources location.

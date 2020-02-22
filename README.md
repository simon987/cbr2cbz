# cbr2cbz

Convert a .cbr file to a .cbz file without modifying the original document.

## Usage

```bash
cbr2cbz file1.cbr file2.cbr ...
```

**Convert all files in a directory**
```bash
cbr2cbz /path/to/comics/*.cbr
cbr2cbz /path/to/comics/**/*.cbr
```

**Convert all files in a directory (multithreaded)**
```bash
find /path/to/comics/ -name '*.cbr' | parallel -j4 cbr2cbz {}
```

## Build from source
```bash
cmake .
make
```

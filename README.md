# cbr2cbz

[![Development snapshots](https://ci.simon987.net/app/rest/builds/buildType(Cbr2cbz_Build)/statusIcon)](https://files.simon987.net/artifacts/Cbr2cbz/Build/)

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

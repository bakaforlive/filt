## About
Filt is a CLI text filter.

## Usage
```bash
$ ./filt {parameter 1} {parameter 2} < {file}
```
or
```bash
$ ./filt {parameter 1} {parameter 2}
{your input here}
```

## Build
To build filt, you need to install C compiler (e.g. clang, gcc) with your package manager.

```bash
# Arch Linux
sudo pacman -S gcc

git clone https://github.com/bakaforlive/filt.git
cd filt
gcc filt.c -o filt
```

Or you can install it [manually](https://gcc.gnu.org/install/).

## Parameters
seek - SEEK for a specified characters.
- digits
- letters
- spaces
- capital-letters
- lowercase-letters
- punctuation

change - CHANGE the format.
- letters-lower - formats any capital letters to lower.
- letters-upper - vice versa. Formats any lowercase letters to uppercase.

## Roadmap
Currently, this project will get new features over time.

- [ ] Implement fun features (change text into binary/gibberish)

## Contributing

PRs and issues are welcome. Fork the repo, create a branch, and submit a pull request.

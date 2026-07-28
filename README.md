## About
Filt is a CLI text filter written in Pascal.

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
To build filt, you need to install fpc (Free Pascal Compilator) with your package manager.

```bash
# Arch Linux
sudo pacman -S fpc

git clone https://github.com/bakaforlive/filt.git
cd filt
fpc filt.pas
```

Or you can install it [manually](https://www.freepascal.org/).

## Roadmap
Currently, this project will get new features over time.

- [ ] Implement fun features (change text into binary/gibberish)

## Contributing

PRs and issues are welcome. Fork the repo, create a branch, and submit a pull request.

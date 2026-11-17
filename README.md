# my_sudo

A reimplementation of the `sudo` command in C: authenticates the caller against `/etc/shadow`, then runs a command with elevated privileges.

## Features

- Password authentication through `/etc/shadow` and `crypt`
- 3 attempts before the program aborts
- Run a command as another user or group
- Spawn a privileged shell
- Optionally preserve the caller's environment

## Build

```bash
make            # build ./my_sudo
make re         # rebuild from scratch
make clean      # remove object and coverage files
make fclean     # also remove the binary
```

The binary must be owned by root and setuid to work:

```bash
sudo chown root:root my_sudo && sudo chmod u+s my_sudo
```

## Usage

```bash
./my_sudo [-u user] [-g group] [-s] [-E] [command [args...]]
./my_sudo -h
```

| Option | Description |
|---|---|
| `-u user` | Run the command as `user` |
| `-g group` | Run the command with `group` privileges |
| `-s` | Open a shell instead of running a command |
| `-E` | Preserve the current environment |
| `-h` | Print usage |

### Examples

```bash
./my_sudo ls /root
./my_sudo -u postgres whoami
./my_sudo -g docker docker ps
./my_sudo -E -s -u postgres
```

## Tests

```bash
make tests_run  # run the Criterion test suite
make cov        # line and branch coverage report
```

Requires [Criterion](https://github.com/Snaipe/Criterion) and `gcovr`.

## Notes

Linux only — it reads `/etc/shadow` and links against `libcrypt`.

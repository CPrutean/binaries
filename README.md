# bin

Personal collection of shell utilities and scripts.

---

## sutil

SSH host manager. Tracks hosts from `~/.ssh/.sshrc` and auto-imports new entries from `~/.ssh/known_hosts`.

```
Usage: sutil [COMMAND] [OPTIONS]

Commands:
  ssh, -s <host>                   Connect to a host by IP or name
  rename, -rn <host> <name>        Assign or change a host's friendly name
  default-user, -du <host> <user>  Set the default SSH user for a host
  user, -u <user>                  Override the SSH user for this session
  list, -l                         List all known hosts
  help, -h                         Show help
```

Run `sutil <command> help` for help on a specific subcommand.

**Examples:**
```bash
sutil list                          # show all known hosts
sutil rename 192.168.1.10 myserver  # give a host a friendly name
sutil default-user myserver ubuntu  # set the default login user
sutil ssh myserver                  # connect using saved user
sutil -u root ssh myserver          # connect as root (this session only)
```

**Host config file:** `~/.ssh/.sshrc` — one entry per line: `<ip> <name> <default_user>`

---

## fields

Print specific whitespace-delimited fields from stdin or a file, similar to `awk '{print $N}'`.

```
Usage: fields <N> [N ...] [-dl <delimiter>] [file]

Options:
  -dl <char>   Field delimiter (default: space)
  -h           Show help
```

**Examples:**
```bash
echo "a b c" | fields 1        # → a
echo "a b c" | fields 1 3      # → a,c
fields 2 -dl , data.csv        # → second column of a CSV
```

---

## pfc

Copy files from Docker containers by container name, ID, or index.

```
Usage: pfc <container> <src-path> <dest-path>
       pfc list_container | -lc
       pfc ls | -ls <index> <path>
       pfc help | -h
```

**Examples:**
```bash
pfc -lc                          # list running containers with their index
pfc mycontainer /app/config .    # copy by container name
pfc 0 /app/logs/out.log .        # copy by index
pfc -ls 0 /app                   # ls a path inside container 0
```

---

## pyenv

Set up a Python virtual environment for a project directory. Scans all `*.py` files for third-party imports, installs them with pip, and writes a `pyrightconfig.json`.

```
Usage: pyenv <directory>
```

Skips setup if a `venv/` directory already exists.

---

## showip

Resolve a hostname to its IPv4 and IPv6 addresses.

```
Usage: showip <hostname>
```

**Example:**
```bash
showip example.com
# IP addresses for example.com:
#  IPv4: 93.184.216.34
```

Source: `showip.c` — compile with `gcc showip.c -o showip`.

---

## clearc

Reset the practice C file at `~/Code/practice/main.c` to a minimal boilerplate.

```
Usage: clearc
```

---

## clearcpp

Reset the practice C++ file at `~/Code/practice/main.cpp` to a minimal boilerplate.

```
Usage: clearcpp
```

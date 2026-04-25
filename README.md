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

---

## hex_to_int

Decode raw hex bytes from stdin into typed values. Reads a space-separated hex byte sequence and interprets segments as the specified C types in order.

```
Usage: echo "<hex bytes>" | hex_to_int <num_bytes> [type ...]

Supported types: int16_t, uint16_t, int32_t, uint32_t, int8_t, uint8_t, Float
```

**Examples:**
```bash
echo "01 00" | hex_to_int 2 int16_t               # → [int16: 1]
echo "00 00 80 3F" | hex_to_int 4 Float            # → [float: 1.00]
echo "01 00 FF 7F" | hex_to_int 4 int16_t int16_t  # → [int16: 1] [int16: 32767]
```

Source: `hex_translator.c` — compile with `gcc hex_translator.c -o hex_to_int`.

---

## int16_to_float

Convert a raw int16 integer (read from stdin) to a float divided by 100. Useful for decoding fixed-point sensor values.

```
Usage: echo "<int16 value>" | int16_to_float
```

**Examples:**
```bash
echo "1234" | int16_to_float   # → 12.340000
echo "-500" | int16_to_float   # → -5.000000
```

Source: `int16_to_float.c` — compile with `gcc int16_to_float.c -o int16_to_float`.

---

## parse_can

Parse a CAN bus log file and decode messages using an optional translation file. Identifies each packet as SEND or RECV based on address prefix, maps command IDs to descriptions, and decodes payload bytes into typed values.

```
Usage: parse_can -f <can_log> [-t <translation_file>]

Options:
  -f <file>   CAN log file to parse
  -t <file>   Translation file (pipe-delimited: COMMAND_ID|DESCRIPTION|DATA_TYPES)
```

Translation file format (first line is header):
```
COMMAND_ID|DESCRIPTION|RESULTING_DATA_TYPES
0x30|Read PID Parameter Command|Float
0x42|Read Acceleration Command|int32_t
```

**Example:**
```bash
parse_can -f can_test.txt -t test_translation.txt
```

---

## amps_to_float

Decode motor current (amp) values from a CAN log file. Filters for "Motor Status 2" packets, converts the raw int16 payload via `int16_to_float`, and maps CAN addresses to motor IDs.

```
Usage: amps_to_float
```

Reads `can_test.txt` in the current directory and uses `parse_can`, `int16_to_float`, and `fields` internally.

---

## todo

Command-line task manager. Tasks are stored persistently and support priorities, tags, and descriptions.

```
Usage: todo <command> [options]

Commands:
  add <title> [options]   Create a new task
  list [options]          List tasks
  show <id>               Show task details
  done <id>               Mark task as done
  delete <id>             Delete a task
  help                    Show this help

Add options:
  --desc <text>           Task description
  --priority <0-5>        Priority level (default: 0)
  --tags <t1,t2,...>      Comma-separated tags

List options:
  --tag <name>            Filter by tag
  --priority <0-5>        Filter by priority
  --done                  Show only completed tasks
  --pending               Show only pending tasks
```

**Examples:**
```bash
todo add "Fix login bug" --priority 3 --tags backend,auth
todo list --pending
todo list --tag backend
todo done 1
todo show 2
```

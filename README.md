# table-printer
Linux file content manipulation utility for printing formatted table for better readability

## Motivation

Have you ever tried reading a config file that was in `csv` format and had trouble getting any useful information out of
it at first glance. This utility will format the table and color it so that it is easy to read and get sense of what you
are looking at.

### Example:
> #### Before
> ```
> root:x:0:0:root:/root:/bin/bash
> daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
> bin:x:2:2:bin:/bin:/usr/sbin/nologin
> sys:x:3:3:sys:/dev:/usr/sbin/nologin
> sync:x:4:65534:sync:/bin:/bin/sync
> games:x:5:60:games:/usr/games:/usr/sbin/nologin
> man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
> lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
> mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
> news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
> uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
> proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
> www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
> ```
> #### After
> ```
> +----------+---+----+-------+----------+-----------------+-------------------+
> |     root | x |  0 |     0 |     root |           /root |         /bin/bash |
> |   daemon | x |  1 |     1 |   daemon |       /usr/sbin | /usr/sbin/nologin |
> |      bin | x |  2 |     2 |      bin |            /bin | /usr/sbin/nologin |
> |      sys | x |  3 |     3 |      sys |            /dev | /usr/sbin/nologin |
> |     sync | x |  4 | 65534 |     sync |            /bin |         /bin/sync |
> |    games | x |  5 |    60 |    games |      /usr/games | /usr/sbin/nologin |
> |      man | x |  6 |    12 |      man |  /var/cache/man | /usr/sbin/nologin |
> |       lp | x |  7 |     7 |       lp |  /var/spool/lpd | /usr/sbin/nologin |
> |     mail | x |  8 |     8 |     mail |       /var/mail | /usr/sbin/nologin |
> |     news | x |  9 |     9 |     news | /var/spool/news | /usr/sbin/nologin |
> |     uucp | x | 10 |    10 |     uucp | /var/spool/uucp | /usr/sbin/nologin |
> |    proxy | x | 13 |    13 |    proxy |            /bin | /usr/sbin/nologin |
> | www-data | x | 33 |    33 | www-data |        /var/www | /usr/sbin/nologin |
> +----------+---+----+-------+----------+-----------------+-------------------+
> ```

## Installation

#### Download precompiled binary

> Go to https://github.com/dev-null-undefined/table-printer/releases/latest
> under assets download the table-printer binary
> set the execution bit using `chmod +x table-printer`
> and then you should be able to run it using relative path `./table-printer` or moving to for example `/usr/local/bin`
> `mv table-printer /usr/local/bin`

#### Clone the project and compile it your self

> This can be done using cmake with following command
> ```shell
> git clone https://github.com/dev-null-undefined/table-printer
> cd table-printer
> cmake .
> cmake --build .
> ```

## Usage

table-printer has build in help menu that can be accessed by using the `--help` argument which will print this menu

```
Usage: table [OPTION]... FILE
Formats FILE, or standard input, to standard output.

  -C, --counter      prefix each line of output with the line number
  -h, --header       treats the first line as header and separates it
  -v, --version      display the version of table
  -f, --frame        print a frame around the output
  -c, --colors       use colors in the output
  -H, --help         display this help
  -r, --align-right  align text to the right side of the frame
  -o, --output-file  output to file instead of stdout
  -F, --force        used to override output file if file exists
  -d, --delimiter    delimiter char to separate fields
```

Feel free to fork this repo and make any changes or file issue with suggestion.

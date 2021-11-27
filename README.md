# table-printer
Linux file content manipulation utility for printing formated table for better read ability

## Why 
Have you ever tried reading config file that was in `csv` format and had trouble getting any usefull information out of it at first glance.
This utility will format the table and color it so that it is easy to read and get sense of what each data means.

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

Feel free to fork this repo and make any changes or file issue with suggestion.

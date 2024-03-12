# Root the (Ballot) Box

This is the base system for the e-voting project.

It's not very secure by default. This was _not_ written with best practices
in mind, so in your testing you should see if the base system itself could be
vulnerable to an attack!

## Running the Front-End

The front-end interface to the voting machine is a series of CGI
applications, written in both Bash and in Python. From the root of the
folder, run

```sh
$ make cgi
```

This starts a CGI-aware web server running on port 8000 on the local machine.
Then, using a web browser, go to `http://localhost:8000/cgi-bin/home.cgi` to
access the interface. The default password for the login system is `admin`.
If you wish to add additional CGI scripts, add them to the `cgi-bin/`
directory, making sure you mark them as executable (`chmod 755 file.cgi`). To
exit the CGI server, send a keyboard interupt (`<Ctrl>+C`).

## Running the Back-End

The back-end is a set of C and Python programs that access a database. We
have provided the database software, `sqlite3`, along with `etovucca`, the
interface to it. `sqlite3` is a SQL system much like MySQL (which we used in
class), but simpler. To get started, build the `etovucca` interface. From the
directory root, run:

```sh
$ make
```

This will build both the interface and the `sqlite3` database engine.

Next, you will have to initialize the database file, `rtbb.sqlite3`. Run
(from the directory root):

```sh
$ make initdb
```
This will create the database based on a setup script that we have already
provided. You can then run the `make cgi` command to interface with the
front-end via a web browser, or run the `./etovucca` binary.

If you want to interface with the database directly (using SQL statements),
run:

```sh
$ ./sqlite3 rtbb.sqlite3
```

Information on the CLI can be found [here](https://sqlite.org/cli.html).
Also, please note the `./sqlite3` in the command. The SEED VM has its own
version of `sqlite3`, but you should use the one bundled in this repository.

Happy rooting! Please ask questions on Piazza if you need more help. We may
update this base code as the project evolves.


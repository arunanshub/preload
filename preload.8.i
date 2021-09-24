[SIGNALS]

On receipt of a SIGHUP, the daemon will close and reopen its log file, and
reread the configuratoin file.

On receipt of a SIGUSR1, the daemon dumps the currently loaded configuration
into the log file.

On receipt of a SIGUSR2, the daemon saves its state into the state file.

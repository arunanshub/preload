#!/bin/sh

set -e

> preload.state

echo Testing preload with preconf.conf.debug config file
( sleep 1; killall ./preload 2>/dev/null ) &
./preload -c preload.conf -s '' -d

echo Testing preload with preconf.conf config file
( sleep 1; killall ./preload 2>/dev/null ) &
./preload -c preload.conf -s '' -l '' -f


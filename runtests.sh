#!/bin/sh

set -e

test_debug() {
    ( sleep 1; killall $APPNAME 2>/dev/null ) &
    $APPNAME -c preload.conf -s '' -d
}

test_normal() {
    ( sleep 1; killall $APPNAME 2>/dev/null ) &
    $APPNAME -c preload.conf -s '' -l '' -f
}

main() {
    case $1 in
        debug)
            test_debug
            ;;
        normal)
            test_normal
            ;;
        *)
            return 1
            ;;
    esac
}

main $1

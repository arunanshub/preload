#!/bin/sh

IN="$1"
KEYS="$2"

I='[ \t]*\([^, \t]*\)[ \t]*'
SEDSCRIPT=`sed -e "s/confkey($I,$I,$I,$I,$I)/s@default_\3@\4@g; s@unit_\3@\5@g;/;" < "$KEYS"`

sed -e "$SEDSCRIPT" "$IN"

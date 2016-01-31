#!/bin/sh
../arduino.sh --verbose --upload --port `cat ../port` --board `cat ../board` "$@"

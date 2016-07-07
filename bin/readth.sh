#!/bin/bash

# Usage: readth.sh pin_number

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
TH="$DIR/th"
sudo $TH $1 2>&2

#!/bin/bash
make && time python/run.py
if [[ $# -eq 1 ]]; then time python/makePlots.py; fi
if [[ $# -eq 2 ]]; then time python/createTables.py; fi

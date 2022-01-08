#!/usr/bin/env python
import subprocess

macro = "rf706_histpdf.C"
macro = "rf201_composite.C"

fout = open("tmp.txt", 'w')

with open(macro, 'r') as f:
    for line in f.readlines():
        if not '//' in line:
            fout.write(line)
        else:
            new = line.split('//')[1].strip()
            fout.write("    %s\n" % new)

fout.close()
subprocess.call("cat tmp.txt", shell=True)
#subprocess.call("mv tmp.txt %s" % macro, shell=True)

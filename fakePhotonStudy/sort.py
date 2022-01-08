#!/usr/bin/env python
import subprocess

def sort():
    additional_info = []
    d = {}
    with open ('log.txt', 'r') as fin:
        for line in fin.readlines():
            if '#' in line:
                additional_info.append(line.strip())
                continue
            factor = float(line.split()[-1])
            d[factor] = line.strip()
    
    with open ('tmp.txt', 'w') as fout:
        for info in additional_info:
            fout.write(info + '\n')
        for key in sorted(d.keys()):
            fout.write(d[key] + '\n')
    
    subprocess.call("mv tmp.txt log.txt", shell=True)
    subprocess.call("vim log.txt", shell=True)

if __name__ == "__main__":
    sort()

#!/usr/bin/env python2

def get_efficiency(tag):
    counter, collection = 0, []
    for line in content:
        if tag in line:
            efficiency = float(line.split()[-1].strip())
            if counter>0: collection.append( efficiency )
            counter += 1
    
    print output_tags[tag], ":", collection, ","

if __name__ == "__main__":
    with open("log.txt", 'r') as fin: content = fin.readlines()

    tags = ["SR1", "SR2", "SR3"]
    output_tags = {}
    output_tags[tags[0]] = "raw_M600_M700"
    output_tags[tags[1]] = "raw_M800_M1000"
    output_tags[tags[2]] = "raw_M1100_1200"

    # main
    for tag in tags: get_efficiency(tag)

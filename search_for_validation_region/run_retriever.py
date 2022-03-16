#!/usr/bin/env python
import subprocess
import glob
import helper as h
import metaConditions as m

path = "/afs/cern.ch/user/y/ykao/work/tPrimeExcessHgg/CMSSW_10_6_8/src/tprimetH/plots/log"

def get_summary_of_a_sample(sample):
    d_sum = h.get_empty_dict(sample)

    # sum over three years
    for log in glob.glob( path + "/*%s*" % sample ):
        with open(log, 'r') as fin:
            # use filter
            contents = filter(lambda x: "vs_" in x, fin.readlines())

            for key in m.keywords:
                line = filter(lambda x: key in x, contents)
                line = list(line)[0]

                value = float(line.split(":")[1].split("/")[0])
                total = float(line.split(":")[1].split("/")[1].split()[0])
                d_sum[key]["value"] += value
                d_sum[key]["total"] += total
                #print line, value, total

            continue
            # use nested for loop
            for line in fin.readlines():
                for key in m.keywords:
                    if key in line:
                        value = float(line.split(":")[1].split("/")[0])
                        total = float(line.split(":")[1].split("/")[1].split()[0])
                        d_sum[key]["value"] += value
                        d_sum[key]["total"] += total
                        print line.strip(), value, total

    #h.print_dictionary(d_sum)
    my_big_dictionary[sample] = d_sum

def get_summary(sample):
    summary = map(lambda x: get_summary_of_a_sample(x), m.samples[sample])

if __name__ == "__main__":
    my_big_dictionary = {}
    get_summary("smh")
    get_summary("signal")

    h.merge_dictionary(my_big_dictionary, m.samples["smh"])
    h.print_dictionary(my_big_dictionary)

    #get_summary("nrb")
    #get_summary("data")


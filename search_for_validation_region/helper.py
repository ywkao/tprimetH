#!/usr/bin/env python
import metaConditions as m

def get_empty_dict(sample):
    d = {}
    d["sample"] = sample
    for key in m.keywords:
        d[key] = {}
        d[key]["value"] = 0.
        d[key]["total"] = 0.
    return d

def print_dictionary(d):
    is_dictionary_with_one_sample = "sample" in d.keys()

    # print summary
    if not is_dictionary_with_one_sample:
        samples = m.samples["data"] + ["SMH"] + m.samples["signal"]
        for key in m.keywords:

            if False:
                print "\n%s, yields, total, percentage" % key
                output = map(lambda x: "%18s, %5.2f, %6.2f, %5.2f %%" % (x, d[x][key]["value"], d[x][key]["total"], 100.*d[x][key]["value"]/d[x][key]["total"]), samples)
            else:
                print "\n%s, yields, percentage" % key
                output = map(lambda x: "%12s, %5.2f, %5.1f %%" % (m.convert_signal_title[x], d[x][key]["value"], 100.*d[x][key]["value"]/d[x][key]["total"]), samples)

            for ele in list(output): print ele

    # print one sample
    if is_dictionary_with_one_sample:
        print "\n", d["sample"]
        for key in m.keywords:
            print "%18s, %5.2f, %6.2f, %5.2f %%" % (key, d[key]["value"], d[key]["total"], 100.*d[key]["value"]/d[key]["total"])

def merge_dictionary(d, samples):
    output = get_empty_dict("SMH")
    for s in samples:
        for key in m.keywords:
            output[key]["value"] += d[s][key]["value"]
            output[key]["total"] += d[s][key]["total"]

    #print_dictionary(output)
    d["SMH"] = output

def check(l):
    print l
    for i, e in enumerate(l):
        if i+1 == len(l):
            continue
        else:
            print e - l[i+1]

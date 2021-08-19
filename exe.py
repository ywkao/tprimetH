#!/usr/bin/env python
import subprocess
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("-t", help = "tag = set1, set2, ..., set6, test", type=str)
parser.add_argument("-e", help = "enable to process samples"            , action="store_true")
parser.add_argument("-d", help = "data only"                            , action="store_true")
parser.add_argument("-m", help = "make mvababies; otherwise histograms" , action="store_true")
args = parser.parse_args()

tag = args.t
mission = "--make_histograms" if args.m == False else "--make_mvababies"
execution = "--exe" if args.e == True else ""

def run():
    # examples
    '''
    ./exe.py -e -t set1 # hist
    ./exe.py -e -t set1 -m # mvababies
    ./exe.py -e -d # dataOnly test
    ./exe.py -e # test only
    ./exe.py # print test only
    '''

    if args.e:
        subprocess.call("make", shell=True)
    
    if not tag is None:
        subprocess.call("time python/run.py %s --%s %s" % (execution, tag, mission), shell=True)
    else:
        if args.d:
            subprocess.call("time python/run.py %s --dataOnly %s" % (execution, mission), shell=True)
        else:
            subprocess.call("time python/run.py %s --test %s" % (execution, mission), shell=True)
    
if __name__ == "__main__":
    run()

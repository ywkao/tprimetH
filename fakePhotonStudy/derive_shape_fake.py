#!/usr/bin/env python2
import ROOT
import numpy
import math
ROOT.gROOT.SetBatch(True)

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--input", help = "file with histograms to derive shape from", type=str)
parser.add_argument("--hist_name", help = "which histogram to fit", type=str, default = "hFakePhotonIDMVA")
args = parser.parse_args()

f = ROOT.TFile.Open(args.input, "R")
hist_name = args.hist_name 

fake_template = f.Get(hist_name + "_GammaJets")

fake_template.GetXaxis().SetRangeUser(-0.9,1.0)

fake_template.Fit("pol7")

input("Press any key to continue")

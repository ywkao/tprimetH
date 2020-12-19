#!/usr/bin/env python2
import subprocess
import json
import ROOT
ROOT.gROOT.SetBatch(True)

json_file = 'json/covMatrix_Era2017_M1000.json'
with open(json_file) as f:
    data = json.load(f)

labels = ["W boson", "top quark", "T' quark"]

h = ROOT.TH2F("h", ";;", 2, 0, 2, 2, 0, 2);
h.Fill(labels[0], labels[0], data["covMatrix_00"])
h.Fill(labels[0], labels[1], data["covMatrix_01"])
h.Fill(labels[1], labels[0], data["covMatrix_10"])
h.Fill(labels[1], labels[1], data["covMatrix_11"])

#h.Fill(labels[0], labels[0], data["covMatrix_00"])
#h.Fill(labels[0], labels[1], data["covMatrix_01"])
#h.Fill(labels[0], labels[2], data["covMatrix_02"])
#h.Fill(labels[1], labels[0], data["covMatrix_10"])
#h.Fill(labels[1], labels[1], data["covMatrix_11"])
#h.Fill(labels[1], labels[2], data["covMatrix_12"])
#h.Fill(labels[2], labels[0], data["covMatrix_20"])
#h.Fill(labels[2], labels[1], data["covMatrix_21"])
#h.Fill(labels[2], labels[2], data["covMatrix_22"])

#h.SetBinContent(0+1, 0+1, data["covMatrix_00"])
#h.SetBinContent(0+1, 1+1, data["covMatrix_01"])
#h.SetBinContent(0+1, 2+1, data["covMatrix_02"])
#h.SetBinContent(1+1, 0+1, data["covMatrix_10"])
#h.SetBinContent(1+1, 1+1, data["covMatrix_11"])
#h.SetBinContent(1+1, 2+1, data["covMatrix_12"])
#h.SetBinContent(2+1, 0+1, data["covMatrix_20"])
#h.SetBinContent(2+1, 1+1, data["covMatrix_21"])
#h.SetBinContent(2+1, 2+1, data["covMatrix_22"])


filename = "plots/" + json_file.split('/')[1].split('.')[0] + ".png"
c1 = ROOT.TCanvas("c1", "", 800, 600)

ROOT.gStyle.SetPalette(1)
h.SetStats(0)
h.Draw("text;colz")
c1.SaveAs(filename)


index_file = "/eos/user/y/ykao/www/plots/index.php"
target = "/eos/user/y/ykao/www/plots/20201218/09_CovMatrix"
subprocess.call('mkdir -p %s' % target, shell=True)
subprocess.call('mv %s %s' % (filename, target), shell=True)

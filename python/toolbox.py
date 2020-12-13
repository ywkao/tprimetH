#/usr/bin/env python2
import ROOT
ROOT.gROOT.SetBatch(True)

def make_plot(h, filename, option = "hist", removeStats = False, setOverflow = False):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    if removeStats:
        h.SetStats(0)

    if setOverflow:
        ROOT.gStyle.SetOptStat("nemro");

    h.SetLineWidth(2)
    h.Draw(option)
    c1.SaveAs(filename)

def make_plot_cut_efficiency(h, filename, cut_value):
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    h.SetLineWidth(2)
    h.Draw("hist")

    c1.Update()
    l = ROOT.TLine( cut_value, c1.GetUymin(), cut_value, c1.GetUymax() )
    l.SetLineColor(ROOT.kBlack)
    l.SetLineWidth(2)
    l.Draw()

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.40, 0.60, "Criterion: < %.1f" % cut_value )

    passed_entries = 0.
    for i in range(5):
        passed_entries += h.GetBinContent(i+1)

    efficiency = 100. * passed_entries / h.GetEntries()
    latex.DrawLatex( 0.40, 0.50, "Efficiency: %.1f%%" % efficiency )


    #c1.Update()
    #box = ROOT.TBox( cut_value, c1.GetUymin(), cut_value, c1.GetUymax() )
    ##box.SetFillStyle(3003);
    #box.SetFillColor(ROOT.kBlack);
    #box.SetLineColor(ROOT.kBlack);
    #box.SetLineWidth(2);
    #box.Draw("same");

    c1.SaveAs(filename)

def make_plot_two_hists(h1, title1, h2, title2, filename):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    h1.SetLineWidth(2)
    h2.SetLineWidth(2)
    h1.SetLineColor(ROOT.kBlue)
    h2.SetLineColor(ROOT.kRed)

    scale = 1.2
    value1 = h1.GetMaximum()
    value2 = h2.GetMaximum()
    max_scope = value1 if value1 > value2 else value2
    h1.SetMaximum(max_scope*scale)
    h2.SetMaximum(max_scope*scale)

    h1.SetStats(0)
    h2.SetStats(0)

    h1.Draw()
    h2.Draw("same")

    ROOT.gPad.SetTicky()
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.60, 0.915, "#bf{CMS} #it{Preliminary}" )
    
    latex.SetTextSize(32)

    draw_stats(title1, h1, latex, ROOT.kBlue, 0.20)
    draw_stats(title2, h2, latex, ROOT.kRed, 0.55)

    c1.SaveAs(filename)

def draw_stats(name, h, latex, color, xposition):
    latex.SetTextColor(color)
    latex.DrawLatex( xposition        , 0.80 , name                     )
    latex.DrawLatex( xposition        , 0.73 , "Entries"                )
    latex.DrawLatex( xposition        , 0.66 , "Mean"                   )
    latex.DrawLatex( xposition        , 0.59 , "Std Dev"                )
    latex.DrawLatex( xposition + 0.15 , 0.73 , "%d"   % h.GetEntries()  )
    latex.DrawLatex( xposition + 0.15 , 0.66 , "%.2f" % h.GetMean()     )
    latex.DrawLatex( xposition + 0.15 , 0.59 , "%.2f" % h.GetStdDev()   )

#/usr/bin/env python2
import ROOT
ROOT.gROOT.SetBatch(True)

def set_overflow_bin(h):
    nbins = h.GetNbinsX()
    overflow = h.GetBinContent(nbins) + h.GetBinContent(nbins + 1);
    h.SetBinContent(nbins, overflow);

def make_plot(h, filename, option = "hist", removeStats = False, setOverflow = False):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    if removeStats:
        h.SetStats(0)

    if setOverflow:
        ROOT.gStyle.SetOptStat("nemro");
        set_overflow_bin(h)

    h.SetLineWidth(2)
    h.Draw(option)
    c1.SaveAs(filename)

def make_plot_cut_efficiency(h, filename, cut_value):
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    set_overflow_bin(h)
    h.SetLineWidth(2)
    h.Draw("hist")

    c1.Update()
    line = ROOT.TLine( cut_value, c1.GetUymin(), cut_value, c1.GetUymax() )
    line.SetLineColor(ROOT.kBlack)
    line.SetLineWidth(2)
    line.Draw()

    box = ROOT.TBox( cut_value, c1.GetUymin(), c1.GetUxmax(), c1.GetUymax() )
    box.SetFillColorAlpha(ROOT.kBlack, 0.35);
    box.Draw();

    h.Draw("hist;same")

    x_position = 0.40 if cut_value < 1.5 else 0.20

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( x_position, 0.60, "Criterion: < %.1f" % cut_value )

    passed_entries = 0.
    num_bins = int(cut_value * 10)
    for i in range(num_bins):
        content = h.GetBinContent(i+1)
        passed_entries += content
    total_entries = h.GetEntries() - 1. # setting overflow bin will increase total entries by 1
    efficiency = 100. * float(passed_entries) / float(total_entries)
    latex.DrawLatex( x_position, 0.50, "Efficiency: %.1f%%" % efficiency )

    #c1.Update()
    #box = ROOT.TBox( cut_value, c1.GetUymin(), cut_value, c1.GetUymax() )
    ##box.SetFillStyle(3003);
    #box.SetFillColor(ROOT.kBlack);
    #box.SetLineColor(ROOT.kBlack);
    #box.SetLineWidth(2);
    #box.Draw("same");

    c1.SaveAs(filename)

def make_plot_two_hists(h1, title1, h2, title2, year, mass, filename):
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

    legend = ROOT.TLegend(0.55, 0.65, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.AddEntry(h1, "Min. #chi^{2} method", "l")
    legend.AddEntry(h2, "MC-truth matching", "l")
    legend.Draw()

    ROOT.gPad.SetTicky()
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.10, 0.912, "#bf{CMS} #it{Preliminary}" )
    latex.DrawLatex( 0.70, 0.912, "%s (13TeV)" % year )
    c1.SaveAs(filename)

    latex.SetTextSize(24)
    draw_stats(title1, h1, latex, ROOT.kBlue, 0.13, 0.55)
    draw_stats(title2, h2, latex, ROOT.kRed , 0.60, 0.55)
    c1.SaveAs("text_" + filename)


def draw_stats(name, h, latex, color, xposition, yposition):
    latex.SetTextColor(color)
    #latex.DrawLatex( xposition        , 0.80 , name                     )
    latex.DrawLatex( xposition        , yposition        , "Entries"                )
    latex.DrawLatex( xposition        , yposition - 0.07 , "Mean"                   )
    latex.DrawLatex( xposition        , yposition - 0.14 , "Std Dev"                )
    latex.DrawLatex( xposition + 0.12 , yposition        , "%d"   % h.GetEntries()  )
    latex.DrawLatex( xposition + 0.12 , yposition - 0.07 , "%.2f" % h.GetMean()     )
    latex.DrawLatex( xposition + 0.12 , yposition - 0.14 , "%.2f" % h.GetStdDev()   )

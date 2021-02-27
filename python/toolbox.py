#/usr/bin/env python2
import ROOT
ROOT.gROOT.SetBatch(True)

def set_overflow_bin(h):
    nbins = h.GetNbinsX()
    overflow = h.GetBinContent(nbins) + h.GetBinContent(nbins + 1);
    h.SetBinContent(nbins, overflow);

def set_normalize_to_unity(h):
    Area = h.Integral(1, h.GetNbinsX())
    h.Scale(1. / float(Area))

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

def make_plot_matching_efficiency(h, filename, option = "hist", removeStats = False, setOverflow = False):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    if removeStats:
        h.SetStats(0)

    if setOverflow:
        ROOT.gStyle.SetOptStat("nemro");
        set_overflow_bin(h)

    h.Scale(100)
    h.SetMaximum(90.)
    h.SetMinimum(0.)
    h.GetYaxis().SetTitle("Matching efficiency (%)")
    
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

def make_plot_two_hists(h1, title1, h2, title2, year, mass, filename, show_stat = True, scale = 1.2):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    h1.SetLineWidth(2)
    h2.SetLineWidth(2)
    h1.SetLineColor(ROOT.kBlue)
    h2.SetLineColor(ROOT.kRed)

    value1 = h1.GetMaximum()
    value2 = h2.GetMaximum()
    max_scope = value1 if value1 > value2 else value2
    h1.SetMaximum(max_scope*scale)
    h2.SetMaximum(max_scope*scale)

    h1.SetStats(0)
    h2.SetStats(0)

    h1.Draw("hist")
    h2.Draw("hist;same")

    legend = ROOT.TLegend(0.55, 0.65, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.AddEntry(h1, title1, "l")
    legend.AddEntry(h2, title2, "l")
    legend.Draw()

    ROOT.gPad.SetTicky()
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.10, 0.912, "#bf{CMS} #it{Preliminary}" )
    latex.DrawLatex( 0.70, 0.912, "%s (13TeV)" % str(year) )
    #c1.SaveAs(filename)

    if show_stat:
        latex.SetTextSize(24)
        draw_stats(title1, h1, latex, ROOT.kBlue, 0.13, 0.55)
        draw_stats(title2, h2, latex, ROOT.kRed , 0.60, 0.55)
        c1.SaveAs(filename)
        #c1.SaveAs("text_" + filename)

def make_plot_three_hists(h1, title1, h2, title2, h3, title3, year, mass, filename):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    h1.SetLineWidth(2)
    h2.SetLineWidth(2)
    h3.SetLineWidth(2)
    h1.SetLineColor(ROOT.kBlue)
    h2.SetLineColor(ROOT.kGreen+4)
    h3.SetLineColor(ROOT.kRed)

    scale = 1.2
    value1 = h1.GetMaximum()
    value2 = h2.GetMaximum()
    value3 = h3.GetMaximum()
    max_scope = max(value1, value2, value3)

    h1.SetMaximum(max_scope*scale)
    h2.SetMaximum(max_scope*scale)
    h3.SetMaximum(max_scope*scale)

    h1.SetStats(0)
    h2.SetStats(0)
    h3.SetStats(0)

    h1.Draw("hist")
    h2.Draw("hist;same")
    h3.Draw("hist;same")

    legend = ROOT.TLegend(0.55, 0.65, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.AddEntry(h1, "Min. #chi^{2} method", "l")
    legend.AddEntry(h2, "Covariant matrix", "l")
    legend.AddEntry(h3, "MC-truth matching", "l")
    legend.Draw()

    ROOT.gPad.SetTicky()
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.10, 0.912, "#bf{CMS} #it{Preliminary}" )
    latex.DrawLatex( 0.70, 0.912, "%s (13TeV)" % str(year) )
    #c1.SaveAs(filename)

    latex.SetTextSize(24)
    draw_stats(title1, h1, latex, ROOT.kBlue, 0.13, 0.55)
    draw_stats(title2, h2, latex, ROOT.kGreen+4, 0.13, 0.80)
    draw_stats(title3, h3, latex, ROOT.kRed , 0.60, 0.55)
    c1.SaveAs(filename)
    #c1.SaveAs("text_" + filename)

def make_plot_multi_hists(hists, colors, styles, texts, xytitles, filename, year = 2017, draw_option = "hist", legend_option = "l", setOverflow = False, init_xy = [0.50, 0.20], width_xy = [0.30, 0.20], setNormalize = False):
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    left_margin = 0.14
    c1.SetRightMargin(0.10)
    c1.SetLeftMargin(left_margin)

    legend = ROOT.TLegend(init_xy[0], init_xy[1], init_xy[0] + width_xy[0], init_xy[1] + width_xy[1])
    legend.SetLineColor(0)
    legend.SetFillStyle(0)
    legend.SetTextSize(0.04)
    
    values = []
    counter = 0
    for h in hists:
        h.SetStats(0)
        h.SetLineWidth(2)
        h.SetLineStyle(styles[counter])
        h.SetLineColor(colors[counter])
        legend.AddEntry(h, texts[counter], legend_option)

        if setNormalize:
            set_normalize_to_unity(h)

        if setOverflow:
            set_overflow_bin(h)

        values.append(h.GetMaximum())
        h.Draw(draw_option) if counter == 0 else h.Draw("%s;same" % draw_option)
        counter += 1
    
    scale = 1.2
    max_scope = max(values)
    hists[0].SetMaximum(max_scope*scale)
    hists[0].GetXaxis().SetTitle(xytitles[0])
    hists[0].GetYaxis().SetTitle(xytitles[1])
    
    legend.Draw()
    #draw_preliminary_tlatex(year, left_margin)

    ROOT.gPad.SetGrid()
    ROOT.gPad.SetTicks()
    c1.SaveAs(filename)


def make_mass_pt_2D_plot(obj, ptnbins, ptmin, ptmax, massnbins, massmin, massmax, fin_collection, tprime_masses):
    c1 = ROOT.TCanvas("c1", "", 800, 600)
    legend = ROOT.TLegend(0.65, 0.35, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    scale = 1.2

    counter = 0
    for fin in fin_collection:
        name = "h_" + obj + "_" + str(tprime_masses[counter])
        h = ROOT.TH2D( name, ";p_{T} (GeV / c); reconstructed mass (GeV / c^{2})", ptnbins, ptmin, ptmax, massnbins, massmin, massmax )
        nt = fin.Get( "nt_" + obj )
        nt.Project(name, "mass:pt")
        h.Draw("colz")

        draw_preliminary_tlatex_v2(2017)
        c1.SaveAs("h_tm_" + obj + "_2d_map_Era2017_" + str(tprime_masses[counter]) + ".png")
        counter += 1


def make_plot_from_ntuple_from_various_files(obj, var, nbins, hmin, hmax, fin_collection, tprime_masses, colors, ptmin, ptmax):
    '''
        study of mass-pt relation of top / wboson
        obj = top or wboson
        var = mass or pt
    '''
    selection = "pt>%d && pt<%d" %(ptmin, ptmax) if not (ptmin == 0 and ptmax == 0) else ""
    label = "%d < p_{T} < %d" %(ptmin, ptmax) if not (ptmin == 0 and ptmax == 0) else ""
    tag = "_pt_%d_%d" %(ptmin, ptmax) if not (ptmin == 0 and ptmax == 0) else ""

    c1 = ROOT.TCanvas("c1", "", 800, 600)
    legend = ROOT.TLegend(0.65, 0.35, 0.85, 0.85)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    scale = 1.2
    
    h_collection = []
    for i in range(len(tprime_masses)):
        h = ROOT.TH1D("h_"+obj+"_"+var+"_"+str(i), "", nbins, hmin, hmax)
        h_collection.append(h)

    counter = 0
    for fin in fin_collection:
        nt = fin.Get( "nt_"+obj )
        nt.Project("h_"+obj+"_"+var+"_"+str(counter), var, selection)
        set_hist_and_draw(h_collection[counter], tprime_masses[counter], colors[counter], legend, counter)
        counter += 1
                
    max_value = get_hist_collection_max_scope(h_collection)
    h_collection[0].SetMaximum( max_value * scale )

    legend.Draw()
    ROOT.gPad.SetTicky()
    draw_tlatex(0.15, 0.80, label)
    draw_preliminary_tlatex(2017)
    c1.SaveAs("h_tm_"+var+"_"+obj+"_Era2017"+tag+".png")

def make_2d_plot_from_ntuple(nts, xytitles, labels, histnames, var, selection, xnbins, xhmin, xhmax, ynbins, yhmin, yhmax, is_subspace = False):
    colors = [ROOT.kBlue, ROOT.kRed]

    c1 = ROOT.TCanvas("c1", "", 800, 600)
    legend = ROOT.TLegend(0.45, 0.20, 0.85, 0.40)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)

    h_collection = []
    for histname in histnames:
        h = ROOT.TH2D(histname, ";%s;%s" %(xytitles[0], xytitles[1]), xnbins, xhmin, xhmax, ynbins, yhmin, yhmax)
        h_collection.append(h)

    counter = 0
    for nt in nts:
        nt.Project(histnames[counter], var, selection)
        set_hist_and_draw_v2(h_collection[counter], colors[counter], legend, labels[counter], counter)
        counter += 1

    if is_subspace:
        c1.Update()
        cut_eff = 0.34 # taken from log message; portion of events that truth-mathing criteria applicable within selected events
        line = ROOT.TLine( cut_eff, c1.GetUymin(), cut_eff, c1.GetUymax() )
        line.SetLineColor(ROOT.kBlack)
        line.SetLineWidth(1)
        line.Draw()
        yposition = 0.80
        spacing = 0.08
        draw_tlatex(0.42, yposition, "Max. selection efficiency (34%)")
        draw_tlatex(0.42, yposition - spacing, "after applying")
        draw_tlatex(0.42, yposition - spacing * 2., "the turth-matching criteria")
    
    legend.Draw()
    ROOT.gPad.SetTicks()
    c1.SaveAs("%s.png" % histname)

def set_hist_and_draw(h, mass, color, legend, counter):
    h.SetStats(0)
    h.SetLineWidth(2)
    h.SetLineColor(color)
    h.Draw("hist") if counter == 0 else h.Draw("hist;same")
    legend.AddEntry(h, "M_{T'} = " + str(mass), "l")

def set_hist_and_draw_v2(h, color, legend, label, counter):
    h.SetStats(0)
    h.SetMarkerStyle(20)
    h.SetMarkerColor(color)
    h.Draw("p") if counter == 0 else h.Draw("p;same")
    legend.AddEntry(h, label, "p")

def get_hist_collection_max_scope(h_collection):
    values = []
    for h in h_collection:
        values.append(h.GetMaximum())
    max_value = max(values)
    return max_value

def normalize_to_unity(h):
    normalization_factor = float(h.GetEntries()) if h.GetEntries() > 0 else 1.
    h.Scale(1./normalization_factor)
    h.GetYaxis().SetTitle("")

def draw_stats(name, h, latex, color, xposition, yposition):
    latex.SetTextColor(color)
    #latex.DrawLatex( xposition        , 0.80 , name                     )
    latex.DrawLatex( xposition        , yposition        , "Entries"                )
    latex.DrawLatex( xposition        , yposition - 0.07 , "Mean"                   )
    latex.DrawLatex( xposition        , yposition - 0.14 , "Std Dev"                )
    latex.DrawLatex( xposition + 0.12 , yposition        , "%d"   % h.GetEntries()  )
    latex.DrawLatex( xposition + 0.12 , yposition - 0.07 , "%.2f" % h.GetMean()     )
    latex.DrawLatex( xposition + 0.12 , yposition - 0.14 , "%.2f" % h.GetStdDev()   )

def draw_preliminary_tlatex(year, left_margin = 0.10):
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( left_margin, 0.912, "#bf{CMS} #it{Simulation Preliminary}" )
    latex.DrawLatex( 0.70, 0.912, "%s (13TeV)" % str(year) )

def draw_preliminary_tlatex_v2(year):
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( 0.10, 0.912, "#bf{CMS} #it{Simulation Preliminary}" )

def draw_tlatex(x, y, texts):
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextFont(43)
    latex.SetTextAlign(11)
    latex.SetTextSize(28)
    latex.DrawLatex( x, y, texts )

def set_tgraph(gr, min, max, color):
    gr.SetMinimum(min)
    gr.SetMaximum(max)
    gr.SetMarkerStyle(20)
    gr.SetMarkerColor(color)
    gr.SetLineColor(color)

def make_tgraph(gr1, gr2, gr3, mass, title, filename):
    c1 = ROOT.TCanvas("c1", "", 800, 600)

    gr1.SetTitle(title);
    gr1.Draw("ap");

    c1.Update()
    line = ROOT.TLine( c1.GetUxmin(), mass, c1.GetUxmax(), mass )
    line.SetLineColor(ROOT.kBlack)
    line.SetLineWidth(1)
    line.Draw()

    gr1.Draw("p");
    gr2.Draw("p");
    gr3.Draw("p");

    legend = ROOT.TLegend(0.35, 0.70, 0.85, 0.85)
    legend.SetNColumns(3)
    legend.SetLineColor(0)
    legend.SetTextSize(0.04)
    legend.AddEntry(gr1, "2016", "ep")
    legend.AddEntry(gr2, "2017", "ep")
    legend.AddEntry(gr3, "2018", "ep")
    legend.Draw()
    c1.SaveAs(filename)

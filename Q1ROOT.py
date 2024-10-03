import ROOT



file_path ="/mnt/c/Users/aisha/source/repos/ComputationalCourse/ComputationalCourse/Assignments/PythonRootMat/sorted_mass.root"

file = ROOT.TFile(file_path, "READ")

Kaon_hist = file.Get("histKaon")
Pion_hist = file.Get("histPion")
# Canvas 1: Pion and Kaon histograms
canvas1 = ROOT.TCanvas("canvas1", "Pion and Kaon Mass Distribution", 800, 600)
Pion_hist.SetLineColor(ROOT.kBlue)
Kaon_hist.SetLineColor(ROOT.kRed)
Pion_hist.SetStats(0)
Kaon_hist.SetStats(0)
Kaon_hist.Draw("HIST")
Pion_hist.Draw("HIST SAME")
Kaon_hist.SetTitle("Pion and Kaon Mass Distribution")
Pion_hist.GetYaxis().SetTitle("Events")
Pion_hist.GetXaxis().SetTitle("Mass (GeV/c^2)")

legend1 = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend1.AddEntry(Pion_hist, "massPion", "l")
legend1.AddEntry(Kaon_hist, "massKaon", "l")
legend1.Draw()

canvas1.SaveAs("/mnt/c/Users/aisha/source/repos/ComputationalCourse/ComputationalCourse/Assignments/PythonRootMat/Pion_and_Kaon_Mass_Distribution.png")

# Canvas 2: Ratio of Pion to Kaon histograms
canvas2 = ROOT.TCanvas("canvas2", "Ratio of Pion to Kaon Mass", 800, 600)
ratio_hist = Pion_hist.Clone("ratio_hist")
ratio_hist.Divide(Kaon_hist)
ratio_hist.SetLineColor(ROOT.kBlack)
ratio_hist.SetMarkerStyle(20)
ratio_hist.SetMarkerSize(0.7)
ratio_hist.SetStats(0)
ratio_hist.SetMarkerColor(ROOT.kBlack)
ratio_hist.Draw("E")
ratio_hist.SetTitle("Ratio of Pion to Kaon Mass")
ratio_hist.GetYaxis().SetTitle("massPion / massKaon")
ratio_hist.GetXaxis().SetTitle("Mass (GeV/c^2)")

legend3 = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend3.AddEntry(ratio_hist, "massPion / massKaon", "l")
legend3.Draw()

canvas2.SaveAs("/mnt/c/Users/aisha/source/repos/ComputationalCourse/ComputationalCourse/Assignments/PythonRootMat/Ratio_of_Pion_to_Kaon_Mass.png")
#canvas2.SaveAs("Ratio_of_Pion_to_Kaon_Mass.png")

# Canvas 3: Gaussian fit to Pion histogram
canvas3 = ROOT.TCanvas("canvas3", "Gaussian Fit to Pion Mass Distribution", 800, 600)
gauss = ROOT.TF1("gauss", "gaus", 0.05, 0.25)
Pion_hist2 = file.Get("histPion")
#gauss.SetParLimits(0, 220, 300)
Pion_hist2.Fit(gauss, "R")
Pion_hist2.SetLineColor(ROOT.kBlue)
Pion_hist2.SetStats(0)
Pion_hist2.Draw("HIST")
gauss.Draw("SAME")
Pion_hist2.SetTitle("Gaussian Fit to Pion Mass Distribution")
Pion_hist2.GetYaxis().SetTitle("Gaussian Fit")
gauss.GetXaxis().SetTitle("Mass (GeV/c^2)")

mean = gauss.GetParameter(1)
sigma = gauss.GetParameter(2)
mean_error = gauss.GetParError(1)
sigma_error = gauss.GetParError(2)

legend2 = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend2.AddEntry(gauss, "Gaussian Fit", "l")
legend2.AddEntry(Pion_hist2, "massPion", "l")
legend2.AddEntry("", f"#mu: {mean:.2f} #pm {mean_error:.3f}", "")
legend2.AddEntry("", f"#sigma: {sigma:.2f} #pm {sigma_error:.3f}", "")
legend2.Draw()


canvas3.SaveAs("/mnt/c/Users/aisha/source/repos/ComputationalCourse/ComputationalCourse/Assignments/PythonRootMat/Gaussian_Fit_to_Pion_Mass_Distribution.png")

file.Close()

ROOT.gApplication.Run()

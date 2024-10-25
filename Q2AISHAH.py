'''
Find the confidence level for ptsums (bg_filtered) from the mlpHiggs.root
'''
import ROOT
import numpy as np

file_path = "mlpHiggs.root"
file = ROOT.TFile(file_path, "READ")
bg_tree = file.Get("bg_filtered")

bg_hist = ROOT.TH1F("bg_ptsumf", "ptsumf - Background", 150, 0, 0.5)
for j in range(bg_tree.GetEntries()):
    bg_tree.GetEntry(j)
    bg_hist.Fill(bg_tree.ptsumf)

bg_hist.SetStats(0)

canvas = ROOT.TCanvas("canvas", "ptsumf with Confidence level", 800, 600)
bg_hist.GetXaxis().SetRangeUser(0, 0.6)
bg_hist.GetYaxis().SetRangeUser(0, 50)
bg_hist.SetXTitle("ptsumf")
bg_hist.SetYTitle("ptsumf with Confidence level")
bg_hist.Draw("HIST")

mean = bg_hist.GetMean()
sigma = bg_hist.GetStdDev()
x_values = np.linspace(mean - 5 * sigma, mean + 5 * sigma, 100)
#x_values = np.linspace(bg_hist.GetXaxis().GetXmin(), bg_hist.GetXaxis().GetXmax(), 100) # same result
confidence_level = 2
n_bins = bg_hist.GetNbinsX()
x_values = []
y_values_upper = []
y_values_lower = []
n_points = 0  # To keep track of valid points
for i in range(1,n_bins +1):
    x = bg_hist.GetBinCenter(i)
    y = bg_hist.GetBinContent(i)

    
    if y > 0:
        x_values.append(x)
        y_values_upper.append(y + confidence_level)  # Upper limit
        y_values_lower.append(y - confidence_level)  # Lower limit
        n_points += 1  # Count valid points

# Create a filled area only if there are valid points
n_points = len(x_values)
if n_points > 0:
    fill_graph = ROOT.TGraph(2 * n_points)

    for i in range(n_points):
        fill_graph.SetPoint(i, x_values[i], y_values_upper[i])  # Upper points
        fill_graph.SetPoint(n_points + i, x_values[n_points - 1 - i], y_values_lower[n_points - 1 - i])
    fill_graph.SetFillColor(ROOT.kBlue)  # Light gray color
    #fill_graph.SetFillStyle(3001)
    # Solid filling style
    fill_graph.SetLineWidth(1)
    fill_graph.Draw("F SAME")

legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.SetHeader("AISHAH")
legend.AddEntry(bg_hist, "ptsumf", "l")
if n_points > 0:
    legend.AddEntry(fill_graph, "Confidence_Level", "f")
legend.Draw()

# Draw the canvas
canvas.Update()
canvas.Draw()

# Save the canvas in the Plots directory
canvas.SaveAs("/mnt/c/Users/aisha/source/repos/ComputationalCourse/ComputationalCourse/Assignments/PythonRootMat/ptsumfCL.png")
ROOT.gApplication.Run()

# Close the ROOT file
file.Close()

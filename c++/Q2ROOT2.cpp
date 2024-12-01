/*
You are given a ROOT file with two trees: sig_filtered (signal events) and \
bg_filtered (background events).
The goal is to calculate the efficiency for signal events as a function of \
the acollinearity threshold (acolin)
and plot it alongside its 95% Confidence Intervals (CL).

Instructions:
1. Use the following equations for confidence intervals:
   Lower Bound = p - z * sqrt(p * (1 - p) / n)
   Upper Bound = p + z * sqrt(p * (1 - p) / n)
   where:
     - p = efficiency (signal count / total signal events)
     - z = 1.96 (for 95% CL)
     - n = total signal events.

2. Write a ROOT macro or C++ program to:
   - Loop over acollinearity thresholds from 80 to 200.
   - Calculate efficiency and confidence intervals for each threshold.
   - Plot:
       * Efficiency as a blue line with markers.
       * Confidence intervals as dashed lines in a different color.

3. Label the plot:
   - X-axis: Acollinearity threshold (degrees).
   - Y-axis: Efficiency.
   - Include a legend for efficiency and confidence intervals.
*/

void  Q2ROOT2() {
    // Open the ROOT file and retrieve the signal tree
    TFile *file = TFile::Open("mlpHiggs.root", "READ");
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");

    // Retrieve the total number of signal events
    Long64_t total_signal_events = sig_tree->GetEntries();

    // Set branch address for acollinearity
    Float_t acolin_signal;
    sig_tree->SetBranchAddress("acolin", &acolin_signal);

    // Constants for 95% Confidence Interval
    const double z = 1.96; // For 95% confidence

    // Define the range for acollinearity thresholds
    const int n_points = 121; // From 80 to 200 inclusive
    double thresholds[n_points], efficiency[n_points], lower_bound[n_points], upper_bound[n_points];

    // Loop over acollinearity thresholds
    int index = 0;
    for (int threshold = 80; threshold <= 200; ++threshold, ++index) {
        thresholds[index] = threshold;

        // Count signal events passing the threshold
        int signal_count = 0;
        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin_signal >= threshold) {
                ++signal_count;
            }
        }

        // Calculate efficiency
        double p = static_cast<double>(signal_count) / total_signal_events;
        efficiency[index] = p;

        // Calculate confidence intervals
        double margin_of_error = z * sqrt(p * (1 - p) / total_signal_events);
        lower_bound[index] = p - margin_of_error;
        upper_bound[index] = p + margin_of_error;

        // Ensure bounds are within [0, 1]
        if (lower_bound[index] < 0) lower_bound[index] = 0;
        if (upper_bound[index] > 1) upper_bound[index] = 1;
    }

    // Create canvas for the plot
    TCanvas *canvas = new TCanvas("canvas", "Efficiency with 95% Confidence Intervals", 800, 600);
    canvas->SetGrid();

    // Create TGraphs for efficiency and confidence intervals
    TGraph *eff_graph = new TGraph(n_points, thresholds, efficiency);
    TGraph *lower_graph = new TGraph(n_points, thresholds, lower_bound);
    TGraph *upper_graph = new TGraph(n_points, thresholds, upper_bound);

    // Style the efficiency graph
    eff_graph->SetTitle("Signal Efficiency with 95% Confidence Intervals");
    eff_graph->GetXaxis()->SetTitle("Acollinearity Threshold (degrees)");
    eff_graph->GetYaxis()->SetTitle("Efficiency");
    eff_graph->SetLineColor(kBlue);
    eff_graph->SetMarkerStyle(20);
    eff_graph->SetMarkerColor(kBlue);
    eff_graph->SetLineWidth(2);

    // Style the confidence interval graphs
    lower_graph->SetLineColor(kRed);
    lower_graph->SetLineStyle(2); // Dashed line
    lower_graph->SetLineWidth(2);

    upper_graph->SetLineColor(kRed);
    upper_graph->SetLineStyle(2); // Dashed line
    upper_graph->SetLineWidth(2);

    // Draw the graphs
    eff_graph->Draw("ALP");  // Axis + Line + Points
    lower_graph->Draw("L SAME"); // Overlay lower bound
    upper_graph->Draw("L SAME"); // Overlay upper bound

    // Add legend
    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(eff_graph, "Efficiency", "lp");
    legend->AddEntry(lower_graph, "95% Confidence Interval", "l");
    legend->Draw();

    // Save the canvas
    canvas->SaveAs("efficiency_with_confidence_intervals.png");

     canvas->Show();
}

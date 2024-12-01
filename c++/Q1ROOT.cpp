/* Using C++ Sytenx
File Handling

1. How would you open the mlpHiggs.root file and retrieve the trees sig_filtered and bg_filtered in C++?

2. Write C++ code to calculate the purity for a given acolinearity threshold.
3. Extend your code to calculate the product of efficiency and purity for each threshold.
Plotting

4. How would you plot the efficiency, purity, and their product in a single graph using ROOT in C++?
Threshold Range

5. How would you modify your loop to evaluate acolinearity thresholds from 80 to 200 ?
 */


gROOT->SetStyle("ATLAS");
gROOT->ForceStyle();


gStyle->SetLabelFont(22, "X");
gStyle->SetLabelFont(22, "Y");
gStyle->SetTitleFont(22, "X");
gStyle->SetTitleFont(22, "Y");

gStyle->SetLabelSize(0.03, "X");
gStyle->SetLabelSize(0.03, "Y");
gStyle->SetTitleSize(0.04, "X");
gStyle->SetTitleSize(0.04, "Y");
gStyle->SetMarkerSize(0.5);


gStyle->SetLegendFont(22);
void Q1ROOT() {
    TFile *file = TFile::Open("mlpHiggs.root", "READ");
    TTree *sig_tree = (TTree*)file->Get("sig_filtered");
    TTree *bg_tree = (TTree*)file->Get("bg_filtered");

    
    Long64_t total_signal_events = sig_tree->GetEntries();
    Long64_t total_background_events = bg_tree->GetEntries();

    
    TGraphErrors* efficiency_graph = new TGraphErrors();
    TGraphErrors* purity_graph = new TGraphErrors();
    TGraphErrors* product_graph = new TGraphErrors();

    
    Float_t acolin_signal, acolin_background;
    sig_tree->SetBranchAddress("acolin", &acolin_signal);
    bg_tree->SetBranchAddress("acolin", &acolin_background);

    
    for (int threshold = 80; threshold <= 200; ++threshold) {
        
        int signal_entry_count = 0;
        int background_entry_count = 0;

        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (acolin_signal >= threshold) {
                signal_entry_count++;
            }
        }

        for (int i = 0; i < total_background_events; ++i) {
            bg_tree->GetEntry(i);
            if (acolin_background >= threshold) {
                background_entry_count++;
            }
        }

        
        double efficiency = static_cast<double>(signal_entry_count) / total_signal_events;
        int total_valid_events = signal_entry_count + background_entry_count;
	double purity;
	if (total_valid_events > 0) {
	  purity = static_cast<double>(signal_entry_count) / total_valid_events;
	} else {
	  purity = 0.0;
}
        double product = efficiency * purity;

       
        double efficiency_error = sqrt(efficiency * (1 - efficiency) / total_signal_events);
        double purity_error;
	if (total_valid_events > 0) {
	  purity_error = sqrt(purity * (1 - purity) / total_valid_events);
	} else {
	  purity_error = 0.0;
}

	double product_error;
	if (efficiency > 0 && purity > 0) {
	  product_error = efficiency_error * purity_error;
	} else {
	  product_error = 0.0;
}

 efficiency_graph->SetPoint(efficiency_graph->GetN(), threshold, efficiency);
 efficiency_graph->SetPointError(efficiency_graph->GetN() - 1, 0, efficiency_error);

 purity_graph->SetPoint(purity_graph->GetN(), threshold, purity);
 purity_graph->SetPointError(purity_graph->GetN() - 1, 0, purity_error);

 product_graph->SetPoint(product_graph->GetN(), threshold, product);
 product_graph->SetPointError(product_graph->GetN() - 1, 0, product_error);
    }
   

    
    efficiency_graph->SetTitle("Efficiency, Purity, and Product vs Acolinearity");
    efficiency_graph->GetXaxis()->SetTitle("Acolinearity (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Signal Efficiency / Purity / Product");
    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);

    purity_graph->SetLineColor(kRed);
    purity_graph->SetMarkerStyle(21);
    purity_graph->SetMarkerColor(kRed);

    product_graph->SetLineColor(kGreen);
    product_graph->SetMarkerStyle(22);
    product_graph->SetMarkerColor(kGreen);

    
    TCanvas *canvas = new TCanvas("canvas", "Efficiency, Purity, and Product vs Acolinearity", 800, 600);
    canvas->SetGrid();

    efficiency_graph->Draw("ALP"); 
    purity_graph->Draw("LP SAME"); 
    product_graph->Draw("LP SAME"); 

    efficiency_graph->GetYaxis()->SetRangeUser(0.009, 1.01);
    TLegend*legend = new TLegend(0.17, 0.17, 0.3, 0.34);
    legend->AddEntry(efficiency_graph, "Efficiency", "lp");
    legend->AddEntry(purity_graph, "Purity", "lp");
    legend->AddEntry(product_graph, "Product", "lp");
    legend->Draw();

    
    canvas->SaveAs("EfficiencyPurityProduct.png");

     canvas->Show();
}

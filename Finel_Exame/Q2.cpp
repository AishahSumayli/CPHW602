
//Question-2 (S(CLO 2.1))-10points:
/*
You are given a ROOT file with two trees: sig_filtered (signal events) and bg_filtered (background events). 
The goal is to calculate the purity for signal events as a function of the acollinearity threshold (acolin) 

Instructions:
1- Write a ROOT macro or C++ program to:
   - Loop over acollinearity thresholds from 80 to 200.
   - Calculate the purity as the efficiency is already given
   - Calculate the product between the efficiency and purity
   - Estimate the error on each varaibles
   - Plot:
       * Efficiency with purity and the product between them with markers.
       
2- Label the plot them on the same canvas:
   - X-axis: Acollinearity threshold (degrees).
   - Y-axis: Efficiency, Purity, Efficiency * Purity.
   - Include a legend for Efficiency, Purity, Efficiency * Purity.          
   - Save the plot
*/




#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <cmath>


void Q2(){
 // Set font for axis titles and labels                                                                                                                                               
    gStyle->SetLabelFont(22, "X");
    gStyle->SetLabelFont(22, "Y");
    gStyle->SetTitleFont(22, "X");
    gStyle->SetTitleFont(22, "Y");

    // Set size of axis titles and labels                                                                                                                                                
    gStyle->SetLabelSize(0.03, "X");
    gStyle->SetLabelSize(0.03, "Y");
    gStyle->SetTitleSize(0.04, "X");
    gStyle->SetTitleSize(0.04, "Y");
    gStyle->SetMarkerSize(0.5);


 TFile *file = TFile::Open("ParticlePhysics.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    TTree *sig_tree = dynamic_cast<TTree *>(file->Get("sig_filtered"));
    if (!sig_tree) {
        std::cerr << "Error: Signal tree not found!" << std::endl;
        file->Close();
        return;
    }

    TTree *bg_tree = dynamic_cast<TTree *>(file->Get("bg_filtered"));
    if (!sig_tree) {
        std::cerr << "Error: Signal tree not found!" << std::endl;
        file->Close();
        return;
    }
    int total_signal_events = sig_tree->GetEntries();
    int total_background_events = bg_tree->GetEntries();
    float sig_acolin;
    float bg_acolin;
    sig_tree->SetBranchAddress("acolin", &sig_acolin);
    bg_tree->SetBranchAddress("acolin", &bg_acolin);
    TGraphErrors *efficiency_graph = new TGraphErrors();
    TGraphErrors *purity_graph = new TGraphErrors();
    TGraphErrors *product_graph = new TGraphErrors();
    for (int threshold = 80; threshold <= 200; ++threshold) {
        int signal_entry_count = 0;
	int background_entry_count = 0;
        for (int i = 0; i < total_signal_events; ++i) {
            sig_tree->GetEntry(i);
            if (sig_acolin >= threshold) signal_entry_count++;
        }
	 for (int i = 0; i < total_background_events; ++i) {
            bg_tree->GetEntry(i);
            if (bg_acolin >= threshold) background_entry_count++;
        }
      

  
        double efficiency = static_cast<double>(signal_entry_count) / total_signal_events;
        double efficiency_error = std::sqrt(efficiency * (1 - efficiency) / total_signal_events);
	double total_entry_count = signal_entry_count + background_entry_count;
	double purity = static_cast<double>(signal_entry_count) / total_entry_count;
        double purity_error = std::sqrt(purity * (1 - purity) / total_entry_count);
	double product = efficiency * purity;
	double product_error = efficiency_error * purity_error;

    
        int n = efficiency_graph->GetN();
        efficiency_graph->SetPoint(n, threshold, efficiency);
        efficiency_graph->SetPointError(n, 0, efficiency_error);
	
	int n1 = purity_graph->GetN();
	purity_graph->SetPoint(n1, threshold, purity);
        purity_graph->SetPointError(n1, 0, purity_error);
	int n2 = product_graph->GetN();
	product_graph->SetPoint(n2, threshold, product);
        product_graph->SetPointError(n2, 0, product_error);
    }


    efficiency_graph->SetTitle("Efficiency, Purity, Efficiency * Purity");
    efficiency_graph->GetXaxis()->SetTitle(" Acollinearity threshold (degrees)");
    efficiency_graph->GetYaxis()->SetTitle("Efficiency, Purity, Efficiency * Purity");
    efficiency_graph->SetLineColor(kBlue);
    efficiency_graph->SetMarkerStyle(20);
    efficiency_graph->SetMarkerColor(kBlue);

     purity_graph->SetLineColor(kRed);
    purity_graph->SetMarkerStyle(20);
    purity_graph->SetMarkerColor(kRed);


     product_graph->SetLineColor(kGreen);
    product_graph->SetMarkerStyle(20);
    product_graph->SetMarkerColor(kGreen);
   
    TCanvas *canvas = new TCanvas("canvas", "Efficiency, Purity, Efficiency * Purity", 800, 600);
    canvas->SetGrid();
    efficiency_graph->Draw("ALP");// Draw efficiency graph
    product_graph->Draw("LP SAME");
    purity_graph->Draw("LP SAME");
    efficiency_graph->GetYaxis()->SetRangeUser(0.0, 1.2);
    TLegend* legend = new TLegend();
    legend->SetHeader("AISHAH");
    legend->AddEntry(efficiency_graph, "Efficiency", "lp");
    legend->AddEntry(purity_graph, "Purity", "lp");
    legend->AddEntry( product_graph, " product", "lp");
    legend->Draw();
    
    canvas->SaveAs("Efficiency_Purity_product.png");
    canvas->Show();
    //    canvas->Update();                                                                                                                                                                 //gApplication->Run();                                                                                                                                                                  // Close the file                                                                                                                                                                       //    file->Close();                                                                                                                                                                 
}

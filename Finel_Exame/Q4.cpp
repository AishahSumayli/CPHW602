
//Question-4 S(CLO 2.3)-10points:
/*
Fitting a Histogram with a Gaussian Function and Displaying Parameters
1. Fit the Histogram:
Use the TH1::Fit method to fit the histogram data_hist with a Gaussian function.
2. Retrieve Fit Parameters:
After fitting, obtain the Gaussian parameters: amplitude, mean, and sigma.
3. Update the Legend:
Modify the legend to include the fit parameters with their values and uncertainties.
*/


void Q4(){
  
  gStyle->SetLabelFont(22, "X");
  gStyle->SetLabelFont(22, "Y");
    gStyle->SetTitleFont(22, "X");
    gStyle->SetTitleFont(22, "Y");

    gStyle->SetLabelSize(0.2, "X");
    gStyle->SetLabelSize(0.03, "Y");
    gStyle->SetTitleSize(0.02, "X");
    gStyle->SetTitleSize(0.04, "Y");
    gStyle->SetMarkerSize(0.5);
  
    
  TFile* file = TFile::Open("histo.root","READ");
  TH1* data_hist = (TH1*)file->Get("data");
  TH1* mc_hist = (TH1*)file->Get("MC");

  TCanvas* canvas = new TCanvas("","", 800, 600);
  canvas->SetMargin(0.15,0.05,0.15,0.1);
  data_hist->GetXaxis()->SetTitle(" mass");
  data_hist->GetYaxis()->SetTitle("gauss_data");
  data_hist->SetMarkerColor(kBlue);
  mc_hist->SetMarkerColor(kRed);
  data_hist->SetStats(0);
  mc_hist->SetStats(0);
  data_hist->Draw("P");
  TF1* gauss= new TF1("gauss","gaus",-5,5);
  gauss->SetParLimits(0,230,300);
  data_hist->Fit("gauss");
  gauss->SetLineColor(kRed);
 
  
  
 
   double amplitude = gauss->GetParameter(0);
  double mean = gauss->GetParameter(1);
  double sigma = gauss->GetParameter(2);
  double mean_error = gauss->GetParError(1);
  double sigma_error= gauss->GetParError(2);

  TLegend* legend = new TLegend(0.5, 0.5, 0.7, 0.7);
  legend->SetHeader("made by AISHAH");
  legend->AddEntry(data_hist, "Data", "P");
  legend->AddEntry((TObject*)0,Form("#mu: %.2f #pm %.3f",mean, mean_error ),"");
    legend->AddEntry((TObject*)0,Form("#sigma: %.2f #pm %.3f",sigma, sigma_error ),"");
  legend->Draw();

  //  data_hist->GetYaxis()->SetRangeUser(0.0,220);
  canvas->SaveAs("Plots/Data_MC_Histograms.png");
  canvas->Show();
  //  canvas->Update();
}




    

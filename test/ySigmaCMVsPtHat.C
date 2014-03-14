{
  Double_t PtHat[5] = {20, 100, 300, 500, 1000};

  Double_t ySigmaCM[5] = {1.21, 0.95, 0.75, 0.64, 0.50};


  TGraph *ySigmaCM_vs_PtHat = new TGraph(5, PtHat, ySigmaCM);
  ySigmaCM_vs_PtHat->SetMarkerStyle(24);
  ySigmaCM_vs_PtHat->SetMarkerColor(kBlue);
  ySigmaCM_vs_PtHat->SetLineColor(kBlue);
  ySigmaCM_vs_PtHat->SetLineWidth(3);
  ySigmaCM_vs_PtHat->SetLineStyle(2);
  ySigmaCM_vs_PtHat->SetMarkerSize(1.5);
  ySigmaCM_vs_PtHat->Draw("ACP");

  TF1 *f1CM = new TF1("f1CM","[0]/pow(x+[1],[2])",0,1000);
  ySigmaCM_vs_PtHat->Fit("f1CM");
}
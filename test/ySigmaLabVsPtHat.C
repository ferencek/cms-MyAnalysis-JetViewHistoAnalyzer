{
  Double_t PtHat[5] = {20, 100, 300, 500, 1000};

  Double_t ySigmaLab[5] = {1.75, 1.18, 0.81, 0.63, 0.40};


  TGraph *ySigmaLab_vs_PtHat = new TGraph(5, PtHat, ySigmaLab);
  ySigmaLab_vs_PtHat->SetMarkerStyle(24);
  ySigmaLab_vs_PtHat->SetMarkerColor(kBlue);
  ySigmaLab_vs_PtHat->SetLineColor(kBlue);
  ySigmaLab_vs_PtHat->SetLineWidth(3);
  ySigmaLab_vs_PtHat->SetLineStyle(2);
  ySigmaLab_vs_PtHat->SetMarkerSize(1.5);
  ySigmaLab_vs_PtHat->Draw("ACP");

  TF1 *f1Lab = new TF1("f1Lab","[0]/pow(x,[1])+[2]",0,1000);
  ySigmaLab_vs_PtHat->Fit("f1Lab");
}
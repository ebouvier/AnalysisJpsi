#include <string>
#include <iostream>
#include <sstream>

#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TVectorD.h"
#include "TObject.h"

using std::cout ;
using std::endl ;

void leg_style(TLegend *leg,
    double text_size = 0.035,
    int text_font = 62,
    int text_align = 22,
    int fill_style = 1,
    int fill_color = 10,
    int border_size = 1) {
  leg->SetTextSize(text_size);
  leg->SetTextFont(text_font);
  leg->SetTextAlign(text_align);
  leg->SetFillStyle(fill_style);
  leg->SetFillColor(fill_color);
  leg->SetBorderSize(border_size);
}
void h1_style(TH1 *h,
    int line_width=2,
    int line_color=1,
    int line_style=1, 
    int fill_color=50,
    int fill_style=1001,
    float y_min=-1111.,
    float y_max=-1111.,
    int ndivx=510,
    int ndivy=510,
    int marker_style=20,
    int marker_color=1,
    float marker_size=1.2,
    int optstat=0,
    const char* title="",
    const char* xtitle="",
    const char* ytitle="") {

  h->SetLineWidth(line_width);
  h->SetLineColor(line_color);
  h->SetLineStyle(line_style);
  h->SetFillColor(fill_color);
  h->SetFillStyle(fill_style);
  h->SetMaximum(y_max);
  h->SetMinimum(y_min);
  h->GetXaxis()->SetNdivisions(ndivx);
  h->GetYaxis()->SetNdivisions(ndivy);

  h->SetMarkerStyle(marker_style);
  h->SetMarkerColor(marker_color);
  h->SetMarkerSize(marker_size);
  h->SetStats(optstat);

  h->SetLabelFont(62,"X");       // 42
  h->SetLabelFont(62,"Y");       // 42
  h->SetLabelOffset(0.01,"X");  // D=0.005
  h->SetLabelOffset(0.01,"Y");  // D=0.005
  h->SetLabelSize(0.05,"X");
  h->SetLabelSize(0.05,"Y");
  h->SetTitleOffset(1.0,"X");
  h->SetTitleOffset(1.0,"Y");
  h->SetTitleSize(0.045,"X");
  h->SetTitleSize(0.045,"Y");
  h->GetXaxis()->SetTitle(xtitle);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetXaxis()->SetTitleFont(62);
  h->GetYaxis()->SetTitleFont(62);
  h->SetTitle(title);
}

int Profile(TString channel="el", TString date="130927", TString numberofjets="4jets_top", bool shouldsave=false) {
  TString folder;
  TString outname;
  if ( channel.Contains("el") || channel.Contains("El") ) {
    cout << "Plots in the electron channel" << endl;
    folder = "Plots_El_" + numberofjets + "_" + date + "/";
    outname = folder + "ElectronChannel_" + numberofjets +"_" + date +".root";
  } 
  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    cout << "Plots in the muon channel" << endl;
    folder = "Plots_Mu_" + numberofjets + "_" + date + "/";
    outname = folder + "MuonChannel_" + numberofjets +"_" + date +".root";
  } 

  TFile *fi = TFile::Open(outname);

  float inter = 0.;
  float num = 0.;

  TCanvas *cn1 = new TCanvas("JPSI_CHI2","JPSI_CHI2",700,500);
  cn1->cd();
  cn1->SetLogy(1);
  TH1F *JPSI_CHI2 = (TH1F*)fi->Get("JPSI_CHI2");
  JPSI_CHI2->Rebin(4);
  JPSI_CHI2->Draw();
  inter = JPSI_CHI2->GetXaxis()->GetXmax() - JPSI_CHI2->GetXaxis()->GetXmin();
  num = (inter/(Float_t)JPSI_CHI2->GetXaxis()->GetNbins());
  h1_style(JPSI_CHI2,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","#chi^{2}(J/#psi vertex)",TString::Format("Events / %0.1f", num));
  cn1->Modified();
  if (shouldsave) {
    cn1->SaveAs(folder + "Plots/Sum_JPSI_CHI2.jpg");
    cn1->SaveAs(folder + "Plots/Sum_JPSI_CHI2.pdf");
    cn1->SaveAs(folder + "Plots/Sum_JPSI_CHI2.eps");
    cn1->SaveAs(folder + "Plots/Sum_JPSI_CHI2.C");
  }

  TH2F *JPSI_MUDIST_CHI2 = (TH2F*)fi->Get("JPSI_MUDIST_CHI2");
  JPSI_MUDIST_CHI2->SetContour(20);
  JPSI_MUDIST_CHI2->SetStats(0);
  JPSI_MUDIST_CHI2->GetXaxis()->SetTitle("3D distance (J/#psi's daughters) (#mu m)");
  JPSI_MUDIST_CHI2->GetYaxis()->SetTitle("#chi^{2}(J/#psi vertex)");
  JPSI_MUDIST_CHI2->SetTitle("");

  TCanvas *cn11 = new TCanvas("cn11","cn11",700,500);
  cn11->cd();
  JPSI_MUDIST_CHI2->SetLabelFont(62,"X");
  JPSI_MUDIST_CHI2->SetLabelFont(62,"Y");
  JPSI_MUDIST_CHI2->SetLabelOffset(0.01,"X");
  JPSI_MUDIST_CHI2->SetLabelOffset(0.01,"Y");
  JPSI_MUDIST_CHI2->SetLabelOffset(0.01,"Z");
  JPSI_MUDIST_CHI2->SetTitleSize(0.045,"X");
  JPSI_MUDIST_CHI2->SetTitleSize(0.045,"Y");
  JPSI_MUDIST_CHI2->SetTitleSize(0.045,"Z");
  JPSI_MUDIST_CHI2->SetTitleOffset(1.0,"X");
  JPSI_MUDIST_CHI2->SetTitleOffset(1.0,"Y");
  JPSI_MUDIST_CHI2->DrawCopy("cont1z");
  if (shouldsave) {
    cn11->SaveAs(folder + "Plots/Sum_JPSI_MUDIST_CHI2.jpg");
    cn11->SaveAs(folder + "Plots/Sum_JPSI_MUDIST_CHI2.pdf");
    cn11->SaveAs(folder + "Plots/Sum_JPSI_MUDIST_CHI2.eps");
    cn11->SaveAs(folder + "Plots/Sum_JPSI_MUDIST_CHI2.C");
  }

  TCanvas *cn12 = new TCanvas("cn12","cn12",700,500);
  cn12->cd();
  JPSI_MUDIST_CHI2->DrawCopy();
  TProfile *prof = JPSI_MUDIST_CHI2->ProfileX();
  prof->Draw("same");
  if (shouldsave) {
    cn12->SaveAs(folder + "Plots/Prof_JPSI_MUDIST_CHI2.jpg");
    cn12->SaveAs(folder + "Plots/Prof_JPSI_MUDIST_CHI2.pdf");
    cn12->SaveAs(folder + "Plots/Prof_JPSI_MUDIST_CHI2.eps");
    cn12->SaveAs(folder + "Plots/Prof_JPSI_MUDIST_CHI2.C");
    }

  return 0;
}

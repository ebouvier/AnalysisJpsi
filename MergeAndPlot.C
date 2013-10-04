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

void Merge(TString channel, TString date, TString numberofjets){
TString folder;
TString outname;
vector<TString> inname;
if ( channel.Contains("el") || channel.Contains("El") ) {
  cout << "Merge files for the electron channel" << endl;
  folder = "Plots_El_" + numberofjets + "_" + date + "/";
  outname = folder + "ElectronChannel_" + numberofjets +"_" + date +".root";
  inname.push_back(folder + "ElectronHad_Run2012A.root");
  inname.push_back(folder + "SingleElectron_Run2012B.root");
  inname.push_back(folder + "SingleElectron_Run2012C.root");
  inname.push_back(folder + "SingleElectron_Run2012D.root");
  } 

if ( channel.Contains("mu") || channel.Contains("Mu") ) {
  cout << "Merge files for the muon channel" << endl;
  folder = "Plots_Mu_" + numberofjets + "_" + date + "/";
  outname = folder + "MuonChannel_" + numberofjets +"_" + date +".root";
  inname.push_back(folder + "MuHad_Run2012A.root");
  inname.push_back(folder + "SingleMu_Run2012B.root");
  inname.push_back(folder + "SingleMu_Run2012C.root");
  inname.push_back(folder + "SingleMu_Run2012D.root");
  }

TH1F* JPSI_PT		= new TH1F("JPSI_PT","JPSI_PT",500,0.,500.);   
TH1F* JPSI_CHI2 	= new TH1F("JPSI_CHI2","JPSI_CHI2",200,0.,20.);
TH1F* JPSI_L		= new TH1F("JPSI_L","JPSI_L",1000,0.,1.);
TH1F* JPSI_SIGMAL	= new TH1F("JPSI_SIGMAL","JPSI_SIGMAL",5000,0.,0.005);
TH1F* JPSI_LOVERSIG	= new TH1F("JPSI_LOVERSIG","JPSI_LOVERSIG",21000,0.,7000.);
TH2F* JPSI_SIGMAL_L	= new TH2F("JPSI_SIGMAL_L","JPSI_SIGMAL_L",5000,0.,0.005,1000,0.,1.);
TH2F* JPSI_LOVERSIG_L	= new TH2F("JPSI_LOVERSIG_L","JPSI_LOVERSIG_L",14000,0.,7000.,1000,0.,1.);
TH2F* JPSI_L_PT 	= new TH2F("JPSI_L_PT","JPSI_L_PT",1000,0.,1.,500,0.,500.);
TH2F* JPSI_SIGMAL_PT	= new TH2F("JPSI_SIGMAL_PT","JPSI_SIGMAL_PT",5000,0.,0.005,500,0.,500.); 
TH2F* JPSI_LOVERSIG_PT  = new TH2F("JPSI_LOVERSIG_PT","JPSI_LOVERSIG_PT",21000,0.,7000.,500,0.,500.);
TH2F* JPSI_MUDIST_CHI2  = new TH2F("JPSI_MUDIST_CHI2","JPSI_MUDIST_CHI2",300,0.,300.,200,0.,20.);

for (unsigned int i=0; i<inname.size(); i++) {

cout << "File " << inname[i] << " loaded" << endl;

  TFile *in = TFile::Open(inname[i]);
  TH1F *JPSI_PT_in = (TH1F*)in->Get("JPSI_PT");
  TH1F *JPSI_CHI2_in = (TH1F*)in->Get("JPSI_CHI2");
  TH1F *JPSI_L_in = (TH1F*)in->Get("JPSI_L");
  TH1F *JPSI_SIGMAL_in = (TH1F*)in->Get("JPSI_SIGMAL");
  TH1F *JPSI_LOVERSIG_in = (TH1F*)in->Get("JPSI_LOVERSIG");
  TH2F *JPSI_SIGMAL_L_in = (TH2F*)in->Get("JPSI_SIGMAL_L");
  TH2F *JPSI_LOVERSIG_L_in = (TH2F*)in->Get("JPSI_LOVERSIG_L");
  TH2F *JPSI_L_PT_in = (TH2F*)in->Get("JPSI_L_PT");
  TH2F *JPSI_SIGMAL_PT_in = (TH2F*)in->Get("JPSI_SIGMAL_PT");
  TH2F *JPSI_LOVERSIG_PT_in = (TH2F*)in->Get("JPSI_LOVERSIG_PT");
  TH2F *JPSI_MUDIST_CHI2_in = (TH2F*)in->Get("JPSI_MUDIST_CHI2");

  JPSI_PT->Add(JPSI_PT_in,1.);
  JPSI_CHI2->Add(JPSI_CHI2_in,1.);
  JPSI_L->Add(JPSI_L_in,1.);
  JPSI_SIGMAL->Add(JPSI_SIGMAL_in,1.);
  JPSI_LOVERSIG->Add(JPSI_LOVERSIG_in,1.);
  JPSI_SIGMAL_L->Add(JPSI_SIGMAL_L_in,1.);
  JPSI_LOVERSIG_L->Add(JPSI_LOVERSIG_L_in,1.);
  JPSI_L_PT->Add(JPSI_L_PT_in,1.);
  JPSI_SIGMAL_PT->Add(JPSI_SIGMAL_PT_in,1.);
  JPSI_LOVERSIG_PT->Add(JPSI_LOVERSIG_PT_in,1.);
  JPSI_MUDIST_CHI2->Add(JPSI_MUDIST_CHI2_in,1.);
  
  in->Close();
  delete in;
  }  
  
TFile *out = TFile::Open(outname, "recreate");
JPSI_PT->Write(); 
JPSI_CHI2->Write(); 
JPSI_L->Write(); 
JPSI_SIGMAL->Write(); 
JPSI_LOVERSIG->Write(); 
JPSI_SIGMAL_L->Write(); 
JPSI_LOVERSIG_L->Write(); 
JPSI_L_PT->Write(); 
JPSI_SIGMAL_PT->Write(); 
JPSI_LOVERSIG_PT->Write();
JPSI_MUDIST_CHI2->Write();

cout << "Distributions written" << endl;

JPSI_PT->Reset(); 
JPSI_CHI2->Reset(); 
JPSI_L->Reset(); 
JPSI_SIGMAL->Reset(); 
JPSI_LOVERSIG->Reset(); 
JPSI_SIGMAL_L->Reset(); 
JPSI_LOVERSIG_L->Reset(); 
JPSI_L_PT->Reset(); 
JPSI_SIGMAL_PT->Reset(); 
JPSI_LOVERSIG_PT->Reset(); 
JPSI_MUDIST_CHI2->Reset();

out->Close();
delete out;  
}

void AndPlot(TString channel, TString date, TString numberofjets, bool shouldsave) {
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

TCanvas *cn1 = new TCanvas("JPSI_PT","JPSI_PT",700,500);
cn1->cd();
TH1F *JPSI_PT = (TH1F*)fi->Get("JPSI_PT");
JPSI_PT->Rebin(5);
JPSI_PT->Draw();
JPSI_PT->GetXaxis()->SetRangeUser(0.,141.);
inter = JPSI_PT->GetXaxis()->GetXmax() - JPSI_PT->GetXaxis()->GetXmin();
num = (inter/(Float_t)JPSI_PT->GetXaxis()->GetNbins());
h1_style(JPSI_PT,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","p_{T}(J/#psi) (GeV/c)",TString::Format("Events / %1.0f", num));
cn1->Modified();
if (shouldsave) {
  cn1->SaveAs(folder + "Plots/Sum_JPSI_PT.jpg");
  cn1->SaveAs(folder + "Plots/Sum_JPSI_PT.pdf");
  cn1->SaveAs(folder + "Plots/Sum_JPSI_PT.eps");
  cn1->SaveAs(folder + "Plots/Sum_JPSI_PT.C");
  }

TCanvas *cn2 = new TCanvas("JPSI_CHI2","JPSI_CHI2",700,500);
cn2->cd();
cn2->SetLogy(1);
TH1F *JPSI_CHI2 = (TH1F*)fi->Get("JPSI_CHI2");
JPSI_CHI2->Rebin(4);
JPSI_CHI2->Draw();
inter = JPSI_CHI2->GetXaxis()->GetXmax() - JPSI_CHI2->GetXaxis()->GetXmin();
num = (inter/(Float_t)JPSI_CHI2->GetXaxis()->GetNbins());
h1_style(JPSI_CHI2,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","#chi^{2}(J/#psi vertex)",TString::Format("Events / %0.1f", num));
cn2->Modified();
if (shouldsave) {
  cn2->SaveAs(folder + "Plots/Sum_JPSI_CHI2.jpg");
  cn2->SaveAs(folder + "Plots/Sum_JPSI_CHI2.pdf");
  cn2->SaveAs(folder + "Plots/Sum_JPSI_CHI2.eps");
  cn2->SaveAs(folder + "Plots/Sum_JPSI_CHI2.C");
  }

TCanvas *cn3 = new TCanvas("JPSI_L","JPSI_L",700,500);
cn3->cd();
TH1F *JPSI_L = (TH1F*)fi->Get("JPSI_L");
JPSI_L->Rebin(8);
JPSI_L->Draw();
JPSI_L->GetXaxis()->SetRangeUser(0.,0.6);
inter = JPSI_L->GetXaxis()->GetXmax() - JPSI_L->GetXaxis()->GetXmin();
num = (inter/(Float_t)JPSI_L->GetXaxis()->GetNbins());
h1_style(JPSI_L,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","c#tau(J/#psi) (cm)",TString::Format("Events / %0.2f", num));
cn3->Modified();
if (shouldsave) {
  cn3->SaveAs(folder + "Plots/Sum_JPSI_L.jpg");
  cn3->SaveAs(folder + "Plots/Sum_JPSI_L.pdf");
  cn3->SaveAs(folder + "Plots/Sum_JPSI_L.eps");
  cn3->SaveAs(folder + "Plots/Sum_JPSI_L.C");
  }

TCanvas *cn4 = new TCanvas("JPSI_SIGMAL","JPSI_SIGMAL",700,500);
cn4->cd();
TH1F *JPSI_SIGMAL = (TH1F*)fi->Get("JPSI_SIGMAL");
JPSI_SIGMAL->Rebin(10);
JPSI_SIGMAL->Draw();
inter = JPSI_SIGMAL->GetXaxis()->GetXmax() - JPSI_SIGMAL->GetXaxis()->GetXmin();
num = (inter/(Float_t)JPSI_SIGMAL->GetXaxis()->GetNbins());
h1_style(JPSI_SIGMAL,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","#Delta(c#tau)(J/#psi) (cm)",TString::Format("Events / %0.5f", num));
JPSI_SIGMAL->GetXaxis()->SetNdivisions(503);
cn4->Modified();
if (shouldsave) {
  cn4->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL.jpg");
  cn4->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL.pdf");
  cn4->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL.eps");
  cn4->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL.C");
  }

TCanvas *cn5 = new TCanvas("JPSI_LOVERSIG","JPSI_LOVERSIG",700,500);
cn5->cd();
TH1F *JPSI_LOVERSIG = (TH1F*)fi->Get("JPSI_LOVERSIG");
JPSI_LOVERSIG->Rebin(70);
JPSI_LOVERSIG->Draw();
inter = JPSI_LOVERSIG->GetXaxis()->GetXmax() - JPSI_LOVERSIG->GetXaxis()->GetXmin();
num = (inter/(Float_t)JPSI_LOVERSIG->GetXaxis()->GetNbins());
h1_style(JPSI_LOVERSIG,2,50,1,50,1001,-1111.,-1111.,510,510,20,50,1.2,0,"","#Delta(c#tau)/(c#tau)(J/#psi)",TString::Format("Events / %0.2f", num));
cn5->Modified();
if (shouldsave) {
  cn5->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG.jpg");
  cn5->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG.pdf");
  cn5->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG.eps");
  cn5->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG.C");
  }

TH2F *JPSI_SIGMAL_L = (TH2F*)fi->Get("JPSI_SIGMAL_L");
JPSI_SIGMAL_L->Rebin2D(10,8);
JPSI_SIGMAL_L->SetContour(20);
JPSI_SIGMAL_L->SetStats(0);
JPSI_SIGMAL_L->GetXaxis()->SetTitle("#Delta(c#tau)(J/#psi) (cm)");
JPSI_SIGMAL_L->GetYaxis()->SetTitle("c#tau(J/#psi) (cm)");
JPSI_SIGMAL_L->GetZaxis()->SetTitle("N_{events}");
JPSI_SIGMAL_L->SetTitle("");
JPSI_SIGMAL_L->GetYaxis()->SetRangeUser(0.,0.6);

TCanvas *cn6 = new TCanvas("cn6","cn6",525,750);
cn6->Divide(1,2);
cn6->cd(1);
JPSI_SIGMAL_L->SetLabelFont(62,"X");
JPSI_SIGMAL_L->SetLabelFont(62,"Y");
JPSI_SIGMAL_L->SetLabelOffset(0.01,"X");
JPSI_SIGMAL_L->SetLabelOffset(0.01,"Y");
JPSI_SIGMAL_L->SetLabelOffset(0.01,"Z");
JPSI_SIGMAL_L->SetTitleSize(0.045,"X");
JPSI_SIGMAL_L->SetTitleSize(0.045,"Y");
JPSI_SIGMAL_L->SetTitleSize(0.045,"Z");
JPSI_SIGMAL_L->SetTitleOffset(1.0,"X");
JPSI_SIGMAL_L->SetTitleOffset(1.0,"Y");
JPSI_SIGMAL_L->DrawCopy("cont1z");
cn6->cd(2);
JPSI_SIGMAL_L->SetTitleOffset(1.50,"X");
JPSI_SIGMAL_L->SetTitleOffset(1.80,"Y");
JPSI_SIGMAL_L->SetTitleOffset(1.0,"Z");
JPSI_SIGMAL_L->GetYaxis()->SetRangeUser(0.,0.2);
JPSI_SIGMAL_L->GetXaxis()->SetRangeUser(0.,0.0003);
JPSI_SIGMAL_L->DrawCopy("surf7z fb bb");
if (shouldsave) {
  cn6->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_L.jpg");
  cn6->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_L.pdf");
  cn6->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_L.eps");
  cn6->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_L.C");
  }

TH2F *JPSI_LOVERSIG_L = (TH2F*)fi->Get("JPSI_LOVERSIG_L");
JPSI_LOVERSIG_L->Rebin2D(70,8);
JPSI_LOVERSIG_L->SetContour(20);
JPSI_LOVERSIG_L->SetStats(0);
JPSI_LOVERSIG_L->GetXaxis()->SetTitle("#Delta(c#tau)/(c#tau)(J/#psi)");
JPSI_LOVERSIG_L->GetYaxis()->SetTitle("c#tau(J/#psi) (cm)");
JPSI_LOVERSIG_L->GetZaxis()->SetTitle("N_{events}");
JPSI_LOVERSIG_L->SetTitle("");
JPSI_LOVERSIG_L->GetYaxis()->SetRangeUser(0.,0.6);

TCanvas *cn7 = new TCanvas("cn7","cn7",525,750);
cn7->Divide(1,2);
cn7->cd(1);
JPSI_LOVERSIG_L->SetLabelFont(62,"X");
JPSI_LOVERSIG_L->SetLabelFont(62,"Y");
JPSI_LOVERSIG_L->SetLabelOffset(0.01,"X");
JPSI_LOVERSIG_L->SetLabelOffset(0.01,"Y");
JPSI_LOVERSIG_L->SetLabelOffset(0.01,"Z");
JPSI_LOVERSIG_L->SetTitleSize(0.045,"X");
JPSI_LOVERSIG_L->SetTitleSize(0.045,"Y");
JPSI_LOVERSIG_L->SetTitleSize(0.045,"Z");
JPSI_LOVERSIG_L->SetTitleOffset(1.0,"X");
JPSI_LOVERSIG_L->SetTitleOffset(1.0,"Y");
JPSI_LOVERSIG_L->DrawCopy("cont1z");
cn7->cd(2);
JPSI_LOVERSIG_L->SetTitleOffset(1.50,"X");
JPSI_LOVERSIG_L->SetTitleOffset(1.80,"Y");
JPSI_LOVERSIG_L->SetTitleOffset(1.0,"Z");
JPSI_LOVERSIG_L->GetYaxis()->SetRangeUser(0.,0.06);
JPSI_LOVERSIG_L->GetXaxis()->SetRangeUser(0.,600.);
JPSI_LOVERSIG_L->DrawCopy("surf7z fb bb");
if (shouldsave) {
  cn7->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_L.jpg");
  cn7->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_L.pdf");
  cn7->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_L.eps");
  cn7->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_L.C");
  }

TH2F *JPSI_L_PT = (TH2F*)fi->Get("JPSI_L_PT");
JPSI_L_PT->Rebin2D(8,5);
JPSI_L_PT->SetContour(20);
JPSI_L_PT->SetStats(0);
JPSI_L_PT->GetYaxis()->SetTitle("p_{T}(J/#psi) (GeV/c)");
JPSI_L_PT->GetXaxis()->SetTitle("c#tau(J/#psi) (cm)");
JPSI_L_PT->GetZaxis()->SetTitle("N_{events}");
JPSI_L_PT->SetTitle("");
JPSI_L_PT->GetYaxis()->SetRangeUser(0.,141.);
JPSI_L_PT->GetXaxis()->SetRangeUser(0.,0.6);

TCanvas *cn8 = new TCanvas("cn8","cn8",525,750);
cn8->Divide(1,2);
cn8->cd(1);
JPSI_L_PT->SetLabelFont(62,"X");
JPSI_L_PT->SetLabelFont(62,"Y");
JPSI_L_PT->SetLabelOffset(0.01,"X");
JPSI_L_PT->SetLabelOffset(0.01,"Y");
JPSI_L_PT->SetLabelOffset(0.01,"Z");
JPSI_L_PT->SetTitleSize(0.045,"X");
JPSI_L_PT->SetTitleSize(0.045,"Y");
JPSI_L_PT->SetTitleSize(0.045,"Z");
JPSI_L_PT->SetTitleOffset(1.0,"X");
JPSI_L_PT->SetTitleOffset(1.0,"Y");
JPSI_L_PT->DrawCopy("cont1z");
cn8->cd(2);
JPSI_L_PT->SetTitleOffset(1.50,"X");
JPSI_L_PT->SetTitleOffset(1.80,"Y");
JPSI_L_PT->SetTitleOffset(1.0,"Z");
JPSI_L_PT->GetXaxis()->SetRangeUser(0.,0.2);
JPSI_L_PT->DrawCopy("surf7z fb bb");
if (shouldsave) {
  cn8->SaveAs(folder + "Plots/Sum_JPSI_L_PT.jpg");
  cn8->SaveAs(folder + "Plots/Sum_JPSI_L_PT.pdf");
  cn8->SaveAs(folder + "Plots/Sum_JPSI_L_PT.eps");
  cn8->SaveAs(folder + "Plots/Sum_JPSI_L_PT.C");
  }

TH2F *JPSI_SIGMAL_PT = (TH2F*)fi->Get("JPSI_SIGMAL_PT");
JPSI_SIGMAL_PT->Rebin2D(10,5);
JPSI_SIGMAL_PT->SetContour(20);
JPSI_SIGMAL_PT->SetStats(0);
JPSI_SIGMAL_PT->GetYaxis()->SetTitle("p_{T}(J/#psi) (GeV/c)");
JPSI_SIGMAL_PT->GetXaxis()->SetTitle("#Delta(c#tau)(J/#psi) (cm)");
JPSI_SIGMAL_PT->GetZaxis()->SetTitle("N_{events}");
JPSI_SIGMAL_PT->SetTitle("");
JPSI_SIGMAL_PT->GetYaxis()->SetRangeUser(0.,141.);
JPSI_SIGMAL_PT->GetXaxis()->SetNdivisions(503);

TCanvas *cn9 = new TCanvas("cn9","cn9",525,750);
cn9->Divide(1,2);
cn9->cd(1);
JPSI_SIGMAL_PT->SetLabelFont(62,"X");
JPSI_SIGMAL_PT->SetLabelFont(62,"Y");
JPSI_SIGMAL_PT->SetLabelOffset(0.01,"X");
JPSI_SIGMAL_PT->SetLabelOffset(0.01,"Y");
JPSI_SIGMAL_PT->SetLabelOffset(0.01,"Z");
JPSI_SIGMAL_PT->SetTitleSize(0.045,"X");
JPSI_SIGMAL_PT->SetTitleSize(0.045,"Y");
JPSI_SIGMAL_PT->SetTitleSize(0.045,"Z");
JPSI_SIGMAL_PT->SetTitleOffset(1.0,"X");
JPSI_SIGMAL_PT->SetTitleOffset(1.0,"Y");
JPSI_SIGMAL_PT->DrawCopy("cont1z");
cn9->cd(2);
JPSI_SIGMAL_PT->SetTitleOffset(1.50,"X");
JPSI_SIGMAL_PT->SetTitleOffset(1.80,"Y");
JPSI_SIGMAL_PT->SetTitleOffset(1.0,"Z");
JPSI_SIGMAL_PT->GetXaxis()->SetRangeUser(0.,0.0004);
JPSI_SIGMAL_PT->DrawCopy("surf7z fb bb");
if (shouldsave) {
  cn9->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_PT.jpg");
  cn9->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_PT.pdf");
  cn9->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_PT.eps");
  cn9->SaveAs(folder + "Plots/Sum_JPSI_SIGMAL_PT.C");
  }

TH2F *JPSI_LOVERSIG_PT = (TH2F*)fi->Get("JPSI_LOVERSIG_PT");
JPSI_LOVERSIG_PT->Rebin2D(70,5);
JPSI_LOVERSIG_PT->SetContour(20);
JPSI_LOVERSIG_PT->SetStats(0);
JPSI_LOVERSIG_PT->GetYaxis()->SetTitle("p_{T}(J/#psi) (GeV/c)");
JPSI_LOVERSIG_PT->GetXaxis()->SetTitle("#Delta(c#tau)/(c#tau)(J/#psi)");
JPSI_LOVERSIG_PT->GetZaxis()->SetTitle("N_{events}");
JPSI_LOVERSIG_PT->SetTitle("");
JPSI_LOVERSIG_PT->GetYaxis()->SetRangeUser(0.,141.);

TCanvas *cn10 = new TCanvas("cn10","cn10",525,750);
cn10->Divide(1,2);
cn10->cd(1);
JPSI_LOVERSIG_PT->SetLabelFont(62,"X");
JPSI_LOVERSIG_PT->SetLabelFont(62,"Y");
JPSI_LOVERSIG_PT->SetLabelOffset(0.01,"X");
JPSI_LOVERSIG_PT->SetLabelOffset(0.01,"Y");
JPSI_LOVERSIG_PT->SetLabelOffset(0.01,"Z");
JPSI_LOVERSIG_PT->SetTitleSize(0.045,"X");
JPSI_LOVERSIG_PT->SetTitleSize(0.045,"Y");
JPSI_LOVERSIG_PT->SetTitleSize(0.045,"Z");
JPSI_LOVERSIG_PT->SetTitleOffset(1.0,"X");
JPSI_LOVERSIG_PT->SetTitleOffset(1.0,"Y");
JPSI_LOVERSIG_PT->DrawCopy("cont1z");
cn10->cd(2);
JPSI_LOVERSIG_PT->SetTitleOffset(1.50,"X");
JPSI_LOVERSIG_PT->SetTitleOffset(1.80,"Y");
JPSI_LOVERSIG_PT->SetTitleOffset(1.0,"Z");
JPSI_LOVERSIG_PT->GetXaxis()->SetRangeUser(0.,5000.);
JPSI_LOVERSIG_PT->DrawCopy("surf7z fb bb");
if (shouldsave) {
  cn10->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_PT.jpg");
  cn10->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_PT.pdf");
  cn10->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_PT.eps");
  cn10->SaveAs(folder + "Plots/Sum_JPSI_LOVERSIG_PT.C");
  }

TH2F *JPSI_MUDIST_CHI2 = (TH2F*)fi->Get("JPSI_MUDIST_CHI2");
JPSI_MUDIST_CHI2->SetContour(20);
JPSI_MUDIST_CHI2->SetStats(0);
JPSI_MUDIST_CHI2->GetYaxis()->SetTitle("3D distance (J/#psi's daughters) (#mu m)");
JPSI_MUDIST_CHI2->GetXaxis()->SetTitle("#chi^{2}(J/#psi vertex)");
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
}

void MergeAndPlot(TString channel="el", TString date="130927", TString numberofjets="4jets_top", bool shouldsave=true) {
if (shouldsave) Merge(channel,date,numberofjets);
AndPlot(channel,date,numberofjets,shouldsave);
}

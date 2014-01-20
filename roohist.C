#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "TString.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TObject.h"
#include "TVectorD.h"
#include "RooMsgService.h"
#include "RooWorkspace.h"
#include "RooChi2Var.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooAbsReal.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooMomentMorph.h"
#include "RooArgList.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooMCStudy.h"

using std::cout ;
using std::endl ;

void leg_style(TLegend *leg,
    int text_size = 0.035,
    int text_font = 62,
    int text_align = 12,
    int fill_style = 1,
    int fill_color = 10) {

  leg->SetTextSize(text_size);
  leg->SetTextFont(text_font);
  leg->SetTextAlign(text_align);
  leg->SetFillStyle(fill_style);
  leg->SetFillColor(fill_color);
}

int h1_style(TH1 *h,
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
  h->SetTitle(title);

  return 0;
}


int graph_style(TGraph *gr,
    const char* name="",
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
    const char* title="",
    const char* xtitle="",
    const char* ytitle="") {

  gr->SetLineWidth(line_width);
  gr->SetLineColor(line_color);
  gr->SetLineStyle(line_style);
  gr->SetFillColor(fill_color);
  gr->SetFillStyle(fill_style);
  gr->SetMaximum(y_max);
  gr->SetMinimum(y_min);
  gr->GetXaxis()->SetNdivisions(ndivx);
  gr->GetYaxis()->SetNdivisions(ndivy);

  gr->SetMarkerStyle(marker_style);
  gr->SetMarkerColor(marker_color);
  gr->SetMarkerSize(marker_size);

  gr->GetXaxis()->SetLabelFont(62);	// 42
  gr->GetYaxis()->SetLabelFont(62);	// 42
  gr->GetXaxis()->SetLabelOffset(0.01);  // D=0.005
  gr->GetYaxis()->SetLabelOffset(0.01);  // D=0.005
  gr->GetXaxis()->SetLabelSize(0.05);
  gr->GetYaxis()->SetLabelSize(0.05);
  gr->GetXaxis()->SetTitleOffset(1.0);
  gr->GetYaxis()->SetTitleOffset(1.0);
  gr->GetXaxis()->SetTitleSize(0.045);
  gr->GetYaxis()->SetTitleSize(0.045);
  gr->GetXaxis()->SetTitle(xtitle);
  gr->GetYaxis()->SetTitle(ytitle);
  gr->SetTitle(title);
  gr->SetName(name);

  return 0;
}


int roohist(TString channel) {

//  gROOT->SetStyle("Plain");
//  gSystem->Load("libRooFit");
  using std::cout ;
  using std::endl ;
  using namespace RooFit ;
	bool runMinos = kTRUE;  //Remove Minos when running toys (too slow)
  TH1::SetDefaultSumw2(true);

  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(52);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);

  double rebin;
  //TString textchannel;
  TString sInFileData;

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "mu";
  //  textchannel = "#mu + Jets channel";
    rebin = 34;
    cout << "Don't forget : hadd Muons.root MuHad_Run2012A.root SingleMu_Run2012B.root SingleMu_Run2012C.root SingleMu_Run2012D.root ..." << endl;
    sInFileData = "Muons.root";
  }
  if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "el";
  //  textchannel = "e + Jets channel";
    rebin = 50;
    cout << "Don't forget : hadd Electrons.root ElectronHad_Run2012A.root SingleElectron_Run2012B.root SingleElectron_Run2012C.root SingleElectron_Run2012D.root ..." << endl;
    sInFileData = "Electrons.root";
  }

  vector<TString> vecMassMC;
  vecMassMC.push_back("158");  
  //vecMassMC.push_back("163"); 
  //vecMassMC.push_back("167");
  //vecMassMC.push_back("169"); 
  vecMassMC.push_back("170"); 
  //vecMassMC.push_back("171");
  //vecMassMC.push_back("172"); 
  //vecMassMC.push_back("173"); 
  //vecMassMC.push_back("174"); 
  //vecMassMC.push_back("175");  
  vecMassMC.push_back("176"); 
  //vecMassMC.push_back("177");
  //vecMassMC.push_back("179"); 
  //vecMassMC.push_back("183"); 
  vecMassMC.push_back("188");

  vector<double> vecMass;
  vecMass.push_back(158); 
  //vecMass.push_back(163); 
  //vecMass.push_back(167);
  //vecMass.push_back(169); 
  vecMass.push_back(170);  
  //vecMass.push_back(171);
  //vecMass.push_back(172); 
  //vecMass.push_back(173); 
  //vecMass.push_back(174); 
  //vecMass.push_back(175); 
  vecMass.push_back(176); 
  //vecMass.push_back(177);
  //vecMass.push_back(179);  
  //vecMass.push_back(183); 
  vecMass.push_back(188);

  if (vecMassMC.size()!=vecMass.size()) return 1;
  const unsigned int numberOfPoints = vecMass.size();
  cout << "NoP = " << numberOfPoints << endl;

  //---- Variables
  RooRealVar mtl("trilepmass", "M_{J/#psi+l}", 15., 200., "GeV/c^{2}");
  // for develepment: test on TTbar173
  sInFileData = "TTbar173.root"; 
  rebin = 10;
  TFile *fiData = TFile::Open(sInFileData);
  TH1F* histData = (TH1F*) fiData->Get("TOP_M_RECO_ALL");
  histData->Rebin(rebin); // 10);
  RooDataHist rooHistData("HIST_DATA", "HIST_DATA", RooArgSet(mtl), histData,1.); 
  
  RooRealVar mtop("topmass", "M_{t}", 173, 158, 188, "GeV/c^{2}");
  RooArgList pdfList;
  TVectorD hypoMass(numberOfPoints);
  RooFitResult *fitRes = 0;

  double x[numberOfPoints], y[numberOfPoints];
  for (unsigned int i=0; i<numberOfPoints; i++) {
    x[i] = vecMass[i];
    hypoMass(i) = vecMass[i];
    TFile *fiMC = TFile::Open("TTbar"+vecMassMC[i]+".root");
    TH1F* histMC = (TH1F*) fiMC->Get("TOP_M_RECO_ALL");
    histMC->Rebin(10); // 17);
	  histMC->Scale((rebin*histData->Integral())/(10.*histMC->Integral())); //histMC->Scale(histData->Integral()/histMC->Integral());
    RooDataHist *rooHistMC = new RooDataHist("HIST_MC_"+vecMassMC[i], "HIST_MC_"+vecMassMC[i], RooArgSet(mtl), histMC,1.); 
    RooHistPdf *pdfMC = new RooHistPdf("HISTPDF_MC_"+vecMassMC[i], "HISTPDF_MC_"+vecMassMC[i], RooArgSet(mtl), *rooHistMC);
    RooChi2Var chi2Var("chi2","chi2",*pdfMC,rooHistData);
    y[i] = chi2Var.getVal();
    pdfList.add(RooArgList(*pdfMC));
  }
  RooMomentMorph morphMC("morphMC", "morphMC", mtop, RooArgList(mtl), pdfList, hypoMass, RooMomentMorph::NonLinear);
  /*	
   *	Linear	
	 *  NonLinear	
	 *  NonLinearPosFractions	
	 *  NonLinearLinFractions	
	 *  SineLinear
   */
  //fitRes = morphMC.chi2FitTo(rooHistData);
  fitRes = morphMC.fitTo(rooHistData,Extended(),Minos(runMinos),Save(kTRUE));
  //fitRes->Print();
  //cout << "RooMomentMorph created... minNll = " << fitRes->minNll() << endl;
  //cout << "M_{t} = " << mtop.getVal() << " +/- " << mtop.getError() << " GeV/c^{2}" << endl;

  TCanvas *cn_r = new TCanvas("cn_r","cn_r",700,500);
  cn_r->cd();
  TGraph *gr = new TGraph(numberOfPoints,x,y);
  gr->Draw("A*");

  RooAbsReal* nll = morphMC.createNLL(rooHistData,NumCPU(1));//,Extended(),Minos(runMinos),Save(kTRUE));
  TCanvas *cn_l = new TCanvas("cn_l","cn_l",700,500);
  cn_l->cd();
  RooPlot* likeframe = mtop.frame(Title("-log(likelihood) vs M_{t}"));
  nll->plotOn(likeframe,ShiftToZero());
  likeframe->Draw();

  RooAbsReal* chi2 = morphMC.createChi2(rooHistData,NumCPU(1));//,Extended(),Minos(runMinos),Save(kTRUE));
  TCanvas *cn_c = new TCanvas("cn_c","cn_c",700,500);
  cn_c->cd();
  RooPlot* chiframe = mtop.frame(Title("chi2 vs M_{t}"));
  chi2->plotOn(chiframe,ShiftToZero());
  chiframe->Draw();

  fitRes->Print();
  cout << "nll = " << nll->getVal() << endl;
  cout << "chi2 = " << chi2->getVal() << endl;
  //latex->DrawLatex(157,10,res);

  return 0;
}

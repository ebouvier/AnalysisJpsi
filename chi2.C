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

double DoChi2(TH1* hist1, TH1* hist2) {
  double chi2ondf = 0.;
  double chi2 = 0.;
  int ndf = 0;
  for (int i=0; i<hist1->GetNbinsX(); i++) {
    if (hist1->GetBinContent(i+1)==0) continue;  
    double n1 = hist1->GetBinContent(i+1);
    double n2 = hist2->GetBinContent(i+1);
    chi2 += pow(n1-n2,2.)/fabs(n1);
    ++ndf;
  }
  chi2ondf = chi2/(double)ndf;
  //cout << "chi2 = " << chi2 << ", ndf = " << ndf << ", chi2/ndf = " << chi2ondf << endl;  
  return chi2ondf;
}

double OpenAndCompute(TH1* histdata, TString massMC, double rebin, double integral, const unsigned int i, TCanvas *cn_s, TLegend *leg_s) {

  TFile* fi_mc = TFile::Open("TTbar"+massMC+".root");
  TH1F* histmc = fi_mc->Get("TOP_M_RECO_ALL");
  histmc->Rebin(rebin);
  double integral_mc = histmc->Integral();
  //cout << "Before : histmc->Integral() = " << histmc->Integral() << endl;
  histmc->Scale(integral/integral_mc);
  //cout << "After : histmc->Integral() = " << histmc->Integral() << endl;
  cn_s->cd();
  h1_style(histmc, 2, 40+i, 1, 40+i, 1001, -1111., -1111., 510, 510, 20, 40+i, 1.2, 0, 
      "M_{J/#psi+l} for data and Pythia6 samples", histdata->GetXaxis()->GetTitle(), histdata->GetYaxis()->GetTitle());
  histmc->Draw("same");
  leg_s->AddEntry(histmc,massMC+" GeV/c^{2}","lp");  
  double result = DoChi2(histdata,histmc);
  //delete histmc; delete fi_mc;
  return result;
}


int chi2(TString channel) {

  double rebin;
  TString textchannel;
  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "mu";
    textchannel = "#mu + Jets channel";
    rebin = 34;
    TFile* fi_data = TFile::Open("MJpsil_data_Py6_mu.root");
  }
  if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "el";
    textchannel = "e + Jets channel";
    rebin = 50;
    TFile* fi_data = TFile::Open("MJpsil_data_Py6_el.root");
  }
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(52);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
 
  TH1F* histdata = (TH1F*) fi_data->Get("M_JPSIL");
  h1_style(histdata, 2, 2, 1, 50, 3003, -1111., -1111., 510, 510, 20, 2, 1.2, 0, 
      "M_{J/#psi+l} for data and Pythia6 samples", histdata->GetXaxis()->GetTitle(), histdata->GetYaxis()->GetTitle());
  double integral = histdata->Integral();
  //cout << "histdata->Integral() = " << histdata->Integral() << endl;

  vector<TString> vecMassMC;
  vecMassMC.push_back("158"); vecMassMC.push_back("163"); vecMassMC.push_back("167");
  vecMassMC.push_back("169"); vecMassMC.push_back("170"); vecMassMC.push_back("171");
  vecMassMC.push_back("172"); vecMassMC.push_back("173"); vecMassMC.push_back("174");
  vecMassMC.push_back("175"); vecMassMC.push_back("176"); vecMassMC.push_back("177");
  vecMassMC.push_back("179"); vecMassMC.push_back("183"); vecMassMC.push_back("188");

  vector<double> vecMass;
  vecMass.push_back(158); vecMass.push_back(163); vecMass.push_back(167);
  vecMass.push_back(169); vecMass.push_back(170); vecMass.push_back(171);
  vecMass.push_back(172); vecMass.push_back(173); vecMass.push_back(174);
  vecMass.push_back(175); vecMass.push_back(176); vecMass.push_back(177);
  vecMass.push_back(179); vecMass.push_back(183); vecMass.push_back(188);

  if (vecMassMC.size()!=vecMass.size()) break;

  TCanvas *cn_s = new TCanvas("cn_s","cn_s",700,500);
  cn_s->cd();
  histdata->Draw("hist");
  TLegend *leg_s = new TLegend(0.6,0.41,0.89,0.89,NULL,"brNDC");
  leg_s-> SetNColumns(2);
  leg_style(leg_s);
  leg_s->AddEntry(histdata,"Data","lf");

  const unsigned int numberOfPoints = vecMass.size();
  double x[numberOfPoints]; double y[numberOfPoints];
  for (unsigned int i=0; i<numberOfPoints; i++) {
    x[i] = vecMass[i];
    y[i] = OpenAndCompute(histdata, vecMassMC[i], rebin, integral, i, cn_s, leg_s);
    cout << "mt = " << x[i] << " GeV/c2 -> chi2/ndf = " << y[i] << endl;
  }

  leg_s->Draw();
  latex->DrawLatex(151,1.11*histdata->GetMaximum(),textchannel);
  gPad->Update();
  cn_s->SaveAs("Hist_data_mc_"+channel+".jpg");
  cn_s->SaveAs("Hist_data_mc_"+channel+".eps");
  cn_s->SaveAs("Hist_data_mc_"+channel+".C");
  cn_s->SaveAs("Hist_data_mc_"+channel+".pdf");

  TGraph *chi2 = new TGraph(numberOfPoints,x,y);
  TFitResultPtr fitptr = chi2->Fit("pol2","FS","");
  TF1 *fit = chi2->GetFunction("pol2");
  fit->SetLineColor(9);
  Double_t err_up[numberOfPoints];
  Double_t err_down[numberOfPoints];
  Double_t errval[numberOfPoints];
  fitptr->GetConfidenceIntervals(numberOfPoints,1,1,x,errval,0.68);
  for(int k=0; k<numberOfPoints; ++k) {
    double error = errval[k];
    err_up[k] = fit->Eval(x[k])+error;
    err_down[k] = fit->Eval(x[k])-error;
  }
  TGraph *gr_up = new TGraph(numberOfPoints,x,err_up);
  gr_up->Fit("pol2","FQ","");
  TF1 *fit_up = gr_up->GetFunction("pol2");
  TGraph *gr_down = new TGraph(numberOfPoints,x,err_down);
  gr_down->Fit("pol2","FQ","");
  TF1 *fit_down = gr_down->GetFunction("pol2");  
  double mean = fit->GetMinimumX();
  //68% confidence level interval on the parabolic fit and chi2
  double err = (fit_down->GetX(1.+fit->GetMinimum(),173.,188.)-fit_down->GetX(1.+fit->GetMinimum(),158.,173.))/2.;
  TString result = TString::Format("Par minimisation de chi^{2} : \n \t \t m_{t} = (%3.1f #pm %1.1f) GeV/c^{2}", mean, err);

  TCanvas *cn_c = new TCanvas("cn_c","cn_c",700,500);
  cn_c->cd();
  graph_style(chi2,"chi2",1,9,1,9,1001,-1111.,-1111.,510,510,20,9,1.2,"#chi^{2}/ndf between data and Pythia6 samples",
      "M_{t} (GeV/c^{2})","#chi^{2}/ndf");
  chi2->Draw("AP");
  fit_up->SetLineColor(38); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(38); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  latex->DrawLatex(181,1.09*fit->GetMaximum(),textchannel);
   gPad->Update();
  getchar();

  cn_c->SaveAs("Chi2_"+channel+".jpg");
  cn_c->SaveAs("Chi2_"+channel+".eps");
  cn_c->SaveAs("Chi2_"+channel+".C");
  cn_c->SaveAs("Chi2_"+channel+".pdf");

  delete fit_down; delete fit_up; delete chi2; 
  delete gr_down; delete gr_up; 
  delete leg_s; delete cn_s; delete cn_c;
  delete histdata; delete fi_data;

  cout << result << endl;

  return 0;
}

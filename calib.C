void latex_style(TLatex *latex,
    double text_size = 0.035,
    int text_font = 62,
    int text_align = 22,
    int text_color = 1) {
  latex->SetTextSize(text_size);
  latex->SetTextFont(text_font);
  latex->SetTextAlign(text_align);
  latex->SetTextColor(text_color);
  latex->SetNDC();
}

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

void poly_style(TPolyLine *pl,
    int line_width=2,
    int line_color=1,
    int line_style=1,
    int fill_color=1,
    int fill_style=3001) {
  pl->SetLineWidth(line_width);
  pl->SetLineColor(line_color);
  pl->SetLineStyle(line_style);
  pl->SetFillColor(fill_color);
  pl->SetFillStyle(fill_style);
}

void line_style(TLine *li,
    int line_width=2,
    int line_color=1,
    int line_style=1) {
  li->SetLineWidth(line_width);
  li->SetLineColor(line_color);
  li->SetLineStyle(line_style);
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
  h->SetTitle(title);
}

void graphasymerror_style(TGraphAsymmErrors *gr,
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

}

double *step(string name,double inf,double sup) {

  TFile *res = TFile::Open(name.c_str());

  //---- Variables
  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV/c^{2}");
  RooRealVar weight("weight", "weight", 0., 2.);


  //---- Fit for all
  TTree *M_RECO_ALL = (TTree*)res->Get("M_RECO_ALL");

  RooDataSet *dataset = new RooDataSet("dataset", "dataset for reco events", RooArgSet(mtl, weight), Import(*M_RECO_ALL), WeightVar(weight));

  dataset->Print();

  RooRealVar mean("mean", "mass",70.,50.,90.) ;
  RooRealVar width("width", "width",25.,15.,35.) ;

  RooGaussian pdf("pdf","pdf",mtl,mean,width);

  pdf.fitTo(*dataset,Range(inf,sup));

  TCanvas *cn = new TCanvas("cn","all pairing (reco)",700,500);
  cn->cd();
  RooPlot* massframe = mtl.frame(Title("Mass of the combination of the reco J/#psi and the reco isolated lepton")) ;
  dataset->plotOn(massframe,Binning(50)) ;
  pdf.plotOn(massframe,Range(inf,sup)) ;
  massframe->Draw();

  /*  
      TLatex *text = new TLatex();
      text->SetTextFont(62);
      text->SetTextColor(1);
      text->SetTextAlign(22);
      text->SetTextSize(0.05);
      TString tempo;
      cin >> tempo;
      TString text_text = "M_{t} = "+tempo+" GeV/c^{2}";
      text->DrawLatex(150,120,text_text); 
      */
  gPad->Update();
  //getchar();
  //TString namesave = "PlotsCalib/"+name+".pdf";
  //cn->SaveAs(namesave);

  //----------------------------- Fit parameters
  // cout << "Reco all         : " << mean.getVal() << " +/- "<< mean.getError() << endl;

  double *mean_err = new double[2];
  mean_err[0]=mean.getVal();
  mean_err[1]=mean.getError();

  return mean_err;
}


int calib(TString channel) {

  gROOT->SetStyle("Plain");
  gSystem->Load("libRooFit");
  using namespace RooFit ;

  TString leg_header;
  TString filename;
  TString calibname;
  TString trilepname;
  TString Ytitle;

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    channel = "Muons";
    leg_header = "Muons channel";
    filename = "MJpsil_data_Py6_mu.root";
    calibname = "Calib_mu";
    trilepname = "MJpsil_data_mu";
    Ytilte = "Events/10"; 
  }

  if ( channel.Contains("el") || channel.Contains("El") ) {
    channel = "Electrons";
    leg_header = "Electrons channel";
    filename = "MJpsil_data_Py6_el.root";
    calibname = "Calib_el";
    trilepname = "MJpsil_data_el";
    Ytilte = "Events/15"; 
  }

  double xxmin = 30.;
  double xxmax = 110.;

  //----- Fit des data

  TFile *fi = TFile::Open(filename);
  cout << "Opening " << filename << endl;
  TH1F* histo = fi->Get("M_JPSIL");
  histo->GetYaxis()->SetTitle(Ytitle); 
  h1_style(histo,0,38,1,38,3002,histo->GetMinimum(),1.2*histo->GetMaximum(),510,510,20,38,1.,0.);

  RooRealVar mtl("mass", "M_{J/#psi+l}", 0., 250., "GeV/c^{2}");
  RooDataHist *datahist = new RooDataHist("datahist", "datahist for data", RooArgList(mtl), histo, 1.);
  RooRealVar mean("mean", "mass",70.,60.,80.) ;
  RooRealVar width("width", "width",30.,20.,40.) ;
  RooGaussian pdf("pdf","pdf",mtl,mean,width);
  pdf.fitTo(*datahist,Range(xxmin,xxmax));
  Double_t mean_gaus = mean.getVal();
  Double_t err_gaus = mean.getError();
  TString text_par_gaus = TString::Format("M_{J/#psi+l} = (%0.1f #pm %0.1f) GeV/c^{2}",mean_gaus,err_gaus);

  TCanvas *cn_trilep = new TCanvas("cn_trilep","cn_trilep",700,500);
  cn_trilep->cd();
  RooPlot* massframe = mtl.frame(Title("Mass of the combination of the reco J/#psi and the reco isolated lepton")) ;
  datahist->plotOn(massframe,MarkerColor(38),LineColor(38)) ;
  pdf.plotOn(massframe,LineColor(38),Range(xxmin,xxmax));
  massframe->Draw();
  histo->Draw("samehist");

  TLegend *leg_trilep = new TLegend(0.54,0.7,0.89,0.88,NULL,"brNDC");
  leg_style(leg_trilep,0.035,62,12,1,10,1);
  leg_trilep->SetHeader(leg_header);
  leg_trilep->AddEntry((TObject*)0, "Gaussian fit:","");
  leg_trilep->AddEntry(massframe->findObject("h_datahist"),"t#bar{t} signal within data","lp");
  leg_trilep->AddEntry((TObject*)0, text_par_gaus,"");
  leg_trilep->Draw();

  gPad->Update();

  //----- Fit des samples Pythia et courbe de calibration

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

  const unsigned int numberOfPoints = vecMass.size();
  double x[numberOfPoints]; double exl[numberOfPoints]; double exr[numberOfPoints];
  double y[numberOfPoints]; double ey[numberOfPoints];

  for (unsigned int ind=0; ind<numberOfPoints; ind++) { 
    string name_TTbar = "TTbar"+vecMassMC[ind]+".root";
    cout << "Open file " << name_TTbar << endl;
    double *mean_err_TTbar = step(name_TTbar,xxmin,xxmax);
    y[ind] = mean_err_TTbar[0];
    ey[ind] = mean_err_TTbar[1];
    x[ind] = vecMass[ind];
    exl[ind] = 0.;
    exr[ind] = 0.;
  }

  cout << "=============== " << channel <<" channel ================= \n" <<endl;

  cout << text_par_gaus << endl;

  for (unsigned int ind=0; ind<numberOfPoints; ind++){
    cout << "File TTbar"<< vecMass[ind] << " : " << y[ind] << " +/- "<< ey[ind] << endl;
  }    

  TGraphAsymmErrors *gr = new TGraphAsymmErrors(numberOfPoints,x,y,exl,exr,ey,ey);
  TFitResultPtr fitptr = gr->Fit("pol1","FS","");
  TF1* fit = gr->GetFunction("pol1");
  Double_t slope = fitptr->Parameter(1);
  Double_t err = fitptr->ParError(1);
  TString leg_title = TString::Format("Calibration curve : slope of %0.2f #pm %0.2f",slope,err);
  cout << leg_title << endl;
  TString leg_title2 = TString::Format("ordonnee a l'origine of %0.2f #pm %0.2f",fitptr->Parameter(0),fitptr->ParError(0));
  cout << leg_title2 << endl;
  Double_t chi2 = fitptr->Chi2();
  Double_t ndf = fitptr->Ndf();
  cout << "Chi2/NDF = " << chi2/ndf << endl;

  Double_t err_up[numberOfPoints];
  Double_t err_down[numberOfPoints];
  Double_t errval[numberOfPoints];
  fitptr->GetConfidenceIntervals(numberOfPoints,1,1,x,errval,0.68);

  for(int i=0; i<numberOfPoints; ++i) {
    double error = errval[i];
    err_up[i] = fit->Eval(x[i])+error;
    err_down[i] = fit->Eval(x[i])-error;
  }

  TGraph *gr_up = new TGraph(numberOfPoints,x,err_up);
  gr_up->Fit("pol2","FQ","");
  TF1 *fit_up = gr_up->GetFunction("pol2");
  TGraph *gr_down = new TGraph(numberOfPoints,x,err_down);
  gr_down->Fit("pol2","FQ","");
  TF1 *fit_down = gr_down->GetFunction("pol2");  

  TLegend *leg_calib = new TLegend(0.14,0.75,0.67,0.88,NULL,"brNDC");
  leg_calib->AddEntry(gr,leg_title,"lp");
  leg_calib->SetHeader(leg_header);

  Float_t x_horiz[4]={gr->GetXaxis()->GetXmin(),fit->GetX(mean_gaus+err_gaus,0,250),fit->GetX(mean_gaus-err_gaus,0,250),gr->GetXaxis()->GetXmin()};
  Float_t y_horiz[4]={mean_gaus+err_gaus,mean_gaus+err_gaus,mean_gaus-err_gaus,mean_gaus-err_gaus};
  TPolyLine *horiz = new TPolyLine(4,x_horiz,y_horiz);
  TLine *horiz_sup = new TLine(x_horiz[0], y_horiz[0], x_horiz[1], y_horiz[1]);
  TLine *horiz_med = new TLine(gr->GetXaxis()->GetXmin(), mean_gaus, fit->GetX(mean_gaus,0,250), mean_gaus);
  TLine *horiz_inf = new TLine(x_horiz[2], y_horiz[2], x_horiz[3], y_horiz[3]);
  Float_t x_vert_min[4]={fit_up->GetX(mean_gaus-err_gaus,0,250),fit_up->GetX(mean_gaus-err_gaus,0,250),x_horiz[2],x_horiz[2]};
  Float_t y_vert_min[4]={gr->GetYaxis()->GetXmin(),mean_gaus-err_gaus,mean_gaus-err_gaus,gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_min = new TPolyLine(4,x_vert_min,y_vert_min);
  Float_t x_vert_mean[4]={x_horiz[2],x_horiz[2],x_horiz[1],x_horiz[1]};
  Float_t y_vert_mean[4]={gr->GetYaxis()->GetXmin(),y_horiz[2],y_horiz[1],gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_mean = new TPolyLine(4,x_vert_mean,y_vert_mean);
  Float_t x_vert_max[4]={x_horiz[1],x_horiz[1],fit_down->GetX(mean_gaus+err_gaus,0,250),fit_down->GetX(mean_gaus+err_gaus,0,250)};
  Float_t y_vert_max[4]={gr->GetYaxis()->GetXmin(),mean_gaus+err_gaus,mean_gaus+err_gaus,gr->GetYaxis()->GetXmin()};
  TPolyLine *vert_max = new TPolyLine(4,x_vert_max,y_vert_max);
  TLine *vert1 = new TLine(x_vert_min[0],y_vert_min[0],x_vert_min[1],y_vert_min[1]);
  TLine *vert2 = new TLine(x_vert_mean[0],y_vert_mean[0],x_vert_mean[1],y_vert_mean[1]);
  TLine *vert3 = new TLine(fit->GetX(mean_gaus,0,250),y_vert_mean[0],fit->GetX(mean_gaus,0,250),mean_gaus);
  TLine *vert4 = new TLine(x_vert_mean[3],y_vert_mean[3],x_vert_mean[2],y_vert_mean[2]);
  TLine *vert5 = new TLine(x_vert_max[3],y_vert_max[3],x_vert_max[2],y_vert_max[2]);
  TLatex *top_m = new TLatex();
  TString text_top_m; 
  double pm_fit = (x_vert_mean[3]-x_vert_mean[0])/2.;
  double p_fit = x_vert_max[3]-x_vert_mean[3];
  double m_fit = x_vert_mean[0]-x_vert_min[0];
  if (fabs(p_fit-m_fit)<0.1) {
    text_top_m= TString::Format("#splitline{M_{J/#psi+l} = (%0.1f #pm %0.1f) GeV/c^{2}}{M_{t} = (%0.1f #pm %0.1f #pm %0.1f) GeV/c^{2}}",mean_gaus,err_gaus,
        fit->GetX(mean_gaus,0,250),pm_fit, m_fit);
    cout << TString::Format("M_{t} = (%0.1f #pm %0.1f #pm %0.1f) GeV/c^{2}",fit->GetX(mean_gaus,0,250),pm_fit,m_fit) << endl;
  } else {
    text_top_m= TString::Format("#splitline{M_{J/#psi+l} = (%0.1f #pm %0.1f) GeV/c^{2}}{M_{t} = (%0.1f #pm %0.1f #splitline{_{+ %0.1f}}{_{- %0.1f}}) GeV/c^{2}}",mean_gaus,err_gaus,
        fit->GetX(mean_gaus,0,250),pm_fit, p_fit, m_fit);
    cout << TString::Format("M_{t} = (%0.1f #pm %0.1f ^{+ %0.1f}_{- %0.1f}) GeV/c^{2}",fit->GetX(mean_gaus,0,250),pm_fit,p_fit,m_fit) << endl;
  }

  TCanvas *cn_calib = new TCanvas("cn_calib", "cn_calib",700,500);
  cn_calib->cd();
  float gr_xmin = 0;
  if (x_horiz[0]<x_vert_min[0]-2) gr_xmin = x_horiz[0]; else gr_xmin = x_vert_min[0]-2;
  float gr_xmax = 0;
  if (x[numberOfPoints-1]>x_vert_max[3]) gr_xmax = x[numberOfPoints-1]+3; else gr_xmax = x_vert_max[3]+3;
  float gr_ymin = 0;
  if (y_vert_min[0]<x_vert_min[0]-5) gr_ymin = y_vert_min[0]; else gr_ymin = y_horiz[3]-5;
  float gr_ymax = 0;
  if (y[numberOfPoints-1]>y_horiz[0]) gr_ymax = y[numberOfPoints-1]+2; else gr_ymax = y_horiz[0]+11;
  TH1F* histo_temp = new TH1F("histo_temp","histo_temp",1,gr_xmin,gr_xmax);
  h1_style(histo_temp,1,1,1,1,1001,gr_ymin,gr_ymax,510,510,20,1,1.2,0,
      "Top mass measurement","M_{t} (GeV/c^{2})","M_{J/#psi+l} (GeV/c^{2})");
  histo_temp->Draw();
  graphasymerror_style(gr,"gr",2,30,1,30,1001,gr_ymin,gr_ymax,510,510,21,36,1.,"","","");
  gr->Draw("P");
  cn_calib->Update();
  fit->SetLineColor(30);
  fit_up->SetLineColor(29); fit_up->SetLineStyle(2); fit_up->SetLineWidth(2);
  fit_up->Draw("same");
  fit_down->SetLineColor(29); fit_down->SetLineStyle(2); fit_down->SetLineWidth(2);
  fit_down->Draw("same");
  leg_style(leg_calib);
  leg_calib->Draw();  
  poly_style(horiz,0,30,1,9,3002);
  horiz->Draw("f");
  horiz->Draw("same");
  line_style(horiz_sup,2,9,2);
  horiz_sup->Draw("same");
  line_style(horiz_med,2,4,1);
  horiz_med->Draw("same");
  line_style(horiz_inf,2,9,2);
  horiz_inf->Draw("same");
  poly_style(vert_min,0,9,2,38,3003);
  vert_min->Draw("f");
  vert_min->Draw("same");
  poly_style(vert_mean,0,30,1,9,3002);
  vert_mean->Draw("f");
  vert_mean->Draw("same");
  poly_style(vert_max,2,38,2,38,3003);
  vert_max->Draw("f");
  vert_max->Draw("same");
  line_style(vert1,2,38,2);
  vert1->Draw("same");
  line_style(vert2,2,9,2);
  vert2->Draw("same");
  line_style(vert3,2,4,1);
  vert3->Draw("same");
  line_style(vert4,2,9,2);
  vert4->Draw("same");
  line_style(vert5,2,38,2);
  vert5->Draw("same");
  latex_style(top_m);
  top_m->DrawLatex(0.3,0.68,text_top_m);

  cn_calib->SaveAs(calibname+".jpg");
  cn_calib->SaveAs(calibname+".eps");
  cn_calib->SaveAs(calibname+".C");
  cn_calib->SaveAs(calibname+".pdf");
  cn_trilep->SaveAs(trilepname+".jpg");
  cn_trilep->SaveAs(trilepname+".eps");
  cn_trilep->SaveAs(trilepname+".C");
  cn_trilep->SaveAs(trilepname+".pdf");

  return 0;
}

void PlotAndRun(TString channel, bool print = true) {  

  if (print) gROOT->SetBatch(true); //Speeds things up by not displaying plots in canvas
  gROOT->ProcessLine(".L ../PlotIt/PlotIt_cc.so");

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    //PlotIt toto("../PlotIt/input_mu.list",19771,1.);
    PlotIt toto("../PlotIt/input_mu_0jets.list",19771,1.);
    }
  if ( channel.Contains("el") || channel.Contains("El") ) {
    //PlotIt toto("../PlotIt/input_el.list",19767,1.);
    PlotIt toto("../PlotIt/input_el_0jets.list",19767,1.);
    }

  if ( channel.Contains("mu") || channel.Contains("Mu") ) {
    toto.plotstack("MUONS_ETA",2,1,"#eta(isolated #mu)","right");
    toto._hdata->GetXaxis()->SetRangeUser(-2.2,2.2);
    toto._hdata->GetYaxis()->SetRangeUser(0.,50.);
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(-2.4,1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "#mu + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(-2.2,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/MUONS_ETA.pdf");
      c1->Print("Plots/MUONS_ETA.jpg");
      c1->Print("Plots/MUONS_ETA.eps");
      c1->Print("Plots/MUONS_ETA.C");
    }
    toto.plotstack("MUONS_PFISO",1,1,"#mu isolation","right");
    toto._hdata->GetXaxis()->SetRangeUser(0,0.13);
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "#mu + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(0.01,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/MUONS_PFISO.pdf");
      c1->Print("Plots/MUONS_PFISO.jpg");
      c1->Print("Plots/MUONS_PFISO.eps");
      c1->Print("Plots/MUONS_PFISO.C");
    }
    toto.plotstack("MUONS_PT",10,1,"p_{T}(isolated #mu) (GeV/c)","right");
    toto._hdata->GetXaxis()->SetRangeUser(0,245);
    toto._hdata->GetYaxis()->SetRangeUser(0,70.);
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "#mu + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(10.,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/MUONS_PT.pdf");
      c1->Print("Plots/MUONS_PT.jpg");
      c1->Print("Plots/MUONS_PT.eps");
      c1->Print("Plots/MUONS_PT.C");
    }
  }

  if ( channel.Contains("el") || channel.Contains("El") ) {
    toto.plotstack("ELECTRONS_ETA",2,1,"#eta(isolated e)","right");
    toto._hdata->GetXaxis()->SetRangeUser(-2.5,2.5);
    toto._hdata->GetYaxis()->SetRangeUser(0,60);
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(-2.55,1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "e + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(-2.2,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/ELECTRONS_ETA.pdf");
      c1->Print("Plots/ELECTRONS_ETA.jpg");
      c1->Print("Plots/ELECTRONS_ETA.eps");
      c1->Print("Plots/ELECTRONS_ETA.C");
    }
    toto.plotstack("ELECTRONS_PFISO",1,1,"e isolation","right");
    toto._hdata->GetXaxis()->SetRangeUser(0,0.15);
    toto._hdata->GetYaxis()->SetTitle("Events / 0.01");
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "e + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(0.01,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/ELECTRONS_PFISO.pdf");
      c1->Print("Plots/ELECTRONS_PFISO.jpg");
      c1->Print("Plots/ELECTRONS_PFISO.eps");
      c1->Print("Plots/ELECTRONS_PFISO.C");
    }
    toto.plotstack("ELECTRONS_PT",20,1,"p_{T}(isolated e) (GeV/c)","right");
    toto._hdata->GetXaxis()->SetRangeUser(0,250);
    toto._hdata->GetYaxis()->SetRangeUser(0,55);
    c1->Modified();
    TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.05);
    latex->SetTextFont(62);
    latex->SetTextAlign(12);
    latex->SetTextColor(1);
    latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
    TString textchannel = "e + Jets channel";
    TLatex *latex2 = new TLatex();
    latex2->SetTextSize(0.05);
    latex2->SetTextFont(52);
    latex2->SetTextAlign(12);
    latex2->SetTextColor(1);
    latex2->DrawLatex(10,0.9*toto._hdata->GetMaximum(),textchannel); 
    c1->Modified();
    if (print) {
      c1->Print("Plots/ELECTRONS_PT.pdf");
      c1->Print("Plots/ELECTRONS_PT.jpg");
      c1->Print("Plots/ELECTRONS_PT.eps");
      c1->Print("Plots/ELECTRONS_PT.C");
    }
  }

  toto.plotstack("GOODJET_N",1,1,"Number of jets with p_{T}>20 GeV/c","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,11);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,140.);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.6,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/GOODJET_20_N.pdf");
    c1->Print("Plots/GOODJET_20_N.jpg");
    c1->Print("Plots/GOODJET_20_N.eps");
    c1->Print("Plots/GOODJET_20_N.C");
  }
  toto.plotstack("GOODJET_30_N",1,1,"Number of jets with p_{T}>30 GeV/c","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,11);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,140.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0,130);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.6,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/GOODJET_30_N.pdf");
    c1->Print("Plots/GOODJET_30_N.jpg");
    c1->Print("Plots/GOODJET_30_N.eps");
    c1->Print("Plots/GOODJET_30_N.C");
  }
  toto.plotstack("GOODJET_40_N",1,1,"Number of jets with p_{T}>40 GeV/c","right");
  toto._hdata->GetXaxis()->SetRangeUser(1,9);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,140.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0,135);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(1.,1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(1.4,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/GOODJET_40_N.pdf");
    c1->Print("Plots/GOODJET_40_N.jpg");
    c1->Print("Plots/GOODJET_40_N.eps");
    c1->Print("Plots/GOODJET_40_N.C");
  }
  toto.plotstack("GOODJET_50_N",1,1,"Number of jets with p_{T}>50 GeV/c","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,8);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,140.);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.4,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/GOODJET_50_N.pdf");
    c1->Print("Plots/GOODJET_50_N.jpg");
    c1->Print("Plots/GOODJET_50_N.eps");
    c1->Print("Plots/GOODJET_50_N.C");
  }
  toto.plotstack("GOODJET_PT",20,1,"p_{T} of jets (GeV/c)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,448);
  toto._hdata->GetYaxis()->SetRangeUser(0,260);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(20,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/GOODJET_20_PT.pdf");
    c1->Print("Plots/GOODJET_20_PT.jpg");
    c1->Print("Plots/GOODJET_20_PT.eps");
    c1->Print("Plots/GOODJET_20_PT.C");
  }
  
  toto.plotstack("JPSI_M",5,1,"J/#psi mass (GeV/c^{2})","right");
  toto._hdata->GetXaxis()->SetRangeUser(3,3.195);
  toto._hdata->GetYaxis()->SetRangeUser(0.,55.);
  toto._hdata->GetXaxis()->SetNdivisions(506);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(3.,1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(3.01,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_M.pdf");
    c1->Print("Plots/JPSI_M.jpg");
    c1->Print("Plots/JPSI_M.eps");
    c1->Print("Plots/JPSI_M.C");
  }

  toto.plotstack("JPSI_ETA",2,1,"J/#psi #eta","right");
  toto._hdata->GetXaxis()->SetRangeUser(-2.5,2.5);
  toto._hdata->GetYaxis()->SetRangeUser(0,50);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(-2.55,1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(-2.35,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_ETA.pdf");
    c1->Print("Plots/JPSI_ETA.jpg");
    c1->Print("Plots/JPSI_ETA.eps");
    c1->Print("Plots/JPSI_ETA.C");
  }

  toto.plotstack("JPSI_PT",5,1,"J/#psi p_{T} (GeV/c)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,138);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,50.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0,45);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(6,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_PT.pdf");
    c1->Print("Plots/JPSI_PT.jpg");
    c1->Print("Plots/JPSI_PT.eps");
    c1->Print("Plots/JPSI_PT.C");
  }

  toto.plotstack("JPSI_L",20,1,"c#tau(J/#psi) (cm)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,0.51);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.03,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_L.pdf");
    c1->Print("Plots/JPSI_L.jpg");
    c1->Print("Plots/JPSI_L.eps");
    c1->Print("Plots/JPSI_L.C");
  }
  toto.plotstack("JPSI_L",2,1,"c#tau(J/#psi) (cm)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,0.051);
  toto._hdata->GetYaxis()->SetRangeUser(0,30);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";;
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.003,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_L_ZOOM.pdf");
    c1->Print("Plots/JPSI_L_ZOOM.jpg");
    c1->Print("Plots/JPSI_L_ZOOM.eps");
    c1->Print("Plots/JPSI_L_ZOOM.C");
  }

  toto.plotstack("JPSI_SIGMAL",100,1,"#Delta(c#tau)(J/#psi) (cm)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,0.0051);
  toto._hdata->GetXaxis()->SetNdivisions(506);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.0002,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_SIGMAL.pdf");
    c1->Print("Plots/JPSI_SIGMAL.jpg");
    c1->Print("Plots/JPSI_SIGMAL.eps");
    c1->Print("Plots/JPSI_SIGMAL.C");
  }

  toto.plotstack("JPSI_LOVERSIG",500,1,"(c#tau)/#Delta(c#tau)(J/#psi)","right");
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(300.,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_LOVERSIG.pdf");
    c1->Print("Plots/JPSI_LOVERSIG.jpg");
    c1->Print("Plots/JPSI_LOVERSIG.eps");
    c1->Print("Plots/JPSI_LOVERSIG.C");
  }
  
  toto.plotstack("JPSI_CHI2",5,1,"#chi^{2}(J/#psi vertex)","right");
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(1.,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSI_CHI2.pdf");
    c1->Print("Plots/JPSI_CHI2.jpg");
    c1->Print("Plots/JPSI_CHI2.eps");
    c1->Print("Plots/JPSI_CHI2.C");
  }

  toto.plotstack("DPHIJPSIJETMIN",1,1,"#Delta#phi (J/#psi-jet) min","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,0.58);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.025,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DPHIJPSIJETMIN.pdf");
    c1->Print("Plots/DPHIJPSIJETMIN.jpg");
    c1->Print("Plots/DPHIJPSIJETMIN.eps");
    c1->Print("Plots/DPHIJPSIJETMIN.C");
  }
  
  toto.plotstack("DPHIJPSILEPTON",5,1,"#Delta#phi (J/#psi-isolated lepton)","");
  toto._hdata->GetYaxis()->SetTitle("Events / 0.25");
  toto._hdata->GetXaxis()->SetRangeUser(0,3.4);
  toto._hdata->GetYaxis()->SetRangeUser(0,55);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(2.,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DPHIJPSILEPTON.pdf");
    c1->Print("Plots/DPHIJPSILEPTON.jpg");
    c1->Print("Plots/DPHIJPSILEPTON.eps");
    c1->Print("Plots/DPHIJPSILEPTON.C");
  }
  
  toto.plotstack("DRJPSIJETMIN",1,1,"#DeltaR (J/#psi - jet) min","right");
  toto._hdata->GetYaxis()->SetTitle("Events / 0.25");
  toto._hdata->GetXaxis()->SetRangeUser(0,0.98);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.04,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DRJPSIJETMIN.pdf");
    c1->Print("Plots/DRJPSIJETMIN.jpg");
    c1->Print("Plots/DRJPSIJETMIN.eps");
    c1->Print("Plots/DRJPSIJETMIN.C");
  }
  
  if ( channel.Contains("mu") || channel.Contains("Mu") ) 
    toto.plotstack("DRJPSILEPTON",5,1,"#DeltaR (J/#psi - isolated lepton)","right");
  if ( channel.Contains("el") || channel.Contains("El") )  
    toto.plotstack("DRJPSILEPTON",5,1,"#DeltaR (J/#psi - isolated lepton)","");
  toto._hdata->GetXaxis()->SetRangeUser(0,4.5);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,70.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0.,60.);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  if (channel.Contains("mu") || channel.Contains("Mu")) latex2->DrawLatex(0.2,0.9*toto._hdata->GetMaximum(),textchannel); 
  if (channel.Contains("el") || channel.Contains("El")) latex2->DrawLatex(3.,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/DRJPSILEPTON.pdf");
    c1->Print("Plots/DRJPSILEPTON.jpg");
    c1->Print("Plots/DRJPSILEPTON.eps");
    c1->Print("Plots/DRJPSILEPTON.C");
  }

  toto.plotstack("TOP_M_RECO_ALL",10,1,"M_{J/#psi+l} (GeV/c^{2})","right");
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,50.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0,40);
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(10,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/TOP_M.pdf");
    c1->Print("Plots/TOP_M.jpg");
    c1->Print("Plots/TOP_M.eps");
    c1->Print("Plots/TOP_M.C");
  }
  toto.plotstackratio("TOP_M_RECO_ALL",10,1,"M_{J/#psi+l} (GeV/c^{2})","right");
  if (print) {
    c1->Print("Plots/TOP_M_ratio.pdf");
    c1->Print("Plots/TOP_M_ratio.jpg");
    c1->Print("Plots/TOP_M_ratio.eps");
    c1->Print("Plots/TOP_M_ratio.C");
  }
  
  toto.plotstack("MET_MET",10,1,"MET (GeV)","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,345);
  toto._hdata->GetYaxis()->SetRangeUser(0,50);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(15,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/MET_MET.pdf");
    c1->Print("Plots/MET_MET.jpg");
    c1->Print("Plots/MET_MET.eps");
    c1->Print("Plots/MET_MET.C");
  } 

  toto.plotstack("JPSIJET_FRAC",10,1,"p_{T}(J/#psi)/p_{T}(nearest jet)","right");
  toto._hdata->GetYaxis()->SetRangeUser(0,35);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,45.);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(0.04,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/JPSIJET_FRAC.pdf");
    c1->Print("Plots/JPSIJET_FRAC.jpg");
    c1->Print("Plots/JPSIJET_FRAC.eps");
    c1->Print("Plots/JPSIJET_FRAC.C");
  }

  toto.plotstack("VERTEX_N",2,1,"Number of vertices","right");
  toto._hdata->GetXaxis()->SetRangeUser(0,39);
  if (channel.Contains("mu") || channel.Contains("Mu")) toto._hdata->GetYaxis()->SetRangeUser(0.,50.);
  if (channel.Contains("el") || channel.Contains("El")) toto._hdata->GetYaxis()->SetRangeUser(0,45);
  c1->Modified();
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(2,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/VERTEX_N.pdf");
    c1->Print("Plots/VERTEX_N.jpg");
    c1->Print("Plots/VERTEX_N.eps");
    c1->Print("Plots/VERTEX_N.C");
  }

  toto.plotstack("TOPHAD_MASS",20,1,"M_{bjj} (GeV/c^{2})","right");
  TString header = "CMS preliminary, 19.8 fb^{-1}, #sqrt{s} = 8 TeV";
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(62);
  latex->SetTextAlign(12);
  latex->SetTextColor(1);
  latex->DrawLatex(toto._hdata->GetXaxis()->GetXmin(),1.04*toto._hdata->GetMaximum(),header); 
  TString textchannel;
  if (channel.Contains("mu") || channel.Contains("Mu")) textchannel = "#mu + Jets channel";
  if (channel.Contains("el") || channel.Contains("El")) textchannel = "e + Jets channel";
  TLatex *latex2 = new TLatex();
  latex2->SetTextSize(0.05);
  latex2->SetTextFont(52);
  latex2->SetTextAlign(12);
  latex2->SetTextColor(1);
  latex2->DrawLatex(20.,0.9*toto._hdata->GetMaximum(),textchannel); 
  c1->Modified();
  if (print) {
    c1->Print("Plots/TOPHAD_MASS.pdf");
    c1->Print("Plots/TOPHAD_MASS.jpg");
    c1->Print("Plots/TOPHAD_MASS.eps");
    c1->Print("Plots/TOPHAD_MASS.C");
  }
}

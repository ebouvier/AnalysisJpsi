#define MyAna_cxx

#include <memory>
#include "MyAna.h"
#include "MetRes.h"
#include "TopTriggerEfficiencyProvider.h"
#include "rochcor2012v2/rochcor2012v2.h"


#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include "TRandom3.h"

using namespace std;

MyAna::MyAna(TTree *_muonstree, TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree)
  :RootTupleDefs(_muonstree, _electronstree, _jetstree, _METtree, _verticestree, _eventstree, _HLTtree)
{
   _isMC     = false;
   _isSIG    = false;
   _debug    = false;
   _rootName = "output.root";
   _doSkim   = false;
   _nevt     = -1; 
}

MyAna::~MyAna()
{
}




void MyAna::Loop()
{

  

  cout << " => Running on MC     ? " << boolalpha << _isMC  << endl;
  cout << " => Running on Signal ? " << boolalpha << _isSIG << endl;

  //  const double Pi=3.14159265358979323846 ;
  _newfile = new TFile(_rootName.c_str(),"RECREATE");

  //================================================================================================
  // HISTOGRAMS
  //================================================================================================

  TH1::SetDefaultSumw2(true);
  TH1D* ICUT 		= new TH1D("ICUT","ICUT",100,0.,100.);


  TH1D* TRIGGER_WEIGHT        = new TH1D("TRIGGER_WEIGHT","TRIGGER_WEIGHT",100,0,1); 
  TH1D* PU_WEIGHT        = new TH1D("PU_WEIGHT","PU_WEIGHT",200,0,2); 
  TH1D* TOTAL_WEIGHT        = new TH1D("TOTAL_WEIGHT","TOTAL_WEIGHT",100,0,1); 
    

  TH1D* N_MC_TRUE_INTERACTIONS       = new TH1D("N_MC_TRUE_INTERACTIONS","N_MC_TRUE_INTERACTIONS",120,0.,60);
  TH1D* N_MC_TRUE_INTERACTIONS_REWEIGHTED       = new TH1D("N_MC_TRUE_INTERACTIONS_REWEIGHTED","N_MC_TRUE_INTERACTIONS_REWEIGHTED",120,0.,60);

  TH1D* PASS_TRIGGER                 = new TH1D("PASS_TRIGGER","PASS_TRIGGER",4,-1,3);

  //before cut histos
  TH1D* MUONS_ETA_BEFORECUT             = new TH1D("MUONS_ETA_BEFORECUT","MUONS_ETA_BEFORECUT",60,-3.,3.);
  TH1D* MUONS_PT_BEFORECUT              = new TH1D("MUONS_PT_BEFORECUT","MUONS_PT_BEFORECUT",500,0.,500.);
  TH1D* MUONS_NEW_RELISO_BCORR_BEFORECUT          = new TH1D("MUONS_NEW_RELISO_BCORR_BEFORECUT","MUONS_NEW_RELISO_BCORR_BEFORECUT",200,0.,0.2);
  TH1D* MUONS_NEW_RELISO_BEFORECUT          = new TH1D("MUONS_NEW_RELISO_BEFORECUT","MUONS_NEW_RELISO_BEFORECUT",200,0.,0.2);
  TH1D* MUONS_OLD_RELISO_BEFORECUT          = new TH1D("MUONS_OLD_RELISO_BEFORECUT","MUONS_OLD_RELISO_BEFORECUT",200,0.,0.2);
  TH1D* N_MC_TRUE_INTERACTIONS_REWEIGHTED_BEFORECUTS       = new TH1D("N_MC_TRUE_INTERACTIONS_REWEIGHTED_BEFORECUTS","N_MC_TRUE_INTERACTIONS_REWEIGHTED_BEFORECUTS",120,0.,60);
  TH1D* MUONS_N_BEFORECUT               = new TH1D("MUONS_N_BEFORECUT","MUONS_N_BEFORECUT",10,0,10.);
  TH1D* MUONS_NORMCHI2_BEFORECUT        = new TH1D("MUONS_NORMCHI2_BEFORECUT","MUONS_NORMCHI2_BEFORECUT",1000,0,1000);
  TH1D* MUONS_TRACK_LAYERS_BEFORECUT    = new TH1D("MUONS_TRACK_LAYERS_BEFORECUT","MUONS_TRACK_LAYERS_BEFORECUT",20,0,20);
  TH1D* MUONS_TRACK_VAL_HITS_BEFORECUT  = new TH1D("MUONS_TRACK_VAL_HITS_BEFORECUT","MUONS_TRACK_VAL_HITS_BEFORECUT",60,0,60);
  TH1D* MUONS_MATCHED_STATIONS_BEFORECUT= new TH1D("MUONS_MATCHED_STATIONS_BEFORECUT","MUONS_MATCHED_STATIONS_BEFORECUT",10,0,10);
  TH1D* MUONS_DB_BEFORECUT              = new TH1D("MUONS_DB_BEFORECUT","MUONS_DB_BEFORECUT",60,-0.3,0.3);
  TH1D* MUONS_DZ_BEFORECUT              = new TH1D("MUONS_DZ_BEFORECUT","MUONS_DZ_BEFORECUT",100,0,1);
  TH1D* MUONS_PIXEL_VAL_HITS_BEFORECUT  = new TH1D("MUONS_PIXEL_VAL_HITS_BEFORECUT","MUONS_PIXEL_VAL_HITS_BEFORECUT",10,0,10);
  TH1D* GOODMUONS_N_BEFORECUT           = new TH1D("GOODMUONS_N_BEFORECUT","GOODMUONS_N_BEFORECUT",10,0,10.);
  //TH1D* MET_PFMET_BEFORECUTS         = new TH1D("MET_PFMET_BEFORECUTS","MET_PFMET_BEFORECUTS",500,0.,500.);
  TH1D* WSEL_MT_GROSS_BEFORECUT         = new TH1D("WSEL_MT_GROSS_BEFORECUT","WSEL_MT_GROSS_BEFORECUT",1000,0.,1000.);
  TH1D* GOODPFJET_N_BEFORECUT           = new TH1D("GOODPFJET_N_BEFORECUT","GOODPFJET_N_BEFORECUT",40,0.,40.);
  TH1D* ALLPFJET_N_BEFORECUT            = new TH1D("ALLPFJET_N_BEFORECUT","ALLPFJET_N_BEFORECUT",30,0.,30.);
  TH1D* ALLPFJET_ETA_BEFORECUT          = new TH1D("ALLPFJET_ETA_BEFORECUT","ALLPFJET_ETA_BEFORECUT",60,-3.,3.);
  TH1D* ALLPFJET_PT_BEFORECUT           = new TH1D("ALLPFJET_PT_BEFORECUT","ALLPFJET_PT_BEFORECUT",1000,0.,1000.);
  TH1D* GOODPFJET1_PT_BEFORECUT         = new TH1D("GOODPFJET1_PT_BEFORECUT","GOODPFJET1_PT_BEFORECUT",1000,0.,1000.);
  TH1D* GOODPFJET2_PT_BEFORECUT         = new TH1D("GOODPFJET2_PT_BEFORECUT","GOODPFJET2_PT_BEFORECUT",1000,0.,1000.);
  TH1D* GOODPFJET3_PT_BEFORECUT         = new TH1D("GOODPFJET3_PT_BEFORECUT","GOODPFJET3_PT_BEFORECUT",1000,0.,1000.);
  TH1D* GOODPFJET4_PT_BEFORECUT         = new TH1D("GOODPFJET4_PT_BEFORECUT","GOODPFJET4_PT_BEFORECUT",1000,0.,1000.);


  TH1D* WSEL_MT_SHARP           = new TH1D("WSEL_MT_SHARP","WSEL_MT_SHARP",320,0.,160.);
  TH1D* WSEL_MT_GROSS           = new TH1D("WSEL_MT_GROSS","WSEL_MT_GROSS",1000,0.,1000.);
  TH1D* WSEL_PFMET              = new TH1D("WSEL_PFMET","WSEL_PFMET",500,0.,500.);
  TH1D* ZSEL_M_SUP50            = new TH1D("ZSEL_M_SUP50","ZSEL_M_SUP50",360,0.,180);
  TH1D* ZSEL_M_SHARP            = new TH1D("ZSEL_M_SHARP","ZSEL_M_SHARP",360,0.,180);
  TH1D* ZSEL_M_GROSS            = new TH1D("ZSEL_M_GROSS","ZSEL_M_GROSS",1000,0.,1000);
  TH1D* ZSEL_M_GROSS_BEFORECUT            = new TH1D("ZSEL_M_GROSS_BEFORECUT","ZSEL_M_GROSS_BEFORECUT",1000,0.,1000);
  TH1D* ZSEL_PT_SHARP           = new TH1D("ZSEL_PT_SHARP","ZSEL_PT_SHARP",1000,0.,500);
  TH1D* ZSEL_PT_GROSS           = new TH1D("ZSEL_PT_GROSS","ZSEL_PT_GROSS",2000,0.,2000); 
  TH1D* ZSEL_PFMET              = new TH1D("ZSEL_PFMET","ZSEL_PFMET",500,0.,500.);
  TH1D* ZSEL_PT_RECOIL          = new TH1D("ZSEL_PT_RECOIL","ZSEL_PT_RECOIL",1000,0.,500);
  TH1D* ZSEL_RECOIL_ON_PT       = new TH1D("ZSEL_RECOIL_ON_PT","ZSEL_RECOIL_ON_PT",2000,-500.,500.);
  TH1D* ZSEL_RECOIL_ORTHO_PT    = new TH1D("ZSEL_RECOIL_ORTHO_PT","ZSEL_RECOIL_ORTHO_PT",2000,-500.,500.);
  TH1D* ZSEL_DELTA_PHI_MUS      = new TH1D("ZSEL_DELTA_PHI_MUS","ZSEL_DELTA_PHI_MUS",64,0,3.2);
  TH1D* ZSEL_DELTA_PHI_PTZ_PTRECOIL =new TH1D("ZSEL_DELTA_PHI_PTZ_PTRECOIL","ZSEL_DELTA_PHI_PTZ_PTRECOIL",64,0,3.2);   
  TH1D* ZSEL_PHI                = new TH1D("ZSEL_PHI","ZSEL_PHI",64,-3.2,3.2);



  TH1D* WSEL_MT_SHARP_NOJET  = new TH1D("WSEL_MT_SHARP_NOJET","WSEL_MT_SHARP_NOJET",320,0.,160.);
  TH1D* WSEL_PFMET_NOJET     = new TH1D("WSEL_PFMET_NOJET","WSEL_PFMET_NOJET",500,0.,500.);
  TH1D* ZSEL_M_SHARP_NOJET   = new TH1D("ZSEL_M_SHARP_NOJET","ZSEL_M_SHARP_NOJET",360,0.,180);
  TH1D* ZSEL_PT_SHARP_NOJET  = new TH1D("ZSEL_PT_SHARP_NOJET","ZSEL_PT_SHARP_NOJET",2000,0.,2000);
  TH1D* ZSEL_PFMET_NOJET     = new TH1D("ZSEL_PFMET_NOJET","ZSEL_PFMET_NOJET",500,0.,500.);
  



  TH1D* WSEL_MT_SHARP_1JET  = new TH1D("WSEL_MT_SHARP_1JET","WSEL_MT_SHARP_1JET",1000,0.,1000.);
  TH1D* WSEL_PFMET_1JET = new TH1D("WSEL_PFMET_1JET","WSEL_PFMET_1JET",500,0.,500.);
  TH1D* ZSEL_M_SHARP_1JET            = new TH1D("ZSEL_M_SHARP_1JET","ZSEL_M_SHARP_1JET",1000,0.,1000);
  TH1D* ZSEL_PT_SHARP_1JET            = new TH1D("ZSEL_PT_SHARP_1JET","ZSEL_PT_SHARP_1JET",2000,0.,2000);
  TH1D* ZSEL_PFMET_1JET = new TH1D("ZSEL_PFMET_1JET","ZSEL_PFMET_1JET",500,0.,500.);


  TH1D* WSEL_MT_SHARP_2JETS  = new TH1D("WSEL_MT_SHARP_2JETS","WSEL_MT_SHARP_2JETS",1000,0.,1000.);
  TH1D* WSEL_PFMET_2JETS = new TH1D("WSEL_PFMET_2JETS","WSEL_PFMET_2JETS",500,0.,500.);
  TH1D* ZSEL_M_SHARP_2JETS            = new TH1D("ZSEL_M_SHARP_2JETS","ZSEL_M_SHARP_2JETS",1000,0.,1000);
  TH1D* ZSEL_PT_SHARP_2JETS            = new TH1D("ZSEL_PT_SHARP_2JETS","ZSEL_PT_SHARP_2JETS",2000,0.,2000);
  TH1D* ZSEL_PFMET_2JETS = new TH1D("ZSEL_PFMET_2JETS","ZSEL_PFMET_2JETS",500,0.,500.);
  TH1D* ZSEL_GOODPFJET_DELTAPHI_2JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPHI_2JETS","ZSEL_GOODPFJET_DELTAPHI_2JETS",64,0,3.2);
  TH1D* ZSEL_GOODPFJET_DELTAPT_2JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPT_2JETS","ZSEL_GOODPFJET_DELTAPT_2JETS",1000,0,1000);
  TH1D* WSEL_GOODPFJET_DELTAPHI_2JETS     = new TH1D("WSEL_GOODPFJET_DELTAPHI_2JETS","WSEL_GOODPFJET_DELTAPHI_2JETS",64,0,3.2);
  TH1D* WSEL_GOODPFJET_DELTAPT_2JETS     = new TH1D("WSEL_GOODPFJET_DELTAPT_2JETS","WSEL_GOODPFJET_DELTAPT_2JETS",1000,0,1000);


  TH1D* WSEL_MT_SHARP_3JETS  = new TH1D("WSEL_MT_SHARP_3JETS","WSEL_MT_SHARP_3JETS",1000,0.,1000);
  TH1D* WSEL_PFMET_3JETS = new TH1D("WSEL_PFMET_3JETS","WSEL_PFMET_3JETS",500,0.,500.);
  TH1D* ZSEL_M_SHARP_3JETS            = new TH1D("ZSEL_M_SHARP_3JETS","ZSEL_M_SHARP_3JETS",1000,0.,1000);
  TH1D* ZSEL_PT_SHARP_3JETS            = new TH1D("ZSEL_PT_SHARP_3JETS","ZSEL_PT_SHARP_3JETS",2000,0.,2000);
  TH1D* ZSEL_PFMET_3JETS = new TH1D("ZSEL_PFMET_3JETS","ZSEL_PFMET_3JETS",500,0.,500.);
  TH1D* ZSEL_GOODPFJET_DELTAPHI_3JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPHI_3JETS","ZSEL_GOODPFJET_DELTAPHI_3JETS",64,0,3.2);
  TH1D* ZSEL_GOODPFJET_DELTAPT_3JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPT_3JETS","ZSEL_GOODPFJET_DELTAPT_3JETS",1000,0,1000);
  TH1D* WSEL_GOODPFJET_DELTAPHI_3JETS     = new TH1D("WSEL_GOODPFJET_DELTAPHI_3JETS","WSEL_GOODPFJET_DELTAPHI_3JETS",64,0,3.2);
  TH1D* WSEL_GOODPFJET_DELTAPT_3JETS     = new TH1D("WSEL_GOODPFJET_DELTAPT_3JETS","WSEL_GOODPFJET_DELTAPT_3JETS",1000,0,1000);

  TH1D* WSEL_MT_SHARP_4JETS  = new TH1D("WSEL_MT_SHARP_4JETS","WSEL_MT_SHARP_4JETS",1000,0.,1000);
  TH1D* WSEL_PFMET_4JETS = new TH1D("WSEL_PFMET_4JETS","WSEL_PFMET_4JETS",500,0.,500.);
  TH1D* ZSEL_M_SHARP_4JETS            = new TH1D("ZSEL_M_SHARP_4JETS","ZSEL_M_SHARP_4JETS",1000,0.,1000);
  TH1D* ZSEL_PT_SHARP_4JETS            = new TH1D("ZSEL_PT_SHARP_4JETS","ZSEL_PT_SHARP_4JETS",2000,0.,2000);
  TH1D* ZSEL_PFMET_4JETS = new TH1D("ZSEL_PFMET_4JETS","ZSEL_PFMET_4JETS",500,0.,500.);
  TH1D* ZSEL_GOODPFJET_DELTAPHI_4JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPHI_4JETS","ZSEL_GOODPFJET_DELTAPHI_4JETS",64,0,3.2);
  TH1D* ZSEL_GOODPFJET_DELTAPT_4JETS     = new TH1D("ZSEL_GOODPFJET_DELTAPT_4JETS","ZSEL_GOODPFJET_DELTAPT_4JETS",1000,0,1000);
  TH1D* WSEL_GOODPFJET_DELTAPHI_4JETS     = new TH1D("WSEL_GOODPFJET_DELTAPHI_4JETS","WSEL_GOODPFJET_DELTAPHI_4JETS",64,0,3.2);
  TH1D* WSEL_GOODPFJET_DELTAPT_4JETS     = new TH1D("WSEL_GOODPFJET_DELTAPT_4JETS","WSEL_GOODPFJET_DELTAPT_4JETS",1000,0,1000);



  TH1D* VERTEX_N           = new TH1D("VERTEX_N","VERTEX_N",50,0.,50.);
  TH1D* VERTEX_N_BEFORECUTS           = new TH1D("VERTEX_N_BEFORECUTS","VERTEX_N_BEFORECUTS",50,0.,50.);
  TH1D* VERTEX_NGOOD      = new TH1D("VERTEX_NGOOD","VERTEX_NGOOD",50,0.,50.);
  TH1D* VERTEX_NGOOD_BEFORECUTS      = new TH1D("VERTEX_NGOOD_BEFORECUTS","VERTEX_NGOOD_BEFORECUTS",50,0.,50.);


  TH1D* VERTEX_X           = new TH1D("VERTEX_X","VERTEX_X",1000,-0.5,0.5);
  TH1D* VERTEX_Y           = new TH1D("VERTEX_Y","VERTEX_Y",1000,-0.5,0.5);
  TH1D* VERTEX_Z           = new TH1D("VERTEX_Z","VERTEX_Z",1000,-50.,50.);
  TH1D* VERTEX_NDOF        = new TH1D("VERTEX_NDOF","VERTEX_NDOF",500,0.,250.);
  TH1D* VERTEX_CHI2NORM    = new TH1D("VERTEX_CHI2NORM","VERTEX_CHI2NORM",100,0.,20.);
  TH1D* VERTEX_ISFAKE      = new TH1D("VERTEX_ISFAKE","VERTEX_ISFAKE",3,0.,3.);
  TH1D* VERTEX_NTRACKS     = new TH1D("VERTEX_NTRACKS","VERTEX_NTRACKS",250,0.,250.);  
  
  TH1D* VERTEX0_X           = new TH1D("VERTEX0_X","VERTEX0_X",1000,-0.5,0.5);
  TH1D* VERTEX0_Y           = new TH1D("VERTEX0_Y","VERTEX0_Y",1000,-0.5,0.5);
  TH1D* VERTEX0_Z           = new TH1D("VERTEX0_Z","VERTEX0_Z",500,-50.,50.);
  TH1D* VERTEX0_NDOF        = new TH1D("VERTEX0_NDOF","VERTEX0_NDOF",500,0.,250.);
  TH1D* VERTEX0_CHI2NORM    = new TH1D("VERTEX0_CHI2NORM","VERTEX0_CHI2NORM",100,0.,10.);
  TH1D* VERTEX0_ISFAKE      = new TH1D("VERTEX0_ISFAKE","VERTEX0_ISFAKE",3,0.,3.);
  TH1D* VERTEX0_NTRACKS     = new TH1D("VERTEX0_NTRACKS","VERTEX0_NTRACKS",250,0.,250.);
  




  TH1D* ELECTRONS_N               = new TH1D("ELECTRONS_N","ELECTRONS_N",10,0,10.);
  TH1D* ELECTRONS_PT              = new TH1D("ELECTRONS_PT","ELECTRONS_PT",500,0.,500.);  
  TH1D* ELECTRONS_PZ              = new TH1D("ELECTRONS_PZ","ELECTRONS_PZ",200,0.,200.);
  TH1D* ELECTRONS_ETA             = new TH1D("ELECTRONS_ETA","ELECTRONS_ETA",60,-3.,3.); 
  TH1D* ELECTRONS_PHI             = new TH1D("ELECTRONS_PHI","ELECTRONS_PHI",64,-3.2,3.2); 
  TH1D* ELECTRONS_RELISO        = new TH1D("ELECTRONS_RELISO","ELECTRONS_RELISO",200,0.,0.2);  
  
  TH1D* MUONS_N               = new TH1D("MUONS_N","MUONS_N",10,0,10.);
  TH1D* MUONS_CHG             = new TH1D("MUONS_CHG","MUONS_CHG",3,-1,2.);
  TH1D* MUONS_PT              = new TH1D("MUONS_PT","MUONS_PT",500,0.,500.);
  TH1D* MUONS_PZ              = new TH1D("MUONS_PZ","MUONS_PZ",400,0.,400.);
  TH1D* MUONS_ETA             = new TH1D("MUONS_ETA","MUONS_ETA",60,-3.,3.); 
  TH1D* MUONS_PHI             = new TH1D("MUONS_PHI","MUONS_PHI",64,-3.2,3.2); 
  TH1D* MUONS_CHARGE_PRODUCT  = new TH1D("MUONS_CHARGE_PRODUCT","MUONS_CHARGE_PRODUCT",3,-1,2);
  TH1D* MUONS_NEW_RELISO_BCORR          = new TH1D("MUONS_NEW_RELISO_BCORR","MUONS_NEW_RELISO_BCORR",200,0.,0.2);
  TH1D* MUONS_NEW_RELISO          = new TH1D("MUONS_NEW_RELISO","MUONS_NEW_RELISO",200,0.,0.2);
  TH1D* MUONS_OLD_RELISO          = new TH1D("MUONS_OLD_RELISO","MUONS_OLD_RELISO",200,0.,0.2);
  TH1D* MUONS_NORMCHI2= new TH1D("MUONS_NORMCHI2","MUONS_NORMCHI2",120,0,12);
  TH1D* MUONS_TRACK_LAYERS= new TH1D("MUONS_TRACK_LAYERS","MUONS_TRACK_LAYERS",20,0,20);
  TH1D* MUONS_TRACK_VAL_HITS= new TH1D("MUONS_TRACK_VAL_HITS","MUONS_TRACK_VAL_HITS",60,0,60);
  TH1D* MUONS_MATCHED_STATIONS= new TH1D("MUONS_MATCHED_STATIONS","MUONS_MATCHED_STATIONS",10,0,10);
  TH1D* MUONS_DB= new TH1D("MUONS_DB","MUONS_DB",600,-0.3,0.3);
  TH1D* MUONS_DZ= new TH1D("MUONS_DZ","MUONS_DZ",100,0,1);
  TH1D* MUONS_VZ= new TH1D("MUONS_VZ","MUONS_VZ",500,-25,25);
  TH1D* MUONS_D0= new TH1D("MUONS_D0","MUONS_D0",60,-0.3,0.3);
  TH1D* MUONS_PIXEL_VAL_HITS = new TH1D("MUONS_PIXEL_VAL_HITS","MUONS_PIXEL_VAL_HITS",10,0,10);
  
 
  
  TH1D* MUON1_PT              = new TH1D("MUON1_PT","MUON1_PT",500,0.,500.);
  TH1D* MUON1_PZ              = new TH1D("MUON1_PZ","MUON1_PZ",400,0.,400.);
  TH1D* MUON1_ETA             = new TH1D("MUON1_ETA","MUON1_ETA",60,-3.,3.); 
  TH1D* MUON1_PHI             = new TH1D("MUON1_PHI","MUON1_PHI",64,-3.2,3.2); 
  TH1D* MUON1_NEW_RELISO_BCORR        = new TH1D("MUON1_NEW_RELISO_BCORR","MUON1_NEW_RELISO_BCORR",200,0.,0.2);  
  TH1D* MUON1_OLD_RELISO        = new TH1D("MUON1_OLD_RELISO","MUON1_OLD_RELISO",200,0.,0.2);  
  TH1D* MUON1_NEW_RELISO        = new TH1D("MUON1_NEW_RELISO","MUON1_NEW_RELISO",200,0.,0.2); 

  
  TH1D* MUON2_PT              = new TH1D("MUON2_PT","MUON2_PT",500,0.,500.);
  TH1D* MUON2_PZ              = new TH1D("MUON2_PZ","MUON2_PZ",400,0.,400.);
  TH1D* MUON2_ETA             = new TH1D("MUON2_ETA","MUON2_ETA",60,-3.,3.); 
  TH1D* MUON2_PHI             = new TH1D("MUON2_PHI","MUON2_PHI",64,-3.2,3.2); 
  TH1D* MUON2_NEW_RELISO_BCORR        = new TH1D("MUON2_NEW_RELISO_BCORR","MUON2_NEW_RELISO_BCORR",200,0.,0.2);  
  TH1D* MUON2_OLD_RELISO        = new TH1D("MUON2_OLD_RELISO","MUON2_OLD_RELISO",200,0.,0.2);
  TH1D* MUON2_NEW_RELISO        = new TH1D("MUON2_NEW_RELISO","MUON2_NEW_RELISO",200,0.,0.2);

  //TH1D* MET_SUMET          = new TH1D("MET_SUMET","MET_SUMET",1000,0.,2000.);
  TH1D* MET_PT         = new TH1D("MET_PT","MET_PT",500,0.,500.);    
  TH1D* MET_PHI         = new TH1D("MET_PHI","MET_PHI",64,-3.2,3.2);

  

  TH1D* MHT_PFJET         = new TH1D("MHT_PFJET","MHT_PFJET",500,0.,500.);
  TH1D* HT_PFJET          = new TH1D("HT_PFJET","HT_PFJET",1000,0.,2000.);
  
  

  
  TH1D* ALLPFJET_N30   = new TH1D("ALLPFJET_N30","ALLPFJET_N30",25,0.,25.);
  TH1D* ALLPFJET_N35   = new TH1D("ALLPFJET_N35","ALLPFJET_N35",25,0.,25.);
  TH1D* ALLPFJET_N40   = new TH1D("ALLPFJET_N40","ALLPFJET_N40",25,0.,25.);
  TH1D* ALLPFJET_N45   = new TH1D("ALLPFJET_N45","ALLPFJET_N45",25,0.,25.);
  TH1D* ALLPFJET_N50   = new TH1D("ALLPFJET_N50","ALLPFJET_N50",25,0.,25.);
  TH1D* ALLPFJET_N55   = new TH1D("ALLPFJET_N55","ALLPFJET_N55",25,0.,25.);

  TH1D* ALLPFJET_PT       = new TH1D("ALLPFJET_PT","ALLPFJET_PT",1000,0.,1000.);
  TH1D* ALLPFJET_PZ       = new TH1D("ALLPFJET_PZ","ALLPFJET_PZ",1000,0.,1000.); 
  TH1D* ALLPFJET_ETA      = new TH1D("ALLPFJET_ETA","ALLPFJET_ETA",100,-5.,5);
  TH1D* ALLPFJET_PHI      = new TH1D("ALLPFJET_PHI","ALLPFJET_PHI",64,-3.2,3.2);  
  TH1D* ALLPFJET_BTAG   = new TH1D("ALLPFJET_BTAG","ALLPFJET_BTAG",40,0,4); 
  TH1D* ALLPFJET_BTAG_CSV   = new TH1D("ALLPFJET_BTAG_CSV","ALLPFJET_BTAG_CSV",120,-10,2); 
  
  
  TH1D* GOODPFJET_N20   = new TH1D("GOODPFJET_N20","GOODPFJET_N20",25,0.,25.);
  TH1D* GOODPFJET_N25   = new TH1D("GOODPFJET_N25","GOODPFJET_N25",25,0.,25.);
  TH1D* GOODPFJET_N30   = new TH1D("GOODPFJET_N30","GOODPFJET_N30",25,0.,25.);
  TH1D* GOODPFJET_N35   = new TH1D("GOODPFJET_N35","GOODPFJET_N35",25,0.,25.);
  TH1D* GOODPFJET_N40   = new TH1D("GOODPFJET_N40","GOODPFJET_N40",25,0.,25.);
  TH1D* GOODPFJET_N45   = new TH1D("GOODPFJET_N45","GOODPFJET_N45",25,0.,25.);
  TH1D* GOODPFJET_N50   = new TH1D("GOODPFJET_N50","GOODPFJET_N50",25,0.,25.);
  TH1D* GOODPFJET_N55   = new TH1D("GOODPFJET_N55","GOODPFJET_N55",25,0.,25.);

  
  TH1D* GOODPFJET_PT       = new TH1D("GOODPFJET_PT","GOODPFJET_PT",1000,0.,1000.);
  TH1D* GOODPFJET_PZ       = new TH1D("GOODPFJET_PZ","GOODPFJET_PZ",1000,0.,1000.); 
  TH1D* GOODPFJET_ETA      = new TH1D("GOODPFJET_ETA","GOODPFJET_ETA",100,-5.,5);
  TH1D* GOODPFJET_PHI      = new TH1D("GOODPFJET_PHI","GOODPFJET_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJET_BTAG   = new TH1D("GOODPFJET_BTAG","GOODPFJET_BTAG",40,0,4); 
  TH1D* GOODPFJET_BTAG_CSV   = new TH1D("GOODPFJET_BTAG_CSV","GOODPFJET_BTAG_CSV",120,-10,2);
  
  TH1D* GOODPFJET_DELTAPHI     = new TH1D("GOODPFJET_DELTAPHI","GOODPFJET_DELTAPHI",64,0,3.2);
  TH1D* GOODPFJET_DELTAPT     = new TH1D("GOODPFJET_DELTAPT","GOODPFJET_DELTAPT",1000,0,1000);
  
  TH1D* GOODPFJET1_PT       = new TH1D("GOODPFJET1_PT","GOODPFJET1_PT",1000,0.,1000.);
  TH1D* GOODPFJET1_PZ       = new TH1D("GOODPFJET1_PZ","GOODPFJET1_PZ",1000,0.,1000.); 
  TH1D* GOODPFJET1_ETA      = new TH1D("GOODPFJET1_ETA","GOODPFJET1_ETA",100,-5.,5);
  TH1D* GOODPFJET1_PHI      = new TH1D("GOODPFJET1_PHI","GOODPFJET1_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJET1_BTAG   = new TH1D("GOODPFJET1_BTAG","GOODPFJET1_BTAG",40,0,4); 
  TH1D* GOODPFJET1_BTAG_CSV   = new TH1D("GOODPFJET1_BTAG_CSV","GOODPFJET1_BTAG_CSV",120,-10,2);

  TH1D* GOODPFJET2_PT       = new TH1D("GOODPFJET2_PT","GOODPFJET2_PT",1000,0.,1000.);
  TH1D* GOODPFJET2_PZ       = new TH1D("GOODPFJET2_PZ","GOODPFJET2_PZ",1000,0.,1000.); 
  TH1D* GOODPFJET2_ETA      = new TH1D("GOODPFJET2_ETA","GOODPFJET2_ETA",100,-5.,5);
  TH1D* GOODPFJET2_PHI      = new TH1D("GOODPFJET2_PHI","GOODPFJET2_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJET2_BTAG   = new TH1D("GOODPFJET2_BTAG","GOODPFJET2_BTAG",40,0,4); 
  TH1D* GOODPFJET2_BTAG_CSV   = new TH1D("GOODPFJET2_BTAG_CSV","GOODPFJET2_BTAG_CSV",120,-10,2);
  
  TH1D* GOODPFJET3_PT       = new TH1D("GOODPFJET3_PT","GOODPFJET3_PT",1000,0.,1000.);
  TH1D* GOODPFJET3_PZ       = new TH1D("GOODPFJET3_PZ","GOODPFJET3_PZ",1000,0.,1000.); 
  TH1D* GOODPFJET3_ETA      = new TH1D("GOODPFJET3_ETA","GOODPFJET3_ETA",100,-5.,5);
  TH1D* GOODPFJET3_PHI      = new TH1D("GOODPFJET3_PHI","GOODPFJET3_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJET3_BTAG   = new TH1D("GOODPFJET3_BTAG","GOODPFJET3_BTAG",40,0,4); 
  TH1D* GOODPFJET3_BTAG_CSV   = new TH1D("GOODPFJET3_BTAG_CSV","GOODPFJET3_BTAG_CSV",120,-10,2);
  
  TH1D* GOODPFJET4_PT       = new TH1D("GOODPFJET4_PT","GOODPFJET4_PT",1000,0.,1000.);
  TH1D* GOODPFJET4_PZ       = new TH1D("GOODPFJET4_PZ","GOODPFJET4_PZ",1000,0.,1000.); 
  TH1D* GOODPFJET4_ETA      = new TH1D("GOODPFJET4_ETA","GOODPFJET4_ETA",100,-5.,5);
  TH1D* GOODPFJET4_PHI      = new TH1D("GOODPFJET4_PHI","GOODPFJET4_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJET4_BTAG   = new TH1D("GOODPFJET4_BTAG","GOODPFJET4_BTAG",40,0,4); 
  TH1D* GOODPFJET4_BTAG_CSV   = new TH1D("GOODPFJET4_BTAG_CSV","GOODPFJET4_BTAG_CSV",120,-10,2);
  
  TH1D* GOODPFJETN_PT       = new TH1D("GOODPFJETN_PT","GOODPFJETN_PT",1000,0.,1000.);
  TH1D* GOODPFJETN_PZ       = new TH1D("GOODPFJETN_PZ","GOODPFJETN_PZ",1000,0.,1000.); 
  TH1D* GOODPFJETN_ETA      = new TH1D("GOODPFJETN_ETA","GOODPFJETN_ETA",100,-5.,5);
  TH1D* GOODPFJETN_PHI      = new TH1D("GOODPFJETN_PHI","GOODPFJETN_PHI",64,-3.2,3.2);  
  TH1D* GOODPFJETN_BTAG   = new TH1D("GOODPFJETN_BTAG","GOODPFJETN_BTAG",40,0,4); 
  TH1D* GOODPFJETN_BTAG_CSV   = new TH1D("GOODPFJETN_BTAG_CSV","GOODPFJETN_BTAG_CSV",120,-10,2);
  
  TH1D* DELTA_R_MIN_MU_JET      = new TH1D("DELTA_R_MIN_MU_JET","DELTA_R_MIN_MU_JET",500,0,5);
  
  //ABCD method histos


  TH1D* HT_PFJET_NOJET      = new TH1D("HT_PFJET_NOJET","HT_PFJET_NOJET",100,0.,2000.);
  TH1D* YMET_NOJET          = new TH1D("YMET_NOJET","YMET_NOJET",100,0.,50.);
  TH2D* YMET_VS_HT_NOJET    = new TH2D("YMET_VS_HT_NOJET","YMET_VS_HT_NOJET",1000,0.,2000.,50,0.,50.);
  TH1D* N_A_NOJET           = new TH1D("N_A_NOJET","N_A_NOJET",1,0,1);
  TH1D* N_B_NOJET           = new TH1D("N_B_NOJET","N_B_NOJET",1,0,1);
  TH1D* N_C_NOJET           = new TH1D("N_C_NOJET","N_C_NOJET",1,0,1);
  TH1D* N_D_NOJET           = new TH1D("N_D_NOJET","N_D_NOJET",1,0,1);

  TH1D* HT_PFJET_1JET      = new TH1D("HT_PFJET_1JET","HT_PFJET_1JET",100,0.,2000.);
  TH1D* YMET_1JET          = new TH1D("YMET_1JET","YMET_1JET",100,0.,50.);
  TH2D* YMET_VS_HT_1JET    = new TH2D("YMET_VS_HT_1JET","YMET_VS_HT_1JET",1000,0.,2000.,50,0.,50.);
  TH1D* N_A_1JET           = new TH1D("N_A_1JET","N_A_1JET",1,0,1);
  TH1D* N_B_1JET           = new TH1D("N_B_1JET","N_B_1JET",1,0,1);
  TH1D* N_C_1JET           = new TH1D("N_C_1JET","N_C_1JET",1,0,1);
  TH1D* N_D_1JET           = new TH1D("N_D_1JET","N_D_1JET",1,0,1);

  TH1D* HT_PFJET_2JETS      = new TH1D("HT_PFJET_2JETS","HT_PFJET_2JETS",100,0.,2000.);
  TH1D* YMET_2JETS          = new TH1D("YMET_2JETS","YMET_2JETS",100,0.,50.);
  TH2D* YMET_VS_HT_2JETS    = new TH2D("YMET_VS_HT_2JETS","YMET_VS_HT_2JETS",1000,0.,2000.,50,0.,50.);
  TH1D* N_A_2JETS           = new TH1D("N_A_2JETS","N_A_2JETS",1,0,1);
  TH1D* N_B_2JETS           = new TH1D("N_B_2JETS","N_B_2JETS",1,0,1);
  TH1D* N_C_2JETS           = new TH1D("N_C_2JETS","N_C_2JETS",1,0,1);
  TH1D* N_D_2JETS           = new TH1D("N_D_2JETS","N_D_2JETS",1,0,1);

  TH1D* HT_PFJET_3JETS      = new TH1D("HT_PFJET_3JETS","HT_PFJET_3JETS",100,0.,2000.);
  TH1D* YMET_3JETS          = new TH1D("YMET_3JETS","YMET_3JETS",100,0.,50.);
  TH2D* YMET_VS_HT_3JETS    = new TH2D("YMET_VS_HT_3JETS","YMET_VS_HT_3JETS",1000,0.,2000.,50,0.,50.);
  TH1D* N_A_3JETS           = new TH1D("N_A_3JETS","N_A_3JETS",1,0,1);
  TH1D* N_B_3JETS           = new TH1D("N_B_3JETS","N_B_3JETS",1,0,1);
  TH1D* N_C_3JETS           = new TH1D("N_C_3JETS","N_C_3JETS",1,0,1);
  TH1D* N_D_3JETS           = new TH1D("N_D_3JETS","N_D_3JETS",1,0,1);

  TH1D* HT_PFJET_4JETS      = new TH1D("HT_PFJET_4JETS","HT_PFJET_4JETS",100,0.,2000.);
  TH1D* YMET_4JETS          = new TH1D("YMET_4JETS","YMET_4JETS",100,0.,50.);
  TH2D* YMET_VS_HT_4JETS    = new TH2D("YMET_VS_HT_4JETS","YMET_VS_HT_4JETS",1000,0.,2000.,50,0.,50.);
  TH1D* N_A_4JETS           = new TH1D("N_A_4JETS","N_A_4JETS",1,0,1);
  TH1D* N_B_4JETS           = new TH1D("N_B_4JETS","N_B_4JETS",1,0,1);
  TH1D* N_C_4JETS           = new TH1D("N_C_4JETS","N_C_4JETS",1,0,1);
  TH1D* N_D_4JETS           = new TH1D("N_D_4JETS","N_D_4JETS",1,0,1);     
  
  //================================================================================================
  // corrections methods
  //================================================================================================
  //Rochester muons scale and resolution coorections
  
   rochcor *rmcor = new rochcor();
   
   float qter = 1.0; //pterror pour les systematiques
  

  //Top trigger efficiency module

  //lumitab=[888.7,4446,7021 ,7221] //when running on all the stat
     //double lumitab[4]= {888.7,4446,0,0} ;//only 2012 A and B
     double lumitab[4]= {0,0,7021 ,7221} ;//only 2012 C and D
     //double lumitab[4]=[888.7,4446,7021 ,7221] //when running on full stat (but triggers conflict between the 2 periods)
     
     TopTriggerEfficiencyProvider *weight_provider =NULL;

     if (_isMC){ 
       
       weight_provider = new TopTriggerEfficiencyProvider(true,lumitab);
     }


  //================================================================================================
  // Clone the tree
  //================================================================================================
   
  if ( _doSkim ) {
    GetEntry(0);
    _newmuonstree=muonsChain->GetTree()->CloneTree(0);
    _newelectronstree=electronsChain->CloneTree(0);
    _newjetstree=jetsChain->CloneTree(0);
    _newverticestree=verticesChain->CloneTree(0);
    _newMETtree=METChain->CloneTree(0);
    _neweventstree=eventsChain->CloneTree(0);
    _newHLTtree=HLTChain->CloneTree(0);
  }

  //================================================================================================
  // Start the Loop
  //================================================================================================

  if (muonsChain == 0) return;

  Int_t nentries = Int_t(muonsChain->GetEntriesFast());
  if ( _nevt < 0 ) _nevt = (int)nentries; //nevt initialised to -1 unless -num option is requested  

  int nwrite = 0;
  int nselected = 0;
  
  TString cutName[100]; for (int i=0;i<100;++i) cutName[i] = "";

  TString currentfile = "";
  Int_t nbytes = 0, nb = 0;

  TRandom3 rand;

  for (Int_t jentry=0; jentry<_nevt;jentry++) { //Starting events loop
    // Int_t ientry = LoadTree(jentry);
//     if (ientry < 0) break;
    
    nb = GetEntry(jentry);   nbytes += nb;// call rootupledf GetEntry method that do the GetEntry for all 6 trees  and returns muonstree size (bytes)
    
    if (jentry % 10000 == 0) {                        //Display number of events each 10000 events
      cout << "Loop: processing event  " << jentry <<endl;     
    }

    TString thisfile = muonsChain->GetCurrentFile()->GetName();
    if ( thisfile != currentfile ) {
      currentfile = thisfile;
      cout << " => Start processing : " << currentfile << endl;
    }

    
    double WEIGHT=1; 
    
    int icut = 0;
    
    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Starting"; ++icut;

    //================================================================================================
    // PU reweighting
    //================================================================================================
   
 

    double PU_weight=1; 
    double my_truenuminter=nTrueInteractions;
    //int myinteger_truenuminter = (int) (nTrueInteractions);
      

    if (_isMC){
      N_MC_TRUE_INTERACTIONS->Fill(my_truenuminter,WEIGHT);
    }
    
    

    


    
    WEIGHT=PU_weight;
    

    if (_isMC){ 
      N_MC_TRUE_INTERACTIONS_REWEIGHTED_BEFORECUTS->Fill(my_truenuminter,WEIGHT); 
    }


    //================================================================================================
    //Triggers request 
    //================================================================================================
   
   
    bool passTrigger = true; 
   
   //  bool passTrigger = false; 
    
//        if (!_isMC ){
//  	for ( unsigned int i=0; i<HLT_vector->size(); ++i){

// 	  TString ThistrigName= (TString) HLT_vector->at(i);
// 	  if (ThistrigName.Contains("HLT_Mu17_Mu8")  || ThistrigName.Contains("HLT_Mu17_TkMu8"))  passTrigger = true;
	  
	
// 	}
//       }
//       else passTrigger = true; 
    
    
      



    //================================================================================================
    //objects selection 
    //================================================================================================

    vector<int>     indgoodmu;
    vector<int>     indgoodel;
    vector<int>    indgoodver;
    vector<int>    indgoodjet;
     
    std::shared_ptr<vector<double>>  muPt(new vector<double> () );
    std::shared_ptr<vector<double>>  muPz(new vector<double> () );
    std::shared_ptr<vector<double>>  muPhi(new vector<double>() );
    std::shared_ptr<vector<double>>  muEta(new vector<double>() );
    std::shared_ptr<vector<double>>  muOldReliso(new vector<double>() );
    
    std::shared_ptr<vector<double>>  elPt(new vector<double> () );
    std::shared_ptr<vector<double>>  elPz(new vector<double> () );
    std::shared_ptr<vector<double>>  elPhi(new vector<double>() );
    std::shared_ptr<vector<double>>  elEta(new vector<double>() );
    
    std::shared_ptr<vector<double>>  jetPt(new vector<double> () );
    std::shared_ptr<vector<double>>  jetPhi(new vector<double>() );
    std::shared_ptr<vector<double>>  jetEta(new vector<double>() );
    std::shared_ptr<vector<double>>  jetPz(new vector<double> () );
    double MET_Pt= GetP4(met_4vector,0)->Pt();
    double MET_Phi= GetP4(met_4vector,0)->Phi();
    
   
    // Good vertices selection Now done before reweighting  
    
    
    for (int i=0; i<n_vertices; ++i) {

      if (vertex_isFake[i]) continue;
       if (vertex_ndof[i] <= 4) continue;   
       //if ( fabs(PV_z->at(i)) >  25. ) continue;
      indgoodver.push_back(i);
    }


   

    
    // Good muons selection
    
    
     for (int i=0; i<n_muons; ++i) {

       //muons corrections
       TLorentzVector& muonsP4=*GetP4(muon_4vector,i);
       
       cout<<"before correction "<<GetP4(muon_4vector,i)->Pt()<<endl;
       rmcor->momcor_data(muonsP4, muon_charge[i], 0, qter);

      

       if ( _isMC ) rmcor->momcor_mc(muonsP4, muon_charge[i], 0, qter);

       cout<<"after corrections "<<GetP4(muon_4vector,i)->Pt()<<endl;

       muPt->push_back(GetP4(muon_4vector,i)->Pt());
       muPz->push_back(GetP4(muon_4vector,i)->Pz());
       muPhi->push_back(GetP4(muon_4vector,i)->Phi());
       muEta->push_back(GetP4(muon_4vector,i)->Eta());
       muOldReliso->push_back((muon_trackIso[i]+muon_ecalIso[i]+muon_hcalIso[i])/muPt->at(i));
       
       
       if ( muPt->at(i) <= 26 )                         continue;
       if ( fabs(muEta->at(i)) >= 2.1 )                 continue;
       if ( muon_normChi2[i] >= 10 )                    continue;
       if ( muon_trackerLayersWithMeasurement[i] <= 5 ) continue;
       if ( muon_globalTrackNumberOfValidHits[i] <= 0 ) continue;
       if ( muon_nMatchedStations[i] <= 1 )             continue;
       if ( muon_dB[i] >= 0.2 )                         continue;
       if ( muon_dZ[i] >= 0.5 )                         continue;
       if ( muon_nValPixelHits[i] <= 0)                 continue; 
       /* Isolation cut is done in P2PAT. No need to check that */
           
      indgoodmu.push_back(i);
    }
  
    

     for (int i=0; i<n_electrons; ++i) {
       elPt->push_back(GetP4(electron_4vector,i)->Pt());
       elPhi->push_back(GetP4(electron_4vector,i)->Phi());
       elEta->push_back(GetP4(electron_4vector,i)->Eta());
       elPz->push_back(GetP4(electron_4vector,i)->Pz());
       if ( fabs(elPt->at(i)) <= 30 )       continue;
       if ( fabs(elEta->at(i)) >= 2.5 )     continue;
       if ( !electron_passTightID[i] )      continue;
       if (fabs(electron_SCEta[i]) >= 1.4442 && fabs(electron_SCEta[i]) < 1.5660) continue;
     
       indgoodel.push_back(i);
     }

     for (int i=0; i<n_jets; ++i) {
       jetPt->push_back(GetP4(jet_4vector,i)->Pt());
       jetPz->push_back(GetP4(jet_4vector,i)->Pz());
       jetPhi->push_back(GetP4(jet_4vector,i)->Phi());
       jetEta->push_back(GetP4(jet_4vector,i)->Eta());
       if (fabs(jetPt->at(i)) < 40)     continue;
       if (fabs(jetEta->at(i)) >  2.4) continue;

      indgoodjet.push_back(i);
    }

    //================================================================================================ 
    // top triggers weights computation
    //================================================================================================ 
    
     double Trigger_weight =1;


     //if (_isMC){

//        if ( !(indgoodmu.size() < 1 || indgoodjet.size() < 4 || jetPt->at(indgoodjet[0]) < 55 || jetPt->at(indgoodjet[1]) < 45 || jetPt->at(indgoodjet[2]) < 35 || jetPt->at(indgoodjet[3]) < 20 ) ){
	 
	 
	 
// 	 Trigger_weight = weight_provider->get_weight( muPt->at(indgoodmu[0]), muEta->at(indgoodmu[0]), jetPt->at(indgoodjet[3]), jetEta->at(indgoodjet[3]), indgoodver.size(), indgoodjet.size(),1 );
//        } 
       
     //}
        WEIGHT*=Trigger_weight;   

    

     // if ( !passTrigger ) continue; 

//     ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Pass single mu top PAG triggers"; ++icut;




     
    //================================================================================================
    //Compute reconstructed variables 
    //================================================================================================

     


    //Z->mumu variables

    double PTZ=0;
    double MZ =0;
    double Pt_recoil=0;
    double ZPtrecoil_on_ZPt=0;
    double ZPtrecoil_ortho_ZPt=0;
    double Delta_Phi_PtZ_Ptrecoil=0;
    double Delta_Phi_Mus=0;
    double Z_Phi=0;
    
    
    if ( indgoodmu.size()>= 2 ){

      int i1 = indgoodmu[0];
      int i2 = indgoodmu[1];
    
      double px1 = GetP4(muon_4vector,i1)->Px(); 
      double py1 = GetP4(muon_4vector,i1)->Py();
      double pz1 = GetP4(muon_4vector,i1)->Pz();
      double px2 = GetP4(muon_4vector,i2)->Px(); 
      double py2 = GetP4(muon_4vector,i2)->Py();
      double pz2 = GetP4(muon_4vector,i2)->Pz();
      double pxZ = px1+px2;
      double pyZ = py1+py2;
      double pzZ = pz1+pz2;
      double p1 = sqrt(px1*px1+py1*py1+pz1*pz1);
      double p2 = sqrt(px2*px2+py2*py2+pz2*pz2);
      double pZ = sqrt (pxZ*pxZ+pyZ*pyZ+pzZ*pzZ);
       
      double E1 = sqrt(p1*p1+0.106*0.106);
      double E2 = sqrt(p2*p2+0.106*0.106);
      MZ = sqrt(pow(E1+E2,2)-pZ*pZ);
      PTZ= sqrt (pxZ*pxZ+pyZ*pyZ);
      
      Delta_Phi_Mus=kinem::delta_phi(kinem::phi(px1,py1),kinem::phi(px2,py2));
      double Px_recoil = -MET_Pt*cos (MET_Phi)-cos(muPhi->at(i1))*muPt->at(i1)-cos(muPhi->at(i2))*muPt->at(i2);
      double Py_recoil = -MET_Pt*sin (MET_Phi)-sin(muPhi->at(i1))*muPt->at(i1)-sin(muPhi->at(i2))*muPt->at(i2);
      Pt_recoil = sqrt (Px_recoil*Px_recoil+Py_recoil*Py_recoil);

      Delta_Phi_PtZ_Ptrecoil=kinem::delta_phi(kinem::phi(pxZ,pyZ),kinem::phi(Px_recoil,Py_recoil));
      double real_Delta_Phi_PtZ_Ptrecoil=kinem::phi(pxZ,pyZ)-kinem::phi(Px_recoil,Py_recoil);
      ZPtrecoil_on_ZPt=Pt_recoil*cos(real_Delta_Phi_PtZ_Ptrecoil);
      
      ZPtrecoil_ortho_ZPt=-Pt_recoil*sin(real_Delta_Phi_PtZ_Ptrecoil); //on projette sur vecteur ortho à ptjet (cos(pi/2+x)=-sin(x))
      
      Z_Phi=kinem::phi(pxZ,pyZ);
      
    }

    

    // Multiple parton scattering variables
    double Delta_phi_j1_j2=-1;
    double Delta_pt_j1_j2=-1;
    
    if  ( indgoodjet.size() >= 2 ){
      Delta_phi_j1_j2=kinem::delta_phi(jetPhi->at(indgoodjet[0]),jetPhi->at(indgoodjet[1]));
      Delta_pt_j1_j2=jetPt->at(indgoodjet[0])-jetPt->at(indgoodjet[1]);

    }


    // W->mu variables
    double wmt  =0; 
    if ( indgoodmu.size() >= 1 ) {
      int i1 = indgoodmu[0];
      double Delta_Phi_mu_met=kinem::delta_phi(muPhi->at(i1),MET_Phi);     
      wmt  = sqrt(2*MET_Pt*muPt->at(i1)*( 1-cos(Delta_Phi_mu_met) ) );
    }

    
    //================================================================================================
    //Fill Histo before Cuts 
    //================================================================================================
    PASS_TRIGGER->Fill(passTrigger,WEIGHT);

    VERTEX_NGOOD_BEFORECUTS->Fill(indgoodver.size(),WEIGHT);
    VERTEX_N_BEFORECUTS->Fill(n_vertices,WEIGHT);  
    

    MUONS_N_BEFORECUT->Fill(n_muons,WEIGHT);
    GOODMUONS_N_BEFORECUT->Fill(indgoodmu.size(),WEIGHT);

    for (int i=0; i<n_muons; ++i) {     
       MUONS_PT_BEFORECUT->Fill(muPt->at(i),WEIGHT);
       MUONS_ETA_BEFORECUT->Fill(muEta->at(i),WEIGHT);
       MUONS_NEW_RELISO_BCORR_BEFORECUT->Fill(muon_deltaBetaCorrectedRelIsolation[i],WEIGHT);
       MUONS_NEW_RELISO_BEFORECUT->Fill(muon_relIsolation[i],WEIGHT);
       MUONS_OLD_RELISO_BEFORECUT->Fill(muOldReliso->at(i),WEIGHT);
       MUONS_NORMCHI2_BEFORECUT->Fill(muon_normChi2[i],WEIGHT);
       MUONS_TRACK_LAYERS_BEFORECUT->Fill(muon_trackerLayersWithMeasurement[i],WEIGHT);
       MUONS_TRACK_VAL_HITS_BEFORECUT->Fill(muon_globalTrackNumberOfValidHits[i],WEIGHT);
       MUONS_MATCHED_STATIONS_BEFORECUT->Fill(muon_nMatchedStations[i],WEIGHT);
       MUONS_DB_BEFORECUT->Fill(muon_dB[i],WEIGHT);
       MUONS_DZ_BEFORECUT->Fill(muon_dZ[i],WEIGHT);
       MUONS_PIXEL_VAL_HITS_BEFORECUT->Fill(muon_nValPixelHits[i],WEIGHT);
    }
 
    ALLPFJET_N_BEFORECUT->Fill(n_jets,WEIGHT);
    GOODPFJET_N_BEFORECUT->Fill(indgoodjet.size(),WEIGHT);
    
    for (int i=0; i<n_jets; ++i) {
      ALLPFJET_PT_BEFORECUT->Fill(jetPt->at(i),WEIGHT);
      ALLPFJET_ETA_BEFORECUT->Fill(jetEta->at(i),WEIGHT);
    }

    
    if ( indgoodjet.size()>0 ) GOODPFJET1_PT_BEFORECUT->Fill(jetPt->at(indgoodjet[0]));
    if ( indgoodjet.size()>1 ) GOODPFJET2_PT_BEFORECUT->Fill(jetPt->at(indgoodjet[1]));
    if ( indgoodjet.size()>2 ) GOODPFJET3_PT_BEFORECUT->Fill(jetPt->at(indgoodjet[2]));
    if ( indgoodjet.size()>3 ) GOODPFJET4_PT_BEFORECUT->Fill(jetPt->at(indgoodjet[3]));
    


    WSEL_MT_GROSS_BEFORECUT->Fill(wmt,WEIGHT);
    
    ZSEL_M_GROSS_BEFORECUT->Fill(MZ,WEIGHT);
    

    //================================================================================================
    // Cuts
    //================================================================================================ 
     
    
      if ( indgoodmu.size() < 1 ) continue;

     ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "At least 1 good iso Muons"; ++icut;



    //  if ( MZ < 50 ) continue;

//     ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Dimuon mass sup 50 GeV"; ++icut;
   
    

    
    
    // if ( wmt < 50 ) continue;
//     ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "W transverse mass sup 50"; ++icut;
     //================================================================================================
     // Plots
     //================================================================================================

     //weights
     PU_WEIGHT->Fill(PU_weight,1);
      
     TRIGGER_WEIGHT->Fill(Trigger_weight,1);
      
     TOTAL_WEIGHT->Fill(WEIGHT,1);
    

    
    //Delta min mu jet

     for ( unsigned int i=0; i<indgoodmu.size(); ++i) {

      double Delta_Phi_mu_jet=0;
      double Delta_Eta_mu_jet=0;
      double Delta_R_min=100;

      for(unsigned int u=0; u<indgoodjet.size(); ++u){
	 
	Delta_Phi_mu_jet=kinem::delta_phi(muPhi->at(indgoodmu[i]),jetPhi->at(indgoodjet[u]));
	//if (fabs(Delta_Phi_mu_jet)>Pi) Delta_Phi_mu_jet=2*Pi -fabs(Delta_Phi_mu_jet); 
	Delta_Eta_mu_jet=muEta->at(indgoodmu[i])-jetEta->at(indgoodjet[u]);
	double Delta_R=sqrt(pow(Delta_Phi_mu_jet,2)+pow(Delta_Eta_mu_jet,2));
	if ( Delta_R < Delta_R_min )
	  Delta_R_min=Delta_R;	  
      }
      
      DELTA_R_MIN_MU_JET->Fill(fabs(Delta_R_min),WEIGHT);

    } 

    //------------------------
    // Plot W/Z selections
    //------------------------

    //W selection

    if ( indgoodmu.size() >= 1 ) {
      

      WSEL_MT_SHARP ->Fill(wmt,WEIGHT);
      WSEL_MT_GROSS ->Fill(wmt,WEIGHT);
      WSEL_PFMET ->Fill(MET_Pt,WEIGHT);



      if (indgoodjet.size() == 0 ){
	WSEL_MT_SHARP_NOJET ->Fill(wmt,WEIGHT);
	WSEL_PFMET_NOJET ->Fill(MET_Pt,WEIGHT);
      }

      if (indgoodjet.size() == 1 ){
	WSEL_MT_SHARP_1JET ->Fill(wmt,WEIGHT);
	WSEL_PFMET_1JET ->Fill(MET_Pt,WEIGHT);
      }

      if (indgoodjet.size() == 2 ){
	WSEL_MT_SHARP_2JETS ->Fill(wmt,WEIGHT);
	WSEL_PFMET_2JETS ->Fill(MET_Pt,WEIGHT);
	WSEL_GOODPFJET_DELTAPHI_2JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	WSEL_GOODPFJET_DELTAPT_2JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }

      if (indgoodjet.size() == 3 ){
	WSEL_MT_SHARP_3JETS ->Fill(wmt,WEIGHT);
	WSEL_PFMET_3JETS ->Fill(MET_Pt,WEIGHT);
	WSEL_GOODPFJET_DELTAPHI_3JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	WSEL_GOODPFJET_DELTAPT_3JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }
      
      if (indgoodjet.size() >= 4 ){
	WSEL_MT_SHARP_4JETS ->Fill(wmt,WEIGHT);
	WSEL_PFMET_4JETS ->Fill(MET_Pt,WEIGHT);
	WSEL_GOODPFJET_DELTAPHI_4JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	WSEL_GOODPFJET_DELTAPT_4JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }
      
    }

    // Z selection

    if ( indgoodmu.size()  >= 2 ) {
      
      ZSEL_DELTA_PHI_MUS->Fill(Delta_Phi_Mus,WEIGHT);
      ZSEL_PT_RECOIL->Fill(Pt_recoil,WEIGHT);
      ZSEL_RECOIL_ON_PT->Fill(ZPtrecoil_on_ZPt,WEIGHT);
      ZSEL_RECOIL_ORTHO_PT->Fill(ZPtrecoil_ortho_ZPt,WEIGHT);
      ZSEL_DELTA_PHI_PTZ_PTRECOIL->Fill(Delta_Phi_PtZ_Ptrecoil,WEIGHT);   
      ZSEL_PHI->Fill(Z_Phi,WEIGHT);
      ZSEL_M_SHARP->Fill(MZ,WEIGHT);
      ZSEL_M_GROSS->Fill(MZ,WEIGHT);
      MUONS_CHARGE_PRODUCT->Fill(muon_charge[indgoodmu[0]]*muon_charge[indgoodmu[1]],WEIGHT);
      if ( MZ >= 50 ) ZSEL_M_SUP50->Fill(MZ,WEIGHT);

      ZSEL_PT_SHARP->Fill(PTZ,WEIGHT);
      ZSEL_PT_GROSS->Fill(PTZ,WEIGHT);
      
      ZSEL_PFMET->Fill(MET_Pt,WEIGHT);

      if (indgoodjet.size() == 0 ){
	ZSEL_M_SHARP_NOJET->Fill(MZ,WEIGHT);
	ZSEL_PT_SHARP_NOJET->Fill(PTZ,WEIGHT);
	ZSEL_PFMET_NOJET->Fill(MET_Pt,WEIGHT);
      }
      
      if (indgoodjet.size() == 1 ){
	ZSEL_M_SHARP_1JET->Fill(MZ,WEIGHT);
	ZSEL_PT_SHARP_1JET->Fill(PTZ,WEIGHT);
	ZSEL_PFMET_1JET->Fill(MET_Pt,WEIGHT);
      }
      
      if (indgoodjet.size() == 2 ){
	ZSEL_M_SHARP_2JETS->Fill(MZ,WEIGHT);
	ZSEL_PT_SHARP_2JETS->Fill(PTZ,WEIGHT);
	ZSEL_PFMET_2JETS->Fill(MET_Pt,WEIGHT);
	ZSEL_GOODPFJET_DELTAPHI_2JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	ZSEL_GOODPFJET_DELTAPT_2JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }

      if (indgoodjet.size() == 3 ){
	ZSEL_M_SHARP_3JETS->Fill(MZ,WEIGHT);
	ZSEL_PT_SHARP_3JETS->Fill(PTZ,WEIGHT);
	ZSEL_PFMET_3JETS->Fill(MET_Pt,WEIGHT);
	ZSEL_GOODPFJET_DELTAPHI_3JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	ZSEL_GOODPFJET_DELTAPT_3JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }
      
      if (indgoodjet.size() >= 4 ){
	ZSEL_M_SHARP_4JETS->Fill(MZ,WEIGHT);
	ZSEL_PT_SHARP_4JETS->Fill(PTZ,WEIGHT);
	ZSEL_PFMET_4JETS->Fill(MET_Pt,WEIGHT);
	ZSEL_GOODPFJET_DELTAPHI_4JETS->Fill(Delta_phi_j1_j2,WEIGHT);
	ZSEL_GOODPFJET_DELTAPT_4JETS->Fill(Delta_pt_j1_j2,WEIGHT);
      }
    }
    if (_isMC){
      N_MC_TRUE_INTERACTIONS_REWEIGHTED->Fill(my_truenuminter,WEIGHT);
    }
    


    
    VERTEX_N->Fill(n_vertices,WEIGHT);
    VERTEX_NGOOD->Fill(indgoodver.size(),WEIGHT);
    
    for (unsigned int i=0; i<indgoodver.size();++i) {
      VERTEX_X->Fill(vertex_vx[indgoodver[i]],WEIGHT);
      VERTEX_Y->Fill(vertex_vy[indgoodver[i]],WEIGHT);
      VERTEX_Z->Fill(vertex_vz[indgoodver[i]],WEIGHT);
      
      VERTEX_NDOF->Fill(vertex_ndof[indgoodver[i]],WEIGHT);
      VERTEX_CHI2NORM->Fill(vertex_normChi2[indgoodver[i]],WEIGHT);
      VERTEX_ISFAKE->Fill(vertex_isFake[indgoodver[i]],WEIGHT);
      VERTEX_NTRACKS->Fill(vertex_ntracks[indgoodver[i]],WEIGHT);
      
    }
    
    
      

    if ( indgoodver.size() !=0 ){
      VERTEX0_X->Fill(vertex_vx[indgoodver[0]],WEIGHT);
      VERTEX0_Y->Fill(vertex_vy[indgoodver[0]],WEIGHT);
      VERTEX0_Z->Fill(vertex_vz[indgoodver[0]],WEIGHT);
      VERTEX0_NDOF->Fill(vertex_ndof[indgoodver[0]],WEIGHT);
      VERTEX0_CHI2NORM->Fill(vertex_normChi2[indgoodver[0]],WEIGHT);
      VERTEX0_ISFAKE->Fill(vertex_isFake[indgoodver[0]],WEIGHT);
      VERTEX0_NTRACKS->Fill(vertex_ntracks[indgoodver[0]],WEIGHT);
      
      
      }
      

      ELECTRONS_N->Fill(indgoodel.size(),WEIGHT);
    
    
    for ( unsigned int i=0; i<indgoodel.size(); ++i) {
      //ELECTRONS_CHG->Fill(elChg->at(indgoodel[i]),WEIGHT);
      ELECTRONS_PT->Fill(elPt->at(indgoodel[i]),WEIGHT);
      ELECTRONS_PZ->Fill(elPz->at(indgoodel[i]),WEIGHT);
      ELECTRONS_ETA->Fill(elEta->at(indgoodel[i]),WEIGHT);
      ELECTRONS_PHI->Fill(elPhi->at(indgoodel[i]),WEIGHT);
      ELECTRONS_RELISO->Fill(electron_rhoCorrectedRelIsolation[indgoodel[i]],WEIGHT);
      
    }
    
    MUONS_N->Fill(indgoodmu.size(),WEIGHT);
    
    for ( unsigned int i=0; i<indgoodmu.size(); ++i) {
      MUONS_CHG->Fill(muon_charge[indgoodmu[i]],WEIGHT);
      MUONS_PT->Fill(muPt->at(indgoodmu[i]),WEIGHT);
      MUONS_PZ->Fill(muPz->at(indgoodmu[i]),WEIGHT);
      MUONS_ETA->Fill(muEta->at(indgoodmu[i]),WEIGHT);
      MUONS_PHI->Fill(muPhi->at(indgoodmu[i]),WEIGHT);
      MUONS_NEW_RELISO_BCORR->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[i]],WEIGHT);
      MUONS_NEW_RELISO->Fill(muon_relIsolation[indgoodmu[i]],WEIGHT);
      MUONS_OLD_RELISO->Fill(muOldReliso->at(indgoodmu[i]),WEIGHT);
      MUONS_NORMCHI2->Fill(muon_normChi2[indgoodmu[i]],WEIGHT);
      MUONS_TRACK_LAYERS->Fill(muon_trackerLayersWithMeasurement[indgoodmu[i]],WEIGHT);
      MUONS_TRACK_VAL_HITS->Fill(muon_globalTrackNumberOfValidHits[indgoodmu[i]],WEIGHT);
      MUONS_MATCHED_STATIONS->Fill(muon_nMatchedStations[indgoodmu[i]],WEIGHT);
      MUONS_DB->Fill(muon_dB[indgoodmu[i]],WEIGHT);
      MUONS_D0->Fill(muon_d0[indgoodmu[i]],WEIGHT);
      MUONS_DZ->Fill(muon_dZ[indgoodmu[i]],WEIGHT);
      MUONS_PIXEL_VAL_HITS->Fill(muon_nValPixelHits[indgoodmu[i]],WEIGHT);
      MUONS_VZ->Fill(muon_vz[indgoodmu[i]],WEIGHT);


	
    }

    if ( indgoodmu.size() >= 1 ) {
      
      MUON1_PT->Fill(muPt->at(indgoodmu[0]),WEIGHT);
      MUON1_PZ->Fill(muPz->at(indgoodmu[0]),WEIGHT);
      MUON1_ETA->Fill(muEta->at(indgoodmu[0]),WEIGHT);
      MUON1_PHI->Fill(muPhi->at(indgoodmu[0]),WEIGHT);
      MUON1_NEW_RELISO_BCORR->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[0]],WEIGHT);
      MUON1_NEW_RELISO->Fill(muon_relIsolation[indgoodmu[0]],WEIGHT);
      MUON1_OLD_RELISO->Fill(muOldReliso->at(indgoodmu[0]),WEIGHT);
    }

    if ( indgoodmu.size() >= 2 ) {
      
      MUON2_PT->Fill(muPt->at(indgoodmu[1]),WEIGHT);
      MUON2_PZ->Fill(muPz->at(indgoodmu[1]),WEIGHT);
      MUON2_ETA->Fill(muEta->at(indgoodmu[1]),WEIGHT);
      MUON2_PHI->Fill(muPhi->at(indgoodmu[1]),WEIGHT);
      MUON2_NEW_RELISO_BCORR->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[1]],WEIGHT);
      MUON2_NEW_RELISO->Fill(muon_relIsolation[indgoodmu[1]],WEIGHT);
      MUON2_OLD_RELISO->Fill(muOldReliso->at(indgoodmu[1]),WEIGHT);
    }


    
    


	//MET_SUMET->Fill(MET_sumEt,WEIGHT);
    MET_PT->Fill(MET_Pt,WEIGHT);
    MET_PHI->Fill(MET_Phi,WEIGHT);
    
    



    int allpfjet_n30 = 0;
    int allpfjet_n35 = 0;
    int allpfjet_n40 = 0;
    int allpfjet_n45 = 0;
    int allpfjet_n50 = 0;
    int allpfjet_n55 = 0;

    for (int i=0; i<n_jets ; ++i){

	
	if ( jetPt->at(i) > 30 ) ++allpfjet_n30;
	if ( jetPt->at(i) > 35 ) ++allpfjet_n35;
	if ( jetPt->at(i) > 40 ) ++allpfjet_n40;
	if ( jetPt->at(i) > 45 ) ++allpfjet_n45;
	if ( jetPt->at(i) > 50 ) ++allpfjet_n50;
	if ( jetPt->at(i) > 55 ) ++allpfjet_n55;
	
	
	
	ALLPFJET_PT->Fill(jetPt->at(i),WEIGHT);
	ALLPFJET_PZ->Fill(jetPz->at(i),WEIGHT);
	ALLPFJET_ETA->Fill(jetEta->at(i),WEIGHT);
	ALLPFJET_PHI->Fill(jetPhi->at(i),WEIGHT);
       	ALLPFJET_BTAG->Fill(jet_btag_jetProb[i],WEIGHT);
	ALLPFJET_BTAG_CSV->Fill(jet_btag_CSV[i],WEIGHT);

    }
    

    
    ALLPFJET_N30->Fill((double)allpfjet_n30,WEIGHT);
    ALLPFJET_N35->Fill((double)allpfjet_n35,WEIGHT);
    ALLPFJET_N40->Fill((double)allpfjet_n40,WEIGHT);
    ALLPFJET_N45->Fill((double)allpfjet_n45,WEIGHT);
    ALLPFJET_N50->Fill((double)allpfjet_n50,WEIGHT);
    ALLPFJET_N55->Fill((double)allpfjet_n55,WEIGHT);

    

    

    int goodpfjet_n20 = 0;
    int goodpfjet_n25 = 0;
    int goodpfjet_n30 = 0;
    int goodpfjet_n35 = 0;
    int goodpfjet_n40 = 0;
    int goodpfjet_n45 = 0;
    int goodpfjet_n50 = 0;
    int goodpfjet_n55 = 0;
    double ht_pfjet=0;
    double mht_pfjet=0;
    double mhtx_pfjet=0;
    double mhty_pfjet=0;


    for (unsigned int i=0; i<indgoodjet.size() ; ++i){

	if ( jetPt->at(indgoodjet[i]) > 20 ) ++goodpfjet_n20;
	if ( jetPt->at(indgoodjet[i]) > 25 ) ++goodpfjet_n25;
	if ( jetPt->at(indgoodjet[i]) > 30 ) ++goodpfjet_n30;
	if ( jetPt->at(indgoodjet[i]) > 35 ) ++goodpfjet_n35;
	if ( jetPt->at(indgoodjet[i]) > 40 ) ++goodpfjet_n40;
	if ( jetPt->at(indgoodjet[i]) > 45 ) ++goodpfjet_n45;
	if ( jetPt->at(indgoodjet[i]) > 50 ) ++goodpfjet_n50;
	if ( jetPt->at(indgoodjet[i]) > 55 ) ++goodpfjet_n55;
	
	
	
	
	GOODPFJET_PT->Fill(jetPt->at(indgoodjet[i]),WEIGHT);
	GOODPFJET_PZ->Fill(jetPz->at(indgoodjet[i]),WEIGHT);
	GOODPFJET_ETA->Fill(jetEta->at(indgoodjet[i]),WEIGHT);
	GOODPFJET_PHI->Fill(jetPhi->at(indgoodjet[i]),WEIGHT);
       	GOODPFJET_BTAG->Fill(jet_btag_jetProb[indgoodjet[i]],WEIGHT);
	GOODPFJET_BTAG_CSV->Fill(jet_btag_CSV[indgoodjet[i]],WEIGHT);
       	ht_pfjet+=fabs(jetPt->at(indgoodjet[i]));
	
	
	mhtx_pfjet-=(cos(jetPhi->at(indgoodjet[i]))*(jetPt->at(indgoodjet[i])));
	mhty_pfjet-=(sin(jetPhi->at(indgoodjet[i]))*(jetPt->at(indgoodjet[i])));
	

    }
    
    HT_PFJET->Fill((double)ht_pfjet,WEIGHT);
    mht_pfjet=sqrt(mhtx_pfjet*mhtx_pfjet+mhty_pfjet*mhty_pfjet);
    MHT_PFJET->Fill((double)mht_pfjet,WEIGHT);

    GOODPFJET_N20->Fill((double)goodpfjet_n20,WEIGHT);
    GOODPFJET_N25->Fill((double)goodpfjet_n25,WEIGHT);  
    GOODPFJET_N30->Fill((double)goodpfjet_n30,WEIGHT);
    GOODPFJET_N35->Fill((double)goodpfjet_n35,WEIGHT);
    GOODPFJET_N40->Fill((double)goodpfjet_n40,WEIGHT);
    GOODPFJET_N45->Fill((double)goodpfjet_n45,WEIGHT);
    GOODPFJET_N50->Fill((double)goodpfjet_n50,WEIGHT);
    GOODPFJET_N55->Fill((double)goodpfjet_n55,WEIGHT);

    if ( indgoodjet.size() >= 1 ){
      GOODPFJET1_PT->Fill(jetPt->at(indgoodjet[0]),WEIGHT);
      GOODPFJET1_PZ->Fill(jetPz->at(indgoodjet[0]),WEIGHT);
      GOODPFJET1_ETA->Fill(jetEta->at(indgoodjet[0]),WEIGHT);
      GOODPFJET1_PHI->Fill(jetPhi->at(indgoodjet[0]),WEIGHT);
      GOODPFJET1_BTAG->Fill(jet_btag_jetProb[0],WEIGHT);
      GOODPFJET1_BTAG_CSV->Fill(jet_btag_CSV[0],WEIGHT);
    }
    
    if ( indgoodjet.size() >= 2 ){
      GOODPFJET2_PT->Fill(jetPt->at(indgoodjet[1]),WEIGHT);
      GOODPFJET2_PZ->Fill(jetPz->at(indgoodjet[1]),WEIGHT);
      GOODPFJET2_ETA->Fill(jetEta->at(indgoodjet[1]),WEIGHT);
      GOODPFJET2_PHI->Fill(jetPhi->at(indgoodjet[1]),WEIGHT);
      GOODPFJET2_BTAG->Fill(jet_btag_jetProb[indgoodjet[1]],WEIGHT);
      GOODPFJET_DELTAPHI->Fill(Delta_phi_j1_j2,WEIGHT);
      GOODPFJET_DELTAPT->Fill(Delta_pt_j1_j2,WEIGHT);
      GOODPFJET2_BTAG_CSV->Fill(jet_btag_CSV[1],WEIGHT);
    }
    
    if ( indgoodjet.size() >= 3 ){
      GOODPFJET3_PT->Fill(jetPt->at(indgoodjet[2]),WEIGHT);
      GOODPFJET3_PZ->Fill(jetPz->at(indgoodjet[2]),WEIGHT);
      GOODPFJET3_ETA->Fill(jetEta->at(indgoodjet[2]),WEIGHT);
      GOODPFJET3_PHI->Fill(jetPhi->at(indgoodjet[2]),WEIGHT);
      GOODPFJET3_BTAG->Fill(jet_btag_jetProb[indgoodjet[2]],WEIGHT);
      GOODPFJET3_BTAG_CSV->Fill(jet_btag_CSV[2],WEIGHT);
    }

    if ( indgoodjet.size() >= 4 ){
      GOODPFJET4_PT->Fill(jetPt->at(indgoodjet[3]),WEIGHT);
      GOODPFJET4_PZ->Fill(jetPz->at(indgoodjet[3]),WEIGHT);
      GOODPFJET4_ETA->Fill(jetEta->at(indgoodjet[3]),WEIGHT);
      GOODPFJET4_PHI->Fill(jetPhi->at(indgoodjet[3]),WEIGHT);
      GOODPFJET4_BTAG->Fill(jet_btag_jetProb[indgoodjet[3]],WEIGHT);
      GOODPFJET4_BTAG_CSV->Fill(jet_btag_CSV[3],WEIGHT);
    }

    if ( indgoodjet.size() >= 5 ){
      for (unsigned int i=4; i<indgoodjet.size() ; ++i){
	GOODPFJETN_PT->Fill(jetPt->at(indgoodjet[i]),WEIGHT);
	GOODPFJETN_PZ->Fill(jetPz->at(indgoodjet[i]),WEIGHT);
	GOODPFJETN_ETA->Fill(jetEta->at(indgoodjet[i]),WEIGHT);
	GOODPFJETN_PHI->Fill(jetPhi->at(indgoodjet[i]),WEIGHT);
      	GOODPFJETN_BTAG->Fill(jet_btag_jetProb[indgoodjet[i]],WEIGHT);
	GOODPFJETN_BTAG_CSV->Fill(jet_btag_CSV[i],WEIGHT);
      }
    }
    
    //ABCD method histos fill

    double ymet=MET_Pt/sqrt(ht_pfjet);
    
    if (indgoodjet.size() == 0 ){
      HT_PFJET_NOJET->Fill((double)ht_pfjet,WEIGHT);
      YMET_NOJET->Fill((double)ymet,WEIGHT);
      YMET_VS_HT_NOJET->Fill((double)ht_pfjet,(double)ymet,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 2.5 && ymet < 5.5) N_A_NOJET->Fill(0.5,WEIGHT); 
      if (ht_pfjet > 650 && ymet > 2.5 && ymet < 5.5) N_B_NOJET->Fill(0.5,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 5.5) N_C_NOJET->Fill(0.5,WEIGHT);   
      if (ht_pfjet > 650 && ymet > 5.5) N_D_NOJET->Fill(0.5,WEIGHT);
    }
    
    if (indgoodjet.size() == 1 ){
      HT_PFJET_1JET->Fill((double)ht_pfjet,WEIGHT);
      YMET_1JET->Fill((double)ymet,WEIGHT);
      YMET_VS_HT_1JET->Fill((double)ht_pfjet,(double)ymet,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 2.5 && ymet < 5.5) N_A_1JET->Fill(0.5,WEIGHT); 
      if (ht_pfjet > 650 && ymet > 2.5 && ymet < 5.5) N_B_1JET->Fill(0.5,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 5.5) N_C_1JET->Fill(0.5,WEIGHT);   
      if (ht_pfjet > 650 && ymet > 5.5) N_D_1JET->Fill(0.5,WEIGHT);
    }
    
    if (indgoodjet.size() == 2 ){
      HT_PFJET_2JETS->Fill((double)ht_pfjet,WEIGHT);
      YMET_2JETS->Fill((double)ymet,WEIGHT);
      YMET_VS_HT_2JETS->Fill((double)ht_pfjet,(double)ymet,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 2.5 && ymet < 5.5) N_A_2JETS->Fill(0.5,WEIGHT); 
      if (ht_pfjet > 650 && ymet > 2.5 && ymet < 5.5) N_B_2JETS->Fill(0.5,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 5.5) N_C_2JETS->Fill(0.5,WEIGHT);   
      if (ht_pfjet > 650 && ymet > 5.5) N_D_2JETS->Fill(0.5,WEIGHT);
    }

    if (indgoodjet.size() == 3 ){
      HT_PFJET_3JETS->Fill((double)ht_pfjet,WEIGHT);
      YMET_3JETS->Fill((double)ymet,WEIGHT);
      YMET_VS_HT_3JETS->Fill((double)ht_pfjet,(double)ymet,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 2.5 && ymet < 5.5) N_A_3JETS->Fill(0.5,WEIGHT); 
      if (ht_pfjet > 650 && ymet > 2.5 && ymet < 5.5) N_B_3JETS->Fill(0.5,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 5.5) N_C_3JETS->Fill(0.5,WEIGHT);   
      if (ht_pfjet > 650 && ymet > 5.5) N_D_3JETS->Fill(0.5,WEIGHT);
    }

    if (indgoodjet.size() == 4 ){
      HT_PFJET_4JETS->Fill((double)ht_pfjet,WEIGHT);
      YMET_4JETS->Fill((double)ymet,WEIGHT);
      YMET_VS_HT_4JETS->Fill((double)ht_pfjet,(double)ymet,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 2.5 && ymet < 5.5) N_A_4JETS->Fill(0.5,WEIGHT); 
      if (ht_pfjet > 650 && ymet > 2.5 && ymet < 5.5) N_B_4JETS->Fill(0.5,WEIGHT);
      if (ht_pfjet > 300 && ht_pfjet < 650 && ymet > 5.5) N_C_4JETS->Fill(0.5,WEIGHT);   
      if (ht_pfjet > 650 && ymet > 5.5) N_D_4JETS->Fill(0.5,WEIGHT);
    }
  
  
    
 
    // Write new tree
    //===============================================================================================

    if (_doSkim) {
      _newmuonstree->Fill();
      _newelectronstree->Fill();
      _newjetstree->Fill();
      _newverticestree->Fill();
      _newMETtree->Fill();
      _neweventstree->Fill();
      _newHLTtree->Fill();
      nwrite++;
    }

    ++nselected;
  }

  //================================================================================================
  // Delete dynamical objects
  //================================================================================================
  delete weight_provider;
  delete rmcor;

  cout << "======================================================================" << endl;
  for ( Int_t i=0; i<5 ; i++ ){
  cout << "Number of events after cut " << cutName[i] << " : " << ICUT->GetBinContent(i+1) << endl;
  }

  
  cout << "======================================================================" << endl;
  cout << "Total Number of events selected = "  << nselected                       << endl;
  cout << "Total Number of events skimmed = "  << nwrite                          << endl;
  cout << "======================================================================" << endl;

  _newfile->Write();
  _newfile->Close();

}

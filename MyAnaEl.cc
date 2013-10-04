#define MyAna_cxx

#include <memory>
#include "MyAna.h"
#include "MetRes.h"
#include "TopTriggerEfficiencyProvider.h"
#include "PUReweighter.h"
//#include "MuScleFitCorrector_v3/MuScleFitCorrector.h"


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

std::vector<double> Thrust_calculate (const std::vector<TLorentzVector>& Input_PtEtaPhiE);


MyAna::MyAna(TTree *_muonstree, TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree, TTree *_muonsloosetree, TTree *_electronsloosetree, TTree *_PFparttree, TTree *_MCtree)
  :RootTupleDefs(_muonstree, _electronstree, _jetstree, _METtree, _verticestree, _eventstree, _HLTtree, _muonsloosetree, _electronsloosetree, _PFparttree, _MCtree)
{
   _isMC     = false;
   _isTTbar    = false;
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

  Double_t PUWEIGHT[41] = {0.343966,0.421778,0.436096,0.244907,0.159864,0.301344,0.241472,0.274829,0.44007,0.758224,1.17234,1.57047,1.65648,1.48344,1.25881,1.09602,1.02284,1.01614,1.05619,1.11854,1.17075,1.1998,1.20717,1.1982,1.17317,1.13123,1.0737,1.00772,0.928615,0.834017,0.723992,0.605741,0.485348,0.371787,0.270933,0.187491,0.124365,0.0791913,0.0484192,0.0288752,0.0127159};
  Double_t TRIGWEIGHT[18][2] = {{0.84,0.65},{0.87,0.67},{0.87,0.69},{0.88,0.70},{0.88,0.71},{0.89,0.73},{0.90,0.74},{0.90,0.75},{0.91,0.77},{0.91,0.77},{0.91,0.78},{0.92,0.79},{0.93,0.80},{0.93,0.81},{0.94,0.82},{0.94,0.83},{0.94,0.80},{0.94,0.79}};
  int counter[20]; for (int i=0; i<20; ++i) counter[i] = 0;

  _newfile = new TFile(_rootName.c_str(),"RECREATE");

  //================================================================================================
  // HISTOGRAMS
  //================================================================================================

  TH1::SetDefaultSumw2(true);
  TH1F* ICUT 		      = new TH1F("ICUT","ICUT",100,0.,100.);
  ICUT->SetOption("bar");
  ICUT->SetBarWidth(0.75);
  ICUT->SetBarOffset(0.125);

  TH1F* CUTS_MUONS_N          = new TH1F("CUTS_MUONS_N","CUTS_MUONS_N",10,0,10.);
  TH1F* CUTS_ELECTRONS_N      = new TH1F("CUTS_ELECTRONS_N","CUTS_ELECTRONS_N",10,0,10.);
  TH1F* CUTS_LEPTONS_N        = new TH1F("CUTS_LEPTONS_N","CUTS_LEPTONS_N",10,0,10.);
  TH1F* CUTS_GOODJET_N        = new TH1F("CUTS_GOODJET_N","CUTS_GOODJET_N",20,0.,20.);
  TH1F* CUTS_GOODJET_NB       = new TH1F("CUTS_GOODJET_NB","CUTS_GOODJET_NB",20,0.,20.);
  TH1F* CUT_JPSICAND_M        = new TH1F("CUT_JPSICAND_M","CUT_JPSICAND_M",200,2.8,3.4);
  TH1F* CUT_JPSICAND_N        = new TH1F("CUT_JPSICAND_N","CUT_JPSICAND_N",10,0,10.);
  TH1F* CUT_JPSICAND_CHI2     = new TH1F("CUT_JPSICAND_CHI2","CUT_JPSICAND_CHI2",200,0.,20.);
  TH1F* CUT_JPSICAND_L        = new TH1F("CUT_JPSICAND_L","CUT_JPSICAND_L",1000,0.,1.);
  TH1F* CUT_JPSICAND_LOVERSIG = new TH1F("CUT_JPSICAND_LOVERSIG","CUT_JPSICAND_LOVERSIG",21000,0.,7000.);
  TH1F* CUT_DRJPSIJETMIN      = new TH1F("CUT_DRJPSIJETMIN","CUT_DRJPSIJETMIN",100,0.,5.);

  TH1F* MUONS_N           = new TH1F("MUONS_N","MUONS_N",10,0,10.);
  TH1F* MUONS_PT          = new TH1F("MUONS_PT","MUONS_PT",500,0.,500.);   
  TH1F* MUONS_ETA         = new TH1F("MUONS_ETA","MUONS_ETA",60,-3.,3.); 
  TH1F* MUONS_PHI         = new TH1F("MUONS_PHI","MUONS_PHI",64,-3.2,3.2); 
  TH1F* MUONS_PFISO       = new TH1F("MUONS_PFISO","MUONS_PFISO",110,0.,1.1);  

  TH1F* MUONS1_PT         = new TH1F("MUONS1_PT","MUONS1_PT",500,0.,500.);   
  TH1F* MUONS1_ETA        = new TH1F("MUONS1_ETA","MUONS1_ETA",60,-3.,3.); 
  TH1F* MUONS1_PHI        = new TH1F("MUONS1_PHI","MUONS1_PHI",64,-3.2,3.2); 
  TH1F* MUONS1_PFISO      = new TH1F("MUONS1_PFISO","MUONS1_PFISO",110,0.,1.1);  

  TH1F* MUONS2_PT         = new TH1F("MUONS2_PT","MUONS2_PT",500,0.,500.);   
  TH1F* MUONS2_ETA        = new TH1F("MUONS2_ETA","MUONS2_ETA",60,-3.,3.); 
  TH1F* MUONS2_PHI        = new TH1F("MUONS2_PHI","MUONS2_PHI",64,-3.2,3.2); 
  TH1F* MUONS2_PFISO      = new TH1F("MUONS2_PFISO","MUONS2_PFISO",110,0.,1.1);  

  TH1F* GOODJET_N         = new TH1F("GOODJET_N","GOODJET_N",20,0.,20.); 
  TH1F* GOODJET_PT        = new TH1F("GOODJET_PT","GOODJET_PT",1000,0.,500.); 
  TH1F* GOODJET_ETA       = new TH1F("GOODJET_ETA","GOODJET_ETA",100,-5.,5);
  TH1F* GOODJET_PHI       = new TH1F("GOODJET_PHI","GOODJET_PHI",64,-3.2,3.2);
  TH2F* GOODJET_ETAPHI    = new TH2F("GOODJET_ETAPHI","GOODJET_ETAPHI",100,-5.,5,64,-3.2,3.2);
  TH1F* GOODJET_TCHP      = new TH1F("GOODJET_TCHP","GOODJET_TCHP",500,0.,100.);
  TH1F* GOODJET_SSVHE     = new TH1F("GOODJET_SSVHE","GOODJET_SSVHE",100,0.,10.);
  TH1F* GOODJET_NB        = new TH1F("GOODJET_NB","GOODJET_NB",20,0.,20.); 
  TH1F* GOODJET_NBCSVL    = new TH1F("GOODJET_NBCSVL","GOODJET_NBCSVL",20,0.,20.); 
  TH1F* GOODJET_NBCSVM    = new TH1F("GOODJET_NBCSVM","GOODJET_NBCSVM",20,0.,20.); 
  TH1F* GOODJET_NBCSVT    = new TH1F("GOODJET_NBCSVT","GOODJET_NBCSVT",20,0.,20.); 
  TH1F* GOODJET_30_N      = new TH1F("GOODJET_30_N","GOODJET_30_N",20,0.,20.);
  TH1F* GOODJET_40_N      = new TH1F("GOODJET_40_N","GOODJET_40_N",20,0.,20.);
  TH1F* GOODJET_50_N      = new TH1F("GOODJET_50_N","GOODJET_50_N",20,0.,20.);

  TH1F* LEAD1JET_PT       = new TH1F("LEAD1JET_PT","LEAD1JET_PT",1000,0.,500.); 
  TH1F* LEAD1JET_ETA      = new TH1F("LEAD1JET_ETA","LEAD1JET_ETA",100,-5.,5);
  TH1F* LEAD1JET_PHI      = new TH1F("LEAD1JET_PHI","LEAD1JET_PHI",64,-3.2,3.2);

  TH1F* LEAD2JET_PT       = new TH1F("LEAD2JET_PT","LEAD3JET_PT",1000,0.,500.); 
  TH1F* LEAD2JET_ETA      = new TH1F("LEAD2JET_ETA","LEAD3JET_ETA",100,-5.,5);
  TH1F* LEAD2JET_PHI      = new TH1F("LEAD2JET_PHI","LEAD3JET_PHI",64,-3.2,3.2);

  TH1F* LEAD3JET_PT       = new TH1F("LEAD3JET_PT","LEAD3JET_PT",1000,0.,500.); 
  TH1F* LEAD3JET_ETA      = new TH1F("LEAD3JET_ETA","LEAD3JET_ETA",100,-5.,5);
  TH1F* LEAD3JET_PHI      = new TH1F("LEAD3JET_PHI","LEAD3JET_PHI",64,-3.2,3.2);

  TH1F* LEAD4JET_PT       = new TH1F("LEAD4JET_PT","LEAD4JET_PT",1000,0.,500.); 
  TH1F* LEAD4JET_ETA      = new TH1F("LEAD4JET_ETA","LEAD4JET_ETA",100,-5.,5);
  TH1F* LEAD4JET_PHI      = new TH1F("LEAD4JET_PHI","LEAD4JET_PHI",64,-3.2,3.2);

  TH1F* ELECTRONS_N       = new TH1F("ELECTRONS_N","ELECTRONS_N",20,0.,20.); 
  TH1F* ELECTRONS_PT      = new TH1F("ELECTRONS_PT","ELECTRONS_PT",1000,0.,500.); 
  TH1F* ELECTRONS_ETA     = new TH1F("ELECTRONS_ETA","ELECTRONS_ETA",100,-5.,5);
  TH1F* ELECTRONS_PHI     = new TH1F("ELECTRONS_PHI","ELECTRONS_PHI",64,-3.2,3.2);
  TH1F* ELECTRONS_PFISO   = new TH1F("ELECTRONS_PFISO","ELECTRONS_PFISO",110,0.,1.1);  

  TH1F* ELECTRONS1_PT	  = new TH1F("ELECTRONS1_PT","ELECTRONS1_PT",500,0.,500.);   
  TH1F* ELECTRONS1_ETA    = new TH1F("ELECTRONS1_ETA","ELECTRONS1_ETA",60,-3.,3.); 
  TH1F* ELECTRONS1_PHI    = new TH1F("ELECTRONS1_PHI","ELECTRONS1_PHI",64,-3.2,3.2); 
  TH1F* ELECTRONS1_PFISO  = new TH1F("ELECTRONS1_PFISO","ELECTRONS1_PFISO",110,0.,1.1);  

  TH1F* ELECTRONS2_PT	  = new TH1F("ELECTRONS2_PT","ELECTRONS2_PT",500,0.,500.);   
  TH1F* ELECTRONS2_ETA    = new TH1F("ELECTRONS2_ETA","ELECTRONS2_ETA",60,-3.,3.); 
  TH1F* ELECTRONS2_PHI    = new TH1F("ELECTRONS2_PHI","ELECTRONS2_PHI",64,-3.2,3.2); 
  TH1F* ELECTRONS2_PFISO  = new TH1F("ELECTRONS2_PFISO","ELECTRONS2_PFISO",110,0.,1.1);  

  TH1F* MET_MET           = new TH1F("MET_MET","MET_MET",500,0.,500.);
  TH1F* MET_PHI           = new TH1F("MET_PHI","MET_PHI",80,-4.,4.);
  TH1F* WMT               = new TH1F("WMT","WMT",500,0.,500.);

  TH1F* VERTEX_N          = new TH1F("VERTEX_N","VERTEX_N",100,0.,100.);
  TH1F* VERTEX_X          = new TH1F("VERTEX_X","VERTEX_X",1000,-0.5,0.5);
  TH1F* VERTEX_Y          = new TH1F("VERTEX_Y","VERTEX_Y",1000,-0.5,0.5);
  TH1F* VERTEX_Z          = new TH1F("VERTEX_Z","VERTEX_Z",500,-50.,50.);
  TH1F* VERTEX_NDOF       = new TH1F("VERTEX_NDOF","VERTEX_NDOF",500,0.,250.);
  TH1F* VERTEX_CHI2NORM   = new TH1F("VERTEX_CHI2NORM","VERTEX_CHI2NORM",100,0.,20.);
  TH1F* VERTEX_ISFAKE     = new TH1F("VERTEX_ISFAKE","VERTEX_ISFAKE",3,0.,3.);
  TH1F* VERTEX_NTRACKS    = new TH1F("VERTEX_NTRACKS","VERTEX_NTRACKS",250,0.,250.);

  TH1F* VERTEX0_X         = new TH1F("VERTEX0_X","VERTEX0_X",1000,-0.5,0.5);
  TH1F* VERTEX0_Y         = new TH1F("VERTEX0_Y","VERTEX0_Y",1000,-0.5,0.5);
  TH1F* VERTEX0_Z         = new TH1F("VERTEX0_Z","VERTEX0_Z",500,-50.,50.);
  TH1F* VERTEX0_NDOF      = new TH1F("VERTEX0_NDOF","VERTEX0_NDOF",500,0.,250.);
  TH1F* VERTEX0_CHI2NORM  = new TH1F("VERTEX0_CHI2NORM","VERTEX0_CHI2NORM",100,0.,20.);
  TH1F* VERTEX0_ISFAKE    = new TH1F("VERTEX0_ISFAKE","VERTEX0_ISFAKE",3,0.,3.);
  TH1F* VERTEX0_NTRACKS   = new TH1F("VERTEX0_NTRACKS","VERTEX0_NTRACKS",250,0.,250.);

  TH1F* JPSI_N            = new TH1F("JPSI_N","JPSI_N",10,0,10.);
  TH1F* JPSI_M            = new TH1F("JPSI_M","JPSI_M",300,2.8,3.4);
  TH1F* JPSI_PT           = new TH1F("JPSI_PT","JPSI_PT",500,0.,500.);   
  TH1F* JPSI_ETA          = new TH1F("JPSI_ETA","JPSI_ETA",60,-3.,3.); 
  TH1F* JPSI_PHI          = new TH1F("JPSI_PHI","JPSI_PHI",64,-3.2,3.2); 
  TH1F* JPSI_CHI2         = new TH1F("JPSI_CHI2","JPSI_CHI2",200,0.,20.);
  TH1F* JPSI_L            = new TH1F("JPSI_L","JPSI_L",1000,0.,1.);
  TH1F* JPSI_SIGMAL       = new TH1F("JPSI_SIGMAL","JPSI_SIGMAL",5000,0.,0.005);
  TH1F* JPSI_LOVERSIG     = new TH1F("JPSI_LOVERSIG","JPSI_LOVERSIG",21000,0.,7000.);
  TH2F* JPSI_SIGMAL_L     = new TH2F("JPSI_SIGMAL_L","JPSI_SIGMAL_L",5000,0.,0.005,1000,0.,1.);
  TH2F* JPSI_LOVERSIG_L   = new TH2F("JPSI_LOVERSIG_L","JPSI_LOVERSIG_L",14000,0.,7000.,1000,0.,1.);
  TH2F* JPSI_L_PT         = new TH2F("JPSI_L_PT","JPSI_L_PT",1000,0.,1.,500,0.,500.);
  TH2F* JPSI_SIGMAL_PT    = new TH2F("JPSI_SIGMAL_PT","JPSI_SIGMAL_PT",5000,0.,0.005,500,0.,500.); 
  TH2F* JPSI_LOVERSIG_PT  = new TH2F("JPSI_LOVERSIG_PT","JPSI_LOVERSIG_PT",21000,0.,7000.,500,0.,500.);
  TH2F* JPSI_MUDIST_CHI2  = new TH2F("JPSI_MUDIST_CHI2","JPSI_MUDIST_CHI2",300,0.,300.,200,0.,20.);
  TH1F* JPSIJET_FRAC      = new TH1F("JPSIJET_FRAC","JPSIJET_FRAC",220,0.,1.1);

  TH1F* MUJPSI_PT         = new TH1F("MUJPSI_PT","MUJPSI_PT",500,0.,500.);  
  TH1F* MUJPSI_ETA        = new TH1F("MUJPSI_ETA","MUJPSI_ETA",60,-3.,3.); 
  TH1F* MUJPSI_PHI        = new TH1F("MUJPSI_PHI","MUJPSI_PHI",64,-3.2,3.2);
  TH1F* MUJPSI_DIST       = new TH1F("MUJPSI_DIST","MUJPSI_DIST",300,0.,300.);

  TH1F* TOP_PT            = new TH1F("TOP_PT","TOP_PT",250,0.,250.);   

  TH1F* TOP_M_RECO_ALL    = new TH1F("TOP_M_RECO_ALL","TOP_M_RECO_ALL",250,0,250);
  TH1F* DR_JPSI  	= new TH1F("DR_JPSI","DR_JPSI",400,0.,0.2);
  TH1F* DPT_JPSI 	= new TH1F("DPT_JPSI","DPT_JPSI",400,0.,0.2);
  TH2F* DR_DPT_JPSI	= new TH2F("DR_DPT_JPSI","DR_DPT_JPSI",40,0.,0.2,40,0,0.2);
  TH1F* DR_EL		= new TH1F("DR_EL","DR_EL",600,0.,3.);
  TH1F* DPT_EL		= new TH1F("DPT_EL","DPT_EL",600,0.,3.);
  TH2F* DR_DPT_EL	= new TH2F("DR_DPT_EL","DR_DPT_EL",60,0.,3.,60,0,3.);
  TH1F* TOP_M_RECO_GP    = new TH1F("TOP_M_RECO_GP","TOP_M_RECO_GP",250,0,250);
  TH1F* TOP_M_RECO_WP    = new TH1F("TOP_M_RECO_WP","TOP_M_RECO_WP",250,0,250);

  TH1F* DPHIJPSIJETMIN    = new TH1F("DPHIJPSIJETMIN","DPHIJPSIJETMIN",100,0.,5.);
  TH1F* DPHIJPSILEPTON    = new TH1F("DPHIJPSILEPTON","DPHIJPSILEPTON",100,0.,5.);
  TH1F* DRJPSIJETMIN      = new TH1F("DRJPSIJETMIN","DRJPSIJETMIN",100,0.,5.);
  TH1F* DRJPSILEPTON      = new TH1F("DRJPSILEPTON","DRJPSILEPTON",100,0.,5.);

  TH1F* TOPHAD_MASS       = new TH1F("TOPHAD_MASS","TOPHAD_MASS",500,0.,500.);
  TH1F* TOPHAD_WMASS      = new TH1F("TOPHAD_WMASS","TOPHAD_WMASS",500,0.,500.);

  TTree* M_RECO_ALL       = new TTree("M_RECO_ALL","M_RECO_ALL");
  float mass_reco_all, weight_reco_all;
  M_RECO_ALL->Branch("mass", &mass_reco_all, "mass/F");  
  M_RECO_ALL->Branch("weight", &weight_reco_all, "weight/F");  
 
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
    _newmuonsloosetree=muonslooseChain->CloneTree(0);
    _newelectronsloosetree=electronslooseChain->CloneTree(0);
    _newPFparttree=PFpartChain->CloneTree(0);
    
    if (_isMC) {
      _newMCtree=MCChain->CloneTree(0);
    }
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
    nb = GetEntry(jentry);   nbytes += nb;// call rootupledf GetEntry method that do the GetEntry for all 6 trees  and returns muonstree size (bytes)
    
    if (jentry % 1000 == 0) {                        //Display number of events each 10000 events
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
    ICUT->GetXaxis()->SetBinLabel(icut,"Starting");

    //======================================================
    // Trigger
    //======================================================
    
    bool passTrigger = false;

    //double Trigger_weight =1;
    if (!_isMC) {
      for ( unsigned int i=0; i<HLT_vector->size(); ++i){
        TString ThistrigName= (TString) HLT_vector->at(i);
        if ( ThistrigName.Contains("HLT_Ele27_WP80")     )  passTrigger = true;
        }
      }	

    if ( !passTrigger && !_isMC ) continue;  
    ++counter[5];

    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Trigger"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"Trigger");
		
    //================================================================================================
    // PU reweighting
    //================================================================================================

    if (_isMC) {
      int npu = (int) nTrueInteractions;
      if (npu>40) npu = 40;
      WEIGHT = WEIGHT * PUWEIGHT[npu];
      }

    //================================================================================================
    //objects selection 
    //================================================================================================

    vector<int> indgoodmu;
    vector<int> indgoodel;
    vector<int> indgoodver;
    vector<int> indgoodjet;
    vector<int> indgoodjpsi;

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
    
    //======================================================
    // Good muons selection
    //======================================================

    if (_debug) cout <<" -> muons size "<< n_muons << endl;
    
    for (int i=0; i<n_muons; ++i) {

      muPt->push_back(GetP4(muon_4vector,i)->Pt());
      muPz->push_back(GetP4(muon_4vector,i)->Pz());
      muPhi->push_back(GetP4(muon_4vector,i)->Phi());
      muEta->push_back(GetP4(muon_4vector,i)->Eta());
      muOldReliso->push_back((muon_trackIso[i]+muon_ecalIso[i]+muon_hcalIso[i])/muPt->at(i));
      
      //cout<<"scalefactor muon "<<i<<" : "<<muon_scaleFactor->at(i)[0]<<endl;//->at(0);
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
    unsigned int ngoodmuon = indgoodmu.size();
    CUTS_MUONS_N->Fill((float)ngoodmuon,WEIGHT);
    if (ngoodmuon>=1) ++counter[2];

    if (_debug) cout << "Number of good muons = " << ngoodmuon << endl;
  
    //======================================================
    // Good electrons selection
    //======================================================

     if (_debug) std::cout <<" -> electrons size "<< n_electrons << std::endl;

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
    unsigned int ngoodelectron = indgoodel.size();
    CUTS_ELECTRONS_N->Fill((float)ngoodelectron,WEIGHT);
    if (ngoodelectron>=1) ++counter[3];

    if (_debug) cout << "Number of good electrons = " << ngoodelectron << endl;
  
    //======================================================
    // Good leptons selection
    //======================================================

    int ngoodlepton = ngoodelectron + ngoodmuon;
    CUTS_LEPTONS_N->Fill((float)ngoodlepton,WEIGHT);
    if ( ngoodlepton != 1 || ngoodelectron !=1) continue;
    ++counter[1];
    
    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Exactly 1 lepton"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"Exactly 1 lepton");
    
    //================================================================================================
    // Trigger efficiency
    //================================================================================================ 
    
    int triglin = -1;
    if (elPt->at(indgoodel[0])>=30 && elPt->at(indgoodel[0])<31) triglin = 0;
    if (elPt->at(indgoodel[0])>=31 && elPt->at(indgoodel[0])<32) triglin = 1;
    if (elPt->at(indgoodel[0])>=33 && elPt->at(indgoodel[0])<35) triglin = 3;
    if (elPt->at(indgoodel[0])>=32 && elPt->at(indgoodel[0])<33) triglin = 2;
    if (elPt->at(indgoodel[0])>=33 && elPt->at(indgoodel[0])<35) triglin = 3;
    if (elPt->at(indgoodel[0])>=35 && elPt->at(indgoodel[0])<37) triglin = 4;
    if (elPt->at(indgoodel[0])>=37 && elPt->at(indgoodel[0])<39) triglin = 5;
    if (elPt->at(indgoodel[0])>=39 && elPt->at(indgoodel[0])<41) triglin = 6;
    if (elPt->at(indgoodel[0])>=41 && elPt->at(indgoodel[0])<43) triglin = 7;
    if (elPt->at(indgoodel[0])>=43 && elPt->at(indgoodel[0])<45) triglin = 8;
    if (elPt->at(indgoodel[0])>=45 && elPt->at(indgoodel[0])<47) triglin = 9;
    if (elPt->at(indgoodel[0])>=47 && elPt->at(indgoodel[0])<50) triglin = 10;
    if (elPt->at(indgoodel[0])>=50 && elPt->at(indgoodel[0])<55) triglin = 11;
    if (elPt->at(indgoodel[0])>=55 && elPt->at(indgoodel[0])<60) triglin = 12;
    if (elPt->at(indgoodel[0])>=60 && elPt->at(indgoodel[0])<65) triglin = 13;
    if (elPt->at(indgoodel[0])>=65 && elPt->at(indgoodel[0])<70) triglin = 14;
    if (elPt->at(indgoodel[0])>=70 && elPt->at(indgoodel[0])<80) triglin = 15;
    if (elPt->at(indgoodel[0])>=80 && elPt->at(indgoodel[0])<90) triglin = 16;
    if (elPt->at(indgoodel[0])>=90 )  		                 triglin = 17;
    int trigcol = -1;
    if (fabs(elEta->at(indgoodel[0]))<1.5) trigcol = 0;
    if (fabs(elEta->at(indgoodel[0]))>=1.5 && fabs(elEta->at(indgoodel[0]))<2.5) trigcol = 1;

    if ( _isMC && triglin!=-1 &&  trigcol!=-1 ) WEIGHT = WEIGHT * TRIGWEIGHT[triglin][trigcol];  
    
    //======================================================
    // Good jet selection
    //======================================================

     int njet30 = 0;
     int njet40 = 0;
     int njet50 = 0;
     int nbjet  = 0;
     int nbjetcsvl = 0;
     int nbjetcsvm = 0;
     int nbjetcsvt = 0;

     if (_debug) std::cout <<" -> jets size "<< n_jets << std::endl;

     for (int i=0; i<n_jets; ++i) {
       jetPt->push_back(GetP4(jet_4vector,i)->Pt());
       jetPz->push_back(GetP4(jet_4vector,i)->Pz());
       jetPhi->push_back(GetP4(jet_4vector,i)->Phi());
       jetEta->push_back(GetP4(jet_4vector,i)->Eta());
       if (fabs(jetPt->at(i)) < 20)     continue;
       if (fabs(jetEta->at(i)) >  2.4)  continue;

       if ( fabs(jetPt->at(i)) >= 30. ) ++njet30;
       if ( fabs(jetPt->at(i)) >= 40. ) ++njet40;
       if ( fabs(jetPt->at(i)) >= 50. ) ++njet50;
       if ( jet_btag_TCHP[i] >= 3.41 ) ++nbjet;

       if ( jet_btag_CSV[i] > 0.244 ) ++nbjetcsvl;
       if ( jet_btag_CSV[i] > 0.679 ) ++nbjetcsvm;
       if ( jet_btag_CSV[i] > 0.898 ) ++nbjetcsvt;
      
       indgoodjet.push_back(i);
     }
    unsigned int ngoodjet = indgoodjet.size();
    CUTS_GOODJET_N->Fill((float)ngoodjet,WEIGHT);
    CUTS_GOODJET_NB->Fill((float)nbjet,WEIGHT);

    if (_debug) cout << "Number of good jets = " << ngoodjet << endl;
 
    if ( ngoodjet < 4 ) continue;
    //if ( ngoodjet < 3 ) continue;
    //if ( ngoodjet < 2 ) continue;
    //if ( ngoodjet < 1 ) continue;
    //if ( njet40 < 2 ) continue;
    //if ( njet30 < 3 ) continue;

    if ( ngoodjet >= 4 ) {
      if( jetPt->at(indgoodjet[0]) >= 55. && jetPt->at(indgoodjet[1]) >= 45. && jetPt->at(indgoodjet[2]) >= 35. && jetPt->at(indgoodjet[3]) >= 20. ) ++counter[4];
      }
    if( jetPt->at(indgoodjet[0]) < 55. || jetPt->at(indgoodjet[1]) < 45. || jetPt->at(indgoodjet[2]) < 35. || jetPt->at(indgoodjet[3]) < 20. ) continue;

    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "At least 4 jets"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"At least 4 jets");
	
    //======================================================
    // Vertices
    //======================================================

    if (_debug) std::cout <<" -> vertices size "<< n_vertices << std::endl;
    
    for (int i=0; i<n_vertices; ++i) {
      if (vertex_isFake[i]) continue;
      if (vertex_ndof[i] <= 4) continue;   
      indgoodver.push_back(i);
    }
    unsigned int nvtx = indgoodver.size();
    if (_debug) std::cout <<" number of good vertices "<< nvtx << std::endl;
	
    //======================================================
    // MET
    //======================================================
    
    float MET_Pt = 0.;
    float MET_Phi = 0.;
    
    if ( met_4vector->GetSize() == 0 ) { 
      cout << "WARNING : no Met in this event !!!" << endl;
      } else {
	  MET_Pt= GetP4(met_4vector,0)->Pt();
          MET_Phi= GetP4(met_4vector,0)->Phi();
	  }
		
    //======================================================
    // J/psi
    //======================================================

    for(int j=0; j<n_jpsi; ++j ) {

      if ( GetP4(jpsi_4vector,j)->M() >= 3. && GetP4(jpsi_4vector,j)->M() < 3.2 ) {
//    if ( GetP4(jpsi_4vector,j)->M() >= 2.8 && GetP4(jpsi_4vector,j)->M() < 3.4 ) {
	 CUT_JPSICAND_M->Fill(GetP4(jpsi_4vector,j)->M(),WEIGHT);
         indgoodjpsi.push_back(j);
	 }
      }

    if (_debug) cout << " Number of J/Psi candidate = " << n_jpsi << endl;
      
    CUT_JPSICAND_N->Fill((float)indgoodjpsi.size(),WEIGHT);

    if ( indgoodjpsi.size() != 1 ) continue;
    ++counter[6];
    
    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "Exactly 1 J/psi"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"Exactly 1 J/#psi");

    //======================================================
    // J/psi vertex reconstruction
    //======================================================

    float x0 = pf_vx[jpsi_indpf1[0]];
    float y0 = pf_vy[jpsi_indpf1[0]];
    float z0 = pf_vz[jpsi_indpf1[0]];

    float x1 = pf_vx[jpsi_indpf2[0]];
    float y1 = pf_vy[jpsi_indpf2[0]];
    float z1 = pf_vz[jpsi_indpf2[0]];

    TVector3 AB(x1-x0,y1-y0,z1-z0);

    TVector3 v0(GetP4(jpsi_mu1_4vector,0)->Px(),GetP4(jpsi_mu1_4vector,0)->Py(),GetP4(jpsi_mu1_4vector,0)->Pz());
    TVector3 v1(GetP4(jpsi_mu2_4vector,0)->Px(),GetP4(jpsi_mu2_4vector,0)->Py(),GetP4(jpsi_mu2_4vector,0)->Pz());

    TVector3 v0vecv1 = v0.Cross(v1);
    float mp = AB.Dot(v0vecv1);

    float dist = fabs(mp)/v0vecv1.Mag();
    dist = dist * 10000.; // conversion to micrometer
    if ( dist > 100. ) continue;
    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "... with 3D dist(J/psi's daughters)<100 mum"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"... with 3D dist(J/psi's daughters)<100 mum");

    CUT_JPSICAND_CHI2->Fill(jpsi_vtxchi2[indgoodjpsi[0]],WEIGHT);
    if ( jpsi_vtxchi2[indgoodjpsi[0]] > 4 ) continue;
    ++counter[7];
    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "... with chi2<4"; ++icut;
    ICUT->GetXaxis()->SetBinLabel(icut,"... with chi^{2}<4");

    CUT_JPSICAND_L->Fill(jpsi_L3D[indgoodjpsi[0]],WEIGHT);
//    if ( jpsi_vtxchi2[indgoodjpsi[0]] > 0.005 ) continue;
//    ++counter[8];
//    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "... and L>0.005"; ++icut;
//    ICUT->GetXaxis()->SetBinLabel(icut,"... and L>0.005");
        
    CUT_JPSICAND_LOVERSIG->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]],WEIGHT);
//    if ( jpsi_L3DoverSigmaL3D[indgoodjpsi[0]] > 2 ) continue;
//    ++counter[9];
//    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "... and L/sigma>2"; ++icut;
//    ICUT->GetXaxis()->SetBinLabel(icut,"... and L/sigma>2");

    //======================================================
    // J/psi-nearest jet
    //======================================================

    float drmin = 200.;
    for(unsigned int j=0; j<indgoodjet.size(); ++j ) {
      double dRjet = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(jet_4vector,indgoodjet[j])->Eta(),GetP4(jet_4vector,indgoodjet[j])->Phi());
      if ( dRjet < drmin ) drmin = dRjet;
      }
    CUT_DRJPSIJETMIN->Fill(drmin,WEIGHT);
//    if (drmin>0.2) continue;
//    ++counter[10];
//    ICUT->Fill((Double_t)icut,WEIGHT); cutName[icut] = "... and dR J/psi-jet min <0.2"; ++icut;
//    ICUT->GetXaxis()->SetBinLabel(icut,"... and dR J/psi-jet min <0.2");

    //================================================================================================
    // Cuts
    //================================================================================================ 

//  Les coupures sont faites au fur et a mesure...

    //================================================================================================
    // Plots
    //================================================================================================
	
    // jets :
    //-------
    
    for(unsigned int j=0; j<indgoodjet.size(); ++j ) {
      GOODJET_PT->Fill(GetP4(jet_4vector,indgoodjet[j])->Pt(),WEIGHT);
      GOODJET_ETA->Fill(GetP4(jet_4vector,indgoodjet[j])->Eta(),WEIGHT);
      GOODJET_PHI->Fill(GetP4(jet_4vector,indgoodjet[j])->Phi(),WEIGHT);
      GOODJET_ETAPHI->Fill(GetP4(jet_4vector,indgoodjet[j])->Eta(),GetP4(jet_4vector,indgoodjet[j])->Phi(),WEIGHT);
      GOODJET_TCHP->Fill(jet_btag_TCHP[indgoodjet[j]],WEIGHT);
      GOODJET_SSVHE->Fill(jet_btag_CSV[indgoodjet[j]],WEIGHT);
      }
    
    GOODJET_N->Fill((float)ngoodjet,WEIGHT);
    GOODJET_30_N->Fill((float)njet30,WEIGHT);
    GOODJET_40_N->Fill((float)njet40,WEIGHT);
    GOODJET_50_N->Fill((float)njet50,WEIGHT);
    GOODJET_NB->Fill((float)nbjet,WEIGHT);
    GOODJET_NBCSVL->Fill((float)nbjetcsvl,WEIGHT);
    GOODJET_NBCSVM->Fill((float)nbjetcsvm,WEIGHT);
    GOODJET_NBCSVT->Fill((float)nbjetcsvt,WEIGHT);

    if (ngoodjet >= 1 ) {
      LEAD1JET_PT->Fill(GetP4(jet_4vector,indgoodjet[0])->Pt(),WEIGHT);
      LEAD1JET_ETA->Fill(GetP4(jet_4vector,indgoodjet[0])->Eta(),WEIGHT);
      LEAD1JET_PHI->Fill(GetP4(jet_4vector,indgoodjet[0])->Phi(),WEIGHT);
      }
	
    if (ngoodjet >= 2 ) {
      LEAD2JET_PT->Fill(GetP4(jet_4vector,indgoodjet[1])->Pt(),WEIGHT);
      LEAD2JET_ETA->Fill(GetP4(jet_4vector,indgoodjet[1])->Eta(),WEIGHT);
      LEAD2JET_PHI->Fill(GetP4(jet_4vector,indgoodjet[1])->Phi(),WEIGHT);
      }

    if (ngoodjet >= 3 ) {
      LEAD3JET_PT->Fill(GetP4(jet_4vector,indgoodjet[2])->Pt(),WEIGHT);
      LEAD3JET_ETA->Fill(GetP4(jet_4vector,indgoodjet[2])->Eta(),WEIGHT);
      LEAD3JET_PHI->Fill(GetP4(jet_4vector,indgoodjet[2])->Phi(),WEIGHT);
      }

    if (ngoodjet >= 4 ) {
      LEAD4JET_PT->Fill(GetP4(jet_4vector,indgoodjet[3])->Pt(),WEIGHT);
      LEAD4JET_ETA->Fill(GetP4(jet_4vector,indgoodjet[3])->Eta(),WEIGHT);
      LEAD4JET_PHI->Fill(GetP4(jet_4vector,indgoodjet[3])->Phi(),WEIGHT);
      }
      
      // muons :
      //--------
      
      for(unsigned int j=0; j<indgoodmu.size(); ++j ) {
   	MUONS_PT->Fill(GetP4(muon_4vector,indgoodmu[j])->Pt(),WEIGHT);
	MUONS_ETA->Fill(GetP4(muon_4vector,indgoodmu[j])->Eta(),WEIGHT);
	MUONS_PHI->Fill(GetP4(muon_4vector,indgoodmu[j])->Phi(),WEIGHT);
	MUONS_PFISO->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[j]],WEIGHT);

	if ( j == 0 ) {
	  MUONS1_PT->Fill(GetP4(muon_4vector,indgoodmu[j])->Pt(),WEIGHT);
	  MUONS1_ETA->Fill(GetP4(muon_4vector,indgoodmu[j])->Eta(),WEIGHT);
	  MUONS1_PHI->Fill(GetP4(muon_4vector,indgoodmu[j])->Phi(),WEIGHT);
	  MUONS1_PFISO->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[j]],WEIGHT);
	  }
        if ( j == 1 ) {
          MUONS2_PT->Fill(GetP4(muon_4vector,indgoodmu[j])->Pt(),WEIGHT);
	  MUONS2_ETA->Fill(GetP4(muon_4vector,indgoodmu[j])->Eta(),WEIGHT);
	  MUONS2_PHI->Fill(GetP4(muon_4vector,indgoodmu[j])->Phi(),WEIGHT);
	  MUONS2_PFISO->Fill(muon_deltaBetaCorrectedRelIsolation[indgoodmu[j]],WEIGHT);
	  }
        }    
      MUONS_N->Fill((float)ngoodmuon,WEIGHT);    

      // Electrons :
      //------------
      
      for(unsigned int j=0; j<indgoodel.size(); ++j ) {

        ELECTRONS_PT->Fill(GetP4(electron_4vector,indgoodel[j])->Pt(),WEIGHT);
        ELECTRONS_ETA->Fill(GetP4(electron_4vector,indgoodel[j])->Eta(),WEIGHT);
        ELECTRONS_PHI->Fill(GetP4(electron_4vector,indgoodel[j])->Phi(),WEIGHT);
	ELECTRONS_PFISO->Fill(electron_deltaBetaCorrectedRelIsolation[indgoodel[j]],WEIGHT);

	if ( j == 0 ) {
	  ELECTRONS1_PT->Fill(GetP4(electron_4vector,indgoodel[j])->Pt(),WEIGHT);
	  ELECTRONS1_ETA->Fill(GetP4(electron_4vector,indgoodel[j])->Eta(),WEIGHT);
	  ELECTRONS1_PHI->Fill(GetP4(electron_4vector,indgoodel[j])->Phi(),WEIGHT);
	  ELECTRONS1_PFISO->Fill(electron_deltaBetaCorrectedRelIsolation[indgoodel[j]],WEIGHT);
	  }
	if ( j == 1 ) {
	  ELECTRONS2_PT->Fill(GetP4(electron_4vector,indgoodel[j])->Pt(),WEIGHT);
	  ELECTRONS2_ETA->Fill(GetP4(electron_4vector,indgoodel[j])->Eta(),WEIGHT);
	  ELECTRONS2_PHI->Fill(GetP4(electron_4vector,indgoodel[j])->Phi(),WEIGHT);
	  ELECTRONS2_PFISO->Fill(electron_deltaBetaCorrectedRelIsolation[indgoodel[j]],WEIGHT);
	  }
	}
      ELECTRONS_N->Fill((float)ngoodelectron,WEIGHT);

      // MET :
      //------
      
      MET_MET->Fill(MET_Pt,WEIGHT);
      MET_PHI->Fill(MET_Phi,WEIGHT);
      
      double Delta_Phi_el_met=kinem::delta_phi(elPhi->at(indgoodel[0]),MET_Phi);     
      float wmt  = sqrt(2*MET_Pt*elPt->at(indgoodel[0])*( 1-cos(Delta_Phi_el_met) ) );
      WMT->Fill(wmt,WEIGHT);

      // Vertices :
      //-----------
      
      int nvertex = 0;
      
      float distleptvertgood0 = sqrt(pow((electron_vx[indgoodel[0]]-vertex_vx[indgoodver[0]]),2.)+pow((electron_vy[indgoodel[0]]-vertex_vy[indgoodver[0]]),2.)+pow((electron_vz[indgoodel[0]]-vertex_vz[indgoodver[0]]),2.));
      float distleptvertmin = sqrt(pow((electron_vx[indgoodel[0]]-vertex_vx[indgoodver[0]]),2.)+pow((electron_vy[indgoodel[0]]-vertex_vy[indgoodver[0]]),2.)+pow((electron_vz[indgoodel[0]]-vertex_vz[indgoodver[0]]),2.));
      float distleptvertj = sqrt(pow((electron_vx[indgoodel[0]]-vertex_vx[indgoodver[0]]),2.)+pow((electron_vy[indgoodel[0]]-vertex_vy[indgoodver[0]]),2.)+pow((electron_vz[indgoodel[0]]-vertex_vz[indgoodver[0]]),2.));
      float jmin = 0;
      
      for (unsigned int j=0; j<indgoodver.size(); ++j ) {
        if (vertex_isFake[j]) continue;
        if (vertex_ndof[j] <= 4) continue;   
	++nvertex;
	
	distleptvertj = sqrt(pow((electron_vx[indgoodel[0]]-vertex_vx[indgoodver[j]]),2.)+pow((electron_vy[indgoodel[0]]-vertex_vy[indgoodver[j]]),2.)+pow((electron_vz[indgoodel[0]]-vertex_vz[indgoodver[j]]),2.));
	
	if (distleptvertj<distleptvertmin) {
	  distleptvertmin=distleptvertj;
	  jmin=indgoodver[j];
	  }
	  
	if ( j == 0 ) {
	  VERTEX0_X->Fill(vertex_vx[indgoodver[j]],WEIGHT);
	  VERTEX0_Y->Fill(vertex_vy[indgoodver[j]],WEIGHT);
	  VERTEX0_Z->Fill(vertex_vz[indgoodver[j]],WEIGHT);
	  VERTEX0_NDOF->Fill(vertex_ndof[indgoodver[j]],WEIGHT);
	  VERTEX0_CHI2NORM->Fill(vertex_normChi2[indgoodver[j]],WEIGHT);
	  VERTEX0_ISFAKE->Fill((float)vertex_isFake[indgoodver[j]],WEIGHT);
	  VERTEX0_NTRACKS->Fill((float)vertex_ntracks[indgoodver[j]],WEIGHT);
	  } else {
	      VERTEX_X->Fill(vertex_vx[indgoodver[j]],WEIGHT);
	      VERTEX_Y->Fill(vertex_vy[indgoodver[j]],WEIGHT);
	      VERTEX_Z->Fill(vertex_vz[indgoodver[j]],WEIGHT);
	      VERTEX_NDOF->Fill(vertex_ndof[indgoodver[j]],WEIGHT);
	      VERTEX_CHI2NORM->Fill(vertex_normChi2[indgoodver[j]],WEIGHT);
	      VERTEX_ISFAKE->Fill((float)vertex_isFake[indgoodver[j]],WEIGHT);
	      VERTEX_NTRACKS->Fill((float)vertex_ntracks[indgoodver[j]],WEIGHT);
	      }
	  
        }
      VERTEX_N->Fill((float)nvertex,WEIGHT);

      if (indgoodver[0]>0 || jmin>0) {
        cerr << "distleptvertgood0   = " << distleptvertgood0 << endl;
        if (indgoodver[0]>0) {
          cerr << "indgoodver[0]     = " << indgoodver[0] << endl;
	  }
        if (jmin>0) {
	  cerr << "jmin              = " << jmin << endl;
	  cerr << "distleptvertmin   = " << distleptvertmin << endl;
	  }
	}
      
      // Jpsi analysis :
      //----------------
      
      JPSI_N->Fill((float)indgoodjpsi.size(),WEIGHT);     
      JPSI_M->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->M(),WEIGHT);
      JPSI_PT->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(),WEIGHT);
      JPSI_ETA->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),WEIGHT);
      JPSI_PHI->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),WEIGHT);

      MUJPSI_PT->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Pt(),WEIGHT);
      MUJPSI_ETA->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Eta(),WEIGHT);
      MUJPSI_PHI->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Phi(),WEIGHT);

      MUJPSI_PT->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Pt(),WEIGHT);
      MUJPSI_ETA->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Eta(),WEIGHT);
      MUJPSI_PHI->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Phi(),WEIGHT);

      JPSI_L->Fill(jpsi_L3D[indgoodjpsi[0]],WEIGHT);
      JPSI_SIGMAL->Fill(jpsi_sigmaL3D[indgoodjpsi[0]],WEIGHT);
      JPSI_LOVERSIG->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]],WEIGHT);
      JPSI_SIGMAL_L->Fill(jpsi_sigmaL3D[indgoodjpsi[0]],jpsi_L3D[indgoodjpsi[0]],WEIGHT);
      JPSI_LOVERSIG_L->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]],jpsi_L3D[indgoodjpsi[0]],WEIGHT);
      JPSI_L_PT->Fill(jpsi_L3D[indgoodjpsi[0]],GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(),WEIGHT);
      JPSI_SIGMAL_PT->Fill(jpsi_sigmaL3D[indgoodjpsi[0]],GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(),WEIGHT);
      JPSI_LOVERSIG_PT->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]],GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(),WEIGHT);

      JPSI_CHI2->Fill(jpsi_vtxchi2[indgoodjpsi[0]],WEIGHT);
      JPSI_MUDIST_CHI2->Fill(dist,jpsi_vtxchi2[indgoodjpsi[0]],WEIGHT);
      MUJPSI_DIST->Fill(dist,WEIGHT);

      // Top Candidates :
      //-----------------
      
      float px_reco = 0.;
      float py_reco = 0.;
      float pz_reco = 0.;
      float e_reco = 0.;

      px_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Px() + GetP4(electron_4vector,indgoodel[0])->Px();
      py_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Py() + GetP4(electron_4vector,indgoodel[0])->Py();
      pz_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Pz() + GetP4(electron_4vector,indgoodel[0])->Pz();
      e_reco  = GetP4(jpsi_4vector,indgoodjpsi[0])->E()  + GetP4(electron_4vector,indgoodel[0])->E();

      float p_reco  = sqrt(pow(px_reco,2)+pow(py_reco,2)+pow(pz_reco,2));
      float pt_reco = sqrt(pow(px_reco,2)+pow(py_reco,2));
      float m_reco  = pow(e_reco,2)-pow(p_reco,2);
      if ( m_reco >= 0 ) m_reco = sqrt(m_reco);
	else               m_reco = 0.;
	
      TOP_M_RECO_ALL->Fill(m_reco,WEIGHT);
      
      if (_isMC && _isSIG) {
        bool goodpaired = false;
	int indJPsi = 0;
	int indLepton = 0;

	bool JPsiMatched = false;
	double dr_jpsi = 100.;
	double dpt_jpsi = 100.;
	for ( int i=0; i<n_MCs; ++i) {
	  if (MC_type[i]==443){
	    double dr_jpsi_tmp = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),MC_eta[i],MC_phi[i]);
	    double MC_pt = sqrt( MC_px[i] * MC_px[i] + MC_py[i] * MC_py[i] );
	    double dpt_jpsi_tmp = fabs(GetP4(jpsi_4vector,indgoodjpsi[0])->Pt()-MC_pt)/fabs(MC_pt);
	    if (dpt_jpsi_tmp<dpt_jpsi && dr_jpsi_tmp<dr_jpsi) {
	      dr_jpsi = dr_jpsi_tmp;
	      dpt_jpsi = dpt_jpsi_tmp;
	      indJPsi = i;
	      }
	    }
	  }
	DR_JPSI->Fill(dr_jpsi, WEIGHT);  
	DPT_JPSI->Fill(dpt_jpsi, WEIGHT);  
	DR_DPT_JPSI->Fill(dr_jpsi, dpt_jpsi, WEIGHT);
	if (dr_jpsi<0.05) JPsiMatched = true;
	
	bool LeptonMatched = false;
        double dr_l = 100.;
	double dpt_l = 100.;
	for ( int i=0; i<n_MCs; ++i) {
	  if(fabs(MC_type[i])==11){
	    double dr_l_tmp = kinem::delta_R(GetP4(electron_4vector,indgoodel[0])->Eta(),GetP4(electron_4vector,indgoodel[0])->Phi(),MC_eta[i],MC_phi[i]);
	    double MC_pt = sqrt( MC_px[i] * MC_px[i] + MC_py[i] * MC_py[i] );
	    double dpt_l_tmp = fabs(GetP4(electron_4vector,indgoodel[0])->Pt()-MC_pt)/fabs(MC_pt);
	    if (dpt_l_tmp<dpt_l && dr_l_tmp<dr_l) {
	      dr_l = dr_l_tmp;
	      dpt_l = dpt_l_tmp;
	      indLepton = i;
	      }
	    }
	  }  
	DR_EL->Fill(dr_l, WEIGHT);  
	DPT_EL->Fill(dpt_l, WEIGHT);  
	DR_DPT_EL->Fill(dr_l, dpt_l, WEIGHT);
	if (dr_l<0.05) LeptonMatched = true;
	
	if (_debug) {
	  cout << "J/psi... " 
	       << "from top : " << MC_JPsiFromTop[indJPsi]
	       << "... from antitop : " << MC_JPsiFromAntiTop[indJPsi]
	       << endl;
	  cout << "electron... " 
	       << "from top : " << MC_LeptonFromTop[indLepton]
	       << "... from antitop : " << MC_LeptonFromAntiTop[indLepton]
	       << endl;
	  }     
        if ( MC_JPsiFromTop[indJPsi] && MC_LeptonFromTop[indLepton] ) goodpaired = true;
	if ( MC_JPsiFromAntiTop[indJPsi] && MC_LeptonFromAntiTop[indLepton] ) goodpaired = true;
        if (_debug) cout << "good paired : " << goodpaired << endl;

        if (JPsiMatched && LeptonMatched) {
	  ++counter[11];
          if (goodpaired) {
	    TOP_M_RECO_GP->Fill(m_reco,WEIGHT);
            ++counter[12];
	    } else {
	        TOP_M_RECO_WP->Fill(m_reco,WEIGHT);
		++counter[13];
		}
          }  
	}
     
      TOP_PT->Fill(pt_reco,WEIGHT);
      mass_reco_all = m_reco;
      weight_reco_all = WEIGHT;
      M_RECO_ALL->Fill();
      
      // Angular analysis :
      //-------------------
      
      drmin = 200.;
      float dphi = 200.;
      float jpsijetfrac = 0.;
      for(unsigned int j=0; j<indgoodjet.size(); ++j ) {
        double dRjet = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(jet_4vector,indgoodjet[j])->Eta(),GetP4(jet_4vector,indgoodjet[j])->Phi());
	if ( dRjet < drmin ) {
	  drmin = dRjet;
	  dphi = kinem::delta_phi(GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(jet_4vector,indgoodjet[j])->Phi());
	  jpsijetfrac = GetP4(jpsi_4vector,indgoodjpsi[0])->Pt() / GetP4(jet_4vector,indgoodjet[j])->Pt();
          }
	}
      DPHIJPSIJETMIN->Fill(dphi,WEIGHT);
      DRJPSIJETMIN->Fill(drmin,WEIGHT);
      JPSIJET_FRAC->Fill(jpsijetfrac,WEIGHT);
      
      float dR = 0.;
      float dPhi = 0.;
      dR = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(electron_4vector,indgoodel[0])->Eta(),GetP4(electron_4vector,indgoodel[0])->Phi());
      DRJPSILEPTON->Fill(dR,WEIGHT);
      dPhi = kinem::delta_phi(GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(electron_4vector,indgoodel[0])->Phi());
      DPHIJPSILEPTON->Fill(dPhi,WEIGHT);


      // Candidates:    
      if (_debug) {
	cout << "CANDIDATE = " 
	     << currentfile << " : " 
	     << run << ":" 
	     << lumi << ":" 
	     << evtID << endl;
	}
		
      // Top mass reconstruction :
      //--------------------------
      
      std::vector<TLorentzVector> jjcomb;
      std::vector<unsigned int> jjcombind1;
      std::vector<unsigned int> jjcombind2;
      
      for(unsigned int j=0; j<indgoodjet.size(); ++j ) {
	
	if ( jet_btag_CSV[indgoodjet[j]] > 0.679 ) continue;
	TLorentzVector j1(GetP4(jet_4vector,indgoodjet[j])->Px(),GetP4(jet_4vector,indgoodjet[j])->Py(),GetP4(jet_4vector,indgoodjet[j])->Pz(),GetP4(jet_4vector,indgoodjet[j])->E());

	for(unsigned int k=j+1; k<indgoodjet.size(); ++k ) {
	    
	  if ( jet_btag_CSV[indgoodjet[k]] > 0.679 ) continue;
	  TLorentzVector j2(GetP4(jet_4vector,indgoodjet[k])->Px(),GetP4(jet_4vector,indgoodjet[k])->Py(),GetP4(jet_4vector,indgoodjet[k])->Pz(),GetP4(jet_4vector,indgoodjet[k])->E());
	    
	  TLorentzVector jj;
	  jj = j1 + j2;

	  if ( jj.M() > 50. && jj.M() < 110. ) {
	    jjcomb.push_back(jj);
	    jjcombind1.push_back(j);
	    jjcombind2.push_back(k);
	    }

	  }
	}

      if (_debug) cout << " Number of combinations for W->jj = " << jjcomb.size() << endl;
	
      std::vector<TLorentzVector> bjjcomb;
      
      double ptmax = 0.;
      int indbjj = -1;
      int indjj  = -1;
      int indb   = -1;
      
      int counter = 0;
      
      for ( unsigned int i=0; i<jjcomb.size(); ++i) {
      
        for(unsigned int j=0; j<indgoodjet.size(); ++j ) {
	    
	  if ( jet_btag_CSV[indgoodjet[j]] < 0.679 )      continue;
	  if ( j == jjcombind1[i] || j == jjcombind2[i] ) continue;
	    
	  TLorentzVector j3(GetP4(jet_4vector,indgoodjet[j])->Px(),GetP4(jet_4vector,indgoodjet[j])->Py(),GetP4(jet_4vector,indgoodjet[j])->Pz(),GetP4(jet_4vector,indgoodjet[j])->E());
	    
	  TLorentzVector bjj;
	  bjj = jjcomb[i] + j3;
	   
	  bjjcomb.push_back(bjj);
	    
	  if ( bjj.Pt() > ptmax ) {
	    ptmax  = bjj.Pt();
	    indbjj = counter;
	    indjj  = i;
	    indb   = j;
	    }
	    
          if (_debug) cout << " combination : " << jjcombind1[i] << " " << jjcombind2[i] << " " << j << " - Pt = " << bjj.Pt() << " Mjj=" << jjcomb[i].M() << " Mbjj = " << bjj.M() << endl;
	    
	  ++counter;
	  }
	  
	}
	
      if ( indjj >= 0 && indbjj >= 0 ) {
        if (_debug) cout << " Max Pt combination : " << jjcombind1[indjj] << " " << jjcombind2[indjj] << " " << indb << " - Pt = " << bjjcomb[indbjj].Pt() << " Mjj=" << jjcomb[indjj].M() << " Mbjj = " << bjjcomb[indbjj].M() << endl;
	TOPHAD_MASS->Fill(bjjcomb[indbjj].M(),WEIGHT);
	TOPHAD_WMASS->Fill(jjcomb[indjj].M(),WEIGHT);
	}

    //===============================================================================================
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
      _newmuonsloosetree->Fill();
      _newelectronsloosetree->Fill();
      _newPFparttree->Fill();
      if (_isMC) {
        _newMCtree->Fill();
      }
      nwrite++;
    }
    
    ++nselected;
  }
  
  //================================================================================================
  // Delete dynamical objects
  //================================================================================================
  //delete _corrector;

  cout << "======================================================================" << endl;
  for ( Int_t i=0; i<5 ; i++ ){
  cout << "Number of events after cut " << cutName[i] << " : " << ICUT->GetBinContent(i+1) << endl;
  }

  
  cout << "========================================================================" << endl;
  cout << "Total Number of events selected                                 = "  << nselected			   << endl;
  cout << "========================================================================" << endl;
  cout << "Trigger                                                         = " << counter[5] << endl;
  cout << "Exactly 1 lepton                                                = " << counter[1] << endl;
  cout << "-> exactly 1 muon                                               = " << counter[2] << endl;
  cout << "-> exactly 1 electron                                           = " << counter[3] << endl;
  cout << "At least 4 good jets                                            = " << counter[4] << endl;
  cout << "Exactly 1 J/psi                                                 = " << counter[6] << endl;
  cout << "... with 3D dist(J/psi's daughters)<100 mum and chi2<4          = " << counter[7] << endl;
//  cout << "... and L>0.005                                                 = " << counter[8] << endl;
//  cout << "... and L/sigma>2                                               = " << counter[9] << endl;
//  cout << "... and dR J/psi-jet min <0.2                                   = " << counter[10] << endl;
if (_isMC && _isSIG) {
  cout << "========================================================================" << endl;
  cout << "Events matched to MC truth (DeltaR<0.05 for J/psi and lepton)   = " << counter[11] << endl;
  cout << "... good pairing                                                = " << counter[12] << endl;
  cout << "... wrong pairing                                               = " << counter[13] << endl;
  }
  cout << "========================================================================" << endl;
  cout << "Total Number of events skimmed                                  = "  << nwrite			   << endl;
  cout << "========================================================================" << endl;

  _newfile->Write();
  _newfile->Close();

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++
//Analysis FONCTIONS
//+++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

std::vector<double> Thrust_calculate (const std::vector<TLorentzVector>& Input_PtEtaPhiE)
{
  double thrustmax_calc =0;
  double temp_calc =0;
  unsigned int length_thrust_calc =0;
  std::vector<double> ThrustValues;
  std::vector<double> Thrust_Axis_calc;
  std::vector<double> p_thrust_max_calc;
  std::vector<double> p_dec_1_calc;
  std::vector<double> p_dec_2_calc;
  std::vector<double> p_pt_beam_calc;

  if (!ThrustValues.empty()){
    ThrustValues.clear();
    Thrust_Axis_calc.clear();
    p_thrust_max_calc.clear();
    p_dec_1_calc.clear();
    p_dec_2_calc.clear();
    p_pt_beam_calc.clear();
  }

  for(unsigned int j = 0; j < 3; j++){
    p_pt_beam_calc.push_back(0.);
    p_dec_1_calc.push_back(0.);
    p_dec_2_calc.push_back(0.);
    p_thrust_max_calc.push_back(0.);
    Thrust_Axis_calc.push_back(0.);
  }
  
  for(unsigned int j =0;j<4;j++){
    ThrustValues.push_back(0.);
  }
  length_thrust_calc = Input_PtEtaPhiE.size(); 

  double Pt_sum_calc =0;

  for(unsigned int k=0;k<length_thrust_calc;k++){
    Pt_sum_calc+=Input_PtEtaPhiE[k].Pt(); 
    for(unsigned int j = 0; j < 3; j++){
      p_thrust_max_calc[j]=0;
    }
    //get a vector perpendicular to the beam axis and 
    //perpendicular to the momentum of particle k
    //per default beam axis b = (0,0,1)   
    p_pt_beam_calc[0] = Input_PtEtaPhiE[k].Py()*1; 
    p_pt_beam_calc[1] = - Input_PtEtaPhiE[k].Px()*1;
    for(unsigned int i=0;i<length_thrust_calc;i++){
      if(i!=k){
	if((Input_PtEtaPhiE[i].Px()*p_pt_beam_calc[0]+Input_PtEtaPhiE[i].Py()*p_pt_beam_calc[1])>=0){
	  p_thrust_max_calc[0]= p_thrust_max_calc[0]+Input_PtEtaPhiE[i].Px();
	  p_thrust_max_calc[1]= p_thrust_max_calc[1]+Input_PtEtaPhiE[i].Py();
	}
	else{
	  p_thrust_max_calc[0]= p_thrust_max_calc[0]-Input_PtEtaPhiE[i].Px();
	  p_thrust_max_calc[1]= p_thrust_max_calc[1]-Input_PtEtaPhiE[i].Py();
	}
      }
    }
    p_dec_1_calc[0]=p_thrust_max_calc[0]+Input_PtEtaPhiE[k].Px();
    p_dec_1_calc[1]=p_thrust_max_calc[1]+Input_PtEtaPhiE[k].Py();
    p_dec_1_calc[2]=0;
    p_dec_2_calc[0]=p_thrust_max_calc[0]-Input_PtEtaPhiE[k].Px();
    p_dec_2_calc[1]=p_thrust_max_calc[1]-Input_PtEtaPhiE[k].Py();
    p_dec_2_calc[2]=0;
    temp_calc = pow(p_dec_1_calc[0],2)+pow(p_dec_1_calc[1],2);
    if(temp_calc>thrustmax_calc){
      thrustmax_calc =temp_calc;
      for(unsigned int i=0;i<3;i++){
	Thrust_Axis_calc[i]=p_dec_1_calc[i]/sqrt(thrustmax_calc);
      }
    }
    temp_calc = pow(p_dec_2_calc[0],2)+pow(p_dec_2_calc[1],2);
    if(temp_calc>thrustmax_calc){
      thrustmax_calc =temp_calc;
      for(unsigned int i=0;i<3;i++){
	Thrust_Axis_calc[i]=p_dec_2_calc[i]/sqrt(thrustmax_calc);
      }
    }
  }
  for(unsigned int j=0;j<3;j++){
    ThrustValues[j]=Thrust_Axis_calc[j];
  }
  double thrust_calc=0;
  thrust_calc = sqrt(thrustmax_calc)/Pt_sum_calc;

  //the variable which gets resummed is not the thrust
  //but tau=1-thrust
  ThrustValues[3]=1-thrust_calc;
  
  return ThrustValues;
}

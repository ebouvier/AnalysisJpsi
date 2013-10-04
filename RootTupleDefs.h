//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec 17 16:37:15 2012 by ROOT version 5.32/00
// from TTree muon_PF/PAT PF muon info
// found on file: extracted_MuHad_example.root
//////////////////////////////////////////////////////////

#ifndef RootTupleDefs_h
#define RootTupleDefs_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class RootTupleDefs {
public :
   TTree          *muonsChain;   //!pointer to the analyzed TTrees or TChain
   TTree          *electronsChain;
   TTree          *jetsChain;
   TTree          *verticesChain;
   TTree          *METChain;
   TTree          *eventsChain;
   TTree          *HLTChain;
   TTree          *muonslooseChain;   
   TTree          *electronslooseChain;
   TTree          *MCChain;
   TTree          *PFpartChain;

   Int_t           fCurrent; //!current Tree number in a TChain

   // New function to set branch status and adress at the same time

   void SetBranchStatusAndAddress (TTree* _subtree ,const char* _branchname , void* _branchptr ){
     
     _subtree->SetBranchStatus(_branchname,1);
     _subtree->SetBranchAddress(_branchname, _branchptr, NULL);
   }

   // Declaration of leaf types

   //muons leaves
   Int_t           n_muons;
   TClonesArray    *muon_4vector;
   Float_t         muon_vx[100];
   Float_t         muon_vy[100];
   Float_t         muon_vz[100];
   Float_t         muon_d0[100];
   Int_t           muon_charge[100];   
   Float_t         muon_dB[100];   
   Float_t         muon_normChi2[100];     
   Int_t           muon_nValPixelHits[100];   
   Int_t           muon_nMatchedStations[100];   
   Float_t         muon_trackerLayersWithMeasurement[100];   
   Float_t         muon_dZ[100];   
   Float_t         muon_globalTrackNumberOfValidHits[100];   
   Float_t         muon_relIsolation[100];   
   Float_t         muon_deltaBetaCorrectedRelIsolation[100];   
   Float_t         muon_trackIso[100];   
   Float_t         muon_ecalIso[100];   
   Float_t         muon_hcalIso[100];   
   Float_t         muon_pfParticleIso[100];   
   Float_t         muon_pfChargedHadronIso[100];   
   Float_t         muon_pfNeutralHadronIso[100];   
   Float_t         muon_pfPhotonIso[100];   
   Int_t           muon_isGlobal[100];   
   Int_t           muon_isTracker[100];   
   Int_t           muon_nValTrackerHits[100];   
   Int_t           muon_nMatches[100];   
   Float_t         muon_d0error[100];   
   Int_t           muon_mcParticleIndex[100];   
   Float_t         muon_pixelLayerWithMeasurement[100]; 
   std::vector<std::vector<double> > *muon_scaleFactor;

   //electrons leaves
   Int_t           n_electrons;
   TClonesArray    *electron_4vector;
   Float_t         electron_vx[100];  
   Float_t         electron_vy[100];  
   Float_t         electron_vz[100];
   Int_t           electron_charge[100];
   Bool_t          electron_passTightID[100];
   Float_t         electron_rhoCorrectedRelIsolation[100];
   Float_t         electron_SCEta[100];
   Float_t         electron_dB[100];
   Float_t         electron_trackIso[100];
   Float_t         electron_ecalIso[100];
   Float_t         electron_hcalIso[100];
   Float_t         electron_pfParticleIso[100];
   Float_t         electron_pfChargedHadronIso[100];
   Float_t         electron_pfNeutralHadronIso[100];
   Float_t         electron_pfPhotonIso[100];
   Int_t           electron_numberOfMissedInnerLayer[100];
   Int_t           electron_mcParticleIndex[100];
   Float_t         electron_eidMVATrigV0[100];
   Bool_t          electron_passConversionVeto[100];
   Float_t         electron_effectiveArea[100];
   Float_t         electron_relIsolation[100];
   Float_t         electron_deltaBetaCorrectedRelIsolation[100];
   Bool_t          electron_passVetoID[100];
   Bool_t          electron_passLooseID[100];
   Bool_t          electron_passMediumID[100];
   std::vector<std::vector<double> > *electron_scaleFactor;

   //vertices leaves
   Int_t           n_vertices;
   Float_t         vertex_vx[100];   
   Float_t         vertex_vy[100];   
   Float_t         vertex_vz[100];   
   Bool_t          vertex_isFake[100];
   Float_t         vertex_ndof[100];   
   Float_t         vertex_normChi2[100];   
   Int_t           vertex_ntracks[100];

   //event leaves
   UInt_t          evtID;
   UInt_t          time;
   UInt_t          run;
   UInt_t          lumi;
   Float_t         nTrueInteractions;
   
   //jets leaves
   Int_t           n_jets;
   TClonesArray    *jet_4vector;
   Float_t         jet_btag_jetProb[200];
   Float_t         jet_btag_CSV[200];
   Float_t         jet_vx[200];
   Float_t         jet_vy[200];
   Float_t         jet_vz[200];
   Int_t           jet_chmult[200];
   Float_t         jet_chmuEfrac[200];
   Float_t         jet_chemEfrac[200];
   Float_t         jet_chhadEfrac[200];
   Float_t         jet_nemEfrac[200];
   Float_t         jet_nhadEfrac[200];
   Float_t         jet_btag_TCHP[200];
   Int_t           jet_mcParticleIndex[200];
   std::vector<std::vector<double> > *jet_scaleFactor;
   //MET leaves
   TClonesArray    *met_4vector;


   //HLT leaves
   Int_t           n_paths;
   std::vector<std::string>  *HLT_vector;

   //muonsloose leaves
   Int_t           n_muonsloose;
   TClonesArray    *muonloose_4vector;
   Float_t         muonloose_vx[100];
   Float_t         muonloose_vy[100];
   Float_t         muonloose_vz[100];
   Float_t         muonloose_d0[100];
   Int_t           muonloose_charge[100];   
   Float_t         muonloose_dB[100];   
   Float_t         muonloose_normChi2[100];     
   Int_t           muonloose_nValPixelHits[100];   
   Int_t           muonloose_nMatchedStations[100];   
   Float_t         muonloose_trackerLayersWithMeasurement[100];   
   Float_t         muonloose_dZ[100];   
   Float_t         muonloose_globalTrackNumberOfValidHits[100];   
   Float_t         muonloose_relIsolation[100];   
   Float_t         muonloose_deltaBetaCorrectedRelIsolation[100];   
   Float_t         muonloose_trackIso[100];   
   Float_t         muonloose_ecalIso[100];   
   Float_t         muonloose_hcalIso[100];   
   Float_t         muonloose_pfParticleIso[100];   
   Float_t         muonloose_pfChargedHadronIso[100];   
   Float_t         muonloose_pfNeutralHadronIso[100];   
   Float_t         muonloose_pfPhotonIso[100];   
   Int_t           muonloose_isGlobal[100];   
   Int_t           muonloose_isTracker[100];   
   Int_t           muonloose_nValTrackerHits[100];   
   Int_t           muonloose_nMatches[100];   
   Float_t         muonloose_d0error[100];   
   Int_t           muonloose_mcParticleIndex[100];   
   Float_t         muonloose_pixelLayerWithMeasurement[100]; 
   
   //electronsloose leaves
   Int_t           n_electronsloose;
   TClonesArray    *electronloose_4vector;
   Float_t         electronloose_vx[100];  
   Float_t         electronloose_vy[100];  
   Float_t         electronloose_vz[100];
   Int_t           electronloose_charge[100];
   Bool_t          electronloose_passTightID[100];
   Float_t         electronloose_rhoCorrectedRelIsolation[100];
   Float_t         electronloose_SCEta[100];
   Float_t         electronloose_dB[100];
   Float_t         electronloose_trackIso[100];
   Float_t         electronloose_ecalIso[100];
   Float_t         electronloose_hcalIso[100];
   Float_t         electronloose_pfParticleIso[100];
   Float_t         electronloose_pfChargedHadronIso[100];
   Float_t         electronloose_pfNeutralHadronIso[100];
   Float_t         electronloose_pfPhotonIso[100];
   Int_t           electronloose_numberOfMissedInnerLayer[100];
   Int_t           electronloose_mcParticleIndex[100];
   Float_t         electronloose_eidMVATrigV0[100];
   Bool_t          electronloose_passConversionVeto[100];
   Float_t         electronloose_effectiveArea[100];
   Float_t         electronloose_relIsolation[100];
   Float_t         electronloose_deltaBetaCorrectedRelIsolation[100];
   Bool_t          electronloose_passVetoID[100];
   Bool_t          electronloose_passLooseID[100];
   Bool_t          electronloose_passMediumID[100];
  
   // MC leaves
   TClonesArray    *MC_4vector;
   Int_t           n_MCs;
   Int_t           MC_index[200];   
   Int_t           MC_type[200];   
   Int_t           MC_mot1[200];   
   Int_t           MC_mot2[200];   
   Int_t           MC_generation[200];   
   Float_t         MC_e[200];   
   Float_t         MC_px[200];   
   Float_t         MC_py[200];   
   Float_t         MC_pz[200];   
   Float_t         MC_vx[200];   
   Float_t         MC_vy[200];   
   Float_t         MC_vz[200];   
   Float_t         MC_eta[200];   
   Float_t         MC_phi[200];   
   Bool_t          MC_JPsiFromTop[200];
   Bool_t          MC_JPsiFromAntiTop[200];
   Bool_t          MC_LeptonFromTop[200];
   Bool_t          MC_LeptonFromAntiTop[200];

   // PF part leaves
   Int_t           n_pf;
   TClonesArray    *pf_4vector;
   Float_t         pf_vx[50];   //[n_pf]
   Float_t         pf_vy[50];   //[n_pf]
   Float_t         pf_vz[50];   //[n_pf]
   Int_t           pf_charge[50];   //[n_pf]
   Int_t           pf_pdgid[50];   //[n_pf]   
   Int_t           n_jpsi;
   Int_t           jpsi_indpf1[50];
   Int_t           jpsi_indpf2[50];
   TClonesArray    *jpsi_4vector;
   TClonesArray    *jpsimu_4vector;
   TClonesArray    *jpsi_mu1_4vector;
   TClonesArray    *jpsi_mu2_4vector;
   Float_t         jpsi_vx[50];
   Float_t         jpsi_vy[50];
   Float_t         jpsi_vz[50];
   Float_t         jpsi_vtxchi2[50];
   Float_t         jpsi_L3D[50];
   Float_t         jpsi_sigmaL3D[50];
   Float_t         jpsi_L3DoverSigmaL3D[50];

   RootTupleDefs(TTree *_muonstree,TTree *_electronstree,TTree *_jetstree,TTree *_METtree,TTree *_verticestree,TTree *_eventstree,TTree *_HLTtree, TTree *_muonsloosetree,TTree *_electronsloosetree, TTree *_PFparttree, TTree * _MCtree);

   virtual ~RootTupleDefs();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *_muonstree,TTree *_electronstree,TTree *_jetstree,TTree *_METtree,TTree *_verticestree,TTree *_eventstree,TTree *_HLTtree, TTree *_muonsloosetree,TTree *_electronsloosetree, TTree *_PFparttree, TTree *_MCtree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyAna_cxx
RootTupleDefs::RootTupleDefs(TTree *_muonstree,TTree *_electronstree,TTree *_jetstree,TTree *_METtree,TTree *_verticestree,TTree *_eventstree,TTree *_HLTtree, TTree *_muonsloosetree,TTree *_electronsloosetree, TTree *_PFparttree, TTree *_MCtree)
{
// if parameter tree is not specified (or zero), connect the file
// /* used to generate this class and read the Tree. */
/*    if (_muonstree == 0) { */
/*       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("extracted_MuHad_example.root"); */
/*       if (!f || !f->IsOpen()) { */
/*          f = new TFile("extracted_MuHad_example.root"); */
/*       } */
/*       f->GetObject("muon_PF",_muonstree); */
      

/*    } */
   
   ///////////////////////////////////////
   //protéger les autres tree si renvois 0
   ///////////////////////////////////////
   
  Init(_muonstree, _electronstree, _jetstree, _METtree, _verticestree, _eventstree, _HLTtree, _muonsloosetree, _electronsloosetree, _PFparttree, _MCtree );
}

RootTupleDefs::~RootTupleDefs()
{
   if (!muonsChain) return;
   delete muonsChain->GetCurrentFile();//no need to do it for other trees because there is only one file
   
}

Int_t RootTupleDefs::GetEntry(Long64_t entry)
{
// Read contents of entry for all 5 trees
   if (!muonsChain) return 0;
   
   electronsChain->GetEntry(entry);
   jetsChain->GetEntry(entry); 
   verticesChain->GetEntry(entry); 
   METChain->GetEntry(entry);
   eventsChain->GetEntry(entry);
   HLTChain->GetEntry(entry);
   muonslooseChain->GetEntry(entry);
   electronslooseChain->GetEntry(entry);
   PFpartChain->GetEntry(entry);
   if (MCChain != 0) MCChain->GetEntry(entry); //No Mc branch in data files 
   return muonsChain->GetEntry(entry); //return muon tree size to be consistent with the old make class structure 
   
   
}
Long64_t RootTupleDefs::LoadTree(Long64_t entry) //not used in myana
{
// Set the environment to read one entry
   if (!muonsChain) return -5;
   Long64_t centry = muonsChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (muonsChain->GetTreeNumber() != fCurrent) {
      fCurrent = muonsChain->GetTreeNumber();
      Notify();
   }
   return centry;
   

}

void RootTupleDefs::Init(TTree *_muonstree, TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree, TTree *_muonsloosetree, TTree *_electronsloosetree, TTree *_PFparttree, TTree *_MCtree)
{

  muonsChain=NULL;
  electronsChain=NULL;
  jetsChain=NULL;
  verticesChain=NULL;
  METChain=NULL;
  eventsChain=NULL;
  HLTChain=NULL;
  muonslooseChain=NULL;
  electronslooseChain=NULL;
  MCChain=NULL;
  PFpartChain=NULL;

   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer If not initialized to 0 getentry and clone tree crash
   muon_4vector = NULL;
   electron_4vector = NULL;
   jet_4vector = NULL;
   met_4vector = NULL;
   HLT_vector  = NULL;
   muon_scaleFactor=NULL;
   electron_scaleFactor=NULL;
   jet_scaleFactor=NULL;
   muonloose_4vector = NULL;
   electronloose_4vector = NULL;
   MC_4vector =NULL;
   pf_4vector = NULL;
   jpsi_4vector = NULL; 
   jpsimu_4vector = NULL;
   jpsi_mu1_4vector = NULL;
   jpsi_mu2_4vector = NULL;
   // set pointers and branches adresses  for muons 
   if (!_muonstree) return;
   muonsChain = _muonstree;
   fCurrent = -1;
   muonsChain->SetMakeClass(1);

   muonsChain->SetBranchStatus("*",0); //desactivate all muons branches
      
   SetBranchStatusAndAddress(muonsChain, "n_muons", &n_muons);
   SetBranchStatusAndAddress(muonsChain, "muon_vx", &muon_vx);
   SetBranchStatusAndAddress(muonsChain, "muon_vy", &muon_vy);
   SetBranchStatusAndAddress(muonsChain, "muon_vz", &muon_vz);
   SetBranchStatusAndAddress(muonsChain, "muon_d0", &muon_d0);
   SetBranchStatusAndAddress(muonsChain, "muon_4vector", &muon_4vector);
   SetBranchStatusAndAddress(muonsChain, "muon_charge", &muon_charge);
   SetBranchStatusAndAddress(muonsChain, "muon_dB", &muon_dB);
   SetBranchStatusAndAddress(muonsChain, "muon_normChi2",  &muon_normChi2);
   SetBranchStatusAndAddress(muonsChain, "muon_nValPixelHits", &muon_nValPixelHits);
   SetBranchStatusAndAddress(muonsChain, "muon_nMatchedStations", &muon_nMatchedStations);
   SetBranchStatusAndAddress(muonsChain, "muon_trackerLayersWithMeasurement", &muon_trackerLayersWithMeasurement);
   SetBranchStatusAndAddress(muonsChain, "muon_dZ", &muon_dZ);
   SetBranchStatusAndAddress(muonsChain, "muon_globalTrackNumberOfValidHits", &muon_globalTrackNumberOfValidHits);
   SetBranchStatusAndAddress(muonsChain, "muon_relIsolation", &muon_relIsolation);
   SetBranchStatusAndAddress(muonsChain, "muon_deltaBetaCorrectedRelIsolation", &muon_deltaBetaCorrectedRelIsolation);
   SetBranchStatusAndAddress(muonsChain, "muon_trackIso", &muon_trackIso);
   SetBranchStatusAndAddress(muonsChain, "muon_ecalIso", &muon_ecalIso);
   SetBranchStatusAndAddress(muonsChain, "muon_hcalIso", &muon_hcalIso);
   SetBranchStatusAndAddress(muonsChain, "muon_pfParticleIso", &muon_pfParticleIso);
   SetBranchStatusAndAddress(muonsChain, "muon_pfChargedHadronIso", &muon_pfChargedHadronIso);
   SetBranchStatusAndAddress(muonsChain, "muon_pfNeutralHadronIso", &muon_pfNeutralHadronIso);
   SetBranchStatusAndAddress(muonsChain, "muon_pfPhotonIso", &muon_pfPhotonIso);
   SetBranchStatusAndAddress(muonsChain, "muon_isGlobal", &muon_isGlobal);
   SetBranchStatusAndAddress(muonsChain, "muon_isTracker", &muon_isTracker);
   SetBranchStatusAndAddress(muonsChain, "muon_nValTrackerHits", &muon_nValTrackerHits);
   SetBranchStatusAndAddress(muonsChain, "muon_nMatches", &muon_nMatches);
   SetBranchStatusAndAddress(muonsChain, "muon_d0error", &muon_d0error);
   SetBranchStatusAndAddress(muonsChain, "muon_mcParticleIndex", &muon_mcParticleIndex);
   SetBranchStatusAndAddress(muonsChain, "muon_pixelLayerWithMeasurement", &muon_pixelLayerWithMeasurement);
   SetBranchStatusAndAddress(muonsChain, "muon_scaleFactor", &muon_scaleFactor);

   // set pointers and branches adresses  for electrons
 
   if (!_electronstree) return;
   electronsChain = _electronstree;
   fCurrent = -1;
   electronsChain->SetMakeClass(1);

   electronsChain->SetBranchStatus("*",0); //desactivate all electrons branches
    
   SetBranchStatusAndAddress(electronsChain, "n_electrons", &n_electrons); 
   SetBranchStatusAndAddress(electronsChain, "electron_4vector", &electron_4vector);
   SetBranchStatusAndAddress(electronsChain, "electron_charge", &electron_charge);
   SetBranchStatusAndAddress(electronsChain, "electron_passTightID", &electron_passTightID);
   SetBranchStatusAndAddress(electronsChain, "electron_rhoCorrectedRelIsolation", &electron_rhoCorrectedRelIsolation);
   SetBranchStatusAndAddress(electronsChain, "electron_SCEta", &electron_SCEta);
   SetBranchStatusAndAddress(electronsChain, "electron_vx", &electron_vx);
   SetBranchStatusAndAddress(electronsChain, "electron_vy", &electron_vy);
   SetBranchStatusAndAddress(electronsChain, "electron_vz", &electron_vz);
   SetBranchStatusAndAddress(electronsChain, "electron_dB", &electron_dB);
   SetBranchStatusAndAddress(electronsChain, "electron_trackIso", &electron_trackIso);
   SetBranchStatusAndAddress(electronsChain, "electron_ecalIso", &electron_ecalIso);
   SetBranchStatusAndAddress(electronsChain, "electron_hcalIso", &electron_hcalIso);
   SetBranchStatusAndAddress(electronsChain, "electron_pfParticleIso", &electron_pfParticleIso);
   SetBranchStatusAndAddress(electronsChain, "electron_pfChargedHadronIso", &electron_pfChargedHadronIso);
   SetBranchStatusAndAddress(electronsChain, "electron_pfNeutralHadronIso", &electron_pfNeutralHadronIso);
   SetBranchStatusAndAddress(electronsChain, "electron_pfPhotonIso", &electron_pfPhotonIso);
   SetBranchStatusAndAddress(electronsChain, "electron_numberOfMissedInnerLayer", &electron_numberOfMissedInnerLayer);
   SetBranchStatusAndAddress(electronsChain, "electron_mcParticleIndex", &electron_mcParticleIndex);
   SetBranchStatusAndAddress(electronsChain, "electron_eidMVATrigV0", &electron_eidMVATrigV0);
   SetBranchStatusAndAddress(electronsChain, "electron_passConversionVeto", &electron_passConversionVeto);
   SetBranchStatusAndAddress(electronsChain, "electron_effectiveArea", &electron_effectiveArea);
   SetBranchStatusAndAddress(electronsChain, "electron_relIsolation", &electron_relIsolation);
   SetBranchStatusAndAddress(electronsChain, "electron_deltaBetaCorrectedRelIsolation", &electron_deltaBetaCorrectedRelIsolation);
   SetBranchStatusAndAddress(electronsChain, "electron_passVetoID", &electron_passVetoID);
   SetBranchStatusAndAddress(electronsChain, "electron_passLooseID", &electron_passLooseID);
   SetBranchStatusAndAddress(electronsChain, "electron_passMediumID", &electron_passMediumID);
   SetBranchStatusAndAddress(electronsChain, "electron_scaleFactor", &electron_scaleFactor);

   //scbeta
   //template SetBranchStatusAndAddress(muonsChain, "", &);
   
   // set pointers and branches adresses  for vertices
 
   if (!_verticestree) return;
   verticesChain = _verticestree;
   fCurrent = -1;
   verticesChain->SetMakeClass(1);

   verticesChain->SetBranchStatus("*",0); //desactivate all electrons branches

   SetBranchStatusAndAddress(verticesChain, "n_vertices", &n_vertices); 
   SetBranchStatusAndAddress(verticesChain, "vertex_vx", &vertex_vx);
   SetBranchStatusAndAddress(verticesChain, "vertex_vy", &vertex_vy);
   SetBranchStatusAndAddress(verticesChain, "vertex_vz", &vertex_vz);
   SetBranchStatusAndAddress(verticesChain, "vertex_isFake", &vertex_isFake);
   SetBranchStatusAndAddress(verticesChain, "vertex_ndof", &vertex_ndof);
   SetBranchStatusAndAddress(verticesChain, "vertex_normChi2", &vertex_normChi2);
   SetBranchStatusAndAddress(verticesChain, "vertex_ntracks", &vertex_ntracks);
   

   // set pointers and branches adresses  for jets
   //std::cout<<_jetstree<<std::endl;
   if (!_jetstree) return;
   jetsChain = _jetstree;
   fCurrent = -1;
   jetsChain->SetMakeClass(1);

   jetsChain->SetBranchStatus("*",0); //desactivate all jets branches

   SetBranchStatusAndAddress(jetsChain, "n_jets", &n_jets); 
   SetBranchStatusAndAddress(jetsChain, "jet_4vector", &jet_4vector); 
   SetBranchStatusAndAddress(jetsChain, "jet_btag_jetProb", &jet_btag_jetProb); // à changer
   SetBranchStatusAndAddress(jetsChain, "jet_btag_CSV", &jet_btag_CSV); 
   SetBranchStatusAndAddress(jetsChain, "jet_vx", &jet_vx);
   SetBranchStatusAndAddress(jetsChain, "jet_vy", &jet_vy);
   SetBranchStatusAndAddress(jetsChain, "jet_vz", &jet_vz);
   SetBranchStatusAndAddress(jetsChain, "jet_chmult", &jet_chmult);
   SetBranchStatusAndAddress(jetsChain, "jet_chmuEfrac", &jet_chmuEfrac);
   SetBranchStatusAndAddress(jetsChain, "jet_chemEfrac", &jet_chemEfrac);
   SetBranchStatusAndAddress(jetsChain, "jet_chhadEfrac", &jet_chhadEfrac);
   SetBranchStatusAndAddress(jetsChain, "jet_nemEfrac", &jet_nemEfrac);
   SetBranchStatusAndAddress(jetsChain, "jet_nhadEfrac", &jet_nhadEfrac);
   SetBranchStatusAndAddress(jetsChain, "jet_btag_TCHP", &jet_btag_TCHP);
   SetBranchStatusAndAddress(jetsChain, "jet_mcParticleIndex", &jet_mcParticleIndex);
   SetBranchStatusAndAddress(jetsChain, "jet_scaleFactor", &jet_scaleFactor); 
   // set pointers and branches adresses  for MET
 
   if (!_METtree) return;
   METChain = _METtree;
   fCurrent = -1;
   METChain->SetMakeClass(1);

   METChain->SetBranchStatus("*",0); //desactivate all jets branches

   SetBranchStatusAndAddress(METChain, "met_4vector", &met_4vector);
   

   // set pointers and branches adresses  for events
  
   if (!_eventstree) return;
   eventsChain = _eventstree;
   fCurrent = -1;
   eventsChain->SetMakeClass(1);

   eventsChain->SetBranchStatus("*",0); //desactivate all jets branches
   SetBranchStatusAndAddress(eventsChain, "evtID", &evtID);
   SetBranchStatusAndAddress(eventsChain, "time", &time);
   SetBranchStatusAndAddress(eventsChain, "run", &run);
   SetBranchStatusAndAddress(eventsChain, "lumi", &lumi);
   SetBranchStatusAndAddress(eventsChain, "nTrueInteractions", &nTrueInteractions);

   // set pointers and branches adresses  for HLT
   
   if (!_HLTtree) return;
   HLTChain = _HLTtree;
   fCurrent = -1;
   HLTChain->SetMakeClass(1);

   HLTChain->SetBranchStatus("*",0); //desactivate all jets branches

   SetBranchStatusAndAddress(HLTChain, "HLT_vector", &HLT_vector);
   SetBranchStatusAndAddress(HLTChain, "n_paths", &n_paths);



   //set pointers and branches adresses  for muonsloose 
   
   if (!_muonsloosetree) return;
   muonslooseChain = _muonsloosetree;
   fCurrent = -1;
   muonslooseChain->SetMakeClass(1);
   muonslooseChain->SetBranchStatus("*",0); //desactivate all muonsloose branches
      
   SetBranchStatusAndAddress(muonslooseChain, "n_muons", &n_muonsloose); 
   SetBranchStatusAndAddress(muonslooseChain, "muon_vx", &muonloose_vx);
   SetBranchStatusAndAddress(muonslooseChain, "muon_vy", &muonloose_vy);
   SetBranchStatusAndAddress(muonslooseChain, "muon_vz", &muonloose_vz);
   SetBranchStatusAndAddress(muonslooseChain, "muon_d0", &muonloose_d0);
   SetBranchStatusAndAddress(muonslooseChain, "muon_4vector", &muonloose_4vector);
   SetBranchStatusAndAddress(muonslooseChain, "muon_charge", &muonloose_charge);
   SetBranchStatusAndAddress(muonslooseChain, "muon_dB", &muonloose_dB);
   SetBranchStatusAndAddress(muonslooseChain, "muon_normChi2",  &muonloose_normChi2);
   SetBranchStatusAndAddress(muonslooseChain, "muon_nValPixelHits", &muonloose_nValPixelHits);
   SetBranchStatusAndAddress(muonslooseChain, "muon_nMatchedStations", &muonloose_nMatchedStations);
   SetBranchStatusAndAddress(muonslooseChain, "muon_trackerLayersWithMeasurement", &muonloose_trackerLayersWithMeasurement);
   SetBranchStatusAndAddress(muonslooseChain, "muon_dZ", &muonloose_dZ);
   SetBranchStatusAndAddress(muonslooseChain, "muon_globalTrackNumberOfValidHits", &muonloose_globalTrackNumberOfValidHits);
   SetBranchStatusAndAddress(muonslooseChain, "muon_relIsolation", &muonloose_relIsolation);
   SetBranchStatusAndAddress(muonslooseChain, "muon_deltaBetaCorrectedRelIsolation", &muonloose_deltaBetaCorrectedRelIsolation);
   SetBranchStatusAndAddress(muonslooseChain, "muon_trackIso", &muonloose_trackIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_ecalIso", &muonloose_ecalIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_hcalIso", &muonloose_hcalIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_pfParticleIso", &muonloose_pfParticleIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_pfChargedHadronIso", &muonloose_pfChargedHadronIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_pfNeutralHadronIso", &muonloose_pfNeutralHadronIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_pfPhotonIso", &muonloose_pfPhotonIso);
   SetBranchStatusAndAddress(muonslooseChain, "muon_isGlobal", &muonloose_isGlobal);
   SetBranchStatusAndAddress(muonslooseChain, "muon_isTracker", &muonloose_isTracker);
   SetBranchStatusAndAddress(muonslooseChain, "muon_nValTrackerHits", &muonloose_nValTrackerHits);
   SetBranchStatusAndAddress(muonslooseChain, "muon_nMatches", &muonloose_nMatches);
   SetBranchStatusAndAddress(muonslooseChain, "muon_d0error", &muonloose_d0error);
   SetBranchStatusAndAddress(muonslooseChain, "muon_mcParticleIndex", &muonloose_mcParticleIndex);
   SetBranchStatusAndAddress(muonslooseChain, "muon_pixelLayerWithMeasurement", &muonloose_pixelLayerWithMeasurement);
   

   // set pointers and branches adresses  for electrons loose
 

   if (!_electronsloosetree) return;
   electronslooseChain = _electronsloosetree;
   fCurrent = -1;
   electronslooseChain->SetMakeClass(1);

   electronslooseChain->SetBranchStatus("*",0); //desactivate all electronsloose branches
    
   SetBranchStatusAndAddress(electronslooseChain, "n_electrons", &n_electronsloose); 
   SetBranchStatusAndAddress(electronslooseChain, "electron_4vector", &electronloose_4vector);
   SetBranchStatusAndAddress(electronslooseChain, "electron_charge", &electronloose_charge);
   SetBranchStatusAndAddress(electronslooseChain, "electron_passTightID", &electronloose_passTightID);
   SetBranchStatusAndAddress(electronslooseChain, "electron_rhoCorrectedRelIsolation", &electronloose_rhoCorrectedRelIsolation);
   SetBranchStatusAndAddress(electronslooseChain, "electron_SCEta", &electronloose_SCEta);
   SetBranchStatusAndAddress(electronslooseChain, "electron_vx", &electronloose_vx);
   SetBranchStatusAndAddress(electronslooseChain, "electron_vy", &electronloose_vy);
   SetBranchStatusAndAddress(electronslooseChain, "electron_vz", &electronloose_vz);
   SetBranchStatusAndAddress(electronslooseChain, "electron_dB", &electronloose_dB);
   SetBranchStatusAndAddress(electronslooseChain, "electron_trackIso", &electronloose_trackIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_ecalIso", &electronloose_ecalIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_hcalIso", &electronloose_hcalIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_pfParticleIso", &electronloose_pfParticleIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_pfChargedHadronIso", &electronloose_pfChargedHadronIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_pfNeutralHadronIso", &electronloose_pfNeutralHadronIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_pfPhotonIso", &electronloose_pfPhotonIso);
   SetBranchStatusAndAddress(electronslooseChain, "electron_numberOfMissedInnerLayer", &electronloose_numberOfMissedInnerLayer);
   SetBranchStatusAndAddress(electronslooseChain, "electron_mcParticleIndex", &electronloose_mcParticleIndex);
   SetBranchStatusAndAddress(electronslooseChain, "electron_eidMVATrigV0", &electronloose_eidMVATrigV0);
   SetBranchStatusAndAddress(electronslooseChain, "electron_passConversionVeto", &electronloose_passConversionVeto);
   SetBranchStatusAndAddress(electronslooseChain, "electron_effectiveArea", &electronloose_effectiveArea);
   SetBranchStatusAndAddress(electronslooseChain, "electron_relIsolation", &electronloose_relIsolation);
   SetBranchStatusAndAddress(electronslooseChain, "electron_deltaBetaCorrectedRelIsolation", &electronloose_deltaBetaCorrectedRelIsolation);
   SetBranchStatusAndAddress(electronslooseChain, "electron_passVetoID", &electronloose_passVetoID);
   SetBranchStatusAndAddress(electronslooseChain, "electron_passLooseID", &electronloose_passLooseID);
   SetBranchStatusAndAddress(electronslooseChain, "electron_passMediumID", &electronloose_passMediumID);
   


   // set pointers and branches adresses  for MC
   
   //No Mc branch in data files 
   MCChain = _MCtree;
   if (_MCtree != NULL){
     
     fCurrent = -1;
     MCChain->SetMakeClass(1);

     MCChain->SetBranchStatus("*",0); //desactivate all MC branches

     SetBranchStatusAndAddress(MCChain, "n_MCs", &n_MCs);
     SetBranchStatusAndAddress(MCChain, "MC_4vector", &MC_4vector);
     SetBranchStatusAndAddress(MCChain, "MC_index", &MC_index);
     SetBranchStatusAndAddress(MCChain, "MC_type", &MC_type);
     SetBranchStatusAndAddress(MCChain, "MC_mot1", &MC_mot1);
     SetBranchStatusAndAddress(MCChain, "MC_mot2", &MC_mot2);
     SetBranchStatusAndAddress(MCChain, "MC_generation", &MC_generation);
     SetBranchStatusAndAddress(MCChain, "MC_e", &MC_e);
     SetBranchStatusAndAddress(MCChain, "MC_px", &MC_px);
     SetBranchStatusAndAddress(MCChain, "MC_py", &MC_py);
     SetBranchStatusAndAddress(MCChain, "MC_pz", &MC_pz);
     SetBranchStatusAndAddress(MCChain, "MC_vx", &MC_vx);
     SetBranchStatusAndAddress(MCChain, "MC_vy", &MC_vy);
     SetBranchStatusAndAddress(MCChain, "MC_vz", &MC_vz);
     SetBranchStatusAndAddress(MCChain, "MC_eta", &MC_eta);
     SetBranchStatusAndAddress(MCChain, "MC_phi", &MC_phi);
     SetBranchStatusAndAddress(MCChain, "MC_JPsiFromTop", &MC_JPsiFromTop);
     SetBranchStatusAndAddress(MCChain, "MC_JPsiFromAntiTop", &MC_JPsiFromAntiTop);
     SetBranchStatusAndAddress(MCChain, "MC_LeptonFromTop", &MC_LeptonFromTop);
     SetBranchStatusAndAddress(MCChain, "MC_LeptonFromAntiTop", &MC_LeptonFromAntiTop);
   }   

   if (!_PFparttree) return;
   PFpartChain = _PFparttree;
   fCurrent = -1;
   PFpartChain->SetMakeClass(1);

   PFpartChain->SetBranchStatus("*",0); //desactivate all electrons branches
    
   SetBranchStatusAndAddress(PFpartChain, "n_pf", &n_pf); 
   SetBranchStatusAndAddress(PFpartChain, "pf_4vector", &pf_4vector);   
   SetBranchStatusAndAddress(PFpartChain, "pf_vx", &pf_vx);   
   SetBranchStatusAndAddress(PFpartChain, "pf_vy", &pf_vy);   
   SetBranchStatusAndAddress(PFpartChain, "pf_vz", &pf_vz);   
   SetBranchStatusAndAddress(PFpartChain, "pf_charge", &pf_charge);   
   SetBranchStatusAndAddress(PFpartChain, "pf_pdgid", &pf_pdgid);   
   SetBranchStatusAndAddress(PFpartChain, "n_jpsi", &n_jpsi);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_indpf1", &jpsi_indpf1);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_indpf2", &jpsi_indpf2);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_4vector", &jpsi_4vector);
   SetBranchStatusAndAddress(PFpartChain, "jpsimu_4vector", &jpsimu_4vector);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_mu1_4vector", &jpsi_mu1_4vector);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_mu2_4vector", &jpsi_mu2_4vector);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_vx", &jpsi_vx);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_vy", &jpsi_vy);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_vz", &jpsi_vz);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_vtxchi2", &jpsi_vtxchi2);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_L3D", &jpsi_L3D);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_sigmaL3D", &jpsi_sigmaL3D);
   SetBranchStatusAndAddress(PFpartChain, "jpsi_L3DoverSigmaL3D", &jpsi_L3DoverSigmaL3D);

   Notify();
}

Bool_t RootTupleDefs::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void RootTupleDefs::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!muonsChain) return;
   muonsChain->Show(entry);
}
Int_t RootTupleDefs::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RootTupleDefs_cxx

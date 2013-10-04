#define METRES_cxx

#include "MetRes.h"
#include <iostream>
#include <math.h>

using namespace std;

MetRes::MetRes(int nbins, TString title, double metmax)
{
  _nbins = nbins;
  if ( _nbins > nbinsMax ) {
    cout << "MetRes::MetRes - Warning : _nbins > 25" << endl;
    _nbins = nbinsMax;
  }
  
  _title = title;

  cout << "Creating MetRes object with title : " << title.Data() << endl;

  for (int i=0; i<nbins; ++i ) {

    TString titlex = title+"_metx_";
    TString titley = title+"_mety_";
    TString titles = title+"_set_";

    if ( i<10 ) {
      titlex += 0; titlex += i;
      titley += 0; titley += i;
      titles += 0; titles += i;
    } else {
      titlex += i;
      titley += i;
      titles += i;
    }

    _hmetx[i] = new TH1D(titlex.Data(),titlex.Data(),100,-1.*metmax,metmax);
    _hmety[i] = new TH1D(titley.Data(),titley.Data(),100,-1.*metmax,metmax);
    _hset[i]  = new TH1D(titles.Data(),titles.Data(),300,0.,15.);

  }
  
}

MetRes::~MetRes()
{
  //  for (int i=0; i<_nbins; ++i ) {
  //    _hmetx[i]->Delete();
  //    _hmety[i]->Delete();
  //    _hset[i]->Delete();
  //  }
}

void MetRes::Fill(const double& metx, const double& mety, const double& set, const double& weight)
{
  double sqrtset = sqrt(set);
  
  int binNumber = (int)(sqrtset*2); //pour associer un nombre de bin avec une plage de SET
 
  if ( binNumber < 0 ) cout << "MetRes::Fill() - Warning : binNumber < 0" << endl; //securite supplementaire
      if ( binNumber > _nbins-1 ) binNumber = _nbins-1;  //remplis les histos du dernier bin avec ts l'overflow 

  //  cout << binNumber << " " << sqrtset << endl;

  _hmetx[binNumber]->Fill(metx,weight);    //remplis ts les histos associes au bon bin
  _hmety[binNumber]->Fill(mety,weight);
  _hset[binNumber]->Fill(sqrtset,weight);
  
}


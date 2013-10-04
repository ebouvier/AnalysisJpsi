#ifndef METRES_h
#define METRES_h

#include <TH2.h>
#include <TString.h>

const int nbinsMax = 25;

class MetRes
{
 public:

  MetRes(int nbins, TString title, double metmax = 100.);
  ~MetRes();

  void Fill(const double& metx, const double& mety, const double& set, const double& weight=1.);

 private:
  int _nbins;
  TString _title;
  TH1D* _hmetx[nbinsMax];
  TH1D* _hmety[nbinsMax];
  TH1D* _hset[nbinsMax];
};

#endif

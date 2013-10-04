#include <string>
#include <TH1.h>
#include <map>

enum class PUProfile : uint8_t {
  S6,
  S7,
  S10
};

enum class Systematic : uint8_t {
  NOMINAL,
  UP,
  DOWN
};

class PUReweighter {
  public:
  PUReweighter(bool isSemiMu, std::string _dataFilename="SingleMu_tot_MyDataPileupHistogram_corr69300_fine.root", PUProfile profile = PUProfile::S10, Systematic syst = Systematic::NOMINAL);

    ~PUReweighter() {
      delete puHisto;
    }

    double weight(float interactions) const;

  private:
    void initPUProfiles();

    TH1* puHisto;

    std::map<PUProfile, std::vector<double>> mPUCoefs;
};


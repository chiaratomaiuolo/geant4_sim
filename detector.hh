#ifndef DETECTOR_HH
#define DETECTOR_HH

#include <vector>
#include <algorithm>

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"


//static vectors for saving electron IDs
static std::vector<G4int> RingElectronID;
static std::vector<G4int> ArmElectronID;
static std::vector<G4int> ElectronID;

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
private:
    virtual G4bool ProcessHits(G4Step *,G4TouchableHistory *);
};

#endif
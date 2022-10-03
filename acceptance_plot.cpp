#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
#include <set>
#include <iostream>

void acceptance_plot()
{
    std::set<Char_t*> Volumes;
    TFile *file = new TFile("Screening_datas_gaussian.root", "read");
    TTree *Hits = (TTree*) file->Get("PhotonHits");
    
    Hits->Draw("PhotonHitVolume>>photon_histo");
    TH1F *photon_histo = (TH1F*) gDirectory->Get("photon_histo");
    for(int i=0; i<photon_histo->GetNbinsX(); i++)
    {
        std::cout<<photon_histo->GetBinContent(i+1)<<std::endl;
    }


    photon_histo->SetTitle("Hits of primary photons on target volumes; Volume; occurrencies");
    photon_histo->SetName("hit photons");
    photon_histo->Draw();


}
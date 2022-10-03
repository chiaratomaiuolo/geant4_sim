#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
#include <set>
#include <iostream>

void root_macro()
{
    std::set<Char_t*> Volumes;
    TFile *file = new TFile("output.root", "read");
    TTree *el_energies = (TTree*) file->Get("elEnergySpectra");
    TTree *pos_energies = (TTree*) file->Get("posEnergySpectra");
    
    el_energies->Draw("ElectronEnergies>>el_histo");
    TH1F *el_histo = (TH1F*) gDirectory->Get("el_histo");

    pos_energies->Draw("PositronEnergies>>pos_histo");
    TH1F *pos_histo = (TH1F*) gDirectory->Get("pos_histo");

    TLegend *legend = new TLegend(0.65, 0.7, 0.85, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(el_histo, "electrons", "E");
    legend->AddEntry(pos_histo, "positrons", "E");


    el_histo->SetTitle("Energy spectra of e+ and e- exiting the geometry; E[MeV]; occurrencies");
    el_histo->SetName("electrons histo");
    pos_histo->SetName("positrons histo");
    el_histo->SetLineColor(4);
    pos_histo->SetLineColor(2);
    el_histo->Draw();
    pos_histo->Draw("sames");

    //gStyle->SetOptStat(0111);
    legend->Draw();

}
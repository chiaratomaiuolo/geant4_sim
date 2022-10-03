#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
#include <set>
#include <iostream>

void momentum_plot()
{
    //Taking TTrees from .root file
    std::set<Char_t*> Volumes;
    TFile *file = new TFile("upstream_datas.root", "read");
    TTree *upstream_electrons = (TTree*) file->Get("UpstreamElectrons");

    //DECLARATION OF HISTOGRAMS
    //Compton histograms
    TH1F* PX_Compton_histo = new TH1F("PX_Compton_histo","PX_Compton_histo",200,0.,19.);
    TH1F* PX_EPC_histo = new TH1F("PX_EPC_histo","PX_EPC_histo",200,0.,19.);
    TH1F* PY_histo = new TH1F("PY_Compton_histo","PY_Compton_histo",200,0.,19.);
    TH1F* PZ_histo = new TH1F("PZ_Compton_histo","PZ_Compton_histo",200,0.,19.);

    //Filling histograms with data
    upstream_electrons->Draw("UpstreamElectronExitPZ>>PX_Compton_histo(200,-18.,18.)","UpstreamElectronProcesses==\"compt\"");
    PX_Compton_histo = (TH1F*) gDirectory->Get("PX_Compton_histo");
    upstream_electrons->Draw("UpstreamElectronExitPZ>>PX_EPC_histo(200,-18.,18.)","UpstreamElectronProcesses==\"conv\"");
    PX_EPC_histo = (TH1F*) gDirectory->Get("PX_EPC_histo");
    

    
    
    TLegend *legend = new TLegend(0.65, 0.7, 0.85, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(22);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(PX_Compton_histo, "Compton electrons", "E");
    legend->AddEntry(PX_EPC_histo, "EPC electrons", "E");
    

    PX_EPC_histo->SetTitle("PZ spectrum for upstream e-; Pz[MeV/c**2]; occurrencies");
    PX_EPC_histo->SetLineColor(2);
    PX_EPC_histo->Draw();
    PX_Compton_histo->SetLineColor(4);
    PX_Compton_histo->Draw("sames");

    //gStyle->SetOptStat(0111);
    legend->Draw();

}
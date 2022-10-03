#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
#include <set>
#include <iostream>

void plot_macro()
{
    std::set<Char_t*> Volumes;
    TFile *file = new TFile("energy_spectra_data.root", "read");
    //TTree containing the energy spectrum of all the electrons
    TTree *el_energies = (TTree*) file->Get("elEnergySpectra");
    //TTree containing the energy spectrum of all the positrons
    TTree *pos_energies = (TTree*) file->Get("posEnergySpectra");
    //TTree containing the energy spectrum of Compton electrons
    TTree *Compton_energies = (TTree*) file->Get("ComptonEnergySpectrum");
    //TTree containing the energy spectrum of Conv electrons
    TTree *Conv_energies = (TTree*) file->Get("ConvEnergySpectrum");
    //TTree containing the energy spectrum of Ionization electrons
    TTree *Ionization_energies = (TTree*) file->Get("IonizationEnergySpectrum");
    //TTree containing the energy spectrum of Photoelectric electrons
    TTree *Photoelectric_energies = (TTree*) file->Get("PhotoelectricEnergySpectrum");
    
    TH1F* el_histo = new TH1F("all_e-spectrum","e-spectrum",200,0.,19.);
    TH1F* pos_histo = new TH1F("all_e+spectrum","all_e+spectrum",200,0.,19.);
    TH1F* Compton_histo = new TH1F("Compton_spectrum","Compton_spectrum",200,0.,19.);
    TH1F* Ionization_histo = new TH1F("Ionization_spectrum","Ionization_spectrum",200,0.,19.);
    TH1F* Photoelectric_histo = new TH1F("Photoelectric_spectrum","Photoelectric_spectrum",200,0.,19.);
    TH1F* Conv_histo = new TH1F("conv_spectrum","conv_spectrum",200,0.,19.);
    TH1F* summed_histo = new TH1F("summed_spectrum","summed_spectrum",200,0.,19.);


    el_energies->Draw("ElectronEnergies>>el_histo(200,0.,19.)");
    el_histo = (TH1F*) gDirectory->Get("el_histo");

    pos_energies->Draw("PositronEnergies>>pos_histo(200,0.,19.)");
    pos_histo = (TH1F*) gDirectory->Get("pos_histo");

    Compton_energies->Draw("ComptonElectronEnergies>>Compton_histo(200,0.,19.)");
    Compton_histo = (TH1F*) gDirectory->Get("Compton_histo");

    Ionization_energies->Draw("IonizationElectronEnergies>>Ionization_histo(200,0.,19.)");
    Ionization_histo = (TH1F*) gDirectory->Get("Ionization_histo");

    Conv_energies->Draw("ConvElectronEnergies>>Conv_histo(200,0.,19.)");
    Conv_histo = (TH1F*) gDirectory->Get("Conv_histo");

    Photoelectric_energies->Draw("PhotoelectricElectronEnergies>>Photoelectric_histo(200,0.,19.)");
    Photoelectric_histo = (TH1F*) gDirectory->Get("Photoelectric_histo");

    el_energies->Draw("ElectronEnergies>>summed_histo(200,0.,19.)");
    summed_histo = (TH1F*) gDirectory->Get("summed_histo");
    *summed_histo = *summed_histo-(*Compton_histo + *Ionization_histo);



    TLegend *legend = new TLegend(0.65, 0.7, 0.85, 0.85, "", "NDC nb");
    legend->SetBorderSize(0.);
    legend->SetTextFont(42);
    legend->SetTextSizePixels(17);
    legend->SetFillColorAlpha(0,0.0);
    legend->AddEntry(el_histo, "all electrons", "E");
    //legend->AddEntry(Compton_histo, "Compton electrons", "E");
    //legend->AddEntry(Ionization_histo, "Ionization electrons", "E");
    //legend->AddEntry(Conv_histo, "EPC electrons", "E");
    //legend->AddEntry(Photoelectric_histo, "Photoelectric electrons", "E");
    legend->AddEntry(summed_histo,"electrons without Compton and ionization", "E");
    legend->AddEntry(pos_histo, "positrons", "E");
    

    //el_histo->SetTitle("Energy spectrum of e- e+ exiting the geometry; E[MeV]; occurrencies");
    el_histo->SetTitle("Energy spectra of e- e+ exiting the geometry; E[MeV]; occurrencies");
    el_histo->SetLineColor(1);
    el_histo->SetName("All electrons (no production cuts)");
    Compton_histo->SetName("Compton e-");
    Compton_histo->SetLineColor(2);
    Ionization_histo->SetName("Ionization e-");
    Ionization_histo->SetLineColor(3);
    Conv_histo->SetName("EPC e-");
    Conv_histo->SetLineColor(4);
    Photoelectric_histo->SetName("Photoelectric e-");
    Photoelectric_histo->SetLineColor(6);
    summed_histo->SetName("e- without Compton and ionization");
    summed_histo->SetLineColor(4);
    pos_histo->SetName("e+ histo");
    pos_histo->SetLineColor(2);
    el_histo->Draw();
    pos_histo->Draw("sames");
    summed_histo->Draw("sames");

    //Compton_histo->Draw("sames");
    //Ionization_histo->Draw("sames");
    //Conv_histo->Draw("sames");
    //Photoelectric_histo->Draw("sames");

    //gStyle->SetOptStat(0111);
    legend->Draw();

}
#define t_cxx
#include "t.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void t::Loop()
{
//   In a ROOT session, you can do:
//      root> .L t.C
//      root> t t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // Opt1
   //My_Cut_Values cut_SR1 = set_threshold(0.943, 0.800, 480., 800.);
   //My_Cut_Values cut_SR2 = set_threshold(0.960, 0.800, 630., 1150.);
   //My_Cut_Values cut_SR3 = set_threshold(0.950, 0.800, 750., 1350.);

   // Opt2
   My_Cut_Values cut_SR1 = set_threshold(0.943, 0.800, 480., 800.);
   My_Cut_Values cut_SR2 = set_threshold(0.960, 0.800, 550., 1150.);
   My_Cut_Values cut_SR3 = set_threshold(0.950, 0.800, 650., 1600.);

   int counter_SR1 = 0;
   int counter_SR2 = 0;
   int counter_SR3 = 0;

   double yields_SR1 = 0;
   double yields_SR2 = 0;
   double yields_SR3 = 0;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (Cut(ientry, cut_SR1, BDTG_TprimeVsNonHiggs_M600_M700  , BDTG_TprimeVsHiggs_M600_M700)   > 0){ counter_SR1 += 1; yields_SR1 += weight; }
      if (Cut(ientry, cut_SR2, BDTG_TprimeVsNonHiggs_M800_M1000 , BDTG_TprimeVsHiggs_M800_M1000)  > 0){ counter_SR2 += 1; yields_SR2 += weight; }
      if (Cut(ientry, cut_SR3, BDTG_TprimeVsNonHiggs_M1100_M1200, BDTG_TprimeVsHiggs_M1100_M1200) > 0){ counter_SR3 += 1; yields_SR3 += weight; }
      
   }

   printf("counter_SR1 = %d, yields_SR1 = %.5f\n", counter_SR1, yields_SR1);
   printf("counter_SR2 = %d, yields_SR2 = %.5f\n", counter_SR2, yields_SR2);
   printf("counter_SR3 = %d, yields_SR3 = %.5f\n", counter_SR3, yields_SR3);
}

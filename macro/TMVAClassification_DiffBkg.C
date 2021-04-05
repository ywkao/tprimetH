#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification_DiffBkg( TString myMethodList = "", int year=2 )
{
    TMVA::Tools::Instance();
    // Default MVA methods to be trained + tested{{{
    std::map<std::string,int> Use;
 
    // Cut optimisation
    Use["Cuts"]            = 0;
    Use["CutsD"]           = 0;
    Use["CutsPCA"]         = 0;
    Use["CutsGA"]          = 0;
    Use["CutsSA"]          = 0;
    //
    // 1-dimensional likelihood ("naive Bayes estimator")
    Use["Likelihood"]      = 0;
    Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
    Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
    Use["LikelihoodKDE"]   = 0;
    Use["LikelihoodMIX"]   = 0;
    //
    // Mutidimensional likelihood and Nearest-Neighbour methods
    Use["PDERS"]           = 0;
    Use["PDERSD"]          = 0;
    Use["PDERSPCA"]        = 0;
    Use["PDEFoam"]         = 0;
    Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
    Use["KNN"]             = 0; // k-nearest neighbour method
    //
    // Linear Discriminant Analysis
    Use["LD"]              = 0; // Linear Discriminant identical to Fisher
    Use["Fisher"]          = 0;
    Use["FisherG"]         = 0;
    Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
    Use["HMatrix"]         = 0;
    //
    // Function Discriminant analysis
    Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
    Use["FDA_SA"]          = 0;
    Use["FDA_MC"]          = 0;
    Use["FDA_MT"]          = 0;
    Use["FDA_GAMT"]        = 0;
    Use["FDA_MCMT"]        = 0;
    //
    // Neural Networks (all are feed-forward Multilayer Perceptrons)
    Use["MLP"]             = 0; // Recommended ANN
    Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
    Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
    Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
    Use["TMlpANN"]         = 0; // ROOT's own ANN
    Use["DNN_GPU"]         = 0; // CUDA-accelerated DNN training.
    Use["DNN_CPU"]         = 0; // Multi-core accelerated DNN.
    //
    // Support Vector Machine
    Use["SVM"]             = 0;
    //
    // Boosted Decision Trees
    Use["BDT"]             = 1; // uses Adaptive Boost
    Use["BDTG"]            = 0; // uses Gradient Boost
    Use["BDTB"]            = 0; // uses Bagging
    Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
    Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
    //
    // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
    Use["RuleFit"]         = 0;
    // ---------------------------------------------------------------
    //}}}
    std::cout << std::endl; std::cout << "==> Start TMVAClassification" << std::endl;
    // Select methods (don't look at this code - not of interest) {{{
    if (myMethodList != "") {
       for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
 
       std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
       for (UInt_t i=0; i<mlist.size(); i++) {
          std::string regMethod(mlist[i]);
 
          if (Use.find(regMethod) == Use.end()) {
             std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
             for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
             std::cout << std::endl;
             return 1;
          }
          Use[regMethod] = 1;
       }
    }//}}}
    TMVA::DataLoader *dataloader=new TMVA::DataLoader(Form("dataset_Run%i_Tprime1100_1200VsHiggs",year));
    // TFiles, year, xsec{{{
    TFile *input_thq_16;
    TFile *input_thq_17;
    TFile *input_thq_18;
    
    TFile *input_tth_16;   
    TFile *input_tth_17;
    TFile *input_tth_18;
 
    TFile *input_vh_16;
    TFile *input_vh_17;
    TFile *input_vh_18;
 
    TFile *input_Tprime600_16;
    TFile *input_Tprime625_16;
    TFile *input_Tprime650_16;
    TFile *input_Tprime675_16;
    TFile *input_Tprime700_16;
    TFile *input_Tprime800_16;
    TFile *input_Tprime900_16;
    TFile *input_Tprime1000_16;
    TFile *input_Tprime1100_16;
    TFile *input_Tprime1200_16;
 
    TFile *input_Tprime600_17;
    TFile *input_Tprime625_17;
    TFile *input_Tprime650_17;
    TFile *input_Tprime675_17;
    TFile *input_Tprime700_17;
    TFile *input_Tprime800_17;
    TFile *input_Tprime900_17;
    TFile *input_Tprime1000_17;
    TFile *input_Tprime1100_17;
    TFile *input_Tprime1200_17;
 
    TFile *input_Tprime600_18;
    TFile *input_Tprime625_18;
    TFile *input_Tprime650_18;
    TFile *input_Tprime675_18;
    TFile *input_Tprime700_18;
    TFile *input_Tprime800_18;
    TFile *input_Tprime900_18;
    TFile *input_Tprime1000_18;
    TFile *input_Tprime1100_18;
    TFile *input_Tprime1200_18;
 
    TFile *input_ttgg_16;
    TFile *input_ttgjets_16;
    TFile *input_DiPhotonJetsBox_16;
    TFile *input_DiPhotonJetsBox2BJets_16;
    TFile *input_gjets_16;
    TFile *input_TTJets_16;
    TFile *input_TGJets_16;
    TFile *input_ZG_16;
    TFile *input_WG_16;
    TFile *input_TTWJets_16;
    TFile *input_DYJets_16;
 
    TFile *input_ttgg_17;
    TFile *input_ttgjets_17;
    TFile *input_DiPhotonJetsBox_17;
    TFile *input_DiPhotonJetsBox2BJets_17;
    TFile *input_gjets_17;
    TFile *input_TTJets_17;
    TFile *input_TGJets_17;
    TFile *input_ZG_17;
    TFile *input_WG_17;
    TFile *input_TTWJets_17;
    TFile *input_DYJets_17;
 
    TFile *input_ttgg_18;
    TFile *input_ttgjets_18;
    TFile *input_DiPhotonJetsBox_18;
    TFile *input_DiPhotonJetsBox2BJets_18;
    TFile *input_gjets_18;
    TFile *input_TTJets_18;
    TFile *input_TGJets_18;
    TFile *input_ZG_18;
    TFile *input_WG_18;
    TFile *input_TTWJets_18;
    TFile *input_DYJets_18;

    bool run2016=false, run2017=false, run2018=false;
    if(year==2016) run2016=true;
    else if (year==2017) run2017=true;
    else if (year==2018) run2018=true;
    else {run2016=true; run2017=true; run2018=true;}
 
    TCut mycuts;
    TCut mycutb;
    TString file_path;
 
    float Tprime600_xs  = 0.07399;
    float Tprime625_xs  = 0.06981;
    float Tprime650_xs  = 0.06640;
    float Tprime675_xs  = 0.06282;
    float Tprime700_xs  = 0.05981;
    float Tprime800_xs  = 0.04764;
    float Tprime900_xs  = 0.03809;
    float Tprime1000_xs = 0.03044;
    float Tprime1100_xs = 0.02464;
    float Tprime1200_xs = 0.01993;
    //}}}

    cout<<"Year----------------------------------------->"<<year<<endl;
    if(run2016){ //{{{
        file_path="/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/2016/";
    
        input_Tprime600_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-600_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime625_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-625_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime650_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-650_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime675_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-675_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime700_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime800_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime900_16                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-900_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"       );
        input_Tprime1000_16                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"      );
        input_Tprime1100_16                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1100_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"      );
        input_Tprime1200_16                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1200_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"      );
        input_thq_16                         = TFile::Open(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_TuneCUETP8M1_v2.root"            );
        input_tth_16                         = TFile::Open(file_path + "output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                      );
        input_vh_16                          = TFile::Open(file_path + "output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                          );
        input_ttgg_16                        = TFile::Open(file_path + "output_TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root"                  );
        input_ttgjets_16                     = TFile::Open(file_path + "output_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root"                 );
        input_DiPhotonJetsBox_16             = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root"                                );
        input_DiPhotonJetsBox2BJets_16       = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root"                          );
        input_gjets_16                       = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root" );
        input_TTJets_16                      = TFile::Open(file_path + "output_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root"                        );
        input_TGJets_16                      = TFile::Open(file_path + "output_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root"                      );
        input_ZG_16                          = TFile::Open(file_path + "ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root"                                );
        input_WG_16                          = TFile::Open(file_path + "output_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root"                        );
        input_TTWJets_16                     = TFile::Open(file_path + "output_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root"            );
        input_DYJets_16                      = TFile::Open(file_path + "output_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root"                 );

        TTree *signalTree600_16              = (TTree*)input_Tprime600_16             -> Get("tagsDumper/trees/Tprime_600_13TeV_THQLeptonicTag"              );
        TTree *signalTree625_16              = (TTree*)input_Tprime625_16             -> Get("tagsDumper/trees/Tprime_625_13TeV_THQLeptonicTag"              );
        TTree *signalTree650_16              = (TTree*)input_Tprime650_16             -> Get("tagsDumper/trees/Tprime_650_13TeV_THQLeptonicTag"              );
        TTree *signalTree675_16              = (TTree*)input_Tprime675_16             -> Get("tagsDumper/trees/Tprime_675_13TeV_THQLeptonicTag"              );
        TTree *signalTree700_16              = (TTree*)input_Tprime700_16             -> Get("tagsDumper/trees/Tprime_700_13TeV_THQLeptonicTag"              );
        TTree *signalTree800_16              = (TTree*)input_Tprime800_16             -> Get("tagsDumper/trees/Tprime_800_13TeV_THQLeptonicTag"              );
        TTree *signalTree900_16              = (TTree*)input_Tprime900_16             -> Get("tagsDumper/trees/Tprime_900_13TeV_THQLeptonicTag"              );
        TTree *signalTree1000_16             = (TTree*)input_Tprime1000_16            -> Get("tagsDumper/trees/Tprime_1000_13TeV_THQLeptonicTag"             );
        TTree *signalTree1100_16             = (TTree*)input_Tprime1100_16            -> Get("tagsDumper/trees/Tprime_1100_13TeV_THQLeptonicTag"             );
        TTree *signalTree1200_16             = (TTree*)input_Tprime1200_16            -> Get("tagsDumper/trees/Tprime_1200_13TeV_THQLeptonicTag"             );
        TTree *tree_thq_16                   = (TTree*)input_thq_16                   -> Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag"                 );
        TTree *tree_tth_16                   = (TTree*)input_tth_16                   -> Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag"                 );
        TTree *tree_ttgg_16                  = (TTree*)input_ttgg_16                  -> Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag"                    );
        TTree *tree_ttgjets_16               = (TTree*)input_ttgjets_16               -> Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag"                 );
        TTree *tree_DiPhotonJetsBox_16       = (TTree*)input_DiPhotonJetsBox_16       -> Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag"         );
        TTree *tree_DiPhotonJetsBox2BJets_16 = (TTree*)input_DiPhotonJetsBox2BJets_16 -> Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag"   );
        TTree *tree_gjets_16                 = (TTree*)input_gjets_16                 -> Get("tagsDumper/trees/gjets_13TeV_THQLeptonicTag"                   );
        TTree *tree_TGJets_16                = (TTree*)input_TGJets_16                -> Get("tagsDumper/trees/tgjets_13TeV_THQLeptonicTag"                  );
        TTree *tree_TTJets_16                = (TTree*)input_TTJets_16                -> Get("tagsDumper/trees/ttjets_13TeV_THQLeptonicTag"                  );
        TTree *tree_ZG_16                    = (TTree*)input_ZG_16                    -> Get("tagsDumper/trees/ZG_13TeV_THQLeptonicTag"                      );
        TTree *tree_WG_16                    = (TTree*)input_WG_16                    -> Get("tagsDumper/trees/WG_13TeV_THQLeptonicTag"                      );
        TTree *tree_TTWJets_16               = (TTree*)input_TTWJets_16               -> Get("tagsDumper/trees/ttwjets_13TeV_THQLeptonicTag"                 );
        TTree *tree_DYJets_16                = (TTree*)input_DYJets_16                -> Get("tagsDumper/trees/DYJets_13TeV_THQLeptonicTag"                  );
        TTree *tree_VH_16                    = (TTree*)input_vh_16                    -> Get("tagsDumper/trees/vh_125_13TeV_THQLeptonicTag"                  );
    
        std::cout << "--- TMVAClassification       : Using input file: " << input_thq_16->GetName() << std::endl;
    
        double sig_eqvW_16 = 1/35.9;
        dataloader->AddSignalTree( signalTree1100_16, sig_eqvW_16/Tprime1100_xs);
        dataloader->AddSignalTree( signalTree1200_16, sig_eqvW_16/Tprime1200_xs);
        dataloader->AddBackgroundTree(tree_thq_16, sig_eqvW_16);
        dataloader->AddBackgroundTree(tree_tth_16, sig_eqvW_16);
        dataloader->AddBackgroundTree(tree_VH_16, sig_eqvW_16);
    
        mycuts ="weight>0 && lepton_leadPt>10";	
        mycutb ="weight>0 && lepton_leadPt>10";
    } // end of 2016 //}}}
    if(run2017){ //{{{
        file_path="/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/2017/";
        input_Tprime600_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-600_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime625_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-625_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime650_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-650_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime675_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-675_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime700_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime800_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime900_17                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-900_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime1000_17                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_Tprime1100_17                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1100_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_Tprime1200_17                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1200_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_thq_17                         = TFile::Open(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root"                          );
        input_tth_17                         = TFile::Open(file_path + "output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                    );
        input_vh_17                          = TFile::Open(file_path + "output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                        );
        input_ttgg_17                        = TFile::Open(file_path + "output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root"                     );
        input_ttgjets_17                     = TFile::Open(file_path + "output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root"                    );
        input_DiPhotonJetsBox_17             = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root"                              );
        input_DiPhotonJetsBox2BJets_17       = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root"                        );
        input_gjets_17                       = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"    );
        input_TTJets_17                      = TFile::Open(file_path + "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                                    );
        input_TGJets_17                      = TFile::Open(file_path + "output_TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root"                         );
        input_ZG_17                          = TFile::Open(file_path + "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                            );
        input_WG_17                          = TFile::Open(file_path + "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                           );
        input_TTWJets_17                     = TFile::Open(file_path + "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root"                      );
        input_DYJets_17                      = TFile::Open(file_path + "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                           );

        TTree *signalTree600_17              = (TTree*)input_Tprime600_17             -> Get("tagsDumper/trees/Tprime_600_13TeV_THQLeptonicTag"            );
        TTree *signalTree625_17              = (TTree*)input_Tprime625_17             -> Get("tagsDumper/trees/Tprime_625_13TeV_THQLeptonicTag"            );
        TTree *signalTree650_17              = (TTree*)input_Tprime650_17             -> Get("tagsDumper/trees/Tprime_650_13TeV_THQLeptonicTag"            );
        TTree *signalTree675_17              = (TTree*)input_Tprime675_17             -> Get("tagsDumper/trees/Tprime_675_13TeV_THQLeptonicTag"            );
        TTree *signalTree700_17              = (TTree*)input_Tprime700_17             -> Get("tagsDumper/trees/Tprime_700_13TeV_THQLeptonicTag"            );
        TTree *signalTree800_17              = (TTree*)input_Tprime800_17             -> Get("tagsDumper/trees/Tprime_800_13TeV_THQLeptonicTag"            );
        TTree *signalTree900_17              = (TTree*)input_Tprime900_17             -> Get("tagsDumper/trees/Tprime_900_13TeV_THQLeptonicTag"            );
        TTree *signalTree1000_17             = (TTree*)input_Tprime1000_17            -> Get("tagsDumper/trees/Tprime_1000_13TeV_THQLeptonicTag"           );
        TTree *signalTree1100_17             = (TTree*)input_Tprime1100_17            -> Get("tagsDumper/trees/Tprime_1100_13TeV_THQLeptonicTag"           );
        TTree *signalTree1200_17             = (TTree*)input_Tprime1200_17            -> Get("tagsDumper/trees/Tprime_1200_13TeV_THQLeptonicTag"           );
        TTree *tree_thq_17                   = (TTree*)input_thq_17                   -> Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag"               );
        TTree *tree_tth_17                   = (TTree*)input_tth_17                   -> Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag"               );
        TTree *tree_vh_17                    = (TTree*)input_vh_17                    -> Get("tagsDumper/trees/wzh_125_13TeV_THQLeptonicTag"               );
        TTree *tree_ttgg_17                  = (TTree*)input_ttgg_17                  -> Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag"                  );
        TTree *tree_ttgjets_17               = (TTree*)input_ttgjets_17               -> Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag"               );
        TTree *tree_DiPhotonJetsBox_17       = (TTree*)input_DiPhotonJetsBox_17       -> Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag"       );
        TTree *tree_DiPhotonJetsBox2BJets_17 = (TTree*)input_DiPhotonJetsBox2BJets_17 -> Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag" );
        TTree *tree_gjets_17                 = (TTree*)input_gjets_17                 -> Get("tagsDumper/trees/gjets_13TeV_THQLeptonicTag"                 );
        TTree *tree_TGJets_17                = (TTree*)input_TGJets_17                -> Get("tagsDumper/trees/tgjets_13TeV_THQLeptonicTag"                );
        TTree *tree_TTJets_17                = (TTree*)input_TTJets_17                -> Get("tagsDumper/trees/ttjets_13TeV_THQLeptonicTag"                );
        TTree *tree_ZG_17                    = (TTree*)input_ZG_17                    -> Get("tagsDumper/trees/ZG_13TeV_THQLeptonicTag"                    );
        TTree *tree_WG_17                    = (TTree*)input_WG_17                    -> Get("tagsDumper/trees/WG_13TeV_THQLeptonicTag"                    );
        TTree *tree_TTWJets_17               = (TTree*)input_TTWJets_17               -> Get("tagsDumper/trees/ttwjets_13TeV_THQLeptonicTag"               );
        TTree *tree_DYJets_17                = (TTree*)input_DYJets_17                -> Get("tagsDumper/trees/DYJets_13TeV_THQLeptonicTag"                );
    
    
        std::cout << "--- TMVAClassification       : Using input file: " << input_thq_17->GetName() << std::endl;
    
        double sig_eqvW_17 = 1/41.5;
        dataloader->AddSignalTree( signalTree1100_17, sig_eqvW_17/Tprime1100_xs);
        dataloader->AddSignalTree( signalTree1200_17, sig_eqvW_17/Tprime1200_xs);
        dataloader->AddBackgroundTree(tree_thq_17, sig_eqvW_17);
        dataloader->AddBackgroundTree(tree_tth_17, sig_eqvW_17);
        dataloader->AddBackgroundTree(tree_vh_17, sig_eqvW_17);
    
        mycuts ="weight>0 && lepton_leadPt>10";
        mycutb ="weight>0 && lepton_leadPt>10";
    } // end of 2017 //}}}
    if(run2018){ //{{{
        file_path="/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/2018/";
        input_Tprime600_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-600_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime625_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-625_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime650_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-650_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime675_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-675_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime700_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime800_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime900_18                   = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-900_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"     );
        input_Tprime1000_18                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_Tprime1100_18                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1100_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_Tprime1200_18                  = TFile::Open(file_path + "output_TprimeBToTH_Hgg_M-1200_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root"    );
        input_thq_18                         = TFile::Open(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root"                          );
        input_tth_18                         = TFile::Open(file_path + "output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                    );
        input_vh_18                          = TFile::Open(file_path + "output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root"                        );
        input_ttgg_18                        = TFile::Open(file_path + "output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root"                     );
        input_ttgjets_18                     = TFile::Open(file_path + "output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root"                    );
        input_DiPhotonJetsBox_18             = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root"                              );
        input_DiPhotonJetsBox2BJets_18       = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root"                        );
        input_gjets_18                       = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"    );
        input_TTJets_18                      = TFile::Open(file_path + "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                                    );
        input_TGJets_18                      = TFile::Open(file_path + "output_TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root"                         );
        input_ZG_18                          = TFile::Open(file_path + "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                            );
        input_WG_18                          = TFile::Open(file_path + "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                           );
        input_TTWJets_18                     = TFile::Open(file_path + "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root"                      );
        input_DYJets_18                      = TFile::Open(file_path + "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root"                           );

        TTree *signalTree600_18              = (TTree*)input_Tprime600_18             -> Get("tagsDumper/trees/Tprime_600_13TeV_THQLeptonicTag"            );
        TTree *signalTree625_18              = (TTree*)input_Tprime625_18             -> Get("tagsDumper/trees/Tprime_625_13TeV_THQLeptonicTag"            );
        TTree *signalTree650_18              = (TTree*)input_Tprime650_18             -> Get("tagsDumper/trees/Tprime_650_13TeV_THQLeptonicTag"            );
        TTree *signalTree675_18              = (TTree*)input_Tprime675_18             -> Get("tagsDumper/trees/Tprime_675_13TeV_THQLeptonicTag"            );
        TTree *signalTree700_18              = (TTree*)input_Tprime700_18             -> Get("tagsDumper/trees/Tprime_700_13TeV_THQLeptonicTag"            );
        TTree *signalTree800_18              = (TTree*)input_Tprime800_18             -> Get("tagsDumper/trees/Tprime_800_13TeV_THQLeptonicTag"            );
        TTree *signalTree900_18              = (TTree*)input_Tprime900_18             -> Get("tagsDumper/trees/Tprime_900_13TeV_THQLeptonicTag"            );
        TTree *signalTree1000_18             = (TTree*)input_Tprime1000_18            -> Get("tagsDumper/trees/Tprime_1000_13TeV_THQLeptonicTag"           );
        TTree *signalTree1100_18             = (TTree*)input_Tprime1100_18            -> Get("tagsDumper/trees/Tprime_1100_13TeV_THQLeptonicTag"           );
        TTree *signalTree1200_18             = (TTree*)input_Tprime1200_18            -> Get("tagsDumper/trees/Tprime_1200_13TeV_THQLeptonicTag"           );
        TTree *tree_thq_18                   = (TTree*)input_thq_18                   -> Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag"               );
        TTree *tree_tth_18                   = (TTree*)input_tth_18                   -> Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag"               );
        TTree *tree_vh_18                    = (TTree*)input_vh_18                    -> Get("tagsDumper/trees/vh_125_13TeV_THQLeptonicTag"                );
        TTree *tree_ttgg_18                  = (TTree*)input_ttgg_18                  -> Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag"                  );
        TTree *tree_ttgjets_18               = (TTree*)input_ttgjets_18               -> Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag"               );
        TTree *tree_DiPhotonJetsBox_18       = (TTree*)input_DiPhotonJetsBox_18       -> Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag"       );
        TTree *tree_DiPhotonJetsBox2BJets_18 = (TTree*)input_DiPhotonJetsBox2BJets_18 -> Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag" );
        TTree *tree_gjets_18                 = (TTree*)input_gjets_18                 -> Get("tagsDumper/trees/gjets_13TeV_THQLeptonicTag"                 );
        TTree *tree_TGJets_18                = (TTree*)input_TGJets_18                -> Get("tagsDumper/trees/tgjets_13TeV_THQLeptonicTag"                );
        TTree *tree_TTJets_18                = (TTree*)input_TTJets_18                -> Get("tagsDumper/trees/ttjets_13TeV_THQLeptonicTag"                );
        TTree *tree_ZG_18                    = (TTree*)input_ZG_18                    -> Get("tagsDumper/trees/ZG_13TeV_THQLeptonicTag"                    );
        TTree *tree_WG_18                    = (TTree*)input_WG_18                    -> Get("tagsDumper/trees/WG_13TeV_THQLeptonicTag"                    );
        TTree *tree_TTWJets_18               = (TTree*)input_TTWJets_18               -> Get("tagsDumper/trees/ttwjets_13TeV_THQLeptonicTag"               );
        TTree *tree_DYJets_18                = (TTree*)input_DYJets_18                -> Get("tagsDumper/trees/DYJets_13TeV_THQLeptonicTag"                );
       
        std::cout << "--- TMVAClassification       : Using input file: " << input_thq_18->GetName() << std::endl;
    
        double sig_eqvW_18 = 1/59.5;
        dataloader->AddSignalTree( signalTree1100_18, sig_eqvW_18/Tprime1100_xs);
        dataloader->AddSignalTree( signalTree1200_18, sig_eqvW_18/Tprime1200_xs);
        dataloader->AddBackgroundTree(tree_thq_18, sig_eqvW_18);
        dataloader->AddBackgroundTree(tree_tth_18, sig_eqvW_18);
        dataloader->AddBackgroundTree(tree_vh_18, sig_eqvW_18);
    
        mycuts ="weight>0 && lepton_leadPt>10";
        mycutb ="weight>0 && lepton_leadPt>10";
    } // end of 2018 //}}}

    // output file{{{
    // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
    TString outfileName( Form("TMVA_Run%i_Tprime1100_1200VsHiggs.root", year) );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I,P,G:AnalysisType=Classification" );
    //}}}
    // Add variables, set weight, prepare training and test trees{{{
    dataloader->AddVariable( "dipho_leadPtOvermass    := dipho_leadPt/dipho_mass"                                                                , 'F' );
    dataloader->AddVariable( "dipho_subleadPtOvermass := dipho_subleadPt/dipho_mass"                                                             , 'F' );
    dataloader->AddVariable( "ScalarTPtOverAllPt      := (solvedMET_pt + dipho_pt + lepton_leadPt + bjet1_pt)/(HT + recoMET_pt + lepton_leadPt)" , 'F' );
    dataloader->AddVariable( "dipho_leadEta"              , "dipho_leadEta"              , "units" , 'F' );
    dataloader->AddVariable( "dipho_subleadEta"           , "dipho_subleadEta"           , "units" , 'F' );
    dataloader->AddVariable( "dipho_leadIDMVA"            , "dipho_leadIDMVA"            , "units" , 'F' );
    dataloader->AddVariable( "dipho_subleadIDMVA"         , "dipho_subleadIDMVA"         , "units" , 'F' );
    dataloader->AddVariable( "dipho_lead_haspixelseed"    , "dipho_lead_haspixelseed"    , "units" , 'F' );
    dataloader->AddVariable( "dipho_sublead_haspixelseed" , "dipho_sublead_haspixelseed" , "units" , 'F' );
    dataloader->AddVariable( "n_jets"                     , "n_jets"                     , "units" , 'F' );
    dataloader->AddVariable( "n_bjets"                    , "n_bjets"                    , "units" , 'F' );
    dataloader->AddVariable( "n_centraljets"              , "n_centraljets"              , "units" , 'F' );
    dataloader->AddVariable( "lepton_charge"              , "lepton_charge"              , "units" , 'F' );
    dataloader->AddVariable( "lepton_leadPt"              , "lepton_leadPt"              , "units" , 'F' );
    dataloader->AddVariable( "lepton_leadEta"             , "lepton_leadEta"             , "units" , 'F' );
    dataloader->AddVariable( "fwdjet1_pt"                 , "fwdjet1_pt"                 , "units" , 'F' );
    dataloader->AddVariable( "fwdjet1_discr"              , "fwdjet1_discr"              , "units" , 'F' );
    dataloader->AddVariable( "dr_tHchainfwdjet"           , "dRtHchainfwdjet"            , "units" , 'F' );
    dataloader->AddVariable( "dr_leptonbjet"              , "dRleptonbjet"               , "units" , 'F' );
    dataloader->AddVariable( "dr_leptonfwdjet"            , "dRleptonfwdjet"             , "units" , 'F' );
    dataloader->AddVariable( "dr_bjetfwdjet"              , "dr_bjetfwdjet"              , "units" , 'F' );
    dataloader->AddVariable( "dr_leadphofwdjet"           , "dRleadphofwdjet"            , "units" , 'F' );
    dataloader->AddVariable( "dr_subleadphofwdjet"        , "dRsubleadphofwdjet"         , "units" , 'F' );
    dataloader->AddVariable( "bjet1_pt"                   , "bjet1_pt"                   , "units" , 'F' );
    dataloader->AddVariable( "bjet1_eta"                  , "bjet1_eta"                  , "units" , 'F' );
    dataloader->AddVariable( "bjet1_discr"                , "bjet1_discr"                , "units" , 'F' );
    dataloader->AddVariable( "jet1_pt"                    , "jet1_pt"                    , "units" , 'F' );
    dataloader->AddVariable( "jet2_pt"                    , "jet2_pt"                    , "units" , 'F' );
    dataloader->AddVariable( "jet1_eta"                   , "jet1_eta"                   , "units" , 'F' );
    dataloader->AddVariable( "jet2_eta"                   , "jet2_eta"                   , "units" , 'F' );
    dataloader->AddVariable( "jet1_discr"                 , "jet1_discr"                 , "units" , 'F' );
    dataloader->AddVariable( "jet2_discr"                 , "jet2_discr"                 , "units" , 'F' );
    dataloader->AddVariable( "recoMET_pt"                 , "recoMET_pt"                 , "units" , 'F' );

    dataloader->SetSignalWeightExpression( "137*weight" );
    dataloader->SetBackgroundWeightExpression( "137*weight" );

    dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                         "nTrain_Signal=0:nTrain_Background=0:SplitMode=Alternate:NormMode=NumEvents:!V" );
    //}}}
    //BookMethod{{{
    // Cut optimisation
    if (Use["Cuts"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
 
    if (Use["CutsD"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );
 
    if (Use["CutsPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                            "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );
 
    if (Use["CutsGA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                            "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );
 
    if (Use["CutsSA"])
       factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                            "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
 
    // Likelihood ("naive Bayes estimator")
    if (Use["Likelihood"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                            "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
 
    // Decorrelated likelihood
    if (Use["LikelihoodD"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                            "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
 
    // PCA-transformed likelihood
    if (Use["LikelihoodPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                            "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );
    // Use a kernel density estimator to approximate the PDFs
    if (Use["LikelihoodKDE"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                            "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );
 
    // Use a variable-dependent mix of splines and kernel density estimator
    if (Use["LikelihoodMIX"])
       factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                            "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" );
 
    if (Use["PDERS"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
                            "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
 
    if (Use["PDERSD"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );
 
    if (Use["PDERSPCA"])
       factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                            "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );
 
    // Multi-dimensional likelihood estimator using self-adapting phase-space binning
    if (Use["PDEFoam"])
       factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                            "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );
 
    if (Use["PDEFoamBoost"])
       factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                            "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );
 
    // K-Nearest Neighbour classifier (KNN)
    if (Use["KNN"])
       factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
                            "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
 
    // H-Matrix (chi2-squared) method
    if (Use["HMatrix"])
       factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
 
    // Linear discriminant (same as Fisher discriminant)
    if (Use["LD"])
       factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
 
    // Fisher discriminant (same as LD)
    if (Use["Fisher"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
 
    // Fisher with Gauss-transformed input variables
    if (Use["FisherG"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
 
    // Composite classifier: ensemble (tree) of boosted Fisher classifiers
    if (Use["BoostedFisher"])
       factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
 			"H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );                           
    // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
    if (Use["FDA_MC"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );
 
    if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );
 
    if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
 
    if (Use["FDA_MT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );
 
    if (Use["FDA_GAMT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );
 
    if (Use["FDA_MCMT"])
       factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                            "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );
 
    // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
    if (Use["MLP"])
       factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
 
    if (Use["MLPBFGS"])
       factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
 
    if (Use["MLPBNN"])
       factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
 
 
    // Multi-architecture DNN implementation.
    if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
       // General layout.
       TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");
 
       // Training strategies.
       TString training0("LearningRate=1e-1,Momentum=0.9,Repetitions=1,"
                         "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=L2,"
                         "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
       TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                         "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=L2,"
                         "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
       TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                         "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                         "WeightDecay=1e-4,Regularization=L2,"
                         "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
       TString trainingStrategyString ("TrainingStrategy=");
       trainingStrategyString += training0 + "|" + training1 + "|" + training2;
 
       // General Options.
       TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                           "WeightInitialization=XAVIERUNIFORM");
       dnnOptions.Append (":"); dnnOptions.Append (layoutString);
       dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);
 
       // Cuda implementation.
       if (Use["DNN_GPU"]) {
          TString gpuOptions = dnnOptions + ":Architecture=GPU";
          factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_GPU", gpuOptions);
       }
       // Multi-core CPU implementation.
       if (Use["DNN_CPU"]) {
          TString cpuOptions = dnnOptions + ":Architecture=CPU";
          factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);
       }
    }
 
    // CF(Clermont-Ferrand)ANN
    if (Use["CFMlpANN"])
       factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...
 
    // Tmlp(Root)ANN
    if (Use["TMlpANN"])
       factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
 
    // Support Vector Machine
    if (Use["SVM"])
       factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
 
    // Boosted Decision Trees
    if (Use["BDTG"]) // Gradient Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                            "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
 
    if (Use["BDT"])  // Adaptive Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                            "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
 
    if (Use["BDTB"]) // Bagging
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                            "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
 
    if (Use["BDTD"]) // Decorrelation + Adaptive Boost
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                            "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );
 
    if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
       factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                            "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );
 
    // RuleFit -- TMVA implementation of Friedman's method
    if (Use["RuleFit"])
       factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
                            "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
    //}}}

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    // close{{{
    outputFile->Close();
    std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
    std::cout << "==> TMVAClassification is done!" << std::endl;

    delete factory;
    delete dataloader;
    if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );
    return 0;
    //}}}
}

// main function{{{
int main( int argc, char** argv )
{
    // Select methods (don't look at this code - not of interest)
    TString methodList;
    int year;
    for (int i=1; i<argc; i++) {
       TString regMethod(argv[i]);
       if(regMethod=="-b" || regMethod=="--batch") continue;
       if (!methodList.IsNull()) methodList += TString(",");
       methodList += regMethod;
    }
    return TMVAClassification_DiffBkg(methodList, year);
}
//}}}

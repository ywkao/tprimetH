#include "tprimetHHadronic.h"
tprimetHHadronic analyzer;

void tprimetHHadronic::Init(TTree *tree) {

  tree->SetMakeClass(1);

  candidate_id_branch = tree->GetBranch("candidate_id");
  if (candidate_id_branch) candidate_id_branch->SetAddress(&candidate_id_);
  weight_branch = tree->GetBranch("weight");
  if (weight_branch) weight_branch->SetAddress(&weight_);
  CMS_hgg_mass_branch = tree->GetBranch("CMS_hgg_mass");
  if (CMS_hgg_mass_branch) CMS_hgg_mass_branch->SetAddress(&CMS_hgg_mass_);
  sigmaMoM_decorr_branch = tree->GetBranch("sigmaMoM_decorr");
  if (sigmaMoM_decorr_branch) sigmaMoM_decorr_branch->SetAddress(&sigmaMoM_decorr_);
  dZ_branch = tree->GetBranch("dZ");
  if (dZ_branch) dZ_branch->SetAddress(&dZ_);
  centralObjectWeight_branch = tree->GetBranch("centralObjectWeight");
  if (centralObjectWeight_branch) centralObjectWeight_branch->SetAddress(&centralObjectWeight_);
  vtxprob_branch = tree->GetBranch("vtxprob");
  if (vtxprob_branch) vtxprob_branch->SetAddress(&vtxprob_);
  ptbal_branch = tree->GetBranch("ptbal");
  if (ptbal_branch) ptbal_branch->SetAddress(&ptbal_);
  ptasym_branch = tree->GetBranch("ptasym");
  if (ptasym_branch) ptasym_branch->SetAddress(&ptasym_);
  logspt2_branch = tree->GetBranch("logspt2");
  if (logspt2_branch) logspt2_branch->SetAddress(&logspt2_);
  p2conv_branch = tree->GetBranch("p2conv");
  if (p2conv_branch) p2conv_branch->SetAddress(&p2conv_);
  nconv_branch = tree->GetBranch("nconv");
  if (nconv_branch) nconv_branch->SetAddress(&nconv_);
  vtxmva_branch = tree->GetBranch("vtxmva");
  if (vtxmva_branch) vtxmva_branch->SetAddress(&vtxmva_);
  vtxdz_branch = tree->GetBranch("vtxdz");
  if (vtxdz_branch) vtxdz_branch->SetAddress(&vtxdz_);
  vtx_x_branch = tree->GetBranch("vtx_x");
  if (vtx_x_branch) vtx_x_branch->SetAddress(&vtx_x_);
  vtx_y_branch = tree->GetBranch("vtx_y");
  if (vtx_y_branch) vtx_y_branch->SetAddress(&vtx_y_);
  vtx_z_branch = tree->GetBranch("vtx_z");
  if (vtx_z_branch) vtx_z_branch->SetAddress(&vtx_z_);
  dipho_sumpt_branch = tree->GetBranch("dipho_sumpt");
  if (dipho_sumpt_branch) dipho_sumpt_branch->SetAddress(&dipho_sumpt_);
  dipho_cosphi_branch = tree->GetBranch("dipho_cosphi");
  if (dipho_cosphi_branch) dipho_cosphi_branch->SetAddress(&dipho_cosphi_);
  dipho_mass_branch = tree->GetBranch("dipho_mass");
  if (dipho_mass_branch) dipho_mass_branch->SetAddress(&dipho_mass_);
  dipho_pt_branch = tree->GetBranch("dipho_pt");
  if (dipho_pt_branch) dipho_pt_branch->SetAddress(&dipho_pt_);
  dipho_phi_branch = tree->GetBranch("dipho_phi");
  if (dipho_phi_branch) dipho_phi_branch->SetAddress(&dipho_phi_);
  dipho_eta_branch = tree->GetBranch("dipho_eta");
  if (dipho_eta_branch) dipho_eta_branch->SetAddress(&dipho_eta_);
  dipho_e_branch = tree->GetBranch("dipho_e");
  if (dipho_e_branch) dipho_e_branch->SetAddress(&dipho_e_);
  dipho_PtoM_branch = tree->GetBranch("dipho_PtoM");
  if (dipho_PtoM_branch) dipho_PtoM_branch->SetAddress(&dipho_PtoM_);
  cosphi_branch = tree->GetBranch("cosphi");
  if (cosphi_branch) cosphi_branch->SetAddress(&cosphi_);
  sigmaMrvoM_branch = tree->GetBranch("sigmaMrvoM");
  if (sigmaMrvoM_branch) sigmaMrvoM_branch->SetAddress(&sigmaMrvoM_);
  sigmaMwvoM_branch = tree->GetBranch("sigmaMwvoM");
  if (sigmaMwvoM_branch) sigmaMwvoM_branch->SetAddress(&sigmaMwvoM_);
  dipho_leadPt_branch = tree->GetBranch("dipho_leadPt");
  if (dipho_leadPt_branch) dipho_leadPt_branch->SetAddress(&dipho_leadPt_);
  dipho_leadEt_branch = tree->GetBranch("dipho_leadEt");
  if (dipho_leadEt_branch) dipho_leadEt_branch->SetAddress(&dipho_leadEt_);
  dipho_leadEta_branch = tree->GetBranch("dipho_leadEta");
  if (dipho_leadEta_branch) dipho_leadEta_branch->SetAddress(&dipho_leadEta_);
  dipho_leadPhi_branch = tree->GetBranch("dipho_leadPhi");
  if (dipho_leadPhi_branch) dipho_leadPhi_branch->SetAddress(&dipho_leadPhi_);
  dipho_lead_sieie_branch = tree->GetBranch("dipho_lead_sieie");
  if (dipho_lead_sieie_branch) dipho_lead_sieie_branch->SetAddress(&dipho_lead_sieie_);
  dipho_lead_hoe_branch = tree->GetBranch("dipho_lead_hoe");
  if (dipho_lead_hoe_branch) dipho_lead_hoe_branch->SetAddress(&dipho_lead_hoe_);
  dipho_lead_sigmaEoE_branch = tree->GetBranch("dipho_lead_sigmaEoE");
  if (dipho_lead_sigmaEoE_branch) dipho_lead_sigmaEoE_branch->SetAddress(&dipho_lead_sigmaEoE_);
  dipho_lead_ptoM_branch = tree->GetBranch("dipho_lead_ptoM");
  if (dipho_lead_ptoM_branch) dipho_lead_ptoM_branch->SetAddress(&dipho_lead_ptoM_);
  dipho_leadR9_branch = tree->GetBranch("dipho_leadR9");
  if (dipho_leadR9_branch) dipho_leadR9_branch->SetAddress(&dipho_leadR9_);
  dipho_leadIDMVA_branch = tree->GetBranch("dipho_leadIDMVA");
  if (dipho_leadIDMVA_branch) dipho_leadIDMVA_branch->SetAddress(&dipho_leadIDMVA_);
  dipho_lead_elveto_branch = tree->GetBranch("dipho_lead_elveto");
  if (dipho_lead_elveto_branch) dipho_lead_elveto_branch->SetAddress(&dipho_lead_elveto_);
  dipho_lead_prompt_branch = tree->GetBranch("dipho_lead_prompt");
  if (dipho_lead_prompt_branch) dipho_lead_prompt_branch->SetAddress(&dipho_lead_prompt_);
  dipho_lead_chiso_branch = tree->GetBranch("dipho_lead_chiso");
  if (dipho_lead_chiso_branch) dipho_lead_chiso_branch->SetAddress(&dipho_lead_chiso_);
  dipho_lead_chisow_branch = tree->GetBranch("dipho_lead_chisow");
  if (dipho_lead_chisow_branch) dipho_lead_chisow_branch->SetAddress(&dipho_lead_chisow_);
  dipho_lead_phoiso_branch = tree->GetBranch("dipho_lead_phoiso");
  if (dipho_lead_phoiso_branch) dipho_lead_phoiso_branch->SetAddress(&dipho_lead_phoiso_);
  dipho_lead_phoiso04_branch = tree->GetBranch("dipho_lead_phoiso04");
  if (dipho_lead_phoiso04_branch) dipho_lead_phoiso04_branch->SetAddress(&dipho_lead_phoiso04_);
  dipho_lead_neutiso_branch = tree->GetBranch("dipho_lead_neutiso");
  if (dipho_lead_neutiso_branch) dipho_lead_neutiso_branch->SetAddress(&dipho_lead_neutiso_);
  dipho_lead_ecaliso03_branch = tree->GetBranch("dipho_lead_ecaliso03");
  if (dipho_lead_ecaliso03_branch) dipho_lead_ecaliso03_branch->SetAddress(&dipho_lead_ecaliso03_);
  dipho_lead_hcaliso03_branch = tree->GetBranch("dipho_lead_hcaliso03");
  if (dipho_lead_hcaliso03_branch) dipho_lead_hcaliso03_branch->SetAddress(&dipho_lead_hcaliso03_);
  dipho_lead_pfcluecal03_branch = tree->GetBranch("dipho_lead_pfcluecal03");
  if (dipho_lead_pfcluecal03_branch) dipho_lead_pfcluecal03_branch->SetAddress(&dipho_lead_pfcluecal03_);
  dipho_lead_pfcluhcal03_branch = tree->GetBranch("dipho_lead_pfcluhcal03");
  if (dipho_lead_pfcluhcal03_branch) dipho_lead_pfcluhcal03_branch->SetAddress(&dipho_lead_pfcluhcal03_);
  dipho_lead_trkiso03_branch = tree->GetBranch("dipho_lead_trkiso03");
  if (dipho_lead_trkiso03_branch) dipho_lead_trkiso03_branch->SetAddress(&dipho_lead_trkiso03_);
  dipho_lead_pfchiso2_branch = tree->GetBranch("dipho_lead_pfchiso2");
  if (dipho_lead_pfchiso2_branch) dipho_lead_pfchiso2_branch->SetAddress(&dipho_lead_pfchiso2_);
  dipho_lead_haspixelseed_branch = tree->GetBranch("dipho_lead_haspixelseed");
  if (dipho_lead_haspixelseed_branch) dipho_lead_haspixelseed_branch->SetAddress(&dipho_lead_haspixelseed_);
  dipho_lead_sieip_branch = tree->GetBranch("dipho_lead_sieip");
  if (dipho_lead_sieip_branch) dipho_lead_sieip_branch->SetAddress(&dipho_lead_sieip_);
  dipho_lead_etawidth_branch = tree->GetBranch("dipho_lead_etawidth");
  if (dipho_lead_etawidth_branch) dipho_lead_etawidth_branch->SetAddress(&dipho_lead_etawidth_);
  dipho_lead_phiwidth_branch = tree->GetBranch("dipho_lead_phiwidth");
  if (dipho_lead_phiwidth_branch) dipho_lead_phiwidth_branch->SetAddress(&dipho_lead_phiwidth_);
  dipho_lead_regrerr_branch = tree->GetBranch("dipho_lead_regrerr");
  if (dipho_lead_regrerr_branch) dipho_lead_regrerr_branch->SetAddress(&dipho_lead_regrerr_);
  dipho_lead_s4ratio_branch = tree->GetBranch("dipho_lead_s4ratio");
  if (dipho_lead_s4ratio_branch) dipho_lead_s4ratio_branch->SetAddress(&dipho_lead_s4ratio_);
  dipho_lead_effSigma_branch = tree->GetBranch("dipho_lead_effSigma");
  if (dipho_lead_effSigma_branch) dipho_lead_effSigma_branch->SetAddress(&dipho_lead_effSigma_);
  dipho_lead_scraw_branch = tree->GetBranch("dipho_lead_scraw");
  if (dipho_lead_scraw_branch) dipho_lead_scraw_branch->SetAddress(&dipho_lead_scraw_);
  dipho_lead_ese_branch = tree->GetBranch("dipho_lead_ese");
  if (dipho_lead_ese_branch) dipho_lead_ese_branch->SetAddress(&dipho_lead_ese_);
  dipho_subleadPt_branch = tree->GetBranch("dipho_subleadPt");
  if (dipho_subleadPt_branch) dipho_subleadPt_branch->SetAddress(&dipho_subleadPt_);
  dipho_subleadEt_branch = tree->GetBranch("dipho_subleadEt");
  if (dipho_subleadEt_branch) dipho_subleadEt_branch->SetAddress(&dipho_subleadEt_);
  dipho_subleadEta_branch = tree->GetBranch("dipho_subleadEta");
  if (dipho_subleadEta_branch) dipho_subleadEta_branch->SetAddress(&dipho_subleadEta_);
  dipho_subleadPhi_branch = tree->GetBranch("dipho_subleadPhi");
  if (dipho_subleadPhi_branch) dipho_subleadPhi_branch->SetAddress(&dipho_subleadPhi_);
  dipho_sublead_sieie_branch = tree->GetBranch("dipho_sublead_sieie");
  if (dipho_sublead_sieie_branch) dipho_sublead_sieie_branch->SetAddress(&dipho_sublead_sieie_);
  dipho_sublead_hoe_branch = tree->GetBranch("dipho_sublead_hoe");
  if (dipho_sublead_hoe_branch) dipho_sublead_hoe_branch->SetAddress(&dipho_sublead_hoe_);
  dipho_sublead_sigmaEoE_branch = tree->GetBranch("dipho_sublead_sigmaEoE");
  if (dipho_sublead_sigmaEoE_branch) dipho_sublead_sigmaEoE_branch->SetAddress(&dipho_sublead_sigmaEoE_);
  dipho_sublead_ptoM_branch = tree->GetBranch("dipho_sublead_ptoM");
  if (dipho_sublead_ptoM_branch) dipho_sublead_ptoM_branch->SetAddress(&dipho_sublead_ptoM_);
  dipho_subleadR9_branch = tree->GetBranch("dipho_subleadR9");
  if (dipho_subleadR9_branch) dipho_subleadR9_branch->SetAddress(&dipho_subleadR9_);
  dipho_subleadIDMVA_branch = tree->GetBranch("dipho_subleadIDMVA");
  if (dipho_subleadIDMVA_branch) dipho_subleadIDMVA_branch->SetAddress(&dipho_subleadIDMVA_);
  dipho_sublead_elveto_branch = tree->GetBranch("dipho_sublead_elveto");
  if (dipho_sublead_elveto_branch) dipho_sublead_elveto_branch->SetAddress(&dipho_sublead_elveto_);
  dipho_sulead_prompt_branch = tree->GetBranch("dipho_sulead_prompt");
  if (dipho_sulead_prompt_branch) dipho_sulead_prompt_branch->SetAddress(&dipho_sulead_prompt_);
  dipho_sublead_chiso_branch = tree->GetBranch("dipho_sublead_chiso");
  if (dipho_sublead_chiso_branch) dipho_sublead_chiso_branch->SetAddress(&dipho_sublead_chiso_);
  dipho_sublead_chisow_branch = tree->GetBranch("dipho_sublead_chisow");
  if (dipho_sublead_chisow_branch) dipho_sublead_chisow_branch->SetAddress(&dipho_sublead_chisow_);
  dipho_sublead_phoiso_branch = tree->GetBranch("dipho_sublead_phoiso");
  if (dipho_sublead_phoiso_branch) dipho_sublead_phoiso_branch->SetAddress(&dipho_sublead_phoiso_);
  dipho_sublead_phoiso04_branch = tree->GetBranch("dipho_sublead_phoiso04");
  if (dipho_sublead_phoiso04_branch) dipho_sublead_phoiso04_branch->SetAddress(&dipho_sublead_phoiso04_);
  dipho_sublead_neutiso_branch = tree->GetBranch("dipho_sublead_neutiso");
  if (dipho_sublead_neutiso_branch) dipho_sublead_neutiso_branch->SetAddress(&dipho_sublead_neutiso_);
  dipho_sublead_ecaliso03_branch = tree->GetBranch("dipho_sublead_ecaliso03");
  if (dipho_sublead_ecaliso03_branch) dipho_sublead_ecaliso03_branch->SetAddress(&dipho_sublead_ecaliso03_);
  dipho_sublead_hcaliso03_branch = tree->GetBranch("dipho_sublead_hcaliso03");
  if (dipho_sublead_hcaliso03_branch) dipho_sublead_hcaliso03_branch->SetAddress(&dipho_sublead_hcaliso03_);
  dipho_sublead_pfcluecal03_branch = tree->GetBranch("dipho_sublead_pfcluecal03");
  if (dipho_sublead_pfcluecal03_branch) dipho_sublead_pfcluecal03_branch->SetAddress(&dipho_sublead_pfcluecal03_);
  dipho_sublead_pfcluhcal03_branch = tree->GetBranch("dipho_sublead_pfcluhcal03");
  if (dipho_sublead_pfcluhcal03_branch) dipho_sublead_pfcluhcal03_branch->SetAddress(&dipho_sublead_pfcluhcal03_);
  dipho_sublead_trkiso03_branch = tree->GetBranch("dipho_sublead_trkiso03");
  if (dipho_sublead_trkiso03_branch) dipho_sublead_trkiso03_branch->SetAddress(&dipho_sublead_trkiso03_);
  dipho_sublead_pfchiso2_branch = tree->GetBranch("dipho_sublead_pfchiso2");
  if (dipho_sublead_pfchiso2_branch) dipho_sublead_pfchiso2_branch->SetAddress(&dipho_sublead_pfchiso2_);
  dipho_sublead_haspixelseed_branch = tree->GetBranch("dipho_sublead_haspixelseed");
  if (dipho_sublead_haspixelseed_branch) dipho_sublead_haspixelseed_branch->SetAddress(&dipho_sublead_haspixelseed_);
  dipho_sublead_sieip_branch = tree->GetBranch("dipho_sublead_sieip");
  if (dipho_sublead_sieip_branch) dipho_sublead_sieip_branch->SetAddress(&dipho_sublead_sieip_);
  dipho_sublead_etawidth_branch = tree->GetBranch("dipho_sublead_etawidth");
  if (dipho_sublead_etawidth_branch) dipho_sublead_etawidth_branch->SetAddress(&dipho_sublead_etawidth_);
  dipho_sublead_phiwidth_branch = tree->GetBranch("dipho_sublead_phiwidth");
  if (dipho_sublead_phiwidth_branch) dipho_sublead_phiwidth_branch->SetAddress(&dipho_sublead_phiwidth_);
  dipho_sublead_regrerr_branch = tree->GetBranch("dipho_sublead_regrerr");
  if (dipho_sublead_regrerr_branch) dipho_sublead_regrerr_branch->SetAddress(&dipho_sublead_regrerr_);
  dipho_sublead_s4ratio_branch = tree->GetBranch("dipho_sublead_s4ratio");
  if (dipho_sublead_s4ratio_branch) dipho_sublead_s4ratio_branch->SetAddress(&dipho_sublead_s4ratio_);
  dipho_sublead_effSigma_branch = tree->GetBranch("dipho_sublead_effSigma");
  if (dipho_sublead_effSigma_branch) dipho_sublead_effSigma_branch->SetAddress(&dipho_sublead_effSigma_);
  dipho_sublead_scraw_branch = tree->GetBranch("dipho_sublead_scraw");
  if (dipho_sublead_scraw_branch) dipho_sublead_scraw_branch->SetAddress(&dipho_sublead_scraw_);
  dipho_sublead_ese_branch = tree->GetBranch("dipho_sublead_ese");
  if (dipho_sublead_ese_branch) dipho_sublead_ese_branch->SetAddress(&dipho_sublead_ese_);
  LeptonType_branch = tree->GetBranch("LeptonType");
  if (LeptonType_branch) LeptonType_branch->SetAddress(&LeptonType_);
  n_ele_branch = tree->GetBranch("n_ele");
  if (n_ele_branch) n_ele_branch->SetAddress(&n_ele_);
  n_loose_ele_branch = tree->GetBranch("n_loose_ele");
  if (n_loose_ele_branch) n_loose_ele_branch->SetAddress(&n_loose_ele_);
  n_veto_ele_branch = tree->GetBranch("n_veto_ele");
  if (n_veto_ele_branch) n_veto_ele_branch->SetAddress(&n_veto_ele_);
  n_medium_ele_branch = tree->GetBranch("n_medium_ele");
  if (n_medium_ele_branch) n_medium_ele_branch->SetAddress(&n_medium_ele_);
  n_tight_ele_branch = tree->GetBranch("n_tight_ele");
  if (n_tight_ele_branch) n_tight_ele_branch->SetAddress(&n_tight_ele_);
  ele1_pt_branch = tree->GetBranch("ele1_pt");
  if (ele1_pt_branch) ele1_pt_branch->SetAddress(&ele1_pt_);
  ele2_pt_branch = tree->GetBranch("ele2_pt");
  if (ele2_pt_branch) ele2_pt_branch->SetAddress(&ele2_pt_);
  ele1_eta_branch = tree->GetBranch("ele1_eta");
  if (ele1_eta_branch) ele1_eta_branch->SetAddress(&ele1_eta_);
  ele2_eta_branch = tree->GetBranch("ele2_eta");
  if (ele2_eta_branch) ele2_eta_branch->SetAddress(&ele2_eta_);
  ele1_phi_branch = tree->GetBranch("ele1_phi");
  if (ele1_phi_branch) ele1_phi_branch->SetAddress(&ele1_phi_);
  ele2_phi_branch = tree->GetBranch("ele2_phi");
  if (ele2_phi_branch) ele2_phi_branch->SetAddress(&ele2_phi_);
  ele1_e_branch = tree->GetBranch("ele1_e");
  if (ele1_e_branch) ele1_e_branch->SetAddress(&ele1_e_);
  ele2_e_branch = tree->GetBranch("ele2_e");
  if (ele2_e_branch) ele2_e_branch->SetAddress(&ele2_e_);
  ele1_ch_branch = tree->GetBranch("ele1_ch");
  if (ele1_ch_branch) ele1_ch_branch->SetAddress(&ele1_ch_);
  ele2_ch_branch = tree->GetBranch("ele2_ch");
  if (ele2_ch_branch) ele2_ch_branch->SetAddress(&ele2_ch_);
  ele1_sigmaIetaIeta_branch = tree->GetBranch("ele1_sigmaIetaIeta");
  if (ele1_sigmaIetaIeta_branch) ele1_sigmaIetaIeta_branch->SetAddress(&ele1_sigmaIetaIeta_);
  ele2_sigmaIetaIeta_branch = tree->GetBranch("ele2_sigmaIetaIeta");
  if (ele2_sigmaIetaIeta_branch) ele2_sigmaIetaIeta_branch->SetAddress(&ele2_sigmaIetaIeta_);
  ele1_dEtaInSeed_branch = tree->GetBranch("ele1_dEtaInSeed");
  if (ele1_dEtaInSeed_branch) ele1_dEtaInSeed_branch->SetAddress(&ele1_dEtaInSeed_);
  ele2_dEtaInSeed_branch = tree->GetBranch("ele2_dEtaInSeed");
  if (ele2_dEtaInSeed_branch) ele2_dEtaInSeed_branch->SetAddress(&ele2_dEtaInSeed_);
  ele1_dPhiIn_branch = tree->GetBranch("ele1_dPhiIn");
  if (ele1_dPhiIn_branch) ele1_dPhiIn_branch->SetAddress(&ele1_dPhiIn_);
  ele2_dPhiIn_branch = tree->GetBranch("ele2_dPhiIn");
  if (ele2_dPhiIn_branch) ele2_dPhiIn_branch->SetAddress(&ele2_dPhiIn_);
  ele1_hOverE_branch = tree->GetBranch("ele1_hOverE");
  if (ele1_hOverE_branch) ele1_hOverE_branch->SetAddress(&ele1_hOverE_);
  ele2_hOverE_branch = tree->GetBranch("ele2_hOverE");
  if (ele2_hOverE_branch) ele2_hOverE_branch->SetAddress(&ele2_hOverE_);
  ele1_RelIsoEA_branch = tree->GetBranch("ele1_RelIsoEA");
  if (ele1_RelIsoEA_branch) ele1_RelIsoEA_branch->SetAddress(&ele1_RelIsoEA_);
  ele2_RelIsoEA_branch = tree->GetBranch("ele2_RelIsoEA");
  if (ele2_RelIsoEA_branch) ele2_RelIsoEA_branch->SetAddress(&ele2_RelIsoEA_);
  ele1_ooEmooP_branch = tree->GetBranch("ele1_ooEmooP");
  if (ele1_ooEmooP_branch) ele1_ooEmooP_branch->SetAddress(&ele1_ooEmooP_);
  ele2_ooEmooP_branch = tree->GetBranch("ele2_ooEmooP");
  if (ele2_ooEmooP_branch) ele2_ooEmooP_branch->SetAddress(&ele2_ooEmooP_);
  ele1_dxy_branch = tree->GetBranch("ele1_dxy");
  if (ele1_dxy_branch) ele1_dxy_branch->SetAddress(&ele1_dxy_);
  ele2_dxy_branch = tree->GetBranch("ele2_dxy");
  if (ele2_dxy_branch) ele2_dxy_branch->SetAddress(&ele2_dxy_);
  ele1_diphodxy_branch = tree->GetBranch("ele1_diphodxy");
  if (ele1_diphodxy_branch) ele1_diphodxy_branch->SetAddress(&ele1_diphodxy_);
  ele2_diphodxy_branch = tree->GetBranch("ele2_diphodxy");
  if (ele2_diphodxy_branch) ele2_diphodxy_branch->SetAddress(&ele2_diphodxy_);
  ele1_dz_branch = tree->GetBranch("ele1_dz");
  if (ele1_dz_branch) ele1_dz_branch->SetAddress(&ele1_dz_);
  ele2_dz_branch = tree->GetBranch("ele2_dz");
  if (ele2_dz_branch) ele2_dz_branch->SetAddress(&ele2_dz_);
  ele1_diphodz_branch = tree->GetBranch("ele1_diphodz");
  if (ele1_diphodz_branch) ele1_diphodz_branch->SetAddress(&ele1_diphodz_);
  ele2_diphodz_branch = tree->GetBranch("ele2_diphodz");
  if (ele2_diphodz_branch) ele2_diphodz_branch->SetAddress(&ele2_diphodz_);
  ele1_misHits_branch = tree->GetBranch("ele1_misHits");
  if (ele1_misHits_branch) ele1_misHits_branch->SetAddress(&ele1_misHits_);
  ele2_misHits_branch = tree->GetBranch("ele2_misHits");
  if (ele2_misHits_branch) ele2_misHits_branch->SetAddress(&ele2_misHits_);
  ele1_ConversionVeto_branch = tree->GetBranch("ele1_ConversionVeto");
  if (ele1_ConversionVeto_branch) ele1_ConversionVeto_branch->SetAddress(&ele1_ConversionVeto_);
  ele2_ConversionVeto_branch = tree->GetBranch("ele2_ConversionVeto");
  if (ele2_ConversionVeto_branch) ele2_ConversionVeto_branch->SetAddress(&ele2_ConversionVeto_);
  ele1_ChargedHadronPt_branch = tree->GetBranch("ele1_ChargedHadronPt");
  if (ele1_ChargedHadronPt_branch) ele1_ChargedHadronPt_branch->SetAddress(&ele1_ChargedHadronPt_);
  ele2_ChargedHadronPt_branch = tree->GetBranch("ele2_ChargedHadronPt");
  if (ele2_ChargedHadronPt_branch) ele2_ChargedHadronPt_branch->SetAddress(&ele2_ChargedHadronPt_);
  ele2_NeutralHadronEt_branch = tree->GetBranch("ele2_NeutralHadronEt");
  if (ele2_NeutralHadronEt_branch) ele2_NeutralHadronEt_branch->SetAddress(&ele2_NeutralHadronEt_);
  ele1_NeutralHadronEt_branch = tree->GetBranch("ele1_NeutralHadronEt");
  if (ele1_NeutralHadronEt_branch) ele1_NeutralHadronEt_branch->SetAddress(&ele1_NeutralHadronEt_);
  ele1_PhotonEt_branch = tree->GetBranch("ele1_PhotonEt");
  if (ele1_PhotonEt_branch) ele1_PhotonEt_branch->SetAddress(&ele1_PhotonEt_);
  ele2_PhotonEt_branch = tree->GetBranch("ele2_PhotonEt");
  if (ele2_PhotonEt_branch) ele2_PhotonEt_branch->SetAddress(&ele2_PhotonEt_);
  ele1_PassTight_branch = tree->GetBranch("ele1_PassTight");
  if (ele1_PassTight_branch) ele1_PassTight_branch->SetAddress(&ele1_PassTight_);
  ele2_PassTight_branch = tree->GetBranch("ele2_PassTight");
  if (ele2_PassTight_branch) ele2_PassTight_branch->SetAddress(&ele2_PassTight_);
  ele1_PassVeto_branch = tree->GetBranch("ele1_PassVeto");
  if (ele1_PassVeto_branch) ele1_PassVeto_branch->SetAddress(&ele1_PassVeto_);
  ele2_PassVeto_branch = tree->GetBranch("ele2_PassVeto");
  if (ele2_PassVeto_branch) ele2_PassVeto_branch->SetAddress(&ele2_PassVeto_);
  ele1_dPhiMET_branch = tree->GetBranch("ele1_dPhiMET");
  if (ele1_dPhiMET_branch) ele1_dPhiMET_branch->SetAddress(&ele1_dPhiMET_);
  ele2_dPhiMET_branch = tree->GetBranch("ele2_dPhiMET");
  if (ele2_dPhiMET_branch) ele2_dPhiMET_branch->SetAddress(&ele2_dPhiMET_);
  n_muons_branch = tree->GetBranch("n_muons");
  if (n_muons_branch) n_muons_branch->SetAddress(&n_muons_);
  n_LooseMu25_branch = tree->GetBranch("n_LooseMu25");
  if (n_LooseMu25_branch) n_LooseMu25_branch->SetAddress(&n_LooseMu25_);
  n_LooseMu15_branch = tree->GetBranch("n_LooseMu15");
  if (n_LooseMu15_branch) n_LooseMu15_branch->SetAddress(&n_LooseMu15_);
  n_TightMu25_branch = tree->GetBranch("n_TightMu25");
  if (n_TightMu25_branch) n_TightMu25_branch->SetAddress(&n_TightMu25_);
  n_TightMu15_branch = tree->GetBranch("n_TightMu15");
  if (n_TightMu15_branch) n_TightMu15_branch->SetAddress(&n_TightMu15_);
  n_MediumMu25_branch = tree->GetBranch("n_MediumMu25");
  if (n_MediumMu25_branch) n_MediumMu25_branch->SetAddress(&n_MediumMu25_);
  n_MediumMu15_branch = tree->GetBranch("n_MediumMu15");
  if (n_MediumMu15_branch) n_MediumMu15_branch->SetAddress(&n_MediumMu15_);
  muon1_pt_branch = tree->GetBranch("muon1_pt");
  if (muon1_pt_branch) muon1_pt_branch->SetAddress(&muon1_pt_);
  muon2_pt_branch = tree->GetBranch("muon2_pt");
  if (muon2_pt_branch) muon2_pt_branch->SetAddress(&muon2_pt_);
  muon1_eta_branch = tree->GetBranch("muon1_eta");
  if (muon1_eta_branch) muon1_eta_branch->SetAddress(&muon1_eta_);
  muon2_eta_branch = tree->GetBranch("muon2_eta");
  if (muon2_eta_branch) muon2_eta_branch->SetAddress(&muon2_eta_);
  muon1_phi_branch = tree->GetBranch("muon1_phi");
  if (muon1_phi_branch) muon1_phi_branch->SetAddress(&muon1_phi_);
  muon2_phi_branch = tree->GetBranch("muon2_phi");
  if (muon2_phi_branch) muon2_phi_branch->SetAddress(&muon2_phi_);
  muon1_e_branch = tree->GetBranch("muon1_e");
  if (muon1_e_branch) muon1_e_branch->SetAddress(&muon1_e_);
  muon2_e_branch = tree->GetBranch("muon2_e");
  if (muon2_e_branch) muon2_e_branch->SetAddress(&muon2_e_);
  muon1_ch_branch = tree->GetBranch("muon1_ch");
  if (muon1_ch_branch) muon1_ch_branch->SetAddress(&muon1_ch_);
  muon2_ch_branch = tree->GetBranch("muon2_ch");
  if (muon2_ch_branch) muon2_ch_branch->SetAddress(&muon2_ch_);
  muon1_iso_branch = tree->GetBranch("muon1_iso");
  if (muon1_iso_branch) muon1_iso_branch->SetAddress(&muon1_iso_);
  muon2_iso_branch = tree->GetBranch("muon2_iso");
  if (muon2_iso_branch) muon2_iso_branch->SetAddress(&muon2_iso_);
  muon1_chi2_branch = tree->GetBranch("muon1_chi2");
  if (muon1_chi2_branch) muon1_chi2_branch->SetAddress(&muon1_chi2_);
  muon2_chi2_branch = tree->GetBranch("muon2_chi2");
  if (muon2_chi2_branch) muon2_chi2_branch->SetAddress(&muon2_chi2_);
  muon1_mHits_branch = tree->GetBranch("muon1_mHits");
  if (muon1_mHits_branch) muon1_mHits_branch->SetAddress(&muon1_mHits_);
  muon2_mHits_branch = tree->GetBranch("muon2_mHits");
  if (muon2_mHits_branch) muon2_mHits_branch->SetAddress(&muon2_mHits_);
  muon1_mStations_branch = tree->GetBranch("muon1_mStations");
  if (muon1_mStations_branch) muon1_mStations_branch->SetAddress(&muon1_mStations_);
  muon2_mStations_branch = tree->GetBranch("muon2_mStations");
  if (muon2_mStations_branch) muon2_mStations_branch->SetAddress(&muon2_mStations_);
  muon1_dxy_branch = tree->GetBranch("muon1_dxy");
  if (muon1_dxy_branch) muon1_dxy_branch->SetAddress(&muon1_dxy_);
  muon2_dxy_branch = tree->GetBranch("muon2_dxy");
  if (muon2_dxy_branch) muon2_dxy_branch->SetAddress(&muon2_dxy_);
  muon1_diphodxy_branch = tree->GetBranch("muon1_diphodxy");
  if (muon1_diphodxy_branch) muon1_diphodxy_branch->SetAddress(&muon1_diphodxy_);
  muon2_diphodxy_branch = tree->GetBranch("muon2_diphodxy");
  if (muon2_diphodxy_branch) muon2_diphodxy_branch->SetAddress(&muon2_diphodxy_);
  muon1_dz_branch = tree->GetBranch("muon1_dz");
  if (muon1_dz_branch) muon1_dz_branch->SetAddress(&muon1_dz_);
  muon2_dz_branch = tree->GetBranch("muon2_dz");
  if (muon2_dz_branch) muon2_dz_branch->SetAddress(&muon2_dz_);
  muon1_diphodz_branch = tree->GetBranch("muon1_diphodz");
  if (muon1_diphodz_branch) muon1_diphodz_branch->SetAddress(&muon1_diphodz_);
  muon2_diphodz_branch = tree->GetBranch("muon2_diphodz");
  if (muon2_diphodz_branch) muon2_diphodz_branch->SetAddress(&muon2_diphodz_);
  muon1_pxHits_branch = tree->GetBranch("muon1_pxHits");
  if (muon1_pxHits_branch) muon1_pxHits_branch->SetAddress(&muon1_pxHits_);
  muon2_pxHits_branch = tree->GetBranch("muon2_pxHits");
  if (muon2_pxHits_branch) muon2_pxHits_branch->SetAddress(&muon2_pxHits_);
  muon1_tkLayers_branch = tree->GetBranch("muon1_tkLayers");
  if (muon1_tkLayers_branch) muon1_tkLayers_branch->SetAddress(&muon1_tkLayers_);
  muon2_tkLayers_branch = tree->GetBranch("muon2_tkLayers");
  if (muon2_tkLayers_branch) muon2_tkLayers_branch->SetAddress(&muon2_tkLayers_);
  muon1_PassTight_branch = tree->GetBranch("muon1_PassTight");
  if (muon1_PassTight_branch) muon1_PassTight_branch->SetAddress(&muon1_PassTight_);
  muon2_PassTight_branch = tree->GetBranch("muon2_PassTight");
  if (muon2_PassTight_branch) muon2_PassTight_branch->SetAddress(&muon2_PassTight_);
  muon1_dPhiMET_branch = tree->GetBranch("muon1_dPhiMET");
  if (muon1_dPhiMET_branch) muon1_dPhiMET_branch->SetAddress(&muon1_dPhiMET_);
  muon2_dPhiMET_branch = tree->GetBranch("muon2_dPhiMET");
  if (muon2_dPhiMET_branch) muon2_dPhiMET_branch->SetAddress(&muon2_dPhiMET_);
  n_fwdjets_branch = tree->GetBranch("n_fwdjets");
  if (n_fwdjets_branch) n_fwdjets_branch->SetAddress(&n_fwdjets_);
  fwdjet1_pt_branch = tree->GetBranch("fwdjet1_pt");
  if (fwdjet1_pt_branch) fwdjet1_pt_branch->SetAddress(&fwdjet1_pt_);
  fwdjet2_pt_branch = tree->GetBranch("fwdjet2_pt");
  if (fwdjet2_pt_branch) fwdjet2_pt_branch->SetAddress(&fwdjet2_pt_);
  fwdjet3_pt_branch = tree->GetBranch("fwdjet3_pt");
  if (fwdjet3_pt_branch) fwdjet3_pt_branch->SetAddress(&fwdjet3_pt_);
  fwdjet1_eta_branch = tree->GetBranch("fwdjet1_eta");
  if (fwdjet1_eta_branch) fwdjet1_eta_branch->SetAddress(&fwdjet1_eta_);
  fwdjet2_eta_branch = tree->GetBranch("fwdjet2_eta");
  if (fwdjet2_eta_branch) fwdjet2_eta_branch->SetAddress(&fwdjet2_eta_);
  fwdjet3_eta_branch = tree->GetBranch("fwdjet3_eta");
  if (fwdjet3_eta_branch) fwdjet3_eta_branch->SetAddress(&fwdjet3_eta_);
  fwdjet4_eta_branch = tree->GetBranch("fwdjet4_eta");
  if (fwdjet4_eta_branch) fwdjet4_eta_branch->SetAddress(&fwdjet4_eta_);
  fwdjet5_eta_branch = tree->GetBranch("fwdjet5_eta");
  if (fwdjet5_eta_branch) fwdjet5_eta_branch->SetAddress(&fwdjet5_eta_);
  fwdjet6_eta_branch = tree->GetBranch("fwdjet6_eta");
  if (fwdjet6_eta_branch) fwdjet6_eta_branch->SetAddress(&fwdjet6_eta_);
  fwdjet7_eta_branch = tree->GetBranch("fwdjet7_eta");
  if (fwdjet7_eta_branch) fwdjet7_eta_branch->SetAddress(&fwdjet7_eta_);
  fwdjet8_eta_branch = tree->GetBranch("fwdjet8_eta");
  if (fwdjet8_eta_branch) fwdjet8_eta_branch->SetAddress(&fwdjet8_eta_);
  fwdjet9_eta_branch = tree->GetBranch("fwdjet9_eta");
  if (fwdjet9_eta_branch) fwdjet9_eta_branch->SetAddress(&fwdjet9_eta_);
  fwdjet1_phi_branch = tree->GetBranch("fwdjet1_phi");
  if (fwdjet1_phi_branch) fwdjet1_phi_branch->SetAddress(&fwdjet1_phi_);
  fwdjet2_phi_branch = tree->GetBranch("fwdjet2_phi");
  if (fwdjet2_phi_branch) fwdjet2_phi_branch->SetAddress(&fwdjet2_phi_);
  fwdjet3_phi_branch = tree->GetBranch("fwdjet3_phi");
  if (fwdjet3_phi_branch) fwdjet3_phi_branch->SetAddress(&fwdjet3_phi_);
  fwdjet1_e_branch = tree->GetBranch("fwdjet1_e");
  if (fwdjet1_e_branch) fwdjet1_e_branch->SetAddress(&fwdjet1_e_);
  fwdjet2_e_branch = tree->GetBranch("fwdjet2_e");
  if (fwdjet2_e_branch) fwdjet2_e_branch->SetAddress(&fwdjet2_e_);
  fwdjet3_e_branch = tree->GetBranch("fwdjet3_e");
  if (fwdjet3_e_branch) fwdjet3_e_branch->SetAddress(&fwdjet3_e_);
  fwdjet1_discr_branch = tree->GetBranch("fwdjet1_discr");
  if (fwdjet1_discr_branch) fwdjet1_discr_branch->SetAddress(&fwdjet1_discr_);
  n_M_bjets_branch = tree->GetBranch("n_M_bjets");
  if (n_M_bjets_branch) n_M_bjets_branch->SetAddress(&n_M_bjets_);
  n_L_bjets_branch = tree->GetBranch("n_L_bjets");
  if (n_L_bjets_branch) n_L_bjets_branch->SetAddress(&n_L_bjets_);
  n_T_bjets_branch = tree->GetBranch("n_T_bjets");
  if (n_T_bjets_branch) n_T_bjets_branch->SetAddress(&n_T_bjets_);
  n_bjets_branch = tree->GetBranch("n_bjets");
  if (n_bjets_branch) n_bjets_branch->SetAddress(&n_bjets_);
  bjet1_pt_branch = tree->GetBranch("bjet1_pt");
  if (bjet1_pt_branch) bjet1_pt_branch->SetAddress(&bjet1_pt_);
  bjet2_pt_branch = tree->GetBranch("bjet2_pt");
  if (bjet2_pt_branch) bjet2_pt_branch->SetAddress(&bjet2_pt_);
  bjet3_pt_branch = tree->GetBranch("bjet3_pt");
  if (bjet3_pt_branch) bjet3_pt_branch->SetAddress(&bjet3_pt_);
  bjet1_eta_branch = tree->GetBranch("bjet1_eta");
  if (bjet1_eta_branch) bjet1_eta_branch->SetAddress(&bjet1_eta_);
  bjet2_eta_branch = tree->GetBranch("bjet2_eta");
  if (bjet2_eta_branch) bjet2_eta_branch->SetAddress(&bjet2_eta_);
  bjet3_eta_branch = tree->GetBranch("bjet3_eta");
  if (bjet3_eta_branch) bjet3_eta_branch->SetAddress(&bjet3_eta_);
  bjet1_phi_branch = tree->GetBranch("bjet1_phi");
  if (bjet1_phi_branch) bjet1_phi_branch->SetAddress(&bjet1_phi_);
  bjet2_phi_branch = tree->GetBranch("bjet2_phi");
  if (bjet2_phi_branch) bjet2_phi_branch->SetAddress(&bjet2_phi_);
  bjet3_phi_branch = tree->GetBranch("bjet3_phi");
  if (bjet3_phi_branch) bjet3_phi_branch->SetAddress(&bjet3_phi_);
  bjet1_e_branch = tree->GetBranch("bjet1_e");
  if (bjet1_e_branch) bjet1_e_branch->SetAddress(&bjet1_e_);
  bjet2_e_branch = tree->GetBranch("bjet2_e");
  if (bjet2_e_branch) bjet2_e_branch->SetAddress(&bjet2_e_);
  bjet3_e_branch = tree->GetBranch("bjet3_e");
  if (bjet3_e_branch) bjet3_e_branch->SetAddress(&bjet3_e_);
  bjet1_discr_branch = tree->GetBranch("bjet1_discr");
  if (bjet1_discr_branch) bjet1_discr_branch->SetAddress(&bjet1_discr_);
  bjet2_discr_branch = tree->GetBranch("bjet2_discr");
  if (bjet2_discr_branch) bjet2_discr_branch->SetAddress(&bjet2_discr_);
  bjet3_discr_branch = tree->GetBranch("bjet3_discr");
  if (bjet3_discr_branch) bjet3_discr_branch->SetAddress(&bjet3_discr_);
  bjet4_discr_branch = tree->GetBranch("bjet4_discr");
  if (bjet4_discr_branch) bjet4_discr_branch->SetAddress(&bjet4_discr_);
  n_jets_branch = tree->GetBranch("n_jets");
  if (n_jets_branch) n_jets_branch->SetAddress(&n_jets_);
  jet1_pt_branch = tree->GetBranch("jet1_pt");
  if (jet1_pt_branch) jet1_pt_branch->SetAddress(&jet1_pt_);
  jet2_pt_branch = tree->GetBranch("jet2_pt");
  if (jet2_pt_branch) jet2_pt_branch->SetAddress(&jet2_pt_);
  jet3_pt_branch = tree->GetBranch("jet3_pt");
  if (jet3_pt_branch) jet3_pt_branch->SetAddress(&jet3_pt_);
  jet4_pt_branch = tree->GetBranch("jet4_pt");
  if (jet4_pt_branch) jet4_pt_branch->SetAddress(&jet4_pt_);
  jet5_pt_branch = tree->GetBranch("jet5_pt");
  if (jet5_pt_branch) jet5_pt_branch->SetAddress(&jet5_pt_);
  jet6_pt_branch = tree->GetBranch("jet6_pt");
  if (jet6_pt_branch) jet6_pt_branch->SetAddress(&jet6_pt_);
  jet7_pt_branch = tree->GetBranch("jet7_pt");
  if (jet7_pt_branch) jet7_pt_branch->SetAddress(&jet7_pt_);
  jet8_pt_branch = tree->GetBranch("jet8_pt");
  if (jet8_pt_branch) jet8_pt_branch->SetAddress(&jet8_pt_);
  jet9_pt_branch = tree->GetBranch("jet9_pt");
  if (jet9_pt_branch) jet9_pt_branch->SetAddress(&jet9_pt_);
  jet10_pt_branch = tree->GetBranch("jet10_pt");
  if (jet10_pt_branch) jet10_pt_branch->SetAddress(&jet10_pt_);
  jet11_pt_branch = tree->GetBranch("jet11_pt");
  if (jet11_pt_branch) jet11_pt_branch->SetAddress(&jet11_pt_);
  jet12_pt_branch = tree->GetBranch("jet12_pt");
  if (jet12_pt_branch) jet12_pt_branch->SetAddress(&jet12_pt_);
  jet13_pt_branch = tree->GetBranch("jet13_pt");
  if (jet13_pt_branch) jet13_pt_branch->SetAddress(&jet13_pt_);
  jet14_pt_branch = tree->GetBranch("jet14_pt");
  if (jet14_pt_branch) jet14_pt_branch->SetAddress(&jet14_pt_);
  jet15_pt_branch = tree->GetBranch("jet15_pt");
  if (jet15_pt_branch) jet15_pt_branch->SetAddress(&jet15_pt_);
  jet1_eta_branch = tree->GetBranch("jet1_eta");
  if (jet1_eta_branch) jet1_eta_branch->SetAddress(&jet1_eta_);
  jet2_eta_branch = tree->GetBranch("jet2_eta");
  if (jet2_eta_branch) jet2_eta_branch->SetAddress(&jet2_eta_);
  jet3_eta_branch = tree->GetBranch("jet3_eta");
  if (jet3_eta_branch) jet3_eta_branch->SetAddress(&jet3_eta_);
  jet4_eta_branch = tree->GetBranch("jet4_eta");
  if (jet4_eta_branch) jet4_eta_branch->SetAddress(&jet4_eta_);
  jet5_eta_branch = tree->GetBranch("jet5_eta");
  if (jet5_eta_branch) jet5_eta_branch->SetAddress(&jet5_eta_);
  jet6_eta_branch = tree->GetBranch("jet6_eta");
  if (jet6_eta_branch) jet6_eta_branch->SetAddress(&jet6_eta_);
  jet7_eta_branch = tree->GetBranch("jet7_eta");
  if (jet7_eta_branch) jet7_eta_branch->SetAddress(&jet7_eta_);
  jet8_eta_branch = tree->GetBranch("jet8_eta");
  if (jet8_eta_branch) jet8_eta_branch->SetAddress(&jet8_eta_);
  jet9_eta_branch = tree->GetBranch("jet9_eta");
  if (jet9_eta_branch) jet9_eta_branch->SetAddress(&jet9_eta_);
  jet10_eta_branch = tree->GetBranch("jet10_eta");
  if (jet10_eta_branch) jet10_eta_branch->SetAddress(&jet10_eta_);
  jet11_eta_branch = tree->GetBranch("jet11_eta");
  if (jet11_eta_branch) jet11_eta_branch->SetAddress(&jet11_eta_);
  jet12_eta_branch = tree->GetBranch("jet12_eta");
  if (jet12_eta_branch) jet12_eta_branch->SetAddress(&jet12_eta_);
  jet13_eta_branch = tree->GetBranch("jet13_eta");
  if (jet13_eta_branch) jet13_eta_branch->SetAddress(&jet13_eta_);
  jet14_eta_branch = tree->GetBranch("jet14_eta");
  if (jet14_eta_branch) jet14_eta_branch->SetAddress(&jet14_eta_);
  jet15_eta_branch = tree->GetBranch("jet15_eta");
  if (jet15_eta_branch) jet15_eta_branch->SetAddress(&jet15_eta_);
  jet1_phi_branch = tree->GetBranch("jet1_phi");
  if (jet1_phi_branch) jet1_phi_branch->SetAddress(&jet1_phi_);
  jet2_phi_branch = tree->GetBranch("jet2_phi");
  if (jet2_phi_branch) jet2_phi_branch->SetAddress(&jet2_phi_);
  jet3_phi_branch = tree->GetBranch("jet3_phi");
  if (jet3_phi_branch) jet3_phi_branch->SetAddress(&jet3_phi_);
  jet4_phi_branch = tree->GetBranch("jet4_phi");
  if (jet4_phi_branch) jet4_phi_branch->SetAddress(&jet4_phi_);
  jet5_phi_branch = tree->GetBranch("jet5_phi");
  if (jet5_phi_branch) jet5_phi_branch->SetAddress(&jet5_phi_);
  jet6_phi_branch = tree->GetBranch("jet6_phi");
  if (jet6_phi_branch) jet6_phi_branch->SetAddress(&jet6_phi_);
  jet7_phi_branch = tree->GetBranch("jet7_phi");
  if (jet7_phi_branch) jet7_phi_branch->SetAddress(&jet7_phi_);
  jet8_phi_branch = tree->GetBranch("jet8_phi");
  if (jet8_phi_branch) jet8_phi_branch->SetAddress(&jet8_phi_);
  jet9_phi_branch = tree->GetBranch("jet9_phi");
  if (jet9_phi_branch) jet9_phi_branch->SetAddress(&jet9_phi_);
  jet10_phi_branch = tree->GetBranch("jet10_phi");
  if (jet10_phi_branch) jet10_phi_branch->SetAddress(&jet10_phi_);
  jet11_phi_branch = tree->GetBranch("jet11_phi");
  if (jet11_phi_branch) jet11_phi_branch->SetAddress(&jet11_phi_);
  jet12_phi_branch = tree->GetBranch("jet12_phi");
  if (jet12_phi_branch) jet12_phi_branch->SetAddress(&jet12_phi_);
  jet13_phi_branch = tree->GetBranch("jet13_phi");
  if (jet13_phi_branch) jet13_phi_branch->SetAddress(&jet13_phi_);
  jet14_phi_branch = tree->GetBranch("jet14_phi");
  if (jet14_phi_branch) jet14_phi_branch->SetAddress(&jet14_phi_);
  jet15_phi_branch = tree->GetBranch("jet15_phi");
  if (jet15_phi_branch) jet15_phi_branch->SetAddress(&jet15_phi_);
  jet1_e_branch = tree->GetBranch("jet1_e");
  if (jet1_e_branch) jet1_e_branch->SetAddress(&jet1_e_);
  jet2_e_branch = tree->GetBranch("jet2_e");
  if (jet2_e_branch) jet2_e_branch->SetAddress(&jet2_e_);
  jet3_e_branch = tree->GetBranch("jet3_e");
  if (jet3_e_branch) jet3_e_branch->SetAddress(&jet3_e_);
  jet4_e_branch = tree->GetBranch("jet4_e");
  if (jet4_e_branch) jet4_e_branch->SetAddress(&jet4_e_);
  jet5_e_branch = tree->GetBranch("jet5_e");
  if (jet5_e_branch) jet5_e_branch->SetAddress(&jet5_e_);
  jet6_e_branch = tree->GetBranch("jet6_e");
  if (jet6_e_branch) jet6_e_branch->SetAddress(&jet6_e_);
  jet7_e_branch = tree->GetBranch("jet7_e");
  if (jet7_e_branch) jet7_e_branch->SetAddress(&jet7_e_);
  jet8_e_branch = tree->GetBranch("jet8_e");
  if (jet8_e_branch) jet8_e_branch->SetAddress(&jet8_e_);
  jet9_e_branch = tree->GetBranch("jet9_e");
  if (jet9_e_branch) jet9_e_branch->SetAddress(&jet9_e_);
  jet10_e_branch = tree->GetBranch("jet10_e");
  if (jet10_e_branch) jet10_e_branch->SetAddress(&jet10_e_);
  jet11_e_branch = tree->GetBranch("jet11_e");
  if (jet11_e_branch) jet11_e_branch->SetAddress(&jet11_e_);
  jet12_e_branch = tree->GetBranch("jet12_e");
  if (jet12_e_branch) jet12_e_branch->SetAddress(&jet12_e_);
  jet13_e_branch = tree->GetBranch("jet13_e");
  if (jet13_e_branch) jet13_e_branch->SetAddress(&jet13_e_);
  jet14_e_branch = tree->GetBranch("jet14_e");
  if (jet14_e_branch) jet14_e_branch->SetAddress(&jet14_e_);
  jet15_e_branch = tree->GetBranch("jet15_e");
  if (jet15_e_branch) jet15_e_branch->SetAddress(&jet15_e_);
  jet1_discr_branch = tree->GetBranch("jet1_discr");
  if (jet1_discr_branch) jet1_discr_branch->SetAddress(&jet1_discr_);
  jet2_discr_branch = tree->GetBranch("jet2_discr");
  if (jet2_discr_branch) jet2_discr_branch->SetAddress(&jet2_discr_);
  jet3_discr_branch = tree->GetBranch("jet3_discr");
  if (jet3_discr_branch) jet3_discr_branch->SetAddress(&jet3_discr_);
  jet4_discr_branch = tree->GetBranch("jet4_discr");
  if (jet4_discr_branch) jet4_discr_branch->SetAddress(&jet4_discr_);
  jet5_discr_branch = tree->GetBranch("jet5_discr");
  if (jet5_discr_branch) jet5_discr_branch->SetAddress(&jet5_discr_);
  jet6_discr_branch = tree->GetBranch("jet6_discr");
  if (jet6_discr_branch) jet6_discr_branch->SetAddress(&jet6_discr_);
  jet7_discr_branch = tree->GetBranch("jet7_discr");
  if (jet7_discr_branch) jet7_discr_branch->SetAddress(&jet7_discr_);
  jet8_discr_branch = tree->GetBranch("jet8_discr");
  if (jet8_discr_branch) jet8_discr_branch->SetAddress(&jet8_discr_);
  jet9_discr_branch = tree->GetBranch("jet9_discr");
  if (jet9_discr_branch) jet9_discr_branch->SetAddress(&jet9_discr_);
  jet10_discr_branch = tree->GetBranch("jet10_discr");
  if (jet10_discr_branch) jet10_discr_branch->SetAddress(&jet10_discr_);
  jet11_discr_branch = tree->GetBranch("jet11_discr");
  if (jet11_discr_branch) jet11_discr_branch->SetAddress(&jet11_discr_);
  jet12_discr_branch = tree->GetBranch("jet12_discr");
  if (jet12_discr_branch) jet12_discr_branch->SetAddress(&jet12_discr_);
  jet13_discr_branch = tree->GetBranch("jet13_discr");
  if (jet13_discr_branch) jet13_discr_branch->SetAddress(&jet13_discr_);
  jet14_discr_branch = tree->GetBranch("jet14_discr");
  if (jet14_discr_branch) jet14_discr_branch->SetAddress(&jet14_discr_);
  jet15_discr_branch = tree->GetBranch("jet15_discr");
  if (jet15_discr_branch) jet15_discr_branch->SetAddress(&jet15_discr_);
  recoMET_pt_branch = tree->GetBranch("recoMET_pt");
  if (recoMET_pt_branch) recoMET_pt_branch->SetAddress(&recoMET_pt_);
  recoMET_eta_branch = tree->GetBranch("recoMET_eta");
  if (recoMET_eta_branch) recoMET_eta_branch->SetAddress(&recoMET_eta_);
  recoMET_phi_branch = tree->GetBranch("recoMET_phi");
  if (recoMET_phi_branch) recoMET_phi_branch->SetAddress(&recoMET_phi_);
  recoMET_e_branch = tree->GetBranch("recoMET_e");
  if (recoMET_e_branch) recoMET_e_branch->SetAddress(&recoMET_e_);
  solvedMET_pt_branch = tree->GetBranch("solvedMET_pt");
  if (solvedMET_pt_branch) solvedMET_pt_branch->SetAddress(&solvedMET_pt_);
  solvedMET_eta_branch = tree->GetBranch("solvedMET_eta");
  if (solvedMET_eta_branch) solvedMET_eta_branch->SetAddress(&solvedMET_eta_);
  solvedMET_phi_branch = tree->GetBranch("solvedMET_phi");
  if (solvedMET_phi_branch) solvedMET_phi_branch->SetAddress(&solvedMET_phi_);
  solvedMET_e_branch = tree->GetBranch("solvedMET_e");
  if (solvedMET_e_branch) solvedMET_e_branch->SetAddress(&solvedMET_e_);
  dr_leadphobjet_branch = tree->GetBranch("dr_leadphobjet");
  if (dr_leadphobjet_branch) dr_leadphobjet_branch->SetAddress(&dr_leadphobjet_);
  dr_leptonfwdjet_branch = tree->GetBranch("dr_leptonfwdjet");
  if (dr_leptonfwdjet_branch) dr_leptonfwdjet_branch->SetAddress(&dr_leptonfwdjet_);
  top_mt_branch = tree->GetBranch("top_mt");
  if (top_mt_branch) top_mt_branch->SetAddress(&top_mt_);
  top_mass_branch = tree->GetBranch("top_mass");
  if (top_mass_branch) top_mass_branch->SetAddress(&top_mass_);
  HT_branch = tree->GetBranch("HT");
  if (HT_branch) HT_branch->SetAddress(&HT_);
  gen_parton1_pt_branch = tree->GetBranch("gen_parton1_pt");
  if (gen_parton1_pt_branch) gen_parton1_pt_branch->SetAddress(&gen_parton1_pt_);
  gen_parton2_pt_branch = tree->GetBranch("gen_parton2_pt");
  if (gen_parton2_pt_branch) gen_parton2_pt_branch->SetAddress(&gen_parton2_pt_);
  gen_parton3_pt_branch = tree->GetBranch("gen_parton3_pt");
  if (gen_parton3_pt_branch) gen_parton3_pt_branch->SetAddress(&gen_parton3_pt_);
  gen_parton4_pt_branch = tree->GetBranch("gen_parton4_pt");
  if (gen_parton4_pt_branch) gen_parton4_pt_branch->SetAddress(&gen_parton4_pt_);
  gen_parton5_pt_branch = tree->GetBranch("gen_parton5_pt");
  if (gen_parton5_pt_branch) gen_parton5_pt_branch->SetAddress(&gen_parton5_pt_);
  gen_parton6_pt_branch = tree->GetBranch("gen_parton6_pt");
  if (gen_parton6_pt_branch) gen_parton6_pt_branch->SetAddress(&gen_parton6_pt_);
  gen_parton7_pt_branch = tree->GetBranch("gen_parton7_pt");
  if (gen_parton7_pt_branch) gen_parton7_pt_branch->SetAddress(&gen_parton7_pt_);
  gen_parton8_pt_branch = tree->GetBranch("gen_parton8_pt");
  if (gen_parton8_pt_branch) gen_parton8_pt_branch->SetAddress(&gen_parton8_pt_);
  gen_parton9_pt_branch = tree->GetBranch("gen_parton9_pt");
  if (gen_parton9_pt_branch) gen_parton9_pt_branch->SetAddress(&gen_parton9_pt_);
  gen_parton10_pt_branch = tree->GetBranch("gen_parton10_pt");
  if (gen_parton10_pt_branch) gen_parton10_pt_branch->SetAddress(&gen_parton10_pt_);
  gen_parton1_eta_branch = tree->GetBranch("gen_parton1_eta");
  if (gen_parton1_eta_branch) gen_parton1_eta_branch->SetAddress(&gen_parton1_eta_);
  gen_parton2_eta_branch = tree->GetBranch("gen_parton2_eta");
  if (gen_parton2_eta_branch) gen_parton2_eta_branch->SetAddress(&gen_parton2_eta_);
  gen_parton3_eta_branch = tree->GetBranch("gen_parton3_eta");
  if (gen_parton3_eta_branch) gen_parton3_eta_branch->SetAddress(&gen_parton3_eta_);
  gen_parton4_eta_branch = tree->GetBranch("gen_parton4_eta");
  if (gen_parton4_eta_branch) gen_parton4_eta_branch->SetAddress(&gen_parton4_eta_);
  gen_parton5_eta_branch = tree->GetBranch("gen_parton5_eta");
  if (gen_parton5_eta_branch) gen_parton5_eta_branch->SetAddress(&gen_parton5_eta_);
  gen_parton6_eta_branch = tree->GetBranch("gen_parton6_eta");
  if (gen_parton6_eta_branch) gen_parton6_eta_branch->SetAddress(&gen_parton6_eta_);
  gen_parton7_eta_branch = tree->GetBranch("gen_parton7_eta");
  if (gen_parton7_eta_branch) gen_parton7_eta_branch->SetAddress(&gen_parton7_eta_);
  gen_parton8_eta_branch = tree->GetBranch("gen_parton8_eta");
  if (gen_parton8_eta_branch) gen_parton8_eta_branch->SetAddress(&gen_parton8_eta_);
  gen_parton9_eta_branch = tree->GetBranch("gen_parton9_eta");
  if (gen_parton9_eta_branch) gen_parton9_eta_branch->SetAddress(&gen_parton9_eta_);
  gen_parton10_eta_branch = tree->GetBranch("gen_parton10_eta");
  if (gen_parton10_eta_branch) gen_parton10_eta_branch->SetAddress(&gen_parton10_eta_);
  gen_parton1_phi_branch = tree->GetBranch("gen_parton1_phi");
  if (gen_parton1_phi_branch) gen_parton1_phi_branch->SetAddress(&gen_parton1_phi_);
  gen_parton2_phi_branch = tree->GetBranch("gen_parton2_phi");
  if (gen_parton2_phi_branch) gen_parton2_phi_branch->SetAddress(&gen_parton2_phi_);
  gen_parton3_phi_branch = tree->GetBranch("gen_parton3_phi");
  if (gen_parton3_phi_branch) gen_parton3_phi_branch->SetAddress(&gen_parton3_phi_);
  gen_parton4_phi_branch = tree->GetBranch("gen_parton4_phi");
  if (gen_parton4_phi_branch) gen_parton4_phi_branch->SetAddress(&gen_parton4_phi_);
  gen_parton5_phi_branch = tree->GetBranch("gen_parton5_phi");
  if (gen_parton5_phi_branch) gen_parton5_phi_branch->SetAddress(&gen_parton5_phi_);
  gen_parton6_phi_branch = tree->GetBranch("gen_parton6_phi");
  if (gen_parton6_phi_branch) gen_parton6_phi_branch->SetAddress(&gen_parton6_phi_);
  gen_parton7_phi_branch = tree->GetBranch("gen_parton7_phi");
  if (gen_parton7_phi_branch) gen_parton7_phi_branch->SetAddress(&gen_parton7_phi_);
  gen_parton8_phi_branch = tree->GetBranch("gen_parton8_phi");
  if (gen_parton8_phi_branch) gen_parton8_phi_branch->SetAddress(&gen_parton8_phi_);
  gen_parton9_phi_branch = tree->GetBranch("gen_parton9_phi");
  if (gen_parton9_phi_branch) gen_parton9_phi_branch->SetAddress(&gen_parton9_phi_);
  gen_parton10_phi_branch = tree->GetBranch("gen_parton10_phi");
  if (gen_parton10_phi_branch) gen_parton10_phi_branch->SetAddress(&gen_parton10_phi_);
  gen_parton1_mass_branch = tree->GetBranch("gen_parton1_mass");
  if (gen_parton1_mass_branch) gen_parton1_mass_branch->SetAddress(&gen_parton1_mass_);
  gen_parton2_mass_branch = tree->GetBranch("gen_parton2_mass");
  if (gen_parton2_mass_branch) gen_parton2_mass_branch->SetAddress(&gen_parton2_mass_);
  gen_parton3_mass_branch = tree->GetBranch("gen_parton3_mass");
  if (gen_parton3_mass_branch) gen_parton3_mass_branch->SetAddress(&gen_parton3_mass_);
  gen_parton4_mass_branch = tree->GetBranch("gen_parton4_mass");
  if (gen_parton4_mass_branch) gen_parton4_mass_branch->SetAddress(&gen_parton4_mass_);
  gen_parton5_mass_branch = tree->GetBranch("gen_parton5_mass");
  if (gen_parton5_mass_branch) gen_parton5_mass_branch->SetAddress(&gen_parton5_mass_);
  gen_parton6_mass_branch = tree->GetBranch("gen_parton6_mass");
  if (gen_parton6_mass_branch) gen_parton6_mass_branch->SetAddress(&gen_parton6_mass_);
  gen_parton7_mass_branch = tree->GetBranch("gen_parton7_mass");
  if (gen_parton7_mass_branch) gen_parton7_mass_branch->SetAddress(&gen_parton7_mass_);
  gen_parton8_mass_branch = tree->GetBranch("gen_parton8_mass");
  if (gen_parton8_mass_branch) gen_parton8_mass_branch->SetAddress(&gen_parton8_mass_);
  gen_parton9_mass_branch = tree->GetBranch("gen_parton9_mass");
  if (gen_parton9_mass_branch) gen_parton9_mass_branch->SetAddress(&gen_parton9_mass_);
  gen_parton10_mass_branch = tree->GetBranch("gen_parton10_mass");
  if (gen_parton10_mass_branch) gen_parton10_mass_branch->SetAddress(&gen_parton10_mass_);
  gen_parton1_pdgId_branch = tree->GetBranch("gen_parton1_pdgId");
  if (gen_parton1_pdgId_branch) gen_parton1_pdgId_branch->SetAddress(&gen_parton1_pdgId_);
  gen_parton2_pdgId_branch = tree->GetBranch("gen_parton2_pdgId");
  if (gen_parton2_pdgId_branch) gen_parton2_pdgId_branch->SetAddress(&gen_parton2_pdgId_);
  gen_parton3_pdgId_branch = tree->GetBranch("gen_parton3_pdgId");
  if (gen_parton3_pdgId_branch) gen_parton3_pdgId_branch->SetAddress(&gen_parton3_pdgId_);
  gen_parton4_pdgId_branch = tree->GetBranch("gen_parton4_pdgId");
  if (gen_parton4_pdgId_branch) gen_parton4_pdgId_branch->SetAddress(&gen_parton4_pdgId_);
  gen_parton5_pdgId_branch = tree->GetBranch("gen_parton5_pdgId");
  if (gen_parton5_pdgId_branch) gen_parton5_pdgId_branch->SetAddress(&gen_parton5_pdgId_);
  gen_parton6_pdgId_branch = tree->GetBranch("gen_parton6_pdgId");
  if (gen_parton6_pdgId_branch) gen_parton6_pdgId_branch->SetAddress(&gen_parton6_pdgId_);
  gen_parton7_pdgId_branch = tree->GetBranch("gen_parton7_pdgId");
  if (gen_parton7_pdgId_branch) gen_parton7_pdgId_branch->SetAddress(&gen_parton7_pdgId_);
  gen_parton8_pdgId_branch = tree->GetBranch("gen_parton8_pdgId");
  if (gen_parton8_pdgId_branch) gen_parton8_pdgId_branch->SetAddress(&gen_parton8_pdgId_);
  gen_parton9_pdgId_branch = tree->GetBranch("gen_parton9_pdgId");
  if (gen_parton9_pdgId_branch) gen_parton9_pdgId_branch->SetAddress(&gen_parton9_pdgId_);
  gen_parton10_pdgId_branch = tree->GetBranch("gen_parton10_pdgId");
  if (gen_parton10_pdgId_branch) gen_parton10_pdgId_branch->SetAddress(&gen_parton10_pdgId_);
  gen_parton1_status_branch = tree->GetBranch("gen_parton1_status");
  if (gen_parton1_status_branch) gen_parton1_status_branch->SetAddress(&gen_parton1_status_);
  gen_parton2_status_branch = tree->GetBranch("gen_parton2_status");
  if (gen_parton2_status_branch) gen_parton2_status_branch->SetAddress(&gen_parton2_status_);
  gen_parton3_status_branch = tree->GetBranch("gen_parton3_status");
  if (gen_parton3_status_branch) gen_parton3_status_branch->SetAddress(&gen_parton3_status_);
  gen_parton4_status_branch = tree->GetBranch("gen_parton4_status");
  if (gen_parton4_status_branch) gen_parton4_status_branch->SetAddress(&gen_parton4_status_);
  gen_parton5_status_branch = tree->GetBranch("gen_parton5_status");
  if (gen_parton5_status_branch) gen_parton5_status_branch->SetAddress(&gen_parton5_status_);
  gen_parton6_status_branch = tree->GetBranch("gen_parton6_status");
  if (gen_parton6_status_branch) gen_parton6_status_branch->SetAddress(&gen_parton6_status_);
  gen_parton7_status_branch = tree->GetBranch("gen_parton7_status");
  if (gen_parton7_status_branch) gen_parton7_status_branch->SetAddress(&gen_parton7_status_);
  gen_parton8_status_branch = tree->GetBranch("gen_parton8_status");
  if (gen_parton8_status_branch) gen_parton8_status_branch->SetAddress(&gen_parton8_status_);
  gen_parton9_status_branch = tree->GetBranch("gen_parton9_status");
  if (gen_parton9_status_branch) gen_parton9_status_branch->SetAddress(&gen_parton9_status_);
  gen_parton10_status_branch = tree->GetBranch("gen_parton10_status");
  if (gen_parton10_status_branch) gen_parton10_status_branch->SetAddress(&gen_parton10_status_);
  genMatched_jet0_pdgId_branch = tree->GetBranch("genMatched_jet0_pdgId");
  if (genMatched_jet0_pdgId_branch) genMatched_jet0_pdgId_branch->SetAddress(&genMatched_jet0_pdgId_);
  genMatched_jet1_pdgId_branch = tree->GetBranch("genMatched_jet1_pdgId");
  if (genMatched_jet1_pdgId_branch) genMatched_jet1_pdgId_branch->SetAddress(&genMatched_jet1_pdgId_);
  genMatched_jet2_pdgId_branch = tree->GetBranch("genMatched_jet2_pdgId");
  if (genMatched_jet2_pdgId_branch) genMatched_jet2_pdgId_branch->SetAddress(&genMatched_jet2_pdgId_);
  genMatched_jet0_index_branch = tree->GetBranch("genMatched_jet0_index");
  if (genMatched_jet0_index_branch) genMatched_jet0_index_branch->SetAddress(&genMatched_jet0_index_);
  genMatched_jet1_index_branch = tree->GetBranch("genMatched_jet1_index");
  if (genMatched_jet1_index_branch) genMatched_jet1_index_branch->SetAddress(&genMatched_jet1_index_);
  genMatched_jet2_index_branch = tree->GetBranch("genMatched_jet2_index");
  if (genMatched_jet2_index_branch) genMatched_jet2_index_branch->SetAddress(&genMatched_jet2_index_);
  genMatched_jet0_deltaR_branch = tree->GetBranch("genMatched_jet0_deltaR");
  if (genMatched_jet0_deltaR_branch) genMatched_jet0_deltaR_branch->SetAddress(&genMatched_jet0_deltaR_);
  genMatched_jet1_deltaR_branch = tree->GetBranch("genMatched_jet1_deltaR");
  if (genMatched_jet1_deltaR_branch) genMatched_jet1_deltaR_branch->SetAddress(&genMatched_jet1_deltaR_);
  genMatched_jet2_deltaR_branch = tree->GetBranch("genMatched_jet2_deltaR");
  if (genMatched_jet2_deltaR_branch) genMatched_jet2_deltaR_branch->SetAddress(&genMatched_jet2_deltaR_);
  genMET_pt_branch = tree->GetBranch("genMET_pt");
  if (genMET_pt_branch) genMET_pt_branch->SetAddress(&genMET_pt_);
  genMET_eta_branch = tree->GetBranch("genMET_eta");
  if (genMET_eta_branch) genMET_eta_branch->SetAddress(&genMET_eta_);
  genMET_phi_branch = tree->GetBranch("genMET_phi");
  if (genMET_phi_branch) genMET_phi_branch->SetAddress(&genMET_phi_);
  genMET_e_branch = tree->GetBranch("genMET_e");
  if (genMET_e_branch) genMET_e_branch->SetAddress(&genMET_e_);
  promptGenMET_pt_branch = tree->GetBranch("promptGenMET_pt");
  if (promptGenMET_pt_branch) promptGenMET_pt_branch->SetAddress(&promptGenMET_pt_);
  promptGenMET_eta_branch = tree->GetBranch("promptGenMET_eta");
  if (promptGenMET_eta_branch) promptGenMET_eta_branch->SetAddress(&promptGenMET_eta_);
  promptGenMET_phi_branch = tree->GetBranch("promptGenMET_phi");
  if (promptGenMET_phi_branch) promptGenMET_phi_branch->SetAddress(&promptGenMET_phi_);
  promptGenMET_e_branch = tree->GetBranch("promptGenMET_e");
  if (promptGenMET_e_branch) promptGenMET_e_branch->SetAddress(&promptGenMET_e_);
  genMETTrue_pt_branch = tree->GetBranch("genMETTrue_pt");
  if (genMETTrue_pt_branch) genMETTrue_pt_branch->SetAddress(&genMETTrue_pt_);
  genMETTrue_eta_branch = tree->GetBranch("genMETTrue_eta");
  if (genMETTrue_eta_branch) genMETTrue_eta_branch->SetAddress(&genMETTrue_eta_);
  genMETTrue_phi_branch = tree->GetBranch("genMETTrue_phi");
  if (genMETTrue_phi_branch) genMETTrue_phi_branch->SetAddress(&genMETTrue_phi_);
  genMETTrue_e_branch = tree->GetBranch("genMETTrue_e");
  if (genMETTrue_e_branch) genMETTrue_e_branch->SetAddress(&genMETTrue_e_);
  rho_branch = tree->GetBranch("rho");
  if (rho_branch) rho_branch->SetAddress(&rho_);
  nvtx_branch = tree->GetBranch("nvtx");
  if (nvtx_branch) nvtx_branch->SetAddress(&nvtx_);
  event_branch = tree->GetBranch("event");
  if (event_branch) event_branch->SetAddress(&event_);
  lumi_branch = tree->GetBranch("lumi");
  if (lumi_branch) lumi_branch->SetAddress(&lumi_);
  processIndex_branch = tree->GetBranch("processIndex");
  if (processIndex_branch) processIndex_branch->SetAddress(&processIndex_);
  run_branch = tree->GetBranch("run");
  if (run_branch) run_branch->SetAddress(&run_);
  npu_branch = tree->GetBranch("npu");
  if (npu_branch) npu_branch->SetAddress(&npu_);
  puweight_branch = tree->GetBranch("puweight");
  if (puweight_branch) puweight_branch->SetAddress(&puweight_);

  tree->SetMakeClass(0);
}

void tprimetHHadronic::GetEntry(unsigned int idx) {
  // this only marks branches as not loaded, saving a lot of time
  index = idx;
  candidate_id_isLoaded = false;
  weight_isLoaded = false;
  CMS_hgg_mass_isLoaded = false;
  sigmaMoM_decorr_isLoaded = false;
  dZ_isLoaded = false;
  centralObjectWeight_isLoaded = false;
  vtxprob_isLoaded = false;
  ptbal_isLoaded = false;
  ptasym_isLoaded = false;
  logspt2_isLoaded = false;
  p2conv_isLoaded = false;
  nconv_isLoaded = false;
  vtxmva_isLoaded = false;
  vtxdz_isLoaded = false;
  vtx_x_isLoaded = false;
  vtx_y_isLoaded = false;
  vtx_z_isLoaded = false;
  dipho_sumpt_isLoaded = false;
  dipho_cosphi_isLoaded = false;
  dipho_mass_isLoaded = false;
  dipho_pt_isLoaded = false;
  dipho_phi_isLoaded = false;
  dipho_eta_isLoaded = false;
  dipho_e_isLoaded = false;
  dipho_PtoM_isLoaded = false;
  cosphi_isLoaded = false;
  sigmaMrvoM_isLoaded = false;
  sigmaMwvoM_isLoaded = false;
  dipho_leadPt_isLoaded = false;
  dipho_leadEt_isLoaded = false;
  dipho_leadEta_isLoaded = false;
  dipho_leadPhi_isLoaded = false;
  dipho_lead_sieie_isLoaded = false;
  dipho_lead_hoe_isLoaded = false;
  dipho_lead_sigmaEoE_isLoaded = false;
  dipho_lead_ptoM_isLoaded = false;
  dipho_leadR9_isLoaded = false;
  dipho_leadIDMVA_isLoaded = false;
  dipho_lead_elveto_isLoaded = false;
  dipho_lead_prompt_isLoaded = false;
  dipho_lead_chiso_isLoaded = false;
  dipho_lead_chisow_isLoaded = false;
  dipho_lead_phoiso_isLoaded = false;
  dipho_lead_phoiso04_isLoaded = false;
  dipho_lead_neutiso_isLoaded = false;
  dipho_lead_ecaliso03_isLoaded = false;
  dipho_lead_hcaliso03_isLoaded = false;
  dipho_lead_pfcluecal03_isLoaded = false;
  dipho_lead_pfcluhcal03_isLoaded = false;
  dipho_lead_trkiso03_isLoaded = false;
  dipho_lead_pfchiso2_isLoaded = false;
  dipho_lead_haspixelseed_isLoaded = false;
  dipho_lead_sieip_isLoaded = false;
  dipho_lead_etawidth_isLoaded = false;
  dipho_lead_phiwidth_isLoaded = false;
  dipho_lead_regrerr_isLoaded = false;
  dipho_lead_s4ratio_isLoaded = false;
  dipho_lead_effSigma_isLoaded = false;
  dipho_lead_scraw_isLoaded = false;
  dipho_lead_ese_isLoaded = false;
  dipho_subleadPt_isLoaded = false;
  dipho_subleadEt_isLoaded = false;
  dipho_subleadEta_isLoaded = false;
  dipho_subleadPhi_isLoaded = false;
  dipho_sublead_sieie_isLoaded = false;
  dipho_sublead_hoe_isLoaded = false;
  dipho_sublead_sigmaEoE_isLoaded = false;
  dipho_sublead_ptoM_isLoaded = false;
  dipho_subleadR9_isLoaded = false;
  dipho_subleadIDMVA_isLoaded = false;
  dipho_sublead_elveto_isLoaded = false;
  dipho_sulead_prompt_isLoaded = false;
  dipho_sublead_chiso_isLoaded = false;
  dipho_sublead_chisow_isLoaded = false;
  dipho_sublead_phoiso_isLoaded = false;
  dipho_sublead_phoiso04_isLoaded = false;
  dipho_sublead_neutiso_isLoaded = false;
  dipho_sublead_ecaliso03_isLoaded = false;
  dipho_sublead_hcaliso03_isLoaded = false;
  dipho_sublead_pfcluecal03_isLoaded = false;
  dipho_sublead_pfcluhcal03_isLoaded = false;
  dipho_sublead_trkiso03_isLoaded = false;
  dipho_sublead_pfchiso2_isLoaded = false;
  dipho_sublead_haspixelseed_isLoaded = false;
  dipho_sublead_sieip_isLoaded = false;
  dipho_sublead_etawidth_isLoaded = false;
  dipho_sublead_phiwidth_isLoaded = false;
  dipho_sublead_regrerr_isLoaded = false;
  dipho_sublead_s4ratio_isLoaded = false;
  dipho_sublead_effSigma_isLoaded = false;
  dipho_sublead_scraw_isLoaded = false;
  dipho_sublead_ese_isLoaded = false;
  LeptonType_isLoaded = false;
  n_ele_isLoaded = false;
  n_loose_ele_isLoaded = false;
  n_veto_ele_isLoaded = false;
  n_medium_ele_isLoaded = false;
  n_tight_ele_isLoaded = false;
  ele1_pt_isLoaded = false;
  ele2_pt_isLoaded = false;
  ele1_eta_isLoaded = false;
  ele2_eta_isLoaded = false;
  ele1_phi_isLoaded = false;
  ele2_phi_isLoaded = false;
  ele1_e_isLoaded = false;
  ele2_e_isLoaded = false;
  ele1_ch_isLoaded = false;
  ele2_ch_isLoaded = false;
  ele1_sigmaIetaIeta_isLoaded = false;
  ele2_sigmaIetaIeta_isLoaded = false;
  ele1_dEtaInSeed_isLoaded = false;
  ele2_dEtaInSeed_isLoaded = false;
  ele1_dPhiIn_isLoaded = false;
  ele2_dPhiIn_isLoaded = false;
  ele1_hOverE_isLoaded = false;
  ele2_hOverE_isLoaded = false;
  ele1_RelIsoEA_isLoaded = false;
  ele2_RelIsoEA_isLoaded = false;
  ele1_ooEmooP_isLoaded = false;
  ele2_ooEmooP_isLoaded = false;
  ele1_dxy_isLoaded = false;
  ele2_dxy_isLoaded = false;
  ele1_diphodxy_isLoaded = false;
  ele2_diphodxy_isLoaded = false;
  ele1_dz_isLoaded = false;
  ele2_dz_isLoaded = false;
  ele1_diphodz_isLoaded = false;
  ele2_diphodz_isLoaded = false;
  ele1_misHits_isLoaded = false;
  ele2_misHits_isLoaded = false;
  ele1_ConversionVeto_isLoaded = false;
  ele2_ConversionVeto_isLoaded = false;
  ele1_ChargedHadronPt_isLoaded = false;
  ele2_ChargedHadronPt_isLoaded = false;
  ele2_NeutralHadronEt_isLoaded = false;
  ele1_NeutralHadronEt_isLoaded = false;
  ele1_PhotonEt_isLoaded = false;
  ele2_PhotonEt_isLoaded = false;
  ele1_PassTight_isLoaded = false;
  ele2_PassTight_isLoaded = false;
  ele1_PassVeto_isLoaded = false;
  ele2_PassVeto_isLoaded = false;
  ele1_dPhiMET_isLoaded = false;
  ele2_dPhiMET_isLoaded = false;
  n_muons_isLoaded = false;
  n_LooseMu25_isLoaded = false;
  n_LooseMu15_isLoaded = false;
  n_TightMu25_isLoaded = false;
  n_TightMu15_isLoaded = false;
  n_MediumMu25_isLoaded = false;
  n_MediumMu15_isLoaded = false;
  muon1_pt_isLoaded = false;
  muon2_pt_isLoaded = false;
  muon1_eta_isLoaded = false;
  muon2_eta_isLoaded = false;
  muon1_phi_isLoaded = false;
  muon2_phi_isLoaded = false;
  muon1_e_isLoaded = false;
  muon2_e_isLoaded = false;
  muon1_ch_isLoaded = false;
  muon2_ch_isLoaded = false;
  muon1_iso_isLoaded = false;
  muon2_iso_isLoaded = false;
  muon1_chi2_isLoaded = false;
  muon2_chi2_isLoaded = false;
  muon1_mHits_isLoaded = false;
  muon2_mHits_isLoaded = false;
  muon1_mStations_isLoaded = false;
  muon2_mStations_isLoaded = false;
  muon1_dxy_isLoaded = false;
  muon2_dxy_isLoaded = false;
  muon1_diphodxy_isLoaded = false;
  muon2_diphodxy_isLoaded = false;
  muon1_dz_isLoaded = false;
  muon2_dz_isLoaded = false;
  muon1_diphodz_isLoaded = false;
  muon2_diphodz_isLoaded = false;
  muon1_pxHits_isLoaded = false;
  muon2_pxHits_isLoaded = false;
  muon1_tkLayers_isLoaded = false;
  muon2_tkLayers_isLoaded = false;
  muon1_PassTight_isLoaded = false;
  muon2_PassTight_isLoaded = false;
  muon1_dPhiMET_isLoaded = false;
  muon2_dPhiMET_isLoaded = false;
  n_fwdjets_isLoaded = false;
  fwdjet1_pt_isLoaded = false;
  fwdjet2_pt_isLoaded = false;
  fwdjet3_pt_isLoaded = false;
  fwdjet1_eta_isLoaded = false;
  fwdjet2_eta_isLoaded = false;
  fwdjet3_eta_isLoaded = false;
  fwdjet4_eta_isLoaded = false;
  fwdjet5_eta_isLoaded = false;
  fwdjet6_eta_isLoaded = false;
  fwdjet7_eta_isLoaded = false;
  fwdjet8_eta_isLoaded = false;
  fwdjet9_eta_isLoaded = false;
  fwdjet1_phi_isLoaded = false;
  fwdjet2_phi_isLoaded = false;
  fwdjet3_phi_isLoaded = false;
  fwdjet1_e_isLoaded = false;
  fwdjet2_e_isLoaded = false;
  fwdjet3_e_isLoaded = false;
  fwdjet1_discr_isLoaded = false;
  n_M_bjets_isLoaded = false;
  n_L_bjets_isLoaded = false;
  n_T_bjets_isLoaded = false;
  n_bjets_isLoaded = false;
  bjet1_pt_isLoaded = false;
  bjet2_pt_isLoaded = false;
  bjet3_pt_isLoaded = false;
  bjet1_eta_isLoaded = false;
  bjet2_eta_isLoaded = false;
  bjet3_eta_isLoaded = false;
  bjet1_phi_isLoaded = false;
  bjet2_phi_isLoaded = false;
  bjet3_phi_isLoaded = false;
  bjet1_e_isLoaded = false;
  bjet2_e_isLoaded = false;
  bjet3_e_isLoaded = false;
  bjet1_discr_isLoaded = false;
  bjet2_discr_isLoaded = false;
  bjet3_discr_isLoaded = false;
  bjet4_discr_isLoaded = false;
  n_jets_isLoaded = false;
  jet1_pt_isLoaded = false;
  jet2_pt_isLoaded = false;
  jet3_pt_isLoaded = false;
  jet4_pt_isLoaded = false;
  jet5_pt_isLoaded = false;
  jet6_pt_isLoaded = false;
  jet7_pt_isLoaded = false;
  jet8_pt_isLoaded = false;
  jet9_pt_isLoaded = false;
  jet10_pt_isLoaded = false;
  jet11_pt_isLoaded = false;
  jet12_pt_isLoaded = false;
  jet13_pt_isLoaded = false;
  jet14_pt_isLoaded = false;
  jet15_pt_isLoaded = false;
  jet1_eta_isLoaded = false;
  jet2_eta_isLoaded = false;
  jet3_eta_isLoaded = false;
  jet4_eta_isLoaded = false;
  jet5_eta_isLoaded = false;
  jet6_eta_isLoaded = false;
  jet7_eta_isLoaded = false;
  jet8_eta_isLoaded = false;
  jet9_eta_isLoaded = false;
  jet10_eta_isLoaded = false;
  jet11_eta_isLoaded = false;
  jet12_eta_isLoaded = false;
  jet13_eta_isLoaded = false;
  jet14_eta_isLoaded = false;
  jet15_eta_isLoaded = false;
  jet1_phi_isLoaded = false;
  jet2_phi_isLoaded = false;
  jet3_phi_isLoaded = false;
  jet4_phi_isLoaded = false;
  jet5_phi_isLoaded = false;
  jet6_phi_isLoaded = false;
  jet7_phi_isLoaded = false;
  jet8_phi_isLoaded = false;
  jet9_phi_isLoaded = false;
  jet10_phi_isLoaded = false;
  jet11_phi_isLoaded = false;
  jet12_phi_isLoaded = false;
  jet13_phi_isLoaded = false;
  jet14_phi_isLoaded = false;
  jet15_phi_isLoaded = false;
  jet1_e_isLoaded = false;
  jet2_e_isLoaded = false;
  jet3_e_isLoaded = false;
  jet4_e_isLoaded = false;
  jet5_e_isLoaded = false;
  jet6_e_isLoaded = false;
  jet7_e_isLoaded = false;
  jet8_e_isLoaded = false;
  jet9_e_isLoaded = false;
  jet10_e_isLoaded = false;
  jet11_e_isLoaded = false;
  jet12_e_isLoaded = false;
  jet13_e_isLoaded = false;
  jet14_e_isLoaded = false;
  jet15_e_isLoaded = false;
  jet1_discr_isLoaded = false;
  jet2_discr_isLoaded = false;
  jet3_discr_isLoaded = false;
  jet4_discr_isLoaded = false;
  jet5_discr_isLoaded = false;
  jet6_discr_isLoaded = false;
  jet7_discr_isLoaded = false;
  jet8_discr_isLoaded = false;
  jet9_discr_isLoaded = false;
  jet10_discr_isLoaded = false;
  jet11_discr_isLoaded = false;
  jet12_discr_isLoaded = false;
  jet13_discr_isLoaded = false;
  jet14_discr_isLoaded = false;
  jet15_discr_isLoaded = false;
  recoMET_pt_isLoaded = false;
  recoMET_eta_isLoaded = false;
  recoMET_phi_isLoaded = false;
  recoMET_e_isLoaded = false;
  solvedMET_pt_isLoaded = false;
  solvedMET_eta_isLoaded = false;
  solvedMET_phi_isLoaded = false;
  solvedMET_e_isLoaded = false;
  dr_leadphobjet_isLoaded = false;
  dr_leptonfwdjet_isLoaded = false;
  top_mt_isLoaded = false;
  top_mass_isLoaded = false;
  HT_isLoaded = false;
  gen_parton1_pt_isLoaded = false;
  gen_parton2_pt_isLoaded = false;
  gen_parton3_pt_isLoaded = false;
  gen_parton4_pt_isLoaded = false;
  gen_parton5_pt_isLoaded = false;
  gen_parton6_pt_isLoaded = false;
  gen_parton7_pt_isLoaded = false;
  gen_parton8_pt_isLoaded = false;
  gen_parton9_pt_isLoaded = false;
  gen_parton10_pt_isLoaded = false;
  gen_parton1_eta_isLoaded = false;
  gen_parton2_eta_isLoaded = false;
  gen_parton3_eta_isLoaded = false;
  gen_parton4_eta_isLoaded = false;
  gen_parton5_eta_isLoaded = false;
  gen_parton6_eta_isLoaded = false;
  gen_parton7_eta_isLoaded = false;
  gen_parton8_eta_isLoaded = false;
  gen_parton9_eta_isLoaded = false;
  gen_parton10_eta_isLoaded = false;
  gen_parton1_phi_isLoaded = false;
  gen_parton2_phi_isLoaded = false;
  gen_parton3_phi_isLoaded = false;
  gen_parton4_phi_isLoaded = false;
  gen_parton5_phi_isLoaded = false;
  gen_parton6_phi_isLoaded = false;
  gen_parton7_phi_isLoaded = false;
  gen_parton8_phi_isLoaded = false;
  gen_parton9_phi_isLoaded = false;
  gen_parton10_phi_isLoaded = false;
  gen_parton1_mass_isLoaded = false;
  gen_parton2_mass_isLoaded = false;
  gen_parton3_mass_isLoaded = false;
  gen_parton4_mass_isLoaded = false;
  gen_parton5_mass_isLoaded = false;
  gen_parton6_mass_isLoaded = false;
  gen_parton7_mass_isLoaded = false;
  gen_parton8_mass_isLoaded = false;
  gen_parton9_mass_isLoaded = false;
  gen_parton10_mass_isLoaded = false;
  gen_parton1_pdgId_isLoaded = false;
  gen_parton2_pdgId_isLoaded = false;
  gen_parton3_pdgId_isLoaded = false;
  gen_parton4_pdgId_isLoaded = false;
  gen_parton5_pdgId_isLoaded = false;
  gen_parton6_pdgId_isLoaded = false;
  gen_parton7_pdgId_isLoaded = false;
  gen_parton8_pdgId_isLoaded = false;
  gen_parton9_pdgId_isLoaded = false;
  gen_parton10_pdgId_isLoaded = false;
  gen_parton1_status_isLoaded = false;
  gen_parton2_status_isLoaded = false;
  gen_parton3_status_isLoaded = false;
  gen_parton4_status_isLoaded = false;
  gen_parton5_status_isLoaded = false;
  gen_parton6_status_isLoaded = false;
  gen_parton7_status_isLoaded = false;
  gen_parton8_status_isLoaded = false;
  gen_parton9_status_isLoaded = false;
  gen_parton10_status_isLoaded = false;
  genMatched_jet0_pdgId_isLoaded = false;
  genMatched_jet1_pdgId_isLoaded = false;
  genMatched_jet2_pdgId_isLoaded = false;
  genMatched_jet0_index_isLoaded = false;
  genMatched_jet1_index_isLoaded = false;
  genMatched_jet2_index_isLoaded = false;
  genMatched_jet0_deltaR_isLoaded = false;
  genMatched_jet1_deltaR_isLoaded = false;
  genMatched_jet2_deltaR_isLoaded = false;
  genMET_pt_isLoaded = false;
  genMET_eta_isLoaded = false;
  genMET_phi_isLoaded = false;
  genMET_e_isLoaded = false;
  promptGenMET_pt_isLoaded = false;
  promptGenMET_eta_isLoaded = false;
  promptGenMET_phi_isLoaded = false;
  promptGenMET_e_isLoaded = false;
  genMETTrue_pt_isLoaded = false;
  genMETTrue_eta_isLoaded = false;
  genMETTrue_phi_isLoaded = false;
  genMETTrue_e_isLoaded = false;
  rho_isLoaded = false;
  nvtx_isLoaded = false;
  event_isLoaded = false;
  lumi_isLoaded = false;
  processIndex_isLoaded = false;
  run_isLoaded = false;
  npu_isLoaded = false;
  puweight_isLoaded = false;
}

void tprimetHHadronic::LoadAllBranches() {
  // load all branches
  if (candidate_id_branch != 0) candidate_id();
  if (weight_branch != 0) weight();
  if (CMS_hgg_mass_branch != 0) CMS_hgg_mass();
  if (sigmaMoM_decorr_branch != 0) sigmaMoM_decorr();
  if (dZ_branch != 0) dZ();
  if (centralObjectWeight_branch != 0) centralObjectWeight();
  if (vtxprob_branch != 0) vtxprob();
  if (ptbal_branch != 0) ptbal();
  if (ptasym_branch != 0) ptasym();
  if (logspt2_branch != 0) logspt2();
  if (p2conv_branch != 0) p2conv();
  if (nconv_branch != 0) nconv();
  if (vtxmva_branch != 0) vtxmva();
  if (vtxdz_branch != 0) vtxdz();
  if (vtx_x_branch != 0) vtx_x();
  if (vtx_y_branch != 0) vtx_y();
  if (vtx_z_branch != 0) vtx_z();
  if (dipho_sumpt_branch != 0) dipho_sumpt();
  if (dipho_cosphi_branch != 0) dipho_cosphi();
  if (dipho_mass_branch != 0) dipho_mass();
  if (dipho_pt_branch != 0) dipho_pt();
  if (dipho_phi_branch != 0) dipho_phi();
  if (dipho_eta_branch != 0) dipho_eta();
  if (dipho_e_branch != 0) dipho_e();
  if (dipho_PtoM_branch != 0) dipho_PtoM();
  if (cosphi_branch != 0) cosphi();
  if (sigmaMrvoM_branch != 0) sigmaMrvoM();
  if (sigmaMwvoM_branch != 0) sigmaMwvoM();
  if (dipho_leadPt_branch != 0) dipho_leadPt();
  if (dipho_leadEt_branch != 0) dipho_leadEt();
  if (dipho_leadEta_branch != 0) dipho_leadEta();
  if (dipho_leadPhi_branch != 0) dipho_leadPhi();
  if (dipho_lead_sieie_branch != 0) dipho_lead_sieie();
  if (dipho_lead_hoe_branch != 0) dipho_lead_hoe();
  if (dipho_lead_sigmaEoE_branch != 0) dipho_lead_sigmaEoE();
  if (dipho_lead_ptoM_branch != 0) dipho_lead_ptoM();
  if (dipho_leadR9_branch != 0) dipho_leadR9();
  if (dipho_leadIDMVA_branch != 0) dipho_leadIDMVA();
  if (dipho_lead_elveto_branch != 0) dipho_lead_elveto();
  if (dipho_lead_prompt_branch != 0) dipho_lead_prompt();
  if (dipho_lead_chiso_branch != 0) dipho_lead_chiso();
  if (dipho_lead_chisow_branch != 0) dipho_lead_chisow();
  if (dipho_lead_phoiso_branch != 0) dipho_lead_phoiso();
  if (dipho_lead_phoiso04_branch != 0) dipho_lead_phoiso04();
  if (dipho_lead_neutiso_branch != 0) dipho_lead_neutiso();
  if (dipho_lead_ecaliso03_branch != 0) dipho_lead_ecaliso03();
  if (dipho_lead_hcaliso03_branch != 0) dipho_lead_hcaliso03();
  if (dipho_lead_pfcluecal03_branch != 0) dipho_lead_pfcluecal03();
  if (dipho_lead_pfcluhcal03_branch != 0) dipho_lead_pfcluhcal03();
  if (dipho_lead_trkiso03_branch != 0) dipho_lead_trkiso03();
  if (dipho_lead_pfchiso2_branch != 0) dipho_lead_pfchiso2();
  if (dipho_lead_haspixelseed_branch != 0) dipho_lead_haspixelseed();
  if (dipho_lead_sieip_branch != 0) dipho_lead_sieip();
  if (dipho_lead_etawidth_branch != 0) dipho_lead_etawidth();
  if (dipho_lead_phiwidth_branch != 0) dipho_lead_phiwidth();
  if (dipho_lead_regrerr_branch != 0) dipho_lead_regrerr();
  if (dipho_lead_s4ratio_branch != 0) dipho_lead_s4ratio();
  if (dipho_lead_effSigma_branch != 0) dipho_lead_effSigma();
  if (dipho_lead_scraw_branch != 0) dipho_lead_scraw();
  if (dipho_lead_ese_branch != 0) dipho_lead_ese();
  if (dipho_subleadPt_branch != 0) dipho_subleadPt();
  if (dipho_subleadEt_branch != 0) dipho_subleadEt();
  if (dipho_subleadEta_branch != 0) dipho_subleadEta();
  if (dipho_subleadPhi_branch != 0) dipho_subleadPhi();
  if (dipho_sublead_sieie_branch != 0) dipho_sublead_sieie();
  if (dipho_sublead_hoe_branch != 0) dipho_sublead_hoe();
  if (dipho_sublead_sigmaEoE_branch != 0) dipho_sublead_sigmaEoE();
  if (dipho_sublead_ptoM_branch != 0) dipho_sublead_ptoM();
  if (dipho_subleadR9_branch != 0) dipho_subleadR9();
  if (dipho_subleadIDMVA_branch != 0) dipho_subleadIDMVA();
  if (dipho_sublead_elveto_branch != 0) dipho_sublead_elveto();
  if (dipho_sulead_prompt_branch != 0) dipho_sulead_prompt();
  if (dipho_sublead_chiso_branch != 0) dipho_sublead_chiso();
  if (dipho_sublead_chisow_branch != 0) dipho_sublead_chisow();
  if (dipho_sublead_phoiso_branch != 0) dipho_sublead_phoiso();
  if (dipho_sublead_phoiso04_branch != 0) dipho_sublead_phoiso04();
  if (dipho_sublead_neutiso_branch != 0) dipho_sublead_neutiso();
  if (dipho_sublead_ecaliso03_branch != 0) dipho_sublead_ecaliso03();
  if (dipho_sublead_hcaliso03_branch != 0) dipho_sublead_hcaliso03();
  if (dipho_sublead_pfcluecal03_branch != 0) dipho_sublead_pfcluecal03();
  if (dipho_sublead_pfcluhcal03_branch != 0) dipho_sublead_pfcluhcal03();
  if (dipho_sublead_trkiso03_branch != 0) dipho_sublead_trkiso03();
  if (dipho_sublead_pfchiso2_branch != 0) dipho_sublead_pfchiso2();
  if (dipho_sublead_haspixelseed_branch != 0) dipho_sublead_haspixelseed();
  if (dipho_sublead_sieip_branch != 0) dipho_sublead_sieip();
  if (dipho_sublead_etawidth_branch != 0) dipho_sublead_etawidth();
  if (dipho_sublead_phiwidth_branch != 0) dipho_sublead_phiwidth();
  if (dipho_sublead_regrerr_branch != 0) dipho_sublead_regrerr();
  if (dipho_sublead_s4ratio_branch != 0) dipho_sublead_s4ratio();
  if (dipho_sublead_effSigma_branch != 0) dipho_sublead_effSigma();
  if (dipho_sublead_scraw_branch != 0) dipho_sublead_scraw();
  if (dipho_sublead_ese_branch != 0) dipho_sublead_ese();
  if (LeptonType_branch != 0) LeptonType();
  if (n_ele_branch != 0) n_ele();
  if (n_loose_ele_branch != 0) n_loose_ele();
  if (n_veto_ele_branch != 0) n_veto_ele();
  if (n_medium_ele_branch != 0) n_medium_ele();
  if (n_tight_ele_branch != 0) n_tight_ele();
  if (ele1_pt_branch != 0) ele1_pt();
  if (ele2_pt_branch != 0) ele2_pt();
  if (ele1_eta_branch != 0) ele1_eta();
  if (ele2_eta_branch != 0) ele2_eta();
  if (ele1_phi_branch != 0) ele1_phi();
  if (ele2_phi_branch != 0) ele2_phi();
  if (ele1_e_branch != 0) ele1_e();
  if (ele2_e_branch != 0) ele2_e();
  if (ele1_ch_branch != 0) ele1_ch();
  if (ele2_ch_branch != 0) ele2_ch();
  if (ele1_sigmaIetaIeta_branch != 0) ele1_sigmaIetaIeta();
  if (ele2_sigmaIetaIeta_branch != 0) ele2_sigmaIetaIeta();
  if (ele1_dEtaInSeed_branch != 0) ele1_dEtaInSeed();
  if (ele2_dEtaInSeed_branch != 0) ele2_dEtaInSeed();
  if (ele1_dPhiIn_branch != 0) ele1_dPhiIn();
  if (ele2_dPhiIn_branch != 0) ele2_dPhiIn();
  if (ele1_hOverE_branch != 0) ele1_hOverE();
  if (ele2_hOverE_branch != 0) ele2_hOverE();
  if (ele1_RelIsoEA_branch != 0) ele1_RelIsoEA();
  if (ele2_RelIsoEA_branch != 0) ele2_RelIsoEA();
  if (ele1_ooEmooP_branch != 0) ele1_ooEmooP();
  if (ele2_ooEmooP_branch != 0) ele2_ooEmooP();
  if (ele1_dxy_branch != 0) ele1_dxy();
  if (ele2_dxy_branch != 0) ele2_dxy();
  if (ele1_diphodxy_branch != 0) ele1_diphodxy();
  if (ele2_diphodxy_branch != 0) ele2_diphodxy();
  if (ele1_dz_branch != 0) ele1_dz();
  if (ele2_dz_branch != 0) ele2_dz();
  if (ele1_diphodz_branch != 0) ele1_diphodz();
  if (ele2_diphodz_branch != 0) ele2_diphodz();
  if (ele1_misHits_branch != 0) ele1_misHits();
  if (ele2_misHits_branch != 0) ele2_misHits();
  if (ele1_ConversionVeto_branch != 0) ele1_ConversionVeto();
  if (ele2_ConversionVeto_branch != 0) ele2_ConversionVeto();
  if (ele1_ChargedHadronPt_branch != 0) ele1_ChargedHadronPt();
  if (ele2_ChargedHadronPt_branch != 0) ele2_ChargedHadronPt();
  if (ele2_NeutralHadronEt_branch != 0) ele2_NeutralHadronEt();
  if (ele1_NeutralHadronEt_branch != 0) ele1_NeutralHadronEt();
  if (ele1_PhotonEt_branch != 0) ele1_PhotonEt();
  if (ele2_PhotonEt_branch != 0) ele2_PhotonEt();
  if (ele1_PassTight_branch != 0) ele1_PassTight();
  if (ele2_PassTight_branch != 0) ele2_PassTight();
  if (ele1_PassVeto_branch != 0) ele1_PassVeto();
  if (ele2_PassVeto_branch != 0) ele2_PassVeto();
  if (ele1_dPhiMET_branch != 0) ele1_dPhiMET();
  if (ele2_dPhiMET_branch != 0) ele2_dPhiMET();
  if (n_muons_branch != 0) n_muons();
  if (n_LooseMu25_branch != 0) n_LooseMu25();
  if (n_LooseMu15_branch != 0) n_LooseMu15();
  if (n_TightMu25_branch != 0) n_TightMu25();
  if (n_TightMu15_branch != 0) n_TightMu15();
  if (n_MediumMu25_branch != 0) n_MediumMu25();
  if (n_MediumMu15_branch != 0) n_MediumMu15();
  if (muon1_pt_branch != 0) muon1_pt();
  if (muon2_pt_branch != 0) muon2_pt();
  if (muon1_eta_branch != 0) muon1_eta();
  if (muon2_eta_branch != 0) muon2_eta();
  if (muon1_phi_branch != 0) muon1_phi();
  if (muon2_phi_branch != 0) muon2_phi();
  if (muon1_e_branch != 0) muon1_e();
  if (muon2_e_branch != 0) muon2_e();
  if (muon1_ch_branch != 0) muon1_ch();
  if (muon2_ch_branch != 0) muon2_ch();
  if (muon1_iso_branch != 0) muon1_iso();
  if (muon2_iso_branch != 0) muon2_iso();
  if (muon1_chi2_branch != 0) muon1_chi2();
  if (muon2_chi2_branch != 0) muon2_chi2();
  if (muon1_mHits_branch != 0) muon1_mHits();
  if (muon2_mHits_branch != 0) muon2_mHits();
  if (muon1_mStations_branch != 0) muon1_mStations();
  if (muon2_mStations_branch != 0) muon2_mStations();
  if (muon1_dxy_branch != 0) muon1_dxy();
  if (muon2_dxy_branch != 0) muon2_dxy();
  if (muon1_diphodxy_branch != 0) muon1_diphodxy();
  if (muon2_diphodxy_branch != 0) muon2_diphodxy();
  if (muon1_dz_branch != 0) muon1_dz();
  if (muon2_dz_branch != 0) muon2_dz();
  if (muon1_diphodz_branch != 0) muon1_diphodz();
  if (muon2_diphodz_branch != 0) muon2_diphodz();
  if (muon1_pxHits_branch != 0) muon1_pxHits();
  if (muon2_pxHits_branch != 0) muon2_pxHits();
  if (muon1_tkLayers_branch != 0) muon1_tkLayers();
  if (muon2_tkLayers_branch != 0) muon2_tkLayers();
  if (muon1_PassTight_branch != 0) muon1_PassTight();
  if (muon2_PassTight_branch != 0) muon2_PassTight();
  if (muon1_dPhiMET_branch != 0) muon1_dPhiMET();
  if (muon2_dPhiMET_branch != 0) muon2_dPhiMET();
  if (n_fwdjets_branch != 0) n_fwdjets();
  if (fwdjet1_pt_branch != 0) fwdjet1_pt();
  if (fwdjet2_pt_branch != 0) fwdjet2_pt();
  if (fwdjet3_pt_branch != 0) fwdjet3_pt();
  if (fwdjet1_eta_branch != 0) fwdjet1_eta();
  if (fwdjet2_eta_branch != 0) fwdjet2_eta();
  if (fwdjet3_eta_branch != 0) fwdjet3_eta();
  if (fwdjet4_eta_branch != 0) fwdjet4_eta();
  if (fwdjet5_eta_branch != 0) fwdjet5_eta();
  if (fwdjet6_eta_branch != 0) fwdjet6_eta();
  if (fwdjet7_eta_branch != 0) fwdjet7_eta();
  if (fwdjet8_eta_branch != 0) fwdjet8_eta();
  if (fwdjet9_eta_branch != 0) fwdjet9_eta();
  if (fwdjet1_phi_branch != 0) fwdjet1_phi();
  if (fwdjet2_phi_branch != 0) fwdjet2_phi();
  if (fwdjet3_phi_branch != 0) fwdjet3_phi();
  if (fwdjet1_e_branch != 0) fwdjet1_e();
  if (fwdjet2_e_branch != 0) fwdjet2_e();
  if (fwdjet3_e_branch != 0) fwdjet3_e();
  if (fwdjet1_discr_branch != 0) fwdjet1_discr();
  if (n_M_bjets_branch != 0) n_M_bjets();
  if (n_L_bjets_branch != 0) n_L_bjets();
  if (n_T_bjets_branch != 0) n_T_bjets();
  if (n_bjets_branch != 0) n_bjets();
  if (bjet1_pt_branch != 0) bjet1_pt();
  if (bjet2_pt_branch != 0) bjet2_pt();
  if (bjet3_pt_branch != 0) bjet3_pt();
  if (bjet1_eta_branch != 0) bjet1_eta();
  if (bjet2_eta_branch != 0) bjet2_eta();
  if (bjet3_eta_branch != 0) bjet3_eta();
  if (bjet1_phi_branch != 0) bjet1_phi();
  if (bjet2_phi_branch != 0) bjet2_phi();
  if (bjet3_phi_branch != 0) bjet3_phi();
  if (bjet1_e_branch != 0) bjet1_e();
  if (bjet2_e_branch != 0) bjet2_e();
  if (bjet3_e_branch != 0) bjet3_e();
  if (bjet1_discr_branch != 0) bjet1_discr();
  if (bjet2_discr_branch != 0) bjet2_discr();
  if (bjet3_discr_branch != 0) bjet3_discr();
  if (bjet4_discr_branch != 0) bjet4_discr();
  if (n_jets_branch != 0) n_jets();
  if (jet1_pt_branch != 0) jet1_pt();
  if (jet2_pt_branch != 0) jet2_pt();
  if (jet3_pt_branch != 0) jet3_pt();
  if (jet4_pt_branch != 0) jet4_pt();
  if (jet5_pt_branch != 0) jet5_pt();
  if (jet6_pt_branch != 0) jet6_pt();
  if (jet7_pt_branch != 0) jet7_pt();
  if (jet8_pt_branch != 0) jet8_pt();
  if (jet9_pt_branch != 0) jet9_pt();
  if (jet10_pt_branch != 0) jet10_pt();
  if (jet11_pt_branch != 0) jet11_pt();
  if (jet12_pt_branch != 0) jet12_pt();
  if (jet13_pt_branch != 0) jet13_pt();
  if (jet14_pt_branch != 0) jet14_pt();
  if (jet15_pt_branch != 0) jet15_pt();
  if (jet1_eta_branch != 0) jet1_eta();
  if (jet2_eta_branch != 0) jet2_eta();
  if (jet3_eta_branch != 0) jet3_eta();
  if (jet4_eta_branch != 0) jet4_eta();
  if (jet5_eta_branch != 0) jet5_eta();
  if (jet6_eta_branch != 0) jet6_eta();
  if (jet7_eta_branch != 0) jet7_eta();
  if (jet8_eta_branch != 0) jet8_eta();
  if (jet9_eta_branch != 0) jet9_eta();
  if (jet10_eta_branch != 0) jet10_eta();
  if (jet11_eta_branch != 0) jet11_eta();
  if (jet12_eta_branch != 0) jet12_eta();
  if (jet13_eta_branch != 0) jet13_eta();
  if (jet14_eta_branch != 0) jet14_eta();
  if (jet15_eta_branch != 0) jet15_eta();
  if (jet1_phi_branch != 0) jet1_phi();
  if (jet2_phi_branch != 0) jet2_phi();
  if (jet3_phi_branch != 0) jet3_phi();
  if (jet4_phi_branch != 0) jet4_phi();
  if (jet5_phi_branch != 0) jet5_phi();
  if (jet6_phi_branch != 0) jet6_phi();
  if (jet7_phi_branch != 0) jet7_phi();
  if (jet8_phi_branch != 0) jet8_phi();
  if (jet9_phi_branch != 0) jet9_phi();
  if (jet10_phi_branch != 0) jet10_phi();
  if (jet11_phi_branch != 0) jet11_phi();
  if (jet12_phi_branch != 0) jet12_phi();
  if (jet13_phi_branch != 0) jet13_phi();
  if (jet14_phi_branch != 0) jet14_phi();
  if (jet15_phi_branch != 0) jet15_phi();
  if (jet1_e_branch != 0) jet1_e();
  if (jet2_e_branch != 0) jet2_e();
  if (jet3_e_branch != 0) jet3_e();
  if (jet4_e_branch != 0) jet4_e();
  if (jet5_e_branch != 0) jet5_e();
  if (jet6_e_branch != 0) jet6_e();
  if (jet7_e_branch != 0) jet7_e();
  if (jet8_e_branch != 0) jet8_e();
  if (jet9_e_branch != 0) jet9_e();
  if (jet10_e_branch != 0) jet10_e();
  if (jet11_e_branch != 0) jet11_e();
  if (jet12_e_branch != 0) jet12_e();
  if (jet13_e_branch != 0) jet13_e();
  if (jet14_e_branch != 0) jet14_e();
  if (jet15_e_branch != 0) jet15_e();
  if (jet1_discr_branch != 0) jet1_discr();
  if (jet2_discr_branch != 0) jet2_discr();
  if (jet3_discr_branch != 0) jet3_discr();
  if (jet4_discr_branch != 0) jet4_discr();
  if (jet5_discr_branch != 0) jet5_discr();
  if (jet6_discr_branch != 0) jet6_discr();
  if (jet7_discr_branch != 0) jet7_discr();
  if (jet8_discr_branch != 0) jet8_discr();
  if (jet9_discr_branch != 0) jet9_discr();
  if (jet10_discr_branch != 0) jet10_discr();
  if (jet11_discr_branch != 0) jet11_discr();
  if (jet12_discr_branch != 0) jet12_discr();
  if (jet13_discr_branch != 0) jet13_discr();
  if (jet14_discr_branch != 0) jet14_discr();
  if (jet15_discr_branch != 0) jet15_discr();
  if (recoMET_pt_branch != 0) recoMET_pt();
  if (recoMET_eta_branch != 0) recoMET_eta();
  if (recoMET_phi_branch != 0) recoMET_phi();
  if (recoMET_e_branch != 0) recoMET_e();
  if (solvedMET_pt_branch != 0) solvedMET_pt();
  if (solvedMET_eta_branch != 0) solvedMET_eta();
  if (solvedMET_phi_branch != 0) solvedMET_phi();
  if (solvedMET_e_branch != 0) solvedMET_e();
  if (dr_leadphobjet_branch != 0) dr_leadphobjet();
  if (dr_leptonfwdjet_branch != 0) dr_leptonfwdjet();
  if (top_mt_branch != 0) top_mt();
  if (top_mass_branch != 0) top_mass();
  if (HT_branch != 0) HT();
  if (gen_parton1_pt_branch != 0) gen_parton1_pt();
  if (gen_parton2_pt_branch != 0) gen_parton2_pt();
  if (gen_parton3_pt_branch != 0) gen_parton3_pt();
  if (gen_parton4_pt_branch != 0) gen_parton4_pt();
  if (gen_parton5_pt_branch != 0) gen_parton5_pt();
  if (gen_parton6_pt_branch != 0) gen_parton6_pt();
  if (gen_parton7_pt_branch != 0) gen_parton7_pt();
  if (gen_parton8_pt_branch != 0) gen_parton8_pt();
  if (gen_parton9_pt_branch != 0) gen_parton9_pt();
  if (gen_parton10_pt_branch != 0) gen_parton10_pt();
  if (gen_parton1_eta_branch != 0) gen_parton1_eta();
  if (gen_parton2_eta_branch != 0) gen_parton2_eta();
  if (gen_parton3_eta_branch != 0) gen_parton3_eta();
  if (gen_parton4_eta_branch != 0) gen_parton4_eta();
  if (gen_parton5_eta_branch != 0) gen_parton5_eta();
  if (gen_parton6_eta_branch != 0) gen_parton6_eta();
  if (gen_parton7_eta_branch != 0) gen_parton7_eta();
  if (gen_parton8_eta_branch != 0) gen_parton8_eta();
  if (gen_parton9_eta_branch != 0) gen_parton9_eta();
  if (gen_parton10_eta_branch != 0) gen_parton10_eta();
  if (gen_parton1_phi_branch != 0) gen_parton1_phi();
  if (gen_parton2_phi_branch != 0) gen_parton2_phi();
  if (gen_parton3_phi_branch != 0) gen_parton3_phi();
  if (gen_parton4_phi_branch != 0) gen_parton4_phi();
  if (gen_parton5_phi_branch != 0) gen_parton5_phi();
  if (gen_parton6_phi_branch != 0) gen_parton6_phi();
  if (gen_parton7_phi_branch != 0) gen_parton7_phi();
  if (gen_parton8_phi_branch != 0) gen_parton8_phi();
  if (gen_parton9_phi_branch != 0) gen_parton9_phi();
  if (gen_parton10_phi_branch != 0) gen_parton10_phi();
  if (gen_parton1_mass_branch != 0) gen_parton1_mass();
  if (gen_parton2_mass_branch != 0) gen_parton2_mass();
  if (gen_parton3_mass_branch != 0) gen_parton3_mass();
  if (gen_parton4_mass_branch != 0) gen_parton4_mass();
  if (gen_parton5_mass_branch != 0) gen_parton5_mass();
  if (gen_parton6_mass_branch != 0) gen_parton6_mass();
  if (gen_parton7_mass_branch != 0) gen_parton7_mass();
  if (gen_parton8_mass_branch != 0) gen_parton8_mass();
  if (gen_parton9_mass_branch != 0) gen_parton9_mass();
  if (gen_parton10_mass_branch != 0) gen_parton10_mass();
  if (gen_parton1_pdgId_branch != 0) gen_parton1_pdgId();
  if (gen_parton2_pdgId_branch != 0) gen_parton2_pdgId();
  if (gen_parton3_pdgId_branch != 0) gen_parton3_pdgId();
  if (gen_parton4_pdgId_branch != 0) gen_parton4_pdgId();
  if (gen_parton5_pdgId_branch != 0) gen_parton5_pdgId();
  if (gen_parton6_pdgId_branch != 0) gen_parton6_pdgId();
  if (gen_parton7_pdgId_branch != 0) gen_parton7_pdgId();
  if (gen_parton8_pdgId_branch != 0) gen_parton8_pdgId();
  if (gen_parton9_pdgId_branch != 0) gen_parton9_pdgId();
  if (gen_parton10_pdgId_branch != 0) gen_parton10_pdgId();
  if (gen_parton1_status_branch != 0) gen_parton1_status();
  if (gen_parton2_status_branch != 0) gen_parton2_status();
  if (gen_parton3_status_branch != 0) gen_parton3_status();
  if (gen_parton4_status_branch != 0) gen_parton4_status();
  if (gen_parton5_status_branch != 0) gen_parton5_status();
  if (gen_parton6_status_branch != 0) gen_parton6_status();
  if (gen_parton7_status_branch != 0) gen_parton7_status();
  if (gen_parton8_status_branch != 0) gen_parton8_status();
  if (gen_parton9_status_branch != 0) gen_parton9_status();
  if (gen_parton10_status_branch != 0) gen_parton10_status();
  if (genMatched_jet0_pdgId_branch != 0) genMatched_jet0_pdgId();
  if (genMatched_jet1_pdgId_branch != 0) genMatched_jet1_pdgId();
  if (genMatched_jet2_pdgId_branch != 0) genMatched_jet2_pdgId();
  if (genMatched_jet0_index_branch != 0) genMatched_jet0_index();
  if (genMatched_jet1_index_branch != 0) genMatched_jet1_index();
  if (genMatched_jet2_index_branch != 0) genMatched_jet2_index();
  if (genMatched_jet0_deltaR_branch != 0) genMatched_jet0_deltaR();
  if (genMatched_jet1_deltaR_branch != 0) genMatched_jet1_deltaR();
  if (genMatched_jet2_deltaR_branch != 0) genMatched_jet2_deltaR();
  if (genMET_pt_branch != 0) genMET_pt();
  if (genMET_eta_branch != 0) genMET_eta();
  if (genMET_phi_branch != 0) genMET_phi();
  if (genMET_e_branch != 0) genMET_e();
  if (promptGenMET_pt_branch != 0) promptGenMET_pt();
  if (promptGenMET_eta_branch != 0) promptGenMET_eta();
  if (promptGenMET_phi_branch != 0) promptGenMET_phi();
  if (promptGenMET_e_branch != 0) promptGenMET_e();
  if (genMETTrue_pt_branch != 0) genMETTrue_pt();
  if (genMETTrue_eta_branch != 0) genMETTrue_eta();
  if (genMETTrue_phi_branch != 0) genMETTrue_phi();
  if (genMETTrue_e_branch != 0) genMETTrue_e();
  if (rho_branch != 0) rho();
  if (nvtx_branch != 0) nvtx();
  if (event_branch != 0) event();
  if (lumi_branch != 0) lumi();
  if (processIndex_branch != 0) processIndex();
  if (run_branch != 0) run();
  if (npu_branch != 0) npu();
  if (puweight_branch != 0) puweight();
}

const int &tprimetHHadronic::candidate_id() {
  if (not candidate_id_isLoaded) {
    if (candidate_id_branch != 0) {
      candidate_id_branch->GetEntry(index);
    } else {
      printf("branch candidate_id_branch does not exist!\n");
      exit(1);
    }
    candidate_id_isLoaded = true;
  }
  return candidate_id_;
}

const float &tprimetHHadronic::weight() {
  if (not weight_isLoaded) {
    if (weight_branch != 0) {
      weight_branch->GetEntry(index);
    } else {
      printf("branch weight_branch does not exist!\n");
      exit(1);
    }
    weight_isLoaded = true;
  }
  return weight_;
}

const float &tprimetHHadronic::CMS_hgg_mass() {
  if (not CMS_hgg_mass_isLoaded) {
    if (CMS_hgg_mass_branch != 0) {
      CMS_hgg_mass_branch->GetEntry(index);
    } else {
      printf("branch CMS_hgg_mass_branch does not exist!\n");
      exit(1);
    }
    CMS_hgg_mass_isLoaded = true;
  }
  return CMS_hgg_mass_;
}

const float &tprimetHHadronic::sigmaMoM_decorr() {
  if (not sigmaMoM_decorr_isLoaded) {
    if (sigmaMoM_decorr_branch != 0) {
      sigmaMoM_decorr_branch->GetEntry(index);
    } else {
      printf("branch sigmaMoM_decorr_branch does not exist!\n");
      exit(1);
    }
    sigmaMoM_decorr_isLoaded = true;
  }
  return sigmaMoM_decorr_;
}

const float &tprimetHHadronic::dZ() {
  if (not dZ_isLoaded) {
    if (dZ_branch != 0) {
      dZ_branch->GetEntry(index);
    } else {
      printf("branch dZ_branch does not exist!\n");
      exit(1);
    }
    dZ_isLoaded = true;
  }
  return dZ_;
}

const float &tprimetHHadronic::centralObjectWeight() {
  if (not centralObjectWeight_isLoaded) {
    if (centralObjectWeight_branch != 0) {
      centralObjectWeight_branch->GetEntry(index);
    } else {
      printf("branch centralObjectWeight_branch does not exist!\n");
      exit(1);
    }
    centralObjectWeight_isLoaded = true;
  }
  return centralObjectWeight_;
}

const float &tprimetHHadronic::vtxprob() {
  if (not vtxprob_isLoaded) {
    if (vtxprob_branch != 0) {
      vtxprob_branch->GetEntry(index);
    } else {
      printf("branch vtxprob_branch does not exist!\n");
      exit(1);
    }
    vtxprob_isLoaded = true;
  }
  return vtxprob_;
}

const float &tprimetHHadronic::ptbal() {
  if (not ptbal_isLoaded) {
    if (ptbal_branch != 0) {
      ptbal_branch->GetEntry(index);
    } else {
      printf("branch ptbal_branch does not exist!\n");
      exit(1);
    }
    ptbal_isLoaded = true;
  }
  return ptbal_;
}

const float &tprimetHHadronic::ptasym() {
  if (not ptasym_isLoaded) {
    if (ptasym_branch != 0) {
      ptasym_branch->GetEntry(index);
    } else {
      printf("branch ptasym_branch does not exist!\n");
      exit(1);
    }
    ptasym_isLoaded = true;
  }
  return ptasym_;
}

const float &tprimetHHadronic::logspt2() {
  if (not logspt2_isLoaded) {
    if (logspt2_branch != 0) {
      logspt2_branch->GetEntry(index);
    } else {
      printf("branch logspt2_branch does not exist!\n");
      exit(1);
    }
    logspt2_isLoaded = true;
  }
  return logspt2_;
}

const float &tprimetHHadronic::p2conv() {
  if (not p2conv_isLoaded) {
    if (p2conv_branch != 0) {
      p2conv_branch->GetEntry(index);
    } else {
      printf("branch p2conv_branch does not exist!\n");
      exit(1);
    }
    p2conv_isLoaded = true;
  }
  return p2conv_;
}

const float &tprimetHHadronic::nconv() {
  if (not nconv_isLoaded) {
    if (nconv_branch != 0) {
      nconv_branch->GetEntry(index);
    } else {
      printf("branch nconv_branch does not exist!\n");
      exit(1);
    }
    nconv_isLoaded = true;
  }
  return nconv_;
}

const float &tprimetHHadronic::vtxmva() {
  if (not vtxmva_isLoaded) {
    if (vtxmva_branch != 0) {
      vtxmva_branch->GetEntry(index);
    } else {
      printf("branch vtxmva_branch does not exist!\n");
      exit(1);
    }
    vtxmva_isLoaded = true;
  }
  return vtxmva_;
}

const float &tprimetHHadronic::vtxdz() {
  if (not vtxdz_isLoaded) {
    if (vtxdz_branch != 0) {
      vtxdz_branch->GetEntry(index);
    } else {
      printf("branch vtxdz_branch does not exist!\n");
      exit(1);
    }
    vtxdz_isLoaded = true;
  }
  return vtxdz_;
}

const float &tprimetHHadronic::vtx_x() {
  if (not vtx_x_isLoaded) {
    if (vtx_x_branch != 0) {
      vtx_x_branch->GetEntry(index);
    } else {
      printf("branch vtx_x_branch does not exist!\n");
      exit(1);
    }
    vtx_x_isLoaded = true;
  }
  return vtx_x_;
}

const float &tprimetHHadronic::vtx_y() {
  if (not vtx_y_isLoaded) {
    if (vtx_y_branch != 0) {
      vtx_y_branch->GetEntry(index);
    } else {
      printf("branch vtx_y_branch does not exist!\n");
      exit(1);
    }
    vtx_y_isLoaded = true;
  }
  return vtx_y_;
}

const float &tprimetHHadronic::vtx_z() {
  if (not vtx_z_isLoaded) {
    if (vtx_z_branch != 0) {
      vtx_z_branch->GetEntry(index);
    } else {
      printf("branch vtx_z_branch does not exist!\n");
      exit(1);
    }
    vtx_z_isLoaded = true;
  }
  return vtx_z_;
}

const float &tprimetHHadronic::dipho_sumpt() {
  if (not dipho_sumpt_isLoaded) {
    if (dipho_sumpt_branch != 0) {
      dipho_sumpt_branch->GetEntry(index);
    } else {
      printf("branch dipho_sumpt_branch does not exist!\n");
      exit(1);
    }
    dipho_sumpt_isLoaded = true;
  }
  return dipho_sumpt_;
}

const float &tprimetHHadronic::dipho_cosphi() {
  if (not dipho_cosphi_isLoaded) {
    if (dipho_cosphi_branch != 0) {
      dipho_cosphi_branch->GetEntry(index);
    } else {
      printf("branch dipho_cosphi_branch does not exist!\n");
      exit(1);
    }
    dipho_cosphi_isLoaded = true;
  }
  return dipho_cosphi_;
}

const float &tprimetHHadronic::dipho_mass() {
  if (not dipho_mass_isLoaded) {
    if (dipho_mass_branch != 0) {
      dipho_mass_branch->GetEntry(index);
    } else {
      printf("branch dipho_mass_branch does not exist!\n");
      exit(1);
    }
    dipho_mass_isLoaded = true;
  }
  return dipho_mass_;
}

const float &tprimetHHadronic::dipho_pt() {
  if (not dipho_pt_isLoaded) {
    if (dipho_pt_branch != 0) {
      dipho_pt_branch->GetEntry(index);
    } else {
      printf("branch dipho_pt_branch does not exist!\n");
      exit(1);
    }
    dipho_pt_isLoaded = true;
  }
  return dipho_pt_;
}

const float &tprimetHHadronic::dipho_phi() {
  if (not dipho_phi_isLoaded) {
    if (dipho_phi_branch != 0) {
      dipho_phi_branch->GetEntry(index);
    } else {
      printf("branch dipho_phi_branch does not exist!\n");
      exit(1);
    }
    dipho_phi_isLoaded = true;
  }
  return dipho_phi_;
}

const float &tprimetHHadronic::dipho_eta() {
  if (not dipho_eta_isLoaded) {
    if (dipho_eta_branch != 0) {
      dipho_eta_branch->GetEntry(index);
    } else {
      printf("branch dipho_eta_branch does not exist!\n");
      exit(1);
    }
    dipho_eta_isLoaded = true;
  }
  return dipho_eta_;
}

const float &tprimetHHadronic::dipho_e() {
  if (not dipho_e_isLoaded) {
    if (dipho_e_branch != 0) {
      dipho_e_branch->GetEntry(index);
    } else {
      printf("branch dipho_e_branch does not exist!\n");
      exit(1);
    }
    dipho_e_isLoaded = true;
  }
  return dipho_e_;
}

const float &tprimetHHadronic::dipho_PtoM() {
  if (not dipho_PtoM_isLoaded) {
    if (dipho_PtoM_branch != 0) {
      dipho_PtoM_branch->GetEntry(index);
    } else {
      printf("branch dipho_PtoM_branch does not exist!\n");
      exit(1);
    }
    dipho_PtoM_isLoaded = true;
  }
  return dipho_PtoM_;
}

const float &tprimetHHadronic::cosphi() {
  if (not cosphi_isLoaded) {
    if (cosphi_branch != 0) {
      cosphi_branch->GetEntry(index);
    } else {
      printf("branch cosphi_branch does not exist!\n");
      exit(1);
    }
    cosphi_isLoaded = true;
  }
  return cosphi_;
}

const float &tprimetHHadronic::sigmaMrvoM() {
  if (not sigmaMrvoM_isLoaded) {
    if (sigmaMrvoM_branch != 0) {
      sigmaMrvoM_branch->GetEntry(index);
    } else {
      printf("branch sigmaMrvoM_branch does not exist!\n");
      exit(1);
    }
    sigmaMrvoM_isLoaded = true;
  }
  return sigmaMrvoM_;
}

const float &tprimetHHadronic::sigmaMwvoM() {
  if (not sigmaMwvoM_isLoaded) {
    if (sigmaMwvoM_branch != 0) {
      sigmaMwvoM_branch->GetEntry(index);
    } else {
      printf("branch sigmaMwvoM_branch does not exist!\n");
      exit(1);
    }
    sigmaMwvoM_isLoaded = true;
  }
  return sigmaMwvoM_;
}

const float &tprimetHHadronic::dipho_leadPt() {
  if (not dipho_leadPt_isLoaded) {
    if (dipho_leadPt_branch != 0) {
      dipho_leadPt_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadPt_branch does not exist!\n");
      exit(1);
    }
    dipho_leadPt_isLoaded = true;
  }
  return dipho_leadPt_;
}

const float &tprimetHHadronic::dipho_leadEt() {
  if (not dipho_leadEt_isLoaded) {
    if (dipho_leadEt_branch != 0) {
      dipho_leadEt_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadEt_branch does not exist!\n");
      exit(1);
    }
    dipho_leadEt_isLoaded = true;
  }
  return dipho_leadEt_;
}

const float &tprimetHHadronic::dipho_leadEta() {
  if (not dipho_leadEta_isLoaded) {
    if (dipho_leadEta_branch != 0) {
      dipho_leadEta_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadEta_branch does not exist!\n");
      exit(1);
    }
    dipho_leadEta_isLoaded = true;
  }
  return dipho_leadEta_;
}

const float &tprimetHHadronic::dipho_leadPhi() {
  if (not dipho_leadPhi_isLoaded) {
    if (dipho_leadPhi_branch != 0) {
      dipho_leadPhi_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadPhi_branch does not exist!\n");
      exit(1);
    }
    dipho_leadPhi_isLoaded = true;
  }
  return dipho_leadPhi_;
}

const float &tprimetHHadronic::dipho_lead_sieie() {
  if (not dipho_lead_sieie_isLoaded) {
    if (dipho_lead_sieie_branch != 0) {
      dipho_lead_sieie_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_sieie_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_sieie_isLoaded = true;
  }
  return dipho_lead_sieie_;
}

const float &tprimetHHadronic::dipho_lead_hoe() {
  if (not dipho_lead_hoe_isLoaded) {
    if (dipho_lead_hoe_branch != 0) {
      dipho_lead_hoe_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_hoe_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_hoe_isLoaded = true;
  }
  return dipho_lead_hoe_;
}

const float &tprimetHHadronic::dipho_lead_sigmaEoE() {
  if (not dipho_lead_sigmaEoE_isLoaded) {
    if (dipho_lead_sigmaEoE_branch != 0) {
      dipho_lead_sigmaEoE_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_sigmaEoE_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_sigmaEoE_isLoaded = true;
  }
  return dipho_lead_sigmaEoE_;
}

const float &tprimetHHadronic::dipho_lead_ptoM() {
  if (not dipho_lead_ptoM_isLoaded) {
    if (dipho_lead_ptoM_branch != 0) {
      dipho_lead_ptoM_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_ptoM_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_ptoM_isLoaded = true;
  }
  return dipho_lead_ptoM_;
}

const float &tprimetHHadronic::dipho_leadR9() {
  if (not dipho_leadR9_isLoaded) {
    if (dipho_leadR9_branch != 0) {
      dipho_leadR9_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadR9_branch does not exist!\n");
      exit(1);
    }
    dipho_leadR9_isLoaded = true;
  }
  return dipho_leadR9_;
}

const float &tprimetHHadronic::dipho_leadIDMVA() {
  if (not dipho_leadIDMVA_isLoaded) {
    if (dipho_leadIDMVA_branch != 0) {
      dipho_leadIDMVA_branch->GetEntry(index);
    } else {
      printf("branch dipho_leadIDMVA_branch does not exist!\n");
      exit(1);
    }
    dipho_leadIDMVA_isLoaded = true;
  }
  return dipho_leadIDMVA_;
}

const float &tprimetHHadronic::dipho_lead_elveto() {
  if (not dipho_lead_elveto_isLoaded) {
    if (dipho_lead_elveto_branch != 0) {
      dipho_lead_elveto_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_elveto_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_elveto_isLoaded = true;
  }
  return dipho_lead_elveto_;
}

const float &tprimetHHadronic::dipho_lead_prompt() {
  if (not dipho_lead_prompt_isLoaded) {
    if (dipho_lead_prompt_branch != 0) {
      dipho_lead_prompt_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_prompt_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_prompt_isLoaded = true;
  }
  return dipho_lead_prompt_;
}

const float &tprimetHHadronic::dipho_lead_chiso() {
  if (not dipho_lead_chiso_isLoaded) {
    if (dipho_lead_chiso_branch != 0) {
      dipho_lead_chiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_chiso_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_chiso_isLoaded = true;
  }
  return dipho_lead_chiso_;
}

const float &tprimetHHadronic::dipho_lead_chisow() {
  if (not dipho_lead_chisow_isLoaded) {
    if (dipho_lead_chisow_branch != 0) {
      dipho_lead_chisow_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_chisow_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_chisow_isLoaded = true;
  }
  return dipho_lead_chisow_;
}

const float &tprimetHHadronic::dipho_lead_phoiso() {
  if (not dipho_lead_phoiso_isLoaded) {
    if (dipho_lead_phoiso_branch != 0) {
      dipho_lead_phoiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_phoiso_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_phoiso_isLoaded = true;
  }
  return dipho_lead_phoiso_;
}

const float &tprimetHHadronic::dipho_lead_phoiso04() {
  if (not dipho_lead_phoiso04_isLoaded) {
    if (dipho_lead_phoiso04_branch != 0) {
      dipho_lead_phoiso04_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_phoiso04_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_phoiso04_isLoaded = true;
  }
  return dipho_lead_phoiso04_;
}

const float &tprimetHHadronic::dipho_lead_neutiso() {
  if (not dipho_lead_neutiso_isLoaded) {
    if (dipho_lead_neutiso_branch != 0) {
      dipho_lead_neutiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_neutiso_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_neutiso_isLoaded = true;
  }
  return dipho_lead_neutiso_;
}

const float &tprimetHHadronic::dipho_lead_ecaliso03() {
  if (not dipho_lead_ecaliso03_isLoaded) {
    if (dipho_lead_ecaliso03_branch != 0) {
      dipho_lead_ecaliso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_ecaliso03_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_ecaliso03_isLoaded = true;
  }
  return dipho_lead_ecaliso03_;
}

const float &tprimetHHadronic::dipho_lead_hcaliso03() {
  if (not dipho_lead_hcaliso03_isLoaded) {
    if (dipho_lead_hcaliso03_branch != 0) {
      dipho_lead_hcaliso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_hcaliso03_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_hcaliso03_isLoaded = true;
  }
  return dipho_lead_hcaliso03_;
}

const float &tprimetHHadronic::dipho_lead_pfcluecal03() {
  if (not dipho_lead_pfcluecal03_isLoaded) {
    if (dipho_lead_pfcluecal03_branch != 0) {
      dipho_lead_pfcluecal03_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_pfcluecal03_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_pfcluecal03_isLoaded = true;
  }
  return dipho_lead_pfcluecal03_;
}

const float &tprimetHHadronic::dipho_lead_pfcluhcal03() {
  if (not dipho_lead_pfcluhcal03_isLoaded) {
    if (dipho_lead_pfcluhcal03_branch != 0) {
      dipho_lead_pfcluhcal03_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_pfcluhcal03_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_pfcluhcal03_isLoaded = true;
  }
  return dipho_lead_pfcluhcal03_;
}

const float &tprimetHHadronic::dipho_lead_trkiso03() {
  if (not dipho_lead_trkiso03_isLoaded) {
    if (dipho_lead_trkiso03_branch != 0) {
      dipho_lead_trkiso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_trkiso03_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_trkiso03_isLoaded = true;
  }
  return dipho_lead_trkiso03_;
}

const float &tprimetHHadronic::dipho_lead_pfchiso2() {
  if (not dipho_lead_pfchiso2_isLoaded) {
    if (dipho_lead_pfchiso2_branch != 0) {
      dipho_lead_pfchiso2_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_pfchiso2_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_pfchiso2_isLoaded = true;
  }
  return dipho_lead_pfchiso2_;
}

const float &tprimetHHadronic::dipho_lead_haspixelseed() {
  if (not dipho_lead_haspixelseed_isLoaded) {
    if (dipho_lead_haspixelseed_branch != 0) {
      dipho_lead_haspixelseed_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_haspixelseed_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_haspixelseed_isLoaded = true;
  }
  return dipho_lead_haspixelseed_;
}

const float &tprimetHHadronic::dipho_lead_sieip() {
  if (not dipho_lead_sieip_isLoaded) {
    if (dipho_lead_sieip_branch != 0) {
      dipho_lead_sieip_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_sieip_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_sieip_isLoaded = true;
  }
  return dipho_lead_sieip_;
}

const float &tprimetHHadronic::dipho_lead_etawidth() {
  if (not dipho_lead_etawidth_isLoaded) {
    if (dipho_lead_etawidth_branch != 0) {
      dipho_lead_etawidth_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_etawidth_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_etawidth_isLoaded = true;
  }
  return dipho_lead_etawidth_;
}

const float &tprimetHHadronic::dipho_lead_phiwidth() {
  if (not dipho_lead_phiwidth_isLoaded) {
    if (dipho_lead_phiwidth_branch != 0) {
      dipho_lead_phiwidth_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_phiwidth_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_phiwidth_isLoaded = true;
  }
  return dipho_lead_phiwidth_;
}

const float &tprimetHHadronic::dipho_lead_regrerr() {
  if (not dipho_lead_regrerr_isLoaded) {
    if (dipho_lead_regrerr_branch != 0) {
      dipho_lead_regrerr_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_regrerr_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_regrerr_isLoaded = true;
  }
  return dipho_lead_regrerr_;
}

const float &tprimetHHadronic::dipho_lead_s4ratio() {
  if (not dipho_lead_s4ratio_isLoaded) {
    if (dipho_lead_s4ratio_branch != 0) {
      dipho_lead_s4ratio_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_s4ratio_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_s4ratio_isLoaded = true;
  }
  return dipho_lead_s4ratio_;
}

const float &tprimetHHadronic::dipho_lead_effSigma() {
  if (not dipho_lead_effSigma_isLoaded) {
    if (dipho_lead_effSigma_branch != 0) {
      dipho_lead_effSigma_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_effSigma_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_effSigma_isLoaded = true;
  }
  return dipho_lead_effSigma_;
}

const float &tprimetHHadronic::dipho_lead_scraw() {
  if (not dipho_lead_scraw_isLoaded) {
    if (dipho_lead_scraw_branch != 0) {
      dipho_lead_scraw_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_scraw_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_scraw_isLoaded = true;
  }
  return dipho_lead_scraw_;
}

const float &tprimetHHadronic::dipho_lead_ese() {
  if (not dipho_lead_ese_isLoaded) {
    if (dipho_lead_ese_branch != 0) {
      dipho_lead_ese_branch->GetEntry(index);
    } else {
      printf("branch dipho_lead_ese_branch does not exist!\n");
      exit(1);
    }
    dipho_lead_ese_isLoaded = true;
  }
  return dipho_lead_ese_;
}

const float &tprimetHHadronic::dipho_subleadPt() {
  if (not dipho_subleadPt_isLoaded) {
    if (dipho_subleadPt_branch != 0) {
      dipho_subleadPt_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadPt_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadPt_isLoaded = true;
  }
  return dipho_subleadPt_;
}

const float &tprimetHHadronic::dipho_subleadEt() {
  if (not dipho_subleadEt_isLoaded) {
    if (dipho_subleadEt_branch != 0) {
      dipho_subleadEt_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadEt_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadEt_isLoaded = true;
  }
  return dipho_subleadEt_;
}

const float &tprimetHHadronic::dipho_subleadEta() {
  if (not dipho_subleadEta_isLoaded) {
    if (dipho_subleadEta_branch != 0) {
      dipho_subleadEta_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadEta_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadEta_isLoaded = true;
  }
  return dipho_subleadEta_;
}

const float &tprimetHHadronic::dipho_subleadPhi() {
  if (not dipho_subleadPhi_isLoaded) {
    if (dipho_subleadPhi_branch != 0) {
      dipho_subleadPhi_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadPhi_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadPhi_isLoaded = true;
  }
  return dipho_subleadPhi_;
}

const float &tprimetHHadronic::dipho_sublead_sieie() {
  if (not dipho_sublead_sieie_isLoaded) {
    if (dipho_sublead_sieie_branch != 0) {
      dipho_sublead_sieie_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_sieie_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_sieie_isLoaded = true;
  }
  return dipho_sublead_sieie_;
}

const float &tprimetHHadronic::dipho_sublead_hoe() {
  if (not dipho_sublead_hoe_isLoaded) {
    if (dipho_sublead_hoe_branch != 0) {
      dipho_sublead_hoe_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_hoe_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_hoe_isLoaded = true;
  }
  return dipho_sublead_hoe_;
}

const float &tprimetHHadronic::dipho_sublead_sigmaEoE() {
  if (not dipho_sublead_sigmaEoE_isLoaded) {
    if (dipho_sublead_sigmaEoE_branch != 0) {
      dipho_sublead_sigmaEoE_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_sigmaEoE_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_sigmaEoE_isLoaded = true;
  }
  return dipho_sublead_sigmaEoE_;
}

const float &tprimetHHadronic::dipho_sublead_ptoM() {
  if (not dipho_sublead_ptoM_isLoaded) {
    if (dipho_sublead_ptoM_branch != 0) {
      dipho_sublead_ptoM_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_ptoM_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_ptoM_isLoaded = true;
  }
  return dipho_sublead_ptoM_;
}

const float &tprimetHHadronic::dipho_subleadR9() {
  if (not dipho_subleadR9_isLoaded) {
    if (dipho_subleadR9_branch != 0) {
      dipho_subleadR9_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadR9_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadR9_isLoaded = true;
  }
  return dipho_subleadR9_;
}

const float &tprimetHHadronic::dipho_subleadIDMVA() {
  if (not dipho_subleadIDMVA_isLoaded) {
    if (dipho_subleadIDMVA_branch != 0) {
      dipho_subleadIDMVA_branch->GetEntry(index);
    } else {
      printf("branch dipho_subleadIDMVA_branch does not exist!\n");
      exit(1);
    }
    dipho_subleadIDMVA_isLoaded = true;
  }
  return dipho_subleadIDMVA_;
}

const float &tprimetHHadronic::dipho_sublead_elveto() {
  if (not dipho_sublead_elveto_isLoaded) {
    if (dipho_sublead_elveto_branch != 0) {
      dipho_sublead_elveto_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_elveto_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_elveto_isLoaded = true;
  }
  return dipho_sublead_elveto_;
}

const float &tprimetHHadronic::dipho_sulead_prompt() {
  if (not dipho_sulead_prompt_isLoaded) {
    if (dipho_sulead_prompt_branch != 0) {
      dipho_sulead_prompt_branch->GetEntry(index);
    } else {
      printf("branch dipho_sulead_prompt_branch does not exist!\n");
      exit(1);
    }
    dipho_sulead_prompt_isLoaded = true;
  }
  return dipho_sulead_prompt_;
}

const float &tprimetHHadronic::dipho_sublead_chiso() {
  if (not dipho_sublead_chiso_isLoaded) {
    if (dipho_sublead_chiso_branch != 0) {
      dipho_sublead_chiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_chiso_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_chiso_isLoaded = true;
  }
  return dipho_sublead_chiso_;
}

const float &tprimetHHadronic::dipho_sublead_chisow() {
  if (not dipho_sublead_chisow_isLoaded) {
    if (dipho_sublead_chisow_branch != 0) {
      dipho_sublead_chisow_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_chisow_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_chisow_isLoaded = true;
  }
  return dipho_sublead_chisow_;
}

const float &tprimetHHadronic::dipho_sublead_phoiso() {
  if (not dipho_sublead_phoiso_isLoaded) {
    if (dipho_sublead_phoiso_branch != 0) {
      dipho_sublead_phoiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_phoiso_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_phoiso_isLoaded = true;
  }
  return dipho_sublead_phoiso_;
}

const float &tprimetHHadronic::dipho_sublead_phoiso04() {
  if (not dipho_sublead_phoiso04_isLoaded) {
    if (dipho_sublead_phoiso04_branch != 0) {
      dipho_sublead_phoiso04_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_phoiso04_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_phoiso04_isLoaded = true;
  }
  return dipho_sublead_phoiso04_;
}

const float &tprimetHHadronic::dipho_sublead_neutiso() {
  if (not dipho_sublead_neutiso_isLoaded) {
    if (dipho_sublead_neutiso_branch != 0) {
      dipho_sublead_neutiso_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_neutiso_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_neutiso_isLoaded = true;
  }
  return dipho_sublead_neutiso_;
}

const float &tprimetHHadronic::dipho_sublead_ecaliso03() {
  if (not dipho_sublead_ecaliso03_isLoaded) {
    if (dipho_sublead_ecaliso03_branch != 0) {
      dipho_sublead_ecaliso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_ecaliso03_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_ecaliso03_isLoaded = true;
  }
  return dipho_sublead_ecaliso03_;
}

const float &tprimetHHadronic::dipho_sublead_hcaliso03() {
  if (not dipho_sublead_hcaliso03_isLoaded) {
    if (dipho_sublead_hcaliso03_branch != 0) {
      dipho_sublead_hcaliso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_hcaliso03_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_hcaliso03_isLoaded = true;
  }
  return dipho_sublead_hcaliso03_;
}

const float &tprimetHHadronic::dipho_sublead_pfcluecal03() {
  if (not dipho_sublead_pfcluecal03_isLoaded) {
    if (dipho_sublead_pfcluecal03_branch != 0) {
      dipho_sublead_pfcluecal03_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_pfcluecal03_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_pfcluecal03_isLoaded = true;
  }
  return dipho_sublead_pfcluecal03_;
}

const float &tprimetHHadronic::dipho_sublead_pfcluhcal03() {
  if (not dipho_sublead_pfcluhcal03_isLoaded) {
    if (dipho_sublead_pfcluhcal03_branch != 0) {
      dipho_sublead_pfcluhcal03_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_pfcluhcal03_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_pfcluhcal03_isLoaded = true;
  }
  return dipho_sublead_pfcluhcal03_;
}

const float &tprimetHHadronic::dipho_sublead_trkiso03() {
  if (not dipho_sublead_trkiso03_isLoaded) {
    if (dipho_sublead_trkiso03_branch != 0) {
      dipho_sublead_trkiso03_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_trkiso03_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_trkiso03_isLoaded = true;
  }
  return dipho_sublead_trkiso03_;
}

const float &tprimetHHadronic::dipho_sublead_pfchiso2() {
  if (not dipho_sublead_pfchiso2_isLoaded) {
    if (dipho_sublead_pfchiso2_branch != 0) {
      dipho_sublead_pfchiso2_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_pfchiso2_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_pfchiso2_isLoaded = true;
  }
  return dipho_sublead_pfchiso2_;
}

const float &tprimetHHadronic::dipho_sublead_haspixelseed() {
  if (not dipho_sublead_haspixelseed_isLoaded) {
    if (dipho_sublead_haspixelseed_branch != 0) {
      dipho_sublead_haspixelseed_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_haspixelseed_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_haspixelseed_isLoaded = true;
  }
  return dipho_sublead_haspixelseed_;
}

const float &tprimetHHadronic::dipho_sublead_sieip() {
  if (not dipho_sublead_sieip_isLoaded) {
    if (dipho_sublead_sieip_branch != 0) {
      dipho_sublead_sieip_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_sieip_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_sieip_isLoaded = true;
  }
  return dipho_sublead_sieip_;
}

const float &tprimetHHadronic::dipho_sublead_etawidth() {
  if (not dipho_sublead_etawidth_isLoaded) {
    if (dipho_sublead_etawidth_branch != 0) {
      dipho_sublead_etawidth_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_etawidth_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_etawidth_isLoaded = true;
  }
  return dipho_sublead_etawidth_;
}

const float &tprimetHHadronic::dipho_sublead_phiwidth() {
  if (not dipho_sublead_phiwidth_isLoaded) {
    if (dipho_sublead_phiwidth_branch != 0) {
      dipho_sublead_phiwidth_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_phiwidth_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_phiwidth_isLoaded = true;
  }
  return dipho_sublead_phiwidth_;
}

const float &tprimetHHadronic::dipho_sublead_regrerr() {
  if (not dipho_sublead_regrerr_isLoaded) {
    if (dipho_sublead_regrerr_branch != 0) {
      dipho_sublead_regrerr_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_regrerr_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_regrerr_isLoaded = true;
  }
  return dipho_sublead_regrerr_;
}

const float &tprimetHHadronic::dipho_sublead_s4ratio() {
  if (not dipho_sublead_s4ratio_isLoaded) {
    if (dipho_sublead_s4ratio_branch != 0) {
      dipho_sublead_s4ratio_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_s4ratio_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_s4ratio_isLoaded = true;
  }
  return dipho_sublead_s4ratio_;
}

const float &tprimetHHadronic::dipho_sublead_effSigma() {
  if (not dipho_sublead_effSigma_isLoaded) {
    if (dipho_sublead_effSigma_branch != 0) {
      dipho_sublead_effSigma_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_effSigma_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_effSigma_isLoaded = true;
  }
  return dipho_sublead_effSigma_;
}

const float &tprimetHHadronic::dipho_sublead_scraw() {
  if (not dipho_sublead_scraw_isLoaded) {
    if (dipho_sublead_scraw_branch != 0) {
      dipho_sublead_scraw_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_scraw_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_scraw_isLoaded = true;
  }
  return dipho_sublead_scraw_;
}

const float &tprimetHHadronic::dipho_sublead_ese() {
  if (not dipho_sublead_ese_isLoaded) {
    if (dipho_sublead_ese_branch != 0) {
      dipho_sublead_ese_branch->GetEntry(index);
    } else {
      printf("branch dipho_sublead_ese_branch does not exist!\n");
      exit(1);
    }
    dipho_sublead_ese_isLoaded = true;
  }
  return dipho_sublead_ese_;
}

const float &tprimetHHadronic::LeptonType() {
  if (not LeptonType_isLoaded) {
    if (LeptonType_branch != 0) {
      LeptonType_branch->GetEntry(index);
    } else {
      printf("branch LeptonType_branch does not exist!\n");
      exit(1);
    }
    LeptonType_isLoaded = true;
  }
  return LeptonType_;
}

const float &tprimetHHadronic::n_ele() {
  if (not n_ele_isLoaded) {
    if (n_ele_branch != 0) {
      n_ele_branch->GetEntry(index);
    } else {
      printf("branch n_ele_branch does not exist!\n");
      exit(1);
    }
    n_ele_isLoaded = true;
  }
  return n_ele_;
}

const float &tprimetHHadronic::n_loose_ele() {
  if (not n_loose_ele_isLoaded) {
    if (n_loose_ele_branch != 0) {
      n_loose_ele_branch->GetEntry(index);
    } else {
      printf("branch n_loose_ele_branch does not exist!\n");
      exit(1);
    }
    n_loose_ele_isLoaded = true;
  }
  return n_loose_ele_;
}

const float &tprimetHHadronic::n_veto_ele() {
  if (not n_veto_ele_isLoaded) {
    if (n_veto_ele_branch != 0) {
      n_veto_ele_branch->GetEntry(index);
    } else {
      printf("branch n_veto_ele_branch does not exist!\n");
      exit(1);
    }
    n_veto_ele_isLoaded = true;
  }
  return n_veto_ele_;
}

const float &tprimetHHadronic::n_medium_ele() {
  if (not n_medium_ele_isLoaded) {
    if (n_medium_ele_branch != 0) {
      n_medium_ele_branch->GetEntry(index);
    } else {
      printf("branch n_medium_ele_branch does not exist!\n");
      exit(1);
    }
    n_medium_ele_isLoaded = true;
  }
  return n_medium_ele_;
}

const float &tprimetHHadronic::n_tight_ele() {
  if (not n_tight_ele_isLoaded) {
    if (n_tight_ele_branch != 0) {
      n_tight_ele_branch->GetEntry(index);
    } else {
      printf("branch n_tight_ele_branch does not exist!\n");
      exit(1);
    }
    n_tight_ele_isLoaded = true;
  }
  return n_tight_ele_;
}

const float &tprimetHHadronic::ele1_pt() {
  if (not ele1_pt_isLoaded) {
    if (ele1_pt_branch != 0) {
      ele1_pt_branch->GetEntry(index);
    } else {
      printf("branch ele1_pt_branch does not exist!\n");
      exit(1);
    }
    ele1_pt_isLoaded = true;
  }
  return ele1_pt_;
}

const float &tprimetHHadronic::ele2_pt() {
  if (not ele2_pt_isLoaded) {
    if (ele2_pt_branch != 0) {
      ele2_pt_branch->GetEntry(index);
    } else {
      printf("branch ele2_pt_branch does not exist!\n");
      exit(1);
    }
    ele2_pt_isLoaded = true;
  }
  return ele2_pt_;
}

const float &tprimetHHadronic::ele1_eta() {
  if (not ele1_eta_isLoaded) {
    if (ele1_eta_branch != 0) {
      ele1_eta_branch->GetEntry(index);
    } else {
      printf("branch ele1_eta_branch does not exist!\n");
      exit(1);
    }
    ele1_eta_isLoaded = true;
  }
  return ele1_eta_;
}

const float &tprimetHHadronic::ele2_eta() {
  if (not ele2_eta_isLoaded) {
    if (ele2_eta_branch != 0) {
      ele2_eta_branch->GetEntry(index);
    } else {
      printf("branch ele2_eta_branch does not exist!\n");
      exit(1);
    }
    ele2_eta_isLoaded = true;
  }
  return ele2_eta_;
}

const float &tprimetHHadronic::ele1_phi() {
  if (not ele1_phi_isLoaded) {
    if (ele1_phi_branch != 0) {
      ele1_phi_branch->GetEntry(index);
    } else {
      printf("branch ele1_phi_branch does not exist!\n");
      exit(1);
    }
    ele1_phi_isLoaded = true;
  }
  return ele1_phi_;
}

const float &tprimetHHadronic::ele2_phi() {
  if (not ele2_phi_isLoaded) {
    if (ele2_phi_branch != 0) {
      ele2_phi_branch->GetEntry(index);
    } else {
      printf("branch ele2_phi_branch does not exist!\n");
      exit(1);
    }
    ele2_phi_isLoaded = true;
  }
  return ele2_phi_;
}

const float &tprimetHHadronic::ele1_e() {
  if (not ele1_e_isLoaded) {
    if (ele1_e_branch != 0) {
      ele1_e_branch->GetEntry(index);
    } else {
      printf("branch ele1_e_branch does not exist!\n");
      exit(1);
    }
    ele1_e_isLoaded = true;
  }
  return ele1_e_;
}

const float &tprimetHHadronic::ele2_e() {
  if (not ele2_e_isLoaded) {
    if (ele2_e_branch != 0) {
      ele2_e_branch->GetEntry(index);
    } else {
      printf("branch ele2_e_branch does not exist!\n");
      exit(1);
    }
    ele2_e_isLoaded = true;
  }
  return ele2_e_;
}

const float &tprimetHHadronic::ele1_ch() {
  if (not ele1_ch_isLoaded) {
    if (ele1_ch_branch != 0) {
      ele1_ch_branch->GetEntry(index);
    } else {
      printf("branch ele1_ch_branch does not exist!\n");
      exit(1);
    }
    ele1_ch_isLoaded = true;
  }
  return ele1_ch_;
}

const float &tprimetHHadronic::ele2_ch() {
  if (not ele2_ch_isLoaded) {
    if (ele2_ch_branch != 0) {
      ele2_ch_branch->GetEntry(index);
    } else {
      printf("branch ele2_ch_branch does not exist!\n");
      exit(1);
    }
    ele2_ch_isLoaded = true;
  }
  return ele2_ch_;
}

const float &tprimetHHadronic::ele1_sigmaIetaIeta() {
  if (not ele1_sigmaIetaIeta_isLoaded) {
    if (ele1_sigmaIetaIeta_branch != 0) {
      ele1_sigmaIetaIeta_branch->GetEntry(index);
    } else {
      printf("branch ele1_sigmaIetaIeta_branch does not exist!\n");
      exit(1);
    }
    ele1_sigmaIetaIeta_isLoaded = true;
  }
  return ele1_sigmaIetaIeta_;
}

const float &tprimetHHadronic::ele2_sigmaIetaIeta() {
  if (not ele2_sigmaIetaIeta_isLoaded) {
    if (ele2_sigmaIetaIeta_branch != 0) {
      ele2_sigmaIetaIeta_branch->GetEntry(index);
    } else {
      printf("branch ele2_sigmaIetaIeta_branch does not exist!\n");
      exit(1);
    }
    ele2_sigmaIetaIeta_isLoaded = true;
  }
  return ele2_sigmaIetaIeta_;
}

const float &tprimetHHadronic::ele1_dEtaInSeed() {
  if (not ele1_dEtaInSeed_isLoaded) {
    if (ele1_dEtaInSeed_branch != 0) {
      ele1_dEtaInSeed_branch->GetEntry(index);
    } else {
      printf("branch ele1_dEtaInSeed_branch does not exist!\n");
      exit(1);
    }
    ele1_dEtaInSeed_isLoaded = true;
  }
  return ele1_dEtaInSeed_;
}

const float &tprimetHHadronic::ele2_dEtaInSeed() {
  if (not ele2_dEtaInSeed_isLoaded) {
    if (ele2_dEtaInSeed_branch != 0) {
      ele2_dEtaInSeed_branch->GetEntry(index);
    } else {
      printf("branch ele2_dEtaInSeed_branch does not exist!\n");
      exit(1);
    }
    ele2_dEtaInSeed_isLoaded = true;
  }
  return ele2_dEtaInSeed_;
}

const float &tprimetHHadronic::ele1_dPhiIn() {
  if (not ele1_dPhiIn_isLoaded) {
    if (ele1_dPhiIn_branch != 0) {
      ele1_dPhiIn_branch->GetEntry(index);
    } else {
      printf("branch ele1_dPhiIn_branch does not exist!\n");
      exit(1);
    }
    ele1_dPhiIn_isLoaded = true;
  }
  return ele1_dPhiIn_;
}

const float &tprimetHHadronic::ele2_dPhiIn() {
  if (not ele2_dPhiIn_isLoaded) {
    if (ele2_dPhiIn_branch != 0) {
      ele2_dPhiIn_branch->GetEntry(index);
    } else {
      printf("branch ele2_dPhiIn_branch does not exist!\n");
      exit(1);
    }
    ele2_dPhiIn_isLoaded = true;
  }
  return ele2_dPhiIn_;
}

const float &tprimetHHadronic::ele1_hOverE() {
  if (not ele1_hOverE_isLoaded) {
    if (ele1_hOverE_branch != 0) {
      ele1_hOverE_branch->GetEntry(index);
    } else {
      printf("branch ele1_hOverE_branch does not exist!\n");
      exit(1);
    }
    ele1_hOverE_isLoaded = true;
  }
  return ele1_hOverE_;
}

const float &tprimetHHadronic::ele2_hOverE() {
  if (not ele2_hOverE_isLoaded) {
    if (ele2_hOverE_branch != 0) {
      ele2_hOverE_branch->GetEntry(index);
    } else {
      printf("branch ele2_hOverE_branch does not exist!\n");
      exit(1);
    }
    ele2_hOverE_isLoaded = true;
  }
  return ele2_hOverE_;
}

const float &tprimetHHadronic::ele1_RelIsoEA() {
  if (not ele1_RelIsoEA_isLoaded) {
    if (ele1_RelIsoEA_branch != 0) {
      ele1_RelIsoEA_branch->GetEntry(index);
    } else {
      printf("branch ele1_RelIsoEA_branch does not exist!\n");
      exit(1);
    }
    ele1_RelIsoEA_isLoaded = true;
  }
  return ele1_RelIsoEA_;
}

const float &tprimetHHadronic::ele2_RelIsoEA() {
  if (not ele2_RelIsoEA_isLoaded) {
    if (ele2_RelIsoEA_branch != 0) {
      ele2_RelIsoEA_branch->GetEntry(index);
    } else {
      printf("branch ele2_RelIsoEA_branch does not exist!\n");
      exit(1);
    }
    ele2_RelIsoEA_isLoaded = true;
  }
  return ele2_RelIsoEA_;
}

const float &tprimetHHadronic::ele1_ooEmooP() {
  if (not ele1_ooEmooP_isLoaded) {
    if (ele1_ooEmooP_branch != 0) {
      ele1_ooEmooP_branch->GetEntry(index);
    } else {
      printf("branch ele1_ooEmooP_branch does not exist!\n");
      exit(1);
    }
    ele1_ooEmooP_isLoaded = true;
  }
  return ele1_ooEmooP_;
}

const float &tprimetHHadronic::ele2_ooEmooP() {
  if (not ele2_ooEmooP_isLoaded) {
    if (ele2_ooEmooP_branch != 0) {
      ele2_ooEmooP_branch->GetEntry(index);
    } else {
      printf("branch ele2_ooEmooP_branch does not exist!\n");
      exit(1);
    }
    ele2_ooEmooP_isLoaded = true;
  }
  return ele2_ooEmooP_;
}

const float &tprimetHHadronic::ele1_dxy() {
  if (not ele1_dxy_isLoaded) {
    if (ele1_dxy_branch != 0) {
      ele1_dxy_branch->GetEntry(index);
    } else {
      printf("branch ele1_dxy_branch does not exist!\n");
      exit(1);
    }
    ele1_dxy_isLoaded = true;
  }
  return ele1_dxy_;
}

const float &tprimetHHadronic::ele2_dxy() {
  if (not ele2_dxy_isLoaded) {
    if (ele2_dxy_branch != 0) {
      ele2_dxy_branch->GetEntry(index);
    } else {
      printf("branch ele2_dxy_branch does not exist!\n");
      exit(1);
    }
    ele2_dxy_isLoaded = true;
  }
  return ele2_dxy_;
}

const float &tprimetHHadronic::ele1_diphodxy() {
  if (not ele1_diphodxy_isLoaded) {
    if (ele1_diphodxy_branch != 0) {
      ele1_diphodxy_branch->GetEntry(index);
    } else {
      printf("branch ele1_diphodxy_branch does not exist!\n");
      exit(1);
    }
    ele1_diphodxy_isLoaded = true;
  }
  return ele1_diphodxy_;
}

const float &tprimetHHadronic::ele2_diphodxy() {
  if (not ele2_diphodxy_isLoaded) {
    if (ele2_diphodxy_branch != 0) {
      ele2_diphodxy_branch->GetEntry(index);
    } else {
      printf("branch ele2_diphodxy_branch does not exist!\n");
      exit(1);
    }
    ele2_diphodxy_isLoaded = true;
  }
  return ele2_diphodxy_;
}

const float &tprimetHHadronic::ele1_dz() {
  if (not ele1_dz_isLoaded) {
    if (ele1_dz_branch != 0) {
      ele1_dz_branch->GetEntry(index);
    } else {
      printf("branch ele1_dz_branch does not exist!\n");
      exit(1);
    }
    ele1_dz_isLoaded = true;
  }
  return ele1_dz_;
}

const float &tprimetHHadronic::ele2_dz() {
  if (not ele2_dz_isLoaded) {
    if (ele2_dz_branch != 0) {
      ele2_dz_branch->GetEntry(index);
    } else {
      printf("branch ele2_dz_branch does not exist!\n");
      exit(1);
    }
    ele2_dz_isLoaded = true;
  }
  return ele2_dz_;
}

const float &tprimetHHadronic::ele1_diphodz() {
  if (not ele1_diphodz_isLoaded) {
    if (ele1_diphodz_branch != 0) {
      ele1_diphodz_branch->GetEntry(index);
    } else {
      printf("branch ele1_diphodz_branch does not exist!\n");
      exit(1);
    }
    ele1_diphodz_isLoaded = true;
  }
  return ele1_diphodz_;
}

const float &tprimetHHadronic::ele2_diphodz() {
  if (not ele2_diphodz_isLoaded) {
    if (ele2_diphodz_branch != 0) {
      ele2_diphodz_branch->GetEntry(index);
    } else {
      printf("branch ele2_diphodz_branch does not exist!\n");
      exit(1);
    }
    ele2_diphodz_isLoaded = true;
  }
  return ele2_diphodz_;
}

const float &tprimetHHadronic::ele1_misHits() {
  if (not ele1_misHits_isLoaded) {
    if (ele1_misHits_branch != 0) {
      ele1_misHits_branch->GetEntry(index);
    } else {
      printf("branch ele1_misHits_branch does not exist!\n");
      exit(1);
    }
    ele1_misHits_isLoaded = true;
  }
  return ele1_misHits_;
}

const float &tprimetHHadronic::ele2_misHits() {
  if (not ele2_misHits_isLoaded) {
    if (ele2_misHits_branch != 0) {
      ele2_misHits_branch->GetEntry(index);
    } else {
      printf("branch ele2_misHits_branch does not exist!\n");
      exit(1);
    }
    ele2_misHits_isLoaded = true;
  }
  return ele2_misHits_;
}

const float &tprimetHHadronic::ele1_ConversionVeto() {
  if (not ele1_ConversionVeto_isLoaded) {
    if (ele1_ConversionVeto_branch != 0) {
      ele1_ConversionVeto_branch->GetEntry(index);
    } else {
      printf("branch ele1_ConversionVeto_branch does not exist!\n");
      exit(1);
    }
    ele1_ConversionVeto_isLoaded = true;
  }
  return ele1_ConversionVeto_;
}

const float &tprimetHHadronic::ele2_ConversionVeto() {
  if (not ele2_ConversionVeto_isLoaded) {
    if (ele2_ConversionVeto_branch != 0) {
      ele2_ConversionVeto_branch->GetEntry(index);
    } else {
      printf("branch ele2_ConversionVeto_branch does not exist!\n");
      exit(1);
    }
    ele2_ConversionVeto_isLoaded = true;
  }
  return ele2_ConversionVeto_;
}

const float &tprimetHHadronic::ele1_ChargedHadronPt() {
  if (not ele1_ChargedHadronPt_isLoaded) {
    if (ele1_ChargedHadronPt_branch != 0) {
      ele1_ChargedHadronPt_branch->GetEntry(index);
    } else {
      printf("branch ele1_ChargedHadronPt_branch does not exist!\n");
      exit(1);
    }
    ele1_ChargedHadronPt_isLoaded = true;
  }
  return ele1_ChargedHadronPt_;
}

const float &tprimetHHadronic::ele2_ChargedHadronPt() {
  if (not ele2_ChargedHadronPt_isLoaded) {
    if (ele2_ChargedHadronPt_branch != 0) {
      ele2_ChargedHadronPt_branch->GetEntry(index);
    } else {
      printf("branch ele2_ChargedHadronPt_branch does not exist!\n");
      exit(1);
    }
    ele2_ChargedHadronPt_isLoaded = true;
  }
  return ele2_ChargedHadronPt_;
}

const float &tprimetHHadronic::ele2_NeutralHadronEt() {
  if (not ele2_NeutralHadronEt_isLoaded) {
    if (ele2_NeutralHadronEt_branch != 0) {
      ele2_NeutralHadronEt_branch->GetEntry(index);
    } else {
      printf("branch ele2_NeutralHadronEt_branch does not exist!\n");
      exit(1);
    }
    ele2_NeutralHadronEt_isLoaded = true;
  }
  return ele2_NeutralHadronEt_;
}

const float &tprimetHHadronic::ele1_NeutralHadronEt() {
  if (not ele1_NeutralHadronEt_isLoaded) {
    if (ele1_NeutralHadronEt_branch != 0) {
      ele1_NeutralHadronEt_branch->GetEntry(index);
    } else {
      printf("branch ele1_NeutralHadronEt_branch does not exist!\n");
      exit(1);
    }
    ele1_NeutralHadronEt_isLoaded = true;
  }
  return ele1_NeutralHadronEt_;
}

const float &tprimetHHadronic::ele1_PhotonEt() {
  if (not ele1_PhotonEt_isLoaded) {
    if (ele1_PhotonEt_branch != 0) {
      ele1_PhotonEt_branch->GetEntry(index);
    } else {
      printf("branch ele1_PhotonEt_branch does not exist!\n");
      exit(1);
    }
    ele1_PhotonEt_isLoaded = true;
  }
  return ele1_PhotonEt_;
}

const float &tprimetHHadronic::ele2_PhotonEt() {
  if (not ele2_PhotonEt_isLoaded) {
    if (ele2_PhotonEt_branch != 0) {
      ele2_PhotonEt_branch->GetEntry(index);
    } else {
      printf("branch ele2_PhotonEt_branch does not exist!\n");
      exit(1);
    }
    ele2_PhotonEt_isLoaded = true;
  }
  return ele2_PhotonEt_;
}

const float &tprimetHHadronic::ele1_PassTight() {
  if (not ele1_PassTight_isLoaded) {
    if (ele1_PassTight_branch != 0) {
      ele1_PassTight_branch->GetEntry(index);
    } else {
      printf("branch ele1_PassTight_branch does not exist!\n");
      exit(1);
    }
    ele1_PassTight_isLoaded = true;
  }
  return ele1_PassTight_;
}

const float &tprimetHHadronic::ele2_PassTight() {
  if (not ele2_PassTight_isLoaded) {
    if (ele2_PassTight_branch != 0) {
      ele2_PassTight_branch->GetEntry(index);
    } else {
      printf("branch ele2_PassTight_branch does not exist!\n");
      exit(1);
    }
    ele2_PassTight_isLoaded = true;
  }
  return ele2_PassTight_;
}

const float &tprimetHHadronic::ele1_PassVeto() {
  if (not ele1_PassVeto_isLoaded) {
    if (ele1_PassVeto_branch != 0) {
      ele1_PassVeto_branch->GetEntry(index);
    } else {
      printf("branch ele1_PassVeto_branch does not exist!\n");
      exit(1);
    }
    ele1_PassVeto_isLoaded = true;
  }
  return ele1_PassVeto_;
}

const float &tprimetHHadronic::ele2_PassVeto() {
  if (not ele2_PassVeto_isLoaded) {
    if (ele2_PassVeto_branch != 0) {
      ele2_PassVeto_branch->GetEntry(index);
    } else {
      printf("branch ele2_PassVeto_branch does not exist!\n");
      exit(1);
    }
    ele2_PassVeto_isLoaded = true;
  }
  return ele2_PassVeto_;
}

const float &tprimetHHadronic::ele1_dPhiMET() {
  if (not ele1_dPhiMET_isLoaded) {
    if (ele1_dPhiMET_branch != 0) {
      ele1_dPhiMET_branch->GetEntry(index);
    } else {
      printf("branch ele1_dPhiMET_branch does not exist!\n");
      exit(1);
    }
    ele1_dPhiMET_isLoaded = true;
  }
  return ele1_dPhiMET_;
}

const float &tprimetHHadronic::ele2_dPhiMET() {
  if (not ele2_dPhiMET_isLoaded) {
    if (ele2_dPhiMET_branch != 0) {
      ele2_dPhiMET_branch->GetEntry(index);
    } else {
      printf("branch ele2_dPhiMET_branch does not exist!\n");
      exit(1);
    }
    ele2_dPhiMET_isLoaded = true;
  }
  return ele2_dPhiMET_;
}

const float &tprimetHHadronic::n_muons() {
  if (not n_muons_isLoaded) {
    if (n_muons_branch != 0) {
      n_muons_branch->GetEntry(index);
    } else {
      printf("branch n_muons_branch does not exist!\n");
      exit(1);
    }
    n_muons_isLoaded = true;
  }
  return n_muons_;
}

const float &tprimetHHadronic::n_LooseMu25() {
  if (not n_LooseMu25_isLoaded) {
    if (n_LooseMu25_branch != 0) {
      n_LooseMu25_branch->GetEntry(index);
    } else {
      printf("branch n_LooseMu25_branch does not exist!\n");
      exit(1);
    }
    n_LooseMu25_isLoaded = true;
  }
  return n_LooseMu25_;
}

const float &tprimetHHadronic::n_LooseMu15() {
  if (not n_LooseMu15_isLoaded) {
    if (n_LooseMu15_branch != 0) {
      n_LooseMu15_branch->GetEntry(index);
    } else {
      printf("branch n_LooseMu15_branch does not exist!\n");
      exit(1);
    }
    n_LooseMu15_isLoaded = true;
  }
  return n_LooseMu15_;
}

const float &tprimetHHadronic::n_TightMu25() {
  if (not n_TightMu25_isLoaded) {
    if (n_TightMu25_branch != 0) {
      n_TightMu25_branch->GetEntry(index);
    } else {
      printf("branch n_TightMu25_branch does not exist!\n");
      exit(1);
    }
    n_TightMu25_isLoaded = true;
  }
  return n_TightMu25_;
}

const float &tprimetHHadronic::n_TightMu15() {
  if (not n_TightMu15_isLoaded) {
    if (n_TightMu15_branch != 0) {
      n_TightMu15_branch->GetEntry(index);
    } else {
      printf("branch n_TightMu15_branch does not exist!\n");
      exit(1);
    }
    n_TightMu15_isLoaded = true;
  }
  return n_TightMu15_;
}

const float &tprimetHHadronic::n_MediumMu25() {
  if (not n_MediumMu25_isLoaded) {
    if (n_MediumMu25_branch != 0) {
      n_MediumMu25_branch->GetEntry(index);
    } else {
      printf("branch n_MediumMu25_branch does not exist!\n");
      exit(1);
    }
    n_MediumMu25_isLoaded = true;
  }
  return n_MediumMu25_;
}

const float &tprimetHHadronic::n_MediumMu15() {
  if (not n_MediumMu15_isLoaded) {
    if (n_MediumMu15_branch != 0) {
      n_MediumMu15_branch->GetEntry(index);
    } else {
      printf("branch n_MediumMu15_branch does not exist!\n");
      exit(1);
    }
    n_MediumMu15_isLoaded = true;
  }
  return n_MediumMu15_;
}

const float &tprimetHHadronic::muon1_pt() {
  if (not muon1_pt_isLoaded) {
    if (muon1_pt_branch != 0) {
      muon1_pt_branch->GetEntry(index);
    } else {
      printf("branch muon1_pt_branch does not exist!\n");
      exit(1);
    }
    muon1_pt_isLoaded = true;
  }
  return muon1_pt_;
}

const float &tprimetHHadronic::muon2_pt() {
  if (not muon2_pt_isLoaded) {
    if (muon2_pt_branch != 0) {
      muon2_pt_branch->GetEntry(index);
    } else {
      printf("branch muon2_pt_branch does not exist!\n");
      exit(1);
    }
    muon2_pt_isLoaded = true;
  }
  return muon2_pt_;
}

const float &tprimetHHadronic::muon1_eta() {
  if (not muon1_eta_isLoaded) {
    if (muon1_eta_branch != 0) {
      muon1_eta_branch->GetEntry(index);
    } else {
      printf("branch muon1_eta_branch does not exist!\n");
      exit(1);
    }
    muon1_eta_isLoaded = true;
  }
  return muon1_eta_;
}

const float &tprimetHHadronic::muon2_eta() {
  if (not muon2_eta_isLoaded) {
    if (muon2_eta_branch != 0) {
      muon2_eta_branch->GetEntry(index);
    } else {
      printf("branch muon2_eta_branch does not exist!\n");
      exit(1);
    }
    muon2_eta_isLoaded = true;
  }
  return muon2_eta_;
}

const float &tprimetHHadronic::muon1_phi() {
  if (not muon1_phi_isLoaded) {
    if (muon1_phi_branch != 0) {
      muon1_phi_branch->GetEntry(index);
    } else {
      printf("branch muon1_phi_branch does not exist!\n");
      exit(1);
    }
    muon1_phi_isLoaded = true;
  }
  return muon1_phi_;
}

const float &tprimetHHadronic::muon2_phi() {
  if (not muon2_phi_isLoaded) {
    if (muon2_phi_branch != 0) {
      muon2_phi_branch->GetEntry(index);
    } else {
      printf("branch muon2_phi_branch does not exist!\n");
      exit(1);
    }
    muon2_phi_isLoaded = true;
  }
  return muon2_phi_;
}

const float &tprimetHHadronic::muon1_e() {
  if (not muon1_e_isLoaded) {
    if (muon1_e_branch != 0) {
      muon1_e_branch->GetEntry(index);
    } else {
      printf("branch muon1_e_branch does not exist!\n");
      exit(1);
    }
    muon1_e_isLoaded = true;
  }
  return muon1_e_;
}

const float &tprimetHHadronic::muon2_e() {
  if (not muon2_e_isLoaded) {
    if (muon2_e_branch != 0) {
      muon2_e_branch->GetEntry(index);
    } else {
      printf("branch muon2_e_branch does not exist!\n");
      exit(1);
    }
    muon2_e_isLoaded = true;
  }
  return muon2_e_;
}

const float &tprimetHHadronic::muon1_ch() {
  if (not muon1_ch_isLoaded) {
    if (muon1_ch_branch != 0) {
      muon1_ch_branch->GetEntry(index);
    } else {
      printf("branch muon1_ch_branch does not exist!\n");
      exit(1);
    }
    muon1_ch_isLoaded = true;
  }
  return muon1_ch_;
}

const float &tprimetHHadronic::muon2_ch() {
  if (not muon2_ch_isLoaded) {
    if (muon2_ch_branch != 0) {
      muon2_ch_branch->GetEntry(index);
    } else {
      printf("branch muon2_ch_branch does not exist!\n");
      exit(1);
    }
    muon2_ch_isLoaded = true;
  }
  return muon2_ch_;
}

const float &tprimetHHadronic::muon1_iso() {
  if (not muon1_iso_isLoaded) {
    if (muon1_iso_branch != 0) {
      muon1_iso_branch->GetEntry(index);
    } else {
      printf("branch muon1_iso_branch does not exist!\n");
      exit(1);
    }
    muon1_iso_isLoaded = true;
  }
  return muon1_iso_;
}

const float &tprimetHHadronic::muon2_iso() {
  if (not muon2_iso_isLoaded) {
    if (muon2_iso_branch != 0) {
      muon2_iso_branch->GetEntry(index);
    } else {
      printf("branch muon2_iso_branch does not exist!\n");
      exit(1);
    }
    muon2_iso_isLoaded = true;
  }
  return muon2_iso_;
}

const float &tprimetHHadronic::muon1_chi2() {
  if (not muon1_chi2_isLoaded) {
    if (muon1_chi2_branch != 0) {
      muon1_chi2_branch->GetEntry(index);
    } else {
      printf("branch muon1_chi2_branch does not exist!\n");
      exit(1);
    }
    muon1_chi2_isLoaded = true;
  }
  return muon1_chi2_;
}

const float &tprimetHHadronic::muon2_chi2() {
  if (not muon2_chi2_isLoaded) {
    if (muon2_chi2_branch != 0) {
      muon2_chi2_branch->GetEntry(index);
    } else {
      printf("branch muon2_chi2_branch does not exist!\n");
      exit(1);
    }
    muon2_chi2_isLoaded = true;
  }
  return muon2_chi2_;
}

const float &tprimetHHadronic::muon1_mHits() {
  if (not muon1_mHits_isLoaded) {
    if (muon1_mHits_branch != 0) {
      muon1_mHits_branch->GetEntry(index);
    } else {
      printf("branch muon1_mHits_branch does not exist!\n");
      exit(1);
    }
    muon1_mHits_isLoaded = true;
  }
  return muon1_mHits_;
}

const float &tprimetHHadronic::muon2_mHits() {
  if (not muon2_mHits_isLoaded) {
    if (muon2_mHits_branch != 0) {
      muon2_mHits_branch->GetEntry(index);
    } else {
      printf("branch muon2_mHits_branch does not exist!\n");
      exit(1);
    }
    muon2_mHits_isLoaded = true;
  }
  return muon2_mHits_;
}

const float &tprimetHHadronic::muon1_mStations() {
  if (not muon1_mStations_isLoaded) {
    if (muon1_mStations_branch != 0) {
      muon1_mStations_branch->GetEntry(index);
    } else {
      printf("branch muon1_mStations_branch does not exist!\n");
      exit(1);
    }
    muon1_mStations_isLoaded = true;
  }
  return muon1_mStations_;
}

const float &tprimetHHadronic::muon2_mStations() {
  if (not muon2_mStations_isLoaded) {
    if (muon2_mStations_branch != 0) {
      muon2_mStations_branch->GetEntry(index);
    } else {
      printf("branch muon2_mStations_branch does not exist!\n");
      exit(1);
    }
    muon2_mStations_isLoaded = true;
  }
  return muon2_mStations_;
}

const float &tprimetHHadronic::muon1_dxy() {
  if (not muon1_dxy_isLoaded) {
    if (muon1_dxy_branch != 0) {
      muon1_dxy_branch->GetEntry(index);
    } else {
      printf("branch muon1_dxy_branch does not exist!\n");
      exit(1);
    }
    muon1_dxy_isLoaded = true;
  }
  return muon1_dxy_;
}

const float &tprimetHHadronic::muon2_dxy() {
  if (not muon2_dxy_isLoaded) {
    if (muon2_dxy_branch != 0) {
      muon2_dxy_branch->GetEntry(index);
    } else {
      printf("branch muon2_dxy_branch does not exist!\n");
      exit(1);
    }
    muon2_dxy_isLoaded = true;
  }
  return muon2_dxy_;
}

const float &tprimetHHadronic::muon1_diphodxy() {
  if (not muon1_diphodxy_isLoaded) {
    if (muon1_diphodxy_branch != 0) {
      muon1_diphodxy_branch->GetEntry(index);
    } else {
      printf("branch muon1_diphodxy_branch does not exist!\n");
      exit(1);
    }
    muon1_diphodxy_isLoaded = true;
  }
  return muon1_diphodxy_;
}

const float &tprimetHHadronic::muon2_diphodxy() {
  if (not muon2_diphodxy_isLoaded) {
    if (muon2_diphodxy_branch != 0) {
      muon2_diphodxy_branch->GetEntry(index);
    } else {
      printf("branch muon2_diphodxy_branch does not exist!\n");
      exit(1);
    }
    muon2_diphodxy_isLoaded = true;
  }
  return muon2_diphodxy_;
}

const float &tprimetHHadronic::muon1_dz() {
  if (not muon1_dz_isLoaded) {
    if (muon1_dz_branch != 0) {
      muon1_dz_branch->GetEntry(index);
    } else {
      printf("branch muon1_dz_branch does not exist!\n");
      exit(1);
    }
    muon1_dz_isLoaded = true;
  }
  return muon1_dz_;
}

const float &tprimetHHadronic::muon2_dz() {
  if (not muon2_dz_isLoaded) {
    if (muon2_dz_branch != 0) {
      muon2_dz_branch->GetEntry(index);
    } else {
      printf("branch muon2_dz_branch does not exist!\n");
      exit(1);
    }
    muon2_dz_isLoaded = true;
  }
  return muon2_dz_;
}

const float &tprimetHHadronic::muon1_diphodz() {
  if (not muon1_diphodz_isLoaded) {
    if (muon1_diphodz_branch != 0) {
      muon1_diphodz_branch->GetEntry(index);
    } else {
      printf("branch muon1_diphodz_branch does not exist!\n");
      exit(1);
    }
    muon1_diphodz_isLoaded = true;
  }
  return muon1_diphodz_;
}

const float &tprimetHHadronic::muon2_diphodz() {
  if (not muon2_diphodz_isLoaded) {
    if (muon2_diphodz_branch != 0) {
      muon2_diphodz_branch->GetEntry(index);
    } else {
      printf("branch muon2_diphodz_branch does not exist!\n");
      exit(1);
    }
    muon2_diphodz_isLoaded = true;
  }
  return muon2_diphodz_;
}

const float &tprimetHHadronic::muon1_pxHits() {
  if (not muon1_pxHits_isLoaded) {
    if (muon1_pxHits_branch != 0) {
      muon1_pxHits_branch->GetEntry(index);
    } else {
      printf("branch muon1_pxHits_branch does not exist!\n");
      exit(1);
    }
    muon1_pxHits_isLoaded = true;
  }
  return muon1_pxHits_;
}

const float &tprimetHHadronic::muon2_pxHits() {
  if (not muon2_pxHits_isLoaded) {
    if (muon2_pxHits_branch != 0) {
      muon2_pxHits_branch->GetEntry(index);
    } else {
      printf("branch muon2_pxHits_branch does not exist!\n");
      exit(1);
    }
    muon2_pxHits_isLoaded = true;
  }
  return muon2_pxHits_;
}

const float &tprimetHHadronic::muon1_tkLayers() {
  if (not muon1_tkLayers_isLoaded) {
    if (muon1_tkLayers_branch != 0) {
      muon1_tkLayers_branch->GetEntry(index);
    } else {
      printf("branch muon1_tkLayers_branch does not exist!\n");
      exit(1);
    }
    muon1_tkLayers_isLoaded = true;
  }
  return muon1_tkLayers_;
}

const float &tprimetHHadronic::muon2_tkLayers() {
  if (not muon2_tkLayers_isLoaded) {
    if (muon2_tkLayers_branch != 0) {
      muon2_tkLayers_branch->GetEntry(index);
    } else {
      printf("branch muon2_tkLayers_branch does not exist!\n");
      exit(1);
    }
    muon2_tkLayers_isLoaded = true;
  }
  return muon2_tkLayers_;
}

const float &tprimetHHadronic::muon1_PassTight() {
  if (not muon1_PassTight_isLoaded) {
    if (muon1_PassTight_branch != 0) {
      muon1_PassTight_branch->GetEntry(index);
    } else {
      printf("branch muon1_PassTight_branch does not exist!\n");
      exit(1);
    }
    muon1_PassTight_isLoaded = true;
  }
  return muon1_PassTight_;
}

const float &tprimetHHadronic::muon2_PassTight() {
  if (not muon2_PassTight_isLoaded) {
    if (muon2_PassTight_branch != 0) {
      muon2_PassTight_branch->GetEntry(index);
    } else {
      printf("branch muon2_PassTight_branch does not exist!\n");
      exit(1);
    }
    muon2_PassTight_isLoaded = true;
  }
  return muon2_PassTight_;
}

const float &tprimetHHadronic::muon1_dPhiMET() {
  if (not muon1_dPhiMET_isLoaded) {
    if (muon1_dPhiMET_branch != 0) {
      muon1_dPhiMET_branch->GetEntry(index);
    } else {
      printf("branch muon1_dPhiMET_branch does not exist!\n");
      exit(1);
    }
    muon1_dPhiMET_isLoaded = true;
  }
  return muon1_dPhiMET_;
}

const float &tprimetHHadronic::muon2_dPhiMET() {
  if (not muon2_dPhiMET_isLoaded) {
    if (muon2_dPhiMET_branch != 0) {
      muon2_dPhiMET_branch->GetEntry(index);
    } else {
      printf("branch muon2_dPhiMET_branch does not exist!\n");
      exit(1);
    }
    muon2_dPhiMET_isLoaded = true;
  }
  return muon2_dPhiMET_;
}

const float &tprimetHHadronic::n_fwdjets() {
  if (not n_fwdjets_isLoaded) {
    if (n_fwdjets_branch != 0) {
      n_fwdjets_branch->GetEntry(index);
    } else {
      printf("branch n_fwdjets_branch does not exist!\n");
      exit(1);
    }
    n_fwdjets_isLoaded = true;
  }
  return n_fwdjets_;
}

const float &tprimetHHadronic::fwdjet1_pt() {
  if (not fwdjet1_pt_isLoaded) {
    if (fwdjet1_pt_branch != 0) {
      fwdjet1_pt_branch->GetEntry(index);
    } else {
      printf("branch fwdjet1_pt_branch does not exist!\n");
      exit(1);
    }
    fwdjet1_pt_isLoaded = true;
  }
  return fwdjet1_pt_;
}

const float &tprimetHHadronic::fwdjet2_pt() {
  if (not fwdjet2_pt_isLoaded) {
    if (fwdjet2_pt_branch != 0) {
      fwdjet2_pt_branch->GetEntry(index);
    } else {
      printf("branch fwdjet2_pt_branch does not exist!\n");
      exit(1);
    }
    fwdjet2_pt_isLoaded = true;
  }
  return fwdjet2_pt_;
}

const float &tprimetHHadronic::fwdjet3_pt() {
  if (not fwdjet3_pt_isLoaded) {
    if (fwdjet3_pt_branch != 0) {
      fwdjet3_pt_branch->GetEntry(index);
    } else {
      printf("branch fwdjet3_pt_branch does not exist!\n");
      exit(1);
    }
    fwdjet3_pt_isLoaded = true;
  }
  return fwdjet3_pt_;
}

const float &tprimetHHadronic::fwdjet1_eta() {
  if (not fwdjet1_eta_isLoaded) {
    if (fwdjet1_eta_branch != 0) {
      fwdjet1_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet1_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet1_eta_isLoaded = true;
  }
  return fwdjet1_eta_;
}

const float &tprimetHHadronic::fwdjet2_eta() {
  if (not fwdjet2_eta_isLoaded) {
    if (fwdjet2_eta_branch != 0) {
      fwdjet2_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet2_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet2_eta_isLoaded = true;
  }
  return fwdjet2_eta_;
}

const float &tprimetHHadronic::fwdjet3_eta() {
  if (not fwdjet3_eta_isLoaded) {
    if (fwdjet3_eta_branch != 0) {
      fwdjet3_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet3_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet3_eta_isLoaded = true;
  }
  return fwdjet3_eta_;
}

const float &tprimetHHadronic::fwdjet4_eta() {
  if (not fwdjet4_eta_isLoaded) {
    if (fwdjet4_eta_branch != 0) {
      fwdjet4_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet4_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet4_eta_isLoaded = true;
  }
  return fwdjet4_eta_;
}

const float &tprimetHHadronic::fwdjet5_eta() {
  if (not fwdjet5_eta_isLoaded) {
    if (fwdjet5_eta_branch != 0) {
      fwdjet5_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet5_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet5_eta_isLoaded = true;
  }
  return fwdjet5_eta_;
}

const float &tprimetHHadronic::fwdjet6_eta() {
  if (not fwdjet6_eta_isLoaded) {
    if (fwdjet6_eta_branch != 0) {
      fwdjet6_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet6_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet6_eta_isLoaded = true;
  }
  return fwdjet6_eta_;
}

const float &tprimetHHadronic::fwdjet7_eta() {
  if (not fwdjet7_eta_isLoaded) {
    if (fwdjet7_eta_branch != 0) {
      fwdjet7_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet7_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet7_eta_isLoaded = true;
  }
  return fwdjet7_eta_;
}

const float &tprimetHHadronic::fwdjet8_eta() {
  if (not fwdjet8_eta_isLoaded) {
    if (fwdjet8_eta_branch != 0) {
      fwdjet8_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet8_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet8_eta_isLoaded = true;
  }
  return fwdjet8_eta_;
}

const float &tprimetHHadronic::fwdjet9_eta() {
  if (not fwdjet9_eta_isLoaded) {
    if (fwdjet9_eta_branch != 0) {
      fwdjet9_eta_branch->GetEntry(index);
    } else {
      printf("branch fwdjet9_eta_branch does not exist!\n");
      exit(1);
    }
    fwdjet9_eta_isLoaded = true;
  }
  return fwdjet9_eta_;
}

const float &tprimetHHadronic::fwdjet1_phi() {
  if (not fwdjet1_phi_isLoaded) {
    if (fwdjet1_phi_branch != 0) {
      fwdjet1_phi_branch->GetEntry(index);
    } else {
      printf("branch fwdjet1_phi_branch does not exist!\n");
      exit(1);
    }
    fwdjet1_phi_isLoaded = true;
  }
  return fwdjet1_phi_;
}

const float &tprimetHHadronic::fwdjet2_phi() {
  if (not fwdjet2_phi_isLoaded) {
    if (fwdjet2_phi_branch != 0) {
      fwdjet2_phi_branch->GetEntry(index);
    } else {
      printf("branch fwdjet2_phi_branch does not exist!\n");
      exit(1);
    }
    fwdjet2_phi_isLoaded = true;
  }
  return fwdjet2_phi_;
}

const float &tprimetHHadronic::fwdjet3_phi() {
  if (not fwdjet3_phi_isLoaded) {
    if (fwdjet3_phi_branch != 0) {
      fwdjet3_phi_branch->GetEntry(index);
    } else {
      printf("branch fwdjet3_phi_branch does not exist!\n");
      exit(1);
    }
    fwdjet3_phi_isLoaded = true;
  }
  return fwdjet3_phi_;
}

const float &tprimetHHadronic::fwdjet1_e() {
  if (not fwdjet1_e_isLoaded) {
    if (fwdjet1_e_branch != 0) {
      fwdjet1_e_branch->GetEntry(index);
    } else {
      printf("branch fwdjet1_e_branch does not exist!\n");
      exit(1);
    }
    fwdjet1_e_isLoaded = true;
  }
  return fwdjet1_e_;
}

const float &tprimetHHadronic::fwdjet2_e() {
  if (not fwdjet2_e_isLoaded) {
    if (fwdjet2_e_branch != 0) {
      fwdjet2_e_branch->GetEntry(index);
    } else {
      printf("branch fwdjet2_e_branch does not exist!\n");
      exit(1);
    }
    fwdjet2_e_isLoaded = true;
  }
  return fwdjet2_e_;
}

const float &tprimetHHadronic::fwdjet3_e() {
  if (not fwdjet3_e_isLoaded) {
    if (fwdjet3_e_branch != 0) {
      fwdjet3_e_branch->GetEntry(index);
    } else {
      printf("branch fwdjet3_e_branch does not exist!\n");
      exit(1);
    }
    fwdjet3_e_isLoaded = true;
  }
  return fwdjet3_e_;
}

const float &tprimetHHadronic::fwdjet1_discr() {
  if (not fwdjet1_discr_isLoaded) {
    if (fwdjet1_discr_branch != 0) {
      fwdjet1_discr_branch->GetEntry(index);
    } else {
      printf("branch fwdjet1_discr_branch does not exist!\n");
      exit(1);
    }
    fwdjet1_discr_isLoaded = true;
  }
  return fwdjet1_discr_;
}

const float &tprimetHHadronic::n_M_bjets() {
  if (not n_M_bjets_isLoaded) {
    if (n_M_bjets_branch != 0) {
      n_M_bjets_branch->GetEntry(index);
    } else {
      printf("branch n_M_bjets_branch does not exist!\n");
      exit(1);
    }
    n_M_bjets_isLoaded = true;
  }
  return n_M_bjets_;
}

const float &tprimetHHadronic::n_L_bjets() {
  if (not n_L_bjets_isLoaded) {
    if (n_L_bjets_branch != 0) {
      n_L_bjets_branch->GetEntry(index);
    } else {
      printf("branch n_L_bjets_branch does not exist!\n");
      exit(1);
    }
    n_L_bjets_isLoaded = true;
  }
  return n_L_bjets_;
}

const float &tprimetHHadronic::n_T_bjets() {
  if (not n_T_bjets_isLoaded) {
    if (n_T_bjets_branch != 0) {
      n_T_bjets_branch->GetEntry(index);
    } else {
      printf("branch n_T_bjets_branch does not exist!\n");
      exit(1);
    }
    n_T_bjets_isLoaded = true;
  }
  return n_T_bjets_;
}

const float &tprimetHHadronic::n_bjets() {
  if (not n_bjets_isLoaded) {
    if (n_bjets_branch != 0) {
      n_bjets_branch->GetEntry(index);
    } else {
      printf("branch n_bjets_branch does not exist!\n");
      exit(1);
    }
    n_bjets_isLoaded = true;
  }
  return n_bjets_;
}

const float &tprimetHHadronic::bjet1_pt() {
  if (not bjet1_pt_isLoaded) {
    if (bjet1_pt_branch != 0) {
      bjet1_pt_branch->GetEntry(index);
    } else {
      printf("branch bjet1_pt_branch does not exist!\n");
      exit(1);
    }
    bjet1_pt_isLoaded = true;
  }
  return bjet1_pt_;
}

const float &tprimetHHadronic::bjet2_pt() {
  if (not bjet2_pt_isLoaded) {
    if (bjet2_pt_branch != 0) {
      bjet2_pt_branch->GetEntry(index);
    } else {
      printf("branch bjet2_pt_branch does not exist!\n");
      exit(1);
    }
    bjet2_pt_isLoaded = true;
  }
  return bjet2_pt_;
}

const float &tprimetHHadronic::bjet3_pt() {
  if (not bjet3_pt_isLoaded) {
    if (bjet3_pt_branch != 0) {
      bjet3_pt_branch->GetEntry(index);
    } else {
      printf("branch bjet3_pt_branch does not exist!\n");
      exit(1);
    }
    bjet3_pt_isLoaded = true;
  }
  return bjet3_pt_;
}

const float &tprimetHHadronic::bjet1_eta() {
  if (not bjet1_eta_isLoaded) {
    if (bjet1_eta_branch != 0) {
      bjet1_eta_branch->GetEntry(index);
    } else {
      printf("branch bjet1_eta_branch does not exist!\n");
      exit(1);
    }
    bjet1_eta_isLoaded = true;
  }
  return bjet1_eta_;
}

const float &tprimetHHadronic::bjet2_eta() {
  if (not bjet2_eta_isLoaded) {
    if (bjet2_eta_branch != 0) {
      bjet2_eta_branch->GetEntry(index);
    } else {
      printf("branch bjet2_eta_branch does not exist!\n");
      exit(1);
    }
    bjet2_eta_isLoaded = true;
  }
  return bjet2_eta_;
}

const float &tprimetHHadronic::bjet3_eta() {
  if (not bjet3_eta_isLoaded) {
    if (bjet3_eta_branch != 0) {
      bjet3_eta_branch->GetEntry(index);
    } else {
      printf("branch bjet3_eta_branch does not exist!\n");
      exit(1);
    }
    bjet3_eta_isLoaded = true;
  }
  return bjet3_eta_;
}

const float &tprimetHHadronic::bjet1_phi() {
  if (not bjet1_phi_isLoaded) {
    if (bjet1_phi_branch != 0) {
      bjet1_phi_branch->GetEntry(index);
    } else {
      printf("branch bjet1_phi_branch does not exist!\n");
      exit(1);
    }
    bjet1_phi_isLoaded = true;
  }
  return bjet1_phi_;
}

const float &tprimetHHadronic::bjet2_phi() {
  if (not bjet2_phi_isLoaded) {
    if (bjet2_phi_branch != 0) {
      bjet2_phi_branch->GetEntry(index);
    } else {
      printf("branch bjet2_phi_branch does not exist!\n");
      exit(1);
    }
    bjet2_phi_isLoaded = true;
  }
  return bjet2_phi_;
}

const float &tprimetHHadronic::bjet3_phi() {
  if (not bjet3_phi_isLoaded) {
    if (bjet3_phi_branch != 0) {
      bjet3_phi_branch->GetEntry(index);
    } else {
      printf("branch bjet3_phi_branch does not exist!\n");
      exit(1);
    }
    bjet3_phi_isLoaded = true;
  }
  return bjet3_phi_;
}

const float &tprimetHHadronic::bjet1_e() {
  if (not bjet1_e_isLoaded) {
    if (bjet1_e_branch != 0) {
      bjet1_e_branch->GetEntry(index);
    } else {
      printf("branch bjet1_e_branch does not exist!\n");
      exit(1);
    }
    bjet1_e_isLoaded = true;
  }
  return bjet1_e_;
}

const float &tprimetHHadronic::bjet2_e() {
  if (not bjet2_e_isLoaded) {
    if (bjet2_e_branch != 0) {
      bjet2_e_branch->GetEntry(index);
    } else {
      printf("branch bjet2_e_branch does not exist!\n");
      exit(1);
    }
    bjet2_e_isLoaded = true;
  }
  return bjet2_e_;
}

const float &tprimetHHadronic::bjet3_e() {
  if (not bjet3_e_isLoaded) {
    if (bjet3_e_branch != 0) {
      bjet3_e_branch->GetEntry(index);
    } else {
      printf("branch bjet3_e_branch does not exist!\n");
      exit(1);
    }
    bjet3_e_isLoaded = true;
  }
  return bjet3_e_;
}

const float &tprimetHHadronic::bjet1_discr() {
  if (not bjet1_discr_isLoaded) {
    if (bjet1_discr_branch != 0) {
      bjet1_discr_branch->GetEntry(index);
    } else {
      printf("branch bjet1_discr_branch does not exist!\n");
      exit(1);
    }
    bjet1_discr_isLoaded = true;
  }
  return bjet1_discr_;
}

const float &tprimetHHadronic::bjet2_discr() {
  if (not bjet2_discr_isLoaded) {
    if (bjet2_discr_branch != 0) {
      bjet2_discr_branch->GetEntry(index);
    } else {
      printf("branch bjet2_discr_branch does not exist!\n");
      exit(1);
    }
    bjet2_discr_isLoaded = true;
  }
  return bjet2_discr_;
}

const float &tprimetHHadronic::bjet3_discr() {
  if (not bjet3_discr_isLoaded) {
    if (bjet3_discr_branch != 0) {
      bjet3_discr_branch->GetEntry(index);
    } else {
      printf("branch bjet3_discr_branch does not exist!\n");
      exit(1);
    }
    bjet3_discr_isLoaded = true;
  }
  return bjet3_discr_;
}

const float &tprimetHHadronic::bjet4_discr() {
  if (not bjet4_discr_isLoaded) {
    if (bjet4_discr_branch != 0) {
      bjet4_discr_branch->GetEntry(index);
    } else {
      printf("branch bjet4_discr_branch does not exist!\n");
      exit(1);
    }
    bjet4_discr_isLoaded = true;
  }
  return bjet4_discr_;
}

const float &tprimetHHadronic::n_jets() {
  if (not n_jets_isLoaded) {
    if (n_jets_branch != 0) {
      n_jets_branch->GetEntry(index);
    } else {
      printf("branch n_jets_branch does not exist!\n");
      exit(1);
    }
    n_jets_isLoaded = true;
  }
  return n_jets_;
}

const float &tprimetHHadronic::jet1_pt() {
  if (not jet1_pt_isLoaded) {
    if (jet1_pt_branch != 0) {
      jet1_pt_branch->GetEntry(index);
    } else {
      printf("branch jet1_pt_branch does not exist!\n");
      exit(1);
    }
    jet1_pt_isLoaded = true;
  }
  return jet1_pt_;
}

const float &tprimetHHadronic::jet2_pt() {
  if (not jet2_pt_isLoaded) {
    if (jet2_pt_branch != 0) {
      jet2_pt_branch->GetEntry(index);
    } else {
      printf("branch jet2_pt_branch does not exist!\n");
      exit(1);
    }
    jet2_pt_isLoaded = true;
  }
  return jet2_pt_;
}

const float &tprimetHHadronic::jet3_pt() {
  if (not jet3_pt_isLoaded) {
    if (jet3_pt_branch != 0) {
      jet3_pt_branch->GetEntry(index);
    } else {
      printf("branch jet3_pt_branch does not exist!\n");
      exit(1);
    }
    jet3_pt_isLoaded = true;
  }
  return jet3_pt_;
}

const float &tprimetHHadronic::jet4_pt() {
  if (not jet4_pt_isLoaded) {
    if (jet4_pt_branch != 0) {
      jet4_pt_branch->GetEntry(index);
    } else {
      printf("branch jet4_pt_branch does not exist!\n");
      exit(1);
    }
    jet4_pt_isLoaded = true;
  }
  return jet4_pt_;
}

const float &tprimetHHadronic::jet5_pt() {
  if (not jet5_pt_isLoaded) {
    if (jet5_pt_branch != 0) {
      jet5_pt_branch->GetEntry(index);
    } else {
      printf("branch jet5_pt_branch does not exist!\n");
      exit(1);
    }
    jet5_pt_isLoaded = true;
  }
  return jet5_pt_;
}

const float &tprimetHHadronic::jet6_pt() {
  if (not jet6_pt_isLoaded) {
    if (jet6_pt_branch != 0) {
      jet6_pt_branch->GetEntry(index);
    } else {
      printf("branch jet6_pt_branch does not exist!\n");
      exit(1);
    }
    jet6_pt_isLoaded = true;
  }
  return jet6_pt_;
}

const float &tprimetHHadronic::jet7_pt() {
  if (not jet7_pt_isLoaded) {
    if (jet7_pt_branch != 0) {
      jet7_pt_branch->GetEntry(index);
    } else {
      printf("branch jet7_pt_branch does not exist!\n");
      exit(1);
    }
    jet7_pt_isLoaded = true;
  }
  return jet7_pt_;
}

const float &tprimetHHadronic::jet8_pt() {
  if (not jet8_pt_isLoaded) {
    if (jet8_pt_branch != 0) {
      jet8_pt_branch->GetEntry(index);
    } else {
      printf("branch jet8_pt_branch does not exist!\n");
      exit(1);
    }
    jet8_pt_isLoaded = true;
  }
  return jet8_pt_;
}

const float &tprimetHHadronic::jet9_pt() {
  if (not jet9_pt_isLoaded) {
    if (jet9_pt_branch != 0) {
      jet9_pt_branch->GetEntry(index);
    } else {
      printf("branch jet9_pt_branch does not exist!\n");
      exit(1);
    }
    jet9_pt_isLoaded = true;
  }
  return jet9_pt_;
}

const float &tprimetHHadronic::jet10_pt() {
  if (not jet10_pt_isLoaded) {
    if (jet10_pt_branch != 0) {
      jet10_pt_branch->GetEntry(index);
    } else {
      printf("branch jet10_pt_branch does not exist!\n");
      exit(1);
    }
    jet10_pt_isLoaded = true;
  }
  return jet10_pt_;
}

const float &tprimetHHadronic::jet11_pt() {
  if (not jet11_pt_isLoaded) {
    if (jet11_pt_branch != 0) {
      jet11_pt_branch->GetEntry(index);
    } else {
      printf("branch jet11_pt_branch does not exist!\n");
      exit(1);
    }
    jet11_pt_isLoaded = true;
  }
  return jet11_pt_;
}

const float &tprimetHHadronic::jet12_pt() {
  if (not jet12_pt_isLoaded) {
    if (jet12_pt_branch != 0) {
      jet12_pt_branch->GetEntry(index);
    } else {
      printf("branch jet12_pt_branch does not exist!\n");
      exit(1);
    }
    jet12_pt_isLoaded = true;
  }
  return jet12_pt_;
}

const float &tprimetHHadronic::jet13_pt() {
  if (not jet13_pt_isLoaded) {
    if (jet13_pt_branch != 0) {
      jet13_pt_branch->GetEntry(index);
    } else {
      printf("branch jet13_pt_branch does not exist!\n");
      exit(1);
    }
    jet13_pt_isLoaded = true;
  }
  return jet13_pt_;
}

const float &tprimetHHadronic::jet14_pt() {
  if (not jet14_pt_isLoaded) {
    if (jet14_pt_branch != 0) {
      jet14_pt_branch->GetEntry(index);
    } else {
      printf("branch jet14_pt_branch does not exist!\n");
      exit(1);
    }
    jet14_pt_isLoaded = true;
  }
  return jet14_pt_;
}

const float &tprimetHHadronic::jet15_pt() {
  if (not jet15_pt_isLoaded) {
    if (jet15_pt_branch != 0) {
      jet15_pt_branch->GetEntry(index);
    } else {
      printf("branch jet15_pt_branch does not exist!\n");
      exit(1);
    }
    jet15_pt_isLoaded = true;
  }
  return jet15_pt_;
}

const float &tprimetHHadronic::jet1_eta() {
  if (not jet1_eta_isLoaded) {
    if (jet1_eta_branch != 0) {
      jet1_eta_branch->GetEntry(index);
    } else {
      printf("branch jet1_eta_branch does not exist!\n");
      exit(1);
    }
    jet1_eta_isLoaded = true;
  }
  return jet1_eta_;
}

const float &tprimetHHadronic::jet2_eta() {
  if (not jet2_eta_isLoaded) {
    if (jet2_eta_branch != 0) {
      jet2_eta_branch->GetEntry(index);
    } else {
      printf("branch jet2_eta_branch does not exist!\n");
      exit(1);
    }
    jet2_eta_isLoaded = true;
  }
  return jet2_eta_;
}

const float &tprimetHHadronic::jet3_eta() {
  if (not jet3_eta_isLoaded) {
    if (jet3_eta_branch != 0) {
      jet3_eta_branch->GetEntry(index);
    } else {
      printf("branch jet3_eta_branch does not exist!\n");
      exit(1);
    }
    jet3_eta_isLoaded = true;
  }
  return jet3_eta_;
}

const float &tprimetHHadronic::jet4_eta() {
  if (not jet4_eta_isLoaded) {
    if (jet4_eta_branch != 0) {
      jet4_eta_branch->GetEntry(index);
    } else {
      printf("branch jet4_eta_branch does not exist!\n");
      exit(1);
    }
    jet4_eta_isLoaded = true;
  }
  return jet4_eta_;
}

const float &tprimetHHadronic::jet5_eta() {
  if (not jet5_eta_isLoaded) {
    if (jet5_eta_branch != 0) {
      jet5_eta_branch->GetEntry(index);
    } else {
      printf("branch jet5_eta_branch does not exist!\n");
      exit(1);
    }
    jet5_eta_isLoaded = true;
  }
  return jet5_eta_;
}

const float &tprimetHHadronic::jet6_eta() {
  if (not jet6_eta_isLoaded) {
    if (jet6_eta_branch != 0) {
      jet6_eta_branch->GetEntry(index);
    } else {
      printf("branch jet6_eta_branch does not exist!\n");
      exit(1);
    }
    jet6_eta_isLoaded = true;
  }
  return jet6_eta_;
}

const float &tprimetHHadronic::jet7_eta() {
  if (not jet7_eta_isLoaded) {
    if (jet7_eta_branch != 0) {
      jet7_eta_branch->GetEntry(index);
    } else {
      printf("branch jet7_eta_branch does not exist!\n");
      exit(1);
    }
    jet7_eta_isLoaded = true;
  }
  return jet7_eta_;
}

const float &tprimetHHadronic::jet8_eta() {
  if (not jet8_eta_isLoaded) {
    if (jet8_eta_branch != 0) {
      jet8_eta_branch->GetEntry(index);
    } else {
      printf("branch jet8_eta_branch does not exist!\n");
      exit(1);
    }
    jet8_eta_isLoaded = true;
  }
  return jet8_eta_;
}

const float &tprimetHHadronic::jet9_eta() {
  if (not jet9_eta_isLoaded) {
    if (jet9_eta_branch != 0) {
      jet9_eta_branch->GetEntry(index);
    } else {
      printf("branch jet9_eta_branch does not exist!\n");
      exit(1);
    }
    jet9_eta_isLoaded = true;
  }
  return jet9_eta_;
}

const float &tprimetHHadronic::jet10_eta() {
  if (not jet10_eta_isLoaded) {
    if (jet10_eta_branch != 0) {
      jet10_eta_branch->GetEntry(index);
    } else {
      printf("branch jet10_eta_branch does not exist!\n");
      exit(1);
    }
    jet10_eta_isLoaded = true;
  }
  return jet10_eta_;
}

const float &tprimetHHadronic::jet11_eta() {
  if (not jet11_eta_isLoaded) {
    if (jet11_eta_branch != 0) {
      jet11_eta_branch->GetEntry(index);
    } else {
      printf("branch jet11_eta_branch does not exist!\n");
      exit(1);
    }
    jet11_eta_isLoaded = true;
  }
  return jet11_eta_;
}

const float &tprimetHHadronic::jet12_eta() {
  if (not jet12_eta_isLoaded) {
    if (jet12_eta_branch != 0) {
      jet12_eta_branch->GetEntry(index);
    } else {
      printf("branch jet12_eta_branch does not exist!\n");
      exit(1);
    }
    jet12_eta_isLoaded = true;
  }
  return jet12_eta_;
}

const float &tprimetHHadronic::jet13_eta() {
  if (not jet13_eta_isLoaded) {
    if (jet13_eta_branch != 0) {
      jet13_eta_branch->GetEntry(index);
    } else {
      printf("branch jet13_eta_branch does not exist!\n");
      exit(1);
    }
    jet13_eta_isLoaded = true;
  }
  return jet13_eta_;
}

const float &tprimetHHadronic::jet14_eta() {
  if (not jet14_eta_isLoaded) {
    if (jet14_eta_branch != 0) {
      jet14_eta_branch->GetEntry(index);
    } else {
      printf("branch jet14_eta_branch does not exist!\n");
      exit(1);
    }
    jet14_eta_isLoaded = true;
  }
  return jet14_eta_;
}

const float &tprimetHHadronic::jet15_eta() {
  if (not jet15_eta_isLoaded) {
    if (jet15_eta_branch != 0) {
      jet15_eta_branch->GetEntry(index);
    } else {
      printf("branch jet15_eta_branch does not exist!\n");
      exit(1);
    }
    jet15_eta_isLoaded = true;
  }
  return jet15_eta_;
}

const float &tprimetHHadronic::jet1_phi() {
  if (not jet1_phi_isLoaded) {
    if (jet1_phi_branch != 0) {
      jet1_phi_branch->GetEntry(index);
    } else {
      printf("branch jet1_phi_branch does not exist!\n");
      exit(1);
    }
    jet1_phi_isLoaded = true;
  }
  return jet1_phi_;
}

const float &tprimetHHadronic::jet2_phi() {
  if (not jet2_phi_isLoaded) {
    if (jet2_phi_branch != 0) {
      jet2_phi_branch->GetEntry(index);
    } else {
      printf("branch jet2_phi_branch does not exist!\n");
      exit(1);
    }
    jet2_phi_isLoaded = true;
  }
  return jet2_phi_;
}

const float &tprimetHHadronic::jet3_phi() {
  if (not jet3_phi_isLoaded) {
    if (jet3_phi_branch != 0) {
      jet3_phi_branch->GetEntry(index);
    } else {
      printf("branch jet3_phi_branch does not exist!\n");
      exit(1);
    }
    jet3_phi_isLoaded = true;
  }
  return jet3_phi_;
}

const float &tprimetHHadronic::jet4_phi() {
  if (not jet4_phi_isLoaded) {
    if (jet4_phi_branch != 0) {
      jet4_phi_branch->GetEntry(index);
    } else {
      printf("branch jet4_phi_branch does not exist!\n");
      exit(1);
    }
    jet4_phi_isLoaded = true;
  }
  return jet4_phi_;
}

const float &tprimetHHadronic::jet5_phi() {
  if (not jet5_phi_isLoaded) {
    if (jet5_phi_branch != 0) {
      jet5_phi_branch->GetEntry(index);
    } else {
      printf("branch jet5_phi_branch does not exist!\n");
      exit(1);
    }
    jet5_phi_isLoaded = true;
  }
  return jet5_phi_;
}

const float &tprimetHHadronic::jet6_phi() {
  if (not jet6_phi_isLoaded) {
    if (jet6_phi_branch != 0) {
      jet6_phi_branch->GetEntry(index);
    } else {
      printf("branch jet6_phi_branch does not exist!\n");
      exit(1);
    }
    jet6_phi_isLoaded = true;
  }
  return jet6_phi_;
}

const float &tprimetHHadronic::jet7_phi() {
  if (not jet7_phi_isLoaded) {
    if (jet7_phi_branch != 0) {
      jet7_phi_branch->GetEntry(index);
    } else {
      printf("branch jet7_phi_branch does not exist!\n");
      exit(1);
    }
    jet7_phi_isLoaded = true;
  }
  return jet7_phi_;
}

const float &tprimetHHadronic::jet8_phi() {
  if (not jet8_phi_isLoaded) {
    if (jet8_phi_branch != 0) {
      jet8_phi_branch->GetEntry(index);
    } else {
      printf("branch jet8_phi_branch does not exist!\n");
      exit(1);
    }
    jet8_phi_isLoaded = true;
  }
  return jet8_phi_;
}

const float &tprimetHHadronic::jet9_phi() {
  if (not jet9_phi_isLoaded) {
    if (jet9_phi_branch != 0) {
      jet9_phi_branch->GetEntry(index);
    } else {
      printf("branch jet9_phi_branch does not exist!\n");
      exit(1);
    }
    jet9_phi_isLoaded = true;
  }
  return jet9_phi_;
}

const float &tprimetHHadronic::jet10_phi() {
  if (not jet10_phi_isLoaded) {
    if (jet10_phi_branch != 0) {
      jet10_phi_branch->GetEntry(index);
    } else {
      printf("branch jet10_phi_branch does not exist!\n");
      exit(1);
    }
    jet10_phi_isLoaded = true;
  }
  return jet10_phi_;
}

const float &tprimetHHadronic::jet11_phi() {
  if (not jet11_phi_isLoaded) {
    if (jet11_phi_branch != 0) {
      jet11_phi_branch->GetEntry(index);
    } else {
      printf("branch jet11_phi_branch does not exist!\n");
      exit(1);
    }
    jet11_phi_isLoaded = true;
  }
  return jet11_phi_;
}

const float &tprimetHHadronic::jet12_phi() {
  if (not jet12_phi_isLoaded) {
    if (jet12_phi_branch != 0) {
      jet12_phi_branch->GetEntry(index);
    } else {
      printf("branch jet12_phi_branch does not exist!\n");
      exit(1);
    }
    jet12_phi_isLoaded = true;
  }
  return jet12_phi_;
}

const float &tprimetHHadronic::jet13_phi() {
  if (not jet13_phi_isLoaded) {
    if (jet13_phi_branch != 0) {
      jet13_phi_branch->GetEntry(index);
    } else {
      printf("branch jet13_phi_branch does not exist!\n");
      exit(1);
    }
    jet13_phi_isLoaded = true;
  }
  return jet13_phi_;
}

const float &tprimetHHadronic::jet14_phi() {
  if (not jet14_phi_isLoaded) {
    if (jet14_phi_branch != 0) {
      jet14_phi_branch->GetEntry(index);
    } else {
      printf("branch jet14_phi_branch does not exist!\n");
      exit(1);
    }
    jet14_phi_isLoaded = true;
  }
  return jet14_phi_;
}

const float &tprimetHHadronic::jet15_phi() {
  if (not jet15_phi_isLoaded) {
    if (jet15_phi_branch != 0) {
      jet15_phi_branch->GetEntry(index);
    } else {
      printf("branch jet15_phi_branch does not exist!\n");
      exit(1);
    }
    jet15_phi_isLoaded = true;
  }
  return jet15_phi_;
}

const float &tprimetHHadronic::jet1_e() {
  if (not jet1_e_isLoaded) {
    if (jet1_e_branch != 0) {
      jet1_e_branch->GetEntry(index);
    } else {
      printf("branch jet1_e_branch does not exist!\n");
      exit(1);
    }
    jet1_e_isLoaded = true;
  }
  return jet1_e_;
}

const float &tprimetHHadronic::jet2_e() {
  if (not jet2_e_isLoaded) {
    if (jet2_e_branch != 0) {
      jet2_e_branch->GetEntry(index);
    } else {
      printf("branch jet2_e_branch does not exist!\n");
      exit(1);
    }
    jet2_e_isLoaded = true;
  }
  return jet2_e_;
}

const float &tprimetHHadronic::jet3_e() {
  if (not jet3_e_isLoaded) {
    if (jet3_e_branch != 0) {
      jet3_e_branch->GetEntry(index);
    } else {
      printf("branch jet3_e_branch does not exist!\n");
      exit(1);
    }
    jet3_e_isLoaded = true;
  }
  return jet3_e_;
}

const float &tprimetHHadronic::jet4_e() {
  if (not jet4_e_isLoaded) {
    if (jet4_e_branch != 0) {
      jet4_e_branch->GetEntry(index);
    } else {
      printf("branch jet4_e_branch does not exist!\n");
      exit(1);
    }
    jet4_e_isLoaded = true;
  }
  return jet4_e_;
}

const float &tprimetHHadronic::jet5_e() {
  if (not jet5_e_isLoaded) {
    if (jet5_e_branch != 0) {
      jet5_e_branch->GetEntry(index);
    } else {
      printf("branch jet5_e_branch does not exist!\n");
      exit(1);
    }
    jet5_e_isLoaded = true;
  }
  return jet5_e_;
}

const float &tprimetHHadronic::jet6_e() {
  if (not jet6_e_isLoaded) {
    if (jet6_e_branch != 0) {
      jet6_e_branch->GetEntry(index);
    } else {
      printf("branch jet6_e_branch does not exist!\n");
      exit(1);
    }
    jet6_e_isLoaded = true;
  }
  return jet6_e_;
}

const float &tprimetHHadronic::jet7_e() {
  if (not jet7_e_isLoaded) {
    if (jet7_e_branch != 0) {
      jet7_e_branch->GetEntry(index);
    } else {
      printf("branch jet7_e_branch does not exist!\n");
      exit(1);
    }
    jet7_e_isLoaded = true;
  }
  return jet7_e_;
}

const float &tprimetHHadronic::jet8_e() {
  if (not jet8_e_isLoaded) {
    if (jet8_e_branch != 0) {
      jet8_e_branch->GetEntry(index);
    } else {
      printf("branch jet8_e_branch does not exist!\n");
      exit(1);
    }
    jet8_e_isLoaded = true;
  }
  return jet8_e_;
}

const float &tprimetHHadronic::jet9_e() {
  if (not jet9_e_isLoaded) {
    if (jet9_e_branch != 0) {
      jet9_e_branch->GetEntry(index);
    } else {
      printf("branch jet9_e_branch does not exist!\n");
      exit(1);
    }
    jet9_e_isLoaded = true;
  }
  return jet9_e_;
}

const float &tprimetHHadronic::jet10_e() {
  if (not jet10_e_isLoaded) {
    if (jet10_e_branch != 0) {
      jet10_e_branch->GetEntry(index);
    } else {
      printf("branch jet10_e_branch does not exist!\n");
      exit(1);
    }
    jet10_e_isLoaded = true;
  }
  return jet10_e_;
}

const float &tprimetHHadronic::jet11_e() {
  if (not jet11_e_isLoaded) {
    if (jet11_e_branch != 0) {
      jet11_e_branch->GetEntry(index);
    } else {
      printf("branch jet11_e_branch does not exist!\n");
      exit(1);
    }
    jet11_e_isLoaded = true;
  }
  return jet11_e_;
}

const float &tprimetHHadronic::jet12_e() {
  if (not jet12_e_isLoaded) {
    if (jet12_e_branch != 0) {
      jet12_e_branch->GetEntry(index);
    } else {
      printf("branch jet12_e_branch does not exist!\n");
      exit(1);
    }
    jet12_e_isLoaded = true;
  }
  return jet12_e_;
}

const float &tprimetHHadronic::jet13_e() {
  if (not jet13_e_isLoaded) {
    if (jet13_e_branch != 0) {
      jet13_e_branch->GetEntry(index);
    } else {
      printf("branch jet13_e_branch does not exist!\n");
      exit(1);
    }
    jet13_e_isLoaded = true;
  }
  return jet13_e_;
}

const float &tprimetHHadronic::jet14_e() {
  if (not jet14_e_isLoaded) {
    if (jet14_e_branch != 0) {
      jet14_e_branch->GetEntry(index);
    } else {
      printf("branch jet14_e_branch does not exist!\n");
      exit(1);
    }
    jet14_e_isLoaded = true;
  }
  return jet14_e_;
}

const float &tprimetHHadronic::jet15_e() {
  if (not jet15_e_isLoaded) {
    if (jet15_e_branch != 0) {
      jet15_e_branch->GetEntry(index);
    } else {
      printf("branch jet15_e_branch does not exist!\n");
      exit(1);
    }
    jet15_e_isLoaded = true;
  }
  return jet15_e_;
}

const float &tprimetHHadronic::jet1_discr() {
  if (not jet1_discr_isLoaded) {
    if (jet1_discr_branch != 0) {
      jet1_discr_branch->GetEntry(index);
    } else {
      printf("branch jet1_discr_branch does not exist!\n");
      exit(1);
    }
    jet1_discr_isLoaded = true;
  }
  return jet1_discr_;
}

const float &tprimetHHadronic::jet2_discr() {
  if (not jet2_discr_isLoaded) {
    if (jet2_discr_branch != 0) {
      jet2_discr_branch->GetEntry(index);
    } else {
      printf("branch jet2_discr_branch does not exist!\n");
      exit(1);
    }
    jet2_discr_isLoaded = true;
  }
  return jet2_discr_;
}

const float &tprimetHHadronic::jet3_discr() {
  if (not jet3_discr_isLoaded) {
    if (jet3_discr_branch != 0) {
      jet3_discr_branch->GetEntry(index);
    } else {
      printf("branch jet3_discr_branch does not exist!\n");
      exit(1);
    }
    jet3_discr_isLoaded = true;
  }
  return jet3_discr_;
}

const float &tprimetHHadronic::jet4_discr() {
  if (not jet4_discr_isLoaded) {
    if (jet4_discr_branch != 0) {
      jet4_discr_branch->GetEntry(index);
    } else {
      printf("branch jet4_discr_branch does not exist!\n");
      exit(1);
    }
    jet4_discr_isLoaded = true;
  }
  return jet4_discr_;
}

const float &tprimetHHadronic::jet5_discr() {
  if (not jet5_discr_isLoaded) {
    if (jet5_discr_branch != 0) {
      jet5_discr_branch->GetEntry(index);
    } else {
      printf("branch jet5_discr_branch does not exist!\n");
      exit(1);
    }
    jet5_discr_isLoaded = true;
  }
  return jet5_discr_;
}

const float &tprimetHHadronic::jet6_discr() {
  if (not jet6_discr_isLoaded) {
    if (jet6_discr_branch != 0) {
      jet6_discr_branch->GetEntry(index);
    } else {
      printf("branch jet6_discr_branch does not exist!\n");
      exit(1);
    }
    jet6_discr_isLoaded = true;
  }
  return jet6_discr_;
}

const float &tprimetHHadronic::jet7_discr() {
  if (not jet7_discr_isLoaded) {
    if (jet7_discr_branch != 0) {
      jet7_discr_branch->GetEntry(index);
    } else {
      printf("branch jet7_discr_branch does not exist!\n");
      exit(1);
    }
    jet7_discr_isLoaded = true;
  }
  return jet7_discr_;
}

const float &tprimetHHadronic::jet8_discr() {
  if (not jet8_discr_isLoaded) {
    if (jet8_discr_branch != 0) {
      jet8_discr_branch->GetEntry(index);
    } else {
      printf("branch jet8_discr_branch does not exist!\n");
      exit(1);
    }
    jet8_discr_isLoaded = true;
  }
  return jet8_discr_;
}

const float &tprimetHHadronic::jet9_discr() {
  if (not jet9_discr_isLoaded) {
    if (jet9_discr_branch != 0) {
      jet9_discr_branch->GetEntry(index);
    } else {
      printf("branch jet9_discr_branch does not exist!\n");
      exit(1);
    }
    jet9_discr_isLoaded = true;
  }
  return jet9_discr_;
}

const float &tprimetHHadronic::jet10_discr() {
  if (not jet10_discr_isLoaded) {
    if (jet10_discr_branch != 0) {
      jet10_discr_branch->GetEntry(index);
    } else {
      printf("branch jet10_discr_branch does not exist!\n");
      exit(1);
    }
    jet10_discr_isLoaded = true;
  }
  return jet10_discr_;
}

const float &tprimetHHadronic::jet11_discr() {
  if (not jet11_discr_isLoaded) {
    if (jet11_discr_branch != 0) {
      jet11_discr_branch->GetEntry(index);
    } else {
      printf("branch jet11_discr_branch does not exist!\n");
      exit(1);
    }
    jet11_discr_isLoaded = true;
  }
  return jet11_discr_;
}

const float &tprimetHHadronic::jet12_discr() {
  if (not jet12_discr_isLoaded) {
    if (jet12_discr_branch != 0) {
      jet12_discr_branch->GetEntry(index);
    } else {
      printf("branch jet12_discr_branch does not exist!\n");
      exit(1);
    }
    jet12_discr_isLoaded = true;
  }
  return jet12_discr_;
}

const float &tprimetHHadronic::jet13_discr() {
  if (not jet13_discr_isLoaded) {
    if (jet13_discr_branch != 0) {
      jet13_discr_branch->GetEntry(index);
    } else {
      printf("branch jet13_discr_branch does not exist!\n");
      exit(1);
    }
    jet13_discr_isLoaded = true;
  }
  return jet13_discr_;
}

const float &tprimetHHadronic::jet14_discr() {
  if (not jet14_discr_isLoaded) {
    if (jet14_discr_branch != 0) {
      jet14_discr_branch->GetEntry(index);
    } else {
      printf("branch jet14_discr_branch does not exist!\n");
      exit(1);
    }
    jet14_discr_isLoaded = true;
  }
  return jet14_discr_;
}

const float &tprimetHHadronic::jet15_discr() {
  if (not jet15_discr_isLoaded) {
    if (jet15_discr_branch != 0) {
      jet15_discr_branch->GetEntry(index);
    } else {
      printf("branch jet15_discr_branch does not exist!\n");
      exit(1);
    }
    jet15_discr_isLoaded = true;
  }
  return jet15_discr_;
}

const float &tprimetHHadronic::recoMET_pt() {
  if (not recoMET_pt_isLoaded) {
    if (recoMET_pt_branch != 0) {
      recoMET_pt_branch->GetEntry(index);
    } else {
      printf("branch recoMET_pt_branch does not exist!\n");
      exit(1);
    }
    recoMET_pt_isLoaded = true;
  }
  return recoMET_pt_;
}

const float &tprimetHHadronic::recoMET_eta() {
  if (not recoMET_eta_isLoaded) {
    if (recoMET_eta_branch != 0) {
      recoMET_eta_branch->GetEntry(index);
    } else {
      printf("branch recoMET_eta_branch does not exist!\n");
      exit(1);
    }
    recoMET_eta_isLoaded = true;
  }
  return recoMET_eta_;
}

const float &tprimetHHadronic::recoMET_phi() {
  if (not recoMET_phi_isLoaded) {
    if (recoMET_phi_branch != 0) {
      recoMET_phi_branch->GetEntry(index);
    } else {
      printf("branch recoMET_phi_branch does not exist!\n");
      exit(1);
    }
    recoMET_phi_isLoaded = true;
  }
  return recoMET_phi_;
}

const float &tprimetHHadronic::recoMET_e() {
  if (not recoMET_e_isLoaded) {
    if (recoMET_e_branch != 0) {
      recoMET_e_branch->GetEntry(index);
    } else {
      printf("branch recoMET_e_branch does not exist!\n");
      exit(1);
    }
    recoMET_e_isLoaded = true;
  }
  return recoMET_e_;
}

const float &tprimetHHadronic::solvedMET_pt() {
  if (not solvedMET_pt_isLoaded) {
    if (solvedMET_pt_branch != 0) {
      solvedMET_pt_branch->GetEntry(index);
    } else {
      printf("branch solvedMET_pt_branch does not exist!\n");
      exit(1);
    }
    solvedMET_pt_isLoaded = true;
  }
  return solvedMET_pt_;
}

const float &tprimetHHadronic::solvedMET_eta() {
  if (not solvedMET_eta_isLoaded) {
    if (solvedMET_eta_branch != 0) {
      solvedMET_eta_branch->GetEntry(index);
    } else {
      printf("branch solvedMET_eta_branch does not exist!\n");
      exit(1);
    }
    solvedMET_eta_isLoaded = true;
  }
  return solvedMET_eta_;
}

const float &tprimetHHadronic::solvedMET_phi() {
  if (not solvedMET_phi_isLoaded) {
    if (solvedMET_phi_branch != 0) {
      solvedMET_phi_branch->GetEntry(index);
    } else {
      printf("branch solvedMET_phi_branch does not exist!\n");
      exit(1);
    }
    solvedMET_phi_isLoaded = true;
  }
  return solvedMET_phi_;
}

const float &tprimetHHadronic::solvedMET_e() {
  if (not solvedMET_e_isLoaded) {
    if (solvedMET_e_branch != 0) {
      solvedMET_e_branch->GetEntry(index);
    } else {
      printf("branch solvedMET_e_branch does not exist!\n");
      exit(1);
    }
    solvedMET_e_isLoaded = true;
  }
  return solvedMET_e_;
}

const float &tprimetHHadronic::dr_leadphobjet() {
  if (not dr_leadphobjet_isLoaded) {
    if (dr_leadphobjet_branch != 0) {
      dr_leadphobjet_branch->GetEntry(index);
    } else {
      printf("branch dr_leadphobjet_branch does not exist!\n");
      exit(1);
    }
    dr_leadphobjet_isLoaded = true;
  }
  return dr_leadphobjet_;
}

const float &tprimetHHadronic::dr_leptonfwdjet() {
  if (not dr_leptonfwdjet_isLoaded) {
    if (dr_leptonfwdjet_branch != 0) {
      dr_leptonfwdjet_branch->GetEntry(index);
    } else {
      printf("branch dr_leptonfwdjet_branch does not exist!\n");
      exit(1);
    }
    dr_leptonfwdjet_isLoaded = true;
  }
  return dr_leptonfwdjet_;
}

const float &tprimetHHadronic::top_mt() {
  if (not top_mt_isLoaded) {
    if (top_mt_branch != 0) {
      top_mt_branch->GetEntry(index);
    } else {
      printf("branch top_mt_branch does not exist!\n");
      exit(1);
    }
    top_mt_isLoaded = true;
  }
  return top_mt_;
}

const float &tprimetHHadronic::top_mass() {
  if (not top_mass_isLoaded) {
    if (top_mass_branch != 0) {
      top_mass_branch->GetEntry(index);
    } else {
      printf("branch top_mass_branch does not exist!\n");
      exit(1);
    }
    top_mass_isLoaded = true;
  }
  return top_mass_;
}

const float &tprimetHHadronic::HT() {
  if (not HT_isLoaded) {
    if (HT_branch != 0) {
      HT_branch->GetEntry(index);
    } else {
      printf("branch HT_branch does not exist!\n");
      exit(1);
    }
    HT_isLoaded = true;
  }
  return HT_;
}

const float &tprimetHHadronic::gen_parton1_pt() {
  if (not gen_parton1_pt_isLoaded) {
    if (gen_parton1_pt_branch != 0) {
      gen_parton1_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_pt_isLoaded = true;
  }
  return gen_parton1_pt_;
}

const float &tprimetHHadronic::gen_parton2_pt() {
  if (not gen_parton2_pt_isLoaded) {
    if (gen_parton2_pt_branch != 0) {
      gen_parton2_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_pt_isLoaded = true;
  }
  return gen_parton2_pt_;
}

const float &tprimetHHadronic::gen_parton3_pt() {
  if (not gen_parton3_pt_isLoaded) {
    if (gen_parton3_pt_branch != 0) {
      gen_parton3_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_pt_isLoaded = true;
  }
  return gen_parton3_pt_;
}

const float &tprimetHHadronic::gen_parton4_pt() {
  if (not gen_parton4_pt_isLoaded) {
    if (gen_parton4_pt_branch != 0) {
      gen_parton4_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_pt_isLoaded = true;
  }
  return gen_parton4_pt_;
}

const float &tprimetHHadronic::gen_parton5_pt() {
  if (not gen_parton5_pt_isLoaded) {
    if (gen_parton5_pt_branch != 0) {
      gen_parton5_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_pt_isLoaded = true;
  }
  return gen_parton5_pt_;
}

const float &tprimetHHadronic::gen_parton6_pt() {
  if (not gen_parton6_pt_isLoaded) {
    if (gen_parton6_pt_branch != 0) {
      gen_parton6_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_pt_isLoaded = true;
  }
  return gen_parton6_pt_;
}

const float &tprimetHHadronic::gen_parton7_pt() {
  if (not gen_parton7_pt_isLoaded) {
    if (gen_parton7_pt_branch != 0) {
      gen_parton7_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_pt_isLoaded = true;
  }
  return gen_parton7_pt_;
}

const float &tprimetHHadronic::gen_parton8_pt() {
  if (not gen_parton8_pt_isLoaded) {
    if (gen_parton8_pt_branch != 0) {
      gen_parton8_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_pt_isLoaded = true;
  }
  return gen_parton8_pt_;
}

const float &tprimetHHadronic::gen_parton9_pt() {
  if (not gen_parton9_pt_isLoaded) {
    if (gen_parton9_pt_branch != 0) {
      gen_parton9_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_pt_isLoaded = true;
  }
  return gen_parton9_pt_;
}

const float &tprimetHHadronic::gen_parton10_pt() {
  if (not gen_parton10_pt_isLoaded) {
    if (gen_parton10_pt_branch != 0) {
      gen_parton10_pt_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_pt_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_pt_isLoaded = true;
  }
  return gen_parton10_pt_;
}

const float &tprimetHHadronic::gen_parton1_eta() {
  if (not gen_parton1_eta_isLoaded) {
    if (gen_parton1_eta_branch != 0) {
      gen_parton1_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_eta_isLoaded = true;
  }
  return gen_parton1_eta_;
}

const float &tprimetHHadronic::gen_parton2_eta() {
  if (not gen_parton2_eta_isLoaded) {
    if (gen_parton2_eta_branch != 0) {
      gen_parton2_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_eta_isLoaded = true;
  }
  return gen_parton2_eta_;
}

const float &tprimetHHadronic::gen_parton3_eta() {
  if (not gen_parton3_eta_isLoaded) {
    if (gen_parton3_eta_branch != 0) {
      gen_parton3_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_eta_isLoaded = true;
  }
  return gen_parton3_eta_;
}

const float &tprimetHHadronic::gen_parton4_eta() {
  if (not gen_parton4_eta_isLoaded) {
    if (gen_parton4_eta_branch != 0) {
      gen_parton4_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_eta_isLoaded = true;
  }
  return gen_parton4_eta_;
}

const float &tprimetHHadronic::gen_parton5_eta() {
  if (not gen_parton5_eta_isLoaded) {
    if (gen_parton5_eta_branch != 0) {
      gen_parton5_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_eta_isLoaded = true;
  }
  return gen_parton5_eta_;
}

const float &tprimetHHadronic::gen_parton6_eta() {
  if (not gen_parton6_eta_isLoaded) {
    if (gen_parton6_eta_branch != 0) {
      gen_parton6_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_eta_isLoaded = true;
  }
  return gen_parton6_eta_;
}

const float &tprimetHHadronic::gen_parton7_eta() {
  if (not gen_parton7_eta_isLoaded) {
    if (gen_parton7_eta_branch != 0) {
      gen_parton7_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_eta_isLoaded = true;
  }
  return gen_parton7_eta_;
}

const float &tprimetHHadronic::gen_parton8_eta() {
  if (not gen_parton8_eta_isLoaded) {
    if (gen_parton8_eta_branch != 0) {
      gen_parton8_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_eta_isLoaded = true;
  }
  return gen_parton8_eta_;
}

const float &tprimetHHadronic::gen_parton9_eta() {
  if (not gen_parton9_eta_isLoaded) {
    if (gen_parton9_eta_branch != 0) {
      gen_parton9_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_eta_isLoaded = true;
  }
  return gen_parton9_eta_;
}

const float &tprimetHHadronic::gen_parton10_eta() {
  if (not gen_parton10_eta_isLoaded) {
    if (gen_parton10_eta_branch != 0) {
      gen_parton10_eta_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_eta_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_eta_isLoaded = true;
  }
  return gen_parton10_eta_;
}

const float &tprimetHHadronic::gen_parton1_phi() {
  if (not gen_parton1_phi_isLoaded) {
    if (gen_parton1_phi_branch != 0) {
      gen_parton1_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_phi_isLoaded = true;
  }
  return gen_parton1_phi_;
}

const float &tprimetHHadronic::gen_parton2_phi() {
  if (not gen_parton2_phi_isLoaded) {
    if (gen_parton2_phi_branch != 0) {
      gen_parton2_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_phi_isLoaded = true;
  }
  return gen_parton2_phi_;
}

const float &tprimetHHadronic::gen_parton3_phi() {
  if (not gen_parton3_phi_isLoaded) {
    if (gen_parton3_phi_branch != 0) {
      gen_parton3_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_phi_isLoaded = true;
  }
  return gen_parton3_phi_;
}

const float &tprimetHHadronic::gen_parton4_phi() {
  if (not gen_parton4_phi_isLoaded) {
    if (gen_parton4_phi_branch != 0) {
      gen_parton4_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_phi_isLoaded = true;
  }
  return gen_parton4_phi_;
}

const float &tprimetHHadronic::gen_parton5_phi() {
  if (not gen_parton5_phi_isLoaded) {
    if (gen_parton5_phi_branch != 0) {
      gen_parton5_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_phi_isLoaded = true;
  }
  return gen_parton5_phi_;
}

const float &tprimetHHadronic::gen_parton6_phi() {
  if (not gen_parton6_phi_isLoaded) {
    if (gen_parton6_phi_branch != 0) {
      gen_parton6_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_phi_isLoaded = true;
  }
  return gen_parton6_phi_;
}

const float &tprimetHHadronic::gen_parton7_phi() {
  if (not gen_parton7_phi_isLoaded) {
    if (gen_parton7_phi_branch != 0) {
      gen_parton7_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_phi_isLoaded = true;
  }
  return gen_parton7_phi_;
}

const float &tprimetHHadronic::gen_parton8_phi() {
  if (not gen_parton8_phi_isLoaded) {
    if (gen_parton8_phi_branch != 0) {
      gen_parton8_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_phi_isLoaded = true;
  }
  return gen_parton8_phi_;
}

const float &tprimetHHadronic::gen_parton9_phi() {
  if (not gen_parton9_phi_isLoaded) {
    if (gen_parton9_phi_branch != 0) {
      gen_parton9_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_phi_isLoaded = true;
  }
  return gen_parton9_phi_;
}

const float &tprimetHHadronic::gen_parton10_phi() {
  if (not gen_parton10_phi_isLoaded) {
    if (gen_parton10_phi_branch != 0) {
      gen_parton10_phi_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_phi_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_phi_isLoaded = true;
  }
  return gen_parton10_phi_;
}

const float &tprimetHHadronic::gen_parton1_mass() {
  if (not gen_parton1_mass_isLoaded) {
    if (gen_parton1_mass_branch != 0) {
      gen_parton1_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_mass_isLoaded = true;
  }
  return gen_parton1_mass_;
}

const float &tprimetHHadronic::gen_parton2_mass() {
  if (not gen_parton2_mass_isLoaded) {
    if (gen_parton2_mass_branch != 0) {
      gen_parton2_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_mass_isLoaded = true;
  }
  return gen_parton2_mass_;
}

const float &tprimetHHadronic::gen_parton3_mass() {
  if (not gen_parton3_mass_isLoaded) {
    if (gen_parton3_mass_branch != 0) {
      gen_parton3_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_mass_isLoaded = true;
  }
  return gen_parton3_mass_;
}

const float &tprimetHHadronic::gen_parton4_mass() {
  if (not gen_parton4_mass_isLoaded) {
    if (gen_parton4_mass_branch != 0) {
      gen_parton4_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_mass_isLoaded = true;
  }
  return gen_parton4_mass_;
}

const float &tprimetHHadronic::gen_parton5_mass() {
  if (not gen_parton5_mass_isLoaded) {
    if (gen_parton5_mass_branch != 0) {
      gen_parton5_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_mass_isLoaded = true;
  }
  return gen_parton5_mass_;
}

const float &tprimetHHadronic::gen_parton6_mass() {
  if (not gen_parton6_mass_isLoaded) {
    if (gen_parton6_mass_branch != 0) {
      gen_parton6_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_mass_isLoaded = true;
  }
  return gen_parton6_mass_;
}

const float &tprimetHHadronic::gen_parton7_mass() {
  if (not gen_parton7_mass_isLoaded) {
    if (gen_parton7_mass_branch != 0) {
      gen_parton7_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_mass_isLoaded = true;
  }
  return gen_parton7_mass_;
}

const float &tprimetHHadronic::gen_parton8_mass() {
  if (not gen_parton8_mass_isLoaded) {
    if (gen_parton8_mass_branch != 0) {
      gen_parton8_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_mass_isLoaded = true;
  }
  return gen_parton8_mass_;
}

const float &tprimetHHadronic::gen_parton9_mass() {
  if (not gen_parton9_mass_isLoaded) {
    if (gen_parton9_mass_branch != 0) {
      gen_parton9_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_mass_isLoaded = true;
  }
  return gen_parton9_mass_;
}

const float &tprimetHHadronic::gen_parton10_mass() {
  if (not gen_parton10_mass_isLoaded) {
    if (gen_parton10_mass_branch != 0) {
      gen_parton10_mass_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_mass_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_mass_isLoaded = true;
  }
  return gen_parton10_mass_;
}

const float &tprimetHHadronic::gen_parton1_pdgId() {
  if (not gen_parton1_pdgId_isLoaded) {
    if (gen_parton1_pdgId_branch != 0) {
      gen_parton1_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_pdgId_isLoaded = true;
  }
  return gen_parton1_pdgId_;
}

const float &tprimetHHadronic::gen_parton2_pdgId() {
  if (not gen_parton2_pdgId_isLoaded) {
    if (gen_parton2_pdgId_branch != 0) {
      gen_parton2_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_pdgId_isLoaded = true;
  }
  return gen_parton2_pdgId_;
}

const float &tprimetHHadronic::gen_parton3_pdgId() {
  if (not gen_parton3_pdgId_isLoaded) {
    if (gen_parton3_pdgId_branch != 0) {
      gen_parton3_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_pdgId_isLoaded = true;
  }
  return gen_parton3_pdgId_;
}

const float &tprimetHHadronic::gen_parton4_pdgId() {
  if (not gen_parton4_pdgId_isLoaded) {
    if (gen_parton4_pdgId_branch != 0) {
      gen_parton4_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_pdgId_isLoaded = true;
  }
  return gen_parton4_pdgId_;
}

const float &tprimetHHadronic::gen_parton5_pdgId() {
  if (not gen_parton5_pdgId_isLoaded) {
    if (gen_parton5_pdgId_branch != 0) {
      gen_parton5_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_pdgId_isLoaded = true;
  }
  return gen_parton5_pdgId_;
}

const float &tprimetHHadronic::gen_parton6_pdgId() {
  if (not gen_parton6_pdgId_isLoaded) {
    if (gen_parton6_pdgId_branch != 0) {
      gen_parton6_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_pdgId_isLoaded = true;
  }
  return gen_parton6_pdgId_;
}

const float &tprimetHHadronic::gen_parton7_pdgId() {
  if (not gen_parton7_pdgId_isLoaded) {
    if (gen_parton7_pdgId_branch != 0) {
      gen_parton7_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_pdgId_isLoaded = true;
  }
  return gen_parton7_pdgId_;
}

const float &tprimetHHadronic::gen_parton8_pdgId() {
  if (not gen_parton8_pdgId_isLoaded) {
    if (gen_parton8_pdgId_branch != 0) {
      gen_parton8_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_pdgId_isLoaded = true;
  }
  return gen_parton8_pdgId_;
}

const float &tprimetHHadronic::gen_parton9_pdgId() {
  if (not gen_parton9_pdgId_isLoaded) {
    if (gen_parton9_pdgId_branch != 0) {
      gen_parton9_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_pdgId_isLoaded = true;
  }
  return gen_parton9_pdgId_;
}

const float &tprimetHHadronic::gen_parton10_pdgId() {
  if (not gen_parton10_pdgId_isLoaded) {
    if (gen_parton10_pdgId_branch != 0) {
      gen_parton10_pdgId_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_pdgId_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_pdgId_isLoaded = true;
  }
  return gen_parton10_pdgId_;
}

const float &tprimetHHadronic::gen_parton1_status() {
  if (not gen_parton1_status_isLoaded) {
    if (gen_parton1_status_branch != 0) {
      gen_parton1_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton1_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton1_status_isLoaded = true;
  }
  return gen_parton1_status_;
}

const float &tprimetHHadronic::gen_parton2_status() {
  if (not gen_parton2_status_isLoaded) {
    if (gen_parton2_status_branch != 0) {
      gen_parton2_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton2_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton2_status_isLoaded = true;
  }
  return gen_parton2_status_;
}

const float &tprimetHHadronic::gen_parton3_status() {
  if (not gen_parton3_status_isLoaded) {
    if (gen_parton3_status_branch != 0) {
      gen_parton3_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton3_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton3_status_isLoaded = true;
  }
  return gen_parton3_status_;
}

const float &tprimetHHadronic::gen_parton4_status() {
  if (not gen_parton4_status_isLoaded) {
    if (gen_parton4_status_branch != 0) {
      gen_parton4_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton4_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton4_status_isLoaded = true;
  }
  return gen_parton4_status_;
}

const float &tprimetHHadronic::gen_parton5_status() {
  if (not gen_parton5_status_isLoaded) {
    if (gen_parton5_status_branch != 0) {
      gen_parton5_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton5_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton5_status_isLoaded = true;
  }
  return gen_parton5_status_;
}

const float &tprimetHHadronic::gen_parton6_status() {
  if (not gen_parton6_status_isLoaded) {
    if (gen_parton6_status_branch != 0) {
      gen_parton6_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton6_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton6_status_isLoaded = true;
  }
  return gen_parton6_status_;
}

const float &tprimetHHadronic::gen_parton7_status() {
  if (not gen_parton7_status_isLoaded) {
    if (gen_parton7_status_branch != 0) {
      gen_parton7_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton7_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton7_status_isLoaded = true;
  }
  return gen_parton7_status_;
}

const float &tprimetHHadronic::gen_parton8_status() {
  if (not gen_parton8_status_isLoaded) {
    if (gen_parton8_status_branch != 0) {
      gen_parton8_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton8_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton8_status_isLoaded = true;
  }
  return gen_parton8_status_;
}

const float &tprimetHHadronic::gen_parton9_status() {
  if (not gen_parton9_status_isLoaded) {
    if (gen_parton9_status_branch != 0) {
      gen_parton9_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton9_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton9_status_isLoaded = true;
  }
  return gen_parton9_status_;
}

const float &tprimetHHadronic::gen_parton10_status() {
  if (not gen_parton10_status_isLoaded) {
    if (gen_parton10_status_branch != 0) {
      gen_parton10_status_branch->GetEntry(index);
    } else {
      printf("branch gen_parton10_status_branch does not exist!\n");
      exit(1);
    }
    gen_parton10_status_isLoaded = true;
  }
  return gen_parton10_status_;
}

const float &tprimetHHadronic::genMatched_jet0_pdgId() {
  if (not genMatched_jet0_pdgId_isLoaded) {
    if (genMatched_jet0_pdgId_branch != 0) {
      genMatched_jet0_pdgId_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet0_pdgId_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet0_pdgId_isLoaded = true;
  }
  return genMatched_jet0_pdgId_;
}

const float &tprimetHHadronic::genMatched_jet1_pdgId() {
  if (not genMatched_jet1_pdgId_isLoaded) {
    if (genMatched_jet1_pdgId_branch != 0) {
      genMatched_jet1_pdgId_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet1_pdgId_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet1_pdgId_isLoaded = true;
  }
  return genMatched_jet1_pdgId_;
}

const float &tprimetHHadronic::genMatched_jet2_pdgId() {
  if (not genMatched_jet2_pdgId_isLoaded) {
    if (genMatched_jet2_pdgId_branch != 0) {
      genMatched_jet2_pdgId_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet2_pdgId_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet2_pdgId_isLoaded = true;
  }
  return genMatched_jet2_pdgId_;
}

const float &tprimetHHadronic::genMatched_jet0_index() {
  if (not genMatched_jet0_index_isLoaded) {
    if (genMatched_jet0_index_branch != 0) {
      genMatched_jet0_index_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet0_index_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet0_index_isLoaded = true;
  }
  return genMatched_jet0_index_;
}

const float &tprimetHHadronic::genMatched_jet1_index() {
  if (not genMatched_jet1_index_isLoaded) {
    if (genMatched_jet1_index_branch != 0) {
      genMatched_jet1_index_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet1_index_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet1_index_isLoaded = true;
  }
  return genMatched_jet1_index_;
}

const float &tprimetHHadronic::genMatched_jet2_index() {
  if (not genMatched_jet2_index_isLoaded) {
    if (genMatched_jet2_index_branch != 0) {
      genMatched_jet2_index_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet2_index_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet2_index_isLoaded = true;
  }
  return genMatched_jet2_index_;
}

const float &tprimetHHadronic::genMatched_jet0_deltaR() {
  if (not genMatched_jet0_deltaR_isLoaded) {
    if (genMatched_jet0_deltaR_branch != 0) {
      genMatched_jet0_deltaR_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet0_deltaR_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet0_deltaR_isLoaded = true;
  }
  return genMatched_jet0_deltaR_;
}

const float &tprimetHHadronic::genMatched_jet1_deltaR() {
  if (not genMatched_jet1_deltaR_isLoaded) {
    if (genMatched_jet1_deltaR_branch != 0) {
      genMatched_jet1_deltaR_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet1_deltaR_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet1_deltaR_isLoaded = true;
  }
  return genMatched_jet1_deltaR_;
}

const float &tprimetHHadronic::genMatched_jet2_deltaR() {
  if (not genMatched_jet2_deltaR_isLoaded) {
    if (genMatched_jet2_deltaR_branch != 0) {
      genMatched_jet2_deltaR_branch->GetEntry(index);
    } else {
      printf("branch genMatched_jet2_deltaR_branch does not exist!\n");
      exit(1);
    }
    genMatched_jet2_deltaR_isLoaded = true;
  }
  return genMatched_jet2_deltaR_;
}

const float &tprimetHHadronic::genMET_pt() {
  if (not genMET_pt_isLoaded) {
    if (genMET_pt_branch != 0) {
      genMET_pt_branch->GetEntry(index);
    } else {
      printf("branch genMET_pt_branch does not exist!\n");
      exit(1);
    }
    genMET_pt_isLoaded = true;
  }
  return genMET_pt_;
}

const float &tprimetHHadronic::genMET_eta() {
  if (not genMET_eta_isLoaded) {
    if (genMET_eta_branch != 0) {
      genMET_eta_branch->GetEntry(index);
    } else {
      printf("branch genMET_eta_branch does not exist!\n");
      exit(1);
    }
    genMET_eta_isLoaded = true;
  }
  return genMET_eta_;
}

const float &tprimetHHadronic::genMET_phi() {
  if (not genMET_phi_isLoaded) {
    if (genMET_phi_branch != 0) {
      genMET_phi_branch->GetEntry(index);
    } else {
      printf("branch genMET_phi_branch does not exist!\n");
      exit(1);
    }
    genMET_phi_isLoaded = true;
  }
  return genMET_phi_;
}

const float &tprimetHHadronic::genMET_e() {
  if (not genMET_e_isLoaded) {
    if (genMET_e_branch != 0) {
      genMET_e_branch->GetEntry(index);
    } else {
      printf("branch genMET_e_branch does not exist!\n");
      exit(1);
    }
    genMET_e_isLoaded = true;
  }
  return genMET_e_;
}

const float &tprimetHHadronic::promptGenMET_pt() {
  if (not promptGenMET_pt_isLoaded) {
    if (promptGenMET_pt_branch != 0) {
      promptGenMET_pt_branch->GetEntry(index);
    } else {
      printf("branch promptGenMET_pt_branch does not exist!\n");
      exit(1);
    }
    promptGenMET_pt_isLoaded = true;
  }
  return promptGenMET_pt_;
}

const float &tprimetHHadronic::promptGenMET_eta() {
  if (not promptGenMET_eta_isLoaded) {
    if (promptGenMET_eta_branch != 0) {
      promptGenMET_eta_branch->GetEntry(index);
    } else {
      printf("branch promptGenMET_eta_branch does not exist!\n");
      exit(1);
    }
    promptGenMET_eta_isLoaded = true;
  }
  return promptGenMET_eta_;
}

const float &tprimetHHadronic::promptGenMET_phi() {
  if (not promptGenMET_phi_isLoaded) {
    if (promptGenMET_phi_branch != 0) {
      promptGenMET_phi_branch->GetEntry(index);
    } else {
      printf("branch promptGenMET_phi_branch does not exist!\n");
      exit(1);
    }
    promptGenMET_phi_isLoaded = true;
  }
  return promptGenMET_phi_;
}

const float &tprimetHHadronic::promptGenMET_e() {
  if (not promptGenMET_e_isLoaded) {
    if (promptGenMET_e_branch != 0) {
      promptGenMET_e_branch->GetEntry(index);
    } else {
      printf("branch promptGenMET_e_branch does not exist!\n");
      exit(1);
    }
    promptGenMET_e_isLoaded = true;
  }
  return promptGenMET_e_;
}

const float &tprimetHHadronic::genMETTrue_pt() {
  if (not genMETTrue_pt_isLoaded) {
    if (genMETTrue_pt_branch != 0) {
      genMETTrue_pt_branch->GetEntry(index);
    } else {
      printf("branch genMETTrue_pt_branch does not exist!\n");
      exit(1);
    }
    genMETTrue_pt_isLoaded = true;
  }
  return genMETTrue_pt_;
}

const float &tprimetHHadronic::genMETTrue_eta() {
  if (not genMETTrue_eta_isLoaded) {
    if (genMETTrue_eta_branch != 0) {
      genMETTrue_eta_branch->GetEntry(index);
    } else {
      printf("branch genMETTrue_eta_branch does not exist!\n");
      exit(1);
    }
    genMETTrue_eta_isLoaded = true;
  }
  return genMETTrue_eta_;
}

const float &tprimetHHadronic::genMETTrue_phi() {
  if (not genMETTrue_phi_isLoaded) {
    if (genMETTrue_phi_branch != 0) {
      genMETTrue_phi_branch->GetEntry(index);
    } else {
      printf("branch genMETTrue_phi_branch does not exist!\n");
      exit(1);
    }
    genMETTrue_phi_isLoaded = true;
  }
  return genMETTrue_phi_;
}

const float &tprimetHHadronic::genMETTrue_e() {
  if (not genMETTrue_e_isLoaded) {
    if (genMETTrue_e_branch != 0) {
      genMETTrue_e_branch->GetEntry(index);
    } else {
      printf("branch genMETTrue_e_branch does not exist!\n");
      exit(1);
    }
    genMETTrue_e_isLoaded = true;
  }
  return genMETTrue_e_;
}

const float &tprimetHHadronic::rho() {
  if (not rho_isLoaded) {
    if (rho_branch != 0) {
      rho_branch->GetEntry(index);
    } else {
      printf("branch rho_branch does not exist!\n");
      exit(1);
    }
    rho_isLoaded = true;
  }
  return rho_;
}

const int &tprimetHHadronic::nvtx() {
  if (not nvtx_isLoaded) {
    if (nvtx_branch != 0) {
      nvtx_branch->GetEntry(index);
    } else {
      printf("branch nvtx_branch does not exist!\n");
      exit(1);
    }
    nvtx_isLoaded = true;
  }
  return nvtx_;
}

const unsigned long long &tprimetHHadronic::event() {
  if (not event_isLoaded) {
    if (event_branch != 0) {
      event_branch->GetEntry(index);
    } else {
      printf("branch event_branch does not exist!\n");
      exit(1);
    }
    event_isLoaded = true;
  }
  return event_;
}

const unsigned int &tprimetHHadronic::lumi() {
  if (not lumi_isLoaded) {
    if (lumi_branch != 0) {
      lumi_branch->GetEntry(index);
    } else {
      printf("branch lumi_branch does not exist!\n");
      exit(1);
    }
    lumi_isLoaded = true;
  }
  return lumi_;
}

const int &tprimetHHadronic::processIndex() {
  if (not processIndex_isLoaded) {
    if (processIndex_branch != 0) {
      processIndex_branch->GetEntry(index);
    } else {
      printf("branch processIndex_branch does not exist!\n");
      exit(1);
    }
    processIndex_isLoaded = true;
  }
  return processIndex_;
}

const unsigned int &tprimetHHadronic::run() {
  if (not run_isLoaded) {
    if (run_branch != 0) {
      run_branch->GetEntry(index);
    } else {
      printf("branch run_branch does not exist!\n");
      exit(1);
    }
    run_isLoaded = true;
  }
  return run_;
}

const float &tprimetHHadronic::npu() {
  if (not npu_isLoaded) {
    if (npu_branch != 0) {
      npu_branch->GetEntry(index);
    } else {
      printf("branch npu_branch does not exist!\n");
      exit(1);
    }
    npu_isLoaded = true;
  }
  return npu_;
}

const float &tprimetHHadronic::puweight() {
  if (not puweight_isLoaded) {
    if (puweight_branch != 0) {
      puweight_branch->GetEntry(index);
    } else {
      printf("branch puweight_branch does not exist!\n");
      exit(1);
    }
    puweight_isLoaded = true;
  }
  return puweight_;
}


void tprimetHHadronic::progress( int nEventsTotal, int nEventsChain ){
  int period = 1000;
  if (nEventsTotal%1000 == 0) {
    // xterm magic from L. Vacavant and A. Cerri
    if (isatty(1)) {
      if ((nEventsChain - nEventsTotal) > period) {
        float frac = (float)nEventsTotal/(nEventsChain*0.01);
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
             "\033[0m\033[32m <---\033[0m\015", frac);
        fflush(stdout);
      }
      else {
        printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", 100.);
        cout << endl;
      }
    }
  }
}

namespace tprime {

const int &candidate_id() { return analyzer.candidate_id(); }
const float &weight() { return analyzer.weight(); }
const float &CMS_hgg_mass() { return analyzer.CMS_hgg_mass(); }
const float &sigmaMoM_decorr() { return analyzer.sigmaMoM_decorr(); }
const float &dZ() { return analyzer.dZ(); }
const float &centralObjectWeight() { return analyzer.centralObjectWeight(); }
const float &vtxprob() { return analyzer.vtxprob(); }
const float &ptbal() { return analyzer.ptbal(); }
const float &ptasym() { return analyzer.ptasym(); }
const float &logspt2() { return analyzer.logspt2(); }
const float &p2conv() { return analyzer.p2conv(); }
const float &nconv() { return analyzer.nconv(); }
const float &vtxmva() { return analyzer.vtxmva(); }
const float &vtxdz() { return analyzer.vtxdz(); }
const float &vtx_x() { return analyzer.vtx_x(); }
const float &vtx_y() { return analyzer.vtx_y(); }
const float &vtx_z() { return analyzer.vtx_z(); }
const float &dipho_sumpt() { return analyzer.dipho_sumpt(); }
const float &dipho_cosphi() { return analyzer.dipho_cosphi(); }
const float &dipho_mass() { return analyzer.dipho_mass(); }
const float &dipho_pt() { return analyzer.dipho_pt(); }
const float &dipho_phi() { return analyzer.dipho_phi(); }
const float &dipho_eta() { return analyzer.dipho_eta(); }
const float &dipho_e() { return analyzer.dipho_e(); }
const float &dipho_PtoM() { return analyzer.dipho_PtoM(); }
const float &cosphi() { return analyzer.cosphi(); }
const float &sigmaMrvoM() { return analyzer.sigmaMrvoM(); }
const float &sigmaMwvoM() { return analyzer.sigmaMwvoM(); }
const float &dipho_leadPt() { return analyzer.dipho_leadPt(); }
const float &dipho_leadEt() { return analyzer.dipho_leadEt(); }
const float &dipho_leadEta() { return analyzer.dipho_leadEta(); }
const float &dipho_leadPhi() { return analyzer.dipho_leadPhi(); }
const float &dipho_lead_sieie() { return analyzer.dipho_lead_sieie(); }
const float &dipho_lead_hoe() { return analyzer.dipho_lead_hoe(); }
const float &dipho_lead_sigmaEoE() { return analyzer.dipho_lead_sigmaEoE(); }
const float &dipho_lead_ptoM() { return analyzer.dipho_lead_ptoM(); }
const float &dipho_leadR9() { return analyzer.dipho_leadR9(); }
const float &dipho_leadIDMVA() { return analyzer.dipho_leadIDMVA(); }
const float &dipho_lead_elveto() { return analyzer.dipho_lead_elveto(); }
const float &dipho_lead_prompt() { return analyzer.dipho_lead_prompt(); }
const float &dipho_lead_chiso() { return analyzer.dipho_lead_chiso(); }
const float &dipho_lead_chisow() { return analyzer.dipho_lead_chisow(); }
const float &dipho_lead_phoiso() { return analyzer.dipho_lead_phoiso(); }
const float &dipho_lead_phoiso04() { return analyzer.dipho_lead_phoiso04(); }
const float &dipho_lead_neutiso() { return analyzer.dipho_lead_neutiso(); }
const float &dipho_lead_ecaliso03() { return analyzer.dipho_lead_ecaliso03(); }
const float &dipho_lead_hcaliso03() { return analyzer.dipho_lead_hcaliso03(); }
const float &dipho_lead_pfcluecal03() { return analyzer.dipho_lead_pfcluecal03(); }
const float &dipho_lead_pfcluhcal03() { return analyzer.dipho_lead_pfcluhcal03(); }
const float &dipho_lead_trkiso03() { return analyzer.dipho_lead_trkiso03(); }
const float &dipho_lead_pfchiso2() { return analyzer.dipho_lead_pfchiso2(); }
const float &dipho_lead_haspixelseed() { return analyzer.dipho_lead_haspixelseed(); }
const float &dipho_lead_sieip() { return analyzer.dipho_lead_sieip(); }
const float &dipho_lead_etawidth() { return analyzer.dipho_lead_etawidth(); }
const float &dipho_lead_phiwidth() { return analyzer.dipho_lead_phiwidth(); }
const float &dipho_lead_regrerr() { return analyzer.dipho_lead_regrerr(); }
const float &dipho_lead_s4ratio() { return analyzer.dipho_lead_s4ratio(); }
const float &dipho_lead_effSigma() { return analyzer.dipho_lead_effSigma(); }
const float &dipho_lead_scraw() { return analyzer.dipho_lead_scraw(); }
const float &dipho_lead_ese() { return analyzer.dipho_lead_ese(); }
const float &dipho_subleadPt() { return analyzer.dipho_subleadPt(); }
const float &dipho_subleadEt() { return analyzer.dipho_subleadEt(); }
const float &dipho_subleadEta() { return analyzer.dipho_subleadEta(); }
const float &dipho_subleadPhi() { return analyzer.dipho_subleadPhi(); }
const float &dipho_sublead_sieie() { return analyzer.dipho_sublead_sieie(); }
const float &dipho_sublead_hoe() { return analyzer.dipho_sublead_hoe(); }
const float &dipho_sublead_sigmaEoE() { return analyzer.dipho_sublead_sigmaEoE(); }
const float &dipho_sublead_ptoM() { return analyzer.dipho_sublead_ptoM(); }
const float &dipho_subleadR9() { return analyzer.dipho_subleadR9(); }
const float &dipho_subleadIDMVA() { return analyzer.dipho_subleadIDMVA(); }
const float &dipho_sublead_elveto() { return analyzer.dipho_sublead_elveto(); }
const float &dipho_sulead_prompt() { return analyzer.dipho_sulead_prompt(); }
const float &dipho_sublead_chiso() { return analyzer.dipho_sublead_chiso(); }
const float &dipho_sublead_chisow() { return analyzer.dipho_sublead_chisow(); }
const float &dipho_sublead_phoiso() { return analyzer.dipho_sublead_phoiso(); }
const float &dipho_sublead_phoiso04() { return analyzer.dipho_sublead_phoiso04(); }
const float &dipho_sublead_neutiso() { return analyzer.dipho_sublead_neutiso(); }
const float &dipho_sublead_ecaliso03() { return analyzer.dipho_sublead_ecaliso03(); }
const float &dipho_sublead_hcaliso03() { return analyzer.dipho_sublead_hcaliso03(); }
const float &dipho_sublead_pfcluecal03() { return analyzer.dipho_sublead_pfcluecal03(); }
const float &dipho_sublead_pfcluhcal03() { return analyzer.dipho_sublead_pfcluhcal03(); }
const float &dipho_sublead_trkiso03() { return analyzer.dipho_sublead_trkiso03(); }
const float &dipho_sublead_pfchiso2() { return analyzer.dipho_sublead_pfchiso2(); }
const float &dipho_sublead_haspixelseed() { return analyzer.dipho_sublead_haspixelseed(); }
const float &dipho_sublead_sieip() { return analyzer.dipho_sublead_sieip(); }
const float &dipho_sublead_etawidth() { return analyzer.dipho_sublead_etawidth(); }
const float &dipho_sublead_phiwidth() { return analyzer.dipho_sublead_phiwidth(); }
const float &dipho_sublead_regrerr() { return analyzer.dipho_sublead_regrerr(); }
const float &dipho_sublead_s4ratio() { return analyzer.dipho_sublead_s4ratio(); }
const float &dipho_sublead_effSigma() { return analyzer.dipho_sublead_effSigma(); }
const float &dipho_sublead_scraw() { return analyzer.dipho_sublead_scraw(); }
const float &dipho_sublead_ese() { return analyzer.dipho_sublead_ese(); }
const float &LeptonType() { return analyzer.LeptonType(); }
const float &n_ele() { return analyzer.n_ele(); }
const float &n_loose_ele() { return analyzer.n_loose_ele(); }
const float &n_veto_ele() { return analyzer.n_veto_ele(); }
const float &n_medium_ele() { return analyzer.n_medium_ele(); }
const float &n_tight_ele() { return analyzer.n_tight_ele(); }
const float &ele1_pt() { return analyzer.ele1_pt(); }
const float &ele2_pt() { return analyzer.ele2_pt(); }
const float &ele1_eta() { return analyzer.ele1_eta(); }
const float &ele2_eta() { return analyzer.ele2_eta(); }
const float &ele1_phi() { return analyzer.ele1_phi(); }
const float &ele2_phi() { return analyzer.ele2_phi(); }
const float &ele1_e() { return analyzer.ele1_e(); }
const float &ele2_e() { return analyzer.ele2_e(); }
const float &ele1_ch() { return analyzer.ele1_ch(); }
const float &ele2_ch() { return analyzer.ele2_ch(); }
const float &ele1_sigmaIetaIeta() { return analyzer.ele1_sigmaIetaIeta(); }
const float &ele2_sigmaIetaIeta() { return analyzer.ele2_sigmaIetaIeta(); }
const float &ele1_dEtaInSeed() { return analyzer.ele1_dEtaInSeed(); }
const float &ele2_dEtaInSeed() { return analyzer.ele2_dEtaInSeed(); }
const float &ele1_dPhiIn() { return analyzer.ele1_dPhiIn(); }
const float &ele2_dPhiIn() { return analyzer.ele2_dPhiIn(); }
const float &ele1_hOverE() { return analyzer.ele1_hOverE(); }
const float &ele2_hOverE() { return analyzer.ele2_hOverE(); }
const float &ele1_RelIsoEA() { return analyzer.ele1_RelIsoEA(); }
const float &ele2_RelIsoEA() { return analyzer.ele2_RelIsoEA(); }
const float &ele1_ooEmooP() { return analyzer.ele1_ooEmooP(); }
const float &ele2_ooEmooP() { return analyzer.ele2_ooEmooP(); }
const float &ele1_dxy() { return analyzer.ele1_dxy(); }
const float &ele2_dxy() { return analyzer.ele2_dxy(); }
const float &ele1_diphodxy() { return analyzer.ele1_diphodxy(); }
const float &ele2_diphodxy() { return analyzer.ele2_diphodxy(); }
const float &ele1_dz() { return analyzer.ele1_dz(); }
const float &ele2_dz() { return analyzer.ele2_dz(); }
const float &ele1_diphodz() { return analyzer.ele1_diphodz(); }
const float &ele2_diphodz() { return analyzer.ele2_diphodz(); }
const float &ele1_misHits() { return analyzer.ele1_misHits(); }
const float &ele2_misHits() { return analyzer.ele2_misHits(); }
const float &ele1_ConversionVeto() { return analyzer.ele1_ConversionVeto(); }
const float &ele2_ConversionVeto() { return analyzer.ele2_ConversionVeto(); }
const float &ele1_ChargedHadronPt() { return analyzer.ele1_ChargedHadronPt(); }
const float &ele2_ChargedHadronPt() { return analyzer.ele2_ChargedHadronPt(); }
const float &ele2_NeutralHadronEt() { return analyzer.ele2_NeutralHadronEt(); }
const float &ele1_NeutralHadronEt() { return analyzer.ele1_NeutralHadronEt(); }
const float &ele1_PhotonEt() { return analyzer.ele1_PhotonEt(); }
const float &ele2_PhotonEt() { return analyzer.ele2_PhotonEt(); }
const float &ele1_PassTight() { return analyzer.ele1_PassTight(); }
const float &ele2_PassTight() { return analyzer.ele2_PassTight(); }
const float &ele1_PassVeto() { return analyzer.ele1_PassVeto(); }
const float &ele2_PassVeto() { return analyzer.ele2_PassVeto(); }
const float &ele1_dPhiMET() { return analyzer.ele1_dPhiMET(); }
const float &ele2_dPhiMET() { return analyzer.ele2_dPhiMET(); }
const float &n_muons() { return analyzer.n_muons(); }
const float &n_LooseMu25() { return analyzer.n_LooseMu25(); }
const float &n_LooseMu15() { return analyzer.n_LooseMu15(); }
const float &n_TightMu25() { return analyzer.n_TightMu25(); }
const float &n_TightMu15() { return analyzer.n_TightMu15(); }
const float &n_MediumMu25() { return analyzer.n_MediumMu25(); }
const float &n_MediumMu15() { return analyzer.n_MediumMu15(); }
const float &muon1_pt() { return analyzer.muon1_pt(); }
const float &muon2_pt() { return analyzer.muon2_pt(); }
const float &muon1_eta() { return analyzer.muon1_eta(); }
const float &muon2_eta() { return analyzer.muon2_eta(); }
const float &muon1_phi() { return analyzer.muon1_phi(); }
const float &muon2_phi() { return analyzer.muon2_phi(); }
const float &muon1_e() { return analyzer.muon1_e(); }
const float &muon2_e() { return analyzer.muon2_e(); }
const float &muon1_ch() { return analyzer.muon1_ch(); }
const float &muon2_ch() { return analyzer.muon2_ch(); }
const float &muon1_iso() { return analyzer.muon1_iso(); }
const float &muon2_iso() { return analyzer.muon2_iso(); }
const float &muon1_chi2() { return analyzer.muon1_chi2(); }
const float &muon2_chi2() { return analyzer.muon2_chi2(); }
const float &muon1_mHits() { return analyzer.muon1_mHits(); }
const float &muon2_mHits() { return analyzer.muon2_mHits(); }
const float &muon1_mStations() { return analyzer.muon1_mStations(); }
const float &muon2_mStations() { return analyzer.muon2_mStations(); }
const float &muon1_dxy() { return analyzer.muon1_dxy(); }
const float &muon2_dxy() { return analyzer.muon2_dxy(); }
const float &muon1_diphodxy() { return analyzer.muon1_diphodxy(); }
const float &muon2_diphodxy() { return analyzer.muon2_diphodxy(); }
const float &muon1_dz() { return analyzer.muon1_dz(); }
const float &muon2_dz() { return analyzer.muon2_dz(); }
const float &muon1_diphodz() { return analyzer.muon1_diphodz(); }
const float &muon2_diphodz() { return analyzer.muon2_diphodz(); }
const float &muon1_pxHits() { return analyzer.muon1_pxHits(); }
const float &muon2_pxHits() { return analyzer.muon2_pxHits(); }
const float &muon1_tkLayers() { return analyzer.muon1_tkLayers(); }
const float &muon2_tkLayers() { return analyzer.muon2_tkLayers(); }
const float &muon1_PassTight() { return analyzer.muon1_PassTight(); }
const float &muon2_PassTight() { return analyzer.muon2_PassTight(); }
const float &muon1_dPhiMET() { return analyzer.muon1_dPhiMET(); }
const float &muon2_dPhiMET() { return analyzer.muon2_dPhiMET(); }
const float &n_fwdjets() { return analyzer.n_fwdjets(); }
const float &fwdjet1_pt() { return analyzer.fwdjet1_pt(); }
const float &fwdjet2_pt() { return analyzer.fwdjet2_pt(); }
const float &fwdjet3_pt() { return analyzer.fwdjet3_pt(); }
const float &fwdjet1_eta() { return analyzer.fwdjet1_eta(); }
const float &fwdjet2_eta() { return analyzer.fwdjet2_eta(); }
const float &fwdjet3_eta() { return analyzer.fwdjet3_eta(); }
const float &fwdjet4_eta() { return analyzer.fwdjet4_eta(); }
const float &fwdjet5_eta() { return analyzer.fwdjet5_eta(); }
const float &fwdjet6_eta() { return analyzer.fwdjet6_eta(); }
const float &fwdjet7_eta() { return analyzer.fwdjet7_eta(); }
const float &fwdjet8_eta() { return analyzer.fwdjet8_eta(); }
const float &fwdjet9_eta() { return analyzer.fwdjet9_eta(); }
const float &fwdjet1_phi() { return analyzer.fwdjet1_phi(); }
const float &fwdjet2_phi() { return analyzer.fwdjet2_phi(); }
const float &fwdjet3_phi() { return analyzer.fwdjet3_phi(); }
const float &fwdjet1_e() { return analyzer.fwdjet1_e(); }
const float &fwdjet2_e() { return analyzer.fwdjet2_e(); }
const float &fwdjet3_e() { return analyzer.fwdjet3_e(); }
const float &fwdjet1_discr() { return analyzer.fwdjet1_discr(); }
const float &n_M_bjets() { return analyzer.n_M_bjets(); }
const float &n_L_bjets() { return analyzer.n_L_bjets(); }
const float &n_T_bjets() { return analyzer.n_T_bjets(); }
const float &n_bjets() { return analyzer.n_bjets(); }
const float &bjet1_pt() { return analyzer.bjet1_pt(); }
const float &bjet2_pt() { return analyzer.bjet2_pt(); }
const float &bjet3_pt() { return analyzer.bjet3_pt(); }
const float &bjet1_eta() { return analyzer.bjet1_eta(); }
const float &bjet2_eta() { return analyzer.bjet2_eta(); }
const float &bjet3_eta() { return analyzer.bjet3_eta(); }
const float &bjet1_phi() { return analyzer.bjet1_phi(); }
const float &bjet2_phi() { return analyzer.bjet2_phi(); }
const float &bjet3_phi() { return analyzer.bjet3_phi(); }
const float &bjet1_e() { return analyzer.bjet1_e(); }
const float &bjet2_e() { return analyzer.bjet2_e(); }
const float &bjet3_e() { return analyzer.bjet3_e(); }
const float &bjet1_discr() { return analyzer.bjet1_discr(); }
const float &bjet2_discr() { return analyzer.bjet2_discr(); }
const float &bjet3_discr() { return analyzer.bjet3_discr(); }
const float &bjet4_discr() { return analyzer.bjet4_discr(); }
const float &n_jets() { return analyzer.n_jets(); }
const float &jet1_pt() { return analyzer.jet1_pt(); }
const float &jet2_pt() { return analyzer.jet2_pt(); }
const float &jet3_pt() { return analyzer.jet3_pt(); }
const float &jet4_pt() { return analyzer.jet4_pt(); }
const float &jet5_pt() { return analyzer.jet5_pt(); }
const float &jet6_pt() { return analyzer.jet6_pt(); }
const float &jet7_pt() { return analyzer.jet7_pt(); }
const float &jet8_pt() { return analyzer.jet8_pt(); }
const float &jet9_pt() { return analyzer.jet9_pt(); }
const float &jet10_pt() { return analyzer.jet10_pt(); }
const float &jet11_pt() { return analyzer.jet11_pt(); }
const float &jet12_pt() { return analyzer.jet12_pt(); }
const float &jet13_pt() { return analyzer.jet13_pt(); }
const float &jet14_pt() { return analyzer.jet14_pt(); }
const float &jet15_pt() { return analyzer.jet15_pt(); }
const float &jet1_eta() { return analyzer.jet1_eta(); }
const float &jet2_eta() { return analyzer.jet2_eta(); }
const float &jet3_eta() { return analyzer.jet3_eta(); }
const float &jet4_eta() { return analyzer.jet4_eta(); }
const float &jet5_eta() { return analyzer.jet5_eta(); }
const float &jet6_eta() { return analyzer.jet6_eta(); }
const float &jet7_eta() { return analyzer.jet7_eta(); }
const float &jet8_eta() { return analyzer.jet8_eta(); }
const float &jet9_eta() { return analyzer.jet9_eta(); }
const float &jet10_eta() { return analyzer.jet10_eta(); }
const float &jet11_eta() { return analyzer.jet11_eta(); }
const float &jet12_eta() { return analyzer.jet12_eta(); }
const float &jet13_eta() { return analyzer.jet13_eta(); }
const float &jet14_eta() { return analyzer.jet14_eta(); }
const float &jet15_eta() { return analyzer.jet15_eta(); }
const float &jet1_phi() { return analyzer.jet1_phi(); }
const float &jet2_phi() { return analyzer.jet2_phi(); }
const float &jet3_phi() { return analyzer.jet3_phi(); }
const float &jet4_phi() { return analyzer.jet4_phi(); }
const float &jet5_phi() { return analyzer.jet5_phi(); }
const float &jet6_phi() { return analyzer.jet6_phi(); }
const float &jet7_phi() { return analyzer.jet7_phi(); }
const float &jet8_phi() { return analyzer.jet8_phi(); }
const float &jet9_phi() { return analyzer.jet9_phi(); }
const float &jet10_phi() { return analyzer.jet10_phi(); }
const float &jet11_phi() { return analyzer.jet11_phi(); }
const float &jet12_phi() { return analyzer.jet12_phi(); }
const float &jet13_phi() { return analyzer.jet13_phi(); }
const float &jet14_phi() { return analyzer.jet14_phi(); }
const float &jet15_phi() { return analyzer.jet15_phi(); }
const float &jet1_e() { return analyzer.jet1_e(); }
const float &jet2_e() { return analyzer.jet2_e(); }
const float &jet3_e() { return analyzer.jet3_e(); }
const float &jet4_e() { return analyzer.jet4_e(); }
const float &jet5_e() { return analyzer.jet5_e(); }
const float &jet6_e() { return analyzer.jet6_e(); }
const float &jet7_e() { return analyzer.jet7_e(); }
const float &jet8_e() { return analyzer.jet8_e(); }
const float &jet9_e() { return analyzer.jet9_e(); }
const float &jet10_e() { return analyzer.jet10_e(); }
const float &jet11_e() { return analyzer.jet11_e(); }
const float &jet12_e() { return analyzer.jet12_e(); }
const float &jet13_e() { return analyzer.jet13_e(); }
const float &jet14_e() { return analyzer.jet14_e(); }
const float &jet15_e() { return analyzer.jet15_e(); }
const float &jet1_discr() { return analyzer.jet1_discr(); }
const float &jet2_discr() { return analyzer.jet2_discr(); }
const float &jet3_discr() { return analyzer.jet3_discr(); }
const float &jet4_discr() { return analyzer.jet4_discr(); }
const float &jet5_discr() { return analyzer.jet5_discr(); }
const float &jet6_discr() { return analyzer.jet6_discr(); }
const float &jet7_discr() { return analyzer.jet7_discr(); }
const float &jet8_discr() { return analyzer.jet8_discr(); }
const float &jet9_discr() { return analyzer.jet9_discr(); }
const float &jet10_discr() { return analyzer.jet10_discr(); }
const float &jet11_discr() { return analyzer.jet11_discr(); }
const float &jet12_discr() { return analyzer.jet12_discr(); }
const float &jet13_discr() { return analyzer.jet13_discr(); }
const float &jet14_discr() { return analyzer.jet14_discr(); }
const float &jet15_discr() { return analyzer.jet15_discr(); }
const float &recoMET_pt() { return analyzer.recoMET_pt(); }
const float &recoMET_eta() { return analyzer.recoMET_eta(); }
const float &recoMET_phi() { return analyzer.recoMET_phi(); }
const float &recoMET_e() { return analyzer.recoMET_e(); }
const float &solvedMET_pt() { return analyzer.solvedMET_pt(); }
const float &solvedMET_eta() { return analyzer.solvedMET_eta(); }
const float &solvedMET_phi() { return analyzer.solvedMET_phi(); }
const float &solvedMET_e() { return analyzer.solvedMET_e(); }
const float &dr_leadphobjet() { return analyzer.dr_leadphobjet(); }
const float &dr_leptonfwdjet() { return analyzer.dr_leptonfwdjet(); }
const float &top_mt() { return analyzer.top_mt(); }
const float &top_mass() { return analyzer.top_mass(); }
const float &HT() { return analyzer.HT(); }
const float &gen_parton1_pt() { return analyzer.gen_parton1_pt(); }
const float &gen_parton2_pt() { return analyzer.gen_parton2_pt(); }
const float &gen_parton3_pt() { return analyzer.gen_parton3_pt(); }
const float &gen_parton4_pt() { return analyzer.gen_parton4_pt(); }
const float &gen_parton5_pt() { return analyzer.gen_parton5_pt(); }
const float &gen_parton6_pt() { return analyzer.gen_parton6_pt(); }
const float &gen_parton7_pt() { return analyzer.gen_parton7_pt(); }
const float &gen_parton8_pt() { return analyzer.gen_parton8_pt(); }
const float &gen_parton9_pt() { return analyzer.gen_parton9_pt(); }
const float &gen_parton10_pt() { return analyzer.gen_parton10_pt(); }
const float &gen_parton1_eta() { return analyzer.gen_parton1_eta(); }
const float &gen_parton2_eta() { return analyzer.gen_parton2_eta(); }
const float &gen_parton3_eta() { return analyzer.gen_parton3_eta(); }
const float &gen_parton4_eta() { return analyzer.gen_parton4_eta(); }
const float &gen_parton5_eta() { return analyzer.gen_parton5_eta(); }
const float &gen_parton6_eta() { return analyzer.gen_parton6_eta(); }
const float &gen_parton7_eta() { return analyzer.gen_parton7_eta(); }
const float &gen_parton8_eta() { return analyzer.gen_parton8_eta(); }
const float &gen_parton9_eta() { return analyzer.gen_parton9_eta(); }
const float &gen_parton10_eta() { return analyzer.gen_parton10_eta(); }
const float &gen_parton1_phi() { return analyzer.gen_parton1_phi(); }
const float &gen_parton2_phi() { return analyzer.gen_parton2_phi(); }
const float &gen_parton3_phi() { return analyzer.gen_parton3_phi(); }
const float &gen_parton4_phi() { return analyzer.gen_parton4_phi(); }
const float &gen_parton5_phi() { return analyzer.gen_parton5_phi(); }
const float &gen_parton6_phi() { return analyzer.gen_parton6_phi(); }
const float &gen_parton7_phi() { return analyzer.gen_parton7_phi(); }
const float &gen_parton8_phi() { return analyzer.gen_parton8_phi(); }
const float &gen_parton9_phi() { return analyzer.gen_parton9_phi(); }
const float &gen_parton10_phi() { return analyzer.gen_parton10_phi(); }
const float &gen_parton1_mass() { return analyzer.gen_parton1_mass(); }
const float &gen_parton2_mass() { return analyzer.gen_parton2_mass(); }
const float &gen_parton3_mass() { return analyzer.gen_parton3_mass(); }
const float &gen_parton4_mass() { return analyzer.gen_parton4_mass(); }
const float &gen_parton5_mass() { return analyzer.gen_parton5_mass(); }
const float &gen_parton6_mass() { return analyzer.gen_parton6_mass(); }
const float &gen_parton7_mass() { return analyzer.gen_parton7_mass(); }
const float &gen_parton8_mass() { return analyzer.gen_parton8_mass(); }
const float &gen_parton9_mass() { return analyzer.gen_parton9_mass(); }
const float &gen_parton10_mass() { return analyzer.gen_parton10_mass(); }
const float &gen_parton1_pdgId() { return analyzer.gen_parton1_pdgId(); }
const float &gen_parton2_pdgId() { return analyzer.gen_parton2_pdgId(); }
const float &gen_parton3_pdgId() { return analyzer.gen_parton3_pdgId(); }
const float &gen_parton4_pdgId() { return analyzer.gen_parton4_pdgId(); }
const float &gen_parton5_pdgId() { return analyzer.gen_parton5_pdgId(); }
const float &gen_parton6_pdgId() { return analyzer.gen_parton6_pdgId(); }
const float &gen_parton7_pdgId() { return analyzer.gen_parton7_pdgId(); }
const float &gen_parton8_pdgId() { return analyzer.gen_parton8_pdgId(); }
const float &gen_parton9_pdgId() { return analyzer.gen_parton9_pdgId(); }
const float &gen_parton10_pdgId() { return analyzer.gen_parton10_pdgId(); }
const float &gen_parton1_status() { return analyzer.gen_parton1_status(); }
const float &gen_parton2_status() { return analyzer.gen_parton2_status(); }
const float &gen_parton3_status() { return analyzer.gen_parton3_status(); }
const float &gen_parton4_status() { return analyzer.gen_parton4_status(); }
const float &gen_parton5_status() { return analyzer.gen_parton5_status(); }
const float &gen_parton6_status() { return analyzer.gen_parton6_status(); }
const float &gen_parton7_status() { return analyzer.gen_parton7_status(); }
const float &gen_parton8_status() { return analyzer.gen_parton8_status(); }
const float &gen_parton9_status() { return analyzer.gen_parton9_status(); }
const float &gen_parton10_status() { return analyzer.gen_parton10_status(); }
const float &genMatched_jet0_pdgId() { return analyzer.genMatched_jet0_pdgId(); }
const float &genMatched_jet1_pdgId() { return analyzer.genMatched_jet1_pdgId(); }
const float &genMatched_jet2_pdgId() { return analyzer.genMatched_jet2_pdgId(); }
const float &genMatched_jet0_index() { return analyzer.genMatched_jet0_index(); }
const float &genMatched_jet1_index() { return analyzer.genMatched_jet1_index(); }
const float &genMatched_jet2_index() { return analyzer.genMatched_jet2_index(); }
const float &genMatched_jet0_deltaR() { return analyzer.genMatched_jet0_deltaR(); }
const float &genMatched_jet1_deltaR() { return analyzer.genMatched_jet1_deltaR(); }
const float &genMatched_jet2_deltaR() { return analyzer.genMatched_jet2_deltaR(); }
const float &genMET_pt() { return analyzer.genMET_pt(); }
const float &genMET_eta() { return analyzer.genMET_eta(); }
const float &genMET_phi() { return analyzer.genMET_phi(); }
const float &genMET_e() { return analyzer.genMET_e(); }
const float &promptGenMET_pt() { return analyzer.promptGenMET_pt(); }
const float &promptGenMET_eta() { return analyzer.promptGenMET_eta(); }
const float &promptGenMET_phi() { return analyzer.promptGenMET_phi(); }
const float &promptGenMET_e() { return analyzer.promptGenMET_e(); }
const float &genMETTrue_pt() { return analyzer.genMETTrue_pt(); }
const float &genMETTrue_eta() { return analyzer.genMETTrue_eta(); }
const float &genMETTrue_phi() { return analyzer.genMETTrue_phi(); }
const float &genMETTrue_e() { return analyzer.genMETTrue_e(); }
const float &rho() { return analyzer.rho(); }
const int &nvtx() { return analyzer.nvtx(); }
const unsigned long long &event() { return analyzer.event(); }
const unsigned int &lumi() { return analyzer.lumi(); }
const int &processIndex() { return analyzer.processIndex(); }
const unsigned int &run() { return analyzer.run(); }
const float &npu() { return analyzer.npu(); }
const float &puweight() { return analyzer.puweight(); }

}

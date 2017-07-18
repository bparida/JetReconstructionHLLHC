#ifndef JSSTutorial_JSSTutorialJETTOOLSALGO_H
#define JSSTutorial_JSSTutorialJETTOOLSALGO_H


// EDM include(s):
#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODJet/JetAuxContainer.h>

// For the cluster and tracks information
#include "xAODJet/JetConstituentVector.h"
#include "xAODBTagging/BTagging.h"

// for retrieving of topocluster container
#include "xAODCaloEvent/CaloCluster.h"
#include "xAODCaloEvent/CaloClusterContainer.h"

// algorithm wrapper
#include <xAODAnaHelpers/TreeAlgo.h>

#include "JetRec/JetRecTool.h"



// root includes
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TTree.h"
#include <TFile.h>
#include <TLorentzVector.h>

class JSSTutorialJetToolsAlgo : public TreeAlgo
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.

  // allpublic variables are configurable and do not have //!
  // all private and protected variables are not configurable and need //!

public:

  // configuration variables
  std::string m_MyNewVariable;
  std::string m_TreeName;
  

private:

  JetRecTool * m_jetBuilder; //!
  JetRecTool * m_jetTrimmer; //!

  // event counter
  int m_eventCounter; //!
  TH1D *h_EventCounter; //!

  // histograms to save output
  TH1D *h_jet_pt_cluster;//!
  TH1D *h_jet_eta_cluster;//!
  TH1D *h_jet_phi_cluster;//!
  TH1D *h_jet_mass_cluster;//!
  
  TH1D *h_jet_pt_tower;//!
  TH1D *h_jet_eta_tower;//!
  TH1D *h_jet_phi_tower;//!
  TH1D *h_jet_mass_tower;//! 
 
  TH1D *h_jet_pt_coarsetower;//!
  TH1D *h_jet_eta_coarsetower;//!
  TH1D *h_jet_phi_coarsetower;//!
  TH1D *h_jet_mass_coarsetower;//!
 
  //TH1D * h_njet_cont_cluster;//! 
  TH1D * h_njet_cont_cluster_Eta_2_5_pt_20_30;//! 
  TH1D * h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30;//! 
  TH1D * h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_cluster_Eta_3_9_pt_20_30;//!
  TH1D * h_njet_cont_cluster_EtaGT_2_5_pt_20_30;//! 

  TH1D * h_njet_cont_cluster_Eta_2_5_pt_30_40;//! 
  TH1D * h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40;//! 
  TH1D * h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_cluster_Eta_3_9_pt_30_40;//!
  TH1D * h_njet_cont_cluster_EtaGT_2_5_pt_30_40;//!

  //TH1D * h_njet_cont_tower;//!
  TH1D * h_njet_cont_tower_Eta_2_5_pt_20_30;//!  
  TH1D * h_njet_cont_tower_Eta_2_5_3_2_pt_20_30;//! 
  TH1D * h_njet_cont_tower_Eta_3_2_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_tower_Eta_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_tower_EtaGT_2_5_pt_20_30;//! 

  TH1D * h_njet_cont_tower_Eta_2_5_pt_30_40;//!  
  TH1D * h_njet_cont_tower_Eta_2_5_3_2_pt_30_40;//!
  TH1D * h_njet_cont_tower_Eta_3_2_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_tower_Eta_3_9_pt_30_40;//!
  TH1D * h_njet_cont_tower_EtaGT_2_5_pt_30_40;//! 

  //TH1D * h_njet_cont_coarsetower;//! 
  TH1D * h_njet_cont_coarsetower_Eta_2_5_pt_20_30;//!   
  TH1D * h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30;//!  
  TH1D * h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_coarsetower_Eta_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30;//! 

  TH1D * h_njet_cont_coarsetower_Eta_2_5_pt_30_40;//!   
  TH1D * h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40;//!  
  TH1D * h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40;//!  
  TH1D * h_njet_cont_coarsetower_Eta_3_9_pt_30_40;//!  
  TH1D * h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40;//! 


  TH1D * h_jet_pt_EMTowerClusterFine;//!     
  TH1D * h_jet_eta_EMTowerClusterFine;//!    
  TH1D * h_jet_phi_EMTowerClusterFine;//!    
  TH1D * h_jet_mass_EMTowerClusterFine;//!   
  //TH1D * h_njet_cont_EMTowerClusterFine;//! 
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30;//!  


  TH1D * h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40;//!  
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40;//!
  TH1D * h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40;//! 


  TH1D * h_jet_pt_EMTowerTopoClusterFine;//!     
  TH1D * h_jet_eta_EMTowerTopoClusterFine;//!    
  TH1D * h_jet_phi_EMTowerTopoClusterFine;//!    
  TH1D * h_jet_mass_EMTowerTopoClusterFine;//!   
  //TH1D * h_njet_cont_EMTowerTopoClusterFine;//!
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30;//!  


  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40;//!  
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40;//!
  TH1D * h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40;//! 


  TH1D * h_jet_pt_EMTowerClusterCoarse;//!   
  TH1D * h_jet_eta_EMTowerClusterCoarse;//!  
  TH1D * h_jet_phi_EMTowerClusterCoarse;//!  
  TH1D * h_jet_mass_EMTowerClusterCoarse;//! 
  //TH1D * h_njet_cont_EMTowerClusterCoarse;//!
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30;//!  
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30;//! 
 
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40;//!  
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40;//! 
  TH1D * h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40;//! 


  TH1D * h_ratio;//! 

  TH1D *  h_truthmatched;//!
  TH1D *  h_truthtotal;//!

  TH1D *  h_recotruthmatched;//!
  TH1D *  h_recototal;//!
  
  TH1D *  h_truthmatched_2532;//!
  TH1D *  h_truthtotal_2532;//!

  TH1D *  h_truthmatched_3239;//!
  TH1D *  h_truthtotal_3239;//!

  TH1D *  h_truthmatched_39;//!
  TH1D *  h_truthtotal_39;//!





  TH1D *h_jet_jetrec_Ungroomed_pt; //!
  TH1D *h_jet_jetrec_Ungroomed_m; //!
  TH1D *h_jet_jetrec_Ungroomed_d2; //!
  TH1D *h_jet_jetrec_Ungroomed_tau32; //!

  TH1D *h_jet_jetrec_Trimmed_pt; //!
  TH1D *h_jet_jetrec_Trimmed_m; //!
  TH1D *h_jet_jetrec_Trimmed_d2; //!
  TH1D *h_jet_jetrec_Trimmed_tau32; //!

  TH1D *h_jet_jetrec_Pruned_pt; //!
  TH1D *h_jet_jetrec_Pruned_m; //!
  TH1D *h_jet_jetrec_Pruned_d2; //!
  TH1D *h_jet_jetrec_Pruned_tau32; //!

  TH1D *h_jet_jetrec_SoftDrop_pt; //!
  TH1D *h_jet_jetrec_SoftDrop_m; //!
  TH1D *h_jet_jetrec_SoftDrop_d2; //!
  TH1D *h_jet_jetrec_SoftDrop_tau32; //!

  // TTree to save output results
  TTree *outTree;   //!

  double tvar_jet_pt_cluster; //!
  double tvar_jet_eta_cluster; //!
  double tvar_jet_phi_cluster; //!
  double tvar_jet_mass_cluster; //!
  double tvar_njet_const_cluster; //!

  double tvar_jet_pt_tower; //!
  double tvar_jet_eta_tower; //!
  double tvar_jet_phi_tower; //!
  double tvar_jet_mass_tower; //!
  double tvar_njet_const_tower; //!

  double tvar_jet_pt_coarsetower; //!
  double tvar_jet_eta_coarsetower; //!
  double tvar_jet_phi_coarsetower; //!
  double tvar_jet_mass_coarsetower; //!
  double tvar_njet_const_coarsetower; //!



  double tvar_jet_pt; //!
  double tvar_jet_eta; //!
  double tvar_jet_phi; //!
  double tvar_jet_mass; //!

  double tvar_jet_Ungroomed_pt; //!
  double tvar_jet_Ungroomed_m; //!
  double tvar_jet_Ungroomed_d2; //!
  double tvar_jet_Ungroomed_tau32; //!
  double tvar_jet_Trimmed_pt; //!
  double tvar_jet_Trimmed_m; //!
  double tvar_jet_Trimmed_d2; //!
  double tvar_jet_Trimmed_tau32; //!
  double tvar_jet_Pruned_pt; //!
  double tvar_jet_Pruned_m; //!
  double tvar_jet_Pruned_d2; //!
  double tvar_jet_Pruned_tau32; //!
  double tvar_jet_SoftDrop_pt; //!
  double tvar_jet_SoftDrop_m; //!
  double tvar_jet_SoftDrop_d2; //!
  double tvar_jet_SoftDrop_tau32; //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

  // Subjet Calibration
  JetCalibrationTool* m_jetCalibration_subjet; //!

//FUNCTION DECLARATIONS
public:

  // this is a standard constructor
  JSSTutorialJetToolsAlgo ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(JSSTutorialJetToolsAlgo, 1);
};

#endif

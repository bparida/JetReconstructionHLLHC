/// EL include(s):
#include <EventLoop/Job.h>
#include <EventLoop/Worker.h>
#include <EventLoop/OutputStream.h>

// EDM include(s):
#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>


// for event count
#include "xAODCutFlow/CutBookkeeper.h"
#include "xAODCutFlow/CutBookkeeperContainer.h"

#include "JetRec/JetRecTool.h"
#include "JetRec/PseudoJetGetter.h"
#include "JetRec/JetFromPseudojet.h"
#include "JetRec/JetFinder.h"
#include "JetCalibTools/JetCalibrationTool.h"

#include "JetSubStructureMomentTools/EnergyCorrelatorTool.h"
#include "JetSubStructureMomentTools/EnergyCorrelatorRatiosTool.h"
#include "JetSubStructureMomentTools/NSubjettinessTool.h"
#include "JetSubStructureMomentTools/NSubjettinessRatiosTool.h"
#include "JetRec/JetFilterTool.h"
#include "JetRec/JetTrimmer.h"
#include "JetRec/JetPseudojetRetriever.h"

#include <xAODAnaHelpers/HelperFunctions.h>
#include <xAODAnaHelpers/tools/ReturnCheck.h>
#include <JSSTutorial/JSSTutorialJetToolsAlgo.h>

// c++ include(s)
//#include <stdexcept>

// this is needed to distribute the algorithm to the workers
ClassImp(JSSTutorialJetToolsAlgo)

/// This macro simplify the StatusCode checking
#define SC_CHECK( exp ) RETURN_CHECK("JSSTutorialJetToolsAlgo", exp , "" )
//#define SC_CHECK( exp ) { EL::StatusCode sc= (EL::StatusCode) exp; if(sc==EL::StatusCode::FAILURE) {s//td::cout<< "Config  ERROR   StatusCode failure. "<< std::endl; return sc;}  }



JSSTutorialJetToolsAlgo :: JSSTutorialJetToolsAlgo ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
  msg().setName( "JSSTutorialJetToolsAlgo" );

  ATH_MSG_INFO( "Calling constructor");

  m_MyNewVariable = "";
  m_TreeName = "";

}

EL::StatusCode JSSTutorialJetToolsAlgo :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  job.useXAOD();
  xAOD::Init( "JSSTutorialJetToolsAlgo" ).ignore(); // call before opening first file

  EL::OutputStream outForTree("tree_jetrec");
  job.outputAdd (outForTree);

  return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  ATH_MSG_INFO( "Calling histInitialize");

  std::cout<<"Printing the observable you loaded in (m_MyNewVariable) : "<<m_MyNewVariable<<std::endl;

  // Number of events
  h_EventCounter = new TH1D("h_EventCounter","h_EventCounter",10,0,10);
  wk()->addOutput (h_EventCounter);

  //////////////////////////
  // Histograms
  //////////////////////////
/* 
  h_jet_pt_cluster                = new TH1D("h_jet_pt_cluster",   "h_jet_pt_cluster",100,0,100);
  h_jet_eta_cluster               = new TH1D("h_jet_eta_cluster",   "h_jet_eta_cluster",100,-5.0,5.0);
  h_jet_phi_cluster               = new TH1D("h_jet_phi_cluster",   "h_jet_phi_cluster",100,-5.0,5.0);
  h_jet_mass_cluster              = new TH1D("h_jet_mass_cluster",   "h_jet_mass_cluster",100,0,100);
  //h_njet_cont_cluster             = new TH1D("h_njet_cont_cluster",   "h_njet_cont_cluster",100,0,100);
  h_njet_cont_cluster_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_cluster_Eta_2_5_pt_20_30",   "h_njet_cont_cluster_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_cluster_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_cluster_Eta_3_9_pt_20_30",   "h_njet_cont_cluster_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_cluster_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_cluster_EtaGT_2_5_pt_20_30",   "h_njet_cont_cluster_EtaGT_2_5_pt_20_30",100,0,100);

  h_njet_cont_cluster_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_cluster_Eta_2_5_pt_30_40",   "h_njet_cont_cluster_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_cluster_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_cluster_Eta_3_9_pt_30_40",   "h_njet_cont_cluster_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_cluster_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_cluster_EtaGT_2_5_pt_30_40",   "h_njet_cont_cluster_EtaGT_2_5_pt_30_40",100,0,100);
*/

/*
  h_jet_pt_tower                = new TH1D("h_jet_pt_tower",   "h_jet_pt_tower",100,0,100);
  h_jet_eta_tower               = new TH1D("h_jet_eta_tower",   "h_jet_eta_tower",100,-5.0,5.0);
  h_jet_phi_tower               = new TH1D("h_jet_phi_tower",   "h_jet_phi_tower",100,-5.0,5.0);
  h_jet_mass_tower              = new TH1D("h_jet_mass_tower",   "h_jet_mass_tower",100,0,100);
  //h_njet_cont_tower             = new TH1D("h_njet_cont_tower",   "h_njet_cont_tower",100,0,100);
  h_njet_cont_tower_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_tower_Eta_2_5_pt_20_30",   "h_njet_cont_tower_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_tower_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_tower_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_tower_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_tower_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_tower_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_tower_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_tower_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_tower_Eta_3_9_pt_20_30",   "h_njet_cont_tower_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_tower_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_tower_EtaGT_2_5_pt_20_30",   "h_njet_cont_tower_EtaGT_2_5_pt_20_30",100,0,100);

  h_njet_cont_tower_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_tower_Eta_2_5_pt_30_40",   "h_njet_cont_tower_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_tower_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_tower_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_tower_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_tower_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_tower_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_tower_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_tower_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_tower_Eta_3_9_pt_30_40",   "h_njet_cont_tower_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_tower_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_tower_EtaGT_2_5_pt_30_40",   "h_njet_cont_tower_EtaGT_2_5_pt_30_40",100,0,100);
*/

/*

  h_jet_pt_coarsetower                = new TH1D("h_jet_pt_coarsetower",   "h_jet_pt_coarsetower",100,0,100);
  h_jet_eta_coarsetower               = new TH1D("h_jet_eta_coarsetower",   "h_jet_eta_coarsetower",100,-5.0,5.0);
  h_jet_phi_coarsetower               = new TH1D("h_jet_phi_coarsetower",   "h_jet_phi_coarsetower",100,-5.0,5.0);
  h_jet_mass_coarsetower              = new TH1D("h_jet_mass_coarsetower",   "h_jet_mass_coarsetower",100,0,100);
  //h_njet_cont_coarsetower             = new TH1D("h_njet_cont_coarsetower",   "h_njet_cont_coarsetower",100,0,100);
  h_njet_cont_coarsetower_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_coarsetower_Eta_2_5_pt_20_30",   "h_njet_cont_coarsetower_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_coarsetower_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_coarsetower_Eta_3_9_pt_20_30",   "h_njet_cont_coarsetower_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30",   "h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30",100,0,100);


  h_njet_cont_coarsetower_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_coarsetower_Eta_2_5_pt_30_40",   "h_njet_cont_coarsetower_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_coarsetower_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_coarsetower_Eta_3_9_pt_30_40",   "h_njet_cont_coarsetower_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40",   "h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40",100,0,100);
*/
 /*
  h_jet_pt_EMTowerClusterFine                = new TH1D("h_jet_pt_EMTowerClusterFine",   "h_jet_pt_EMTowerClusterFine",100,0,100);
  h_jet_eta_EMTowerClusterFine               = new TH1D("h_jet_eta_EMTowerClusterFine",   "h_jet_eta_EMTowerClusterFine",100,-5.0,5.0);
  h_jet_phi_EMTowerClusterFine               = new TH1D("h_jet_phi_EMTowerClusterFine",   "h_jet_phi_EMTowerClusterFine",100,-5.0,5.0);
  h_jet_mass_EMTowerClusterFine              = new TH1D("h_jet_mass_EMTowerClusterFine",   "h_jet_mass_EMTowerClusterFine",100,0,100);
  //h_njet_cont_EMTowerClusterFine             = new TH1D("h_njet_cont_EMTowerClusterFine",   "h_njet_cont_EMTowerClusterFine",100,0,100);
 
  h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30",   "h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30",   "h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30",   "h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30",100,0,100);


  h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40",   "h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40",   "h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40",   "h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40",100,0,100);
*/

/*
  h_jet_pt_EMTowerTopoClusterFine                = new TH1D("h_jet_pt_EMTowerTopoClusterFine",   "h_jet_pt_EMTowerTopoClusterFine",100,0,100);
  h_jet_eta_EMTowerTopoClusterFine               = new TH1D("h_jet_eta_EMTowerTopoClusterFine",   "h_jet_eta_EMTowerTopoClusterFine",100,-5.0,5.0);
  h_jet_phi_EMTowerTopoClusterFine               = new TH1D("h_jet_phi_EMTowerTopoClusterFine",   "h_jet_phi_EMTowerTopoClusterFine",100,-5.0,5.0);
  h_jet_mass_EMTowerTopoClusterFine              = new TH1D("h_jet_mass_EMTowerTopoClusterFine",   "h_jet_mass_EMTowerTopoClusterFine",100,0,100);
  //h_njet_cont_EMTowerTopoClusterFine             = new TH1D("h_njet_cont_EMTowerTopoClusterFine",   "h_njet_cont_EMTowerTopoClusterFine",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30",   "h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30",   "h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30",   "h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30",100,0,100);


  h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40",   "h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40",   "h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40",   "h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40",100,0,100);
*/

  h_jet_pt_EMTowerClusterCoarse              = new TH1D("h_jet_pt_EMTowerClusterCoarse",   "h_jet_pt_EMTowerClusterCoarse",100,0,100);
  h_jet_eta_EMTowerClusterCoarse             = new TH1D("h_jet_eta_EMTowerClusterCoarse",   "h_jet_eta_EMTowerClusterCoarse",100,-5.0,5.0);
  h_jet_phi_EMTowerClusterCoarse             = new TH1D("h_jet_phi_EMTowerClusterCoarse",   "h_jet_phi_EMTowerClusterCoarse",100,-5.0,5.0);
  h_jet_mass_EMTowerClusterCoarse            = new TH1D("h_jet_mass_EMTowerClusterCoarse",   "h_jet_mass_EMTowerClusterCoarse",100,0,100);
  //h_njet_cont_EMTowerClusterCoarse           = new TH1D("h_njet_cont_EMTowerClusterCoarse",   "h_njet_cont_EMTowerClusterCoarse",100,0,100);
 
  h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30  = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30",   "h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30",   "h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30",   "h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30",   "h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30 = new TH1D("h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30",   "h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30",100,0,100);
 
  h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40  = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40",   "h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40",   "h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40",   "h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40",   "h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40",100,0,100);
  h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40 = new TH1D("h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40",   "h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40",100,0,100);




  h_truthtotal                = new TH1D("h_truthtotal",   "h_truthtotal",25,0,200);
  h_truthmatched              = new TH1D("h_truthmatched",   "h_truthmatched",25,0,200); 

  h_truthtotal_2532           = new TH1D("h_truthtotal_2532",   "h_truthtotal_2532",25,0,200);
  h_truthmatched_2532         = new TH1D("h_truthmatched_2532",   "h_truthmatched_2532",25,0,200); 

  h_truthtotal_3239           = new TH1D("h_truthtotal_3239",   "h_truthtotal_3239",25,0,200);
  h_truthmatched_3239         = new TH1D("h_truthmatched_3239",   "h_truthmatched_3239",25,0,200); 

  h_truthtotal_39             = new TH1D("h_truthtotal_39",   "h_truthtotal_39",25,0,200);
  h_truthmatched_39           = new TH1D("h_truthmatched_39",   "h_truthmatched_39",25,0,200); 

  h_ratio                = new TH1D("h_ratio",   "h_ratio",25,-2.5, 2.5);

 
  // Add them so they automatically appear in output file
/*
  wk()->addOutput (h_jet_pt_cluster);
  wk()->addOutput (h_jet_eta_cluster);
  wk()->addOutput (h_jet_phi_cluster);
  wk()->addOutput (h_jet_mass_cluster);
  //wk()->addOutput (h_njet_cont_cluster);
  wk()->addOutput (h_njet_cont_cluster_Eta_2_5_pt_20_30); 
  wk()->addOutput (h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_cluster_Eta_3_9_pt_20_30); 

  wk()->addOutput (h_njet_cont_cluster_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_cluster_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_cluster_EtaGT_2_5_pt_20_30);
  wk()->addOutput (h_njet_cont_cluster_EtaGT_2_5_pt_30_40);
*/
/*
  wk()->addOutput (h_jet_pt_tower);
  wk()->addOutput (h_jet_eta_tower);
  wk()->addOutput (h_jet_phi_tower);
  wk()->addOutput (h_jet_mass_tower);
//  wk()->addOutput (h_njet_cont_tower);
  wk()->addOutput (h_njet_cont_tower_Eta_2_5_pt_20_30); 
  wk()->addOutput (h_njet_cont_tower_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_tower_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_tower_Eta_3_9_pt_20_30); 

  wk()->addOutput (h_njet_cont_tower_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_tower_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_tower_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_tower_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_tower_EtaGT_2_5_pt_20_30);
  wk()->addOutput (h_njet_cont_tower_EtaGT_2_5_pt_30_40);
*/
  

/*

  wk()->addOutput (h_jet_pt_coarsetower);
  wk()->addOutput (h_jet_eta_coarsetower);
  wk()->addOutput (h_jet_phi_coarsetower);
  wk()->addOutput (h_jet_mass_coarsetower);
 // wk()->addOutput (h_njet_cont_coarsetower);
  wk()->addOutput (h_njet_cont_coarsetower_Eta_2_5_pt_20_30); 
  wk()->addOutput (h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_coarsetower_Eta_3_9_pt_20_30); 

  wk()->addOutput (h_njet_cont_coarsetower_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_coarsetower_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30);
  wk()->addOutput (h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40);
*/

/*
  wk()->addOutput (h_jet_pt_EMTowerClusterFine);
  wk()->addOutput (h_jet_eta_EMTowerClusterFine);
  wk()->addOutput (h_jet_phi_EMTowerClusterFine);
  wk()->addOutput (h_jet_mass_EMTowerClusterFine);
  //wk()->addOutput (h_njet_cont_EMTowerClusterFine);

  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30); 


  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40); 
*/

/*
  wk()->addOutput (h_jet_pt_EMTowerTopoClusterFine);
  wk()->addOutput (h_jet_eta_EMTowerTopoClusterFine);
  wk()->addOutput (h_jet_phi_EMTowerTopoClusterFine);
  wk()->addOutput (h_jet_mass_EMTowerTopoClusterFine);
  //wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine);
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30); 


  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40); 
 */


  wk()->addOutput (h_jet_pt_EMTowerClusterCoarse);
  wk()->addOutput (h_jet_eta_EMTowerClusterCoarse);
  wk()->addOutput (h_jet_phi_EMTowerClusterCoarse);
  wk()->addOutput (h_jet_mass_EMTowerClusterCoarse);
  //wk()->addOutput (h_njet_cont_EMTowerClusterCoarse);
  
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30);  
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30); 
 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40);  
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40); 
  wk()->addOutput (h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40); 


   wk()->addOutput (h_ratio);
   wk()->addOutput (h_truthtotal);
   wk()->addOutput (h_truthmatched);

   wk()->addOutput (h_truthtotal_2532);          
   wk()->addOutput (h_truthmatched_2532);        

   wk()->addOutput (h_truthtotal_3239);          
   wk()->addOutput (h_truthmatched_3239);         

   wk()->addOutput (h_truthtotal_39);             
   wk()->addOutput (h_truthmatched_39);           

  
  //////////////////////////
  // Tree
  // You need to do this process to link the tree to the output
  //////////////////////////
  //std::cout<<"Trying to initialize tree stuff"<<std::endl;
  // get the file we created already
  // get the file we created already
  TFile* treeFile = wk()->getOutputFile ("tree_jetrec");
  treeFile->mkdir("TreeDirectory");
  treeFile->cd("TreeDirectory");

  outTree = new TTree(m_TreeName.c_str(),m_TreeName.c_str());
/*
  outTree->Branch("tvar_jet_pt_cluster",    &tvar_jet_pt_cluster);
  outTree->Branch("tvar_jet_eta_cluster",    &tvar_jet_eta_cluster);
  outTree->Branch("tvar_jet_phi_cluster",    &tvar_jet_phi_cluster);
  outTree->Branch("tvar_jet_mass_cluster",    &tvar_jet_mass_cluster);
  outTree->Branch("tvar_njet_const_cluster",    &tvar_njet_const_cluster);
*/
/*
  outTree->Branch("tvar_jet_pt_tower",    &tvar_jet_pt_tower);
  outTree->Branch("tvar_jet_eta_tower",    &tvar_jet_eta_tower);
  outTree->Branch("tvar_jet_phi_tower",    &tvar_jet_phi_tower);
  outTree->Branch("tvar_jet_mass_tower",    &tvar_jet_mass_tower);
  outTree->Branch("tvar_njet_const_tower",    &tvar_njet_const_tower);
*/
/*
  outTree->Branch("tvar_jet_pt_coarsetower",    &tvar_jet_pt_coarsetower);
  outTree->Branch("tvar_jet_eta_coarsetower",    &tvar_jet_eta_coarsetower);
  outTree->Branch("tvar_jet_phi_coarsetower",    &tvar_jet_phi_coarsetower);
  outTree->Branch("tvar_jet_mass_coarsetower",    &tvar_jet_mass_coarsetower);
  outTree->Branch("tvar_njet_const_coarsetower",    &tvar_njet_const_coarsetower);
*/
  //outTree->Branch("tvar_jet_Trimmed_pt",      &tvar_jet_Trimmed_pt);
  //add the TTree to the output
  outTree->SetDirectory( treeFile->GetDirectory("TreeDirectory") );




  // Here we configure the jet tools to reproduce what is done in JSSTutorialAlgo
  
  // *********************************************************
  // Step 1 configure input building.
  // PseudoJetGetter is the tool translating xAOD inputs into fastjet
  // there can be several of them (when doing ghost-association) so we use
  // a 'ToolHandleArray' rather than just a 'ToolHandle'

  ToolHandleArray<IPseudoJetGetter> getterArray;
  //ToolHandleArray<IPseudoJetGetter> getterArray_EM_tower;
  // Create a PseudoJet builder.
  //cout << "Creating pseudojet builder." << endl;


  PseudoJetGetter* lcgetter = new PseudoJetGetter("lcget");
  //SC_CHECK(lcgetter->setProperty("InputContainer", "CaloCalTopoClusters"));
  //SC_CHECK(lcgetter->setProperty("InputContainer", "LCWTowerTopoClusterFine"));
  //SC_CHECK(lcgetter->setProperty("InputContainer", "LCWTowerTopoClusterCoarse"));
  //SC_CHECK(lcgetter->setProperty("OutputContainer", "PseudoJetLCTopo"));
  //SC_CHECK(lcgetter->setProperty("Label", "LCTopo"));

  
  //SC_CHECK(lcgetter->setProperty("InputContainer", "EMTowerClusterFine"));
  SC_CHECK(lcgetter->setProperty("InputContainer", "EMTowerClusterCoarse"));
  SC_CHECK(lcgetter->setProperty("OutputContainer", "PseudoJetEMTopo"));
  SC_CHECK(lcgetter->setProperty("Label", "EMTopo"));
  SC_CHECK(lcgetter->setProperty("SkipNegativeEnergy", true));
  SC_CHECK(lcgetter->setProperty("GhostScale", 0.0));
  SC_CHECK(lcgetter->initialize()); // IMPORTANT !! 
  getterArray.push_back( ToolHandle<IPseudoJetGetter>(lcgetter) );

/* 
  //Getting EMTowerTopoClusterFine  from LCWTowerTopoClusterFine 
  PseudoJetGetter* lcgetter_EM_TW = new PseudoJetGetter("lcget_EM_TW");
  SC_CHECK(lcgetter_EM_TW->setProperty("InputContainer", "LCWTowerTopoClusterFine"));
  SC_CHECK(lcgetter_EM_TW->setProperty("OutputContainer", "PseudoJetLCTopo_EM_TW"));
  SC_CHECK(lcgetter_EM_TW->setProperty("Label", "EMTopo"));
  SC_CHECK(lcgetter_EM_TW->setProperty("SkipNegativeEnergy", true));
  SC_CHECK(lcgetter_EM_TW->setProperty("GhostScale", 0.0));
  SC_CHECK(lcgetter_EM_TW->initialize());
  //getterArray.push_back( ToolHandle<IPseudoJetGetter>(lcgetter_EM_TW));
  getterArray_EM_tower.push_back( ToolHandle<IPseudoJetGetter>(lcgetter_EM_TW));
*/

  // *********************************************************
  // Step 2. Configure Jet Finder
  // JetFinder is the tool calling fastjet. We configure it with the relevant parameters

  // Technically we need this tool to translate fastjet to xAOD::Jet
  JetFromPseudojet* jetFromPJ = new JetFromPseudojet("jetbuild");
  std::vector<std::string> areatts = {"ActiveArea", "ActiveAreaFourVector"};
  jetFromPJ->setProperty("Attributes", areatts);
  //  jetFromPJ->msg().setLevel(MSG::ERROR);
  SC_CHECK(jetFromPJ->initialize());

  // JetFinder 
  //cout << "Creating jet finder." << endl;
  JetFinder* finder = new JetFinder("AntiKt4Finder");
  //ToolStore::put(finder);
  SC_CHECK(finder->setProperty("JetAlgorithm", "AntiKt"));
  SC_CHECK(finder->setProperty("JetRadius", 0.4));
  SC_CHECK(finder->setProperty("PtMin", 0)); // unit is MeV
  SC_CHECK(finder->setProperty("GhostArea", 0.01)); // if non-null will run ActiveArea calculation
  SC_CHECK(finder->setProperty("RandomOption", 1));
  SC_CHECK(finder->setProperty("JetBuilder", ToolHandle<IJetFromPseudojet>(jetFromPJ))); // associate

  finder->msg().setLevel(MSG::INFO);
  SC_CHECK(finder->initialize());


  // *********************************************************
  // Finally put everithing together :

  //cout << "Creating jetrec tool." << endl;
  m_jetBuilder = new JetRecTool("jetbuilder");
  //SC_CHECK(m_jetBuilder->setProperty("OutputContainer", "AntiKt10LCTopoJets2"));
  SC_CHECK(m_jetBuilder->setProperty("OutputContainer", "AntiKt4LCTopoJets2"));
  SC_CHECK(m_jetBuilder->setProperty("PseudoJetGetters", getterArray));
  //SC_CHECK(m_jetBuilder->setProperty("PseudoJetGetters", getterArray_EM_tower));
  SC_CHECK(m_jetBuilder->setProperty("JetFinder", ToolHandle<IJetFinder>(finder)));
 //// SC_CHECK(m_jetBuilder->setProperty("JetModifiers", modArray));

  m_jetBuilder->msg().setLevel(MSG::DEBUG);
  SC_CHECK(m_jetBuilder->initialize());

  return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed


  m_event = wk()->xaodEvent();
  // get the MetaData tree once a new file is opened, with
  TTree *MetaData = dynamic_cast<TTree*>(wk()->inputFile()->Get("MetaData"));
  if (!MetaData) {
    ATH_MSG_ERROR( "MetaData not found! Exiting.");
    return EL::StatusCode::FAILURE;
  }
  MetaData->LoadTree(0);
  //check if file is from a DxAOD
  bool m_isDerivation = false;
 // bool m_isDerivation = !MetaData->GetBranch("StreamAOD");

  if(m_isDerivation ){
    // check for corruption
    const xAOD::CutBookkeeperContainer* incompleteCBC = nullptr;
    if(!m_event->retrieveMetaInput(incompleteCBC, "IncompleteCutBookkeepers").isSuccess()){
      ATH_MSG_WARNING("Failed to retrieve IncompleteCutBookkeepers from MetaData! Exiting.");
      //return EL::StatusCode::FAILURE;
    }
    if ( incompleteCBC->size() != 0 ) {
      ATH_MSG_WARNING("Found incomplete Bookkeepers! Check file for corruption.");
      //return EL::StatusCode::FAILURE;
    }

    // Now, let's find the actual information
    const xAOD::CutBookkeeperContainer* completeCBC = 0;
    if(!m_event->retrieveMetaInput(completeCBC, "CutBookkeepers").isSuccess()){
      ATH_MSG_WARNING("Failed to retrieve CutBookkeepers from MetaData! Exiting.");
      //return EL::StatusCode::FAILURE;
    }
    // Now, let's actually find the right one that contains all the needed info...
    const xAOD::CutBookkeeper* allEventsCBK = 0;
    int maxCycle = -1;
    for (const auto& cbk: *completeCBC) {
      if (cbk->cycle() > maxCycle && cbk->name() == "AllExecutedEvents" && cbk->inputStream() == "StreamAOD") {
        allEventsCBK = cbk;
        maxCycle = cbk->cycle();
      }
    }
    uint64_t nEventsProcessed  = allEventsCBK->nAcceptedEvents();
    double sumOfWeights        = allEventsCBK->sumOfEventWeights();
    double sumOfWeightsSquared = allEventsCBK->sumOfEventWeightsSquared();

    h_EventCounter->Fill(0.0,(int)nEventsProcessed);
    h_EventCounter->Fill(1.0,sumOfWeights);
    h_EventCounter->Fill(2.0,sumOfWeightsSquared);
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode JSSTutorialJetToolsAlgo :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.

  return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the outputif you have no
  // input events.

  ATH_MSG_INFO( m_name.c_str());
  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  // count number of events
  m_eventCounter = 0;

  ATH_MSG_INFO( "JSSTutorialJetToolsAlgo Interface succesfully initialized!" );
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode JSSTutorialJetToolsAlgo :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  if ( m_debug ) { ATH_MSG_INFO( "Executing JSSTutorialJetToolsAlgo..."); }

  if ( (m_eventCounter % 5000) == 0 ) {
    ATH_MSG_INFO( m_eventCounter);
  }

  ++m_eventCounter;

  // Run jet building 
  int ret = m_jetBuilder->execute();
  std::cout << "  executed JetBuilder "<< ret << std::endl;
  // Run jet trimming 
  ////ret = m_jetTrimmer->execute();
  ////std::cout << "  executed jet trimmer "<< ret << std::endl;

  // Both jet containers are now availabe in the event store.
  // Let's retrieve them

 //// const xAOD::JetContainer* ungroomedJets;
 //// RETURN_CHECK("JSSTutorialAlgo::execute()", HelperFunctions::retrieve(ungroomedJets, "AntiKt10LCTopoJets2", m_event, m_store,  m_verbose), "");
 
  const xAOD::JetContainer* Jets;
  RETURN_CHECK("JSSTutorialAlgo::execute()", HelperFunctions::retrieve(Jets, "AntiKt4LCTopoJets2", m_event, m_store,  m_verbose), "");

  //const xAOD::JetContainer* JetsTruth;
  //RETURN_CHECK("JSSTutorialAlgo::execute()", HelperFunctions::retrieve(JetsTruth, "AntiKt4TruthJets", m_event, m_store,  m_verbose), "");

/*
  for(const xAOD::Jet * jet : * Jets ){
    if ((fabs(jet->eta())>2.5)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){ 
    //get the clusters from the jet
    xAOD::JetConstituentVector AssociatedClusters = jet->getConstituents();
    std::cout << "no of constituents: " << AssociatedClusters.size() << '\n'; 
    // if(jet->pt()<200000.0)
    // continue;
    // NOT necessary since we configured a pt filter in the jet rec sequence above 
     
    std::cout<<"( Jet pT):         "<<jet->pt()<<std::endl;
    std::cout<<"(Jet mass):       "<<jet->m()<<std::endl;
    std::cout<<"(Jet Eta):         "<<jet->eta()<<std::endl;
    std::cout<<"(Jet Phi):         "<<jet->phi()<<std::endl;

    h_jet_pt_cluster   ->Fill(jet->pt()/1000.0);
    h_jet_mass_cluster ->Fill(jet->m()/1000.0);
    h_jet_eta_cluster ->Fill(jet->eta());
    h_jet_phi_cluster ->Fill(jet->phi());
    h_njet_cont_cluster ->Fill(AssociatedClusters.size());


//    h_jet_pt_tower   ->Fill(jet->pt()/1000.0);
//    h_jet_mass_tower ->Fill(jet->m()/1000.0);
//    h_jet_eta_tower ->Fill(jet->eta());
//    h_jet_phi_tower ->Fill(jet->phi());
//    h_njet_cont_tower ->Fill(AssociatedClusters.size());



//    h_jet_pt_coarsetower   ->Fill(jet->pt()/1000.0);
//    h_jet_mass_coarsetower ->Fill(jet->m()/1000.0);
//    h_jet_eta_coarsetower ->Fill(jet->eta());
//    h_jet_phi_coarsetower ->Fill(jet->phi());
//    h_njet_cont_coarsetower ->Fill(AssociatedClusters.size());



//    h_jet_pt_EMTowerClusterFine   ->Fill(jet->pt()/1000.0);
//    h_jet_mass_EMTowerClusterFine ->Fill(jet->m()/1000.0);
//    h_jet_eta_EMTowerClusterFine ->Fill(jet->eta());
//    h_jet_phi_EMTowerClusterFine ->Fill(jet->phi());
//    h_njet_cont_EMTowerClusterFine ->Fill(AssociatedClusters.size());


//    h_jet_pt_EMTowerTopoClusterFine   ->Fill(jet->pt()/1000.0);
//    h_jet_mass_EMTowerTopoClusterFine ->Fill(jet->m()/1000.0);
//    h_jet_eta_EMTowerTopoClusterFine ->Fill(jet->eta());
//    h_jet_phi_EMTowerTopoClusterFine ->Fill(jet->phi());
//    h_njet_cont_EMTowerTopoClusterFine ->Fill(AssociatedClusters.size());



//    h_jet_pt_EMTowerClusterCoarse   ->Fill(jet->pt()/1000.0);
//    h_jet_mass_EMTowerClusterCoarse ->Fill(jet->m()/1000.0);
//    h_jet_eta_EMTowerClusterCoarse ->Fill(jet->eta());
//    h_jet_phi_EMTowerClusterCoarse ->Fill(jet->phi());
//    h_njet_cont_EMTowerClusterCoarse ->Fill(AssociatedClusters.size());



//   tvar_jet_pt_cluster    = jet->pt()/1000.0;
//   tvar_jet_eta_cluster    = jet->eta();
//   tvar_jet_phi_cluster    = jet->phi();
//   tvar_jet_mass_cluster     = jet->m()/1000.0;
//   tvar_njet_const_cluster   = AssociatedClusters.size();
  
//   tvar_jet_pt_tower    = jet->pt()/1000.0;
//   tvar_jet_eta_tower    = jet->eta();
//   tvar_jet_phi_tower    = jet->phi();
//   tvar_jet_mass_tower     = jet->m()/1000.0;
//   tvar_njet_const_tower   = AssociatedClusters.size();

//   tvar_jet_pt_coarsetower    = jet->pt()/1000.0;
// tvar_jet_eta_coarsetower    = jet->eta();
// tvar_jet_phi_coarsetower    = jet->phi();
// tvar_jet_mass_coarsetower     = jet->m()/1000.0;
// tvar_njet_const_coarsetower   = AssociatedClusters.size(); 


}
  }
*/

for(const xAOD::Jet * jet : * Jets ){
    xAOD::JetConstituentVector AssociatedClusters = jet->getConstituents();
    if ((fabs(jet->eta())< 2.5)  && ((jet->pt())>20000.0 && (jet->pt())<30000.0)){ 
    //get the clusters from the jet
    //xAOD::JetConstituentVector AssociatedClusters = jet->getConstituents();
    std::cout << "no of constituents: " << AssociatedClusters.size() << '\n'; 
    // if(jet->pt()<200000.0)
    // continue;
    // NOT necessary since we configured a pt filter in the jet rec sequence above 
     
    std::cout<<"( Jet pT):         "<<jet->pt()<<std::endl;
    std::cout<<"(Jet mass):       "<<jet->m()<<std::endl;
    std::cout<<"(Jet Eta):         "<<jet->eta()<<std::endl;
    std::cout<<"(Jet Phi):         "<<jet->phi()<<std::endl;
  /*
    h_jet_pt_cluster   ->Fill(jet->pt()/1000.0);
    h_jet_mass_cluster ->Fill(jet->m()/1000.0);
    h_jet_eta_cluster ->Fill(jet->eta());
    h_jet_phi_cluster ->Fill(jet->phi());
    h_njet_cont_cluster_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
  */

   /*
    h_jet_pt_tower   ->Fill(jet->pt()/1000.0);
    h_jet_mass_tower ->Fill(jet->m()/1000.0);
    h_jet_eta_tower ->Fill(jet->eta());
    h_jet_phi_tower ->Fill(jet->phi());
    h_njet_cont_tower_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
   */
    /*
    h_jet_pt_coarsetower   ->Fill(jet->pt()/1000.0);
    h_jet_mass_coarsetower ->Fill(jet->m()/1000.0);
    h_jet_eta_coarsetower ->Fill(jet->eta());
    h_jet_phi_coarsetower ->Fill(jet->phi());
    h_njet_cont_coarsetower_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
    */
   /* 
    h_jet_pt_EMTowerClusterFine   ->Fill(jet->pt()/1000.0);
    h_jet_mass_EMTowerClusterFine ->Fill(jet->m()/1000.0);
    h_jet_eta_EMTowerClusterFine ->Fill(jet->eta());
    h_jet_phi_EMTowerClusterFine ->Fill(jet->phi());
    h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
   */

   /*
    h_jet_pt_EMTowerTopoClusterFine   ->Fill(jet->pt()/1000.0);
    h_jet_mass_EMTowerTopoClusterFine ->Fill(jet->m()/1000.0);
    h_jet_eta_EMTowerTopoClusterFine ->Fill(jet->eta());
    h_jet_phi_EMTowerTopoClusterFine ->Fill(jet->phi());
    h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
   */

    h_jet_pt_EMTowerClusterCoarse  ->Fill(jet->pt()/1000.0);
    h_jet_mass_EMTowerClusterCoarse ->Fill(jet->m()/1000.0);
    h_jet_eta_EMTowerClusterCoarse ->Fill(jet->eta());
    h_jet_phi_EMTowerClusterCoarse ->Fill(jet->phi());
    h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_20_30 ->Fill(AssociatedClusters.size());

}
if ((fabs(jet->eta())> 2.5 && fabs(jet->eta())< 3.2)  && ((jet->pt())>20000.0 && (jet->pt())<30000.0)){
//h_njet_cont_cluster_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_20_30 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())> 3.2 && fabs(jet->eta())< 3.9)  && ((jet->pt())>20000.0 && (jet->pt())<30000.0)){
//h_njet_cont_cluster_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())>3.9)  && ((jet->pt())>20000.0 && (jet->pt())<30000.0)){
//h_njet_cont_cluster_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_20_30 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())>2.5)  && ((jet->pt())>20000.0 && (jet->pt())<30000.0)){
//h_njet_cont_cluster_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_20_30 ->Fill(AssociatedClusters.size());
}


if ((fabs(jet->eta())< 2.5)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){
//h_njet_cont_cluster_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())> 2.5 && fabs(jet->eta())< 3.2)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){
//h_njet_cont_cluster_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_2_5_3_2_pt_30_40 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())> 3.2 && fabs(jet->eta())< 3.9)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){
//h_njet_cont_cluster_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_3_2_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())>3.9)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){
//h_njet_cont_cluster_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_Eta_3_9_pt_30_40 ->Fill(AssociatedClusters.size());
}

if ((fabs(jet->eta())>2.5)  && ((jet->pt())>30000.0 && (jet->pt())<40000.0)){
//h_njet_cont_cluster_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_tower_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_coarsetower_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerClusterFine_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
//h_njet_cont_EMTowerTopoClusterFine_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
h_njet_cont_EMTowerClusterCoarse_EtaGT_2_5_pt_30_40 ->Fill(AssociatedClusters.size());
}

}

  const xAOD::JetContainer* JetsTruth;
  RETURN_CHECK("JSSTutorialAlgo::execute()", HelperFunctions::retrieve(JetsTruth, "AntiKt4TruthJets", m_event, m_store,  m_verbose), "");
  for(const xAOD::Jet* jettruth : * JetsTruth){
     if (jettruth->pt() > 30000.0 && fabs(jettruth->eta())< 2.5){//truth jet pt cut
     h_truthtotal->Fill(jettruth->pt()/1000.0);

     std::cout<<std::endl<<"Jet_Pt : "<<jettruth->pt()<<std::endl; 
     std::cout<<std::endl<<"Jet_Eta : "<<jettruth->eta()<<std::endl;
     std::cout<<std::endl<<"Jet_Phi : "<<jettruth->phi()<<std::endl;

    TLorentzVector TruthJet;
    TruthJet.SetPxPyPzE(jettruth->px(),jettruth->py(),jettruth->pz(),jettruth->e());
    double Delta_R=999;
    for(const xAOD::Jet * jet : * Jets ){ //reco loop

    std::cout<<std::endl<<"Reco Jet_Eta : "<<jet->eta()<<std::endl;
    TLorentzVector RecoJet;
    RecoJet.SetPxPyPzE(jet->px(), jet->py(),jet->pz(),jet->e());
   if (TruthJet.DeltaR(RecoJet) < Delta_R ) Delta_R = TruthJet.DeltaR(RecoJet);
    }//reco loop

   if(Delta_R < 0.3){
      h_truthmatched->Fill(jettruth->pt()/1000.0);
    }
    h_ratio->Fill((jettruth->pt()/1000.0)/(jettruth->pt()/1000.0));
   }//truth jet pt cut
}


for(const xAOD::Jet* jettruth : * JetsTruth){
     if (jettruth->pt() > 30000.0 && fabs(jettruth->eta())>2.5 && fabs(jettruth->eta())< 3.2){//truth jet pt cut
     h_truthtotal_2532->Fill(jettruth->pt()/1000.0);

     std::cout<<std::endl<<"Jet_Pt : "<<jettruth->pt()<<std::endl; 
     std::cout<<std::endl<<"Jet_Eta : "<<jettruth->eta()<<std::endl;
     std::cout<<std::endl<<"Jet_Phi : "<<jettruth->phi()<<std::endl;

    TLorentzVector TruthJet;
    TruthJet.SetPxPyPzE(jettruth->px(),jettruth->py(),jettruth->pz(),jettruth->e());
    double Delta_R=999;
    for(const xAOD::Jet * jet : * Jets ){ //reco loop

    std::cout<<std::endl<<"Reco Jet_Eta : "<<jet->eta()<<std::endl;
    TLorentzVector RecoJet;
    RecoJet.SetPxPyPzE(jet->px(), jet->py(),jet->pz(),jet->e());
   if (TruthJet.DeltaR(RecoJet) < Delta_R ) Delta_R = TruthJet.DeltaR(RecoJet);
    }//reco loop

   if(Delta_R < 0.3){
      h_truthmatched_2532->Fill(jettruth->pt()/1000.0);
    }

   }//truth jet pt cut
}

for(const xAOD::Jet* jettruth : * JetsTruth){
     if (jettruth->pt() > 30000.0 && fabs(jettruth->eta())>3.2 && fabs(jettruth->eta())< 3.9){//truth jet pt cut
     h_truthtotal_3239->Fill(jettruth->pt()/1000.0);

     std::cout<<std::endl<<"Jet_Pt : "<<jettruth->pt()<<std::endl; 
     std::cout<<std::endl<<"Jet_Eta : "<<jettruth->eta()<<std::endl;
     std::cout<<std::endl<<"Jet_Phi : "<<jettruth->phi()<<std::endl;

    TLorentzVector TruthJet;
    TruthJet.SetPxPyPzE(jettruth->px(),jettruth->py(),jettruth->pz(),jettruth->e());
    double Delta_R=999;
    for(const xAOD::Jet * jet : * Jets ){ //reco loop

    std::cout<<std::endl<<"Reco Jet_Eta : "<<jet->eta()<<std::endl;
    TLorentzVector RecoJet;
    RecoJet.SetPxPyPzE(jet->px(), jet->py(),jet->pz(),jet->e());
   if (TruthJet.DeltaR(RecoJet) < Delta_R ) Delta_R = TruthJet.DeltaR(RecoJet);
    }//reco loop

   if(Delta_R < 0.3){
      h_truthmatched_3239->Fill(jettruth->pt()/1000.0);
    }

   }//truth jet pt cut
}


for(const xAOD::Jet* jettruth : * JetsTruth){
     if (jettruth->pt() > 30000.0 && fabs(jettruth->eta())>3.9){//truth jet pt cut
     h_truthtotal_39->Fill(jettruth->pt()/1000.0);

     std::cout<<std::endl<<"Jet_Pt : "<<jettruth->pt()<<std::endl; 
     std::cout<<std::endl<<"Jet_Eta : "<<jettruth->eta()<<std::endl;
     std::cout<<std::endl<<"Jet_Phi : "<<jettruth->phi()<<std::endl;

    TLorentzVector TruthJet;
    TruthJet.SetPxPyPzE(jettruth->px(),jettruth->py(),jettruth->pz(),jettruth->e());
    double Delta_R=999;
    for(const xAOD::Jet * jet : * Jets ){ //reco loop

    std::cout<<std::endl<<"Reco Jet_Eta : "<<jet->eta()<<std::endl;
    TLorentzVector RecoJet;
    RecoJet.SetPxPyPzE(jet->px(), jet->py(),jet->pz(),jet->e());
   if (TruthJet.DeltaR(RecoJet) < Delta_R ) Delta_R = TruthJet.DeltaR(RecoJet);
    }//reco loop

   if(Delta_R < 0.3){
      h_truthmatched_39->Fill(jettruth->pt()/1000.0);
    }

   }//truth jet pt cut
}


  //   //////////////////////////////
  //   //Fill the jet as a new entry into the output tree
  //   //////////////////////////////
     outTree->Fill();

     return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.

  return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  ATH_MSG_INFO( "Deleting tool instances...");

  return EL::StatusCode::SUCCESS;

}

EL::StatusCode JSSTutorialJetToolsAlgo :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  return EL::StatusCode::SUCCESS;

}


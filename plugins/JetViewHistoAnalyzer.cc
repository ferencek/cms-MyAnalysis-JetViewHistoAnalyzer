// -*- C++ -*-
//
// Package:    MyAnalysis/JetViewHistoAnalyzer
// Class:      JetViewHistoAnalyzer
// 
/**\class JetViewHistoAnalyzer JetViewHistoAnalyzer.cc MyAnalysis/JetViewHistoAnalyzer/plugins/JetViewHistoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek
//         Created:  Thu, 13 Mar 2014 20:10:46 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "TH1D.h"
#include "TH2D.h"

//
// class declaration
//

class JetViewHistoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit JetViewHistoAnalyzer(const edm::ParameterSet&);
      ~JetViewHistoAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::Service<TFileService> fs;

      const edm::InputTag src_;
      const double        jetPtMin_, jetPtMax_, jetRapMin_, jetRapMax_;
      const int           jetPtNbins_, jetRapNbins_;

      TH1D *h1_Jet1Pt;
      TH1D *h1_Jet2Pt;

      TH1D *h1_Jet1Rap;
      TH1D *h1_Jet2Rap;
      TH1D *h1_JetRapLab;
      TH1D *h1_JetRapCM;

      TH2D *h2_JetRap;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
JetViewHistoAnalyzer::JetViewHistoAnalyzer(const edm::ParameterSet& iConfig) :

  src_(iConfig.getParameter<edm::InputTag>("src")),
  jetPtMin_(iConfig.getParameter<double>("jetPtMin")),
  jetPtMax_(iConfig.getParameter<double>("jetPtMax")),
  jetRapMin_(iConfig.getParameter<double>("jetRapMin")),
  jetRapMax_(iConfig.getParameter<double>("jetRapMax")),
  jetPtNbins_(iConfig.getParameter<int>("jetPtNbins")),
  jetRapNbins_(iConfig.getParameter<int>("jetRapNbins"))

{
   //now do what ever initialization is needed
   h1_Jet1Pt  = fs->make<TH1D>("h1_Jet1Pt",";p_{T,1} [GeV]", jetPtNbins_, jetPtMin_, jetPtMax_);
   h1_Jet2Pt  = fs->make<TH1D>("h1_Jet2Pt",";p_{T,2} [GeV]", jetPtNbins_, jetPtMin_, jetPtMax_);

   h1_Jet1Rap = fs->make<TH1D>("h1_Jet1Rap",";y_{1}", jetRapNbins_, jetRapMin_, jetRapMax_);
   h1_Jet2Rap = fs->make<TH1D>("h1_Jet2Rap",";y_{2}", jetRapNbins_, jetRapMin_, jetRapMax_);
   h1_JetRapLab = fs->make<TH1D>("h1_JetRapLab",";y_{lab}", jetRapNbins_, jetRapMin_, jetRapMax_);
   h1_JetRapCM = fs->make<TH1D>("h1_JetRapCM",";y_{CM}", jetRapNbins_, jetRapMin_, jetRapMax_);

   h2_JetRap = fs->make<TH2D>("h2_JetRap",";y_{lab};y_{CM}", jetRapNbins_, jetRapMin_, jetRapMax_, jetRapNbins_, jetRapMin_, jetRapMax_);
}


JetViewHistoAnalyzer::~JetViewHistoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JetViewHistoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   // get jets
   edm::Handle<edm::View<reco::Jet> > jets;
   iEvent.getByLabel(src_, jets);

   if( jets->size()<2 )
     return;

   h1_Jet1Pt->Fill( jets->at(0).pt() );
   h1_Jet2Pt->Fill( jets->at(1).pt() );

   h1_Jet1Rap->Fill( jets->at(0).rapidity() );
   h1_Jet2Rap->Fill( jets->at(1).rapidity() );

   double y_lab = (jets->at(0).rapidity()+jets->at(1).rapidity())/2.;
   double y_cm = (jets->at(0).rapidity()-jets->at(1).rapidity())/2.;

   h1_JetRapLab->Fill( y_lab );
   h1_JetRapCM->Fill( y_cm );

   h2_JetRap->Fill( y_lab, y_cm );

   return;
}


// ------------ method called once each job just before starting event loop  ------------
void 
JetViewHistoAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetViewHistoAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
JetViewHistoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
JetViewHistoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
JetViewHistoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
JetViewHistoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetViewHistoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetViewHistoAnalyzer);

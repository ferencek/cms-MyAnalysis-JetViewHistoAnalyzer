import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('IOMC.RandomEngine.IOMC_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100000)
)

process.TFileService = cms.Service("TFileService",
   fileName = cms.string('test.root')
)

# Input source
process.source = cms.Source("EmptySource")

process.generator = cms.EDFilter("Pythia8GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    filterEfficiency = cms.untracked.double(1),
    comEnergy = cms.double(8000.0),
    crossSection = cms.untracked.double(1.0),
    maxEventsToPrint = cms.untracked.int32(1),
    #reweightGen = cms.PSet(),       # flat in Pt
    #reweightGenRap = cms.PSet(      # flat in eta
       #yLabSigmaFunc = cms.string("15.44/pow(x,0.0253)-12.56"),
       #yLabPower = cms.double(2.),
       #yCMSigmaFunc = cms.string("5.45/pow(x+64.84,0.34)"),
       #yCMPower = cms.double(2.),
       #pTHatMin = cms.double(15.),
       #pTHatMax = cms.double(3000.)
    #),
    #reweightGenPtHatRap = cms.PSet( # flat in Pt and eta
       #yLabSigmaFunc = cms.string("15.44/pow(x,0.0253)-12.56"),
       #yLabPower = cms.double(2.),
       #yCMSigmaFunc = cms.string("5.45/pow(x+64.84,0.34)"),
       #yCMPower = cms.double(2.),
       #pTHatMin = cms.double(15.),
       #pTHatMax = cms.double(3000.)
    #),

    PythiaParameters = cms.PSet(
        processParameters = cms.vstring(
            'HardQCD:all = on',
            'PartonLevel:ISR = off',
            'PartonLevel:FSR = off',
            'PartonLevel:MPI = off',
            'HadronLevel:all = off',
            'PhaseSpace:pTHatMin = 15.',
            'PhaseSpace:pTHatMax = 300'
        ),
        parameterSets = cms.vstring('processParameters')
    )
)

process.ak2GenJets = process.ak5GenJets.clone(
    jetPtMin = cms.double(15.0),
    rParam = cms.double(0.2)
)

process.printGenParticles = cms.EDAnalyzer("ParticleListDrawer",
     src = cms.InputTag("genParticles"),
     maxEventsToPrint = cms.untracked.int32(3)
)

process.plotJets= cms.EDAnalyzer("JetViewHistoAnalyzer",
    src = cms.InputTag("ak2GenJets"),
    jetPtMin    = cms.double(0.),
    jetPtMax    = cms.double(1100.),
    jetPtNbins  = cms.int32(220),
    jetRapMin   = cms.double(-5.),
    jetRapMax   = cms.double(5.),
    jetRapNbins = cms.int32(100),
)

process.p = cms.Path(
    process.generator
    *process.genParticles
    *process.genParticlesForJets
    *process.ak2GenJets
    *process.printGenParticles
    *process.plotJets
)

process.schedule = cms.Schedule(process.p)

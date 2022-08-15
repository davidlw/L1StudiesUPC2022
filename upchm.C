#include <iostream>

#include "TString.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TFileCollection.h"
#include "THashList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TVector3.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "TDirectory.h"

#include "interface/L1AnalysisL1CaloTowerDataFormat.h"

using namespace std; 

void upchm(const TString& inputList = "filelist.txt")
{
  TH1D* hntrk_HFAnd = new TH1D("hntrk_HFAnd","nTrk",1000,0,1000);
  TH1D* hntrk_HF1And = new TH1D("hntrk_HF1And","nTrk",1000,0,1000);
  TH1D* hntrk_ZDCAnd_HFAnd = new TH1D("hntrk_ZDCAnd_HFAnd","nTrk",1000,0,1000);
  TH1D* hntrk_ZDCAnd_HF1And = new TH1D("hntrk_ZDCAnd_HF1And","nTrk",1000,0,1000);
  TH1D* hntrk_ZDCOr = new TH1D("hntrk_ZDCOr","nTrk",1000,0,1000);

  TH1D* h1_nothf2and = new TH1D("h1_nothf2and","nTrk",1000,0,1000);

  TH2D* hnTrkvsETT = new TH2D("hnTrkvsETT",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsETTHF = new TH2D("hnTrkvsETTHF",";nTrk;ETTHF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF = new TH2D("hnTrkvsHF",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsETTPlus = new TH2D("hnTrkvsETTPlus",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsETTHFPlus = new TH2D("hnTrkvsETTHFPlus",";nTrk;ETTHFPlus",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHFPlus = new TH2D("hnTrkvsHFPlus",";nTrk;HFPlus",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsETTMinus = new TH2D("hnTrkvsETTMinus",";nTrk;ETTMinus",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsETTHFMinus = new TH2D("hnTrkvsETTHFMinus",";nTrk;ETTHFMinus",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHFMinus = new TH2D("hnTrkvsHFMinus",";nTrk;HFMinus",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower = new TH2D("hnTrkvsTower",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hnTrkvsTowerPlus = new TH2D("hnTrkvsTowerPlus",";nTrk;TowerPlus",1000,0,1000,1000,0,1000);
  TH2D* hnTrkvsTowerMinus = new TH2D("hnTrkvsTowerMinus",";nTrk;TowerMinus",1000,0,1000,1000,0,1000);
  TH2D* hETTPlusVsETTMinus_plus = new TH2D("hETTPlusVsETTMinus_plus",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_plus = new TH2D("hTowerPlusVsTowerMinus_plus",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_minus = new TH2D("hETTPlusVsETTMinus_minus",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_minus = new TH2D("hTowerPlusVsETTMinus_minus",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);
  TH2D* hZDCSumPlusVsMinus = new TH2D("hZDCSumPlusVsMinus",";ZDCSumPlus;ZDCSumMinus",1000,0,50000,1000,0,50000);
  TH1D* hZDCSumPlus = new TH1D("hZDCSumPlus",";ZDCSumPlus",1000,0,50000);
  TH1D* hZDCSumMinus = new TH1D("hZDCSumMinus",";ZDCSumMinus",1000,0,50000);

  TH1D* hntrk = new TH1D("hntrk","nTrk",1000,0,1000);

  TH1D* hntrk_ZDCP = new TH1D("hntrk_ZDCP","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCP = new TH2D("hnTrkvsETT_ZDCP",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCP = new TH2D("hnTrkvsHF_ZDCP",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCP = new TH2D("hnTrkvsTower_ZDCP",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCP = new TH2D("hHFPlusVsHFMinus_ZDCP",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCP = new TH2D("hETTPlusVsETTMinus_ZDCP",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCP = new TH2D("hTowerPlusVsTowerMinus_ZDCP",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCM = new TH1D("hntrk_ZDCM","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCM = new TH2D("hnTrkvsETT_ZDCM",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCM = new TH2D("hnTrkvsHF_ZDCM",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCM = new TH2D("hnTrkvsTower_ZDCM",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCM = new TH2D("hHFPlusVsHFMinus_ZDCM",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCM = new TH2D("hETTPlusVsETTMinus_ZDCM",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCM = new TH2D("hTowerPlusVsTowerMinus_ZDCM",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCP_HFAnd = new TH1D("hntrk_ZDCP_HFAnd","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCP_HFAnd = new TH2D("hnTrkvsETT_ZDCP_HFAnd",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCP_HFAnd = new TH2D("hnTrkvsHF_ZDCP_HFAnd",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCP_HFAnd = new TH2D("hnTrkvsTower_ZDCP_HFAnd",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCP_HFAnd = new TH2D("hHFPlusVsHFMinus_ZDCP_HFAnd",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCP_HFAnd = new TH2D("hETTPlusVsETTMinus_ZDCP_HFAnd",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCP_HFAnd = new TH2D("hTowerPlusVsTowerMinus_ZDCP_HFAnd",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCM_HFAnd = new TH1D("hntrk_ZDCM_HFAnd","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCM_HFAnd = new TH2D("hnTrkvsETT_ZDCM_HFAnd",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCM_HFAnd = new TH2D("hnTrkvsHF_ZDCM_HFAnd",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCM_HFAnd = new TH2D("hnTrkvsTower_ZDCM_HFAnd",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCM_HFAnd = new TH2D("hHFPlusVsHFMinus_ZDCM_HFAnd",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCM_HFAnd = new TH2D("hETTPlusVsETTMinus_ZDCM_HFAnd",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCM_HFAnd = new TH2D("hTowerPlusVsTowerMinus_ZDCM_HFAnd",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCP_HF1And = new TH1D("hntrk_ZDCP_HF1And","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCP_HF1And = new TH2D("hnTrkvsETT_ZDCP_HF1And",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCP_HF1And = new TH2D("hnTrkvsHF_ZDCP_HF1And",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCP_HF1And = new TH2D("hnTrkvsTower_ZDCP_HF1And",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCP_HF1And = new TH2D("hHFPlusVsHFMinus_ZDCP_HF1And",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCP_HF1And = new TH2D("hETTPlusVsETTMinus_ZDCP_HF1And",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCP_HF1And = new TH2D("hTowerPlusVsTowerMinus_ZDCP_HF1And",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCM_HF1And = new TH1D("hntrk_ZDCM_HF1And","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCM_HF1And = new TH2D("hnTrkvsETT_ZDCM_HF1And",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCM_HF1And = new TH2D("hnTrkvsHF_ZDCM_HF1And",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCM_HF1And = new TH2D("hnTrkvsTower_ZDCM_HF1And",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCM_HF1And = new TH2D("hHFPlusVsHFMinus_ZDCM_HF1And",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCM_HF1And = new TH2D("hETTPlusVsETTMinus_ZDCM_HF1And",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCM_HF1And = new TH2D("hTowerPlusVsTowerMinus_ZDCM_HF1And",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCP_HFP = new TH1D("hntrk_ZDCP_HFP","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCP_HFP = new TH2D("hnTrkvsETT_ZDCP_HFP",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCP_HFP = new TH2D("hnTrkvsHF_ZDCP_HFP",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCP_HFP = new TH2D("hnTrkvsTower_ZDCP_HFP",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCP_HFP = new TH2D("hHFPlusVsHFMinus_ZDCP_HFP",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCP_HFP = new TH2D("hETTPlusVsETTMinus_ZDCP_HFP",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCP_HFP = new TH2D("hTowerPlusVsTowerMinus_ZDCP_HFP",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCM_HFM = new TH1D("hntrk_ZDCM_HFM","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCM_HFM = new TH2D("hnTrkvsETT_ZDCM_HFM",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCM_HFM = new TH2D("hnTrkvsHF_ZDCM_HFM",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCM_HFM = new TH2D("hnTrkvsTower_ZDCM_HFM",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCM_HFM = new TH2D("hHFPlusVsHFMinus_ZDCM_HFM",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCM_HFM = new TH2D("hETTPlusVsETTMinus_ZDCM_HFM",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCM_HFM = new TH2D("hTowerPlusVsTowerMinus_ZDCM_HFM",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCP_HF1P = new TH1D("hntrk_ZDCP_HF1P","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCP_HF1P = new TH2D("hnTrkvsETT_ZDCP_HF1P",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCP_HF1P = new TH2D("hnTrkvsHF_ZDCP_HF1P",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCP_HF1P = new TH2D("hnTrkvsTower_ZDCP_HF1P",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCP_HF1P = new TH2D("hHFPlusVsHFMinus_ZDCP_HF1P",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCP_HF1P = new TH2D("hETTPlusVsETTMinus_ZDCP_HF1P",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCP_HF1P = new TH2D("hTowerPlusVsTowerMinus_ZDCP_HF1P",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH1D* hntrk_ZDCM_HF1M = new TH1D("hntrk_ZDCM_HF1M","nTrk",1000,0,1000);
  TH2D* hnTrkvsETT_ZDCM_HF1M = new TH2D("hnTrkvsETT_ZDCM_HF1M",";nTrk;ETT",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsHF_ZDCM_HF1M = new TH2D("hnTrkvsHF_ZDCM_HF1M",";nTrk;HF",1000,0,1000,1000,0,500);
  TH2D* hnTrkvsTower_ZDCM_HF1M = new TH2D("hnTrkvsTower_ZDCM_HF1M",";nTrk;Tower",1000,0,1000,1000,0,1000);
  TH2D* hHFPlusVsHFMinus_ZDCM_HF1M = new TH2D("hHFPlusVsHFMinus_ZDCM_HF1M",";HFPlus;HFMinus",1000,0,500,1000,0,500);
  TH2D* hETTPlusVsETTMinus_ZDCM_HF1M = new TH2D("hETTPlusVsETTMinus_ZDCM_HF1M",";ETTPlus;ETTMinus",1000,0,500,1000,0,500);
  TH2D* hTowerPlusVsTowerMinus_ZDCM_HF1M = new TH2D("hTowerPlusVsTowerMinus_ZDCM_HF1M",";TowerPlus;TowerMinus",1000,0,500,1000,0,500);

  TH2D* hntrkVsGap_g = new TH2D("hntrkVsGap_g",";gap_g;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hntrkVsGap_n = new TH2D("hntrkVsGap_n",";gap_n;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hGap_nvsg = new TH2D("hGap_nvsg",";gap_g;gap_n",55,0,5.5,55,0,5.5);

  TH2D* hntrkVsGap_g_HFAnd = new TH2D("hntrkVsGap_g_HFAnd",";gap_g;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hntrkVsGap_n_HFAnd = new TH2D("hntrkVsGap_n_HFAnd",";gap_n;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hGap_nvsg_HFAnd = new TH2D("hGap_nvsg_HFAnd",";gap_g;gap_n",55,0,5.5,55,0,5.5);

  TH2D* hntrkVsGap_g_HF1And = new TH2D("hntrkVsGap_g_HF1And",";gap_g;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hntrkVsGap_n_HF1And = new TH2D("hntrkVsGap_n_HF1And",";gap_n;nTrk",55,0,5.5,1000,0,1000);
  TH2D* hGap_nvsg_HF1And = new TH2D("hGap_nvsg_HF1And",";gap_g;gap_n",55,0,5.5,55,0,5.5);

  TFileCollection tf("tf", "", inputList);

  const TString& treeDir_trk = "PbPbTracks";
  TChain t_trk(treeDir_trk+"/trackTree");
  t_trk.AddFileInfoList(tf.GetList());

  const TString& treeDir_HFAdc = "HFAdcana";
  TChain t_HFAdc(treeDir_HFAdc+"/adc");
  t_HFAdc.AddFileInfoList(tf.GetList());

  const TString& treeDir_L1CaloTower = "l1CaloTowerEmuTree";
  TChain t_L1CaloTower(treeDir_L1CaloTower+"/L1CaloTowerTree");
  t_L1CaloTower.AddFileInfoList(tf.GetList());

  const TString& treeDir_zdc = "zdcanalyzer";
  TChain t_zdc(treeDir_zdc+"/zdcrechit");
  t_zdc.AddFileInfoList(tf.GetList());

  const TString& treeDir_pf = "particleFlowAnalyser";
  TChain t_pf(treeDir_pf+"/pftree");
  t_pf.AddFileInfoList(tf.GetList());

  TTreeReader trkReader(&t_trk);
  TTreeReaderValue<int> nTrk(trkReader, "nTrk");
  TTreeReaderValue<std::vector<float>> trkPt(trkReader, "trkPt");
  TTreeReaderValue<std::vector<float>> trkEta(trkReader, "trkEta");
  TTreeReaderValue<std::vector<bool>> highPurity(trkReader, "highPurity");

  TTreeReader HFAdcReader(&t_HFAdc);
  TTreeReaderValue<int> mMaxL1HFAdcPlus(HFAdcReader, "mMaxL1HFAdcPlus");
  TTreeReaderValue<int> mMaxL1HFAdcMinus(HFAdcReader, "mMaxL1HFAdcMinus");

  TTreeReader L1CaloTowerReader(&t_L1CaloTower);
  TTreeReaderValue<L1Analysis::L1AnalysisL1CaloTowerDataFormat> caloTower(L1CaloTowerReader, "L1CaloTower");
//  TTreeReaderValue<std::vector<short>> ietaTower(L1CaloTowerReader, "L1CaloTower.ieta");
//  TTreeReaderValue<std::vector<short>> iphiTower(L1CaloTowerReader, "L1CaloTower.iphi");
//  TTreeReaderValue<std::vector<short>> ietTower(L1CaloTowerReader, "L1CaloTower.iet");

  TTreeReader zdcReader(&t_zdc);
  TTreeReaderValue<int> nzdc(zdcReader, "n");
  TTreeReaderArray<float> zdcenergy(zdcReader, "e");
  TTreeReaderArray<int> zdcside(zdcReader, "zside");

  TTreeReader pfReader(&t_pf);
  TTreeReaderValue<int> nPF(pfReader, "nPF");
  TTreeReaderValue<std::vector<float>> pfPt(pfReader, "pfPt");
  TTreeReaderValue<std::vector<float>> pfEta(pfReader, "pfEta");

  int hfmin = 19;
  int hf1min = 15;
  float gap_min = 0.000003;
  
  int nEvents = 0;
  while (L1CaloTowerReader.Next()) {

     HFAdcReader.Next();
     trkReader.Next();
     zdcReader.Next();
     pfReader.Next(); 

     if(!(nEvents % 5000)) cout << "Processing " << nEvents << " events" <<endl;

     sort(pfEta->begin(), pfEta->end());
     int npf = pfEta->size();

     vector<float> pfEta_m, pfEta_p;
     for(int i=0;i<npf;i++)
     {
       if(pfEta->at(i)<0) pfEta_m.push_back(pfEta->at(i));
       if(pfEta->at(i)>0) pfEta_p.push_back(pfEta->at(i));
     } 
     pfEta_m.push_back(0.0);
     pfEta_p.push_back(0.0);

     sort(pfEta_p.begin(), pfEta_p.end());
     sort(pfEta_m.begin(), pfEta_m.end());

     int npf_p = pfEta_p.size();
     int npf_m = pfEta_m.size();
     
     float detasum_m = 0;
     for(int i=0;i<npf_m-1;i++)
     { 
       float deta = pfEta_m.at(i+1)-pfEta_m.at(i);
       if(deta>gap_min) detasum_m += deta;
     }

     float detasum_p = 0;
     for(int i=npf_p-1;i>0;i--)
     { 
       float deta = pfEta_p.at(i)-pfEta_p.at(i-1);
       if(deta>gap_min) detasum_p += deta;
     }

     pfEta_m.clear();  pfEta_p.clear();

     double zdcSumPlus=0; double zdcSumMinus=0;
     for(int i=0;i<(*nzdc);i++)
     {
       if(zdcside[i]>0) zdcSumPlus += zdcenergy[i];
       if(zdcside[i]<0) zdcSumMinus += zdcenergy[i];
     }

     hZDCSumPlusVsMinus->Fill( zdcSumPlus, zdcSumMinus);
     hZDCSumPlus->Fill( zdcSumPlus );
     hZDCSumMinus->Fill( zdcSumMinus );

     int ntower = caloTower->nTower;
//cout<<ntower<<endl;
     int sumTowerPlus=0; int sumTowerMinus=0; double sumETTPlus=0; double sumETTMinus=0; double sumHFPlus=0; double sumHFMinus=0;
     for(int i=0;i<ntower;i++)
     {
       if(caloTower->ieta.at(i)>0 && caloTower->ieta.at(i)<=16) { sumTowerPlus++; sumETTPlus += (caloTower->iet.at(i)); }
       if(caloTower->ieta.at(i)<0 && caloTower->ieta.at(i)>=-16) { sumTowerMinus++; sumETTMinus += (caloTower->iet.at(i)); }
       if(caloTower->ieta.at(i)>16) sumHFPlus += (caloTower->iet.at(i));
       if(caloTower->ieta.at(i)<-16) sumHFMinus += (caloTower->iet.at(i));
     }
  
     int ntrks = trkPt->size();
     int nTrkHP = 0;
     for(int i=0;i<ntrks;i++)
     {
       if(highPurity->at(i) && trkPt->at(i)>0.3 && (trkEta->at(i))<2.4) nTrkHP++;
     }  

     hntrk->Fill( nTrkHP );

    
     if(zdcSumPlus>1400 && zdcSumMinus<1400)
     {
       hntrkVsGap_g->Fill(detasum_m, nTrkHP);   
       hntrkVsGap_n->Fill(detasum_p, nTrkHP);  
       hGap_nvsg->Fill(detasum_m, detasum_p); 

       hntrk_ZDCP->Fill( nTrkHP );

       hnTrkvsETT_ZDCP->Fill( nTrkHP, sumETTPlus );
       hnTrkvsHF_ZDCP->Fill( nTrkHP, sumHFPlus );
       hnTrkvsTower_ZDCP->Fill( nTrkHP, sumTowerPlus );

       hHFPlusVsHFMinus_ZDCP->Fill( sumHFPlus, sumHFMinus );
       hETTPlusVsETTMinus_ZDCP->Fill( sumETTPlus, sumETTMinus );
       hTowerPlusVsTowerMinus_ZDCP->Fill( sumTowerPlus, sumTowerMinus );

       if((*mMaxL1HFAdcPlus)>hfmin && (*mMaxL1HFAdcMinus)>hfmin)
       {
         hntrkVsGap_g_HFAnd->Fill(detasum_m, nTrkHP);
         hntrkVsGap_n_HFAnd->Fill(detasum_p, nTrkHP);
         hGap_nvsg_HFAnd->Fill(detasum_m, detasum_p);

         hntrk_ZDCP_HFAnd->Fill( nTrkHP );

         hnTrkvsETT_ZDCP_HFAnd->Fill( nTrkHP, sumETTPlus );
         hnTrkvsHF_ZDCP_HFAnd->Fill( nTrkHP, sumHFPlus );
         hnTrkvsTower_ZDCP_HFAnd->Fill( nTrkHP, sumTowerPlus );

         hHFPlusVsHFMinus_ZDCP_HFAnd->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCP_HFAnd->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCP_HFAnd->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcPlus)>hf1min && (*mMaxL1HFAdcMinus)>hf1min)
       {
         hntrkVsGap_g_HF1And->Fill(detasum_m, nTrkHP);
         hntrkVsGap_n_HF1And->Fill(detasum_p, nTrkHP);
         hGap_nvsg_HF1And->Fill(detasum_m, detasum_p);

         hntrk_ZDCP_HF1And->Fill( nTrkHP );

         hnTrkvsETT_ZDCP_HF1And->Fill( nTrkHP, sumETTPlus );
         hnTrkvsHF_ZDCP_HF1And->Fill( nTrkHP, sumHFPlus );
         hnTrkvsTower_ZDCP_HF1And->Fill( nTrkHP, sumTowerPlus );

         hHFPlusVsHFMinus_ZDCP_HF1And->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCP_HF1And->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCP_HF1And->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcPlus)>hfmin)
       {
         hntrk_ZDCP_HFP->Fill( nTrkHP );

         hnTrkvsETT_ZDCP_HFP->Fill( nTrkHP, sumETTPlus );
         hnTrkvsHF_ZDCP_HFP->Fill( nTrkHP, sumHFPlus );
         hnTrkvsTower_ZDCP_HFP->Fill( nTrkHP, sumTowerPlus );

         hHFPlusVsHFMinus_ZDCP_HFP->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCP_HFP->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCP_HFP->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcPlus)>hf1min)
       {
         hntrk_ZDCP_HF1P->Fill( nTrkHP );

         hnTrkvsETT_ZDCP_HF1P->Fill( nTrkHP, sumETTPlus );
         hnTrkvsHF_ZDCP_HF1P->Fill( nTrkHP, sumHFPlus );
         hnTrkvsTower_ZDCP_HF1P->Fill( nTrkHP, sumTowerPlus );

         hHFPlusVsHFMinus_ZDCP_HF1P->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCP_HF1P->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCP_HF1P->Fill( sumTowerPlus, sumTowerMinus );
       }
     }

     if(zdcSumPlus<1400 && zdcSumMinus>1400)
     {
       hntrkVsGap_g->Fill(detasum_p, nTrkHP);  
       hntrkVsGap_n->Fill(detasum_m, nTrkHP); 
       hGap_nvsg->Fill(detasum_p, detasum_m);

       hntrk_ZDCM->Fill( nTrkHP );

       hnTrkvsETT_ZDCM->Fill( nTrkHP, sumETTMinus );
       hnTrkvsHF_ZDCM->Fill( nTrkHP, sumHFMinus );
       hnTrkvsTower_ZDCM->Fill( nTrkHP, sumTowerMinus );

       hHFPlusVsHFMinus_ZDCM->Fill( sumHFPlus, sumHFMinus );
       hETTPlusVsETTMinus_ZDCM->Fill( sumETTPlus, sumETTMinus );
       hTowerPlusVsTowerMinus_ZDCM->Fill( sumTowerPlus, sumTowerMinus );

       if((*mMaxL1HFAdcPlus)>hfmin && (*mMaxL1HFAdcMinus)>hfmin)
       {
         hntrkVsGap_g_HFAnd->Fill(detasum_p, nTrkHP);  
         hntrkVsGap_n_HFAnd->Fill(detasum_m, nTrkHP); 
         hGap_nvsg_HFAnd->Fill(detasum_p, detasum_m);

         hntrk_ZDCM_HFAnd->Fill( nTrkHP );

         hnTrkvsETT_ZDCM_HFAnd->Fill( nTrkHP, sumETTMinus );
         hnTrkvsHF_ZDCM_HFAnd->Fill( nTrkHP, sumHFMinus );
         hnTrkvsTower_ZDCM_HFAnd->Fill( nTrkHP, sumTowerMinus );

         hHFPlusVsHFMinus_ZDCM_HFAnd->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCM_HFAnd->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCM_HFAnd->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcPlus)>hf1min && (*mMaxL1HFAdcMinus)>hf1min)
       {
         hntrkVsGap_g_HF1And->Fill(detasum_p, nTrkHP);
         hntrkVsGap_n_HF1And->Fill(detasum_m, nTrkHP);
         hGap_nvsg_HF1And->Fill(detasum_p, detasum_m);

         hntrk_ZDCM_HF1And->Fill( nTrkHP );

         hnTrkvsETT_ZDCM_HF1And->Fill( nTrkHP, sumETTMinus );
         hnTrkvsHF_ZDCM_HF1And->Fill( nTrkHP, sumHFMinus );
         hnTrkvsTower_ZDCM_HF1And->Fill( nTrkHP, sumTowerMinus );

         hHFPlusVsHFMinus_ZDCM_HF1And->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCM_HF1And->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCM_HF1And->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcMinus)>hfmin)
       {
         hntrk_ZDCM_HFM->Fill( nTrkHP );

         hnTrkvsETT_ZDCM_HFM->Fill( nTrkHP, sumETTMinus );
         hnTrkvsHF_ZDCM_HFM->Fill( nTrkHP, sumHFMinus );
         hnTrkvsTower_ZDCM_HFM->Fill( nTrkHP, sumTowerMinus );

         hHFPlusVsHFMinus_ZDCM_HFM->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCM_HFM->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCM_HFM->Fill( sumTowerPlus, sumTowerMinus );
       }

       if((*mMaxL1HFAdcMinus)>hf1min)
       {
         hntrk_ZDCM_HF1M->Fill( nTrkHP );

         hnTrkvsETT_ZDCM_HF1M->Fill( nTrkHP, sumETTMinus );
         hnTrkvsHF_ZDCM_HF1M->Fill( nTrkHP, sumHFMinus );
         hnTrkvsTower_ZDCM_HF1M->Fill( nTrkHP, sumTowerMinus );

         hHFPlusVsHFMinus_ZDCM_HF1M->Fill( sumHFPlus, sumHFMinus );
         hETTPlusVsETTMinus_ZDCM_HF1M->Fill( sumETTPlus, sumETTMinus );
         hTowerPlusVsTowerMinus_ZDCM_HF1M->Fill( sumTowerPlus, sumTowerMinus );
       }
     }

     if((*mMaxL1HFAdcPlus)>hfmin && (*mMaxL1HFAdcMinus)>hfmin)
     {
       hntrk_HFAnd->Fill( nTrkHP );
       if(zdcSumPlus>1400 && zdcSumMinus>1400) hntrk_ZDCAnd_HFAnd->Fill( nTrkHP );
       hnTrkvsETT->Fill( nTrkHP, sumETTPlus+sumETTMinus );
       hnTrkvsETTHF->Fill( nTrkHP, sumETTPlus+sumETTMinus+sumHFPlus+sumHFMinus );
       hnTrkvsHF->Fill( nTrkHP, sumHFPlus+sumHFMinus );
       hnTrkvsTower->Fill( nTrkHP, sumTowerPlus+sumTowerMinus );
     }

     if((*mMaxL1HFAdcPlus)>hf1min && (*mMaxL1HFAdcMinus)>hf1min)
     {
       hntrk_HF1And->Fill( nTrkHP );
       if(zdcSumPlus>1400 && zdcSumMinus>1400) hntrk_ZDCAnd_HF1And->Fill( nTrkHP );
     }

     if(zdcSumPlus>1400 || zdcSumMinus>1400) hntrk_ZDCOr->Fill( nTrkHP );

     if((*mMaxL1HFAdcPlus)>hfmin && (*mMaxL1HFAdcMinus)<hfmin) 
     {
       hnTrkvsETTPlus->Fill( nTrkHP, sumETTPlus );
       hnTrkvsETTHFPlus->Fill( nTrkHP, sumETTPlus+sumHFPlus );
       hnTrkvsHFPlus->Fill( nTrkHP, sumHFPlus );
       hnTrkvsTowerPlus->Fill( nTrkHP, sumTowerPlus );

       hETTPlusVsETTMinus_plus->Fill( sumETTPlus, sumETTMinus );
//cout<<sumETTPlus<<" "<<sumETTMinus<<" "<<nTrkHP<<endl;
       hTowerPlusVsTowerMinus_plus->Fill( sumTowerPlus, sumTowerMinus );
     }

     if((*mMaxL1HFAdcPlus)<hfmin && (*mMaxL1HFAdcMinus)>hfmin) 
     { 
       hnTrkvsETTMinus->Fill( nTrkHP, sumETTMinus );
       hnTrkvsETTHFMinus->Fill( nTrkHP, sumETTMinus+sumHFMinus );
       hnTrkvsHFMinus->Fill( nTrkHP, sumHFMinus );
       hnTrkvsTowerMinus->Fill( nTrkHP, sumTowerMinus );

       hETTPlusVsETTMinus_minus->Fill( sumETTPlus, sumETTMinus );
       hTowerPlusVsTowerMinus_minus->Fill( sumTowerPlus, sumTowerMinus );
     }

     if(!(((*mMaxL1HFAdcPlus)>hfmin) && ((*mMaxL1HFAdcMinus)>hfmin))) h1_nothf2and->Fill( nTrkHP );
     
     nEvents++;
//     if(nEvents>=1000000) break;
  }

  TFile* fout = new TFile("output.root","recreate");
  hntrk_HFAnd->Write(); 
  hntrk_HF1And->Write();
  hntrk_ZDCAnd_HFAnd->Write();
  hntrk_ZDCAnd_HF1And->Write();
  hntrk_ZDCOr->Write();
  h1_nothf2and->Write();
  hnTrkvsETT->Write();
  hnTrkvsETTHF->Write();
  hnTrkvsHF->Write();
  hnTrkvsETTPlus->Write();
  hnTrkvsETTHFPlus->Write();
  hnTrkvsHFPlus->Write();
  hnTrkvsETTMinus->Write();
  hnTrkvsETTHFMinus->Write();
  hnTrkvsHFMinus->Write();
  hnTrkvsTower->Write();
  hnTrkvsTowerPlus->Write();
  hnTrkvsTowerMinus->Write();
  hETTPlusVsETTMinus_plus->Write();
  hTowerPlusVsTowerMinus_plus->Write();
  hETTPlusVsETTMinus_minus->Write();
  hTowerPlusVsTowerMinus_minus->Write();
  hZDCSumPlusVsMinus->Write();
  hZDCSumPlus->Write();
  hZDCSumMinus->Write();

  hntrk_ZDCP->Write();
  hnTrkvsETT_ZDCP->Write();
  hnTrkvsHF_ZDCP->Write();
  hnTrkvsTower_ZDCP->Write();
  hHFPlusVsHFMinus_ZDCP->Write();
  hETTPlusVsETTMinus_ZDCP->Write();
  hTowerPlusVsTowerMinus_ZDCP->Write();
  hntrk_ZDCM->Write();
  hnTrkvsETT_ZDCM->Write();
  hnTrkvsHF_ZDCM->Write();
  hnTrkvsTower_ZDCM->Write();
  hHFPlusVsHFMinus_ZDCM->Write();
  hETTPlusVsETTMinus_ZDCM->Write();
  hTowerPlusVsTowerMinus_ZDCM->Write();
  hntrk->Write();

  hntrk_ZDCP_HFAnd->Write();
  hnTrkvsETT_ZDCP_HFAnd->Write();
  hnTrkvsHF_ZDCP_HFAnd->Write();
  hnTrkvsTower_ZDCP_HFAnd->Write();
  hHFPlusVsHFMinus_ZDCP_HFAnd->Write();
  hETTPlusVsETTMinus_ZDCP_HFAnd->Write();
  hTowerPlusVsTowerMinus_ZDCP_HFAnd->Write();
  hntrk_ZDCM_HFAnd->Write();
  hnTrkvsETT_ZDCM_HFAnd->Write();
  hnTrkvsHF_ZDCM_HFAnd->Write();
  hnTrkvsTower_ZDCM_HFAnd->Write();
  hHFPlusVsHFMinus_ZDCM_HFAnd->Write();
  hETTPlusVsETTMinus_ZDCM_HFAnd->Write();
  hTowerPlusVsTowerMinus_ZDCM_HFAnd->Write();

  hntrk_ZDCP_HF1And->Write();
  hnTrkvsETT_ZDCP_HF1And->Write();
  hnTrkvsHF_ZDCP_HF1And->Write();
  hnTrkvsTower_ZDCP_HF1And->Write();
  hHFPlusVsHFMinus_ZDCP_HF1And->Write();
  hETTPlusVsETTMinus_ZDCP_HF1And->Write();
  hTowerPlusVsTowerMinus_ZDCP_HF1And->Write();
  hntrk_ZDCM_HF1And->Write();
  hnTrkvsETT_ZDCM_HF1And->Write();
  hnTrkvsHF_ZDCM_HF1And->Write();
  hnTrkvsTower_ZDCM_HF1And->Write();
  hHFPlusVsHFMinus_ZDCM_HF1And->Write();
  hETTPlusVsETTMinus_ZDCM_HF1And->Write();
  hTowerPlusVsTowerMinus_ZDCM_HF1And->Write();

  hntrk_ZDCP_HFP->Write();
  hnTrkvsETT_ZDCP_HFP->Write();
  hnTrkvsHF_ZDCP_HFP->Write();
  hnTrkvsTower_ZDCP_HFP->Write();
  hHFPlusVsHFMinus_ZDCP_HFP->Write();
  hETTPlusVsETTMinus_ZDCP_HFP->Write();
  hTowerPlusVsTowerMinus_ZDCP_HFP->Write();
  hntrk_ZDCM_HFM->Write();
  hnTrkvsETT_ZDCM_HFM->Write();
  hnTrkvsHF_ZDCM_HFM->Write();
  hnTrkvsTower_ZDCM_HFM->Write();
  hHFPlusVsHFMinus_ZDCM_HFM->Write();
  hETTPlusVsETTMinus_ZDCM_HFM->Write();
  hTowerPlusVsTowerMinus_ZDCM_HFM->Write();

  hntrk_ZDCP_HF1P->Write();
  hnTrkvsETT_ZDCP_HF1P->Write();
  hnTrkvsHF_ZDCP_HF1P->Write();
  hnTrkvsTower_ZDCP_HF1P->Write();
  hHFPlusVsHFMinus_ZDCP_HF1P->Write();
  hETTPlusVsETTMinus_ZDCP_HF1P->Write();
  hTowerPlusVsTowerMinus_ZDCP_HF1P->Write();
  hntrk_ZDCM_HF1M->Write();
  hnTrkvsETT_ZDCM_HF1M->Write();
  hnTrkvsHF_ZDCM_HF1M->Write();
  hnTrkvsTower_ZDCM_HF1M->Write();
  hHFPlusVsHFMinus_ZDCM_HF1M->Write();
  hETTPlusVsETTMinus_ZDCM_HF1M->Write();
  hTowerPlusVsTowerMinus_ZDCM_HF1M->Write();

  hntrkVsGap_g->Write();
  hntrkVsGap_n->Write();
  hGap_nvsg->Write();

  hntrkVsGap_g_HF1And->Write();
  hntrkVsGap_n_HF1And->Write();
  hGap_nvsg_HF1And->Write();

  hntrkVsGap_g_HFAnd->Write();
  hntrkVsGap_n_HFAnd->Write();
  hGap_nvsg_HFAnd->Write();

  fout->Close();
}

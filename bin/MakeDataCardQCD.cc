#include "UWAnalysis/StatTools/interface/DataCardCreatorQCD.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 


int main (int argc, char* argv[]) 
{

	optutl::CommandLineParser parser ("Background subtraction ");

	//Input Files
	parser.addOption("channel",optutl::CommandLineParser::kString,"Channel  ","mutau");
	parser.addOption("shifts",optutl::CommandLineParser::kStringVector,"Systematic Shifts(Supported Tau,Jet,Unc and whatever else in the tree) ");
	parser.addOption("zttFile",optutl::CommandLineParser::kString,"File with the ZTT","ZTT.root");
	parser.addOption("zEmbeddedSample",optutl::CommandLineParser::kString,"File with the ZTT+vbfs","");
	parser.addOption("zllFile",optutl::CommandLineParser::kString,"File with the ZLL","ZLL.root");
	parser.addOption("wFile",optutl::CommandLineParser::kString,"File with the W","W.root");
	parser.addOption("vvFile",optutl::CommandLineParser::kString,"File with the VV","VV.root");
	parser.addOption("topFile",optutl::CommandLineParser::kString,"File with the TOP","TOP.root");
	parser.addOption("qcdFile",optutl::CommandLineParser::kString,"File with the QCD","QCD.root");
	parser.addOption("dataFile",optutl::CommandLineParser::kString,"DATA! File","DATA.root");

	//Input Selections
	parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection","");
	parser.addOption("inclselection",optutl::CommandLineParser::kString,"inclselection","");
	parser.addOption("signalselection",optutl::CommandLineParser::kString," Signal ","mt_1<30");
	parser.addOption("wselection",optutl::CommandLineParser::kString,"W sideband defintion ","mt_1>70");
	parser.addOption("qcdselection",optutl::CommandLineParser::kString,"QCD Shape definition");
	parser.addOption("relaxedSelection",optutl::CommandLineParser::kString,"Relaxed Selection");
	parser.addOption("vbfselection",optutl::CommandLineParser::kString,"vbf Selection","njets==2&&mjj>300&&jdeta>3.5&&nbtagNoSF==0");
    parser.addOption("vbfselectionQCD",optutl::CommandLineParser::kString,"vbf Selection","njets==2&&mjj>300&&jdeta>3.5&&nbtagNoSF==0");
	parser.addOption("vbfhighselection",optutl::CommandLineParser::kString,"vbf Selection","njets==2&&mjj>300&&jdeta>3.5&&nbtagNoSF==0");
    parser.addOption("vbfhighselectionQCD",optutl::CommandLineParser::kString,"vbf Selection","njets==2&&mjj>300&&jdeta>3.5&&nbtagNoSF==0");
	parser.addOption("zerojselection",optutl::CommandLineParser::kString,"0j Selection","njets==0");
	parser.addOption("zerojhighselection",optutl::CommandLineParser::kString,"0j Selection","njets==0");
	parser.addOption("onejselection",optutl::CommandLineParser::kString,"1j Selection","njets==1&&nbtagNoSF==0");
	parser.addOption("onejboostselection",optutl::CommandLineParser::kString,"1j Boost Selection","njets==1&&nbtagNoSF==0&&pth>100&&pt_2>50");
	parser.addOption("bTagSF",optutl::CommandLineParser::kString,"bTagSF","1");
	parser.addOption("bTagSF2",optutl::CommandLineParser::kString,"bTagSF","1");
    //need these
	parser.addOption("trigSelection",optutl::CommandLineParser::kString,"Trigger Selection","crossTrigger>0||(lTrigger>0&&pt_1>25)");
	parser.addOption("trigSelection50ns",optutl::CommandLineParser::kString,"Trigger Selection","crossTrigger_50ns>0||(lTrigger_50ns>0&&pt_1>25)");
	parser.addOption("trigSelection25ns",optutl::CommandLineParser::kString,"Trigger Selection","crossTrigger_25ns>0||(lTrigger_25ns>0&&pt_1>25)");
	parser.addOption("blinding",optutl::CommandLineParser::kString,"Blinding","pt_1>0");
	parser.addOption("charge",optutl::CommandLineParser::kString,"charge","charge==0");
	parser.addOption("catSplit",optutl::CommandLineParser::kString,"High/Low category split","pt_2>45");

	//Other Options
	parser.addOption("luminosity",optutl::CommandLineParser::kDouble,"Luminosity",10.);
	parser.addOption("luminosityErr",optutl::CommandLineParser::kDouble,"LuminosityErr",0.04);
	parser.addOption("variable",optutl::CommandLineParser::kString,"Shape variable ","mass");
	parser.addOption("weight",optutl::CommandLineParser::kString,"Weight for MC (Multiply Weight Factors here for efficiencies)","__WEIGHT__");
	parser.addOption("Zweight",optutl::CommandLineParser::kString,"Weight DY MC for ZPt reweighting","__ZWEIGHT__");
	parser.addOption("TTweight",optutl::CommandLineParser::kString,"Weight DY MC for ZPt reweighting","topWeight");
	parser.addOption("zlftFactor",optutl::CommandLineParser::kString,"Z Muon fakes tau error","MuTauFake");
	parser.addOption("embWeight",optutl::CommandLineParser::kString,"Weight for Embedded","__CORR__");
	parser.addOption("min",optutl::CommandLineParser::kDouble,"Minimum value",0.);
	parser.addOption("max",optutl::CommandLineParser::kDouble,"Maximum Value ",500.);
	parser.addOption("bins",optutl::CommandLineParser::kInteger,"Number of Bins",50);
	parser.addOption("verbose",optutl::CommandLineParser::kInteger,"verbose",0);
	parser.addOption("binningHighStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
	parser.addOption("binningLowStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");


	//Input Scale Factors
	parser.addOption("topSF",optutl::CommandLineParser::kDouble,"TTBar Scale Factor",1.0);
	parser.addOption("topErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.075);
	parser.addOption("qcdErr",optutl::CommandLineParser::kDouble,"QCD ERROR",0.15);
	parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.3);   
	parser.addOption("zlftErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.25);
	parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.2);
	parser.addOption("zttScale",optutl::CommandLineParser::kDouble,"Z tau tau scale",1.00);
	parser.addOption("zttScaleErr",optutl::CommandLineParser::kDouble,"Z tau tau scale error",0.033);
	parser.addOption("muID",optutl::CommandLineParser::kDouble,"Mu ID",1.0);
	parser.addOption("muIDErr",optutl::CommandLineParser::kDouble,"MuIDErr",0.02);
	parser.addOption("bID",optutl::CommandLineParser::kDouble,"B ID",1.0);
	parser.addOption("bIDErr",optutl::CommandLineParser::kDouble,"BIDErr",0.10);
	parser.addOption("bmisID",optutl::CommandLineParser::kDouble,"B MISID",1.00);
	parser.addOption("bmisIDErr",optutl::CommandLineParser::kDouble,"BMISIDErr",0.17);
	parser.addOption("eleID",optutl::CommandLineParser::kDouble,"Ele ID",0.0);
	parser.addOption("eleIDErr",optutl::CommandLineParser::kDouble,"Ele IDErr",0.00);
	parser.addOption("tauID",optutl::CommandLineParser::kDouble,"Tau ID",1.0);
	parser.addOption("tauIDHigh",optutl::CommandLineParser::kDouble,"Tau ID Pt>40",1.0);
	parser.addOption("tauIDErr",optutl::CommandLineParser::kDouble,"Tau IDErr",0.06);
	parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.00);
	parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
	parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.06);
	parser.addOption("bFactorZ",optutl::CommandLineParser::kDouble,"B factor Z",1.0);
	parser.addOption("bFactorW",optutl::CommandLineParser::kDouble,"B Factor W",1.0);
	parser.addOption("samesign",optutl::CommandLineParser::kDouble,"Plot Same Sign",0.0);
	parser.addOption("energy",optutl::CommandLineParser::kString,"Center of Mass Energy","13TeV");

	parser.addOption("dir",optutl::CommandLineParser::kString,"dir","../inputs/mutau");
	parser.addOption("bitmask",optutl::CommandLineParser::kIntegerVector,"Choose what to run");
	parser.addOption("scaleUp",optutl::CommandLineParser::kDouble,"scale up for extrapolation to higher lumi",1.0);



	parser.parseArguments (argc, argv);
	std::vector<int> bitmask = parser.integerVector("bitMask");
	DataCardCreatorQCD creator(parser);

	printf("HighStat has %d entries ,LowStat has %d entries\n",(int)parser.doubleVector("binningHighStat").size(),(int)parser.doubleVector("binningLowStat").size());

	//Inclusive
	//Definition of runFullExtrapBtag
    //  
    //          BkgOutput runFullExtrapBtag(std::string preSelection, std::string relaxedSelection, std::string qcdSelection, std::string categorySelection_, std::string prefix, std::string bTagSF) {
    //
 

	printf(" -------------------------------------\n"); 
	printf(" --------New Variable--------\n"); 

	if(bitmask[0]==1){
		printf(" -------------------------------------\n"); 
		creator.setBinning(parser.doubleVector("binningHighStat"));
		printf("INCLUSIVE:preselection -------------------------------------\n"); 
		std::string preSel = parser.stringValue("preselection"); 
		std::string relSel = parser.stringValue("relaxedSelection"); 
		std::string catSel = parser.stringValue("preselection"); 
		std::string qcdSel = parser.stringValue("qcdselection"); 
		std::string bTagSF = parser.stringValue("bTagSF");					 

		BkgOutput outputIncl = creator.runFullExtrapBtag(preSel,relSel,qcdSel, catSel,"_inclusive", bTagSF);
	}

	if(bitmask[1]==1){
		printf(" -------------------------------------\n"); 
		creator.setBinning(parser.doubleVector("binningHighStat"));
		printf("INCLUSIVE: 0 Jets-------------------------------------\n"); 
		std::string preSel = parser.stringValue("preselection"); 
		std::string relSel = parser.stringValue("relaxedSelection"); 
		std::string qcdSel = parser.stringValue("qcdselection"); 
		std::string catSel = parser.stringValue("zerojselection"); 
		std::string bTagSF = parser.stringValue("bTagSF");					 

		BkgOutput outputIncl = creator.runFullExtrapBtag(preSel,relSel,qcdSel,catSel,"_0j", bTagSF);
	}


	if(bitmask[1]==2){
		printf(" -------------------------------------\n"); 
		creator.setBinning(parser.doubleVector("binningHighStat"));
		printf("INCLUSIVE: 0 Jets Low-------------------------------------\n"); 
		std::string preSel = parser.stringValue("preselection"); 
		std::string relSel = parser.stringValue("relaxedSelection"); 
		std::string qcdSel = parser.stringValue("qcdselection"); 
		std::string catSel = parser.stringValue("zerojselection"); 
		std::string bTagSF = parser.stringValue("bTagSF");					 

		BkgOutput outputLow = creator.runFullExtrapBtag(preSel,relSel,qcdSel,catSel,"_0jet_low", bTagSF);

        printf("INCLUSIVE: 0 Jets High-------------------------------------\n"); 
        std::string catSelHigh = parser.stringValue("zerojhighselection"); 
        BkgOutput outputHigh = creator.runFullExtrapBtag(preSel,relSel,qcdSel,catSelHigh,"_0jet_high",bTagSF);
    }

    if(bitmask[2]==1){
        printf(" -------------------------------------\n"); 
        std::cout<<"========Running 1j selection========"<<std::endl;
        creator.setBinning(parser.doubleVector("binningLowStat"));
        std::string preSel = parser.stringValue("preselection"); 
        std::string relSel = parser.stringValue("relaxedSelection");//To be relaxed Btag discriminator 
        std::string qcdSel = parser.stringValue("qcdselection");//To be relaxed Btag discriminator 
        std::string catSel = parser.stringValue("onejselection"); 
        std::string bTagSF = parser.stringValue("bTagSF");					 

        BkgOutput outputIncl = creator.runFullExtrapBtag(preSel,relSel,qcdSel,catSel,"_1j",bTagSF);
    }

    if(bitmask[2]==2){
        printf(" -------------------------------------\n"); 
        std::cout<<"========Running 1j Low selection========"<<std::endl;
        creator.setBinning(parser.doubleVector("binningLowStat"));
        std::string preSel = parser.stringValue("preselection"); 
        std::string relSel = parser.stringValue("relaxedSelection");//To be relaxed Btag discriminator 
        std::string qcdSel = parser.stringValue("onejselection");
        std::string catSel = parser.stringValue("onejselection"); 
        std::string bTagSF = parser.stringValue("bTagSF");					 

        BkgOutput outputLow = creator.runFullExtrapBtag(preSel,relSel, catSel, catSel,"_1jet_low",bTagSF);

        std::cout<<"========Running 1j High selection========"<<std::endl;
        creator.setBinning(parser.doubleVector("binningLowStat"));
        std::string catSelHigh = parser.stringValue("onejboostselection"); 
        BkgOutput outputBoost = creator.runFullExtrapBtag(preSel,relSel,catSelHigh,catSelHigh,"_1jet_high",bTagSF);
    }


    if(bitmask[3]==1){

        printf(" -------------------------------------\n"); 
        std::cout<<"========Running vbf selection========"<<std::endl;
        creator.setBinning(parser.doubleVector("binningLowStat"));
        std::string preSel = parser.stringValue("preselection"); 
        std::string relSel = parser.stringValue("relaxedSelection");//To be relaxed Btag discriminator 
        std::string qcdSel = parser.stringValue("qcdselection");//To be relaxed Btag discriminator 
        std::string catSel = parser.stringValue("vbfselection"); 
        std::string catSelQCD = parser.stringValue("vbfselectionQCD"); 
        std::string bTagSF = parser.stringValue("bTagSF");					 

        BkgOutput outputIncl = creator.runFullExtrapBtag(preSel,relSel,qcdSel,catSel,"_vbf",bTagSF);
    }


    if(bitmask[3]==2){

        printf(" -------------------------------------\n"); 
        creator.setBinning(parser.doubleVector("binningLowStat"));
        std::string preSel = parser.stringValue("preselection"); 
        std::string relSel = parser.stringValue("relaxedselection");//To be relaxed Btag discriminator 
        std::string qcdSel = parser.stringValue("qcdselection");//To be relaxed Btag discriminator 
        std::string catSel = parser.stringValue("vbfselection"); 
        std::string catSelQCD = parser.stringValue("vbfselectionQCD"); 
        std::string catSelHigh = parser.stringValue("vbfhighselection"); 
        std::string catSelHighQCD = parser.stringValue("vbfhighselectionQCD"); 
        std::string bTagSF = parser.stringValue("bTagSF");					 
        std::cout<<"Low Selection: "<<catSel<<std::endl;
        std::cout<<"Low qcd Selection: "<<catSelQCD<<std::endl;
        std::cout<<"high Selection: "<<catSelHigh<<std::endl;
        std::cout<<"high qcd Selection: "<<catSelHighQCD<<std::endl;
        std::cout<<"========Running vbf low selection========"<<std::endl;
        BkgOutput outputLow = creator.runFullExtrapBtag(preSel,relSel,catSelQCD,catSel,"_vbf_low",bTagSF);

        std::cout<<"========Running vbf high selection========"<<std::endl;
        BkgOutput outputHigh = creator.runFullExtrapBtag(preSel,relSel,catSelHighQCD,catSelHigh,"_vbf_high",bTagSF);
    }



    creator.close();
}



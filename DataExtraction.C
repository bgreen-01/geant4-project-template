/// \file
/// \ingroup tutorial_tree
/// \notebook
/// TTreeReader simplest example.
///
/// Read data from hsimple.root (written by hsimple.C)
///
/// \macro_code
///
/// \author Anders Eie, 2013

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

void DataExtraction() {
   // Create a histogram for the values we read.
   
   auto myHist0 = new TH1F("h0","neutron",100,0,0.01);
   auto myHist1 = new TH1F("h1","gamma",100,2.2,2.3);
   auto myHist2 = new TH1F("h2","neutron",100,0,0.01);
   auto myHist3 = new TH1F("h3","gamma",100,2.2,2.3);
   auto myHist4 = new TH1F("h4","neutron",100,0,0.01);
   auto myHist5 = new TH1F("h5","gamma",100,2.2,2.3);
     
   
   //TCanvas *c1 = new TCanvas("c1", "Neutron spectra combined", 1100, 800);
   //File 1 --------------------------- 
   auto myFile0 = TFile::Open("ZnO2-0mmWater.root");
   if (!myFile0 || myFile0->IsZombie()) {
      return;
   }   
   //create reader
   TTreeReader myReader0("Hits;1", myFile0);
   
   //fetch neutron tree
   TTreeReaderValue<double_t> myPx0(myReader0, "fNEdep");
   //fetch gamma tree 
   TTreeReaderValue<double_t> myPx3(myReader0, "fEdep");
 
 
   while (myReader0.Next()) {
   	     if (*myPx0>0.0 && *myPx0<0.01)
     	 {
      		myHist0->Fill(*myPx0);
      	 } 
      	 
      	 if (*myPx3>2.2 && *myPx3<2.3)
     	 {
      		myHist1->Fill(*myPx3);
      	 } 
    }

   	     
   
      
   //File 2 --------------------------- 
   auto myFile = TFile::Open("ZnO2-2mmWater.root");
   if (!myFile || myFile->IsZombie()) {
      return;
   }   
   
   //create reader
   TTreeReader myReader("Hits;1", myFile);
   
   //fetch neutron tree
   TTreeReaderValue<double_t> myPx(myReader, "fNEdep");
   //fetch gamma tree
   TTreeReaderValue<double_t> myPx4(myReader, "fEdep");
   
   while (myReader.Next()) {
   	     if (*myPx>0 && *myPx<0.01)
     	 {
      		myHist2->Fill(*myPx);
      	 } 
      	 
     	 if (*myPx4>2.2 && *myPx4<2.3)
     	 {
      		myHist3->Fill(*myPx4);
      	 } 
      	 
   }
   
     
    //File 3 --------------------------- 
   auto myFile2 = TFile::Open("ZnO2-5mmWater.root");
   if (!myFile2 || myFile2->IsZombie()) {
      return;
   }    
  
   //create reader
   TTreeReader myReader2("Hits;1", myFile2);

   //fetch neutron tree
   TTreeReaderValue<double_t> myPx2(myReader2, "fNEdep");
   //fetch gamma tree
   TTreeReaderValue<double_t> myPx5(myReader2, "fEdep");
   
   while (myReader2.Next()) {
   	     if (*myPx2>0 && *myPx2<0.01)
     	 {
      		myHist4->Fill(*myPx2);
      	 } 
      	 
      	 if (*myPx5>2.2 && *myPx5<2.3)
     	 {
      		myHist5->Fill(*myPx5);
      	 } 
    }	
    
	//End of file access --------------------------
	
	//count- n   g
	//Hist   0 & 1 = 0 mm
	//Hist   2 & 3 = 2 mm
	//Hist   4 & 5 = 5 mm

    //Fetch data from files
    double_t entries0 =  myHist0->GetEntries(); 
    double_t entries1 =  myHist1->GetEntries(); 
   	
   	
   	double_t entries2 =  myHist2->GetEntries(); 
   	double_t entries3 =  myHist3->GetEntries(); 
   	
   	
   	double_t entries4 =  myHist4->GetEntries(); 
   	double_t entries5 =  myHist5->GetEntries(); 
   	
   	
   	
    
    //Write data to CSV file
    std::ofstream dataFile;
    dataFile.open ("ZnO2-slab-tests.csv");
   
    dataFile << "Neutrons sub 10 keV" << " " << "Gammas between 2.2 and 2.3" << "\n";
    dataFile << "0 mm"<< " " << entries0 << " " << entries1 <<"\n";
    dataFile << "2 mm"<< " " <<  entries2 << " " << entries3 <<"\n";
    dataFile << "5 mm"<< " " <<  entries4 << " " << entries5 <<"\n";
    
    dataFile.close();
    
 	
}

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <TGraph.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TAxis.h>

using namespace std;

typedef struct{
    int wavelength;
    vector<double> absorption;    
} SpecData;

SpecData stringsplitter(string unparsed){
    
    vector<int> comma_location;
    int comma;
    SpecData spec_data;
    int i=0;
    string parsed;
    
    comma_location.push_back(0);
    comma = unparsed.find(',');
    i=1;
    while(comma!=-1){
        comma_location.push_back(comma);
        comma = unparsed.find( ',' , comma_location[i]+1);
        i++;
    }
    comma = unparsed.size();
    comma_location.push_back(comma);
    
    for(i=0; i< int(comma_location.size())-1; i++){
        
        parsed = unparsed.substr(comma_location[i], comma_location[i+1]-comma_location[i]);
        
        comma = parsed.find(',',0);
        
        if(comma != -1){
            parsed.erase( parsed.find(',',0),1);
        }

        if(i==0){
            spec_data.wavelength = atoi(parsed.c_str());
        } else {
            spec_data.absorption.push_back(atof(parsed.c_str()));
        }
    
    }

    return spec_data;
}

int main(int argc, char* argv[]){


    char* filename = argv[1];
    string unparsed;
    SpecData data;
    int i=0;
    double wl[910]={}, abs[4][910]={};
    ifstream csv_file (filename);
        
        
    if (csv_file.good()){
        while (getline(csv_file,unparsed,'\n')){ 
            data = stringsplitter(unparsed);
            //cout << data.wavelength << endl;
            wl[i]=data.wavelength;
            abs[0][i]=data.absorption[0];
            abs[1][i]=data.absorption[1];
            abs[2][i]=data.absorption[2];
            abs[3][i]=data.absorption[3];

            i++;
        }

    } else {
        cout << "error opening file!" << endl;
    }


    csv_file.close();
    
    TApplication* rootapp = new TApplication("example",&argc,argv);
    
    TCanvas *c = new TCanvas("c","c", 200,10,1000,900);
    TGraph *gra1 = new TGraph(910,wl, abs[0]);  
    TGraph *gra2 = new TGraph(910,wl, abs[1]);
    TGraph *gra3 = new TGraph(910,wl, abs[2]);
    TGraph *gra4 = new TGraph(910,wl, abs[3]);

    gra1->SetLineColor(2);
    gra1->SetLineWidth(2);
    gra1->SetMarkerColor(4);
    gra1->SetMarkerStyle(20);

    gra2->SetLineColor(8);
    gra2->SetLineWidth(2);
    gra2->SetMarkerColor(4);
    gra2->SetMarkerStyle(20);


    gra3->SetLineColor(9);
    gra3->SetLineWidth(2);
    gra3->SetMarkerColor(4);
    gra3->SetMarkerStyle(20);
    

    gra4->SetLineColor(1);
    gra4->SetLineWidth(2);
    gra4->SetMarkerColor(4);
    gra4->SetMarkerStyle(20);
    
    gra1->SetTitle("Annie Liner Absorbance");
    gra1->GetXaxis()->SetTitle("Wavelength (nm)");
    gra1->GetYaxis()->SetTitle("Absorbance");
    gra1->GetXaxis()->SetLimits(250,750);
    gra1->GetYaxis()->SetRangeUser(-0.001,0.075);

    c->cd(1)->SetGrid();
    gra1->Draw("AL");
    gra2->Draw("L");
    gra3->Draw("L");
    gra4->Draw("L");

    rootapp->Run();

return 0;
}

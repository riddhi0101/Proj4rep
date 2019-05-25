#include <iostream>
#include <ostream>
#include <cctype>
#include <fstream>
#include "CSVWriter.h"
#include "CSVReader.h"
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include "StringUtils.h"
//#include "cmake-build-debug/CSVReader.h"
//#include "cmake-build-debug/XMLEntity.h"


int main(int argc, char *argv[]){
    std::cout<<"before assignig"<<std::endl; 
    std::string Inputline(argv[2]);
    std::cout<<"after assigning"<<std::endl;
    //std::getline(std::cin, InputLin);
    //std::string Inputline(InputLin);
    std::ifstream InFile(Inputline);
    std::cout<< "afterfileassinging"<<std::endl;
    if (Inputline[(Inputline).length()-1] == 'v'){
        std::cout<<"MAKING XML"<<std::endl;
        CCSVReader Reader(InFile);
        std::vector <std::string> CSVHeader;
        Reader.ReadRow(CSVHeader);
        std::string outputfilename = Inputline;
        outputfilename.substr(0, Inputline.length()-3);
        outputfilename += "xml";
        std::ofstream  Outfile(outputfilename);
        std:: vector <std::string> header = StringUtils::Split(Inputline,"_");
        SXMLEntity Filename;
        Filename.DNameData = std::string("course");
        Filename.DType = SXMLEntity::EType::StartElement;
        Filename.SetAttribute(std::string("SUBJ"),header[0]);
        Filename.SetAttribute(std::string("CRSE"),header[1]);
        Filename.SetAttribute(std::string("SEC"),header[2]);
        CXMLWriter Headerwrite(Outfile);
        Headerwrite.WriteEntity(Filename);
        while (!Reader.End()) {
            std::vector<std::string> vec;
            Reader.ReadRow(vec);
            SXMLEntity row;
            Filename.DNameData = std::string("student");
            Filename.DType = SXMLEntity::EType::CompleteElement;
            for (int i =0; i<vec.size();i++ ){
                row.SetAttribute(CSVHeader[i], vec[i]);
            }
            Outfile << std::string("   ") ;
            //CXMLWriter elementwrite(Outfile);
            Headerwrite.WriteEntity(Filename);
        }
        SXMLEntity endelement;
        endelement.DType = SXMLEntity::EType::EndElement;
        endelement.DNameData = std::string("course");
        CXMLWriter Endwrite(Outfile);
        Endwrite.WriteEntity(endelement);

    }
    else{
        std::cout<<"MAKING CSV"<<std::endl;
        CXMLReader Reader(InFile);
        SXMLEntity Filename;
        Reader.ReadEntity(Filename,true);
        std:: vector <std::string> OutFilename;
        OutFilename.push_back(Filename.AttributeValue(std::string("SUBJ")));
        OutFilename.push_back(Filename.AttributeValue(std::string("CRSE")));
        OutFilename.push_back(Filename.AttributeValue(std::string("SEC")));
        std::string OutFileName = StringUtils::Join("_", OutFilename);
        OutFileName += std::string(".csv");
        std::ofstream  Outfile(OutFileName);
        //header
        std::vector <std::string> vec;
        SXMLEntity readrow;
        Reader.ReadEntity(readrow);
        for (auto ch :readrow.DAttributes){
            vec.push_back(std::get<0>(ch));
        }
        CCSVWriter headerwrite (Outfile);
        headerwrite.WriteRow(vec);
        while (!Reader.End()){
            std::vector <std::string> vec1;
            SXMLEntity readrow1;
            Reader.ReadEntity(readrow1);
            for (auto ch :readrow.DAttributes) {
                vec.push_back(std::get<1>(ch));
                headerwrite.WriteRow(vec1);
            }
        }


    }


    return EXIT_SUCCESS;
}

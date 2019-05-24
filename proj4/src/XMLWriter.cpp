//
// Created by Dev Patel on 2019-05-22.
//

#include "XMLWriter.h"
std::string CSVWriter::Replace(const std::string &str, const std::string &old, const std::string &rep) static{
    std::string subString;
    ssize_t lengthstr = str.length();
    int lengthf = old.length();// why does it say that the length of "\\" is 1
    size_t lastfound = 0;
    size_t found = str.find(old);
    while (lastfound < lengthstr) {
        subString.append(str, lastfound, (found - lastfound));
        subString.append(rep);
        lastfound = found + lengthf;
        found = str.find(old, lastfound);
        if (found == std::string::npos) {
            subString.append(str, lastfound, (found - lastfound));
            break;
        }
    }
    return subString;
}

CXMLWriter::CXMLWriter(std::ostream &os) {

}


CXMLWriter::~CXMLWriter() {

}
bool CXMLWriter::Flush() {

}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
    std::vector < std::pair< std::string, std::string > > outputform;
    outputform = entity.DAttributes;

    if (entity.DType == StartElement){
        /*for (int i =0; i<entity.DAttributes.length(); i++ ){
            outputform.push_back(entity.DAttributes[1])
        }*/
        for (int i =0; i<outputform.length(); i++ ){
            this-> Replace(outputform[i][0], "\"", "&quot");
            this-> Replace(outputform[i][0], "'", "&apos");
            this-> Replace(outputform[i][0], "<", "&lt");
            this-> Replace(outputform[i][0], ">", "&gt");
            this-> Replace(outputform[i][1], "\"", "&quot");
            this-> Replace(outputform[i][1], "'", "&apos");
            this-> Replace(outputform[i][1], "<", "&lt");
            this-> Replace(outputform[i][1], ">", "&gt");
            this-> Replace(outputform[i][0], "&", "&amp");
            this-> Replace(outputform[i][1], "&", "&amp");
        }
        Output<< "< " + entity.DNameData;
        for (auto ch: outputform){
            Output << ch[0] + "=" + "\"" + ch[1] + "\" ";//extraspace okay?
        }
        Output<<">"<<std::endl;

    }
    else if (entity.DType == CompleteElement ){
        for (int i =0; i<outputform.length(); i++ ){
            this-> Replace(outputform[i][0], "\"", "&quot");
            this-> Replace(outputform[i][0], "'", "&apos");
            this-> Replace(outputform[i][0], "<", "&lt");
            this-> Replace(outputform[i][0], ">", "&gt");
            this-> Replace(outputform[i][1], "\"", "&quot");
            this-> Replace(outputform[i][1], "'", "&apos");
            this-> Replace(outputform[i][1], "<", "&lt");
            this-> Replace(outputform[i][1], ">", "&gt");
            this-> Replace(outputform[i][0], "&", "&amp");
            this-> Replace(outputform[i][1], "&", "&amp");
        }
        Output<< "< " + entity.DNameData;
        for (auto ch: outputform){
            Output << ch[0] + "=" + "\"" + ch[1] + "\" ";//extraspace okay?
        }
        Output<<"\\>"<<std::endl;

    }
    else if (entity.Dtype == CharData){
        Output << "\"" + entity.DNameData + "\"" << std::endl;

    }
    else{
        Output<< "</" + entity.DNameData + ">"<<std::endl;
    }

}
#include "CSVWriter.h"


std::string Join(const std::string &str, const std::vector< std::string > &vect){
    std::string subString;
    int numelements = vect.size();
    for (int i = 0; i < (numelements - 1); i++){
        subString.append(vect[i]);
        subString.append(str);
    }
    if (numelements != 0 ){
        subString.append(vect[numelements -1]);
    }
    return subString;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep){
    std::string subString;
    ssize_t lengthstr = str.length();
    int lengthf = old.length();// why does it say that the length of "\\" is 1
    size_t lastfound = 0;
    size_t found = str.find(old);
    while(lastfound < lengthstr){
        subString.append(str,lastfound, (found - lastfound));
        subString.append(rep);
        lastfound = found + lengthf;
        found = str.find(old,lastfound);
        if (found == std::string::npos){
            subString.append(str,lastfound, (found - lastfound));
            break;
        }
    }
    return subString;
}
CCSVWriter::CCSVWriter(std::ostream &ou) : Output(ou){

}

bool CCSVWriter::WriteRow(const std::vector<std::string> &row) {
    std::vector <std::string>  OutputRow;
    for (auto &Field : row){
        OutputRow.push_back(std::string("\"") + Replace(Field,"\"","\"\"));
    }
    Output<< Join(",", OutputRow) <<std::endl;
    return Output.good();
}






#include "CSVReader.h"

CCSVReader::CCSVReader(std::istream &in) : Input(in) {
    csv_init(&Parser,0);
}

CCSVReader::~CCSVReader() {
    csv_free(&Parser);
}

void CCSVReader::CallBackFeild(void *str, size_t len, void *data) {
    CCSVReader *Ptr = static_cast<CCSVReader*>(data);
    char *str1 = static_cast<char*>(str);
    Ptr->RowBuffer.push_back(std::string(str1));

}

void CCSVReader::CallBackRow(int ch, void *data) {
    CCSVReader *Ptr = static_cast<CCSVReader*>(data);
    Ptr->BufferRows.push(Ptr->RowBuffer);
    Ptr->RowBuffer.clear();
    //Ptr->reachedEnd = true;
}

bool CCSVReader::End() const{
    if (Input.eof){
        return true;
    }
    else{
        return false;
    }

}

bool CCSVReader::ReadRow(std::vector<std::string> &row) {
    int count = 0;
    while (!Input.eof() and BufferRows.empty()) {
        char buffer[128];
        Input.read(buffer, 128);
        csv_parse(&Parser,buffer, Input.gcount(), CallBackFeild, CallBackRow, this);
        count++;
    }
    row = this->BufferRows.front();
    for (auto ch: row){
        std::cout<<ch<<std::endl;
    }
    BufferRows.pop();
    if (Input.eof()){
        csv_fini();
    }
    if (count ==0){
        return false;
    }
    else{
        return true;
    }


}
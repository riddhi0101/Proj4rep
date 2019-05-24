
#include "XMLReader.h"
#include<iostream>

#include <string>

CXMLReader::CXMLReader(std::istream &in) : Input(in){
    XML_ParserCreate(Null);
    XML_SetUserData(DExpatParser, StaticStartElement,StaticEndElement);
    XML_SetElementHandler(DExpatParser,staticStartElement,StaticEndElement)
    XML_SetCharacterDataHandler(DExpatParser, StaticCharacterData);

}

CXMLReader::~CXMLReader() {
    XML_ParserFree(&Parser);
}
void CXMLReader::StartElement (void *data, const XML_Char *name, const XML_Char **attrs){
    CXMLWriter *Ptr = static_cast<CXMLWriterr*>(data);

    SXMLEntity newEntity;
    newEntity.DNameData = std::string(name);
    newEntity.DType = SXMLEntity::EType::StartElement;
    for (int i = 0; attrs[i]; i+=2){
        DAttributes.push_back(std::make_pair(std::string(attrs[i]),std::string(attrs[i+1])));
    }

    Ptr->BufferEntities.push(newEntity);


}

void EndElement (void *data, const XML_Char *name){
    CXMLWriter *Ptr = static_cast<CXMLWriterr*>(data);

    SXMLEntity newEntity;
    newEntity.DNameData = std::string(name);
    newEntity.DType = SXMLEntity::EType::EndElement;

}

void Charecterelement (void *data, const XML_Char *s, int len){
    CXMLWriter *Ptr = static_cast<CXMLWriterr*>(data);

    SXMLEntity newEntity;
    newEntity.DNameData = std::string(s,len);
    newEntity.DType = SXMLEntity::EType::CharData;

}


bool CXMLReader::End() const {
    if (Input.eof() and BufferEntities.empty()){
        return true;
    }
    else{
        return false;
    }

}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    int count = 0;
    while (!Input.eof() and BufferRows.empty()) {
        char buffer[128];
        Input.read(buffer, 128);
        XML_Parse(&Parser,buffer, Input.gcount(),Input.eof());
        count++;

    }
    entity.DAttributes = BufferEntities.front().DAttributes;
    entity.DType = BufferEntities.front().DType;
    entity.DNameData = BufferEntities.front().DNameData;
    BufferEntities.pop();
    if (count ==0){
        return false;
    }
    else{
        return true;
    }

}
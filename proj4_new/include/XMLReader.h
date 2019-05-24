#ifndef XMLREADER_H
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <queue>

class CXMLReader{
    private:
    std::istream &Input;
    XML_Parser DExpatParser;
    std::queue <SXMLEntity> BufferEntities;
    static void StaticStartElement (void *data, const XML_Char *name, const XML_Char **attrs);
    static void StaticEndElement(void *data, const XML_Char *name);
    static void StaticCharacterData (void *data, const XML_Char *s, int len);

        
    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif

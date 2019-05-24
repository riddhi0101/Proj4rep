#ifndef XMLREADER_H
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>

class CXMLReader{
    private:
    std::istream &Input;
    struct XML_Parser DExpatParser;
    std::queue <SXMLEntity> BufferEntities;
    static void StartElement (void *data, const XML_Char *name, const XML_Char **attrs);
    static void EndElement(void *data, const XML_Char *name);
    static void Characterelement (void *data, (ask nick))



        
    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif

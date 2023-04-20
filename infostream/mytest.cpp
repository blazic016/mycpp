// g++ mytest.cpp tinyxml2/tinyxml2.cpp && ./a.out

#include <iostream>
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>


using namespace tinyxml2;
using namespace std;

static const char* xml_simple =
    "<?xml version=\"1.0\"?>"
    "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
    "<PLAY>"
    "<TITLE>A Midsummer Night's Dream</TITLE>"
    "</PLAY>";

static const char* xml_atribut = "<element attrib1=\"1\" attrib2=\"2\" attrib3=\"3\" />";



int TagCount(XMLNode* node, string str)
{
    int cnt = 0;
    std::string prod_id(str);
    // XMLNode* node = doc_bat_sdt.FirstChildElement("tsduck")->FirstChildElement();
    for(node; node; node=node->NextSibling())
    {
        // cout << node->Value() << endl;
        std::string tag_str( node->Value());
        if(tag_str == str)
            cnt++;
    }
    return cnt;
}


void PrintBatAttr(XMLNode* node, string str);
XMLNode* GetNodebyBouquetId(XMLDocument* doc, string id);
string GetBouquetName(XMLNode* node);
vector<string> GetAllTSfromBouquet(XMLNode* node);

int main ()
{

    // Save to file
    XMLDocument file_doc;
    file_doc.Parse(xml_simple);
    file_doc.SaveFile("file.xml");

    XMLDocument doc_attr;
    doc_attr.Parse(xml_atribut);
    doc_attr.SaveFile("xml_atribut.xml");

    // Read from file
    XMLDocument read_doc;
    read_doc.LoadFile( "file.xml" );
	XMLElement* elem = read_doc.FirstChildElement("PLAY")->FirstChildElement("TITLE");
    cout << elem->Name() << ": " << elem->GetText()  << endl;

    // Play with Attribute
    XMLElement* ele = doc_attr.FirstChildElement();
	const XMLAttribute* a = ele->FirstAttribute();
    cout << a->Name() << ": " << a->Value() << endl;
	a = a->Next();
    cout << a->Name() << ": " << a->Value() << endl;
	a = a->Next();
    cout << a->Name() << ": " << a->Value() << endl;

    // Read bat_sdt.xml
    XMLDocument doc_bat_sdt;
    doc_bat_sdt.LoadFile( "bat_sdt.xml" );
    XMLDocument* p_doc_bat_sdt = &doc_bat_sdt;
    // doc_bat_sdt.Print();

    // BAT name
    XMLNode* parrent = doc_bat_sdt.FirstChildElement("tsduck");
    XMLElement* bat = parrent->FirstChildElement("BAT");
    cout << bat->Name() << endl;

    // Num of bats
    int bat_num = TagCount(doc_bat_sdt.FirstChildElement("tsduck")->FirstChildElement(), "BAT");
    cout << "bat_num=" << bat_num << endl;

    // PROVERI i malo sredi funkciju
    PrintBatAttr(doc_bat_sdt.FirstChildElement("tsduck")->FirstChildElement(), "BAT");

    // Get node from bouquet id and continue to work with him
    XMLNode* buket_0xC020 = GetNodebyBouquetId(p_doc_bat_sdt, "0xC020");
    cout << "test... " <<buket_0xC020->ToElement()->FirstAttribute()->Value() << endl;

    // GetBouquetName
    cout << "Bouquet Name: "<< GetBouquetName(buket_0xC020) << endl;
    
    // Get all transport streams from bouquet id
    vector <string> hehe = GetAllTSfromBouquet(buket_0xC020);



    return 0;
}

vector<string> GetAllTSfromBouquet(XMLNode* node)
{
    vector<string> test;
    node = node->ToElement();

    for(node; node; node=node->NextSibling())
    {
        const XMLElement* node_el = node->FirstChildElement("transport_stream");
        cout << "TEST " << node_el->Value() << " " << node_el->FirstAttribute()->GetLineNum() << endl;

    }
    return test;
}


string GetBouquetName(XMLNode* node)
{
    // string name (node->ToElement()->FirstChildElement("bouquet_name_descriptor")->FirstAttribute()->Value() );
    return node->ToElement()->FirstChildElement("bouquet_name_descriptor")->FirstAttribute()->Value();
}


XMLNode* GetNodebyBouquetId(XMLDocument* doc, string id){
    XMLNode* node_root = doc->FirstChildElement("tsduck");
    XMLNode* node_bat_or_sdt = node_root->FirstChildElement();

    XMLElement* firstbat = node_bat_or_sdt->ToElement();
    // cout << firstbat->Name() << endl;
    for(node_bat_or_sdt; node_bat_or_sdt; node_bat_or_sdt=node_bat_or_sdt->NextSibling())
    {
        const XMLElement* bat_elms = node_bat_or_sdt->ToElement();
        string bat_elms_str(node_bat_or_sdt->Value());
        if (bat_elms_str == "BAT")
        {
            const XMLAttribute* bat_attrs = node_bat_or_sdt->ToElement()->FirstAttribute();
            string bat_version( bat_attrs->Value() );
            string bat_bouqet_id( bat_attrs->Next()->Next()->Value() );
            // cout << "bat_version=" << bat_version << " \t ";
            // cout << "bat_bouqet_id=" << bat_bouqet_id;
            // cout << endl;

            if (id == bat_bouqet_id)
            {
                cout << "[GetNodebyBouquetId] return node: " << bat_bouqet_id << endl;
                return node_bat_or_sdt;
            }
        }

    }
    // if not exist string id
    return nullptr;
}


void PrintBatAttr(XMLNode* node, string str)
{
    std::string prod_id(str);
    for(node; node; node=node->NextSibling())
    {
        const XMLAttribute* bat_attrs = node->ToElement()->FirstAttribute();
        std::string tag_str( node->Value());
        if(tag_str == str)
        {
            cout << bat_attrs->Name() << ": " << bat_attrs->Value() << " - ";
            bat_attrs = bat_attrs->Next();
            cout << bat_attrs->Name() << ": " << bat_attrs->Value() << " - ";
            bat_attrs = bat_attrs->Next();
            cout << bat_attrs->Name() << ": " << bat_attrs->Value() << endl;
        }
    }
}
// g++ oop.cpp tinyxml2/tinyxml2.cpp && ./a.out

#include<iostream>
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>

using namespace tinyxml2;
using namespace std;

// #define DEBUG

typedef struct transport_stream {
    string transport_stream_id;
    string generic_descriptor;
} transport_stream;

typedef struct Bouquet {
    string name;
    string id;
    string version;
    vector<transport_stream> tsdata;
} Bouquet;

class bat
{
private:
    XMLDocument doc;
    string xml_filename;
    int num_of_table = 0;
    XMLNode* first_bat_node;
    vector<Bouquet> bouquets;
public:
    bat(string fname);
    string getFileName();
    int getNumTable();
    void setNumTable();
    void setBouquet();
    void setFirstBatNode();
    vector<Bouquet> getBouquet() {return bouquets;}
};

bat::bat(string fname) : xml_filename {fname} {

    XMLError err = doc.LoadFile( xml_filename.c_str() );
    if (err != XML_SUCCESS) {cout << "[bat] Constructor failed" << endl;}
        // To do: constructor return error code (maybe throw)
    
    bat::setNumTable();
    bat::setFirstBatNode();
    bat::setBouquet();
}

string bat::getFileName() { return xml_filename; }

void bat::setNumTable() {

    num_of_table = 0;
    XMLNode* node = doc.FirstChildElement("tsduck")->FirstChildElement();

    for(node; node; node=node->NextSibling())
    {
        std::string tag_str( node->Value());
        if(tag_str == "BAT")
            num_of_table++;
    }

    if (num_of_table == 0) { cout << "No exists bat table!" << endl; }
}

int bat::getNumTable() { return num_of_table; }

void bat::setFirstBatNode() {
    first_bat_node = doc.FirstChildElement("tsduck")->FirstChildElement();
}

void bat::setBouquet() {
    Bouquet bouquet;

    while (first_bat_node=first_bat_node->NextSibling())
    {
        if ( (string) first_bat_node->Value() == "BAT")
        {   
            // Tag 'bouquet_name_descriptor'
            const XMLAttribute* bat_attrs = first_bat_node->ToElement()->FirstAttribute();
            bouquet.id = bat_attrs->Next()->Next()->Value();
            bouquet.name = first_bat_node->FirstChildElement("bouquet_name_descriptor")->FirstAttribute()->Value();
            bouquet.version = bat_attrs->Value();
#ifdef DEBUG
            cout << "BOUQUET: " << bouquet.id << "\t("<< bouquet.name << ")" << "\tVersion: " << bouquet.version<< " \t " << "TS[ ";
#endif 
            // Tag 'transport_stream_id'
            XMLNode* first_ts_node = first_bat_node->FirstChildElement();
            
            vector<transport_stream> v_current_stream;
            while (first_ts_node=first_ts_node->NextSibling())
            {
                transport_stream current_ts;
                XMLElement* transport_stream_e = first_ts_node->ToElement();               
                if ( (string) transport_stream_e->Value() == "transport_stream" ) 
                {
                    // Fill transport_stream_id
                    current_ts.transport_stream_id = transport_stream_e->FirstAttribute()->Value();

                    // Fill generic_descriptor
                    string origin_generic_descriptor = first_ts_node->FirstChildElement("generic_descriptor")->GetText();
                    for (int i=0; i<origin_generic_descriptor.size(); i++ ) {
                        if (origin_generic_descriptor[i] != ' ') {    
                            if (origin_generic_descriptor[i] != '\n') {
                                current_ts.generic_descriptor.push_back(origin_generic_descriptor[i]);
                            }
                        }
                    }

                    v_current_stream.push_back(current_ts);
                }
            }
#ifdef DEBUG            
            for (auto ts:v_current_stream)
                cout << ts.transport_stream_id << ", ";
            cout << "]" << endl;
            for (auto ts:v_current_stream)
                cout << "  "<<ts.transport_stream_id << " [" << ts.generic_descriptor << "]"<< endl;
#endif
            bouquet.tsdata = v_current_stream;
            bouquets.push_back(bouquet);
        }
    }
}

void print (vector<Bouquet> bouquets)
{
    for(auto bouquet:bouquets) {
        cout << "BOUQUET: " << bouquet.id << " (" << bouquet.name << ")" << "\tVer: " << bouquet.version << "\t  ";
        cout << "TS [";
        for (const auto ts:bouquet.tsdata) {
            cout << ts.transport_stream_id << " ";
        }
        cout << "]" << endl;

        for (const auto ts:bouquet.tsdata) {
            cout << "   " << ts.transport_stream_id << "[" << ts.generic_descriptor << "]" << endl;
        }
    }
}

int main()
{
    cout << "====================" << endl;
    bat obj{"bat_sdt.xml"};
    print(obj.getBouquet());

    return 0;
}
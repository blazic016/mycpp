// g++ oop.cpp tinyxml2/tinyxml2.cpp && ./a.out

#include<iostream>
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>


using namespace tinyxml2;
using namespace std;



typedef struct TSData {
    string id;
    string service_name;
    string full_lcn_desc; /* No need */
    vector<string> lcn_desc; /* Each service have own lcn_desc  */
} TSData;

typedef struct BouquetData{
    string name;
    string id;
    string version;
    vector<TSData> tsdata;
} BouquetData;


class bat
{
private:
    XMLDocument doc;
    string xml_filename;
    int num_of_table = 0;
    XMLNode* first_bat_node;
    vector<BouquetData> bouquets;
    void splitDescPerService();
public:
    bat(string fname);
    string getFileName();
    int getNumTable();
    void setNumTable();
    void setBouquetData();
    void setFirstBatNode();
    vector<BouquetData> getBouquetData() {return bouquets;}
};

bat::bat(string fname) : xml_filename {fname} {

    XMLError err = doc.LoadFile( xml_filename.c_str() );
    if (err != XML_SUCCESS) {cout << "[bat] Constructor failed" << endl;}
        // To do: constructor return error code (maybe throw)
    
    bat::setNumTable();
    bat::setFirstBatNode();
    bat::setBouquetData();
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

void bat::setBouquetData() {

    BouquetData bouquet;

    do {
        if ( (string) first_bat_node->Value() == "BAT")
        {   
            // Tag 'bouquet_name_descriptor'
            const XMLAttribute* bat_attrs = first_bat_node->ToElement()->FirstAttribute();
            bouquet.id = bat_attrs->Next()->Next()->Value();
            bouquet.name = first_bat_node->FirstChildElement("bouquet_name_descriptor")->FirstAttribute()->Value();
            bouquet.version = bat_attrs->Value();
            cout << "BOUQUET: " << bouquet.id << "\t("<< bouquet.name << ")" << "\tVersion: " << bouquet.version<< " \t ";

            // Tag 'transport_stream_id'
            XMLNode* first_ts_node = first_bat_node->FirstChildElement();
            TSData current_ts;
            cout << "TS[ ";
            do {
                XMLElement* ts_el = first_ts_node->ToElement();

                if ( (string) ts_el->Value() == "transport_stream" ) {

                    // Fill id
                    current_ts.id = ts_el->FirstAttribute()->Value();

                    // Fill full_lcn_desc
                    string origin_full_lcn_desc = first_ts_node->FirstChildElement("generic_descriptor")->GetText();
                    string filter_full_lcn_desc;
                    for (int i=0; i<origin_full_lcn_desc.size(); i++ ) {
                        if (origin_full_lcn_desc[i] != ' ') {    
                            if (origin_full_lcn_desc[i] != '\n') {
                                /* Fill 'filter_full_lcn_desc' */
                                filter_full_lcn_desc.push_back(origin_full_lcn_desc[i]);
                                /* Fill 'string full_lcn_desc', but it is use only for debug */
                                current_ts.full_lcn_desc.push_back(origin_full_lcn_desc[i]);
                            }
                        }
                    }

                    /* Fill 'vector<string> lcn_desc' */
                    for (size_t i = 0; i < filter_full_lcn_desc.size(); i+=8) {
                        current_ts.lcn_desc.push_back( filter_full_lcn_desc.substr(i,8) );
                    }

                    cout << current_ts.id << ", "; 
                    /* Fill 'struct TSData' */
                     bouquet.tsdata.push_back(current_ts);

                }

            } while (first_ts_node=first_ts_node->NextSibling());
            cout << "]";

            cout << endl;
            bouquets.push_back(bouquet);
        }
    } while (first_bat_node=first_bat_node->NextSibling());
}

void bat::splitDescPerService() {

}

int main()
{
    bat obj{"bat_sdt.xml"};


    cout << "====================" << endl;
    vector bouquets = obj.getBouquetData();
    
    int cnt = 0;
    for(auto bouquet:bouquets) {
        cout << "BOUQUET: " << bouquet.id << " (" << bouquet.name << ")" << "\tVer: " << bouquet.version << " ";
        cout << "TS[ ";
        cout << "size=" << bouquet.tsdata.size() << " ";
        for (auto ts:bouquet.tsdata) {
            cout << ts.id << ", ";
        }
        cout << " ]" << endl;

    }


    cout << "-----------------------------" << endl;
    cout << "Full desc: " << bouquets.at(1).tsdata.at(0).full_lcn_desc <<endl;
    cout << "Desc [0]: " << bouquets.at(1).tsdata.at(0).lcn_desc.at(0) << endl;
    cout << "Desc [1]: " << bouquets.at(1).tsdata.at(0).lcn_desc.at(1) << endl;



    return 0;


}
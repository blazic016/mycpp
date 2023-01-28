// g++ oop.cpp tinyxml2/tinyxml2.cpp && ./a.out

#include<iostream>
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>

using namespace tinyxml2;
using namespace std;

// #define DEBUG

typedef struct transport_stream {
    string transport_stream_id;
    // string generic_descriptor;
    vector<string> tslcns;
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
    vector<string> SplitGenericDescriptor(string gen_desc);
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
                    string filter_generic_descriptor;
                    for (int i=0; i<origin_generic_descriptor.size(); i++ ) {
                        if (origin_generic_descriptor[i] != ' ') {    
                            if (origin_generic_descriptor[i] != '\n') {
                                // current_ts.generic_descriptor.push_back(origin_generic_descriptor[i]); // zakomentarisi
                                filter_generic_descriptor.push_back(origin_generic_descriptor[i]); 
                            }
                        }
                    }

                    current_ts.tslcns = bat::SplitGenericDescriptor(filter_generic_descriptor);
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
vector<string> bat::SplitGenericDescriptor(string gen_desc) {
    vector<string> ret;
    int cnt = 0;
    
    if (gen_desc.size() % 8 != 0) {
        cout << "Greska: Neodgovarajuc deskriptor!" << endl;
        return ret; // size: 0
    }

    for (int i=0;i<gen_desc.size(); i++) {
        if (i == 0) {
            // cout << gen_desc.substr(i,8) << endl;
            ret.push_back(gen_desc.substr(i,8));
        }
        else if (cnt == 8) {
            // cout << gen_desc.substr(i,cnt) << endl;
            ret.push_back(gen_desc.substr(i,cnt));
            cnt = 0;
        }
        cnt++;
    }
    return ret;
}


class ServiceInfo
{
private:
    int ConvertToLcn(std::string str_hex);
    void SetServiceIdLcn(string splitted_gen_desc);
public:
    string bouquet_id;
    string bouquet_name;
    string bouquet_ver;
    string transport_stream_id;
    string service_id;
    string service_name; // TO DO
    int service_lcn;
    ServiceInfo(Bouquet b, string ts, string splitted_gen_desc) : 
    bouquet_id {b.id},
    bouquet_name {b.name},
    bouquet_ver {b.version},
    transport_stream_id {ts}
    {
        // SET: service_id service_lcn
        SetServiceIdLcn(splitted_gen_desc); // TO DO return error
        service_name = "HEHE";
    }

};
int ServiceInfo::ConvertToLcn(std::string str_hex)
{
    int num_h = 0;
    std::istringstream(str_hex) >> std::hex >> num_h;
    std::bitset<10> num_b(num_h);
    int lcn = num_b.to_ullong();
    return lcn;
}
void ServiceInfo::SetServiceIdLcn(string splitted_gen_desc)
{
    if (splitted_gen_desc.size() != 8) 
    {
        cout << "Greska: Neodgovarajuc deskriptor!" << endl;
        service_id= "0";
        service_lcn = 0;
    }
    service_id = splitted_gen_desc.substr(0,4);
    service_lcn = ServiceInfo::ConvertToLcn( splitted_gen_desc.substr(4,8) );
}

void printBouquet (vector<Bouquet> bouquets)
{
    cout << "===================================== ALL BOUQUETS ========================================" << endl;
    for(auto bouquet:bouquets) {
        cout << "BOUQUET: " << bouquet.id << " (" << bouquet.name << ")" << "\tVer: " << bouquet.version << "\t  ";
        cout << "TS [";
        for (const auto ts:bouquet.tsdata) {
            cout << ts.transport_stream_id << " ";
        }
        cout << "]" << endl;
    }
    cout << "=========================================================================================" << endl;

}

vector<ServiceInfo> CreateSinfoObjects(vector<Bouquet> bouquets)
{
    vector<ServiceInfo> sinfos;

    for (auto bouquet:bouquets) {
        for (auto ts_d:bouquet.tsdata) {
            for (auto tslcn:ts_d.tslcns) {
                ServiceInfo sinfo {bouquet, ts_d.transport_stream_id, tslcn};
                sinfos.push_back(sinfo); 
            }
        }
    }
    return sinfos;
}


int main()
{
    bat obj{"bat_sdt.xml"};
    printBouquet(obj.getBouquet());

    vector<ServiceInfo> sinfos = CreateSinfoObjects( obj.getBouquet() );
    

    for (const auto sinfo:sinfos) {
        cout << "bouquet=" << sinfo.bouquet_id << " " << 
        "(" << sinfo.bouquet_name << ") " <<
        "ver=" << sinfo.bouquet_ver << "   " <<
        "ts=" << sinfo.transport_stream_id << "   " <<
        "service_id="<< "0x"<< sinfo.service_id << "  " <<  
        "LCN=" << sinfo.service_lcn << " " <<
        "(" << sinfo.service_name << ")"<< endl;
    }


    
    return 0;
}
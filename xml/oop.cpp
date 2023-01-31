// g++ oop.cpp tinyxml2/tinyxml2.cpp && ./a.out

#include<iostream>
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>

using namespace tinyxml2;
using namespace std;

// Global var
XMLDocument bat_doc;
XMLDocument nit_doc;

string bat_filename = "Nije navedeno";
string nit_filename = "Nije navedeno";

typedef struct transport_stream {
    string transport_stream_id;
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
    string xml_filename {bat_filename};
    int num_of_table = 0;
    vector<Bouquet> bouquets;
    vector<string> SplitGenericDescriptor(string gen_desc);

public:
    bat();
    string getFileName();
    int getNumTable();
    void setNumTable();
    void setBouquet();
    vector<Bouquet> getBouquet() {return bouquets;}
};

bat::bat()
{
    XMLError err = bat_doc.LoadFile( xml_filename.c_str() );
    if (err != XML_SUCCESS) {cout << "[bat] Constructor failed" << endl;}
        // To do: constructor return error code (maybe throw)
    
    bat::setNumTable();
    bat::setBouquet();
}

string bat::getFileName() { return xml_filename; }

void bat::setNumTable() {

    num_of_table = 0;
    XMLNode* node = bat_doc.FirstChildElement("tsduck")->FirstChildElement();

    do
    {
        std::string tag_str( node->Value());
        if(tag_str == "BAT")
            num_of_table++;
    } while((node=node->NextSibling()));

    if (num_of_table == 0) { cout << "No exists bat table!" << endl; }
}

int bat::getNumTable() { return num_of_table; }

void bat::setBouquet() {
    Bouquet bouquet;
    XMLNode* first_bat_node = bat_doc.FirstChildElement("tsduck")->FirstChildElement();

    do
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
            do
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
                    for (size_t i=0; i<origin_generic_descriptor.size(); i++ ) {
                        if (origin_generic_descriptor[i] != ' ') {    
                            if (origin_generic_descriptor[i] != '\n') {
                                filter_generic_descriptor.push_back(origin_generic_descriptor[i]); 
                            }
                        }
                    }

                    current_ts.tslcns = bat::SplitGenericDescriptor(filter_generic_descriptor);
                    v_current_stream.push_back(current_ts);
                }
            } while ((first_ts_node=first_ts_node->NextSibling() ));
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
    } while ((first_bat_node=first_bat_node->NextSibling() ));
}
vector<string> bat::SplitGenericDescriptor(string gen_desc) {
    vector<string> ret;
    int cnt = 0;
    
    if (gen_desc.size() % 8 != 0) {
        cout << "Greska: Neodgovarajuc deskriptor!" << endl;
        return ret; // size: 0
    }

    for (size_t i=0;i<gen_desc.size(); i++) {
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

class TsInfo
{
private:
    string xml_filename {nit_filename};
    string transport_stream_id;
    string frequency;
public:
    // TsInfo();
    string getFrequency() {return frequency;}
    void setFreqency(string tsid);
};

void TsInfo::setFreqency(string tsid) {
    frequency = "NoFreq";

    if (nit_filename == "Nije navedeno")
        return;

    nit_doc.LoadFile( xml_filename.c_str() );
    XMLNode* nit_node = nit_doc.FirstChildElement("tsduck")->FirstChildElement();

    do {
        std::string tag_str( nit_node->Value());
        if(tag_str == "NIT") {
            XMLNode* ts_node = nit_node->FirstChildElement("transport_stream");
            do {
                transport_stream_id = (string) ts_node->ToElement()->FirstAttribute()->Value();
                if (transport_stream_id == tsid) {
                    frequency =  (string)ts_node->FirstChildElement("satellite_delivery_system_descriptor")->FirstAttribute()->Value();
                    // cout << "Frekvencija:" << frequency << endl;
                    return;
                }
            } while( (ts_node = ts_node->NextSibling()) );

        }
    } while( (nit_node=nit_node->NextSibling() ) );

    if (frequency == "NoFreq")
        cout << "Izuzetak: TS " << tsid << " nema frekvenciju!" << endl;
}

class ServiceInfo
{
private:
    int ConvertToLcn(std::string str_hex);
    void SetServiceIdLcn(string splitted_gen_desc);
    void SetServiceName(string ts_id, string s_id);
    void setFrequency();
    TsInfo ts_info;
public:
    string bouquet_id;
    string bouquet_name;
    string bouquet_ver;
    string transport_stream_id;
    string frequency;
    string service_id;
    string service_name;
    int service_lcn;
    ServiceInfo(Bouquet b, string ts, string splitted_gen_desc) : 
    bouquet_id {b.id},
    bouquet_name {b.name},
    bouquet_ver {b.version},
    transport_stream_id {ts}
    {
        SetServiceIdLcn(splitted_gen_desc); // TO DO return error
        SetServiceName(transport_stream_id, service_id);
        setFrequency();
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
void ServiceInfo::SetServiceName(string ts_id, string s_id)
{
    service_name = "Unknown";
    XMLNode* first_node = bat_doc.FirstChildElement("tsduck")->FirstChildElement();
    do
    {
        if ( (string) first_node->Value() == "SDT")
        {
            const XMLAttribute* sdt_attrs = first_node->ToElement()->FirstAttribute();                                                                                          
            string sdt_ver = sdt_attrs->Value();
            string sdt_ts_id = sdt_attrs->Next()->Next()->Value();
            string sdt_actual = sdt_attrs->Next()->Next()->Next()->Next()->Value();

            XMLNode* service_node = first_node->FirstChildElement();
            do
            {
                const XMLAttribute* service_attrs = service_node->ToElement()->FirstAttribute();
                string std_service_id = service_attrs->Value();
                if (sdt_ts_id == transport_stream_id && std_service_id.substr(2,6) == service_id)
                {
                    service_name = service_node->FirstChildElement("service_descriptor")->FirstAttribute()->Next()->Next()->Value();
                }
            } while ( (service_node=service_node->NextSibling()) );

        }
    } while ((first_node=first_node->NextSibling() ));
    if (service_name == "Unknown") {
        cout << "Servis 0x" << service_id << 
        " [ Buket: " << bouquet_id <<  
        ", ts=" << transport_stream_id << 
        "] nema svoje ime!" << endl;
        // TO DO return error code.
    }
}
void ServiceInfo::setFrequency() 
{
    ts_info.setFreqency(transport_stream_id);
    frequency = ts_info.getFrequency();
}


void printBouquet (vector<Bouquet> bouquets)
{
    cout << "===================================== ALL BOUQUETS ========================================" << endl;
    for(auto bouquet:bouquets) {
        cout << "BOUQUET: " << bouquet.id << " (" << bouquet.name << ")" << "\tVer: " << bouquet.version << "\t  ";
        cout << "TS [";
        for (const auto &ts:bouquet.tsdata) {
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


int main(int argc, char** argv)
{

#if 0
    if (argc > 3 || argc == 1)
    {
        cout << "Mora 2 parametra. Prvi: bat_sdt Drugi: nit" << endl;
        return 0;
    }
    else if (argc == 2) {
        cout << "Moze bez drugog parametra (nit tabele), ali neces imati info o frekvenciji.";
        bat_filename = (string) argv[1];
    }
    else if (argc == 3) {
        bat_filename = (string) argv[1];
        nit_filename = (string) argv[2];
    }
#else
        bat_filename = "bat_sdt.xml";
        nit_filename = "nit.xml";
#endif

    cout << "BAT filename: " << bat_filename << endl;    
    cout << "NIT filename: " << nit_filename << endl;

    // bat_filename = "bat_sdt.xml";
    // nit_filename = "nit.xml";

    bat obj;
    printBouquet(obj.getBouquet());
    cout << endl;

    vector<ServiceInfo> sinfos = CreateSinfoObjects( obj.getBouquet() );
    
    cout << endl;
    for (const auto &sinfo:sinfos) {
        cout << "bouquet=" << sinfo.bouquet_id << " " << 
        "(" << sinfo.bouquet_name << ") " <<
        "ver=" << sinfo.bouquet_ver << "   " <<
        "ts=" << sinfo.transport_stream_id << " " <<
        "freq=" << sinfo.frequency << "   " << 
        "service_id="<< "0x"<< sinfo.service_id << "  " <<  
        "LCN=" << sinfo.service_lcn << "  " <<
        "(" << sinfo.service_name << ")"<< endl;
    }

    return 0;
}
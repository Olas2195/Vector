#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>

using namespace std;

struct uczen {
    string imie;
	string nazwisko;
    int numer;
};

class klasa {
	ifstream plik1;
	ofstream plik2;
    vector <struct uczen> spis;
    vector <string> json;
       
    public:
    	klasa();
    	~klasa();
    	
        void wprowadz();
        void zapisJakoJson();        
        bool sprawdzImie(string);
        void wypisz();
    	void zapiszDoPliku();           
};

klasa::klasa() {
	plik1.open("we.txt");
	plik2.open("wy.txt");
}

void klasa::wprowadz() {
	if(plik1.good())
		while(!plik1.eof()) {
			struct uczen wprowadzany;
			
			plik1>>wprowadzany.numer;
			plik1>>wprowadzany.imie;
			plik1>>wprowadzany.nazwisko;
			spis.push_back(wprowadzany);
		}
}

void klasa::zapisJakoJson() {
    for (vector<struct uczen>::iterator it = spis.begin(); it != spis.end(); ++it)
    {
		ostringstream ss;
		ss << it->numer;
		string nr = ss.str();
		
		bool ok;
		string status;
		ok = this->sprawdzImie(it->imie);
		if(ok==false)
			status="error";
		else
			status="ok";
		
        json.push_back("{\"imie\":"+it->imie+",\"nazwisko\":"+it->nazwisko+",\"wiek\":"+nr+",\"status\":"+status+"},\n");

    }
}

bool klasa::sprawdzImie(string Imie) {
	bool ok=false;
	regex wzor("[A-Z]{1}[a-z]+");
	if(regex_match(Imie, wzor)) {
		ok=true;
	}
	return ok;
}

void klasa::wypisz() {
	cout<<"[\n";
	for (int i = 0; i < json.size(); i++) {
    	cout<<json[i];
	}
	cout<<"]";
}

void klasa::zapiszDoPliku() {
	plik2<<"[\n";
	for (int i = 0; i < json.size(); i++) {
    	plik2<<json[i];
	}
	plik2<<"]";
}

klasa::~klasa() {
	plik1.close();
	plik2.close();
}

int main(int argc, char** argv) {
    klasa TP;
    TP.wprowadz();
    TP.zapisJakoJson();
    TP.wypisz();
    TP.zapiszDoPliku();
    return 0;
}

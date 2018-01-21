#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <string_view>
#include <iomanip>
#include <stdio.h>


//Ein Produkt muss einen Namen und einen Preis haben, die Anzahl ist defaultmäßig bei 1 und kann bei Bedarf geändert werden.
struct Produkt{
	public:
		Produkt();
		void writeProduktInfo(int counter);
	
		std::string produktname{};
		double preis = 0.0;
		int anzahl = 0;
		double gesamtPreis = 0.0;
};
Produkt::Produkt(){
	std::cout << "Gib den Namen des Produktes ein" << std::endl;
	std::getline(std::cin, produktname);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Gib den Preis des Produktes ein in der Form xxxx.yy EUR" << std::endl;
	std::cin >> preis;
	std::cin.clear();
	std::cout << "Gib die Anzahl der verkaufte Produkte ein" << std::endl;
	std::cin >> anzahl;
	std::cin.clear();
	gesamtPreis = preis * (double) anzahl;
}

void Produkt::writeProduktInfo(int counter){
	std::ofstream produktinfo;
	produktinfo.open("Produkte.csv", std::ios::app);
	produktinfo << counter <<" " <<this->produktname<< " "<< this->anzahl<< " " << this->preis << " " << this->gesamtPreis << std::endl;
	produktinfo.close();
}

//Ein Kunde muss Namen und vollständige Adresse haben, optional ist eine Lieferadresse.
struct Kundendaten{
	public:
	Kundendaten();
	Kundendaten(std::string name, std::string strasse, std::string ort); 
	std::string name{};
	std::string strasse{};
	std::string ort{};
	std::string firma{};
	std::string firmastrasse{};
	std::string firmaort{};
	bool hasLieferadresse = false;
	void setFirmendaten(std::string firma, std::string firmastrasse, std::string firmaort);
};
Kundendaten::Kundendaten(){
	std::cerr << "Ein Kunde braucht Namen, Straße und Ort." <<std::endl;
}
Kundendaten::Kundendaten(std::string name, std::string strasse, std::string ort){
	name = name;
	strasse = strasse;
	ort = ort;
}
void Kundendaten::setFirmendaten(std::string firma, std::string firmastrasse, std::string firmaort){
	this->firma = firma;
	this->firmastrasse = firmastrasse;
	this->firmaort = firmaort;
	this->hasLieferadresse = true;
}

//Mit der RechnungsTemplate.tex und den gemachten Eingaben wird eine Rechnung im .pdf Format gemacht, die den Namen des Empfängers trägt.
void erstellePDF(Kundendaten *kunde){
	std::string befehl = "texfot --ignore '(Warning|Overfull|Underfull)' xelatex --interaction=nonstopmode --jobname=tabea '\\def\\name{";
	befehl.append(kunde->name);
	befehl.append("} \\def\\strasse{");
	befehl.append(kunde->strasse);
	befehl.append("} \\def\\ort{");
	befehl.append(kunde->ort);
	if( true == kunde->hasLieferadresse){
		befehl.append("} \\def\\firmaname{");
		befehl.append(kunde->firmaort);
		befehl.append("} \\def\\firmastrasse{");
		befehl.append(kunde->firmastrasse);
		befehl.append("} \\def\\firmaort{");
		befehl.append(kunde->firmaort);
		befehl.append("} \\input{RechnungsTemplate.tex}'");
	}
}

template <typename T> T getInput(const std::string_view output){
	std::cin.ignore(std::numeric_limits<std::streamsize>::max());
	std::cout <<output << std::endl;
	T eingabe;
	std::cin >> eingabe;
	return eingabe;
}

int main(){
	// In den richtigen Ordner wechseln.
	system("cd /mnt/c/Users/tabea/Desktop/Rechnung_Excel_Latex");
	int produktCounter = 0;
	double gesamtPreis = 0.0;
	int weiter{};
	//Alle Produkte für die Rechnung eingeben.
	do{
		produktCounter += 1;
		Produkt * p = new Produkt();
		p->writeProduktInfo(produktCounter);
		gesamtPreis += p->preis;
		std::cout << "möchtest du weitermachen? dann gib eine zahl ungleich 0 ein" << std::endl;
		std::cin >> weiter;
		std::cout << weiter << std::endl;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		std::fflush(stdin);
	} while ( 0 != weiter );
   
	//Endwerte der Rechnung in Datei schreiben
	std::ofstream gesamt;
	gesamt.open("Rechnung.csv");
	gesamt << gesamtPreis << std::endl << gesamtPreis*0.19 << std::endl << gesamtPreis*1.19;
	gesamt.close();
    	return 0;
}

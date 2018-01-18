#include <iostream>
#include <fstream>
#include <string>

//Ein Produkt muss einen Namen und einen Preis haben, die Anzahl ist defaultmäßig bei 1 und kann bei Bedarf geändert werden.
struct Produkt{
	public:
		Produkt();
		void writeProduktInfo(Produkt p, int counter);
	private:
		std::string produktname{};
		double preis = 0.0;
		int anzahl = 0;
		double gesamtPreis = 0.0;
};
Produkt::Produkt(){
	std::cout << "Gib den Namen des Produktes ein" << std::endl;
	std::getline(std::cin, produktname);
	std::cout << "Gib den Preis des Produktes ein in der Form xxxx.yy EUR" << std::endl;
	std::cin >> preis;
	std::cout << "Gib die Anzahl der verkauften Produkte ein" << std::endl;
	std::cin >> anzahl;
	gesamtPreis = preis * (double) anzahl;
}

void Produkt::writeProduktInfo(Produkt p, int counter){
	std::fstream produktinfo;
	produktinfo.open("Produkte.csv", ios::out||ios::app);
	produktinfo << counter <<" " <<p.name<< " "<< p.anzahl<< " " << p.preis << " " << p.gesamtPreis << std::endl;
}

//Ein Kunde muss Namen und vollständige Adresse haben, optional ist eine Lieferadresse.
struct Kundendaten{
	public:
	kundendaten();
	kundendaten(std::string name, std::string strasse, std::string ort);
	private: 
	std::string name{};
	std::string strasse{};
	std::string ort{};
	std::string firma{};
	std::string firmastrasse{};
	std::string firmaort{};
	bool hasLieferadresse = false;
	setFirmendaten(std::string firma, std::string firmastrasse, std::string firmaort);
	deleteFirmendaten();
};
Kundendaten::kundendaten(){
	std::cerr << "Ein Kunde braucht Namen, Straße und Ort." <<endl;
}
Kundendaten::kundendaten(std::string name, std::string strasse, std::string ort){
	name = name;
	strasse = strasse;
	ort = ort;
}
Kundendaten::setFirmendaten(std::string firma, std::string firmastrasse, std::string firmaort, Kundendaten *k){
	k.firma = firma;
	k.firmastrasse = firmastrasse;
	k.firmaort = firmaort;
	k.hasLieferadresse = true;
}
Kundendaten::deleteFirmendaten(Kundendaten * k){
	k.firma{};
	k.firmastrasse{};
	k.firmaort{};
	k.hasLieferadresse = false;
}
std::string Kundtendaten::getName(){
	return Kundendaten.name;
}
std::string Kundendaten::getStrasse(){
	return Kundendaten.strasse;
}
std::string Kundendaten::getOrt(){
	return Kundendante.ort;
}
std::string Kundendaten::getFirma(){
	return Kundendaten.Firma;
}
std::string Kundendaten::getFirmenstrasse(){
	return Kundendaten.firmastrasse;
}
std::string Kundendaten::getFirmenort(){
	return Kundendaten.firmaort;
}

//Mit der RechnungsTemplate.tex und den gemachten Eingaben wird eine Rechnung im .pdf Format gemacht, die den Namen des Empfängers trägt.
void erstellePDF(Kundendaten *kunde){
	std::string befehl = "texfot --ignore '(Warning|Overfull|Underfull)' xelatex --interaction=nonstopmode --jobname=tabea '\\def\\name{";
	befehl.append(kunde.name);
	befehl.append("} \\def\\strasse{");
	befehl.append(kunde.strasse);
	befehl.append("} \\def\\ort{");
	befehl.append(kunde.ort);
	if( true == kunde.hasLieferadresse){
		befehl.append("} \\def\\firmaname{");
		befehl.append(kunde.firmaort);
		befehl.append("} \\def\\firmastrasse{");
		befehl.append(kunde.firmastrasse);
		befehl.append("} \\def\\firmaort{");
		befehl.append(kunde.firmaort);
		befehl.append("} \\input{RechnungsTemplate.tex}'")
	}
}

int main(){
	// In den richtigen Ordner wechseln.
	system("cd \\mnt\\C:\\Users\\tabea\\Desktop\\Rechnung_Excel_Latex");
	int produktCounter = 0;
	double gesamtPreis = 0.0;
	//Alle Produkte für die Rechnung eingeben.
	do{
		++produktCounter;
		Produkt * p = Produkt::Produkt();
		Produkt::writeProduktInfo(*p);
		gesamtPreis += *p.preis;
		std::cout << "möchtest du weitermachen? dann gib eine zahl ungleich 0 ein" << std::endl;
		std::cin >> weiter;

	} while ( weiter != 0);
   
	//Endwerte der Rechnung in Datei schreiben
	std::fstream gesamt;
	gesamt.open("Rechnung.csv", std::ios::out);
	gesamt >> gesamtPreis >> "\n" >> gesamtPreis*0.19 >> "\n" >> gesamtPreis*1.19;
	gesamt.close();
	produktdaten();
    return 0;
}
#include <iostream>
#include <fstream>


//Wichtig: Bei Ordnerangaben müssen immer doppelte Backslahs stehen
//char ordner="C:\\Users\\tabea\\Desktop\\Rechnung_Excel_Latex\\";
//char ausgabeordner=ordner;

//void verkaufteProdukte();
//void rechnung_PDF(char name);

int main (){
	
	system("cd C:\\Users\\tabea\\Desktop\\Rechnung_Excel_Latex");
	system("xelatex -jobname=m -quiet -interaction=nonstopmode -shell-escape RechnungsTemplate.tex >/dev/null");

	return 0;

}

/*Funktion, die aus den Dateien eine Rechnung erstellt
//void rechnung_PDF(string name){
	//system("cd ordner");
	//system("xelatex -quiet -jobname=ausgabeordner+name RechnungsTemplate.tex");
}*/

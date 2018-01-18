#include <iostream>
#include <fstream>
#include <string>
int main(){
   
    std::string testname = "tabea";
   std::string befehl = "texfot --ignore '(Warning|Overfull|Underfull)' xelatex --interaction=nonstopmode --jobname=tabea '\\def\\name{";
   befehl.append(testname);
   befehl.append("} \\def\\strasse{t} \\def\\ort{u} \\input{RechnungsTemplate.tex}'");
   
	system(befehl.c_str());
}
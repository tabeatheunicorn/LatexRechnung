@echo on
set /A counter=0
set /A gesamtnetto=0
echo Gib das erste Produkt der Rechnung ein:
goto eingabe

:eingabe
set /p produktname=Produktname: 
set /p anzahl=Anzahl der verkauften Produkte: 
set /p preis=Einzelpreis des Produkts in ct: 
set /p richtig=Alles richtig? (y/n):
if "%richtig%"=="n" goto eingabe
if "%richtig%"=="y" (
set /A gesamtpreis = %anzahl%*%preis%
set /A gesamtnetto = %gesamtnetto%+%gesamtpreis%
goto ineurowandeln)

:ineurowandeln
set /A gesamtnetto = %gesamtnetto%+%gesamtpreis%
set /A counter=%counter%+1
set /A euro=%preis%/100
set /A cent=%preis%-(%euro%*100)
set /A gesamteuro=%gesamtpreis%/100
set /A gesamtcent=%gesamtpreis%-(%gesamteuro%*100)
echo %counter% %produktname% %anzahl% %euro%,%cent% %gesamteuro%,%gesamtcent% >> C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Produkte.csv
goto abfrage

:abfrage
set /p mehr=Möchtest du noch ein Produkt eingeben? (y/n): 
if "%mehr%"=="y" (goto eingabe)
if "%mehr%"=="n" (goto :auswerten)

:auswertenGesamt
set /a mwst=%gesamtnetto%*19
set /a gesamtbrutto=%mwst%+%gesamtnetto%

:kundendatenAufnehmen
set /p name=Kundenname:
set /p strasse=Straße und Hausnummer:
set /p ort=PLZ und Ort:
set /p rechnungsname=Welchen Namen soll die pdf-Datei haben?:
set /p bild=Speicherort des Logos:

:pdfErstellen
echo Gesamtnetto&%gesamtnetto% >> C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Gesamt.csv
echo zzgl. MwSt.&%mwst% >> C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Gesamt.csv
echo Gesamtbrutto&%gesamtbrutto% >> C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Gesamt.csv
xelatex -jobname=%rechnungsname% -quiet "\def\name{%name%} \def\adresse{%strasse%\\%ort%} \def\fromlogo{\includegraphics{%bild%}}\input{C:/Users/tabea/Desktop/Rechnung_Excel_Latex/RechnungsTemplate.tex}"
del C:\Users\tabea\Desktop\Rechnung_Excel_Latex\*.aux
del C:\Users\tabea\Desktop\Rechnung_Excel_Latex\*.log
goto tabellezurueck

:tabellezurueck
echo Pos. Produktname Anz. Stückpreis Gesamtpreis > C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Produkte.csv
echo > C:\Users\tabea\Desktop\Rechnung_Excel_Latex\Rechnung_Produkte.csv
pause
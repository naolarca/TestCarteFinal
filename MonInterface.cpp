/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include <iostream>
#include <math.h>
#include <fstream>
#include <string.h>
#include "MonInterface.h"
#include "CommunicationFPGA.h"
#include "Vecteur.cpp"
#include "Vecteur.h"

using namespace std;

enum Registre { SW = 8, BTN = 9, LD = 10, AN0 = 11, AN1 = 12, AN2 = 13, AN3 = 14 };
string mode = { "file" };
string etat = { "neutre" };
CommunicationFPGA fpga;
Vecteur<DonneesTest> NewArchive;
int increment = 1;




string hexEnBinaire(int nombre) {
	string r;
	while (nombre != 0) {
		r+= (nombre % 2 == 0 ? '0' : '1');
		nombre /= 2;
	}
	return r;
}

//***********************************************************************************************************************************
//COMMUNICATION CARTE FPGA
int Communication() {
		int val;

		if (!fpga.estOk())
		{
			cout << fpga.messageErreur() << endl;
			return 1;
		}

		if (!fpga.lireRegistre(SW, val))
		{
			cout << fpga.messageErreur() << endl;
			return 1;
		}
		int valeurSwitch = val;
		
		return valeurSwitch;
}

//***********************************************************************************************************************************
//INITIALISATION INTERFACE CARTE
MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{

	donnee.typeTest = 1;
	donnee.registreSW = SW;
	donnee.retourSW = 1;

	donnee.registreLD = LD;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	fpga.ecrireRegistre(10, 0);

	resetTest();
	resetArchive();
}

//***********************************************************************************************************************************
//LES 3 TESTS
void MonInterface::testSuivant()
{

	int valSw;
	fpga.lireRegistre(8, valSw);
	string BinValSw = hexEnBinaire(valSw);
	int longueurBinSw = BinValSw.length();
	int ledsConsecutives = 0;
	donnee.retourSW = valSw;
	donnee.etatSW = valSw;

	



	/***************************************************************************************************************************************************************/
	//TEST 1
	if (donnee.typeTest > 3) {
		donnee.typeTest = 1;
	}

	if (donnee.typeTest == 1){
		donnee.valeurLD = valSw;
		donnee.etatLD = valSw;

	}

	/*************************************************************************************************************************/
	//TEST 2
	if (donnee.typeTest == 2) {
		int parite = 0;
		for (int i = 0; i < longueurBinSw; i++) {
			if (BinValSw[i] == '1')
				parite++;
		}

		if (parite % 2 == 1) {
			donnee.valeurLD = 0x00; 
			donnee.etatLD = 0x00;

		}

		else {
			donnee.valeurLD = 0xFF;
			donnee.etatLD = 0xFF;

		}

	}

	/*******************************************************************************************************************/
	//TEST 3
	if (donnee.typeTest == 3) {
		ledsConsecutives = log2(valSw + 1);
		donnee.valeurLD = pow(2,ledsConsecutives) - 1;
		donnee.etatLD = donnee.valeurLD;

	}

	setTest(donnee);
	fpga.ecrireRegistre(10, donnee.etatLD);

	if (etat == "demarrer") {
		if (mode == "file")
		{
			NewArchive.AjoutFile(donnee);
			NewArchive.operator++();
			setArchive(donnee);
			setArchive(increment, increment);
		}
		else {
			if (NewArchive.AfficherPosition() == 0) {
				NewArchive.operator++();
			}
			NewArchive.AjoutPile(donnee); 
			setArchive(donnee);
			setArchive(1, increment);
		}

			increment++;
			
		
	}

	
	donnee.typeTest++;



}


//***********************************************************************************************************************************
//LARCHIVE!!!!!
void MonInterface::demarrer() {
	
	etat = "demarrer";
	message("Archive Activee");

}

void MonInterface::arreter() {
	etat = "arreter";
	message("Archive Arretee");

}

void MonInterface::vider() {
	
	NewArchive.Vider();
	message("Archive videe");
	increment = 1;
	resetArchive();
	resetTest();

}

void MonInterface::modeFile() {
	
	if(NewArchive.AfficherSiVide()){
		mode = "file";
		message("Mode File");
	}

	else message("Mode inchange");
}

void MonInterface::modePile() {
	
	if (NewArchive.AfficherSiVide()) {
		mode = "pile";
		message("Mode Pile");
	}

	else message("Mode inchange");
}

void MonInterface::premier() {
	while (NewArchive.AfficherPosition() != 1) {
		NewArchive.operator--();
	}
	setArchive(NewArchive.operator[](NewArchive.AfficherPosition() - 1));
	setArchive(NewArchive.AfficherPosition(), increment - 1);

}

void MonInterface::dernier() {
	while (NewArchive.AfficherPosition() != NewArchive.AfficherTaille()) {
		NewArchive.operator++();
	}
	setArchive(NewArchive.operator[](NewArchive.AfficherPosition() - 1));
	setArchive(NewArchive.AfficherPosition(), increment - 1);

}

void MonInterface::precedent() {
	
	NewArchive.operator--();
	setArchive(NewArchive.operator[](NewArchive.AfficherPosition()-1));
	setArchive(NewArchive.AfficherPosition(), increment-1);

}

void MonInterface::suivant() {
	
	NewArchive.operator++();
	setArchive(NewArchive.operator[](NewArchive.AfficherPosition() - 1));
	setArchive(NewArchive.AfficherPosition(), increment - 1);
}

void MonInterface::sauvegarder(char* nomFichier) {
	fstream myFile;
	myFile.open(nomFichier, ios_base::out);
	myFile << NewArchive << endl;
	myFile.close();

}
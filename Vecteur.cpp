/********
 * Fichier: Vecteur.cpp
 * Auteurs: Naomie L'Archevêque-Carrière
 * Date: 16 janvier 2021 (creation)
 * Description: Implementation des methodes de la classe decrite dans
 *    vecteur.h.
********/
#include "Vecteur.h"
#include "VisiTest.h"

template <typename T>
Vecteur <T>::Vecteur() {
	
	position=0;
	taille = 0;
	capacite = 8;
	tableau = new T[capacite];

}

template <typename T>
Vecteur<T>::~Vecteur() {

}

template <typename T>
int Vecteur<T>::AfficherCapacite() {
	return capacite;
}

template <typename T>
int Vecteur<T>::AfficherTaille() {
	return taille;
}

template <typename T>
int Vecteur<T>::AfficherPosition() {
	return position;
}

template <typename T>
void Vecteur<T>::AugmentationCapacite() {
	
	T *temporaire= new T[capacite*2];

	for (int i = 0; i < capacite*2; i++) {
		temporaire[i] = tableau[i];
	}

	delete[] tableau;

	capacite *= 2;
	tableau = temporaire;
}


template <typename T>
bool Vecteur<T>::AfficherSiVide() {

	if (taille == 0) return true;
	return false;
}

template <typename T>
void Vecteur<T>::Vider() {
	if (taille != 0) {
		taille = 0;
	}
	if (position != 0) {
		position = 0;
	}
}


template <typename T>
bool Vecteur<T>::AjoutPile(T newElement) {

	if (taille >= capacite) {
		AugmentationCapacite();
	}

	if (taille >= capacite)
		AugmentationCapacite();

	if (taille > 0) {
		for (int i = taille; i >= 1; i--)
		{
			tableau[i] = tableau[i - 1];

		}
	}

	tableau[0] = newElement;
	taille++;
	return true;
}

template <typename T>
bool Vecteur<T>::AjoutFile(T newElement) {

	if (taille >= capacite) {
		AugmentationCapacite();
	}

	tableau[taille] = newElement;
	taille++;

	return true;
}


template <typename T>
void Vecteur<T>::RetraitElement() {
	T* temporaire = new T[capacite];

	if (taille > 0) {
		for (int i = 0; i < taille; i++) {
			if (i + 1 < capacite) {
				tableau[i] = tableau[i+1];
			}

		}
	}
	taille--;
}

template <typename T>
T Vecteur<T>::valeurElement() {
	return tableau[position];
}

template<class T>
T Vecteur<T>::operator [](int index)
{
	return tableau[index];
}

template <class T>
void Vecteur<T>::operator +=(const T& valeur)
{
	ajoutFile(valeur);
}

template<class T>
void Vecteur<T>::operator --()
{
	
	if (position >1)
		position--;
	
}

template <class T>
void Vecteur<T>::operator ++()
{
	if (position<taille)
		position++;
	
}


ostream &operator <<(ostream& output, Vecteur<DonneesTest>& tableau){
	
	for (int i = 0; i < tableau.AfficherTaille(); i++)
	{
		output << "Type Test: " << tableau[i].typeTest << endl;
		output << "Adresse switches " << tableau[i].registreSW << endl;
		output << "Retour switches: " << tableau[i].retourSW << endl;
		output << "Etat switches: " << tableau[i].etatSW << endl;
		output << "Adresse leds: " << tableau[i].registreLD << endl;
		output << "Valeur leds: " << tableau[i].valeurLD<< endl;
		output << "Etat leds: " << tableau[i].etatLD << endl;
		output << "\n";
	}

	return output;
}
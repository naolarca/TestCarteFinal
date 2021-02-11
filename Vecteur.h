/********
 * Fichier: vecteur.h
 * Auteurs: Naomie L'Archevêque-Carrière
 * Date: 20 fevrier 2021 (creation)
 * Description: Declaration de la classe vecteur
********/

#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>

using namespace std;

template <typename T>
class Vecteur
{
public:
    Vecteur();
    ~Vecteur();
    int AfficherCapacite();
    int AfficherTaille();
    int AfficherPosition();
    void AugmentationCapacite();
    bool AfficherSiVide();
    void Vider();

    bool AjoutPile(T newElement);
    bool AjoutFile(T newElement);
    void RetraitElement();
    T valeurElement();

    void operator +=(const T& valeur);
    void operator --();
    void operator ++();
    T operator [](int index);

    friend ostream& operator<<(ostream& output, Vecteur<DonneesTest>& tableau);
private:
    int taille;
    int capacite;
    T* tableau;
    int position;

};

#endif
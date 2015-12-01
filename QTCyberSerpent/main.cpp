/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include <iostream>
#include <fstream>
#include "CyberSerpent.h"

int main(int argc, char *argv[])
{
   std::ofstream myfile("log.txt", std::ios::out | std::ios::app | std::ios::binary);
   std::clog.rdbuf(myfile.rdbuf());

   std::unique_ptr<CyberSerpent> jeu = CyberSerpent::Creer_CyberSerpent(argc, argv);

   jeu->Afficher();
}
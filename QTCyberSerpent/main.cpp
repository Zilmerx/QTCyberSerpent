/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include "CyberSerpent.h"

int main(int argc, char *argv[])
{
   std::unique_ptr<CyberSerpent> jeu = CyberSerpent::Creer_CyberSerpent(argc, argv);

   jeu->Afficher();
}
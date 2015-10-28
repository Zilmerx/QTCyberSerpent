/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include "CyberSerpent.h"

using namespace std;

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void abort()
{
   std::cout << "aborting" << std::endl; // put break here...
   exit(-1);
}

int main(int argc, char *argv[])
{

   CyberSerpent jeu{ argc , argv };

   jeu.Initialize();

   jeu.Afficher();
}
/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include "CyberSerpent.h"

using namespace std;

int main(int argc, char *argv[])
{
   CyberSerpent jeu{ argc , argv, "image.bmp" };

   jeu.Initialize();

   jeu.Start();
}
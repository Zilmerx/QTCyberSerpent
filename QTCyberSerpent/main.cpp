/*
Cree par Jean-Philippe Doyon,

Le 15 Septembre 2015.
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "DoubleBuffer.h"
#include "CyberSerpent.h"


int main(int argc, char *argv[])
{
   CyberSerpent jeu{ argc , argv };

   jeu.Initialize();

   jeu.Start();
}
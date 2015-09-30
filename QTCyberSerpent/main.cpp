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

   int Herp = 10;
   int Derp = 20;
   DoubleBuffer<int> db = DoubleBuffer<int>();
   db.Set(Herp);

   db.Switch();

   db.Set(Derp);

   int DURR = db.Get();
   db.Switch();
   int HURR = db.Get();


   //CyberSerpent jeu{ argc , argv };

   //jeu.Initialize();

   //cv::Mat image;
   //image = cv::imread("image.bmp", CV_LOAD_IMAGE_COLOR);   // Read the file

   //if (!image.data)                              // Check for invalid input
   //{
   //   jeu.m_QTCyberSerpent.Error("Erreur de lecture d'image");
   //}                                                                                                                                      

   //jeu.m_QTCyberSerpent.putImage(image);

   //jeu.Start();

   //jeu.m_QTCyberSerpent.Error("Erreur de lecture d'image");
}
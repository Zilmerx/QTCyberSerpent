#pragma once

#include <functional>
#include <vector>
#include <thread>
#include <memory>
#include <atomic>

/*
KeyboardReader.

Permet d'executer une, ou une serie de fonction au moment de l'activation d'une touche.
*/

// Valeurs de retour pour le clavier a utiliser pour la fonction addFunction(..).
// https://msdn.microsoft.com/en-us/library/aa299374(VS.60).aspx

class KeyboardReader
{
   // Tableau de tableau de fonctions. KeyPressCallbackList[0] retourne la fonction devant s'executer lorsque quelqu'un pese sur le caractere #1 du clavier.
   std::vector<std::function<void(void)>> m_CallbackList;

   // Thread faisant rouler la fonction privee callFuncOnKeyPress.
   std::thread m_Thread;
   // True == Il y a un thread au bout de m_Thread.
   bool m_ThreadIsRunning;
   // True == Le thread a le droit de continuer a rouler, et n'a pas besoin de s'arreter.
   std::atomic<bool> m_RunThread;

public:

   const static int MINKEYVALUE = 1;
   const static int MAXKEYVALUE = 83;

   // Debuter / Arreter la detection de touches
   void start();
   void stop();

   // Gerer les fonctions a callback
   void setFunction(int keyValue, std::function<void(void)> func);
   void clearFunction(int keyValue);

   KeyboardReader();
   ~KeyboardReader();

private:

   static void validateKeyValue(int& keyValue);

   void callFuncOnKeyPress() const;

   int waitForKeypress() const;

   void executeKeyValue(int keyValue) const;


};
#include <conio.h>
#include "KeyboardReader.h"

// PUBLIC

#pragma region Constructeur / Destructeur
KeyboardReader::KeyboardReader()
	: m_RunThread{ false },
	m_ThreadIsRunning{ false },
	m_Thread{},
	m_CallbackList((KeyboardReader::MAXKEYVALUE - KeyboardReader::MINKEYVALUE))
{
}

KeyboardReader::~KeyboardReader()
{
   stop();
}
#pragma endregion

#pragma region Debuter / Arreter la detection de touches
void KeyboardReader::start()
{
   if (!m_ThreadIsRunning)
   {
      m_RunThread = true;
      m_Thread = std::thread(&KeyboardReader::callFuncOnKeyPress, this);
      m_ThreadIsRunning = true;
   }
}

void KeyboardReader::stop()
{
   m_RunThread = false;
   try
   {
      m_Thread.join();
   }
   catch (...)
   {
   }
   m_ThreadIsRunning = false;
}
#pragma endregion

#pragma region Gerer les fonctions
void KeyboardReader::setFunction(int keyValue, std::function<void(void)> func)
{
   validateKeyValue(keyValue);
   m_CallbackList[keyValue - MINKEYVALUE] = func;
}

void KeyboardReader::clearFunction(int keyValue)
{
   validateKeyValue(keyValue);
   m_CallbackList[keyValue - MINKEYVALUE] = nullptr;
}
#pragma endregion

// PRIVATE

void KeyboardReader::validateKeyValue(int& keyValue)
{
   if (keyValue < MINKEYVALUE)
   {
      keyValue = MINKEYVALUE;
   }
   else if (keyValue > MAXKEYVALUE)
   {
      keyValue = MAXKEYVALUE;
   }
}

void KeyboardReader::callFuncOnKeyPress() const
{
   while (m_RunThread)
   {
      int val = waitForKeypress();

      if (val != -1)
         executeKeyValue(val);
   }
}

// -1 == m_RunThread est tombé à false.
int KeyboardReader::waitForKeypress() const
{
   int c = 0;

   do
   {
      if (!m_RunThread)
      {
         c = -1;
         break;
      }

      if (_kbhit())
      {
         c = _getch();
      }
   } while (c == 224 || c == 0); // _getch() retourne (0 ou 224), puis la valeur de la touche du clavier. Nous n'avons pas besoin de la premiere information.

   return c;
}

void KeyboardReader::executeKeyValue(int keyValue) const
{
   if (m_CallbackList[keyValue - MINKEYVALUE] != nullptr)
   {
      m_CallbackList[keyValue - MINKEYVALUE]();
   }
}
#pragma once

// PRIS DE CETTE SOURCE.
// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-copyable_Mixin

template <class T>
class NonCopyable
{
protected:
   NonCopyable() {}
   ~NonCopyable() {} // Protected non-virtual destructor
private:
   NonCopyable(const NonCopyable &);
   NonCopyable & operator = (const NonCopyable &);
};
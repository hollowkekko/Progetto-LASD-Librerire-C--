#include <iostream>
#include <limits>

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"


using namespace std;

/* ************************************************************************** */

  void mytestVectorInt(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<int>:" << endl;
  try
  {
    {
      lasd::SortableVector<int> vec;
      Empty(loctestnum, loctesterr, vec, true);

      GetFront(loctestnum, loctesterr, vec, false, 0);
      GetBack(loctestnum, loctesterr, vec, false, 0);
      SetAt(loctestnum, loctesterr, vec, false, 1, 0);
      GetAt(loctestnum, loctesterr, vec, false, 2, 0);

      Exists(loctestnum, loctesterr, vec, false, 0);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
    }
    {
      lasd::SortableVector<int> vec(3);
      Empty(loctestnum, loctesterr, vec, false);
      Size(loctestnum, loctesterr, vec, true, 3);

      SetAt(loctestnum, loctesterr, vec, true, 0, 10);
      SetAt(loctestnum, loctesterr, vec, true, 1, 20);
      SetAt(loctestnum, loctesterr, vec, true, 2, 30);

      GetFront(loctestnum, loctesterr, vec, true, 10);
      GetBack(loctestnum, loctesterr, vec, true, 30);

      SetFront(loctestnum, loctesterr, vec, true, 5);
      SetBack(loctestnum, loctesterr, vec, true, 4);

      Exists(loctestnum, loctesterr, vec, true, 20);

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 29);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 400);

      vec.Sort();

      TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
      TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

      vec.Resize(2);
      FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 20);
      
    }
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<int>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
  }

/* ************************************************************************** */

void mytestVectorDouble(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<double>:" << endl;
  try
  {
    lasd::SortableVector<double> vec(3);
    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 3);

    SetAt(loctestnum, loctesterr, vec, true, 0, 10.0);
    SetAt(loctestnum, loctesterr, vec, true, 1, 20.0);
    SetAt(loctestnum, loctesterr, vec, true, 2, 30.0);

    GetFront(loctestnum, loctesterr, vec, true, 10.0);
    GetBack(loctestnum, loctesterr, vec, true, 30.0);

    Exists(loctestnum, loctesterr, vec, true, 30.0);

    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 2.0, 62.0);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 2.0, 12000.0);

    vec.Sort();

    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
    TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

    vec.Resize(2);
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1, 200);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<double>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestVectorString(unsigned int &testnum, unsigned int &testerr)
{
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl
       << "Inizio del test Vector<string>:" << endl;
  try
  {
    lasd::SortableVector<string> vec(2);

    Empty(loctestnum, loctesterr, vec, false);
    Size(loctestnum, loctesterr, vec, true, 2);

    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));

    GetFront(loctestnum, loctesterr, vec, true, string("X"));
    GetBack(loctestnum, loctesterr, vec, true, string("Y"));

    Exists(loctestnum, loctesterr, vec, true, string("Y"));

    MapPreOrder(loctestnum, loctesterr, vec, true, [](string &str)
                { MapStringAppend(str, string(" ")); });
    TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
    FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XX Y "));
    FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XY X "));

    Exists(loctestnum, loctesterr, vec, false, string("Y"));

    lasd::SortableVector<string> copvec(vec);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    MapPreOrder(loctestnum, loctesterr, vec, true, [](string &str)
                { MapStringAppend(str, string("!")); });
    NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

    copvec = std::move(vec);
    FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?X !Y !"));

    lasd::SortableVector<string> movvec(std::move(vec));
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?X Y "));
    movvec.Sort();
    FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?X Y "));
    SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
    vec.Resize(1);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("Y"));

    movvec.Clear();
    Empty(loctestnum, loctesterr, movvec, true);
  }
  catch (...)
  {
    loctestnum++;
    loctesterr++;
    cout << endl
         << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector<string>! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestListInt(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test List<int>:" << endl;
  try {
    lasd::List<int> lst;
    Empty(loctestnum, loctesterr, lst, true);
    Size(loctestnum, loctesterr, lst, true, 0);

    GetFront(loctestnum, loctesterr, lst, false, 0);
    GetBack(loctestnum, loctesterr, lst, false, 0);

    Exists(loctestnum, loctesterr, lst, false, 0);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

    RemoveFromFront(loctestnum, loctesterr, lst, false);
    FrontNRemove(loctestnum, loctesterr, lst, false, 0);

    InsertAtBack(loctestnum, loctesterr, lst, true, 50);
    InsertAtFront(loctestnum, loctesterr, lst, true, 40);
    InsertAtFront(loctestnum, loctesterr, lst, true, 30);
    InsertAtBack(loctestnum, loctesterr, lst, true, 20);
    InsertAtFront(loctestnum, loctesterr, lst, true, 10);

    GetFront(loctestnum, loctesterr, lst, true, 10);
    GetBack(loctestnum, loctesterr, lst, true, 20);
    SetFront(loctestnum, loctesterr, lst, true, 30);
    SetBack(loctestnum, loctesterr, lst, true, 20);

    GetAt(loctestnum, loctesterr, lst, true, 3, 50);
    SetAt(loctestnum, loctesterr, lst, true, 3, 35);

    Exists(loctestnum, loctesterr, lst, false, 45);

    TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 155);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 25200000);

    RemoveFromFront(loctestnum, loctesterr, lst, true);
    FrontNRemove(loctestnum, loctesterr, lst, true, 30);
    FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 28000);

    lasd::List<int> coplst(lst);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);

    InsertAtFront(loctestnum, loctesterr, lst, true, 0);
    InsertAtBack(loctestnum, loctesterr, lst, true, 0);
    NonEqualList(loctestnum, loctesterr, lst, coplst, true);
    coplst = lst;
    EqualList(loctestnum, loctesterr, lst, coplst, true);

    RemoveFromFront(loctestnum, loctesterr, coplst, true);
    FrontNRemove(loctestnum, loctesterr, coplst, true, 41);
    coplst = std::move(lst);
    FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 57);
    FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 98);

    lasd::List<int> movlst(std::move(lst));
    MapPreOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 0, 60);

    InsertAtBack(loctestnum, loctesterr, movlst, true, 60);
    InsertAtBack(loctestnum, loctesterr, movlst, true, 80);
    
    RemoveFromFront(loctestnum, loctesterr, movlst, true);
    InsertAtBack(loctestnum, loctesterr, movlst, true, 70);
    FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 234);

    movlst.Clear();
    Empty(loctestnum, loctesterr, movlst, true);
    Size(loctestnum, loctesterr, movlst, true, 0);
  }
  catch (...) {
    loctestnum++; loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test List<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestListDouble(unsigned int & testnum, unsigned int & testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test List<double>:" << endl;
   try {
     lasd::List<double> lst;
     Empty(loctestnum, loctesterr, lst, true);
     Size(loctestnum, loctesterr, lst, true, 0);

     InsertAtBack(loctestnum, loctesterr, lst, true, -4.5);
     InsertAtBack(loctestnum, loctesterr, lst, true, 4.5);

     lst.Clear();

     InsertAtBack(loctestnum, loctesterr, lst, true, 40.0);
     InsertAtFront(loctestnum, loctesterr, lst, true, 30.0);
     InsertAtFront(loctestnum, loctesterr, lst, true, 20.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 10.0);

     GetFront(loctestnum, loctesterr, lst, true, 20.0);
     GetBack(loctestnum, loctesterr, lst, true, 10.0);

     Exists(loctestnum, loctesterr, lst, false, 0.0);

     TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
     TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
     FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 100.0);
     FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 1.0, 240000.0);
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test List<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */


 void mytestListString(unsigned int &testnum, unsigned int &testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test List<string>:" << endl;
   try {
     lasd::List<string> lst;
     Empty(loctestnum, loctesterr, lst, true);
     Size(loctestnum, loctesterr, lst, true, 0);

     InsertAtFront(loctestnum, loctesterr, lst, true, string("X"));
     InsertAtBack(loctestnum, loctesterr, lst, true, string("Y"));

     GetFront(loctestnum, loctesterr, lst, true, string("X"));
     GetBack(loctestnum, loctesterr, lst, true, string("Y"));

     Exists(loctestnum, loctesterr, lst, true, string("Y"));

     MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) { MapStringAppend(str, string(" ")); });
     TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
     FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XX Y "));
     FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XY X "));

     Exists(loctestnum, loctesterr, lst, false, string("Y"));

     lasd::List<string> coplst(lst);
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     RemoveFromFront(loctestnum, loctesterr, coplst, true);
     NonEqualList(loctestnum, loctesterr, lst, coplst, true);

     lst = coplst;
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     InsertAtBack(loctestnum, loctesterr, lst, true, string("C"));
     InsertAtFront(loctestnum, loctesterr, lst, true, string("A"));
     NonEqualList(loctestnum, loctesterr, lst, coplst, true);

     coplst = std::move(lst);
     FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string("?"), string("?AY C"));
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test List<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */

void mytestVectorListInt(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test Vector/List<int>:" << endl;
  try {
    lasd::SortableVector<int> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, 10);  
    SetAt(loctestnum, loctesterr, vec, true, 1, 20);  
    SetAt(loctestnum, loctesterr, vec, true, 2, 30);  

    lasd::List<int> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, 30);
    InsertAtFront(loctestnum, loctesterr, lst, true, 20);  
    InsertAtFront(loctestnum, loctesterr, lst, true, 10);  

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<int> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<int> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<int> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<int> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector/List<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestVectorListDouble(unsigned int & testnum, unsigned int & testerr) {
   unsigned int loctestnum = 0, loctesterr = 0;
   cout << endl << "Inizio del test Vector/List<double>:" << endl;
   try {
     lasd::SortableVector<double> vec(3);
     SetAt(loctestnum, loctesterr, vec, true, 0, 10.0);
     SetAt(loctestnum, loctesterr, vec, true, 1, 20.0);
     SetAt(loctestnum, loctesterr, vec, true, 2, 30.5);

     lasd::List<double> lst;
     InsertAtBack(loctestnum, loctesterr, lst, true, 10.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 20.0);
     InsertAtBack(loctestnum, loctesterr, lst, true, 30.5);

     EqualLinear(loctestnum, loctesterr, vec, lst, true);

     lasd::SortableVector<double> copvec(lst);
     EqualVector(loctestnum, loctesterr, vec, copvec, true);
     lasd::SortableVector<double> copvecx(vec);
     EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

     lasd::List<double> coplst(vec);
     EqualList(loctestnum, loctesterr, lst, coplst, true);
     lasd::List<double> coplstx(lst);
     EqualList(loctestnum, loctesterr, coplstx, coplst, true);
   }
   catch (...) {
     loctestnum++; loctesterr++;
     cout << endl << "Errore non gestito! " << endl;
   }
   cout << "Fine del test Vector/List<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
   testnum += loctestnum;
   testerr += loctesterr;
 }

/* ************************************************************************** */

void mytestVectorListString(unsigned int &testnum, unsigned int &testerr) {
  unsigned int loctestnum = 0, loctesterr = 0;
  cout << endl << "Inizio del test Vector/List<string>:" << endl;
  try {
    lasd::SortableVector<string> vec(3);
    SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));
    SetAt(loctestnum, loctesterr, vec, true, 1, string("Y"));
    SetAt(loctestnum, loctesterr, vec, true, 2, string("Z"));

    lasd::List<string> lst;
    InsertAtFront(loctestnum, loctesterr, lst, true, string("Y"));  
    InsertAtBack(loctestnum, loctesterr, lst, true, string("Z"));  
    InsertAtFront(loctestnum, loctesterr, lst, true, string("X"));  

    EqualLinear(loctestnum, loctesterr, vec, lst, true);

    lasd::SortableVector<string> copvec(lst);
    EqualVector(loctestnum, loctesterr, vec, copvec, true);
    lasd::SortableVector<string> copvecx(vec);
    EqualVector(loctestnum, loctesterr, copvecx, copvec, true);

    lasd::List<string> coplst(vec);
    EqualList(loctestnum, loctesterr, lst, coplst, true);
    lasd::List<string> coplstx(lst);
    EqualList(loctestnum, loctesterr, coplstx, coplst, true);

    lasd::List<string> coplsty(std::move(vec));
    EqualList(loctestnum, loctesterr, coplst, coplsty, true);
    EqualVector(loctestnum, loctesterr, vec, copvec, false);

    lasd::SortableVector<string> copvecy(std::move(lst));
    EqualVector(loctestnum, loctesterr, copvec, copvecy, true);
    EqualList(loctestnum, loctesterr, lst, coplst, false);
  }
  catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
  cout << "Fine del test Vector/List<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
  testnum += loctestnum;
  testerr += loctesterr;
}

/* ************************************************************************** */

void mytestSetLstInt(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test su SetLst<int>:" << endl;

    try {
    lasd::SetLst<int> set;
    InsertC(loctestnum, loctesterr, set, true, 10);   // Inserisce 10, deve andare bene
    InsertC(loctestnum, loctesterr, set, false, 10);  // Prova a inserire 10 di nuovo, deve fallire (duplicato)
    InsertC(loctestnum, loctesterr, set, true, 20);   // Inserisce 20, deve andare bene

    Exists(loctestnum, loctesterr, set, true, 10);
    Exists(loctestnum, loctesterr, set, true, 20);
    Exists(loctestnum, loctesterr, set, false, 30);

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 30);

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetLst<int> set2;
    // Inserimenti multipli e duplicati
    for (int i = 0; i < 10; ++i) InsertC(loctestnum, loctesterr, set2, true, i);
    for (int i = 0; i < 10; ++i) InsertC(loctestnum, loctesterr, set2, false, i); // duplicati

    Size(loctestnum, loctesterr, set2, true, 10);

    // Rimozione alternata (pari)
    for (int i = 0; i < 10; i += 2) Remove(loctestnum, loctesterr, set2, true, i);
    Size(loctestnum, loctesterr, set2, true, 5);

    // Rimozione di elementi non presenti
    for (int i = 20; i < 25; ++i) Remove(loctestnum, loctesterr, set2, false, i);

    // Fold e Traverse
    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<int>, 0, 25); // somma dei dispari 1+3+5+7+9=25
    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<int>);

    // Copy e Move
    lasd::SetLst<int> setcopy(set2);
    EqualSetLst(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetLst<int> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 5);

    lasd::SetLst<int> setA;
    // Accesso fuori range
    GetAt(loctestnum, loctesterr, setA, false, 5, 0);
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetLst<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytestSetLstDouble(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test InsertC su SetLst<double>:" << endl;

    try {
    lasd::SetLst<double> set;
    InsertC(loctestnum, loctesterr, set, true, 3.14);   // Inserisce 3.14, deve andare bene
    InsertC(loctestnum, loctesterr, set, false, 3.14);  // Prova a inserire 3.14 di nuovo, deve fallire (duplicato)
    InsertC(loctestnum, loctesterr, set, true, 2.71);   // Inserisce 2.71, deve andare bene

    Exists(loctestnum, loctesterr, set, true, 3.14);
    Exists(loctestnum, loctesterr, set, true, 2.71);
    Exists(loctestnum, loctesterr, set, false, 1.41);

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 5.85);

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetLst<double> set2;
    for (int i = 0; i < 10; ++i) InsertC(loctestnum, loctesterr, set2, true, i * 1.1);
    for (int i = 0; i < 10; ++i) InsertC(loctestnum, loctesterr, set2, false, i * 1.1);

    Size(loctestnum, loctesterr, set2, true, 10);

    for (int i = 0; i < 10; i += 2) Remove(loctestnum, loctesterr, set2, true, i * 1.1);
    Size(loctestnum, loctesterr, set2, true, 5);

    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<double>, 0.0, 1.1+3.3+5.5+7.7+9.9);
    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<double>);

    lasd::SetLst<double> setcopy(set2);
    EqualSetLst(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetLst<double> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 5);

    lasd::SetLst<double> setA;
    GetAt(loctestnum, loctesterr, setA, false, 5, 0.0);
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetLst<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytestSetLstString(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test su SetLst<string>:" << endl;

    try {
    lasd::SetLst<string> set;
    InsertC(loctestnum, loctesterr, set, true, std::string("ciao"));
    InsertC(loctestnum, loctesterr, set, false, std::string("ciao"));
    InsertC(loctestnum, loctesterr, set, true, std::string("mondo"));

    Exists(loctestnum, loctesterr, set, true, std::string("ciao"));
    Exists(loctestnum, loctesterr, set, true, std::string("mondo"));
    Exists(loctestnum, loctesterr, set, false, std::string("test"));

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("!"), string("!ciaomondo"));

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetLst<string> set2;
    InsertC(loctestnum, loctesterr, set2, true, string("a"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("b"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("c"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("d"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("e"));
    InsertC(loctestnum, loctesterr, set2, false, std::string("a")); // duplicato

    Size(loctestnum, loctesterr, set2, true, 5);

    Remove(loctestnum, loctesterr, set2, true, std::string("c"));
    Exists(loctestnum, loctesterr, set2, false, std::string("c"));
    Size(loctestnum, loctesterr, set2, true, 4);

    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldStringConcatenate, string("!"), string("!abde"));
    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<string>);

    lasd::SetLst<string> setcopy(set2);
    EqualSetLst(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetLst<string> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 4);

    lasd::SetLst<string> setA;
    GetAt(loctestnum, loctesterr, setA, false, 10, std::string(""));
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetLst<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytestSetVecInt(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test su SetVec<int>:" << endl;

    try {
    lasd::SetVec<int> set;
    InsertC(loctestnum, loctesterr, set, true, 10);
    InsertC(loctestnum, loctesterr, set, false, 10);
    InsertC(loctestnum, loctesterr, set, true, 20);

    Exists(loctestnum, loctesterr, set, true, 10);
    Exists(loctestnum, loctesterr, set, true, 20);
    Exists(loctestnum, loctesterr, set, false, 30);

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 30);

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetVec<int> set2;
    // Inserimenti multipli e duplicati
    for (int i = 0; i < 15; ++i) InsertC(loctestnum, loctesterr, set2, true, i);
    for (int i = 0; i < 15; ++i) InsertC(loctestnum, loctesterr, set2, false, i); // duplicati

    Size(loctestnum, loctesterr, set2, true, 15);

    // Rimozione alternata (dispari)
    for (int i = 1; i < 15; i += 2) Remove(loctestnum, loctesterr, set2, true, i);
    Size(loctestnum, loctesterr, set2, true, 8);

    // Fold e Traverse
    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<int>, 0, 56); // somma degli 0,2,4,6,8,10,12,14
    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<int>);

    // Copy e Move
    lasd::SetVec<int> setcopy(set2);
    EqualSetVec(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetVec<int> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 8);

    lasd::SetVec<int> setA;
    // Accesso fuori range
    GetAt(loctestnum, loctesterr, setA, false, 10, 0);
    GetAt(loctestnum, loctesterr, setA, false, 20, 0);
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetVec<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetVecDouble(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test su SetVec<double>:" << endl;

    try { 
    lasd::SetVec<double> set;
    InsertC(loctestnum, loctesterr, set, true, 3.14);
    InsertC(loctestnum, loctesterr, set, false, 3.14);
    InsertC(loctestnum, loctesterr, set, true, 2.71);

    Exists(loctestnum, loctesterr, set, true, 3.14);
    Exists(loctestnum, loctesterr, set, true, 2.71);
    Exists(loctestnum, loctesterr, set, false, 1.41);

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 5.85);

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetVec<double> set2;
    for (int i = 0; i < 15; ++i) InsertC(loctestnum, loctesterr, set2, true, i * 2.5);
    for (int i = 0; i < 15; ++i) InsertC(loctestnum, loctesterr, set2, false, i * 2.5);

    Size(loctestnum, loctesterr, set2, true, 15);

    for (int i = 1; i < 15; i += 2) Remove(loctestnum, loctesterr, set2, true, i * 2.5);
    Size(loctestnum, loctesterr, set2, true, 8);

    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<double>, 0.0, 140.0);
    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<double>);

    lasd::SetVec<double> setcopy(set2);
    EqualSetVec(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetVec<double> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 8);

    lasd::SetVec<double> setA;
    GetAt(loctestnum, loctesterr, setA, false, 10, 0.0);
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetVec<double> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetVecString(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test su SetVec<string>:" << endl;

    try {
    lasd::SetVec<string> set;
    InsertC(loctestnum, loctesterr, set, true, std::string("ciao"));
    InsertC(loctestnum, loctesterr, set, false, std::string("ciao"));
    InsertC(loctestnum, loctesterr, set, true, std::string("mondo"));

    Exists(loctestnum, loctesterr, set, true, std::string("ciao"));
    Exists(loctestnum, loctesterr, set, true, std::string("mondo"));
    Exists(loctestnum, loctesterr, set, false, std::string("test"));

    FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("!"), string("!ciaomondo"));

    set.Clear();
    Empty(loctestnum, loctesterr, set, true);

    lasd::SetVec<string> set2;
    InsertC(loctestnum, loctesterr, set2, true, std::string("uno"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("due"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("tre"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("quattro"));
    InsertC(loctestnum, loctesterr, set2, true, std::string("cinque"));
    InsertC(loctestnum, loctesterr, set2, false, std::string("uno")); // duplicato

    Size(loctestnum, loctesterr, set2, true, 5);

    Remove(loctestnum, loctesterr, set2, true, std::string("tre"));
    Exists(loctestnum, loctesterr, set2, false, std::string("tre"));
    Size(loctestnum, loctesterr, set2, true, 4);

    TraversePreOrder(loctestnum, loctesterr, set2, true, &TraversePrint<string>);

    lasd::SetVec<string> setcopy(set2);
    EqualSetVec(loctestnum, loctesterr, set2, setcopy, true);
    setcopy.Clear();
    Empty(loctestnum, loctesterr, setcopy, true);

    lasd::SetVec<string> setmove(std::move(set2));
    Empty(loctestnum, loctesterr, set2, true);
    Size(loctestnum, loctesterr, setmove, true, 4);

    lasd::SetVec<string> setA;
    GetAt(loctestnum, loctesterr, setA, false, 10, std::string(""));
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test SetVec<string> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetLstIntRemoveMiddle(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test rimozione nodo centrale in SetLst<int>:" << endl;

    try {
    lasd::SetLst<int> set;
    InsertC(loctestnum, loctesterr, set, true, 10);
    InsertC(loctestnum, loctesterr, set, true, 20);
    InsertC(loctestnum, loctesterr, set, true, 30);
    InsertC(loctestnum, loctesterr, set, true, 40);
    InsertC(loctestnum, loctesterr, set, true, 50);

    // La lista ora è: 10, 20, 30, 40, 50

    Remove(loctestnum, loctesterr, set, true, 30); // Rimuove il nodo centrale

    Exists(loctestnum, loctesterr, set, false, 30); // Deve essere false
    Size(loctestnum, loctesterr, set, true, 4);     // Ora il set ha 4 elementi

    // Controlla l'ordine degli elementi rimasti 
    GetAt(loctestnum, loctesterr, set, true, 0, 10);
    GetAt(loctestnum, loctesterr, set, true, 1, 20);
    GetAt(loctestnum, loctesterr, set, true, 2, 40);
    GetAt(loctestnum, loctesterr, set, true, 3, 50);
    }
    catch (...) { 
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
  }
    cout << "Fine del test rimozione nodo centrale in SetLst<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetLstIntEdgeCases(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test edge/casi limite su SetLst<int>:" << endl;

    try {
    lasd::SetLst<int> set;

    // Rimozione da set vuoto
    Remove(loctestnum, loctesterr, set, false, 42);

    // Inserimento e rimozione di duplicati
    InsertC(loctestnum, loctesterr, set, true, 1);
    InsertC(loctestnum, loctesterr, set, false, 1);
    Remove(loctestnum, loctesterr, set, true, 1);
    Remove(loctestnum, loctesterr, set, false, 1);

    // Inserimento di valori estremi
    InsertC(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    InsertC(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());
    Exists(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    Exists(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());

    // Rimozione dalla testa e dalla coda
    Remove(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    Remove(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());
    Empty(loctestnum, loctesterr, set, true);

    // Inserimento multiplo e rimozione sequenziale
    for (int i = 0; i < 5; ++i) InsertC(loctestnum, loctesterr, set, true, i);
    for (int i = 0; i < 5; ++i) Remove(loctestnum, loctesterr, set, true, i);
    Empty(loctestnum, loctesterr, set, true);

    // Clear e nuovo inserimento
    for (int i = 0; i < 3; ++i) InsertC(loctestnum, loctesterr, set, true, i*10);
    set.Clear();
    Empty(loctestnum, loctesterr, set, true);
    InsertC(loctestnum, loctesterr, set, true, 99);
    Exists(loctestnum, loctesterr, set, true, 99);

    // Test di copia e uguaglianza
    lasd::SetLst<int> set1;
    InsertC(loctestnum, loctesterr, set1, true, 1);
    InsertC(loctestnum, loctesterr, set1, true, 2);
    lasd::SetLst<int> set2(set1);
    EqualSetLst(loctestnum, loctesterr, set1, set2, true);
    Remove(loctestnum, loctesterr, set2, true, 1);
    NonEqualSetLst(loctestnum, loctesterr, set1, set2, true);

    // Test di move
    lasd::SetLst<int> set3(std::move(set1));
    Empty(loctestnum, loctesterr, set1, true);
    EqualSetLst(loctestnum, loctesterr, set2, set3, false);

    // Test Fold/Map su set con un solo elemento
    set2.Clear();
    InsertC(loctestnum, loctesterr, set2, true, 42);
    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<int>, 0, 42);

    // Test eccezioni GetAt fuori range
    GetAt(loctestnum, loctesterr, set2, false, 5, 0);
    }
    catch (...) {
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
    }
    cout << "Fine del test edge/casi limite SetLst<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

    testnum += loctestnum;
    testerr += loctesterr;
}

void mytestSetVecIntEdgeCases(unsigned int &testnum, unsigned int &testerr) {
    unsigned int loctestnum = 0, loctesterr = 0;
    cout << endl << "Test edge/casi limite su SetVec<int>:" << endl;

    try {
    lasd::SetVec<int> set;

    // Rimozione da set vuoto
    Remove(loctestnum, loctesterr, set, false, 42);

    // Inserimento e rimozione di duplicati
    InsertC(loctestnum, loctesterr, set, true, 1);
    InsertC(loctestnum, loctesterr, set, false, 1);
    Remove(loctestnum, loctesterr, set, true, 1);
    Remove(loctestnum, loctesterr, set, false, 1);

    // Inserimento di valori estremi
    InsertC(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    InsertC(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());
    Exists(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    Exists(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());

    // Rimozione dalla testa e dalla coda
    Remove(loctestnum, loctesterr, set, true, std::numeric_limits<int>::min());
    Remove(loctestnum, loctesterr, set, true, std::numeric_limits<int>::max());
    Empty(loctestnum, loctesterr, set, true);

    // Inserimento multiplo e rimozione sequenziale
    for (int i = 0; i < 5; ++i) InsertC(loctestnum, loctesterr, set, true, i);
    for (int i = 0; i < 5; ++i) Remove(loctestnum, loctesterr, set, true, i);
    Empty(loctestnum, loctesterr, set, true);

    // Clear e nuovo inserimento
    for (int i = 0; i < 3; ++i) InsertC(loctestnum, loctesterr, set, true, i*10);
    set.Clear();
    Empty(loctestnum, loctesterr, set, true);
    InsertC(loctestnum, loctesterr, set, true, 99);
    Exists(loctestnum, loctesterr, set, true, 99);

    // Test di copia e uguaglianza
    lasd::SetVec<int> set1;
    InsertC(loctestnum, loctesterr, set1, true, 77);
    InsertC(loctestnum, loctesterr, set1, true, 11);
    lasd::SetVec<int> set2(set1);
    EqualSetVec(loctestnum, loctesterr, set1, set2, true);
    Remove(loctestnum, loctesterr, set2, true, 77);
    NonEqualSetVec(loctestnum, loctesterr, set1, set2, true);

    // Test di move
    lasd::SetVec<int> set3(std::move(set1));
    Empty(loctestnum, loctesterr, set1, true);
    EqualSetVec(loctestnum, loctesterr, set2, set3, false);

    // Test Fold/Map su set con un solo elemento
    set2.Clear();
    InsertC(loctestnum, loctesterr, set2, true, 23);
    FoldPreOrder(loctestnum, loctesterr, set2, true, &FoldAdd<int>, 0, 23);

    // Test eccezioni GetAt fuori range
    GetAt(loctestnum, loctesterr, set2, false, 5, 0);
    }
    catch (...) { 
    loctestnum++;
    loctesterr++;
    cout << endl << "Errore non gestito! " << endl;
    }
    cout << "Fine del test edge/casi limite SetVec<int> (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;

    testnum += loctestnum;
    testerr += loctesterr;


}

/* ************************************************************************** */

// Fase di test per gli esercizi 1
void eseguiTest1(unsigned int &testnum, unsigned int &testerr)
{
    // Esegue i test su vettori di interi, double e stringhe
    mytestVectorInt(testnum, testerr);
    mytestVectorDouble(testnum, testerr);
    mytestVectorString(testnum, testerr);

    // Esegue i test su liste di interi, double e stringhe
    mytestListInt(testnum, testerr);
    mytestListDouble(testnum, testerr);
    mytestListString(testnum, testerr);

    // Esegue i test su vettori di liste di interi, double e stringhe
    mytestVectorListInt(testnum, testerr);
    mytestVectorListDouble(testnum, testerr);
    mytestVectorListString(testnum, testerr);

    // Esegue i test su SetLst di interi, double e stringhe
    mytestSetLstInt(testnum, testerr);
    mytestSetLstDouble(testnum, testerr);
    mytestSetLstString(testnum, testerr);

    // Esegue i test su SetVec di interi, double e stringhe
    mytestSetVecInt(testnum, testerr);
    mytestSetVecDouble(testnum, testerr);
    mytestSetVecString(testnum, testerr);
    
    // Esegue i test di rimozione di un nodo centrale in SetLst<int>
    mytestSetLstIntRemoveMiddle(testnum, testerr);

    // Eseguono dei test di edge/casi limite su SetLst<int> e SetVec<int>
    mytestSetLstIntEdgeCases(testnum, testerr);
    mytestSetVecIntEdgeCases(testnum, testerr);
}

/* ************************************************************************** */

void mytest() {
  cout << endl
       << "Test LASD di Francesco Pio Illiano (N86004752) " << endl;
  cout << endl << endl
       << "Test esercizio 1 LASD " << endl;

  unsigned int loctestnum, loctesterr;
  unsigned int stestnum = 0, stesterr = 0;

  loctestnum = 0; loctesterr = 0;
  eseguiTest1(loctestnum, loctesterr);
  stestnum += loctestnum;
  stesterr += loctesterr;
  cout << endl
       << "Esercizio 1(myTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")\n";
}

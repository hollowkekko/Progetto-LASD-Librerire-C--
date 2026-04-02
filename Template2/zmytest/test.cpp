#include <iostream>
#include <limits>
#include <climits>

#include "../pq/heap/pqheap.hpp"
#include "../heap/vec/heapvec.hpp"


#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"
#include "../zlasdtest/pq/pq.hpp"
#include "../zlasdtest/heap/heap.hpp"

using namespace std;

/* ************************************************************************** */

// Test HeapVec<int>

void myIntHeapTests(uint& totalTests, uint& totalErrors) {
    uint localTests = 0, localErrors = 0;
    cout << "\n=== INTEGER HEAP TESTING SUITE ===" << endl;
    
    try {
        // Costruzione
        cout << "[Phase 1] Construction and Basic Properties" << endl;
        lasd::Vector<int> dataSet(12);
        int values[] = {25, 18, 22, 12, 15, 19, 24, 8, 10, 14, 11, 9};
        
        for(int i = 0; i < 12; ++i) {
            SetAt(localTests, localErrors, dataSet, true, i, values[i]);
        }
        
        lasd::HeapVec<int> primaryHeap(dataSet);
        
        // Verifica proprietà di base
        IsHeap(localTests, localErrors, primaryHeap, true);
        Empty(localTests, localErrors, primaryHeap, false);
        Size(localTests, localErrors, primaryHeap, true, 12);
        GetFront(localTests, localErrors, primaryHeap, true, 25); // Maximum element
        
        // Pattern di accesso e Limiti
        cout << "[Phase 2] Element Access and Boundary Conditions" << endl;
        GetAt(localTests, localErrors, primaryHeap, true, 0, 25);
        GetAt(localTests, localErrors, primaryHeap, true, 6, 22);
        GetBack(localTests, localErrors, primaryHeap, true, 9);
        
        // Testi di accesso fuori limite
        GetAt(localTests, localErrors, primaryHeap, false, 50, 0);
        GetAt(localTests, localErrors, primaryHeap, false, -5, 0);
        
        // Attraversamento
        cout << "[Phase 3] Traversal Methods Validation" << endl;
        cout << "Linear traverse: ";
        Traverse(localTests, localErrors, primaryHeap, true, &TraversePrint<int>);
        cout << "PreOrder traverse: ";
        TraversePreOrder(localTests, localErrors, primaryHeap, true, &TraversePrint<int>);
        cout << "PostOrder traverse: ";
        TraversePostOrder(localTests, localErrors, primaryHeap, true, &TraversePrint<int>);
        
        // Casi speciali
        cout << "[Phase 4] Edge Case Analysis" << endl;
        
        // Empty heap scenario
        lasd::HeapVec<int> voidHeap;
        Empty(localTests, localErrors, voidHeap, true);
        Size(localTests, localErrors, voidHeap, true, 0);
        IsHeap(localTests, localErrors, voidHeap, true);
        GetFront(localTests, localErrors, voidHeap, false, 0);
        
        // Singolo elemento 
        lasd::Vector<int> unitVector(1);
        SetAt(localTests, localErrors, unitVector, true, 0, 99);
        lasd::HeapVec<int> unitHeap(unitVector);
        IsHeap(localTests, localErrors, unitHeap, true);
        GetFront(localTests, localErrors, unitHeap, true, 99);
        Size(localTests, localErrors, unitHeap, true, 1);
        
        // Copy and Move Operations
        cout << "[Phase 5] Copy and Move Operations" << endl;
        lasd::HeapVec<int> duplicateHeap(primaryHeap);
        EqualLinear(localTests, localErrors, primaryHeap, duplicateHeap, true);
        
        lasd::HeapVec<int> transferHeap(std::move(duplicateHeap));
        EqualLinear(localTests, localErrors, primaryHeap, transferHeap, true);
        Empty(localTests, localErrors, duplicateHeap, true);
        
        duplicateHeap = transferHeap;
        EqualLinear(localTests, localErrors, duplicateHeap, transferHeap, true);
        
        lasd::HeapVec<int> moveAssignHeap;
        moveAssignHeap = std::move(duplicateHeap);
        Empty(localTests, localErrors, duplicateHeap, true);
        
        // Ordinamento
        cout << "[Phase 6] Sorting and Heap Restoration" << endl;
        lasd::HeapVec<int> sortableHeap(primaryHeap);
        IsHeap(localTests, localErrors, sortableHeap, true);
        
        sortableHeap.Sort();
        IsHeap(localTests, localErrors, sortableHeap, false);
        
        // Ripristino della struttura heap
        sortableHeap.Heapify();
        IsHeap(localTests, localErrors, sortableHeap, true);
        
        // Operazioni Map e Fold
        cout << "[Phase 7] Map and Fold Operations" << endl;
        FoldPreOrder(localTests, localErrors, primaryHeap, true, &FoldAdd<int>, 0, 187);
        FoldPostOrder(localTests, localErrors, primaryHeap, true, &FoldAdd<int>, 0, 187);
        
        lasd::HeapVec<int> mapHeap(primaryHeap);
        MapPreOrder(localTests, localErrors, mapHeap, true, [](int& x) { x *= 2; });
        mapHeap.Heapify();
        IsHeap(localTests, localErrors, mapHeap, true);
        GetFront(localTests, localErrors, mapHeap, true, 50);
        
        // Mutazioni e Effetti
        cout << "[Phase 8] Mutation Effects" << endl;
        SetAt(localTests, localErrors, primaryHeap, true, 0, 5);
        IsHeap(localTests, localErrors, primaryHeap, false);
        primaryHeap.Heapify();
        IsHeap(localTests, localErrors, primaryHeap, true);
        
        // Stress Testing
        cout << "[Phase 9] Large Dataset Validation" << endl;
        lasd::Vector<int> massiveSet(50);
        for(uint i = 0; i < 50; ++i) {
            SetAt(localTests, localErrors, massiveSet, true, i, rand() % 1000);
        }
        
        lasd::HeapVec<int> massiveHeap(massiveSet);
        IsHeap(localTests, localErrors, massiveHeap, true);
        Size(localTests, localErrors, massiveHeap, true, 50);
        massiveHeap.Sort();
        
        // Gestione dei valori duplicati
        cout << "[Phase 10] Duplicate Value Management" << endl;
        lasd::Vector<int> duplicateSet(8);
        int dupValues[] = {7, 7, 5, 5, 3, 3, 1, 1};
        for(int i = 0; i < 8; ++i) {
            SetAt(localTests, localErrors, duplicateSet, true, i, dupValues[i]);
        }
        
        lasd::HeapVec<int> dupHeap(duplicateSet);
        IsHeap(localTests, localErrors, dupHeap, true);
        GetFront(localTests, localErrors, dupHeap, true, 7);
        
        dupHeap.Sort();
        GetAt(localTests, localErrors, dupHeap, true, 0, 1);
        GetAt(localTests, localErrors, dupHeap, true, 7, 7);
        
    } catch(...) {
        localTests++; localErrors++;
        cout << "Critical exception encountered!" << endl;
    }
    
    cout << "=== INTEGER HEAP TESTS COMPLETED (" << localErrors << "/" << localTests << ") ===" << endl;
    totalTests += localTests;
    totalErrors += localErrors;
}

void myDoubleHeapTests(uint& totalTests, uint& totalErrors) {
    uint localTests = 0, localErrors = 0;
    cout << "\n>>> DOUBLE PRECISION HEAP VALIDATION <<<" << endl;
    
    try {
        // Inizializzazione e Costruzione
        cout << "Floating Point Heap Construction" << endl;
        lasd::Vector<double> floatData(8);
        double precisionValues[] = {7.75, 3.125, 6.25, 2.5, 1.875, 5.0, 0.625, 9.5};
        
        for(size_t i = 0; i < 8; ++i) {
            SetAt(localTests, localErrors, floatData, true, i, precisionValues[i]);
        }
        
        lasd::HeapVec<double> floatHeap(floatData);
        IsHeap(localTests, localErrors, floatHeap, true);
        Size(localTests, localErrors, floatHeap, true, 8);
        GetFront(localTests, localErrors, floatHeap, true, 9.5);
        
        // Casi Limiti
        cout << "Floating Point Precision Analysis" << endl;
        lasd::Vector<double> precisionSet(5);
        precisionSet[0] = 2.0000002;
        precisionSet[1] = 2.0000001;
        precisionSet[2] = 1.9999999;
        precisionSet[3] = 1.9999998;
        precisionSet[4] = 2.0;
        
        lasd::HeapVec<double> precisionHeap(precisionSet);
        IsHeap(localTests, localErrors, precisionHeap, true);
        GetFront(localTests, localErrors, precisionHeap, true, 2.0000002);
        
        // Valori Speciali
        cout << "Special Double Values Testing" << endl;
        lasd::Vector<double> specialSet(6);
        specialSet[0] = -7.25;
        specialSet[1] = 0.0;
        specialSet[2] = 4.71238;
        specialSet[3] = -0.0;
        specialSet[4] = 3.14159;
        specialSet[5] = 1.41421;
        
        lasd::HeapVec<double> specialHeap(specialSet);
        IsHeap(localTests, localErrors, specialHeap, true);
        GetFront(localTests, localErrors, specialHeap, true, 4.71238);
        
        cout << "Object Duplication Mechanisms" << endl;
        lasd::HeapVec<double> clonedHeap(floatHeap);
        EqualLinear(localTests, localErrors, floatHeap, clonedHeap, true);
        
        cout << "Sorting and Traversal Patterns" << endl;
        cout << "Initial state: ";
        TraversePreOrder(localTests, localErrors, floatHeap, true, &TraversePrint<double>);
        
        floatHeap.Sort();
        IsHeap(localTests, localErrors, floatHeap, false);
        cout << "Sorted state: ";
        TraversePreOrder(localTests, localErrors, floatHeap, true, &TraversePrint<double>);
        
        // Ripristino della Struttura
        cout << "Structure Restoration" << endl;
        floatHeap.Heapify();
        IsHeap(localTests, localErrors, floatHeap, true);
        cout << "Restored heap: ";
        TraversePreOrder(localTests, localErrors, floatHeap, true, &TraversePrint<double>);
        
        // Trasformazioni Matematiche
        cout << "Mathematical Transformations" << endl;
        MapPreOrder(localTests, localErrors, floatHeap, true, [](double& x) { x *= 1.5; });
        GetFront(localTests, localErrors, floatHeap, true, 14.25);
        IsHeap(localTests, localErrors, floatHeap, true);
        
        cout << "Reduction Operations" << endl;
        double expectedSum = 0.0;
        for(size_t i = 0; i < floatHeap.Size(); i++) {
            expectedSum += floatHeap[i];
        }
        FoldPreOrder(localTests, localErrors, floatHeap, true, &FoldAdd<double>, 0.0, expectedSum);
        FoldPostOrder(localTests, localErrors, floatHeap, true, &FoldAdd<double>, 0.0, expectedSum);
        
        
    } catch(...) {
        localTests++; localErrors++;
        cout << "Floating point exception intercepted!" << endl;
    }
    
    cout << ">>> DOUBLE PRECISION TESTS CONCLUDED (" << localErrors << "/" << localTests << ") <<<" << endl;
    totalTests += localTests;
    totalErrors += localErrors;
}

void myStringHeapTests(uint& totalTests, uint& totalErrors) {
    uint localTests = 0, localErrors = 0;
    cout << "\n*** STRING HEAP TESTING ***" << endl;
    
    try {
        // Inizializzazione e Costruzione
        cout << "String Heap Foundation" << endl;
        lasd::Vector<string> textData(12);
        string words[] = {"Zebra", "Apple", "Mountain", "River", "Ocean", "Forest", 
                         "Desert", "Valley", "Glacier", "Volcano", "Canyon", "Prairie"};
        
        for(int i = 0; i < 12; ++i) {
            SetAt(localTests, localErrors, textData, true, i, words[i]);
        }
        
        lasd::HeapVec<string> textHeap(textData);
        IsHeap(localTests, localErrors, textHeap, true);
        Size(localTests, localErrors, textHeap, true, 12);
        GetFront(localTests, localErrors, textHeap, true, string("Zebra"));
        
        // Set di caratteri e Codifica
        cout << "Character Set and Encoding Tests" << endl;
        lasd::Vector<string> encodingSet(6);
        SetAt(localTests, localErrors, encodingSet, true, 0, string(""));
        SetAt(localTests, localErrors, encodingSet, true, 1, string("z"));
        SetAt(localTests, localErrors, encodingSet, true, 2, string("Z"));
        SetAt(localTests, localErrors, encodingSet, true, 3, string("zz"));
        SetAt(localTests, localErrors, encodingSet, true, 4, string("aa"));
        SetAt(localTests, localErrors, encodingSet, true, 5, string("A"));
        
        lasd::HeapVec<string> encodingHeap(encodingSet);
        IsHeap(localTests, localErrors, encodingHeap, true);
        GetFront(localTests, localErrors, encodingHeap, true, string("zz"));
        
        // Case Sensitivity
        cout << "Case Sensitivity Evaluation" << endl;
        lasd::Vector<string> caseSet(5);
        SetAt(localTests, localErrors, caseSet, true, 0, string("banana"));
        SetAt(localTests, localErrors, caseSet, true, 1, string("Banana"));
        SetAt(localTests, localErrors, caseSet, true, 2, string("BANANA"));
        SetAt(localTests, localErrors, caseSet, true, 3, string("bAnAnA"));
        SetAt(localTests, localErrors, caseSet, true, 4, string("BaNaNa"));
        
        lasd::HeapVec<string> caseHeap(caseSet);
        IsHeap(localTests, localErrors, caseHeap, true);
        GetFront(localTests, localErrors, caseHeap, true, string("banana"));
        
        cout << "String Heap Object Management" << endl;
        lasd::HeapVec<string> replicaHeap(textHeap);
        EqualLinear(localTests, localErrors, textHeap, replicaHeap, true);
        
        lasd::HeapVec<string> movedHeap(std::move(replicaHeap));
        EqualLinear(localTests, localErrors, textHeap, movedHeap, true);
        Empty(localTests, localErrors, replicaHeap, true);
        
        cout << "String Content Modifications" << endl;
        cout << "Original content: ";
        TraversePreOrder(localTests, localErrors, textHeap, true, &TraversePrint<string>);
        
        MapPreOrder(localTests, localErrors, textHeap, true, [](string& str) {
            MapStringAppend(str, string("_Modified"));
        });
        
        cout << "Modified content: ";
        TraversePreOrder(localTests, localErrors, textHeap, true, &TraversePrint<string>);
        IsHeap(localTests, localErrors, textHeap, true);
        
        // Manipolazioni complesse
        cout << "Complex String Manipulations" << endl;
        MapPreOrder(localTests, localErrors, textHeap, true, [](string& str) {
            MapStringAppend(str, string(" [TAG]"));
        });
        
        cout << "Tagged strings: ";
        TraversePreOrder(localTests, localErrors, textHeap, true, &TraversePrint<string>);
        
        // Sorting 
        cout << "Sorting" << endl;
        textHeap.Sort();
        IsHeap(localTests, localErrors, textHeap, false);
        cout << "Sorted arrangement: ";
        TraversePreOrder(localTests, localErrors, textHeap, true, &TraversePrint<string>);
        
        cout << "Structure Rebuilding" << endl;
        textHeap.Heapify();
        IsHeap(localTests, localErrors, textHeap, true);
        cout << "Rebuilt heap: ";
        TraversePreOrder(localTests, localErrors, textHeap, true, &TraversePrint<string>);
        
        // Strighe lunghe 
        cout << "Long String Handling" << endl;
        lasd::Vector<string> longStringSet(4);
        SetAt(localTests, localErrors, longStringSet, true, 0,
                string("This_is_an_extremely_long_string_designed_to_test_heap_performance_with_extended_text_content"));
        SetAt(localTests, localErrors, longStringSet, true, 1,
                string("Another_very_long_string_that_should_be_properly_handled_by_the_heap_data_structure"));
        SetAt(localTests, localErrors, longStringSet, true, 2,
                string("Final_extended_string_for_comprehensive_testing_of_lexicographic_comparison_mechanisms"));
        SetAt(localTests, localErrors, longStringSet, true, 3,
                string("ZZZ_This_string_starts_with_Z_so_it_should_be_lexicographically_maximum"));
        
        lasd::HeapVec<string> longStringHeap(longStringSet);
        IsHeap(localTests, localErrors, longStringHeap, true);
        GetFront(localTests, localErrors, longStringHeap, true,
                string("ZZZ_This_string_starts_with_Z_so_it_should_be_lexicographically_maximum"));
        
        // Gestione dei duplicati
        cout << "Duplicate Content Handling" << endl;
        lasd::Vector<string> duplicateSet(8);
        string dupWords[] = {"Gamma", "Gamma", "Beta", "Beta", "Alpha", "Alpha", "Delta", "Delta"};
        for(int i = 0; i < 8; ++i) {
            SetAt(localTests, localErrors, duplicateSet, true, i, dupWords[i]);
        }
        
        lasd::HeapVec<string> duplicateHeap(duplicateSet);
        IsHeap(localTests, localErrors, duplicateHeap, true);
        GetFront(localTests, localErrors, duplicateHeap, true, string("Gamma"));
        
        duplicateHeap.Sort();
        GetAt(localTests, localErrors, duplicateHeap, true, 0, string("Alpha"));
        GetAt(localTests, localErrors, duplicateHeap, true, 7, string("Gamma"));
        
        // Condizioni di errore
        cout << "Error Condition Testing" << endl;
        GetAt(localTests, localErrors, duplicateHeap, false, 200, string(""));
        GetAt(localTests, localErrors, duplicateHeap, false, -10, string(""));
        
        SetAt(localTests, localErrors, duplicateHeap, true, 0, string("ZZZZ"));
        IsHeap(localTests, localErrors, duplicateHeap, false);
        duplicateHeap.Heapify();
        IsHeap(localTests, localErrors, duplicateHeap, true);
        GetFront(localTests, localErrors, duplicateHeap, true, string("ZZZZ"));
        
        // Gestione dei caratteri speciali
        cout << "Special Character Handling" << endl;
        lasd::Vector<string> specialCharSet(5);
        SetAt(localTests, localErrors, specialCharSet, true, 0, string("text\n"));
        SetAt(localTests, localErrors, specialCharSet, true, 1, string("text\t"));
        SetAt(localTests, localErrors, specialCharSet, true, 2, string("text "));
        SetAt(localTests, localErrors, specialCharSet, true, 3, string("text"));
        SetAt(localTests, localErrors, specialCharSet, true, 4, string("text\r"));
        
        lasd::HeapVec<string> specialCharHeap(specialCharSet);
        IsHeap(localTests, localErrors, specialCharHeap, true);
        
        // Cicli di operazioni ripetute
        cout << "Repeated Operation Cycles" << endl;
        lasd::HeapVec<string> cyclicHeap(duplicateHeap);
        for(int cycle = 0; cycle < 3; ++cycle) {
            cyclicHeap.Heapify();
            IsHeap(localTests, localErrors, cyclicHeap, true);
            cyclicHeap.Sort();
            IsHeap(localTests, localErrors, cyclicHeap, false);
        }
        
    } catch(...) {
        localTests++; localErrors++;
        cout << "String processing exception caught!" << endl;
    }
    
    cout << "*** STRING HEAP TESTING COMPLETED (" << localErrors << "/" << localTests << ") ***" << endl;
    totalTests += localTests;
    totalErrors += localErrors;
}


// Funzione helper per generare numeri interi casuali
int mygenerateRandomInt(int min = 0, int max = 1000) {
    return min + (rand() % (max - min + 1));
}

// Funzione helper per generare numeri double casuali
double mygenerateRandomDouble(double min = 0.0, double max = 100.0) {
    return min + (static_cast<double>(rand()) / RAND_MAX) * (max - min);
}

// Funzione helper per generare stringhe casuali
string mygenerateRandomString(int length = 10) {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string result;
    for(int i = 0; i < length; ++i) {
        result += charset[rand() % charset.length()];
    }
    return result;
}

/* ************************************************************************** */
// INT TESTS
/* ************************************************************************** */

void myRunIntBasicOperations(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Int Basic Operations Test ===" << endl;
    
    try {
        // Inizializzazione
        lasd::Vector<int> initialData(8);
        int values[] = {42, 17, 89, 3, 56, 24, 91, 8};
        for(int i = 0; i < 8; i++) {
            SetAt(loctestnum, loctesterr, initialData, true, i, values[i]);
        }
        
        lasd::PQHeap<int> priorityQueue(initialData);
        
        Tip(loctestnum, loctesterr, priorityQueue, true, 91); 
        
        // Test rimozione sequenziale
        TipNRemove(loctestnum, loctesterr, priorityQueue, true, 91);
        Tip(loctestnum, loctesterr, priorityQueue, true, 89);
        
        RemoveTip(loctestnum, loctesterr, priorityQueue, true);
        Tip(loctestnum, loctesterr, priorityQueue, true, 56);
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Integer Basic Operations!" << endl;
    }
    
    cout << "Integer Basic Operations completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunIntegerInsertionTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Integer Insertion Tests ===" << endl;
    
    try {
        lasd::PQHeap<int> pq;
        
       // Inserimento progressivo con verifica
        int insertValues[] = {15, 47, 2, 88, 31};
        for(int i = 0; i < 5; i++) {
            Insert(loctestnum, loctesterr, pq, insertValues[i]);
        }
        
        Tip(loctestnum, loctesterr, pq, true, 88); 
        
        // Insert duplicates
        Insert(loctestnum, loctesterr, pq, 88);
        Insert(loctestnum, loctesterr, pq, 88);
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Integer Insertion Tests!" << endl;
    }
    
    cout << "Integer Insertion Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunIntegerModificationTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Integer Modification Tests ===" << endl;
    
    try {
        lasd::Vector<int> baseData(6);
        int baseValues[] = {10, 25, 5, 40, 15, 30};
        for(int i = 0; i < 6; i++) {
            SetAt(loctestnum, loctesterr, baseData, true, i, baseValues[i]);
        }
        
        lasd::PQHeap<int> pq(baseData);
        
        // Test operazioni di modifica
        Change(loctestnum, loctesterr, pq, true, 0, 75);  // Cambia primo elemento
        Tip(loctestnum, loctesterr, pq, true, 75);
        
        Change(loctestnum, loctesterr, pq, true, 2, 1);   // Cambia a valore più piccolo
        Tip(loctestnum, loctesterr, pq, true, 75);
        
        Change(loctestnum, loctesterr, pq, true, 1, 80);  // Cambia indice 1 a 80
        Tip(loctestnum, loctesterr, pq, true, 80);
    
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Integer Modification Tests!" << endl;
    }
    
    cout << "Integer Modification Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunIntegerBoundaryTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Integer Boundary Tests ===" << endl;
    
    try {
        lasd::PQHeap<int> emptyPQ;

        Insert(loctestnum, loctesterr, emptyPQ, 123);
        TipNRemove(loctestnum, loctesterr, emptyPQ, true, 123);
        
        // Valori estremi
        lasd::PQHeap<int> extremePQ;
        Insert(loctestnum, loctesterr, extremePQ, numeric_limits<int>::max());
        Insert(loctestnum, loctesterr, extremePQ, numeric_limits<int>::min());
        Insert(loctestnum, loctesterr, extremePQ, 0);
        
        Tip(loctestnum, loctesterr, extremePQ, true, numeric_limits<int>::max());
        TipNRemove(loctestnum, loctesterr, extremePQ, true, numeric_limits<int>::max());
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Integer Boundary Tests!" << endl;
    }
    
    cout << "Integer Boundary Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunIntegerStressTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Integer Stress Tests ===" << endl;
    
    try {
        lasd::PQHeap<int> stressPQ;
        
        const int STRESS_SIZE = 100;
        for(int i = 0; i < STRESS_SIZE; i++) {
            Insert(loctestnum, loctesterr, stressPQ, mygenerateRandomInt(-500, 500));
        }
        
        lasd::Vector<int> removedElements(STRESS_SIZE);
        for(int i = 0; i < STRESS_SIZE; i++) {
            int currentMax = stressPQ.Tip();
            TipNRemove(loctestnum, loctesterr, stressPQ, true, currentMax);
            removedElements[i] = currentMax;
        }
        
        bool isDescending = true;
        for(int i = 1; i < STRESS_SIZE; i++) {
            if(removedElements[i-1] < removedElements[i]) {
                isDescending = false;
                break;
            }
        }
        if(isDescending) loctestnum++;

        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Integer Stress Tests!" << endl;
    }
    
    cout << "Integer Stress Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

/* ************************************************************************** */
// DOUBLE TESTS


void myRunDoubleBasicOperations(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Double Basic Operations Test ===" << endl;
    
    try {
        lasd::PQHeap<double> doublePQ;
        
        // Costanti matematiche
        double constants[] = {3.14159, 2.71828, 1.41421, 1.73205, 0.57721};
        for(int i = 0; i < 5; i++) {
            Insert(loctestnum, loctesterr, doublePQ, constants[i]);
        }
        
        Tip(loctestnum, loctesterr, doublePQ, true, 3.14159); 
        
        TipNRemove(loctestnum, loctesterr, doublePQ, true, 3.14159);
        Tip(loctestnum, loctesterr, doublePQ, true, 2.71828); 
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Double Basic Operations!" << endl;
    }
    
    cout << "Double Basic Operations completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunDoublePrecisionTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Double Precision Tests ===" << endl;
    
    try {
        lasd::PQHeap<double> precisionPQ;
        
        Insert(loctestnum, loctesterr, precisionPQ, 1.0000001);
        Insert(loctestnum, loctesterr, precisionPQ, 1.0000000);
        Insert(loctestnum, loctesterr, precisionPQ, 0.9999999);
        
        double topValue = precisionPQ.Tip();
        TipNRemove(loctestnum, loctesterr, precisionPQ, true, topValue);
        
        lasd::PQHeap<double> specialPQ;
        Insert(loctestnum, loctesterr, specialPQ, 0.0);
        Insert(loctestnum, loctesterr, specialPQ, -0.0);
        Insert(loctestnum, loctesterr, specialPQ, numeric_limits<double>::infinity());
        Insert(loctestnum, loctesterr, specialPQ, -numeric_limits<double>::infinity());
        
        Tip(loctestnum, loctesterr, specialPQ, true, numeric_limits<double>::infinity());
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Double Precision Tests!" << endl;
    }
    
    cout << "Double Precision Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunDoubleModificationTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Double Modification Tests ===" << endl;
    
    try {
        lasd::Vector<double> initialValues(4);
        double values[] = {2.5, 7.8, 1.2, 9.9};
        for(int i = 0; i < 4; i++) {
            SetAt(loctestnum, loctesterr, initialValues, true, i, values[i]);
        }
        
        lasd::PQHeap<double> pq(initialValues);
        
        Change(loctestnum, loctesterr, pq, true, 0, 15.5);
        Tip(loctestnum, loctesterr, pq, true, 15.5);
        
        Change(loctestnum, loctesterr, pq, true, 2, 0.1);
        Tip(loctestnum, loctesterr, pq, true, 15.5);
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Double Modification Tests!" << endl;
    }
    
    cout << "Double Modification Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunDoubleConstructorTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== Double Constructor Tests ===" << endl;
    
    try {
        // Container constructor
        lasd::Vector<double> sourceContainer(6);
        double containerValues[] = {4.4, 3.3, 5.5, 1.1, 2.2, 6.6};
        for(int i = 0; i < 6; i++) {
            SetAt(loctestnum, loctesterr, sourceContainer, true, i, containerValues[i]);
        }
        
        lasd::PQHeap<double> containerPQ(sourceContainer);

        Tip(loctestnum, loctesterr, containerPQ, true, 6.6);
        
        // Copy constructor
        lasd::PQHeap<double> copyPQ(containerPQ);
        Tip(loctestnum, loctesterr, copyPQ, true, 6.6);
        
        // Move constructor
        lasd::PQHeap<double> movePQ(std::move(copyPQ));

        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in Double Constructor Tests!" << endl;
    }
    
    cout << "Double Constructor Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

/* ************************************************************************** */
// STRING TESTS  


void myRunStringBasicOperations(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== String Basic Operations Test ===" << endl;
    
    try {
        lasd::PQHeap<string> stringPQ;
        
        // Inizializzazione e inserimento di stringhe (ho preso alcuni animali come esempio)
        string animals[] = {"Zebra", "Tiger", "Elephant", "Antelope", "Lion"};
        for(int i = 0; i < 5; i++) {
            Insert(loctestnum, loctesterr, stringPQ, animals[i]);
        }
        
        Tip(loctestnum, loctesterr, stringPQ, true, string("Zebra")); 
        
        TipNRemove(loctestnum, loctesterr, stringPQ, true, string("Zebra"));
        Tip(loctestnum, loctesterr, stringPQ, true, string("Tiger"));
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in String Basic Operations!" << endl;
    }
    
    cout << "String Basic Operations completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunStringCaseSensitivityTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== String Case Sensitivity Tests ===" << endl;
    
    try {
        lasd::PQHeap<string> casePQ;
        
        Insert(loctestnum, loctesterr, casePQ, string("apple"));
        Insert(loctestnum, loctesterr, casePQ, string("Apple"));
        Insert(loctestnum, loctesterr, casePQ, string("APPLE"));
        Insert(loctestnum, loctesterr, casePQ, string("Banana"));
    
        Tip(loctestnum, loctesterr, casePQ, true, string("apple"));
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in String Case Sensitivity Tests!" << endl;
    }
    
    cout << "String Case Sensitivity Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunStringSpecialCharacterTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== String Special Character Tests ===" << endl;
    
    try {
        lasd::PQHeap<string> specialPQ;
        
        Insert(loctestnum, loctesterr, specialPQ, string(""));
        Insert(loctestnum, loctesterr, specialPQ, string("a"));
        Insert(loctestnum, loctesterr, specialPQ, string("aa"));
        Insert(loctestnum, loctesterr, specialPQ, string("A"));
        
        Tip(loctestnum, loctesterr, specialPQ, true, string("aa"));
        
        // Caratteri speciali
        lasd::PQHeap<string> symbolPQ;
        Insert(loctestnum, loctesterr, symbolPQ, string("hello@world"));
        Insert(loctestnum, loctesterr, symbolPQ, string("hello#world"));
        Insert(loctestnum, loctesterr, symbolPQ, string("hello\nworld"));
        
        string maxSymbolString = symbolPQ.Tip();
        TipNRemove(loctestnum, loctesterr, symbolPQ, true, maxSymbolString);
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in String Special Character Tests!" << endl;
    }
    
    cout << "String Special Character Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunStringModificationTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== String Modification Tests ===" << endl;
    
    try {
        lasd::Vector<string> words(4);
        string wordList[] = {"Hello", "World", "Programming", "Data"};
        for(int i = 0; i < 4; i++) {
            SetAt(loctestnum, loctesterr, words, true, i, wordList[i]);
        }
        
        lasd::PQHeap<string> wordPQ(words);
        
        // Test di modifica
        Change(loctestnum, loctesterr, wordPQ, true, 0, string("Zzz"));
        Tip(loctestnum, loctesterr, wordPQ, true, string("Zzz"));
        
        Change(loctestnum, loctesterr, wordPQ, true, 1, string("Aaa"));
        Tip(loctestnum, loctesterr, wordPQ, true, string("Zzz"));
        
        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in String Modification Tests!" << endl;
    }
    
    cout << "String Modification Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}

void myRunStringDuplicateTests(uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << "\n=== String Duplicate Tests ===" << endl;
    
    try {
        lasd::PQHeap<string> duplicatePQ;
        
        // Inserimento di stringhe duplicate
        const string duplicateValue = "Duplicate";
        const int duplicateCount = 8;
        
        for(int i = 0; i < duplicateCount; i++) {
            Insert(loctestnum, loctesterr, duplicatePQ, duplicateValue);
        }
        
        Tip(loctestnum, loctesterr, duplicatePQ, true, duplicateValue);
        
        // Rimuove tutti i duplicati
        for(int i = 0; i < duplicateCount; i++) {
            TipNRemove(loctestnum, loctesterr, duplicatePQ, true, duplicateValue);
        }

        
    } catch(...) {
        loctestnum++; loctesterr++;
        cout << "Exception in String Duplicate Tests!" << endl;
    }
    
    cout << "String Duplicate Tests completed (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum; testerr += loctesterr;
}
/* ************************************************************************** */

void eseguiTest(uint & testnum, uint & testerr) {

    cout << endl << "Running tests..." << endl;
    
    // Integer Heap Tests
    myIntHeapTests(testnum, testerr);
    
    // Double Precision Heap Tests
    myDoubleHeapTests(testnum, testerr);
    
    // String Heap Tests
    myStringHeapTests(testnum, testerr);

    // Additional tests 
    myRunIntBasicOperations(testnum, testerr);
    myRunIntegerInsertionTests(testnum, testerr);
    myRunIntegerModificationTests(testnum, testerr);
    myRunIntegerBoundaryTests(testnum, testerr);
    myRunIntegerStressTests(testnum, testerr);
    myRunDoubleBasicOperations(testnum, testerr);
    myRunDoublePrecisionTests(testnum, testerr);
    myRunDoubleModificationTests(testnum, testerr);
    myRunDoubleConstructorTests(testnum, testerr);
    myRunStringBasicOperations(testnum, testerr);
    myRunStringCaseSensitivityTests(testnum, testerr);
    myRunStringSpecialCharacterTests(testnum, testerr);
    myRunStringModificationTests(testnum, testerr);
    myRunStringDuplicateTests(testnum, testerr);
    
    cout << "All tests completed!" << endl;
}


void mytest() {
  cout << endl
       << "Test LASD di Francesco Pio Illiano (N86004752) " << endl;
  cout << endl << endl
       << "Test esercizio 2 LASD " << endl;

  uint loctestnum, loctesterr;
  uint stestnum = 0, stesterr = 0;

  loctestnum = 0; loctesterr = 0;
  eseguiTest(loctestnum, loctesterr);
  stestnum += loctestnum;
  stesterr += loctesterr;
  cout << endl
       << "Esercizio 2(myTest) (Errors/Tests: " << stesterr << "/" << stestnum << ")\n";
}
/* ************************************************************************** */

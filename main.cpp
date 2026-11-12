#include <iostream>
#include <iomanip>
#include "BasicStructures/Pointers.h"
#include "Interfaces/SafeInput.h"
#include "BasicStructures/FunctionsForMapReduce.h"
#include "BasicStructures/DynamicArray.h"
#include "BasicStructures/Sequence.h"
#include "BasicStructures/ArraySequence.h"

#include "Trees/DictionaryTree.h"
#include "Trees/Node.h"
#include "Matriсes/RectangleMatrix.h"

#include "Knapsack/Knapsack.h"
#include "Knapsack/MatrKnap.h"

#include "Trees/ArrayNode.h"
#include "Trees/BinSearchTree.h"
#include "Knapsack/Compare.h"
#include "Knapsack/SortMatrKnap.h"

#include "Knapsack/KnapsackFunctions.h"
#include "Matriсes/MatrixFunctions.h"
#include "Trees/ArrayTree.h"
#include "Interfaces/ToString.h"

#include "Knapsack/MatrKnapFunc.h"

#include "Tests/Tests.h"

#include "Generation/NamesArray.h"
#include "Generation/RandomGenerator.h"
#include "Knapsack/CreateKnapsack.h"
#include "Interfaces/Interface.h"
//#include <SFML/Graphics.hpp>
//#include "Interfaces/GUI.h"

int main()
{
    BasicTests();
    MatrTests();
    //GUI();
    Interface(); 
}
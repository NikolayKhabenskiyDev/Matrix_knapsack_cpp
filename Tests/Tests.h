#ifndef TESTS_H
#define TESTS_H

#include <cassert>
#include "Knapsack/Knapsack.h"
#include "Knapsack/MatrKnap.h"
#include "Generation/RandomGenerator.h"
#include "Knapsack/CreateKnapsack.h"
#include "Knapsack/KnapsackFunctions.h"
#include "Knapsack/MatrKnapFunc.h"
#include "Interfaces/ToString.h"

void TestBasicKnap(KnapsackItem* items, int limit_weight, int amount, ArraySequenceMut<KnapsackContent*>* expected)
{
    std::cout << "Knapsack: limit weight - " << limit_weight << "\n\n";
    std::cout << "Possible items: " << "\n";
    for (int ii = 0; ii < amount; ii++)
    {
        std::cout << ToString(items[ii]);
    }
    std::cout << "\n";

    ArraySequenceMut<KnapsackContent>* result = KnapsackProblem(items, limit_weight, amount);

    std::cout << "Expected output: " << "\n" << ToString(expected);

    std::cout << "Real output: " << "\n" << ToString(result);

    assert(result->GetLength() == expected->GetLength());
    for (int ii = 0; ii < result->GetLength(); ii++)
    {
        assert(result->Get(ii) == expected->Get(ii));
    }
    std::cout << "TEST PASSED" << "\n" << "------------------------" << "\n";
    delete result;
}

void BasicTests()
{
    KnapsackItem item1 = KnapsackItem("travel journal", 5, 10);
    KnapsackItem item2 = KnapsackItem("computer", 50 , 10);
    KnapsackItem item3 = KnapsackItem("candy bars", 7, 20);
    KnapsackItem item4 = KnapsackItem("soccer ball", 8, 30);
    KnapsackItem item5 = KnapsackItem("clothes", 10, 40);
    KnapsackItem item6 = KnapsackItem("keys", 2, 1);
    KnapsackItem item7 = KnapsackItem("portable grill", 11, 45);

    KnapsackItem array1[1] = { item1 };
    KnapsackContent** best_cont1 = new KnapsackContent* [1];
    best_cont1[0] = new KnapsackContent(15);
    best_cont1[0]->AddElem(item1);
    ArraySequenceMut<KnapsackContent*>* expected1 = new ArraySequenceMut<KnapsackContent*>(best_cont1, 1);
    TestBasicKnap(array1, 15, 1, expected1);
    delete[] best_cont1;
    delete expected1;

    KnapsackItem array2[1] = { item2 };
    KnapsackContent** best_cont2 = new KnapsackContent* [1];
    best_cont2[0] = new KnapsackContent(15);
    ArraySequenceMut<KnapsackContent*>* expected2 = new ArraySequenceMut<KnapsackContent*>();
    TestBasicKnap(array2, 15, 1, expected2);
    delete[] best_cont2;
    delete expected2;

    KnapsackItem array3[2] = { item1, item4 };
    KnapsackContent** best_cont3 = new KnapsackContent* [1];
    best_cont3[0] = new KnapsackContent(30);
    best_cont3[0]->AddElem(item1);
    best_cont3[0]->AddElem(item4);
    ArraySequenceMut<KnapsackContent*>* expected3 = new ArraySequenceMut<KnapsackContent*>(best_cont3, 1);
    TestBasicKnap(array3, 30, 2, expected3);
    delete[] best_cont3;
    delete expected3;

    KnapsackItem array4[4] = { item1, item3, item4, item5 };
    KnapsackContent** best_cont4 = new KnapsackContent* [2];
    best_cont4[0] = new KnapsackContent(15);
    best_cont4[0]->AddElem(item1);
    best_cont4[0]->AddElem(item5);
    best_cont4[1] = new KnapsackContent(15);
    best_cont4[1]->AddElem(item3);
    best_cont4[1]->AddElem(item4);
    ArraySequenceMut<KnapsackContent*>* expected4 = new ArraySequenceMut<KnapsackContent*>(best_cont4, 2);
    TestBasicKnap(array4, 15, 4, expected4);
    delete[] best_cont4;
    delete expected4;

    KnapsackItem array5[5] = { item3, item4, item5, item6, item7 };
    KnapsackContent** best_cont5 = new KnapsackContent* [1];
    best_cont5[0] = new KnapsackContent(20);
    best_cont5[0]->AddElem(item4);
    best_cont5[0]->AddElem(item7);
    ArraySequenceMut<KnapsackContent*>* expected5 = new ArraySequenceMut<KnapsackContent*>(best_cont5, 1);
    TestBasicKnap(array5, 20, 5, expected5);
    delete[] best_cont5;
    delete expected5;

    KnapsackItem array6[30];
    KnapsackContent** best_cont6 = new KnapsackContent * [10];
    for (int ii = 0; ii < 30; ii++)
    {
        array6[ii] = KnapsackItem(item_names[ii+100], (ii + 1) * 2, ii + 1);
    }
    for (int ii = 0; ii < 10; ii++)
    {
        best_cont6[ii] = new KnapsackContent(20);
    }

    KnapsackItem item8 = KnapsackItem("earplugs", 2, 1);
    KnapsackItem item9 = KnapsackItem("sleep mask", 4, 2);
    KnapsackItem item10 = KnapsackItem("portable charger", 6, 3);
    KnapsackItem item11 = KnapsackItem("data cable", 8, 4);
    KnapsackItem item12 = KnapsackItem("notebook organizer", 10, 5);
    KnapsackItem item13 = KnapsackItem("pencil case", 12, 6);
    KnapsackItem item14 = KnapsackItem("art kit", 14, 7);
    KnapsackItem item15 = KnapsackItem("coloring book", 16, 8);
    KnapsackItem item16 = KnapsackItem("field guide", 18, 9);
    KnapsackItem item17 = KnapsackItem("nature journal", 20, 10);
    for (int ii = 0; ii < 5; ii++)
    {
        best_cont6[ii]->AddElem(item8);
    }
    best_cont6[0]->AddElem(item9);
    best_cont6[1]->AddElem(item9);
    best_cont6[5]->AddElem(item9);
    best_cont6[6]->AddElem(item9);
    best_cont6[0]->AddElem(item10);
    best_cont6[2]->AddElem(item10);
    best_cont6[5]->AddElem(item10);
    best_cont6[7]->AddElem(item10);
    best_cont6[0]->AddElem(item11);
    best_cont6[3]->AddElem(item11);
    best_cont6[8]->AddElem(item11);
    best_cont6[3]->AddElem(item12);
    best_cont6[5]->AddElem(item12);
    best_cont6[2]->AddElem(item13);
    best_cont6[8]->AddElem(item13);
    best_cont6[1]->AddElem(item14);
    best_cont6[7]->AddElem(item14);
    best_cont6[6]->AddElem(item15);
    best_cont6[4]->AddElem(item16);
    best_cont6[9]->AddElem(item17);
    ArraySequenceMut<KnapsackContent*>* expected6 = new ArraySequenceMut<KnapsackContent*>(best_cont6, 10);
    TestBasicKnap(array6, 20, 30, expected6);
    delete[] best_cont6;
    delete expected6;
}

void TestMatrKnap(ArraySequenceMut<MatrKnapItem*>* items, int limit_weight, int amount,
    int knap_height, int knap_width, ArraySequenceMut<MatrKnapContent*>* expected)
{
    std::cout << "Knapsack: limit weight - " << limit_weight
        << ", Height - " << knap_height << ", Width - " << knap_width << "\n\n";

    std::cout << "Possible items: " << "\n";
    std::cout << ToString(items);
    std::cout << "\n";

    ArraySequenceMut<MatrKnapContent*>* result = MatrKnapProblem(items, amount, limit_weight, knap_height, knap_width);

    std::cout << "Expected output: " << "\n" << expected;

    std::cout << "Real output: " << "\n" << result;

    assert(result->GetLength() == expected->GetLength());
    for (int ii = 0; ii < result->GetLength(); ii++)
    {
        assert(*(result->Get(ii)) == *(expected->Get(ii)));
    }
    std::cout << "TEST PASSED" << "\n" << "------------------------" << "\n";
    delete result;
}

void MatrTests()
{
    int array1[4] = {1, 0, 0, 1};
    int array2[8] = { 2, 0, 2, 2, 2, 2, 2, 0 };
    int array3[4] = { 3, 3, 3, 3 };
    int array4[4] = { 4, 4, 4, 4 };
    int array5[3] = { 5, 5, 5 };
    int array6[15] = { 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6 };
    int array7[1] = { 7 };
    int array8[1] = { 8 };
    int array9[6] = { 9, 9, 9, 0, 9, 9 };
    int array10[6] = { 0, 10, 10, 10, 0, 10 };
    int array11[9] = { 0, 0, 11, 11, 0, 11, 11, 11, 0 };
    int array12[1] = { 12 };

    RectangleMatrix<int>* matr1 = new RectangleMatrix<int>(2, 2, array1);
    RectangleMatrix<int>* matr2 = new RectangleMatrix<int>(2, 4, array2);
    RectangleMatrix<int>* matr3 = new RectangleMatrix<int>(4, 1, array3);
    RectangleMatrix<int>* matr4 = new RectangleMatrix<int>(4, 1, array4);
    RectangleMatrix<int>* matr5 = new RectangleMatrix<int>(3, 1, array5);
    RectangleMatrix<int>* matr6 = new RectangleMatrix<int>(5, 3, array6);
    RectangleMatrix<int>* matr7 = new RectangleMatrix<int>(1, 1, array7);
    RectangleMatrix<int>* matr8 = new RectangleMatrix<int>(1, 1, array8);
    RectangleMatrix<int>* matr9 = new RectangleMatrix<int>(3, 2, array9);
    RectangleMatrix<int>* matr10 = new RectangleMatrix<int>(2, 3, array10);
    RectangleMatrix<int>* matr11 = new RectangleMatrix<int>(3, 3, array11);
    RectangleMatrix<int>* matr12 = new RectangleMatrix<int>(1, 1, array12);

    MatrKnapItem* item1 = new MatrKnapItem("travel journal", 5, 10, matr1);
    MatrKnapItem* item2 = new MatrKnapItem("computer", 50, 10, matr2);
    MatrKnapItem* item3 = new MatrKnapItem("candy bars", 7, 20, matr3);
    MatrKnapItem* item4 = new MatrKnapItem("soccer ball", 8, 30, matr4);
    MatrKnapItem* item5 = new MatrKnapItem("clothes", 10, 40, matr5);
    MatrKnapItem* item6 = new MatrKnapItem("portable grill", 11, 45, matr6);
    MatrKnapItem* item7 = new MatrKnapItem("keys", 2, 1, matr7);
    MatrKnapItem* item8 = new MatrKnapItem("earplugs", 5, 5, matr8);
    MatrKnapItem* item9 = new MatrKnapItem("art kit", 6, 5, matr9);
    MatrKnapItem* item10 = new MatrKnapItem("baseball glove", 6, 5, matr10);
    MatrKnapItem* item11 = new MatrKnapItem("field guide", 9, 5, matr11);
    MatrKnapItem* item12 = new MatrKnapItem("nature journal", 3, 2, matr12);

    ArraySequenceMut<MatrKnapItem*>* seq1 = new ArraySequenceMut<MatrKnapItem*>();
    seq1->Append(item1);
    MatrKnapContent** best_cont1 = new MatrKnapContent * [1];
    best_cont1[0] = new MatrKnapContent(15, 2, 2);
    best_cont1[0]->AddElem(item1, 0, 0);
    ArraySequenceMut<MatrKnapContent*>* expected1 = new ArraySequenceMut<MatrKnapContent*>(best_cont1, 1);
    TestMatrKnap(seq1, 15, 1, 2, 2, expected1);
    delete[] best_cont1;
    delete seq1;
    delete expected1;

    ArraySequenceMut<MatrKnapItem*>* seq2 = new ArraySequenceMut<MatrKnapItem*>();
    seq2->Append(item1);
    MatrKnapContent** best_cont2 = new MatrKnapContent * [4];
    best_cont2[0] = new MatrKnapContent(15, 3, 3);
    best_cont2[0]->AddElem(item1, 0, 0);
    best_cont2[1] = new MatrKnapContent(15, 3, 3);
    best_cont2[1]->AddElem(item1, 0, 1);
    best_cont2[2] = new MatrKnapContent(15, 3, 3);
    best_cont2[2]->AddElem(item1, 1, 0);
    best_cont2[3] = new MatrKnapContent(15, 3, 3);
    best_cont2[3]->AddElem(item1, 1, 1);
    ArraySequenceMut<MatrKnapContent*>* expected2 = new ArraySequenceMut<MatrKnapContent*>(best_cont2, 4);
    TestMatrKnap(seq2, 15, 1, 3, 3, expected2);
    delete[] best_cont2;
    delete seq2;
    delete expected2;

    ArraySequenceMut<MatrKnapItem*>* seq3 = new ArraySequenceMut<MatrKnapItem*>();
    seq3->Append(item2);
    ArraySequenceMut<MatrKnapContent*>* expected3 = new ArraySequenceMut<MatrKnapContent*>();
    TestMatrKnap(seq3, 15, 1, 3, 3, expected3);
    delete expected3;
    delete seq3;

    ArraySequenceMut<MatrKnapItem*>* seq4 = new ArraySequenceMut<MatrKnapItem*>();
    seq4->Append(item2);
    ArraySequenceMut<MatrKnapContent*>* expected4 = new ArraySequenceMut<MatrKnapContent*>();
    TestMatrKnap(seq4, 60, 1, 3, 3, expected4);
    delete expected4;
    delete seq4;

    ArraySequenceMut<MatrKnapItem*>* seq5 = new ArraySequenceMut<MatrKnapItem*>();
    seq5->Append(item3);
    seq5->Append(item4);
    seq5->Append(item5);
    MatrKnapContent** best_cont5 = new MatrKnapContent * [12];
    best_cont5[0] = new MatrKnapContent(30, 4, 3);
    best_cont5[0]->AddElem(item3, 0, 0);
    best_cont5[0]->AddElem(item4, 0, 1);
    best_cont5[0]->AddElem(item5, 0, 2);
    best_cont5[1] = new MatrKnapContent(30, 4, 3);
    best_cont5[1]->AddElem(item3, 0, 0);
    best_cont5[1]->AddElem(item4, 0, 1);
    best_cont5[1]->AddElem(item5, 1, 2);
    best_cont5[2] = new MatrKnapContent(30, 4, 3);
    best_cont5[2]->AddElem(item3, 0, 0);
    best_cont5[2]->AddElem(item4, 0, 2);
    best_cont5[2]->AddElem(item5, 0, 1);
    best_cont5[3] = new MatrKnapContent(30, 4, 3);
    best_cont5[3]->AddElem(item3, 0, 0);
    best_cont5[3]->AddElem(item4, 0, 2);
    best_cont5[3]->AddElem(item5, 1, 1);
    best_cont5[4] = new MatrKnapContent(30, 4, 3);
    best_cont5[4]->AddElem(item3, 0, 1);
    best_cont5[4]->AddElem(item4, 0, 0);
    best_cont5[4]->AddElem(item5, 0, 2);
    best_cont5[5] = new MatrKnapContent(30, 4, 3);
    best_cont5[5]->AddElem(item3, 0, 1);
    best_cont5[5]->AddElem(item4, 0, 0);
    best_cont5[5]->AddElem(item5, 1, 2);
    best_cont5[6] = new MatrKnapContent(30, 4, 3);
    best_cont5[6]->AddElem(item3, 0, 1);
    best_cont5[6]->AddElem(item4, 0, 2);
    best_cont5[6]->AddElem(item5, 0, 0);
    best_cont5[7] = new MatrKnapContent(30, 4, 3);
    best_cont5[7]->AddElem(item3, 0, 1);
    best_cont5[7]->AddElem(item4, 0, 2);
    best_cont5[7]->AddElem(item5, 1, 0);
    best_cont5[8] = new MatrKnapContent(30, 4, 3);
    best_cont5[8]->AddElem(item3, 0, 2);
    best_cont5[8]->AddElem(item4, 0, 0);
    best_cont5[8]->AddElem(item5, 0, 1);
    best_cont5[9] = new MatrKnapContent(30, 4, 3);
    best_cont5[9]->AddElem(item3, 0, 2);
    best_cont5[9]->AddElem(item4, 0, 0);
    best_cont5[9]->AddElem(item5, 1, 1);
    best_cont5[10] = new MatrKnapContent(30, 4, 3);
    best_cont5[10]->AddElem(item3, 0, 2);
    best_cont5[10]->AddElem(item4, 0, 1);
    best_cont5[10]->AddElem(item5, 0, 0);
    best_cont5[11] = new MatrKnapContent(30, 4, 3);
    best_cont5[11]->AddElem(item3, 0, 2);
    best_cont5[11]->AddElem(item4, 0, 1);
    best_cont5[11]->AddElem(item5, 1, 0);
    ArraySequenceMut<MatrKnapContent*>* expected5 = new ArraySequenceMut<MatrKnapContent*>(best_cont5, 12);
    TestMatrKnap(seq5, 30, 3, 4, 3, expected5);
    delete[] best_cont5;
    delete seq5;
    delete expected5;

    ArraySequenceMut<MatrKnapItem*>* seq6 = new ArraySequenceMut<MatrKnapItem*>();
    seq6->Append(item6);
    seq6->Append(item7);
    seq6->Append(item8);
    MatrKnapContent** best_cont6 = new MatrKnapContent * [2];
    best_cont6[0] = new MatrKnapContent(15, 5, 3);
    best_cont6[0]->AddElem(item6, 0, 0);
    best_cont6[0]->AddElem(item7, 1, 1);
    best_cont6[1] = new MatrKnapContent(15, 5, 3);
    best_cont6[1]->AddElem(item6, 0, 0);
    best_cont6[1]->AddElem(item7, 3, 1);
    ArraySequenceMut<MatrKnapContent*>* expected6 = new ArraySequenceMut<MatrKnapContent*>(best_cont6, 2);
    TestMatrKnap(seq6, 15, 3, 5, 3, expected6);
    delete[] best_cont6;
    delete seq6;
    delete expected6;



    delete matr1;
    delete matr2;
    delete matr3;
    delete matr4;
    delete matr5;
    delete matr6;
    delete matr7;
    delete matr8;
    delete matr9;
    delete matr10;
    delete matr11;
    delete matr12;

    delete item1;
    delete item2;
    delete item3;
    delete item4;
    delete item5;
    delete item6;
    delete item7;
    delete item8;
    delete item9;
    //delete item10;
    delete item11;
    delete item12;
}

#endif
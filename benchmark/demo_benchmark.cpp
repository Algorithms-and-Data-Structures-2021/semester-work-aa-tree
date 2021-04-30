#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

//Путь к папке с наборами данных для заполнения
const string setsPath = "C:\\Users\\EvveKiNG\\CLionProjects\\semester-work-aa-tree-fixiki\\dataset\\data";

//Путь к файлу с наборами данных для тестов добавления/поиска/удаления
const string testPath = "C:\\Users\\EvveKiNG\\CLionProjects\\semester-work-aa-tree-fixiki\\dataset\\test.csv";

// Сгенирировать наборы даннх : https://github.com/rthoor/generation.git


//укажите названия папок с наборами данных, если они есть
//string folders[10] = {"/01/","/02/","/03/","/04/","/05/",
//                      "/06/","/07/", "/08/", "/09/","/10/"};

//если их нет
string folders[1] = {"/"};

//укажите названия файлов с наборами данных (без .csv)
string files[14] = {"100", "500", "1000", "5000", "10000", "25000", "50000", "100000",
                    "250000", "500000", "750000", "1000000", "2500000", "5000000"};

//Путь к папке, куда нужно выгрузить результаты
const string outputPath = "C:/Users/EvveKiNG/Desktop/results/";

// Ознакомтесь с директорией "results-path-example/results"
// в папке выгруза результатов нужно будет реализовать похожую структуру,
// опираясь на названия файлов в массиве files

// -----------------------------------
// запускать main() (в самом низу)   |
// -----------------------------------

//Вывод результатов
void writeResults(string file, long insert_time, long search_time, long delete_time) {
    const auto output = string(outputPath);

    // вывод результата добавления
    std::ofstream out(output + file + "/insert_result.txt", std::ios::app);
    if (out.is_open()) {
        out << insert_time << std::endl;
    }
    out.close();

    // вывод результата поиска
    std::ofstream out1(output + file + "/search_result.txt", std::ios::app);
    if (out1.is_open()) {
        out1 << search_time << std::endl;
    }
    out1.close();

    // вывод результата удаления
    std::ofstream out2(output + file + "/delete_result.txt", std::ios::app);
    if (out2.is_open()) {
        out2 << delete_time << std::endl;
    }
    out2.close();
}

void TestModeOne() {
    string line;
    for (auto file : files) {
        for (auto folder : folders) {
            for (int i = 0; i < 10; i++) { // i = сколько раз прогоняем один и тот же csv файл
                auto input_file_insert = ifstream(setsPath + folder + file + ".csv");
                auto input_file_search = ifstream(setsPath + folder + file + ".csv");
                auto input_file_delete = ifstream(setsPath + folder + file + ".csv");

                // Создание структуры
                AATree *tree = new AATree;

                // добавление
                auto time_point_before_insert = chrono::steady_clock::now();
                while (getline(input_file_insert, line, ',')) {
                    tree->Add(stoi(line));
                }
                auto time_point_after_insert = chrono::steady_clock::now();
                auto time_diff_insert = time_point_after_insert - time_point_before_insert;
                long insert_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_insert).count();


                // поиск
                auto time_point_before_search = chrono::steady_clock::now();
                while (getline(input_file_search, line, ',')) {
                    tree->Search(stoi(line));
                }
                auto time_point_after_search = chrono::steady_clock::now();
                auto time_diff_search = time_point_after_search - time_point_before_search;
                long search_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_search).count();


                // удаление
                auto time_point_before_delete = chrono::steady_clock::now();
                while (getline(input_file_delete, line, ',')) {
                    tree->Delete(stoi(line));
                }
                auto time_point_after_delete = chrono::steady_clock::now();
                auto time_diff_delete = time_point_after_delete - time_point_before_delete;
                long delete_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_delete).count();

                delete tree;

                writeResults(file, insert_time, search_time, delete_time);
            }
        }
    }
}

void TestModeTwo() {
    string line;
    string num;
    for (auto file : files) {
        auto test_file = ifstream(testPath);
        while (getline(test_file, num, ',')) {
            for (int i = 0; i < 10; i++) { // i = сколько раз прогоняем один и тот же элемент
                auto input_file = ifstream(setsPath + file + ".csv");

                // Создание структуры
                AATree *tree = new AATree;

                // заполнение структуры
                while (getline(input_file, line, ',')) {
                    tree->Add(stoi(line));
                }

                // добавление
                auto time_point_before_insert = chrono::steady_clock::now();
                tree->Add(stoi(num));
                auto time_point_after_insert = chrono::steady_clock::now();
                auto time_diff_insert = time_point_after_insert - time_point_before_insert;
                long insert_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_insert).count();


                // поиск
                auto time_point_before_search = chrono::steady_clock::now();
                tree->Search(stoi(num));
                auto time_point_after_search = chrono::steady_clock::now();
                auto time_diff_search = time_point_after_search - time_point_before_search;
                long search_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_search).count();


                // удаление
                auto time_point_before_delete = chrono::steady_clock::now();
                tree->Delete(stoi(num));
                auto time_point_after_delete = chrono::steady_clock::now();
                auto time_diff_delete = time_point_after_delete - time_point_before_delete;
                long delete_time = chrono::duration_cast<chrono::nanoseconds>(time_diff_delete).count();


                //запись данных
                writeResults(file, insert_time, search_time, delete_time);
                delete tree;
            }
        }
    }
}

int main() {

    //есть два режима тестирования:
    // 1) Прогоняется сначала последовательное добавление N кол-ва элементов,
    //                потом последовательный поиск каждого и затем удаление каждого
    // 2) Прогоняется добавление, удаление и поиск в дереве из N-элементов (сначала добавится, допустим, 100 элементов,
    //                а далее будет засекаться добавление, поиск и удаление нового элемента

    enum class Mode {
        ONE,
        TWO
    };

    //Установите режим
    Mode mode = Mode::ONE;

    switch (mode) {
        case Mode::ONE:
            TestModeOne();
        case Mode::TWO:
            TestModeTwo();
    }

    return 0;
}


#include <conio.h>

#include <io.h>      // для функции _setmode
#include <fcntl.h>   // для константы _O_U16TEXT
#include <fstream>   // для файлового ввода/вывода
#include <iostream>
#include <string>    // для работы с классом wstring
#include <codecvt>   // для работы с фасетом codecvt_utf8 локали

#include <clocale>
#include <sstream>

#include "simpleDB.h"
using namespace std;

// class MBuf : public std::stringbuf {
// public:
//  int sync() override {
//    fputs(str().c_str(), stdout);
//    str("");
//    return 0;
//  }
//};

int main() {

  _setmode(_fileno(stdout), _O_U8TEXT);
  _setmode(_fileno(stdin), _O_U8TEXT);
  _setmode(_fileno(stderr), _O_U8TEXT);

  const locale utf8_locale = locale(locale(),	new codecvt_utf8<wchar_t>());

  wchar_t ch = L'ы';                        // русская буква 'ы'
  int j = 77;
  double d = 6.02;
  wstring str1 = L"Kafka";                  // две строки (одна — с латинскими буквами,
  wstring str2 = L"Пруст";                  // другая — с русскими) без пробелов

 std:: wofstream outfile("файл с данными.txt"); // создать объект класса wofstream
  outfile.imbue(utf8_locale);               // связываем наш поток с нужной локалью

  outfile << ch                             // вставить (записать) данные
          << j
          << L' '                           // числа разделим пробелом
          << d
          << str1
          << L' '                           // строки тоже разделим пробелом
          << str2;

  wcout << L"Файл записан\n";









  //  SetConsoleCP(CP_UTF8);
  //  SetConsoleOutputCP(CP_UTF8);
  //  setvbuf(stdout, nullptr, _IONBF, 1000);

  //  MBuf buf;
  //  std::cout.rdbuf(&buf);

  //    std::cout << "Russian: абвгд" << std::flush;

  //    _setmode(_fileno(stdout), _O_U8TEXT);
  //  setlocale(LC_ALL, "Russian");
  //      system("chcp 65001");
  //      SetConsoleCP(65001);
  //      SetConsoleOutputCP(65001);

  string oper;
  while (1) {
    wcout << "1 - Отобразить все записи базы данных:\n"
          << "2 - Просмотр существующей записи:\n"
          << "3 - Ввод новой записи:\n"
          << "4 - Редактирование существующей записи:\n"
          << "5 - Удаление записи:\n"
          << "6 - Завершить работу:\n\n"
          << "Введите операцию: ";
    cin >> oper;
    regex regexpr("[123456]");
    if (regex_match(oper, regexpr)) {
      if (oper == "1") read_data();
      if (oper == "2") view_data();
      if (oper == "3") input_data();
      if (oper == "4") edit_data();
      if (oper == "5") remove_data();
      if (oper == "6") return 0;
    } else {
      system("cls");
      cout << "Повторите ввод\n\n";
    }
  }
}

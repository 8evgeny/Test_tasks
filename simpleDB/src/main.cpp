#include <conio.h>
#include <clocale>
#include "simpleDB.h"
#include <sstream>
using namespace std;

class MBuf: public std::stringbuf {
public:
int sync() {
fputs( str().c_str(), stdout );
str( "" );
return 0;
}
};



int main(int argc, char** argv) {

    SetConsoleOutputCP( CP_UTF8 );
    setvbuf( stdout, nullptr, _IONBF, 0 );

    MBuf buf;
    std::cout.rdbuf( &buf );
//    std::cout << "Russian: абвгд" << std::flush;

//    _setmode(_fileno(stdout), _O_U8TEXT);
//  setlocale(LC_ALL, "Russian");
//      system("chcp 65001");
//      SetConsoleCP(65001);
//      SetConsoleOutputCP(65001);

  string oper;
  while (1) {
    cout << "Введите операцию:\n"
         << "1 - Отобразить все записи базы данных:\n"
         << "2 - Просмотр существующей записи:\n"
         << "3 - Ввод новой записи:\n"
         << "4 - Редактирование существующей записи:\n"
         << "5 - Удаление записи:\n"
         << "6 - Завершить работу:\n";
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

#include "simpleDB.h"
using namespace std;

class Buf_out: public std::stringbuf {
public:
int sync() override {
fputs( str().c_str(), stdout );
str( "" );
return 0;
}
};

int main() {

    SetConsoleOutputCP(CP_UTF8);
//    setvbuf( stdout, nullptr, _IONBF, 0 );

    Buf_out bufout;
    std::cout.rdbuf( &bufout );

  string oper;
  while (1) {
    cout << "1 - Работа с существующими записями:\n"
         << "2 - Ввод новой записи:\n"
         << "3 - Завершить работу:\n\n"
         << "Введите операцию: "<<flush;
    cout<<endl;

    cin >> oper;
    regex regexpr("[123456]");
    if (regex_match(oper, regexpr)) {
      if (oper == "1") work_with_DB();
      if (oper == "2") input_data();
      if (oper == "3") return 0;
    } else {

          cout << "Повторите ввод  "<<flush;
          cout<<endl;
    }
  }
}

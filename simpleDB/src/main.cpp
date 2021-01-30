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
 Buf_out bufout;
 std::cout.rdbuf( &bufout );
 string oper;
 while (1) {
  cout << "1 - Просмотр существующиx записей:\n"
       << "2 - Ввод новой записи:\n"
       << "3 - Редактирование существующей записи:\n"
       << "4 - Удаление записи:\n"
       << "5 - Завершить работу:\n\n"
       << "Введите операцию: "<<flush;
  cout<<endl;
  cin >> oper;
  regex regexpr("[123456]");
  if (regex_match(oper, regexpr)) {
   if (oper == "1") view_data();
   if (oper == "2") input_data();
   if (oper == "3") edit_data();
   if (oper == "4") remove_data();
   if (oper == "5") return 0;
  } else {
 cout << "Повторите ввод  "<<flush;
 cout<<endl;
    }
 }
}

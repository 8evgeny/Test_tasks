#include "simpleDB.h"
using namespace std;
void work_with_DB(){
cout<<"Работаем с существующими записями\n";
view_data();
string oper;

//      if (oper == "2")
//      if (oper == "4")
//      if (oper == "5")




while (1) {
  cout << "1 - Выберите номер записи:\n"
       << "0 - Возврат в предыдущее меню:\n\n"
       << "Введите операцию: "<<flush;
  cout<<endl;

  cin >> oper;
  regex regexpr("[01]");
  if (regex_match(oper, regexpr)) {
    if (oper == "1") view_data();
    if (oper == "2") edit_data();
    if (oper == "3") remove_data();
  } else {

        cout << "Повторите ввод  "<<flush;
        cout<<endl;
  }
}








}

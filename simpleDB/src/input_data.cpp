#include "simpleDB.h"
#include "person.h"
using namespace std;
void input_data(){
 system("cls");
 Person person;
 auto max = person.read_max();
 cout<<"Вводим новые данные:\n";
 person.input_name();
 person.input_sex();
 person.input_bithday();
 QDate current_date;
 current_date=QDate::currentDate();
 cout<<"Текущая дата: "<<current_date.toString().toStdString()<<"\n";

  int days = static_cast<int>(person.bithday.daysTo(current_date));
  int age = days/365;
  if (age>max.max_long_life) {
      person.live = false;
      person.input_death();
  }
 person.input_growth(max.max_growth);
 person.input_weight(max.max_weight);
 person.input_nation();
 string  ilive, isave;
 if(person.live){
      cout<<"Введите:\n"<<
            "1 - человек жив\n"<<
            "2 - человек умер   "<<flush;
      cout<<endl;
      while(1){
          cin>>ilive;
          regex regexpr ("[12]");
          if (regex_match (ilive,regexpr)) {
              if(stoi(ilive)==2){
                person.live = false;
                person.input_death();
              }
              break;
          } else  cout << "Ошибка ввода!\n";
      }
  }

  if (person.live) person.age = static_cast<unsigned>(age);
  else{
      person.age = static_cast<unsigned>(person.bithday.daysTo(person.death)/365);
  }
  system("cls");
  person.print();
  cout <<"Введенные данные верны?\n"<<
         "Введите :\n"<<
         "1 - cохраненить данные\n"<<
         "2 - не сохранять   "<<flush;
  cout<<endl;
  while(1){
      cin>>isave;
      regex regexpr ("[12]");
      if (regex_match (isave,regexpr)) {
          if(stoi(isave)==1) person.save_person();
          if(stoi(isave)==2) {
           person.live = true;
          }
       break;
      } else  cout << "Ошибка ввода!\n";
  }

}



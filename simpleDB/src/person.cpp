#include "simpleDB.h"
#include "person.h"
using namespace std;
 Person::Person(){
     live=true;
     age = 0;
     weight=0;
     growth=0;
    };

 Person::~Person(){};
 void Person::print(){
     std::cout
         <<"1\t���: "<<name.toStdString()<<"\n"
         <<"2\t���: "<<sex.toStdString()<<"\n"
         <<"3\t�������: "<<age<<"\n"
         <<"4\t����: "<<growth<<"\n"
         <<"5\t���: "<<weight<<"\n"
         <<"6\t��������������: "<<nation.toStdString()<<"\n"
         <<"7\t���� ��������: "<<Person::bithday.toString().toStdString()<<"\n"
         <<"8\t���� ������: "<<Person::death.toString().toStdString()<<"\n"
         <<"\n";
 }
 void Person::read_person(string & name){
     QString patch_to_DB = read_patch_DB();
     string path = patch_to_DB.toStdString()+"/"+name;
     fstream file;
     file.open(path, fstream::out | fstream::in | fstream::binary);
     if(!file.is_open()) cout<<"error opening file\n";
     else{
 string name;
 string sex;
 string age;
 string growth;
 string weight;
 string nation;
 string bithday;
 string death;
 string live;
 const QString DateFormat = "dd/MM/yyyy";
 file>>name;
 file>>sex;
 file>>age;
 file>>growth;
 file>>weight;
 file>>nation;
 file>>bithday;
 file>>death;
 file>>live;
 cout<<"\nread from file: "<< name<<"\n";
 this->name = QString::fromStdString(name);
 this->sex = QString::fromStdString(sex);
 this->age = stoi(age);
 this->growth = stoi(growth);
 this->weight = stoi(weight);
 this->nation = QString::fromStdString(nation);
 this->bithday = string_toqtate(bithday);
 this->live = stoi(live);
 if(this->live == 0) this->death = string_toqtate(death);
     }
     file.close();
 }
 void Person::save_person(){
     QString patch_to_DB = read_patch_DB();
     string path = patch_to_DB.toStdString()+"/"+this->name.toStdString();
     fstream file;
     file.open(path, fstream::out | fstream::binary);
     if(!file.is_open()) cout<<"error opening file\n";
     else{
const QString DateFormat = "dd/MM/yyyy";
        file<<this->name.toStdString()<<"\n";
        file<<this->sex.toStdString()<<"\n";
        file<<this->age<<"\n";
        file<<this->growth<<"\n";
        file<<this->weight<<"\n";
        file<<this->nation.toStdString()<<"\n";
        file<<this->bithday.toString(DateFormat).toStdString()<<"\n";
        if (!this->live) file<<this->death.toString(DateFormat).toStdString()<<"\n";
        if (this->live) file<<"no"<<"\n";
        file<<this->live<<"\n";
         cout<<"data saved in: "<< this->name.toStdString()<<"\n";
     }
     file.close();
 }
 void Person::input_name(){
     cout<<"\ninput name:\n";
     string iname;
      while(1){
       cin>>iname;
       regex regexpr ("[A-Za-z�-��-���]+");
       if (regex_match (iname,regexpr)) {
           this->name = QString::fromStdString(iname);
          break;
       } else  cout << "incorrect!\n";
      }
      cout << "name: "<<this->name.toStdString()<<"\n";
 }
 void Person::input_sex(){
  string isex;
 cout <<"\ninput sex:\n"<<"1 - male\n"<<"2 - female\n";
 while(1){
  cin>>isex;
   regex regexpr ("[12]");
  if (regex_match (isex,regexpr)) {
       if(stoi(isex)==1)this->sex = "�������";
       else this->sex = "�������";
     break;
  } else  cout << "incorrect!\n";
 }
 cout << "sex: "<<this->sex.toStdString()<<"\n";
 }
 QDate Person::input_bithday(){
  string ibighday;
 cout<<   "\ninput bithday in format DD/MM/YYYY:\n";
//Дата рождения
const QString DateFormat = "dd/MM/yyyy";
while(1){
 cin>>ibighday;
 regex regexpr (
"(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/](1[0-9][0-9]{2}|[2][0][0-9]{2})"
);
 if (regex_match (ibighday,regexpr)) {
  this->bithday = string_toqtate(ibighday);
  break;
 } else  cout << "incorrect!\n";
}
 cout<<"data of bithday: "<<
    this->bithday.toString(DateFormat).toStdString()<<"\n";
 return this->bithday;
}
 QDate Person::input_death(){
      string ideath;
      cout<< "\ninput data of death in format DD/MM/YYYY:\n";
      const QString DateFormat = "dd/MM/yyyy";
      QDate death, current;
      while(1){
       cin>>ideath;
       regex regexpr (
     "(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/](1[0-9][0-9]{2}|[2][0][0-9]{2})"
       );
       if (regex_match (ideath,regexpr)) {
        string day = ideath.substr(0,2);
        string mounth = ideath.substr(3,2);
        string year = ideath.substr(6,4);
        death.setDate(stoi(year),stoi(mounth),stoi(day));
        current=QDate::currentDate();
        QDate bithday = this->bithday;
        int days_from_bithday = bithday.daysTo(death);
        int days_to_current = death.daysTo(current);
        if((days_from_bithday>0) &&(days_to_current>0)){
         this->death = death;
         break;
        } else  cout << "incorrect!\n";
       } else  cout << "incorrect!\n";
      }
      cout<<"data of death: "<<this->death.toString(DateFormat).toStdString()<<"\n";
      return this->death;
 }
 void Person::input_growth(int max_growth){
 string igrowth;
  cout<< "\ninput growth: \n";
  while(1){
      cin>>igrowth;
      regex regexpr ("[1-9]{1}[0-9]{0,2}");
      if (regex_match (igrowth,regexpr)) {
          if(stoi(igrowth)<=max_growth){
          this->growth = stoi(igrowth);
          break;
          } else  cout << "incorrect!\n";
      } else  cout << "incorrect!\n";
  }
  cout << "\ngrowth: "<<this->growth<<"\n\n";
}
 void Person::input_weight(int max_weight){
 string iweight;
 cout<< "\ninput weight: \n";
 while(1){
     cin>>iweight;
     regex regexpr ("[1-9]{1}[0-9]{0,2}");
     if (regex_match (iweight,regexpr)) {
         if(stoi(iweight)<=max_weight){
         this->weight = stoi(iweight);
         break;
         } else  cout << "incorrect!\n";
     } else  cout << "incorrect!\n";
  }
 cout << "\nweight: "<<this->weight<<"\n";
 }
 void Person::input_nation(){
 string inations;
  vector <pair<unsigned,string>> listnations;
  print_nation(listnations);
  cout<<"\ninput nation. choose number from list:\n";
  while(1){
      cin>>inations;
      regex regexpr ("[1-9]{1}[0-9]{0,2}");
      if (regex_match (inations,regexpr)) {
          if (stold(inations) <= listnations.size()) {
          string nation = listnations.at(stoi(inations)-1).second;
          this->nation = QString::fromStdString(nation);
          break;
          } else  cout << "incorrect!\n";
      } else  cout << "incorrect!\n";
  }
   cout << "nation: "<<this->nation.toStdString()<<"\n";
 }

 Person::max Person::read_max(){
     Person::max max;
     QSettings settings(settingsFile, QSettings::IniFormat);
     settings.beginGroup("person");
     max.max_long_life  = settings.value("max_long_life").toInt();
     max.max_growth  = settings.value("max_growth").toInt();
     max.max_weight  = settings.value("max_weight").toInt();
     settings.endGroup();
     return max;
 }

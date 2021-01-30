#include "simpleDB.h"
 using namespace std;
 void fill_vector(QStringList& listFiles, vector<std::string>& v) {
  for (auto& file : listFiles) {
   v.push_back(file.toStdString());
  }
 }
 void print_vector(vector<string>& v) {
  int i = 1;
  for (auto element : v)  {
   cout<<i<<" "<<element<<'\n';
   ++i;
  }
  cout<<'\n';
 }
void print_vector(vector<pair<unsigned,string>>& v) {
 cout<<"Наций: "<<v.size()<<"   "<<flush<<"\n";
 for (auto element : v)  {
  cout<<element.first<<" "<<element.second<<"   "<<flush<<"\n";
 }
}
QDate string_toqtate(string stringdate){
 QDate date;
 string day = stringdate.substr(0,2);
 string mounth = stringdate.substr(3,2);
 string year = stringdate.substr(6,4);
 date.setDate(stoi(year),stoi(mounth),stoi(day));
 return date;
}
void delete_file(QString & name){
 QString patch_to_DB = read_patch_DB();
 string patch = patch_to_DB.toStdString()+"/" + name.toStdString();
 remove(patch.c_str());
}
void view_data(){
 Person person;
 string num;
 unsigned i;
 unsigned number_person = read_data();
 cout<<"Введите номер записи для просмотра: \n"<<
 "Для возврата введите 0   "<<flush;
 cout<<endl;
 while(1){
  cin>>num;
  regex regexpr ("[0-9]+");
  if (regex_match (num,regexpr)) {
   i = static_cast<unsigned>(stoi(num));
   if(i <= number_person) {
   break;
   }else cout << "Ошибка ввода!\n";
  } else  cout << "Ошибка ввода!\n";
 }
// i - номер записи для показа
 if (i!=0){
  string name = name_from_number(static_cast<int>(i));
  person.read_person(name);
  person.print();}
 }
 unsigned read_data(){
  system("cls");
  std::vector<std::string> v;
  QDir dirDB;
  QString patch = read_patch_DB();
  dirDB.setPath(patch);
  QStringList listFiles = dirDB.entryList(QDir::Files);
  fill_vector(listFiles, v);
  cout<<"Все записи базы данных:\n";
  print_vector(v);
  return static_cast<unsigned>(v.size());
}
 string name_from_number(int num){
  system("cls");
  std::vector<std::string> v;
  QDir dirDB;
  QString patch_to_DB = read_patch_DB();
  dirDB.setPath(patch_to_DB);
  QStringList listFiles = dirDB.entryList(QDir::Files);
  fill_vector(listFiles, v);
  return v.at(static_cast<ulong>(num-1));
 }
 QString read_patch_DB(){
  QSettings settings(settingsFile, QSettings::IniFormat);
  settings.beginGroup("person");
  QString patch_to_DB = settings.value("patch_to_DB").toString();
  settings.endGroup();
  return patch_to_DB;
 }
 void remove_data(){
  string num;
  unsigned i;
  unsigned number_person = read_data();
  while(1){
   if(number_person == 0){cout<<"Нет записей\n"; break;}
   cout<<"Введите номер записи для удаления:\n";
   cout<<"Для возврата введите 0 \n";
   cin>>num;
   regex regexpr ("[0-9]+");
   if (regex_match (num,regexpr)) {
    i = static_cast<unsigned>(stoi(num));
    if(i <= number_person) {
    break;
   }else cout << "Ошибка ввода!\n";
  } else  cout << "Ошибка ввода!\n";
 }
// i - номер записи для удаления
  if(i!=0){
  QString name_to_del = QString::fromStdString(name_from_number(static_cast<int>(i)));
  delete_file(name_to_del);
  cout<<"Запись удалена" <<"\n";
  }
 }

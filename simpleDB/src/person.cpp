#include "person.h"
#include "simpleDB.h"
using namespace std;
Person::Person() {
  live = true;
  age = 0;
  weight = 0;
  growth = 0;
};

Person::~Person(){};
void Person::print() {
  std::cout << "1\tИмя: " << name.toStdString() << "\n"
            << "2\tПол: " << sex.toStdString() << "\n"
            << "3\tВозраст: " << age << "\n"
            << "4\tРост: " << growth << "\n"
            << "5\tВес: " << weight << "\n"
            << "6\tНациональность: " << nation.toStdString() << "\n"
            << "7\tДата рождения: " << Person::bithday.toString().toStdString()
            << "\n"
            << "8\tДата смерти: " << Person::death.toString().toStdString()
            << "\n"
            << "\n";
}
void Person::read_person(string& name) {
  QString patch_to_DB = read_patch_DB();
  string path = patch_to_DB.toStdString() + "/" + name;
  fstream file;
  file.open(path, fstream::out | fstream::in | fstream::binary);
  if (!file.is_open())
    cout << "error opening file\n";
  else {
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
    file >> name;
    file >> sex;
    file >> age;
    file >> growth;
    file >> weight;
    file >> nation;
    file >> bithday;
    file >> death;
    file >> live;
    cout << "\nПрочитана запись: " << name << "\n";
    this->name = QString::fromStdString(name);
    this->sex = QString::fromStdString(sex);
    this->age = static_cast<unsigned>(stoi(age));
    this->growth = static_cast<unsigned>(stoi(growth));
    this->weight = static_cast<unsigned>(stoi(weight));
    this->nation = QString::fromStdString(nation);
    this->bithday = string_toqtate(bithday);
    this->live = stoi(live);
    if (this->live == 0) this->death = string_toqtate(death);
  }
  file.close();
}
void Person::save_person() {
  QString patch_to_DB = read_patch_DB();
  string path = patch_to_DB.toStdString() + "/" + this->name.toStdString();
  fstream file;
  file.open(path, fstream::out | fstream::binary);
  if (!file.is_open())
    cout << "error opening file\n";
  else {
    const QString DateFormat = "dd/MM/yyyy";
    file << this->name.toStdString() << "\n";
    file << this->sex.toStdString() << "\n";
    file << this->age << "\n";
    file << this->growth << "\n";
    file << this->weight << "\n";
    file << this->nation.toStdString() << "\n";
    file << this->bithday.toString(DateFormat).toStdString() << "\n";
    if (!this->live)
      file << this->death.toString(DateFormat).toStdString() << "\n";
    if (this->live)
      file << "no"
           << "\n";
    file << this->live << "\n";
    cout << "Данные сохранены в файле: " << this->name.toStdString() << "\n";
  }
  file.close();
}
void Person::input_name() {
  cout << "\nВведите имя латиницей:   "<<flush;
  cout<<endl;
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
  string iname;
//  while (1) {
    cin >> iname;
    cout<<iname<<endl;
//    regex regexpr("[A-Za-z]+");
//    if (regex_match(iname, regexpr)) {
//      this->name = QString::fromStdString(iname);
    this->name = QString::fromLocal8Bit(iname.c_str());
//      break;
//    } else
//      cout << "Ошибка ввода!\n";
//  }
  cout << "Имя: " << this->name.toStdString() << "\n";
      SetConsoleCP(866);
      SetConsoleOutputCP(CP_UTF8);
}

void Person::input_sex() {
  string isex;
  cout << "\nВведите пол:\n"
       << "1 - Мужской\n"
       << "2 - Женский\n";
  while (1) {
    cin >> isex;
    regex regexpr("[12]");
    if (regex_match(isex, regexpr)) {
      if (stoi(isex) == 1)
        this->sex = "Мужской";
      else
        this->sex = "Женский";
      break;
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "sex: " << this->sex.toStdString() << "\n";
}
QDate Person::input_bithday() {
  string ibighday;
  cout << "\nВведите дату рождения в формате DD/MM/YYYY:\n";

  const QString DateFormat = "dd/MM/yyyy";
  while (1) {
    cin >> ibighday;
    regex regexpr(
        "(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/"
        "](1[0-9][0-9]{2}|[2][0][0-9]{2})");
    if (regex_match(ibighday, regexpr)) {
      this->bithday = string_toqtate(ibighday);
      break;
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "Дата рождения: "
       << this->bithday.toString(DateFormat).toStdString() << "\n";
  return this->bithday;
}
QDate Person::input_death() {
  string ideath;
  cout << "\nВведите дату смерти в формате DD/MM/YYYY:\n";
  const QString DateFormat = "dd/MM/yyyy";
  QDate death, current;
  while (1) {
    cin >> ideath;
    regex regexpr(
        "(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/"
        "](1[0-9][0-9]{2}|[2][0][0-9]{2})");
    if (regex_match(ideath, regexpr)) {
      string day = ideath.substr(0, 2);
      string mounth = ideath.substr(3, 2);
      string year = ideath.substr(6, 4);
      death.setDate(stoi(year), stoi(mounth), stoi(day));
      current = QDate::currentDate();
      QDate bithday = this->bithday;
      int days_from_bithday = static_cast<int>(bithday.daysTo(death));
      int days_to_current = static_cast<int>(death.daysTo(current));
      if ((days_from_bithday > 0) && (days_to_current > 0)) {
        this->death = death;
        break;
      } else
        cout << "Ошибка ввода!\n";
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "Дата смерти: " << this->death.toString(DateFormat).toStdString()
       << "\n";
  return this->death;
}
void Person::input_growth(int max_growth) {
  string igrowth;
  cout << "\nВведите рост: \n";
  while (1) {
    cin >> igrowth;
    regex regexpr("[1-9]{1}[0-9]{0,2}");
    if (regex_match(igrowth, regexpr)) {
      if (stoi(igrowth) <= max_growth) {
        this->growth = static_cast<unsigned>(stoi(igrowth));
        break;
      } else
        cout << "Ошибка ввода!\n";
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "\nРост: " << this->growth << "\n\n";
}
void Person::input_weight(int max_weight) {
  string iweight;
  cout << "\nВведите вес: \n";
  while (1) {
    cin >> iweight;
    regex regexpr("[1-9]{1}[0-9]{0,2}");
    if (regex_match(iweight, regexpr)) {
      if (stoi(iweight) <= max_weight) {
        this->weight = static_cast<unsigned>(stoi(iweight));
        break;
      } else
        cout << "Ошибка ввода!\n";
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "\nВес: " << this->weight << "\n";
}
void Person::input_nation() {
  string inations;
  vector<pair<unsigned, string>> listnations;
  print_nation(listnations);
  cout << "\nВведите национальность. Выберите номер из списка:\n";
  while (1) {
    cin >> inations;
    regex regexpr("[1-9]{1}[0-9]{0,2}");
    if (regex_match(inations, regexpr)) {
      if (stold(inations) <= listnations.size()) {
        string nation = listnations.at(static_cast<ulong>(stoi(inations) - 1)).second;
        this->nation = QString::fromStdString(nation);
        break;
      } else
        cout << "Ошибка ввода!\n";
    } else
      cout << "Ошибка ввода!\n";
  }
  cout << "Национальность: " << this->nation.toStdString() << "\n";
}

Person::max Person::read_max() {
  Person::max max;
  QSettings settings(settingsFile, QSettings::IniFormat);
  settings.beginGroup("person");
  max.max_long_life = settings.value("max_long_life").toInt();
  max.max_growth = settings.value("max_growth").toInt();
  max.max_weight = settings.value("max_weight").toInt();
  settings.endGroup();
  return max;
}

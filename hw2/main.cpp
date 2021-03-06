#include <iostream>
#include "utils/UniversityUsers.h"
#include "utils/Rooms.h"

int main() {
    auto director = new Director("Kirill", "Semenikhin", "Microsoft");

    auto admin1 = new Admin("Andrew", "Korobov", "andrey228");
    auto admin2 = new Admin("Nikita", "Takov", "nick420069");

    auto prof1 = new Professor("Igor", "Gaponov", "Head, Lab of Intelligent Robotics Systems");
    auto prof2 = new Professor("Alexandr", "Klimchik", "Head, Center for Technologies in Robotics and Mechatronics Components");
    auto prof3 = new Professor("Eugene", "Zouev", "Head of the Lab of Operating Systems, programming languages and compilers");
    auto prof4 = new Professor("Rasheed", "Hussain", "Head, Lab of Networks and blockchain");

    auto worker1 = new LabEmployee("Pavel", "Kozlov", "industrial robotics");
    auto worker2 = new LabEmployee("Vladislav", "Ostankovich", "autonomous trasnporatation systems");
    auto worker3 = new LabEmployee("Oleg", "Bulichev", "mechatronics");
    auto worker4 = new LabEmployee("Mikhail", "Ivanou", "mechatronics");
    auto worker5 = new LabEmployee("Ramil", "Khusainov", "mechatronics");
    auto worker6 = new LabEmployee("Stanislav", "Protasov", "AI");
    auto worker7 = new LabEmployee("Shokhista", "Ergasheva", "software production");
    auto worker8 = new LabEmployee("Zamira", "Kholmatova", "software production");

    auto student1 = new Student("Lev", "Kozlov", "BS20-03");
    auto student2 = new Student("Egor", "Vlasov", "BS20-05");
    auto student3 = new Student("Dinar", "Shamsutdinov", "BS20-03");
    auto student4 = new Student("Alex", "Strijnev", "BS20-03");
    auto student5 = new Student("Vadim", "Makarov", "BS20-01");
    auto student6 = new Student("Daler", "Zakirov", "BS20-01");
    auto student7 = new Student("Anton", "Kirilin", "BS20-03");
    auto student8 = new Student("Danil", "Korokhov", "BS20-03");
    auto student9 = new Student("Camille", "Khubbetdinov", "BS20-03");
    auto student10 = new Student("Roman", "Voronov", "BS20-03");
    auto student11 = new Student("Artem", "Voronov", "BS20-03");
    auto student12 = new Student("Emil", "Latypov", "BS20-03");
    auto student13 = new Student("Fedor", "Krasilnikov", "BS20-03");
    auto student14 = new Student("Mikhail", "Panimash", "BS20-03");
    auto student15 = new Student("Sergey", "Pasynkov", "BS20-03");
    auto student16 = new Student("Makar", "Shevchenko", "BS20-03");

}
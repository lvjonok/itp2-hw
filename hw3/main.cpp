#include <iostream>
#include <vector>
#include <algorithm>
#include "utils/UniversityUsers.h"
#include "utils/Rooms.h"
#include "utils/Security.h"

template <class T>
/*
 * Function accepts a vector of pointers to generic type T
 * User has to input an index which he chooses from this vector
 */
int select_element(std::vector<T *> variants)
{
    int idx = 0;
    for (auto element : variants)
    {
        std::cout << "(" << idx++ << ") " << *element << std::endl;
    }
    int user_idx = -1;
    std::string user_input = "";
    std::cin >> user_input;
    while (user_idx < 0 || user_idx >= variants.size())
    {
        try
        {
            user_idx = stoi(user_input);
        }
        catch (...)
        {
            std::cout << "Cannot parse index from input" << std::endl;
            std::cin >> user_input;
            continue;
        }

        if ((user_idx < 0 || user_idx >= variants.size()))
        {
            std::cout << "You entered invalid index, pls, try again." << std::endl;
            std::cin >> user_input;
        }
    }

    return user_idx;
}

/*
 * Function allows to select the current user of this system
 */
User *select_user(const std::vector<User *> &users, const std::vector<User *> &admins)
{
    User *current_user = nullptr;

    // admins are in these indices
    auto admin1 = users[1];
    auto admin2 = users[2];

    bool appropriate_selection = false;
    do
    {
        int user_idx = select_element(users);
        current_user = users[user_idx];
        if (std::find(admins.begin(), admins.end(), current_user) != admins.end())
        {
            std::cout << "[INFO] You are trying to enter as admin. Enter the password:" << std::endl;
            std::string user_password;
            std::cin >> user_password;
            if (is_password(user_password))
            {
                std::cout << "[INFO] Password is correct. Enjoy!" << std::endl;
                appropriate_selection = true;
            }
            else
            {
                appropriate_selection = false;
                std::cout << "[INFO] Password is wrong. You return to user selection menu" << std::endl;
            }
        }
        else
        {
            appropriate_selection = true;
        }
    } while (!appropriate_selection);

    return current_user;
}

int main()
{
    auto director = new Director("Kirill", "Semenikhin", "Microsoft");

    auto admin1 = new Admin("Andrew", "Korobov", "andrey228");
    auto admin2 = new Admin("Nikita", "Takov", "nick420069");

    auto prof1 = new Professor("Igor", "Gaponov", "Head, Lab of Intelligent Robotics Systems");
    auto prof2 = new Professor("Alexandr", "Klimchik",
                               "Head, Center for Technologies in Robotics and Mechatronics Components");
    auto prof3 = new Professor("Eugene", "Zouev",
                               "Head of the Lab of Operating Systems, programming languages and compilers");
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

    auto guest1 = new Guest("Vladimir", "Putin", "Sbor stipy");
    auto guest2 = new Guest("Alexey", "Navalny", "Kuda delas' stipa");
    auto mama = new Guest("Marina", "Kozlova", "Posmotret' gde uchitsa son");
    auto premier_ministr = new Guest("Mike", "Mishustin", "Hochet vypendritsa");

    auto director_cabinet = new Cabinet("director_cabinet", director);
    auto prof1_cabinet = new Cabinet("Igor Gaponov cabinet", prof1);
    auto prof2_cabinet = new Cabinet("Alexandr Klimchik cabinet", prof2);
    auto prof3_cabinet = new Cabinet("Eugene Zouev cabinet", prof3);
    auto prof4_cabinet = new Cabinet("Rasheed Hussain cabinet", prof4);
    auto study_room = new ClassRoom("312");
    auto conference_hall = new ConferenceRoom("111");
    auto conference_hall1 = new ConferenceRoom("211");
    auto conference_hall2 = new ConferenceRoom("341");
    auto lecture_room = new LectureRoom("108");
    auto robotics_garage = new LabCabinet("Robotics Garage", {worker1, worker2, worker3, worker4, worker5});
    auto software_lab = new LabCabinet("AI and Software Production lab", {worker6, worker7, worker8});

    std::vector<User *> admins{
        admin1,
        admin2};

    // vector contains all people present in this solution
    std::vector<User *> university_people;
    {
        university_people.push_back(director);
        university_people.push_back(admin1);
        university_people.push_back(admin2);
        university_people.push_back(prof1);
        university_people.push_back(prof2);
        university_people.push_back(prof3);
        university_people.push_back(prof4);
        university_people.push_back(worker1);
        university_people.push_back(worker2);
        university_people.push_back(worker3);
        university_people.push_back(worker4);
        university_people.push_back(worker5);
        university_people.push_back(worker6);
        university_people.push_back(worker7);
        university_people.push_back(worker8);
        university_people.push_back(student1);
        university_people.push_back(student2);
        university_people.push_back(student3);
        university_people.push_back(student4);
        university_people.push_back(student5);
        university_people.push_back(student6);
        university_people.push_back(student7);
        university_people.push_back(student8);
        university_people.push_back(student9);
        university_people.push_back(student10);
        university_people.push_back(student11);
        university_people.push_back(student12);
        university_people.push_back(student13);
        university_people.push_back(student14);
        university_people.push_back(student15);
        university_people.push_back(student16);
        university_people.push_back(guest1);
        university_people.push_back(guest2);
        university_people.push_back(mama);
        university_people.push_back(premier_ministr);
    }
    // vector contains all rooms implemented in this solution
    std::vector<Room *> university_building;
    {
        university_building.push_back(director_cabinet);
        university_building.push_back(study_room);
        university_building.push_back(conference_hall);
        university_building.push_back(conference_hall1);
        university_building.push_back(conference_hall2);
        university_building.push_back(lecture_room);
        university_building.push_back(robotics_garage);
        university_building.push_back(software_lab);
        university_building.push_back(prof1_cabinet);
        university_building.push_back(prof2_cabinet);
        university_building.push_back(prof3_cabinet);
        university_building.push_back(prof4_cabinet);
    }

    std::cout << "To start with, select yourself. Input idx from parenthesis to select needed user:\n";

    auto current_user = select_user(university_people, admins);
    std::cout << "[INFO] You are " << current_user->get_name_surname() << std::endl;

    int action = -1;
    while (action != 0)
    {
        action = select_element(current_user->get_actions());
        std::cout << "[INFO] User selected ==> " << *current_user->get_actions()[action] << std::endl;
        switch (action)
        {
        // Case 1: change of user
        case 1:
        {
            current_user = select_user(university_people, admins);
            std::cout << "[INFO] You changed user. Now you are " << current_user->get_name_surname() << std::endl;
        }
        break;
        // Case 2: Access to room
        case 2:
        {
            auto selected_room = university_building[select_element(university_building)];
            auto result = selected_room->access(current_user);
            if (result)
                std::cout << "[INFO] You have access to this room. Enter!)" << std::endl;
            else
                std::cout << "[INFO] Access denied. You have no rights to enter. Stay away!" << std::endl;
        }
        break;
        // Case 3: Get name and surname of user
        case 3:
        {
            auto result = current_user->get_name_surname();
            std::cout << "[INFO] You are " << result << std::endl;
        }
        break;
        // Case 4: Get property of user
        case 4:
        {
            auto result = current_user->get_property();
            std::cout << "[INFO] Your property is " << result << std::endl;
        }
        break;
        // Case 5: Get level of access of user
        case 5:
        {
            auto result = current_user->get_level();
            std::cout << "[INFO] Your level is " << result << std::endl;
        }
        break;
        // Case 6: EMERGENCY (available only for admins) opens all rooms in the building
        case 6:
        {
            std::cout
                << "You toggled emergency button. "
                   "All rooms will change their emergency access level. "
                   "To switch off emergency, ask admin (login as admin) to disable emergency situation if all is ok."
                << std::endl;

            for (auto room: university_building) {
                room->toggle_emergency();
            }
        }
        break;
        // Case 7: Grant Access (available only for admins)
        case 7:
        {
            std::cout
                << "[INFO] To grant access to someone, on first selection choose person, then choose room. "
                   "After this an access will be granted."
                << std::endl;
            auto selected_user = university_people[select_element(university_people)];
            auto selected_room = university_building[select_element(university_building)];

            std::cout << "[INFO] You grant " << *selected_user << " an access to " << *selected_room << std::endl;

            // we cast current user because this action is available only for admin
            ((Admin *)current_user)->grant_access(selected_user, selected_room);
        }
        break;
        case 8:
        {
            std::cout
                << "You disabled emergency as admin. "
                   "All rooms now have default level of access. "
                << std::endl;

            ((Admin *)current_user)->disable_emergency(university_building);
        }
        default:
            break;
        }
    }
}
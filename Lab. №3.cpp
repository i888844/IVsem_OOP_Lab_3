#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <iomanip>
#include <map>
#include <windows.h>

using namespace std;

const string numbers[12] = { "01", "02", "03",
                             "04", "05", "06",
                             "07", "08", "09",
                             "10", "11", "12" };
const string months[12] = { "Январь", "Февраль", "Март",
                            "Апрель", "Май","Июнь",
                            "Июль", "Август", "Сентябрь",
                            "Октябрь", "Ноябрь","Декабрь" };

string parse_number_to_month(const string& number)
{
    for (unsigned long int i = 0; i < 12; i++)
    {
        if (numbers[i] == number) return months[i];
    }
}

string parse_month_to_number(const string& month)
{
    for (unsigned long int i = 0; i < 12; i++)
    {
        if (months[i] == month) return numbers[i];
    }
}

string parse_other_period(const string& _number, const string& employee_period)
{
    unsigned long int number = stoi(_number) - 1;
    string month = employee_period.substr(0, employee_period.find(" "));
    unsigned long int year = stoi(employee_period.substr(employee_period.find(" ") + 1, 4));
    unsigned long int month_number = distance(months, find(months, months + 12, month));

    if ((number < 6 && month_number >= 6) || (number >= 6 && month_number < 6))
    {
        if (number < month_number)
        {
            year++;
        }
        else {
            year--;
        }
    }

    return parse_number_to_month(numbers[number]) + " " + std::to_string(year) + " г.";
}

class Retention
{
private:
    string period;
    string type;
    double sum;
public:
    Retention()
    {
        period = "N/A";
        type = "N/A";
        sum = 0.0;
    }

    Retention(const string _period, const string _type, const double _sum)
    {
        if (_period.length() > 0)
        {
            period = _period;
        }
        else
        {
            period = "N/A";
        }

        if (_type.length() == 3)
        {
            type = _type;
        }
        else
        {
            type = "N/A";
        }

        if (_sum >= 0.0)
        {
            sum = _sum;
        }
        else
        {
            sum = 0.0;
        }
    }

    Retention(const Retention& src_object)
    {
        period = src_object.period;
        type = src_object.type;
        sum = src_object.sum;
    }

    ~Retention() { }

    string get_period() const { return period; }
    string get_type() const { return type; }
    double get_sum() const { return sum; }

    bool set_period(const string settable_period)
    {
        bool result = false;

        if (settable_period.length() > 0)
        {
            period = settable_period;
            result = true;
        }

        return result;
    }

    bool set_type(const string settable_type)
    {
        bool result = false;

        if (settable_type.length() == 3)
        {
            type = settable_type;
            result = true;
        }

        return result;
    }

    bool set_sum(const double settable_sum)
    {
        bool result = false;

        if (settable_sum > 0.0)
        {
            sum = settable_sum;
            result = true;
        }

        return result;
    }

    void output() const
    {
        cout << period << "  " << type << "  " << sum << endl;
    }
};

class Accural : public Retention
{
private:
    unsigned long int attendance;
    unsigned long int hours;
public:
    Accural() : Retention()
    {
        attendance = 0;
        hours = 0;
    }

    Accural(const string _period, const  string _type, const  double _sum, const  unsigned long int _attendance, const  unsigned long int _hours) : Retention(_period, _type, _sum)
    {
        if (_attendance > 0) attendance = _attendance;
        if (_hours > 0) hours = _hours;
    }

    Accural(const Accural& src_object) : Retention(src_object)
    {
        attendance = src_object.attendance;
        hours = src_object.hours;
    }

    ~Accural() { }

    unsigned long int get_attendance() const { return attendance; }
    unsigned long int get_hours() const { return hours; }

    bool set_attendance(const unsigned long int settable_attendance)
    {
        bool result = false;

        if (settable_attendance > 0)
        {
            attendance = settable_attendance;
            result = true;
        }

        return result;
    }

    bool set_hours(const unsigned long int settable_hours)
    {
        bool result = false;

        if (settable_hours > 0)
        {
            hours = settable_hours;
            result = true;
        }

        return result;
    }

    void output() const
    {
        cout << get_period() << "  " << get_type() << "  " << get_sum() << "  " << attendance << "  " << hours << endl;
    }
};

class Employee
{
private:
    string service_number;
    string full_name;
    string id_code;
    string section_code;
    string profession_code;
    string period;
    double salary;
    unsigned long int attendance_in_schedule;
    unsigned long int accurals_amount;
    Accural** accurals;
    unsigned long int retentions_amount;
    Retention** retentions;
public:
    Employee()
    {
        service_number = "N/A";
        full_name = "N/A";
        id_code = "N/A";
        section_code = "N/A";
        profession_code = "N/A";
        period = "N/A";
        salary = 0.0;
        accurals_amount = 0;
        accurals = nullptr;
        retentions_amount = 0;
        retentions = nullptr;
    }

    Employee(const string _service_number, const string _full_name, const string _id_code, const string _section_code, const string _profession_code, const string _period, const double _salary, const unsigned long int _attendance_in_schedule, const unsigned long int _accurals_amount, const unsigned long int _retentions_amount)
    {
        if (_service_number.length() > 0)
        {
            service_number = _service_number;
        }
        else
        {
            service_number = "N/A";
        }

        if (_full_name.length() > 0)
        {
            full_name = _full_name;
        }
        else
        {
            full_name = "N/A";
        }

        if (_id_code.length() > 0)
        {
            id_code = _id_code;
        }
        else
        {
            id_code = "N/A";
        }

        if (_section_code.length() > 0)
        {
            section_code = _section_code;
        }
        else
        {
            section_code = "N/A";
        }

        if (_profession_code.length() > 0)
        {
            profession_code = _profession_code;
        }
        else
        {
            profession_code = "N/A";
        }

        if (_period.length() > 0)
        {
            period = _period;
        }
        else
        {
            period = "N/A";
        }

        if (_salary != 0.0)
        {
            salary = _salary;
        }
        else
        {
            salary = 0.0;
        }

        if (_attendance_in_schedule >= 0)
        {
            attendance_in_schedule = _attendance_in_schedule;
        }
        else
        {
            attendance_in_schedule = 0;
        }

        if (_accurals_amount > 0)
        {
            accurals_amount = _accurals_amount;
            accurals = new Accural * [accurals_amount];
            for (int i = 0; i < accurals_amount; i++)
            {
                accurals[i] = new Accural();
            }
        }
        else
        {
            accurals_amount = 0;
            accurals = nullptr;
        }

        if (_retentions_amount > 0)
        {
            retentions_amount = _retentions_amount;
            retentions = new Retention * [retentions_amount];
            for (int i = 0; i < retentions_amount; i++)
            {
                retentions[i] = new Retention();
            }
        }
        else
        {
            retentions_amount = 0;
            retentions = nullptr;
        }
    }

    Employee(const Employee& src_object)
    {
        service_number = src_object.service_number;
        full_name = src_object.full_name;
        id_code = src_object.id_code;
        section_code = src_object.section_code;
        profession_code = src_object.profession_code;
        period = src_object.period;
        salary = src_object.salary;
        accurals_amount = src_object.accurals_amount;
        if (accurals_amount > 0)
        {
            accurals = new Accural * [accurals_amount];
            for (int i = 0; i < accurals_amount; i++)
            {
                accurals[i] = new Accural(*(src_object.accurals[i]));
            }
        }
        else
        {
            accurals = nullptr;
        }
        retentions_amount = src_object.retentions_amount;
        if (retentions_amount > 0)
        {
            retentions = new Retention * [retentions_amount];
            for (int i = 0; i < retentions_amount; i++)
            {
                retentions[i] = new Retention(*(src_object.retentions[i]));
            }
        }
        else
        {
            retentions = nullptr;
        }
    }

    ~Employee()
    {
        if (accurals_amount > 0 && accurals != nullptr)
        {
            for (int i = 0; i < accurals_amount; i++)
            {
                delete accurals[i];
            }
            delete[]accurals;
        }
        if (retentions_amount > 0 && retentions != nullptr)
        {
            for (int i = 0; i < retentions_amount; i++)
            {
                delete retentions[i];
            }
            delete[]retentions;
        }
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Employee  # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_service_number() const { return service_number; }
    string get_full_name() const { return full_name; }
    string get_id_code() const { return id_code; }
    string get_profession_code() const { return profession_code; }
    string get_period() const { return period; }
    double get_salary() const { return salary; }
    unsigned long int get_attendance_in_schedule() const { return attendance_in_schedule; }
    unsigned long int get_accurals_amount() const { return accurals_amount; }
    unsigned long int get_retentions_amount() const { return retentions_amount; }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Employee  # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_service_number(const string settable_service_number)
    {
        bool result = false;

        if (settable_service_number.length() > 0)
        {
            service_number = settable_service_number;
            result = true;
        }

        return result;
    }

    bool set_full_name(const string settable_full_name)
    {
        bool result = false;

        if (settable_full_name.length() > 0)
        {
            full_name = settable_full_name;
            result = true;
        }

        return result;
    }

    bool set_id_code(const string settable_id_code)
    {
        bool result = false;

        if (settable_id_code.length() > 0)
        {
            id_code = settable_id_code;
            result = true;
        }

        return result;
    }

    bool set_section_code(const string settable_section_code)
    {
        bool result = false;

        if (settable_section_code.length() > 0)
        {
            section_code = settable_section_code;
            result = true;
        }

        return result;
    }

    bool set_professional_code(const string settable_professional_code)
    {
        bool result = false;

        if (settable_professional_code.length() > 0)
        {
            profession_code = settable_professional_code;
            result = true;
        }

        return result;
    }

    bool set_period(const string settable_period)
    {
        bool result = false;

        if (settable_period.length() > 0)
        {
            period = settable_period;
            result = true;
        }

        return result;
    }

    bool set_salary(const double settable_salary)
    {
        bool result = false;

        if (settable_salary != 0.0)
        {
            salary = settable_salary;
            result = true;
        }

        return result;
    }

    bool set_attendance_in_schedule(const unsigned long int settable_attendance_in_schedule)
    {
        bool result = false;

        if (settable_attendance_in_schedule >= 0)
        {
            attendance_in_schedule = settable_attendance_in_schedule;
            result = true;
        }

        return result;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Employee -> Retention # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_retention_period(const unsigned long int index_retention)
    {
        return retentions[index_retention]->get_period();
    }

    string get_retention_type(const unsigned long int index_retention)
    {
        return retentions[index_retention]->get_type();
    }

    double get_retention_sum(const unsigned long int index_retention)
    {
        return retentions[index_retention]->get_sum();
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Employee -> Retention # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_retentions_period(const unsigned long int index_retentions_period, const string settable_retentions_period)
    {
        const bool result = retentions[index_retentions_period]->set_period(settable_retentions_period);
        return result;
    }

    bool set_retentions_type(const unsigned long int index_retentions_type, const string settable_retentions_type)
    {
        const bool result = retentions[index_retentions_type]->set_type(settable_retentions_type);
        return result;
    }

    bool set_retentions_sum(const unsigned long int index_retentions_sum, const double settable_retentions_sum)
    {
        const bool result = retentions[index_retentions_sum]->set_sum(settable_retentions_sum);
        return result;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Employee -> Accurals  # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_accural_period(const unsigned long int index_accural)
    {
        return accurals[index_accural]->get_period();
    }

    string get_accural_type(const unsigned long int index_accural)
    {
        return accurals[index_accural]->get_type();
    }

    double get_accural_sum(const unsigned long int index_accural)
    {
        return accurals[index_accural]->get_sum();
    }

    unsigned long int get_accural_attendance(const unsigned long int index_accural)
    {
        return accurals[index_accural]->get_attendance();
    }

    unsigned long int get_accural_hours(const unsigned long int index_accural)
    {
        return accurals[index_accural]->get_hours();
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Employee -> Accurals  # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_accurals_period(const unsigned long int index_accurals_period, const string settable_accurals_period)
    {
        const bool result = accurals[index_accurals_period]->set_period(settable_accurals_period);
        return result;
    }

    bool set_accurals_type(const unsigned long int index_accurals_type, const string settable_accurals_type)
    {
        const bool result = accurals[index_accurals_type]->set_type(settable_accurals_type);
        return result;
    }

    bool set_accurals_sum(const unsigned long int index_accurals_sum, const double settable_accurals_sum)
    {
        const bool result = accurals[index_accurals_sum]->set_sum(settable_accurals_sum);
        return result;
    }

    bool set_accurals_attendance(const unsigned long int index_accurals_attendance, const unsigned long int settable_accurals_attendance)
    {
        const bool result = accurals[index_accurals_attendance]->set_attendance(settable_accurals_attendance);
        return result;
    }

    bool set_accurals_hours(const unsigned long int index_accurals_hours, const unsigned long int settable_accurals_hours)
    {
        const bool result = accurals[index_accurals_hours]->set_hours(settable_accurals_hours);
        return result;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    void output() const
    {
        cout << service_number << "  " << full_name << "  " << id_code << " ГП" << "\n";
        cout << "Участок: " << section_code << "  Проф.: " << profession_code << "\n";

        if (salary <= 100)
        {
            cout << period << " Тар.ст.: " << salary << " Яв " << attendance_in_schedule << "\n";
        }
        else
        {
            cout << period << " Оклад: " << salary << " Яв " << attendance_in_schedule << "\n";
        }

        cout << "Начисления:\n";
        cout << "Мц В/О Начислено Яв Час\n";
        unsigned long int i = 0;
        for (i = 0; i < accurals_amount; i++)
        {
            accurals[i]->output();
        }
        cout << "Удержания:\n";
        cout << "Мц В/У Удержано\n";
        for (i = 0; i < retentions_amount; i++)
        {
            if (retentions[i]->get_type() == "П/н") continue;
            retentions[i]->output();
        }
        cout << "\n\n" << endl;
    }
};

class Section
{
private:
    string section_code;
    string section_name;
    unsigned long int employees_amount;
    Employee** employees;
public:
    Section()
    {
        section_code = "N/A";
        section_name = "N/A";
        employees_amount = 0;
        employees = nullptr;
    }

    Section(const string _section_code, const string _section_name, const unsigned long int _employees_amount)
    {
        if (_section_code.length() > 0) section_code = _section_code;
        if (_section_name.length() > 0) section_name = _section_name;
        if (_employees_amount > 0)
        {
            employees_amount = _employees_amount;
            employees = new Employee * [employees_amount];
            for (int i = 0; i < employees_amount; i++)
            {
                employees[i] = new Employee();
            }
        }
        else
        {
            employees_amount = 0;
            employees = nullptr;
        }
    }

    Section(const Section& src_object)
    {
        section_code = src_object.section_code;
        section_name = src_object.section_name;
        employees_amount = src_object.employees_amount;
        if (employees_amount > 0)
        {
            employees = new Employee * [employees_amount];
            for (int i = 0; i < employees_amount; i++)
            {
                employees[i] = new Employee(*(src_object.employees[i]));
            }
        }
        else
        {
            employees = nullptr;
        }
    }

    ~Section()
    {
        if (employees_amount > 0 && employees != nullptr)
        {
            for (int i = 0; i < employees_amount; i++)
            {
                delete employees[i];
            }
            delete[]employees;
        }
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Section # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_section_code() const { return section_code; }
    string get_section_name() const { return section_name; }
    unsigned long int get_employees_amount() const { return employees_amount; }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Section # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_section_code(const string settable_section_code)
    {
        bool result = false;

        if (settable_section_code.length() > 0)
        {
            section_code = settable_section_code;
            result = true;
        }

        return result;
    }

    bool set_section_name(const string settable_section_name)
    {
        bool result = false;

        if (settable_section_name.length() > 0)
        {
            section_name = settable_section_name;
            result = true;
        }

        return result;
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Section -> Employee # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_employee_service_number(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_service_number();
    }

    string get_employee_full_name(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_full_name();
    }

    string get_employee_id_code(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_id_code();
    }

    string get_employee_profession_code(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_profession_code();
    }

    string get_employee_period(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_period();
    }

    double get_employee_salary(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_salary();
    }

    unsigned long int get_employee_attendance_in_schedule(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_attendance_in_schedule();
    }

    unsigned long int get_employee_accurals_amount(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_accurals_amount();
    }

    unsigned long int get_employee_retentions_amount(const unsigned long int index_employee)
    {
        return employees[index_employee]->get_retentions_amount();
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Section -> Employee # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_employee_service_number(const unsigned long int index_employee, const string settable_service_number)
    {
        return employees[index_employee]->set_service_number(settable_service_number);
    }

    bool set_employee_full_name(const unsigned long int index_employee, const string settable_full_name)
    {
        return employees[index_employee]->set_full_name(settable_full_name);
    }

    bool set_employee_id_code(const unsigned long int index_employee, const string settable_id_code)
    {
        return employees[index_employee]->set_id_code(settable_id_code);
    }

    bool set_employee_section_code(const unsigned long int index_employee, const string settable_section_code)
    {
        return employees[index_employee]->set_section_code(settable_section_code);
    }

    bool set_employee_professional_code(const unsigned long int index_employee, const string settable_professional_code)
    {
        return employees[index_employee]->set_professional_code(settable_professional_code);
    }

    bool set_employee_period(const unsigned long int index_employee, const string settable_period)
    {
        return employees[index_employee]->set_period(settable_period);
    }

    bool set_employee_salary(const unsigned long int index_employee, const double settable_salary)
    {
        return employees[index_employee]->set_salary(settable_salary);
    }

    bool set_employee_attendance_in_schedule(const unsigned long int index_employee, const unsigned long int settable_attendance_in_schedule)
    {
        return employees[index_employee]->set_attendance_in_schedule(settable_attendance_in_schedule);
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Section -> Employee -> Retention  # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_employee_retention_period(const unsigned long int index_employee, const unsigned long int index_retention)
    {
        return employees[index_employee]->get_retention_period(index_retention);
    }

    string get_employee_retention_type(const unsigned long int index_employee, const unsigned long int index_retention)
    {
        return employees[index_employee]->get_retention_type(index_retention);
    }

    double get_employee_retention_sum(const unsigned long int index_employee, const unsigned long int index_retention)
    {
        return employees[index_employee]->get_retention_sum(index_retention);
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Section -> Employee -> Retention  # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_employee_retentions_period(const unsigned long int index_employee, const unsigned long int index_retentions_period, const string settable_retentions_period)
    {
        return employees[index_employee]->set_retentions_period(index_retentions_period, settable_retentions_period);
    }

    bool set_employee_retentions_type(const unsigned long int index_employee, const unsigned long int index_retentions_type, const string settable_retentions_type)
    {
        return employees[index_employee]->set_retentions_type(index_retentions_type, settable_retentions_type);
    }

    bool set_employee_retentions_sum(const unsigned long int index_employee, const unsigned long int index_retentions_sum, const double settable_retentions_sum)
    {
        return employees[index_employee]->set_retentions_sum(index_retentions_sum, settable_retentions_sum);
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # get'ы атрибутов Section -> Employee -> Accural  # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    string get_employee_accural_period(const unsigned long int index_employee, const unsigned long int index_accural)
    {
        return employees[index_employee]->get_accural_period(index_accural);
    }

    string get_employee_accural_type(const unsigned long int index_employee, const unsigned long int index_accural)
    {
        return employees[index_employee]->get_accural_type(index_accural);
    }

    double get_employee_accural_sum(const unsigned long int index_employee, const unsigned long int index_accural)
    {
        return employees[index_employee]->get_accural_sum(index_accural);
    }

    unsigned long int get_employee_accural_attendance(const unsigned long int index_employee, const unsigned long int index_accural)
    {
        return employees[index_employee]->get_accural_attendance(index_accural);
    }

    unsigned long int get_employee_accural_hours(const unsigned long int index_employee, const unsigned long int index_accural)
    {
        return employees[index_employee]->get_accural_hours(index_accural);
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # set'ы атрибутов Section -> Employee -> Accural  # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    bool set_employee_accurals_period(const unsigned long int index_employee, const unsigned long int index_accurals_period, const string settable_accurals_period)
    {
        return employees[index_employee]->set_accurals_period(index_accurals_period, settable_accurals_period);
    }

    bool set_employee_accurals_type(const unsigned long int index_employee, const unsigned long int index_accurals_type, const string settable_accurals_type)
    {
        return employees[index_employee]->set_accurals_type(index_accurals_type, settable_accurals_type);
    }

    bool set_employee_accurals_sum(const unsigned long int index_employee, const unsigned long int index_accurals_sum, const double settable_accurals_sum)
    {
        return employees[index_employee]->set_accurals_sum(index_accurals_sum, settable_accurals_sum);
    }

    bool set_employee_accurals_attendance(const unsigned long int index_employee, const unsigned long int index_accurals_attendance, const unsigned long int settable_accurals_attendance)
    {
        return employees[index_employee]->set_accurals_attendance(index_accurals_attendance, settable_accurals_attendance);
    }

    bool set_employee_accurals_hours(const unsigned long int index_employee, const unsigned long int index_accurals_hours, const unsigned long int settable_accurals_hours)
    {
        return employees[index_employee]->set_accurals_hours(index_accurals_hours, settable_accurals_hours);
    }

    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
    // # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

    unsigned long int add_employee(const string _service_number, const  string _full_name, const  string _id_code, const  string _section_code, const  string _profession_code, const  string _period, const  double _salary, const  unsigned long int _attendance_in_schedule, const  unsigned long int _accurals_amount, const  unsigned long int _retentions_amount)
    {
        try
        {
            Employee** new_employees = new Employee * [employees_amount + 1];

            for (unsigned long int i = 0; i < employees_amount; i++)
            {
                new_employees[i] = employees[i];
            }

            new_employees[employees_amount] = new Employee(_service_number, _full_name, _id_code, _section_code, _profession_code, _period, _salary, _attendance_in_schedule, _accurals_amount, _retentions_amount);

            if (employees_amount > 0)
            {
                delete[] employees;
            }

            employees = new_employees;
            employees_amount++;
            return employees_amount - 1;
        }
        catch (const exception& e)
        {
            cerr << "Произошла ошибка при добавлении нового сотрудника: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Произошла неизвестная ошибка при добавлении нового сотрудника." << endl;
        }
    }
    
    void output() const
    {
        cout << "Участок: " << section_code << " " << section_name << "\n\n";
        for (int i = 0; i < employees_amount; i++)
        {
            employees[i]->output();
        }
        cout << "\n\n" << endl;
    }
};

class List
{
private:
    string list_name;
    unsigned long int max_sections_amount;
    unsigned long int sections_amount;
    Section** sections;
public:
    List()
    {
        list_name = "N/A";
        max_sections_amount = 0;
        sections_amount = 0;
        sections = nullptr;
    }

    List(const string _list_name, const unsigned int _max_sections_amount, const unsigned long int _sections_amount)
    {
        if (_list_name.length() > 0) list_name = _list_name;
        if (_max_sections_amount > 0) max_sections_amount = _max_sections_amount;
        if (_sections_amount > 0 && _sections_amount <= max_sections_amount)
        {
            sections_amount = _sections_amount;
            sections = new Section * [sections_amount];
            for (int i = 0; i < sections_amount; i++)
            {
                sections[i] = new Section();
            }
        }
        else
        {
            sections_amount = 0;
            sections = nullptr;
        }
    }

    List(const string file_path)
    {
        ifstream file(file_path);
        list_name = file_path;
        max_sections_amount = 32;
        sections_amount = 0;

        unsigned long int lines_amount = 0;
        string line = "";

        while (getline(file, line))
        {
            lines_amount++;
        }

        file.clear();
        file.seekg(0, ios::beg);

        string* lines = new string[lines_amount];
        unsigned long int i = 0;

        while (getline(file, line))
        {
            lines[i] = line;
            i++;
        }

        unsigned long int index_employee = 0;
        sections = new Section * [max_sections_amount];

        int position = 0;

        for (unsigned long int l = 0; l < lines_amount; l++)
        {
            position = lines[l].find("Участок : ");
            if (position > 0 && sections_amount < max_sections_amount)
            {
                sections[sections_amount] = new Section();
                sections[sections_amount]->set_section_code(lines[l].substr(position + 10, 3));
                sections[sections_amount]->set_section_name(lines[l].substr(position + 14, 3));
                const string section_name = "Участок " + sections[sections_amount]->get_section_code();

                for (unsigned long int j = l + 1; j < lines_amount; j++)
                {
                    position = lines[j].find(section_name);
                    if (position != string::npos && lines[j].find("Проф.") && (lines[j + 1].find("Оклад") || lines[j + 1].find("Тар.ст.:")) && lines[j + 1].find("Яв"))
                    {
                        string employee_service_number = lines[j - 1].substr(0, 6);
                        string employee_full_name = lines[j - 1].substr(7, 19);
                        string employee_id_code = lines[j - 1].substr(26, 10);
                        string employee_section_code = lines[j].substr(8, 3);
                        string employee_profession_code = lines[j].substr(18, 3);
                        position = lines[j + 1].find("г.");
                        string employee_period = lines[j + 1].substr(0, position + 2);
                        string employee_salary = lines[j + 1].substr(position + 11, 9);
                        position = lines[j + 1].find("Яв");
                        string employee_attendance_in_schedule = lines[j + 1].substr(position + 3, 2);

                        unsigned long int employee_accurals_amount = 0;
                        unsigned long int employee_retentions_amount = 0;

                        for (unsigned long int k = j + 3; k < lines_amount; k++)
                        {
                            if (lines[k].find("ИТОГО:") != string::npos) break;
                            if (lines[k].substr(0, 6) != "      ") employee_accurals_amount++;
                        	if (lines[k].substr(24, 6) != "      ") employee_retentions_amount++;
                        }

                        sections[sections_amount]->add_employee(employee_service_number,
                            employee_full_name,
                            employee_id_code,
                            employee_section_code,
                            employee_profession_code,
                            employee_period,
                            atof(employee_salary.c_str()),
                            atof(employee_attendance_in_schedule.c_str()),
                            employee_accurals_amount,
                            employee_retentions_amount);

                        unsigned long int accurals_index = 0;
                        unsigned long int retentions_index = 0;

                        string employee_accurals_period = "";
                        string employee_accurals_type = "";
                        string employee_accurals_sum = "";
                        string employee_accurals_attendance = "";
                        string employee_accurals_hours = "";

                        for (unsigned long int k = j + 3; k < employee_accurals_amount + j + 3; k++)
                        {
                            if (lines[k].substr(0, 2) == "  ")
                            {
                                employee_accurals_period = employee_period;
                            }
                            else
                            {
                                employee_accurals_period = parse_other_period(lines[k].substr(0, 2), employee_period);
                            }
                            employee_accurals_type = lines[k].substr(3, 3);
                            employee_accurals_sum = lines[k].substr(7, 10);
                            employee_accurals_attendance = lines[k].substr(17, 2);
                            employee_accurals_hours = lines[k].substr(20, 3);

                            sections[sections_amount]->set_employee_accurals_period(index_employee,
                                accurals_index,
                                employee_accurals_period);
                            sections[sections_amount]->set_employee_accurals_type(index_employee,
                                accurals_index,
                                employee_accurals_type);
                            sections[sections_amount]->set_employee_accurals_sum(index_employee,
                                accurals_index,
                                atof(employee_accurals_sum.c_str()));
                            sections[sections_amount]->set_employee_accurals_attendance(index_employee,
                                accurals_index,
                                atof(employee_accurals_attendance.c_str()));
                            sections[sections_amount]->set_employee_accurals_hours(index_employee,
                                accurals_index,
                                atof(employee_accurals_hours.c_str()));

                            accurals_index++;
                        }

                        string employee_retentions_period = "";
                        string employee_retentions_type = "";
                        string employee_retentions_sum = "";

                        for (unsigned long int k = j + 3; k < employee_retentions_amount + j + 3; k++)
                        {
                            if (lines[k].substr(24, 2) == "  ")
                            {
                                employee_retentions_period = employee_period;
                            }
                            else
                            {
                                employee_retentions_period = parse_other_period(lines[k].substr(24, 2), employee_period);
                            }
                            employee_retentions_type = lines[k].substr(27, 3);
                            employee_retentions_sum = lines[k].substr(32, 8);

                            sections[sections_amount]->set_employee_retentions_period(index_employee,
                                retentions_index,
                                employee_retentions_period);
                            sections[sections_amount]->set_employee_retentions_type(index_employee,
                                retentions_index,
                                employee_retentions_type);
                            sections[sections_amount]->set_employee_retentions_sum(index_employee,
                                retentions_index,
                                atof(employee_retentions_sum.c_str()));

                            retentions_index++;
                        }
                        index_employee++;
                    }
                }
                sections_amount++;
            }
        }
        delete[]lines;
    }

    List(const List& src_object)
    {
        list_name = src_object.list_name;
        max_sections_amount = src_object.max_sections_amount;
        sections_amount = src_object.sections_amount;
        if (sections_amount > 0 && sections_amount <= max_sections_amount)
        {
            sections = new Section * [sections_amount];
            for (int i = 0; i < sections_amount; i++)
            {
                sections[i] = new Section(*(src_object.sections[i]));
            }
        }
        else
        {
            sections = nullptr;
        }
    }

    ~List()
    {
        if (sections_amount > 0 && sections != nullptr)
        {
            for (int i = 0; i < sections_amount; i++)
            {
                delete sections[i];
            }
            delete[]sections;
        }
    }

    List& operator=(const List& src_object)
    {
        if (this != &src_object)
        {
            list_name = src_object.list_name;
            max_sections_amount = src_object.max_sections_amount;
            sections_amount = src_object.sections_amount;

            unsigned long int i = 0;

            for (i = 0; i < sections_amount; i++)
            {
                delete sections[i];
            }
            delete[] sections;

            if (sections_amount > 0 && sections_amount <= max_sections_amount)
            {
                sections = new Section * [sections_amount];
                for (i = 0; i < sections_amount; i++)
                {
                    sections[i] = new Section(*(src_object.sections[i]));
                }
            }
            else
            {
                sections = nullptr;
            }
        }
        return *this;
    }

    List operator+(const List& src_other)
    {
        List result = *this;

        unsigned long int i = 0;
        unsigned long int j = 0;
        unsigned long int k = 0;
        unsigned long int l = 0;

        for (i = 0; i < src_other.sections_amount; i++)
        {
            bool found = false;
            for (j = 0; j < result.sections_amount; j++)
            {
                if (result.sections[i]->get_section_code() == src_other.sections[j]->get_section_code() &&
                    result.sections[i]->get_section_name() == src_other.sections[j]->get_section_name())
                {
                    for (k = 0; k < src_other.sections[i]->get_employees_amount(); k++)
                    {
                        const unsigned long int index = result.sections[j]->add_employee(
                            src_other.sections[i]->get_employee_service_number(k),
                            src_other.sections[i]->get_employee_full_name(k),
                            src_other.sections[i]->get_employee_id_code(k),
                            src_other.sections[i]->get_section_code(),
                            src_other.sections[i]->get_employee_profession_code(k),
                            src_other.sections[i]->get_employee_period(k),
                            src_other.sections[i]->get_employee_salary(k),
                            src_other.sections[i]->get_employee_attendance_in_schedule(k),
                            src_other.sections[i]->get_employee_accurals_amount(k),
                            src_other.sections[i]->get_employee_retentions_amount(k)
                        );

                        for (l = 0; l < src_other.sections[i]->get_employee_accurals_amount(k); l++)
                        {
                            result.sections[j]->set_employee_accurals_period(index, l, src_other.sections[i]->get_employee_accural_period(k, l));
                            result.sections[j]->set_employee_accurals_type(index, l, src_other.sections[i]->get_employee_accural_type(k, l));
                            result.sections[j]->set_employee_accurals_sum(index, l, src_other.sections[i]->get_employee_accural_sum(k, l));
                            result.sections[j]->set_employee_accurals_attendance(index, l, src_other.sections[i]->get_employee_accural_attendance(k, l));
                            result.sections[j]->set_employee_accurals_hours(index, l, src_other.sections[i]->get_employee_accural_hours(k, l));
                        }

                        for (l = 0; l < src_other.sections[i]->get_employee_retentions_amount(k); l++)
                        {
                            result.sections[j]->set_employee_retentions_period(index, l, src_other.sections[i]->get_employee_retention_period(k, l));
                            result.sections[j]->set_employee_retentions_type(index, l, src_other.sections[i]->get_employee_retention_type(k, l));
                            result.sections[j]->set_employee_retentions_sum(index, l, src_other.sections[i]->get_employee_retention_sum(k, l));
                        }
                    }

                    found = true;
                    break;
                }
            }
            if (!found)
            {
                Section* new_section = new Section(*(src_other.sections[i]));
                Section** new_sections = new Section * [result.sections_amount + 1];
                for (k = 0; k < result.sections_amount; k++)
                {
                    new_sections[k] = result.sections[k];
                }
                delete[] result.sections;
                result.sections = new_sections;
                result.sections[result.sections_amount++] = new_section;
            }
        }
        return result;
    }

    string get_list_name() const { return list_name; }
    unsigned long int get_sections_amount() const { return sections_amount; }

    bool set_list_name(const string settable_list_name)
    {
        bool result = false;

        if (settable_list_name.length() > 0)
        {
            list_name = settable_list_name;
            result = true;
        }

        return result;
    }

    void output() const
    {
        cout << "Файл: " << list_name << "\n\n";
        for (int i = 0; i < sections_amount; i++)
        {
            sections[i]->output();
        }
        cout << "\n\n" << endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    List A("C:\\Users\\i8888\\YandexDisk\\Университет\\Работы\\Лабораторные работы\\Объектно-ориентированное программирование\\Лабораторная работа №3\\Lab. №3\\File A.TXT");
    List B("C:\\Users\\i8888\\YandexDisk\\Университет\\Работы\\Лабораторные работы\\Объектно-ориентированное программирование\\Лабораторная работа №3\\Lab. №3\\File B.TXT");
    List C = A + B;
    C.output();
    return 0;
}

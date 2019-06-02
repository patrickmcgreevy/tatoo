#pragma once
#include "Stack.h"
#include <string>
using std::string;

class Record
{
public:
	Record();
	Record(Record &new_data);
	~Record();
	//getters
	int get_record_num(void) { return record_num; }
	int get_id(void) { return id_num; }
	int get_num_absences(void) { return num_absences; }
	string get_name(void) { return name; }
	string get_email(void) { return email; }
	string get_units(void) { return units; }
	string get_program(void) { return program; }
	string get_level(void) { return level; }
	Stack get_absences(void) { return absences; }

	//setters
	void set_record_num(int new_n) { record_num = new_n; }
	void set_id(int new_id) { id_num = new_id; }
	void set_num_absences(int absences) { num_absences = absences; }
	void set_name(string new_s) { name = new_s; }
	void set_email(string new_s) {email = new_s; }
	void set_units(string new_s) {units = new_s; }
	void set_program(string new_s) { program = new_s; }
	void set_level(string new_s) { level = new_s; }

private:
	int record_num; // max 3 digits
	int id_num; // max 9 digits
	int num_absences;
	string name; // (Last, First)
	string email; 
	string units; // number of credits or AU for audit
	string program; // major
	string level; // (freshman, sophomore, junior, senior, graduate)
	Stack absences;
};


Record::Record()
{
	record_num = 0;
	id_num = 0;
	num_absences = 0;
	name = "\0";
	email = "\0";
	units = "\0";
	program = "\0";
	level = "\0";
}

Record::Record(Record &new_data)
{
	record_num = new_data.record_num;
	id_num = new_data.id_num;
	name = new_data.name;
	email = new_data.email;
	units = new_data.units;
	program = new_data.program;
	level = new_data.level;
	num_absences = new_data.num_absences;
}

Record::~Record()
{

}

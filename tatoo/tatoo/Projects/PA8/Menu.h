#pragma once

#include "List.h"
#include "Record.h"
#include <iostream>
#include <fstream>
#include<time.h>
using std::cout;
using std::endl;
using std::cin;
using std::to_string;
using std::getline;

class Menu
{
public:
	void run(void);
	void import_file(string filename);
	void load_master(void);
	void store_master(void);
	void mark_absences(void);
	void edit_absences(void);
	void gen_report(void);

private:
	List<Record> master;
};

void Menu::run()
{
	int choice = 0;

	while (choice != 7)
	{
		cout << "1.  Import course list\n\
2.  Load master list\n\
3.  Store master \n\
4.  Mark absences\n\
5.  BONUS: Edit absences\n\
6.  Generate report\n\
7.  Exit\n";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			import_file("classList.csv");
			break;
		case 2:
			load_master();
			break;
		case 3:
			store_master();
			break;
		case 4:
			mark_absences();
			break;
		case 5:
			edit_absences();
			break;
		case 6:
			gen_report();
			break;
		case 7:
			break;
		}
	}
}

void Menu::import_file(string filename)
{
	string nrecord_num; // max 3 digits
	string nid_num; // max 9 digits
	string t;
	string nname; // (Last, First)
	string nemail;
	string nunits; // number of credits or AU for audit
	string nprogram; // major
	string nlevel; // (freshman, sophomore, junior, senior, graduate)
	std::fstream infile(filename);
	getline(infile, t);
	while (!infile.eof())
	{
		Record new_record;
		Node<Record> *new_node = NULL;

		getline(infile, nrecord_num, ',');
		if (std::empty(nrecord_num)) break;
		getline(infile, nid_num, ',');
		getline(infile, nname, '\"');
		getline(infile, nname, '\"');
		getline(infile, t, ',');
		getline(infile, nemail, ',');
		getline(infile, nunits, ',');
		getline(infile, nprogram, ',');
		getline(infile, nlevel);
		
		new_record.set_record_num(std::stoi(nrecord_num));
		new_record.set_id(std::stoi(nid_num));
		new_record.set_name(nname);
		new_record.set_email(nemail);
		new_record.set_units(nunits);
		new_record.set_program(nprogram);
		new_record.set_level(nlevel);
		
		new_node = new_node->make_node(new_record);

		master.insert_af(new_node);
	}
	
}

void Menu::load_master(void)
{
	std::fstream outfile("master.txt");
	string nrecord_num; // max 3 digits
	string nid_num; // max 9 digits
	string t;
	string nname; // (Last, First)
	string nemail;
	string nunits; // number of credits or AU for audit
	string nprogram; // major
	string nlevel; // (freshman, sophomore, junior, senior, graduate)
	string num_absences;

	while (!outfile.eof())
	{
		Record new_record;
		Node<Record> *new_node = nullptr;

		getline(outfile, nrecord_num, ',');
		if (std::empty(nrecord_num)) break;
		getline(outfile, nid_num, ',');
		getline(outfile, nname, '\"');
		getline(outfile, nname, '\"');
		getline(outfile, t, ',');
		getline(outfile, nemail, ',');
		getline(outfile, nunits, ',');
		getline(outfile, nprogram, ',');
		getline(outfile, nlevel, ',');
		getline(outfile, num_absences, ',');

		new_record.set_record_num(std::stoi(nrecord_num));
		new_record.set_id(std::stoi(nid_num));
		new_record.set_name(nname);
		new_record.set_email(nemail);
		new_record.set_units(nunits);
		new_record.set_program(nprogram);
		new_record.set_level(nlevel);
		new_record.set_num_absences(std::stoi(num_absences));

		for (int i = 0; i < new_record.get_num_absences(); i++)
		{
			Node<string> *pnew_node2 = nullptr;
			string new_absence;
			if (i + 1 == new_record.get_num_absences()) getline(outfile, new_absence);
			else getline(outfile, new_absence, ',');
			pnew_node2 = pnew_node2->make_node(new_absence);
			new_record.get_absences().push(pnew_node2);
		}

		new_node = new_node->make_node(new_record);

		master.insert_af(new_node);
	}
}

void Menu::store_master(void)
{
	std::fstream infile("master.txt");

	for (Node<Record> *p_cur = master.get_head(); p_cur != NULL; p_cur = p_cur->get_next())
	{
		infile  << p_cur->get_data().get_record_num() << "," << p_cur->get_data().get_id() << ","\
			<< "\"" << p_cur->get_data().get_name() << "\"," << p_cur->get_data().get_email() << "," << p_cur->get_data().get_units()\
			<< "," << p_cur->get_data().get_program() << "," << p_cur->get_data().get_level() << "," << p_cur->get_data().get_num_absences();
		List<string> absences;
		for (int i = 0; i < p_cur->get_data().get_num_absences(); i++)
		{
			string absence = "\0";
			absence =p_cur->get_data().get_absences().pop();
			infile << "," << absence;
			Node<string> *new_node = nullptr;
			new_node = new_node->make_node(absence);
			absences.insert_af(new_node);
		}
		for (Node<string> *p_cur2 = absences.get_head(); p_cur2 != NULL; p_cur2 = p_cur2->get_next())
		{
			p_cur->get_data().get_absences().push(p_cur2);
		}
		infile << endl;
	}
}

void Menu::mark_absences(void)
{
	string date;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	date = to_string(now->tm_year + 1900) + '/'\
		+ to_string(now->tm_mon + 1) + '/'\
		+ to_string(now->tm_mday);

	for (Node<Record> *p_cur = master.get_head(); p_cur != NULL; p_cur = p_cur->get_next())
	{
		char check;
		Node<string> *new_node = nullptr;
		cout << "Is " << p_cur->get_data().get_name() << " here?(y/n)" << endl;
		cin >> check;
		system("cls");
		if (check == 'n')
		{
			new_node = new_node->make_node(date);
			p_cur->get_data().get_absences().push(new_node);
			p_cur->get_data().set_num_absences(p_cur->get_data().get_num_absences() + 1);
		}
	}
}

void Menu::edit_absences(void)
{
	string name_or_id;
	cout << "Enter a name or student id to edit: " << endl;
	cin >> name_or_id;
	system("cls");
	bool is_student_found = false;
	bool is_absence_found = false;

	for (Node<Record> *p_cur = master.get_head(); p_cur != NULL; p_cur = p_cur->get_next())
	{
		if (to_string(p_cur->get_data().get_id()) == name_or_id || p_cur->get_data().get_name() == name_or_id)
		{
			is_student_found = true;
			//edit here
			string date;
			cout << "Enter the date of the absence to removed(yyyy/mm/dd): " << endl;
			cin >> date;
			system("cls");
			List<string> *absences = nullptr;
			for (int i = 0; i < p_cur->get_data().get_num_absences(); i++)
			{
				string absence = p_cur->get_data().get_absences().pop();
				if (absence == date)
				{
					is_absence_found = true;
					break;
				}
				else
				{
					Node<string> *new_node = nullptr;
					new_node = new_node->make_node(absence);
					absences->insert_af(new_node);
				}
			}
			for (Node<string> *p_cur2 = absences->get_head(); p_cur2 != NULL; p_cur2 = p_cur2->get_next())
			{
				p_cur->get_data().get_absences().push(p_cur2);
			}
			break;
		}
	}
	if (!is_student_found) cout << "student not found" << endl;
	else if (!is_absence_found) cout << "absence not found" << endl;
	system("pause");
	system("cls");
}

void Menu::gen_report(void)
{
	char choice;
	cout << "1. Show records for all students, or enter a number to show only students with that many absences or more: " << endl;
	cin >> choice;
	for (Node<Record> *p_cur = master.get_head(); p_cur != NULL; p_cur = p_cur->get_next())
	{
		if (p_cur->get_data().get_num_absences() >= choice)
		{
			cout << p_cur->get_data().get_name() << ": Last absent on " << p_cur->get_data().get_absences().peek() << endl;
		}
		else if (choice == 1)
		{
			if (p_cur->get_data().get_num_absences() == 1) 
				cout << p_cur->get_data().get_name() << ": Absent on " << p_cur->get_data().get_absences().peek() << endl;
			else 
				cout << p_cur->get_data().get_name() << ": No absences" << endl;
		}
	}
}
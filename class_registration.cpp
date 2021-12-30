#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Utils
int findStudentById(vector<string> studentIds, string id);
int findLectureByCode(vector<string> lectureCodes, string code);
void deleteElement(vector<string>& v, int index);

// File read
void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);

// File write
void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes);
void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits);

// Get user input
string getInputId();
string getInputPassword();

// Login
int studentLogin(const vector<string>& studentIds, const vector<string>& passwords);
bool adminLogin();
int login(const vector<string>& studentIds, const vector<string>& passwords);

// Common
void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user = -100);

// Admin
void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);
void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes);
int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits);

// User
void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user);
void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user);
void changePassword(vector<string>& passwords, const int& user);
int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user);

int main() {
	int user = -1; //user index
	int status = -1;

	// Student Info
	vector<string> studentIds;
	vector<string> passwords;
	vector<string> names;
	vector<int> credits;
	vector<vector<string>> appliedLectureCodes;

	// Lecture Info
	vector<string> lectureCodes;
	vector<string> lectureNames;
	vector<int> lectureCredits;
	vector<int> limits;

	// Read from files
	readStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
	readLectureFile(lectureCodes, lectureNames, lectureCredits, limits);

	// Login phase
	while (status == -1) {
		user = login(studentIds, passwords);

		if (user == -999) { // Login fail
			break;
		}
		else if (user == -1) { // Exit command
			break;
		}
		else if (user == -100) { // Admin login success
			status = runAdmin(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits);
		}
		else { // Student login success
			status = runStudent(studentIds, passwords, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
		}
	}

	// Write to files
	writeStudentFile(studentIds, passwords, names, credits, appliedLectureCodes);
	writeLectureFile(lectureCodes, lectureNames, lectureCredits, limits);

	return 0;
}

int findStudentById(vector<string> studentIds, string id) {
	for (unsigned i = 0; i < studentIds.size(); i++) {
		if (studentIds[i] == id)
			return i;
	}
	return -1;
}

int findLectureByCode(vector<string> lectureCodes, string code) {
	for (unsigned i = 0; i < lectureCodes.size(); i++) {
		if (lectureCodes[i] == code)
			return i;
	}
	return -1;
}

void deleteElement(vector<string>& v, int index) {
	v.erase(v.begin() + index);
}

void readStudentFile(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	ifstream fin("students.txt");
	string id,password,name,lec;
	int credit,number;
	vector<string> lecture;
	vector<string> student;
	int user = 0;
	
	while (!fin.eof()) {

		fin >> id >> password >> name >> credit >> number;
		if (fin.eof())
			break;
		appliedLectureCodes.push_back(student);
		for (int i = 0; i < number; i++) {
			fin >> lec;
			appliedLectureCodes[user].push_back(lec);	
		}
	
		studentIds.push_back(id);
		passwords.push_back(password);
		names.push_back(name);
		credits.push_back(credit);
		user++;
		

		}
	
		
		fin.close();
	}

	


void readLectureFile(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	ifstream fin("lectures.txt");
	string lecture_code, lecture_name;
	int lecture_credit, limit;
	while (!fin.eof()) {
		fin >> lecture_code >> lecture_name >> lecture_credit >> limit;
		if (fin.eof())
			break;
		lectureCodes.push_back(lecture_code);
		lectureNames.push_back(lecture_name);
		lectureCredits.push_back(lecture_credit);
		limits.push_back(limit);
		
	}
	fin.close();
}

void writeStudentFile(const vector<string>& studentIds, const vector<string>& passwords, const vector<string>& names, const vector<int>& credits, const vector<vector<string>>& appliedLectureCodes) {
	ofstream fout("students.txt");
	for (int i = 0; i < studentIds.size(); i++) {
		fout << studentIds[i] << "\t" << passwords[i] << "\t" << names[i] << "\t" << credits[i] << "\t";
		fout << appliedLectureCodes[i].size() << "\t";
		for (int j = 0; j < appliedLectureCodes[i].size(); j++)
			fout << appliedLectureCodes[i][j] <<"\t";
	fout << endl;
	}
	fout.close();
}


void writeLectureFile(const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits) {

	ofstream fout("lectures.txt");
	for (int i = 0; i < lectureCodes.size(); i++) {
		fout << lectureCodes[i] << "\t" << lectureNames[i] << "\t" << lectureCredits[i] << "\t" << limits[i] << "\t";
	fout << endl;
	}
	fout.close();
}

string getInputId() {
	string id;
	cout << "���̵�: ";
	cin >> id;
	return id;

}

string getInputPassword() {
	string password;
	cout << "��й�ȣ: ";
	cin >> password;
	return password;

}

int studentLogin(const vector<string>& studentIds, const vector<string>& passwords) {
	
	string id= getInputId();
	string password = getInputPassword();
	for (unsigned int i = 0; i < studentIds.size(); i++) {
		if (id == studentIds[i] && password == passwords[i])
			return i;
		}
		return -1;

}

bool adminLogin() {

	string id= getInputId();
	string password = getInputPassword();
	if (id == "admin" && password == "admin")
		return true;
	else
		return false;
	
}

int login(const vector<string>& studentIds, const vector<string>& passwords) {

	cout << "--------------------------------------------------------" << endl;
	cout << "1. �л� �α���" << endl;
	cout << "2. ������ �α���" << endl;
	cout << "0. ����" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << ">> ";
	string command;
	cin >> command;
	int count = 0;

	while (true) {
		
		if (command == "1") {
			int a = studentLogin(studentIds, passwords);
			if (a != -1) {
				return a;
			}

		}
		else if (command == "2") {
			if (adminLogin() == true) {
				return -100;
			}
		}
		else if (command == "0")
			return -1;
	

		count++;
		cout << "�α��� " << count << "ȸ ���� (3ȸ ���н� ����)" << endl;

		if (count == 3) {
			cout << "3ȸ �����Ͽ� �����մϴ�.";
			system("pause");
			return -999;
		}

	}
	
}

void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user ) {

	cout << "--------------------------------------------------------" << endl;
	cout << "�����ڵ�\t" << "���Ǹ�\t"<< "\t" << "����\t" << "���������ο�\n";
	cout << "--------------------------------------------------------" << endl;
	if (user == -100) {
		for (unsigned int i = 0; i < lectureCodes.size(); i++) {
			cout << lectureCodes[i] << "\t" << lectureNames[i] << "\t" << lectureCredits[i] << "\t" << limits[i] << "\n";
		}
		cout << "--------------------------------------------------------" << endl;
	}
	else { 
			for (unsigned int i = 0; i < appliedLectureCodes[user].size(); i++) {
				int index = findLectureByCode(lectureCodes, appliedLectureCodes[user][i]);
				if (index >= 0) {
					cout << appliedLectureCodes[user][i] << "\t" << lectureNames[index] << "\t" << lectureCredits[index] << "\t" << limits[index] << "\n";
				}
			}
		cout << "--------------------------------------------------------" << endl;
	}
}

void addStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	string id, password, name;
	vector<string> Lecture;
	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "�й�: ";
		cin >> id;
		cout << "��й�ȣ: ";
		cin >> password;
		cout << "�л� �̸�: ";
		cin >> name;
		cout << "--------------------------------------------------------" << endl;
		int index = findStudentById(studentIds, id);
		if (index != -1) {
			cout << "�̹� �����ϴ� �й��Դϴ�." << endl;
			system("pause");
		}
		else {
			studentIds.push_back(id);
			passwords.push_back(password);
			names.push_back(name);
			credits.push_back(18);
			appliedLectureCodes.push_back(Lecture);
			cout << "���������� ��ϵǾ����ϴ�." << endl; 
			system("pause");
			return;
		}
	}
}


void addLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	string add_lecture_code, lecture_name;
	int lecture_credit, lecture_limit;
	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "�����ڵ�: ";
		cin >> add_lecture_code;
		cout << "�����: ";
		cin >> lecture_name;
		cout << "����: ";
		cin >> lecture_credit;
		cout << "�����ο�: ";
		cin >> lecture_limit;
		cout << "--------------------------------------------------------" << endl;
		int index = findLectureByCode(lectureCodes, add_lecture_code);
		if (index != -1) {
			cout << "�̹� �����ϴ� �����ڵ� �Դϴ�." << endl;
			system("pause");
		}
		else  {
			lectureCodes.push_back(add_lecture_code);
			lectureNames.push_back(lecture_name);
			lectureCredits.push_back(lecture_credit);
			limits.push_back(lecture_limit);
			cout << "���������� ���ǰ� �����Ǿ����ϴ�." << endl; 
			system("pause");
			return;
		}
	}



	
}

void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits,-100); // ?
	string delete_lecturecode;

	while (true) {
		cout << "������ ���� �ڵ� (0: �ڷΰ���) >> ";
		cin >> delete_lecturecode;
		if (delete_lecturecode == "0")
			return;
		int index = findLectureByCode(lectureCodes, delete_lecturecode);
		if (index == -1) {
			cout << "��ġ�ϴ� �ڵ尡 �����ϴ�." << endl;
			system("pause");
		}


		else {
			for (int user = 0; user < credits.size(); user++) {
				int delete_index = findLectureByCode(appliedLectureCodes[user], delete_lecturecode);
				if (delete_index != -1) {
					appliedLectureCodes[user].erase(appliedLectureCodes[user].begin() + delete_index);
					credits[user] += lectureCredits[index];
				}
			}
			
			deleteElement(lectureCodes, index);
			deleteElement(lectureNames, index);
			limits.erase(limits.begin() + index);

			lectureCredits.erase(lectureCredits.begin() + index);

			cout << "���������� ���ǰ� ���Ǿ����ϴ�." << endl;
			system("pause");
		}
	}

}

int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	
	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "1. �л� �߰�" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� ����" << endl;
		cout << "4. �α׾ƿ�" << endl;
		cout << "0. ����" << endl;
		cout << "--------------------------------------------------------" << endl;
		int num;
		cout << ">> ";
		cin >> num;
		if (num == 1)
			addStudent(studentIds, passwords, names, credits, appliedLectureCodes);
		else if (num == 2)
			addLecture(lectureCodes, lectureNames, lectureCredits, limits);
		else if (num == 3)
			deleteLecture(lectureCodes, lectureNames, lectureCredits, limits, credits, appliedLectureCodes);
		else if (num == 4)
			return -1;
		else if (num == 0)
			return 0;
	}

}

void printStudent(const vector<string>& studentIds, const vector<string>& names, const vector<int>& credits, const int& user) {

	cout << "--------------------------------------------------------" << endl;
	cout << "�й�: " << studentIds[user] << "\t" << "�̸�: " << names[user] << "\t" << "������������: " << credits[user] << "\n";
	cout << "--------------------------------------------------------" << endl;
}

void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {

	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits,-100);
	string s;
	while (true) {
		cout << "��û�� ���� �ڵ�(0: �ڷΰ���) >> ";
		cin >> s;
		
		if (s == "0") {
			return;
		}
			int index = findLectureByCode(lectureCodes, s);
			if (index == -1) {
				system("pause");
				continue;
			}
			
			int compare = 0;
			string lec_name = lectureNames[index];
			for (int i = 0; i < appliedLectureCodes[user].size(); i++) {
				int before_index = findLectureByCode(lectureCodes, appliedLectureCodes[user][i]);
				if (before_index != -1) {
					if (index != before_index &&lec_name == lectureNames[before_index]) {
						compare = 1;
						break;
					}
				}
			}
			if (findLectureByCode(appliedLectureCodes[user], s) == -1 && compare != 1&&credits[user] >= lectureCredits[index] && limits[index] > 0) {
				appliedLectureCodes[user].push_back(s);
				appliedLectureCodes.push_back(appliedLectureCodes[user]);
				credits[user] -= lectureCredits[index];
				limits[index] -= 1;

				cout << "[" << s << "] " << lectureNames[index] << "(��)�� ���������� ��û�Ͽ����ϴ�." << endl;
				system("pause");
			}

			else {
				if (limits[index] == 0) {
					cout << "���������� �� á���ϴ�." << endl;
					system("pause");
				}
				else if (credits[user] < lectureCredits[index]) {
					cout << "�������������� �����մϴ�." << endl;
					system("pause");
				}
				else if (findLectureByCode(appliedLectureCodes[user], s) != -1) {
					cout << "�̹� �ش� ������ ��û�߽��ϴ�." << endl;
					system("pause");
				}
				else if(compare == 1){
					cout << "�̹� ���ϸ��� ������ ��û�߽��ϴ�." << endl;
					system("pause");
				
				}

			}

	}

}

void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
	/* ���� */
	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
	string s;
	
	while (true) {
		cout << "öȸ�� ���� �ڵ�(0: �ڷΰ���) >> ";
		cin >> s;
		
		if (s == "0")
			return;

		int index = findLectureByCode(appliedLectureCodes[user], s);
	   if (index == -1) {
			cout << "���� �ڵ尡 �ùٸ��� �ʽ��ϴ�." << endl;
			system("pause");
		}
	   else {
		   int index_2 = findLectureByCode(lectureCodes, appliedLectureCodes[user][index]);
		   cout << "[" << appliedLectureCodes[user][index] << "] " << lectureNames[index_2] << "(��)�� öȸ�Ͽ����ϴ�." << endl;
		   appliedLectureCodes[user].erase(appliedLectureCodes[user].begin() + index);
		   credits[user] += lectureCredits[index_2];
		   limits[index_2] += 1;
		   
		   system("pause");
	   }

	}
	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);


}

void changePassword(vector<string>& passwords, const int& user) {

	string password, new_password;
	cout << "���� Ȯ���� ���� ��й�ȣ�� �� �� �� �Է����ּ���." << endl;
	cout << "��й�ȣ: ";
	cin >> password;
	cout << "--------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------" << endl;
	if (password == passwords[user]) {
		cout << "���� ������ ��й�ȣ�� �Է��ϼ���." << endl;
		cout << "��й�ȣ: ";
		cin >> new_password;
		passwords[user] = new_password;
		cout << "����Ǿ����ϴ�." << endl;
		cout << "--------------------------------------------------------" << endl;
		system("pause");

	}
	else {
		cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
		system("pause");
	}

}

int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user) {

	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "1. ���� ��û" << endl;
		cout << "2. ���� ��Ȳ" << endl;
		cout << "3. ���� öȸ" << endl;
		cout << "4. ��й�ȣ ����" << endl;
		cout << "5. �α׾ƿ�" << endl;
		cout << "0. ����" << endl;
		cout << "--------------------------------------------------------" << endl;
		int num;
		cout << ">> ";
		cin >> num;
		if (num == 1)
			applyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
		else if (num == 2) {
				printStudent(studentIds, names, credits, user);
				printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
		
		}
		else if (num == 3)
			disapplyLecture(studentIds, names, credits, appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
		else if (num == 4)
			changePassword(passwords, user);
		else if (num == 5)
			return -1;
		else if (num == 0)
			return 1;
	}
	
}
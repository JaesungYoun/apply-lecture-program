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
	cout << "아이디: ";
	cin >> id;
	return id;

}

string getInputPassword() {
	string password;
	cout << "비밀번호: ";
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
	cout << "1. 학생 로그인" << endl;
	cout << "2. 관리자 로그인" << endl;
	cout << "0. 종료" << endl;
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
		cout << "로그인 " << count << "회 실패 (3회 실패시 종료)" << endl;

		if (count == 3) {
			cout << "3회 실패하여 종료합니다.";
			system("pause");
			return -999;
		}

	}
	
}

void printLectures(const vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, const vector<int>& limits, const int& user ) {

	cout << "--------------------------------------------------------" << endl;
	cout << "과목코드\t" << "강의명\t"<< "\t" << "학점\t" << "수강가능인원\n";
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
		cout << "학번: ";
		cin >> id;
		cout << "비밀번호: ";
		cin >> password;
		cout << "학생 이름: ";
		cin >> name;
		cout << "--------------------------------------------------------" << endl;
		int index = findStudentById(studentIds, id);
		if (index != -1) {
			cout << "이미 존재하는 학번입니다." << endl;
			system("pause");
		}
		else {
			studentIds.push_back(id);
			passwords.push_back(password);
			names.push_back(name);
			credits.push_back(18);
			appliedLectureCodes.push_back(Lecture);
			cout << "성공적으로 등록되었습니다." << endl; 
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
		cout << "과목코드: ";
		cin >> add_lecture_code;
		cout << "과목명: ";
		cin >> lecture_name;
		cout << "학점: ";
		cin >> lecture_credit;
		cout << "수강인원: ";
		cin >> lecture_limit;
		cout << "--------------------------------------------------------" << endl;
		int index = findLectureByCode(lectureCodes, add_lecture_code);
		if (index != -1) {
			cout << "이미 존재하는 과목코드 입니다." << endl;
			system("pause");
		}
		else  {
			lectureCodes.push_back(add_lecture_code);
			lectureNames.push_back(lecture_name);
			lectureCredits.push_back(lecture_credit);
			limits.push_back(lecture_limit);
			cout << "성공적으로 강의가 개설되었습니다." << endl; 
			system("pause");
			return;
		}
	}



	
}

void deleteLecture(vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, vector<int>& credits, vector<vector<string>>& appliedLectureCodes) {
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits,-100); // ?
	string delete_lecturecode;

	while (true) {
		cout << "삭제할 강의 코드 (0: 뒤로가기) >> ";
		cin >> delete_lecturecode;
		if (delete_lecturecode == "0")
			return;
		int index = findLectureByCode(lectureCodes, delete_lecturecode);
		if (index == -1) {
			cout << "일치하는 코드가 없습니다." << endl;
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

			cout << "성공적으로 강의가 폐쇄되었습니다." << endl;
			system("pause");
		}
	}

}

int runAdmin(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits) {
	
	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "1. 학생 추가" << endl;
		cout << "2. 강의 개설" << endl;
		cout << "3. 강의 삭제" << endl;
		cout << "4. 로그아웃" << endl;
		cout << "0. 종료" << endl;
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
	cout << "학번: " << studentIds[user] << "\t" << "이름: " << names[user] << "\t" << "수강가능학점: " << credits[user] << "\n";
	cout << "--------------------------------------------------------" << endl;
}

void applyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {

	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits,-100);
	string s;
	while (true) {
		cout << "신청할 과목 코드(0: 뒤로가기) >> ";
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

				cout << "[" << s << "] " << lectureNames[index] << "(을)를 성공적으로 신청하였습니다." << endl;
				system("pause");
			}

			else {
				if (limits[index] == 0) {
					cout << "수강정원이 꽉 찼습니다." << endl;
					system("pause");
				}
				else if (credits[user] < lectureCredits[index]) {
					cout << "수강가능학점이 부족합니다." << endl;
					system("pause");
				}
				else if (findLectureByCode(appliedLectureCodes[user], s) != -1) {
					cout << "이미 해당 과목을 신청했습니다." << endl;
					system("pause");
				}
				else if(compare == 1){
					cout << "이미 동일명의 과목을 신청했습니다." << endl;
					system("pause");
				
				}

			}

	}

}

void disapplyLecture(const vector<string>& studentIds, const vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, const vector<string>& lectureCodes, const vector<string>& lectureNames, const vector<int>& lectureCredits, vector<int>& limits, const int& user) {
	/* 구현 */
	printStudent(studentIds, names, credits, user);
	printLectures(appliedLectureCodes, lectureCodes, lectureNames, lectureCredits, limits, user);
	string s;
	
	while (true) {
		cout << "철회할 과목 코드(0: 뒤로가기) >> ";
		cin >> s;
		
		if (s == "0")
			return;

		int index = findLectureByCode(appliedLectureCodes[user], s);
	   if (index == -1) {
			cout << "과목 코드가 올바르지 않습니다." << endl;
			system("pause");
		}
	   else {
		   int index_2 = findLectureByCode(lectureCodes, appliedLectureCodes[user][index]);
		   cout << "[" << appliedLectureCodes[user][index] << "] " << lectureNames[index_2] << "(을)를 철회하였습니다." << endl;
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
	cout << "본인 확인을 위해 비밀번호를 한 번 더 입력해주세요." << endl;
	cout << "비밀번호: ";
	cin >> password;
	cout << "--------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------" << endl;
	if (password == passwords[user]) {
		cout << "새로 설정할 비밀번호를 입력하세요." << endl;
		cout << "비밀번호: ";
		cin >> new_password;
		passwords[user] = new_password;
		cout << "변경되었습니다." << endl;
		cout << "--------------------------------------------------------" << endl;
		system("pause");

	}
	else {
		cout << "비밀번호가 일치하지 않습니다." << endl;
		system("pause");
	}

}

int runStudent(vector<string>& studentIds, vector<string>& passwords, vector<string>& names, vector<int>& credits, vector<vector<string>>& appliedLectureCodes, vector<string>& lectureCodes, vector<string>& lectureNames, vector<int>& lectureCredits, vector<int>& limits, int user) {

	while (true) {
		cout << "--------------------------------------------------------" << endl;
		cout << "1. 수강 신청" << endl;
		cout << "2. 수강 현황" << endl;
		cout << "3. 수강 철회" << endl;
		cout << "4. 비밀번호 변경" << endl;
		cout << "5. 로그아웃" << endl;
		cout << "0. 종료" << endl;
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
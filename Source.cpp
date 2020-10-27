#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const char Filename[] = "Domashno.txt";
fstream fp;
enum G { male, female, other };
//string.substr(0,5) --> wzima 5 smvola ot nachalen simvol 0 (wklyuchitelno)

class Person {
protected:
	string name;
	G gender;
	string DateOfBirth;
public:
	void setName(string n) { //(const char*n)
		name = n;
	}
	void setGender(G g1) {
		gender = g1;
	}
	void setDate(string d) {
		DateOfBirth = d;
	}
	string getName() {
		return name;
	}
	G getGender() {
		return gender;
	}
	string getDate() {
		return DateOfBirth;
	}
	void init(string n, G s, string d) {
		name = n; gender = s; DateOfBirth = d;
	}
	Person(string n, G s, string d) {
		name = n; gender= s; DateOfBirth = d;
	}
	Person() {
		name = DateOfBirth = ""; gender ;
	}
	void print() {
		cout << name << ", " << EnumToString(gender)<<", "<< DateOfBirth << endl;
	}
	Person(const Person& obj) {
		name = obj.name;
		gender = obj.gender;
		DateOfBirth = obj.DateOfBirth;
	}
	string EnumToString(G gender) {
		switch (gender) {
		case 0: return "male";
		case 1: return "female";
		case 2: return "other";
		}

	}
	G StringToEnum(string s) {
		if (s == "male")
			return male;
		else if (s == "female")
			return female;
		else 
			return other;
	}
	friend istream&operator>>(istream& istr, Person& obj) { 
		string pol;
		istr >> obj.name >> pol >> obj.DateOfBirth ;
		obj.StringToEnum(pol); 
		return istr;
	}
	friend ostream&operator<<(ostream& ostr, const Person& obj) {
		ostr << obj.name << ", " << obj.gender << ", " << obj.DateOfBirth << endl;
		return ostr;
	}
};

class Address {
private:
	string city;
	string street;
	string postal_code;
public:
	void setCity(string c) {
		city = c;
	}
	void setStreet(string s) {
		street = s;
	}
	void setPostal(string p) {
		postal_code = p;
	}
	string getCity() {
		return city;
	}
	string getStreet() {
		return street;
	}
	string getPostal() {
		return postal_code;
	}
	Address() {
		city = street = postal_code = "";
	}
	Address(string c, string s, string p) {
		city = c;
		street = s;
		postal_code = p;
	}
	Address(const Address& obj) {
		city = obj.city;
		street = obj.street;
		postal_code = obj.postal_code;
	}
	void init(string c, string s, string p) {
		city = c;
		street = s;
		postal_code = p;
	}
	void print() {
		cout << city << ", " << street << ", " << postal_code << endl;
	}
	friend ostream&operator<<(ostream&ostr, const Address&obj) { 
		ostr << obj.city << ", " << obj.street << ", " << obj.postal_code << endl;
		return ostr;
	}
	friend istream&operator>>(istream& istr, Address& obj) { 
		istr >> obj.city >> obj.street >> obj.postal_code;
		return istr;
	}
};

class Student : public Person { 
protected:
	string EGN;
	string Fnumber;
	Address adr;
public:
	Student() {
		EGN = ""; Fnumber = "";
	}
	Student(string n, G s, string d , string e, string num, Address a):Person(n,s,d) {
		EGN = e;
		Fnumber = num;
		adr = a;
	}
	Student(string e, string num, Address a) { 
		EGN = e;
		Fnumber = num;
		adr = a;
	}
	Student(const Student& obj) {
		EGN = obj.EGN;
		Fnumber = obj.Fnumber;
		adr = obj.adr;
	}
	void setEGN(string e) {
		EGN = e;
	}
	void setFnum(string num) {
		Fnumber=num;
	}
	string getEGN() {
		return EGN;
	}
	string getFnum() {
		return Fnumber;
	}
	void print() {
		Person::print();
		cout << ", " << EGN << ", " << Fnumber << ", ";
		adr.print();
		cout << endl;
		
	}
	friend ostream&operator<<(ostream&ostr, const Student&obj) { 
		ostr << obj.name << ", " << obj.gender << ", " << obj.DateOfBirth << ", " << obj.EGN << ", " << obj.Fnumber << ", " << obj.adr << endl;
		return ostr;
	}
	friend istream&operator>>(istream&istr, Student&obj) { 
		string pol;
		istr >> obj.name >> pol >> obj.DateOfBirth >> obj.EGN >> obj.Fnumber >> obj.adr;
		obj.StringToEnum(pol); 
		return istr;
	}
	int GetAge() {
		int a, b;
		b = stoi(EGN.substr(0,2));
		if (b <= 10) {
			a = 2000 + b;
			return 2020-a;
		}
		if (b > 10) {
			a = 1900 + b;
			return 2020 - a;
		}
	}
	bool EqualAge(Student& obj) {
		return this->GetAge() == obj.GetAge();
	}
	bool DiffAge(Student& obj) {
		return this->GetAge() != obj.GetAge();
	}
	bool IsYounger(Student& obj) {
		return this->GetAge() < obj.GetAge();
	}
	bool IsOlder(Student& obj) {
		return this->GetAge() > obj.GetAge();
	}
	bool isValid() {
		if (EGN.length() == 10) {
			if (DateOfBirth.substr(8, 2) == EGN.substr(0, 2)) {
				string s = DateOfBirth.substr(6,4);				
				int a = stoi(s);
				if (a < 2000 && DateOfBirth.substr(3, 2) == EGN.substr(2, 2) || a >= 2000 && stoi(DateOfBirth.substr(3, 2))+40 == stoi(EGN.substr(2, 2))) { 
					if (DateOfBirth.substr(0, 2) == EGN.substr(4, 2)) {
						// 6ta, 7ma i 8ma cifra ot EGN-to sa svyrzani s regiona na rajdane i t.n, za tova propuskam, a i stava mnogo slojno
						// za kontrolnata (posledna) cifra 
						int arr[10];
						for (int i = 0; i < 10; i++) {
							arr[i] = EGN[i] - '0';
						}
						int a = arr[0] * 2 + arr[1] * 4 + arr[2] * 8 + arr[3] * 5 + arr[4] * 10 + arr[5] * 9 + arr[6] * 7 + arr[7] * 3 + arr[8] * 6;
						int b = a / 11;
						int K = a - b * 11;
						if (K == stoi(EGN.substr(9, 1))) {
							return true;
						}
						else
							return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	} 

};
 
class GSM : public Student {
private:
	string number, model;
	int tplan;
public:
	GSM() {
		number = model = ""; tplan = 0;
	}
	void init(string num, string mod, int plan) {
		number = num; model = mod; tplan = plan;
	}
	GSM(string num, string mod, int plan ) {
		number = num; model = mod; tplan = plan;
	}
	int GetPlan() {
		return tplan;
	}
	virtual string getGSMnumber() { return 0; }
	virtual istream&inputGSM(istream&istr) = 0;
	virtual ostream&outputGSM(ostream&ostr)const = 0;
	friend istream&operator>>(istream& istr, Student& obj) {
		istr >> obj.number >> obj.model >> obj.tplan;
		return istr;
	}
};

int main() {
	
	Person p1, p2;
	p1.init("Maria", female, "22.03.2000");
	p2.init("Stoqn", male, "15.09.2002");
	cout << "Person 1 name, gender: "; p1.print();
	cout << "Person 2 name, gender: "; p2.print();
	Person p3("Acho", male, "01.02.1999");
	Person array[5] = {p1, p2, p3, Person("Alex", other, "02.01.2000"), Person("Mika", female, "29.03.1997")};
	cout << "Array of People: " << endl;
	for (int i = 0; i < 5; i++) {
		array[i].print();
	}
	Student p4("Mariela", female, "01.06.2000" , "0046011017", "19621692", Address("Varna", "Vladislavovo", "9023"));
	cout << "\nStudent 4 name, gender, date, EGN, Fnumber: "; p4.print();
	if (p4.isValid())
		cout << p4.getEGN() << " is a valid EGN."<<endl;
	else
		cout << p4.getEGN() << " is not a valid ENG."<<endl; 
	Student p5("Ivan", male, "22.02.1996", "9621020510", "19621699", Address("Varna", "Vladislavovo", "9023"));
	cout << "\nStudent 5 name, gender, date, EGN, Fnumber: "; //p5.print(); 
	cout << p5;
	cout << "\nAge of p5: " << p5.GetAge() << endl;
	cout << "\nStudent 4 age compared to Student 5 age: ";
	if (p4.EqualAge(p5))
		cout << "equal age" << endl;
	else
		cout << "diff age" << endl;
	Student p6;
    cout << "Input Student(name, gender, date, EGN, Fnumber, adr(city, street, postal code)): ";
    cin >> p6;
	cout << "Person 6: " << p6;


	fp.open(Filename, ios::out);
	if (!fp) { cout << "\n Error in file! \n"; exit(1); }
	fp.write((char*)array, sizeof(Student));
	fp.close();
	system("pause");
	return 0;
}
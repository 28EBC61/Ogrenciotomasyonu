#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct StudentNode {
    string name;
    int id;
    string department;
    vector<int> grades;  
    StudentNode* next;

    StudentNode(string name, int id, string department) {
        this->name = name;
        this->id = id;
        this->department = department;
        this->next = nullptr;
    }

    
    double calculateAverage() {
        if (grades.empty()) return 0.0; 
        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }
        return static_cast<double>(sum) / grades.size();
    }
};

class StudentAutomation {
private:
    StudentNode* head;

public:
    StudentAutomation() {
        head = nullptr;
    }

    
    void addStudent(string name, int id, string department) {
        StudentNode* newNode = new StudentNode(name, id, department);

        if (head == nullptr || head->id > id) {
            newNode->next = head;
            head = newNode;
        }
        else {
            StudentNode* temp = head;
            while (temp->next != nullptr && temp->next->id < id) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        cout << "Ogrenci basariyla eklendi: " << name << " - " << id << " - " << department << endl;
    }

    
    void deleteStudent(int id) {
        if (head == nullptr) {
            cout << "Ogrenci bulunmamaktadir!" << endl;
            return;
        }

        if (head->id == id) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Ogrenci silindi: " << id << endl;
            return;
        }

        StudentNode* temp = head;
        while (temp->next != nullptr && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Belirtilen numaraya sahip ogrenci bulunamadi: " << id << endl;
        }
        else {
            StudentNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Ogrenci silindi: " << id << endl;
        }
    }

    
    void addGrade(int id, int grade) {
        StudentNode* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                temp->grades.push_back(grade); 
                cout << "Not eklendi: " << grade << " (Ogrenci: " << temp->name << ")" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Ogrenci bulunamadi!" << endl;
    }

    
    void displayAverage(int id) {
        StudentNode* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Ortalama: " << temp->calculateAverage() << " (Ogrenci: " << temp->name << ")" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Ogrenci bulunamadi!" << endl;
    }

    
    void searchStudent(int id) {
        StudentNode* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "Ogrenci bulundu: " << temp->name << " - " << temp->id << " - " << temp->department << endl;
                cout << "Ortalama: " << temp->calculateAverage() << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Ogrenci bulunamadi: " << id << endl;
    }

    
    void displayStudents() {
        if (head == nullptr) {
            cout << "Ogrenci listesi bos!" << endl;
            return;
        }

        StudentNode* temp = head;
        while (temp != nullptr) {
            cout << temp->name << " - " << temp->id << " - " << temp->department
                << " - Ortalama: " << temp->calculateAverage() << endl;
            temp = temp->next;
        }
    }

    ~StudentAutomation() {
        while (head != nullptr) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    StudentAutomation students;
    int choice, id, grade;
    string name, department;

    do {
        cout << "\n1. Ogrenci Ekleme\n2. Ogrenci Silme\n3. Not Ekleme\n4. Ortalama Goruntuleme\n";
        cout << "5. Ogrenci Arama\n6. Ogrencileri Listeleme\n7. Cikis\nSeciminiz: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Ogrenci Adi: ";
            getline(cin, name);
            cout << "Ogrenci Numarasi: ";
            cin >> id;
            cin.ignore();
            cout << "Bolum: ";
            getline(cin, department);
            students.addStudent(name, id, department);
            break;
        case 2:
            cout << "Silinecek Ogrenci Numarasi: ";
            cin >> id;
            students.deleteStudent(id);
            break;
        case 3:
            cout << "Ogrenci Numarasi: ";
            cin >> id;
            cout << "Not: ";
            cin >> grade;
            students.addGrade(id, grade);
            break;
        case 4:
            cout << "Ogrenci Numarasi: ";
            cin >> id;
            students.displayAverage(id);
            break;
        case 5:
            cout << "Aranacak Ogrenci Numarasi: ";
            cin >> id;
            students.searchStudent(id);
            break;
        case 6:
            students.displayStudents();
            break;
        case 7:
            cout << "Programdan cikiliyor..." << endl;
            break;
        default:
            cout << "Gecersiz secim! Lutfen tekrar deneyin." << endl;
        }
    } while (choice != 7);

    return 0;
}
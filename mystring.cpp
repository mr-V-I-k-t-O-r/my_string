// my own Class string
#include <iostream>
#include<vector>

using namespace std;

// ToDo:
/* write setter of value(cin)
* write operator *= (digit)
* refactor code
* many public and private marks, do it need? - NO
*/
class My_string {

private:
    char* txt = NULL;
    int size;

public:
    friend ostream& operator<< (ostream& os, const My_string& str);

    My_string() {
        txt = new char;
        *txt = '\0';
        size = 0;
    }

    My_string(const char *str) {
        size = get_length(str);
        txt = new char[size + 1];
        for (int i = 0; i < size; i++) {
            txt[i] = str[i];
        }
        txt[size] = '\0';
    }

    ~My_string() {
        delete[] this->txt;
    }

    //for operator + or +=, need to check
    My_string* operator = (My_string* other) {
        delete[] this->txt;
        this->size = get_length(other->txt);
        this->txt = new char[size + 1];
        int i = 0;
        while (i < size) {
            this->txt[i] = other->txt[i++];
        }
        this->txt[size] = '\0';
        return this;
    }

    My_string* operator = (const My_string& other) {
        delete[] this->txt;
        size = get_length(other.txt);
        this->txt = new char[size + 1];
        int i = 0; 
        while (i <= size) {
            this->txt[i] = other.txt[i++];
        }
        return this;
    }

    My_string* operator = (const char* str) {
        delete[] this->txt;
        size = get_length(str);
        this->txt = new char[size + 1];
        int i = 0;
        while (i < size) {
            this->txt[i] = str[i++];
        }
        this->txt[size] = '\0';
        delete[] str;
        return this;
    }

    char* operator + (const My_string& other) {
        int length_f = get_length(this->txt);
        int length_s = get_length(other.txt);
        size = length_f + length_s;
        char* str = new char[size + 1];
        int i = 0;
        int j = 0;
        while (i < length_f) {
            str[i] = this->txt[i++];
        }
        while (j < length_s) {
            str[i++] = other.txt[j++];
        }
        str[size] = '\0';
        return str;
    }

    My_string* operator += (const My_string& other) {
        size = get_length(this->txt);
        char* str = new char[size + 1];
        int i = 0;
        while (i < size) {
            str[i] = this->txt[i++];
        }
        str[size] = '\0';
        delete[] this->txt;
        int length_f = size;
        int length_s = get_length(other.txt);
        this->txt = new char[length_f + length_s + 1];
        i = 0;
        int j = 0;
        while (i < length_f) {
            this->txt[i] = str[i++];
        }
        delete[] str;
        while (j < length_s) {
            this->txt[i++] = other.txt[j++];
        }
        this->txt[length_f + length_s] = '\0';
        return this;
    }

    My_string* operator * (int count) {
        char* str = new char[this->size];
        for (int i = 0; i < this->size; i++) {
            str[i] = this->txt[i];
        }
        delete this->txt;
        this->txt = new char[this->size * count + 1];
        for (int i = 0; i < count; i++) {
            for (int j = i * this->size + 0; (j - (i * this->size)) < this->size; j++) {
                this->txt[j] = str[j - i * this->size];
            }
        }
        this->size *= count;
        this->txt[size] = '\0';
        return this;
    }

    bool operator == (const My_string& other) {
        if (this->size != other.size) {
            return false;
        }
        int i = 0;
        while (this->txt[i] != '\0') {
            if (this->txt[i] != other.txt[i]) {
                return false;
            }
            i++;
        }
        return true;
    }

    bool operator != (const My_string& other) {
        if (this->size != other.size) {
            return true;
        }
        int i = 0;
        while (this->txt[i] != '\0') {
            if (this->txt[i] != other.txt[i]) {
                return true;
            }
        }
        return false;
    }

    char& operator [](int place) {
        return this->txt[place];
    }

    int length() {
        return this->size;
    }

private:
    //function to check length
    int get_length(const char* str) {
        int i = 0;
        while (str[i] != '\0') {
            i++;
        }
        return i;
    }
};

ostream& operator<< (ostream& os,const My_string& str) {
    int i = 0;
    while (str.txt[i] != '\0') {
        os << str.txt[i++];
    }
    return os;
}

//viselitsa by class
//game places in constructor
class vis{
private:
    My_string word;
    My_string write;
    int mistakes;
    vector<char> used_letters;
    bool play;

public:
    vis(My_string str)
    {
        word = str;
        write = (My_string)"*" * word.length();
        mistakes = 0;
        play = true;
        char letter;
        bool right;
        vector<char>::iterator i;
        //game
        while (true) {
            //take the letter
            cout << write << endl;
            cout << "mistakes: " << mistakes << endl;
            do {
                cout << "write a letter: ";
                cin >> letter;
                right = true;
                i = used_letters.begin();
                while (i != used_letters.end()) {
                    if (*i == letter) {
                        right = false;
                    }
                    i++;
                }
            } while (!right);
            //check for letter in the word
            right = moove(letter);
            if (right) {
                replace(letter);
                used_letters.push_back(letter);
            }
            else {
                mistakes++;

            }
            //check for win
            if (mistakes > 7) {
                cout << "you are lose" << endl << "the word is " << word;
                return;
            }
            if (write == word) {
                cout << "congratulations, you are win";
                return;
            }
        }
    }
private:
    bool moove(char let) {
        for (int i = 0; i < word.length(); i++) {
            if (let == word[i]) {
                return true;
            }
        }
        return false;
    }
    void replace(char let) {
        int i = 0; 
        while (i < word.length()) {
            if (word[i] == let) {
                write[i] = word[i];
            }
            i++;
        }
    }

    void check() {
        if (mistakes > 8) {
            play = false;
        }
    }

};

int main()
{
    setlocale(LC_ALL, "Rus");

    //string formating
    My_string DeepXSense = "\tпламя на поленьях\n\tза то, что мы не стали на колени\n\tперед вашими богами на молельнях\n\tи\n\tвы сжигали поколения\n\tи гнали галлелеев и регалии лелеяли.\n\tМы восстали бы, но\n\tчто против тысячной стаи клинок,\n\tи елси ваш бог действительно есть,\n\tто он поможет мне стать купиной";
  //  cout << DeepXSense << endl;

    //viselitsa
    vis test("population");
    return 0;
}
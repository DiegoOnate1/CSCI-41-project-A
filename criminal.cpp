#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

struct CrimeRecord {
    string lurnsak;
    string incidentDate;
    string category;
    string city;
    bool gangRelated;
    string incidentId;
    string longitude;
    string latitude;
    string partCategory;

};

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;

}

static string toUpper(const string& s) {
    string result = s;
    for(int i = 0; i < (int)result.size(); i++ ) {
        result[i] = toupper((unsigned char)result[i]);

    }
    return result;
}




static bool interpretYesNo(const string& s) {
    return (s == "YES");
}


static int splitPipe(const string& line, string fields[], int maxFields) {
    int count = 0;
    string curr = "";

    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == '|') {
            if (count < maxFields) {
                fields[count] = curr;
            }
            count++;
            curr = "";
        } else {
            curr += line[i];
        }
    }

    if (count < maxFields) {
        fields[count] = curr;
    }
    count++;

    return count;
}




int main() {
    const string FILE_NAME = "record.txt";
    
    ifstream find(FILE_NAME.c_str());
    if (!find.is_open()) {
        cout << "sorry could not open file" << FILE_NAME;
        return 1;
    }

    int capacity = 30;
    int size = 0;
    CrimeRecord* records = new CrimeRecord[capacity];

    string line;

    if (!getline(find, line)) {
        cout << "sorry file is empty...";
        delete[] records;
        return 1;
    }

    while (getline(find, line)) {
        if (line.size() == 0) continue;

        const int maxFLD = 12;
        string f[maxFLD];
        int n = splitPipe(line, f, maxFLD);

        if (n < 9) continue;
        if (size >= capacity) break;

        records[size].lurnsak = f[0];
        records[size].incidentDate = f[1];
        records[size].category = f[2];
        records[size].city = f[3];
        records[size].gangRelated = interpretYesNo(f[4]);
        records[size].incidentId = f[5];
        records[size].longitude = f[6];
        records[size].latitude = f[7];
        records[size].partCategory = f[8];
        size++;
    }
    find.close();



    string searchCity = toUpper(readLine("Enter city in Los Angeles county to search: "));

    if (searchCity.size() == 0) {
        cout << "Did not enter city" << endl;
        delete[] records;
        return 0;
    }

    int matches = 0;

    cout << "Crime records in " << searchCity;

    for(int i = 0; i < size; i++) {
        if (records[i].city == searchCity) {
            cout << records[i].incidentId << "|" 
               << records[i].incidentDate << "|"
               << records[i].category << "|"
               << records[i].city << "| Gang: "
               << (records[i].gangRelated ? "YES" : "NO") <<"\n";

            matches++;
        }
    }

    cout <<"Matches found: " << matches << "\n";

    delete[] records;
    return 0;


}
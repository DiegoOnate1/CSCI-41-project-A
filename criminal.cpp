#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct CrimeRecord {
    string lurnsak;
    string incidentDate;
    string category;
    string city;
    bool gangRelated;
    string incidentId;
    string longitude;
    stirng latitude;
    string partCategory;

};

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;

}

static bool interpret(const string& s) {
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
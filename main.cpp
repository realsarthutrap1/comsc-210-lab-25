// COMSC-210 | Lab 25 | Sarthak Pani
// adapted from the instructor race starter and chrono demo

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;

struct RaceResult {
    string operation;
    long long vector_time;
    long long list_time;
    long long set_time;
};

template <typename Container>
long long read_codes(Container& codes, const string& filename);
void print_results(const vector<RaceResult>& results);

int main() {
    vector<string> vector_codes;
    list<string> list_codes;
    set<string> set_codes;
    vector<RaceResult> results;

    try {
        RaceResult reading{"Reading", 0, 0, 0};
        reading.vector_time = read_codes(vector_codes, "codes.txt");
        reading.list_time = read_codes(list_codes, "codes.txt");
        reading.set_time = read_codes(set_codes, "codes.txt");
        results.push_back(reading);
        print_results(results);
    } catch (const runtime_error& error) {
        cerr << error.what() << endl;
        return 1;
    }

    return 0;
}

template <typename Container>
long long read_codes(Container& codes, const string& filename) {
    ifstream input(filename);
    if (!input)
        throw runtime_error("Could not open " + filename);

    // each contestant reads the file with its own stopwatch
    string code;
    auto start = steady_clock::now();
    while (input >> code)
        codes.insert(codes.end(), code);
    auto end = steady_clock::now();

    if (input.bad() || !input.eof())
        throw runtime_error("Could not finish reading " + filename);
    if (codes.empty())
        throw runtime_error("No codes found in " + filename);

    return duration_cast<nanoseconds>(end - start).count();
}

void print_results(const vector<RaceResult>& results) {
    cout << "Data structure races (nanoseconds)\n";
    cout << left << setw(16) << "Operation" << right
         << setw(16) << "Vector" << setw(16) << "List" << setw(16) << "Set" << endl;
    for (const RaceResult& result : results) {
        cout << left << setw(16) << result.operation << right
             << setw(16) << result.vector_time << setw(16) << result.list_time
             << setw(16) << result.set_time << endl;
    }
}

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

struct process {
    string name;
    int priority;
    int burst_time;

    process(string name, int priority, int burst_time) : name(std::move(name)), priority(priority), burst_time(burst_time) {};
};

vector<process> read_tasks(const string& filename) {
    vector<process> tasks;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return tasks;
    }
    string line;
    while (getline(file, line)) {
        string name;
        int priority, burst_time;
        size_t comma_pos = line.find(',');
        if (comma_pos == string::npos) {
            cerr << "Error: Invalid line format (missing comma).\n";
            continue;
        }
        name = line.substr(0, comma_pos);
        size_t next_comma_pos = line.find(',', comma_pos + 1);
        if (next_comma_pos == string::npos) {
            cerr << "Error: Invalid line format (missing second comma).\n";
            continue;
        }
        priority = stoi(line.substr(comma_pos + 1, next_comma_pos - comma_pos - 1));
        burst_time = stoi(line.substr(next_comma_pos + 1));
        tasks.push_back(process(name, priority, burst_time));
    }
    file.close();
    return tasks;
}

void print_processes(vector<process> &processes) {
    for (const auto &p : processes) {
        cout << p.name << " " << p.priority << " " << p.burst_time << endl;
    }
}

void sortby(vector<process> &processes, const string& sortby) {
    if (sortby == "SJF"){
        sort(processes.begin(), processes.end(), [](const process &a, const process &b) {
            if (a.burst_time == b.burst_time)
                return a.name < b.name;
            return a.burst_time < b.burst_time;
        });
    }
    else if (sortby == "Priority"){
        sort(processes.begin(), processes.end(), [](const process &a, const process &b) {
            if (a.priority == b.priority)
                return a.name < b.name;
            return a.priority > b.priority;
        });
    }
    else if (sortby == "Priority RR"){
        sort(processes.begin(), processes.end(), [](const process &a, const process &b) {
            if (a.priority == b.priority)
                return a.name < b.name;
            return a.priority > b.priority;
        });
    } else {
        sort(processes.begin(), processes.end(), [](const process &a, const process &b) {
            return a.name < b.name;
        });
    }
}

void FCFS(vector<process> &processes) {
    int time = 0;
    for (const auto &p : processes) {
        cout << p.name << " " << time << " " << time + p.burst_time << endl;
        time += p.burst_time;
    }
}

void SJF(vector<process> &processes) {
    int time = 0;
    for (const auto &p : processes) {
        cout << p.name << " " << time << " " << time + p.burst_time << endl;
        time += p.burst_time;
    }
}

void Priority(vector<process> &processes) {
    int time = 0;
    for (const auto &p : processes) {
        cout << p.name << " " << time << " " << time + p.burst_time << endl;
        time += p.burst_time;
    }
}

void RR(vector<process> &processes, int quantum) {
    int time = 0;
    queue<process> q;
    for (const auto &p : processes) {
        q.push(p);
    }
    while (!q.empty()) {
        process p = q.front();
        q.pop();
        if (p.burst_time > quantum) {
            cout << p.name << " " << time << " " << time + quantum << endl;
            p.burst_time -= quantum;
            time += quantum;
            q.push(p);
        } else {
            cout << "* " << p.name << " " << time << " " << time + p.burst_time << endl;
            time += quantum;
        }
    }
}

void PriorityRR(vector<process> &processes, int quantum) {
    int time = 0;
    queue<process> q;
    for (const auto &p : processes) {
        q.push(p);
    }
    while (!q.empty()) {
        process p = q.front();
        q.pop();
        if (p.burst_time > quantum) {
            cout << p.name << " " << time << " " << time + quantum << endl;
            p.burst_time -= quantum;
            time += quantum;
            q.push(p);
        } else {
            cout << "* " << p.name << " " << time << " " << time + p.burst_time << endl;
            time += quantum;
        }
    }
}

int main() {
    const string filename = "/Users/davidjiang/Spring24/OS/Program1/schedule.txt";
    const int quantum = 10;

    vector<process> task = read_tasks(filename);
    cout << "Tasks: " << endl;
    print_processes(task);

    cout << "FCFS: " << endl;
    sortby(task, "FCFS");
    FCFS(task);

    cout << "SJF: " << endl;
    sortby(task, "SJF");
    SJF(task);

    cout << "Priority: " << endl;
    sortby(task, "Priority");
    Priority(task);

    cout << "RR: " << endl;
    sortby(task, "RR");
    RR(task, quantum);

    cout << "Priority RR: " << endl;
    sortby(task, "Priority RR");
    PriorityRR(task, quantum);

    return 0;
}

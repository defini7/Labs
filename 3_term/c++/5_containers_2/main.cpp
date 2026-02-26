// Task 11

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <fstream>
#include <optional>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

optional<vector<vector<string>>> read_table(const string_view path) {
  ifstream file(path.data());

  if (!file.is_open()) {
    return nullopt;
  }

  vector<vector<string>> rows;
  string line;

  while (getline(file, line)) {
    vector<string> cols;
    istringstream iss(line);
    string cell;

    while (getline(iss, cell, ';'))
      cols.push_back(cell);

    rows.push_back(move(cols));
  }

  return rows;
}

using Table = unordered_map<int, unordered_map<string, int>>;

optional<Table> parse_table(const string_view filename) {
  const auto content_opt = read_table(filename);

  if (!content_opt) {
    return nullopt;
  }

  const auto content = *content_opt;

  Table buy_list, available, demand;

  auto parse_table = [&](Table& table, int start_col = 0) {
    int col;

    for (col = 1 + start_col; col < content.size() && content[col][0] != ""; col++) {
      for (int row = 1; row < content[col].size(); row++) {
        table[stoi(content[0][row])][content[col][0]] = stoi(content[col][row]);
      }
    }

    return col;
  };

  parse_table(demand, parse_table(available) + 1);

  for (auto& [room, furniture] : available) {
    for (auto& [name, count] : furniture) {
      buy_list[room][name] = max(demand[room][name] - count, 0);
    }
  }

  return buy_list;
}

int main() {
  char c = 'n';

  do {
    string path;
    stringstream out;

    cout << "Enter a path to a file: ";
    cin >> path;

    if (auto buy_list = parse_table(path)) {
      for (const auto& [room, furniture] : *buy_list) {
        cout << "Room " << room << ": " << endl;
        out << "Room " << room << ": " << endl;

        for (const auto& [name, count] : furniture) {
          cout << "\t" << name << ": " << count << endl;
          out << "\t" << name << ": " << count << endl;
        }
      }

      int room;
      string furniture_title;

      cout << "Enter a room: ";
      cin >> room;

      cout << "Enter a furniture title: ";
      cin >> furniture_title;

      if (!buy_list->contains(room) || !(*buy_list)[room].contains(furniture_title)) {
        cout << "No such room or no such furniture in it" << endl;
      } else {
        cout << "You need to buy" << (*buy_list)[room][furniture_title] << ' ' << furniture_title << "s" << endl;
      }

      cout << "\nWould you like to save everything to a file (y/n)? ";
      cin >> c;

      if (c == 'y' || c == 'Y') {
        ofstream file("out.txt");
        file << out.rdbuf();
      }
    }

    cout << "Would you like to rerun the program (y/n)? ";
    cin >> c;
  } while (c == 'y' || c == 'Y');
}

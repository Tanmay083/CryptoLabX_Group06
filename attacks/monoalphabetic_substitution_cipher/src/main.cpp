#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

string key = "QWERTYUIOPASDFGHJKLZXCVBNM";
string revkey = "??????????????????????????";

string encrypt(string s) {
  string ans = "";

  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= 'A' && s[i] <= 'Z')
      ans += key[s[i] - 'A'];
    else if (s[i] >= 'a' && s[i] <= 'z')
      ans += tolower(key[toupper(s[i]) - 'A']);
    else
      ans += s[i];
  }

  return ans;
}

void frequency_analysis(string s) {
  int freq[26] = {0};
  int total = 0;

  for (int i = 0; i < s.length(); i++) {
    char c = toupper(s[i]);

    if (c >= 'A' && c <= 'Z') {
      freq[c - 'A']++;
      total++;
    }
  }

  vector<pair<char, int>> v;

  for (int i = 0; i < 26; i++)
    v.push_back({char('A' + i), freq[i]});

  sort(v.begin(), v.end(), [](auto a, auto b) { return a.second > b.second; });

  cout << "\nLETTER FREQUENCY ANALYSIS\n";

  for (int i = 0; i < 26; i++) {
    double p = 0;

    if (total > 0)
      p = (freq[v[i].first - 'A'] * 100.0) / total;

    cout << v[i].first << " " << v[i].second << " " << fixed << setprecision(2)
         << p << "%\n";
  }

  cout << "\nMost frequent letters:\n";

  for (int i = 0; i < 5; i++) {
    if (v[i].second > 0)
      cout << v[i].first << " -> " << v[i].second << "\n";
  }
}

void word_frequency_analysis(string s) {
  map<string, int> mp;
  string word = "";

  for (int i = 0; i <= s.length(); i++) {
    char c;

    if (i < s.length())
      c = s[i];
    else
      c = ' ';

    if (isalpha(c))
      word += toupper(c);
    else {
      if (word != "") {
        mp[word]++;
        word = "";
      }
    }
  }

  cout << "\nWORD FREQUENCY ANALYSIS\n";

  cout << "\nOne-letter words:\n";

  for (auto x : mp) {
    if (x.first.length() == 1)
      cout << x.first << " -> " << x.second << "\n";
  }

  cout << "\nTwo-letter words:\n";

  for (auto x : mp) {
    if (x.first.length() == 2)
      cout << x.first << " -> " << x.second << "\n";
  }

  cout << "\nThree-letter words:\n";

  for (auto x : mp) {
    if (x.first.length() == 3)
      cout << x.first << " -> " << x.second << "\n";
  }

  cout << "\nRepeated words:\n";

  for (auto x : mp) {
    if (x.second > 1)
      cout << x.first << " -> " << x.second << "\n";
  }
}

string get_pattern(string s) {
  int mp[26];

  for (int i = 0; i < 26; i++)
    mp[i] = -1;

  int x = 0;
  string ans = "";

  for (int i = 0; i < s.length(); i++) {
    int id = s[i] - 'A';

    if (mp[id] == -1)
      mp[id] = x++;

    ans += char('0' + mp[id]);
  }

  return ans;
}

void pattern_analysis(string s) {
  map<string, vector<string>> mp;
  string word = "";

  for (int i = 0; i <= s.length(); i++) {
    char c;

    if (i < s.length())
      c = s[i];
    else
      c = ' ';

    if (isalpha(c))
      word += toupper(c);
    else {
      if (word != "") {
        string p = get_pattern(word);
        mp[p].push_back(word);
        word = "";
      }
    }
  }

  cout << "\nPATTERN ANALYSIS\n";

  for (auto x : mp) {
    cout << x.first << " : ";

    for (int i = 0; i < x.second.size(); i++) {
      cout << x.second[i];

      if (i + 1 < x.second.size())
        cout << ",";
    }

    cout << "\n";
  }
}

string apply_substitution(string s) {
  string ans = "";

  for (int i = 0; i < s.length(); i++) {
    char c = s[i];

    if (c >= 'A' && c <= 'Z') {
      if (revkey[c - 'A'] != '?')
        ans += revkey[c - 'A'];
      else
        ans += '_';
    } else if (c >= 'a' && c <= 'z') {
      char x = toupper(c);

      if (revkey[x - 'A'] != '?')
        ans += tolower(revkey[x - 'A']);
      else
        ans += '_';
    } else
      ans += c;
  }

  return ans;
}

void display_partial_plaintext(string s) {
  cout << "\nPARTIAL PLAINTEXT\n";
  cout << apply_substitution(s) << "\n";
}

bool add_substitution(char c, char p) {
  c = toupper(c);
  p = toupper(p);

  if (c < 'A' || c > 'Z' || p < 'A' || p > 'Z')
    return false;

  int x = c - 'A';

  if (revkey[x] != '?') {
    if (revkey[x] == p)
      return true;

    return false;
  }

  for (int i = 0; i < 26; i++) {
    if (revkey[i] == p)
      return false;
  }

  revkey[x] = p;

  return true;
}

void display_key() {
  cout << "\nRECOVERED KEY\n";

  cout << "Cipher : ";

  for (int i = 0; i < 26; i++)
    cout << char('A' + i) << " ";

  cout << "\nPlain  : ";

  for (int i = 0; i < 26; i++)
    cout << revkey[i] << " ";

  cout << "\n";
}

bool verify_solution(string plain, string cipher) {
  string recoveredKey = "??????????????????????????";

  for (int i = 0; i < 26; i++) {
    if (revkey[i] != '?')
      recoveredKey[revkey[i] - 'A'] = char('A' + i);
  }

  string s = "";

  for (int i = 0; i < plain.length(); i++) {
    char c = plain[i];

    if (c >= 'A' && c <= 'Z')
      s += recoveredKey[c - 'A'];
    else if (c >= 'a' && c <= 'z')
      s += tolower(recoveredKey[toupper(c) - 'A']);
    else
      s += c;
  }

  if (s == cipher) {
    cout << "\nVERIFICATION SUCCESSFUL\n";
    return true;
  }

  cout << "\nVERIFICATION FAILED\n";
  return false;
}

int main() {

  ifstream file("../inputs/plaintext.txt");

  if (!file) {
    cout << "Unable to open plaintext.txt\n";
    return 0;
  }

  string plain = "";
  string line;

  while (getline(file, line)) {
    plain += line;
    plain += '\n';
  }

  file.close();

  string cipher = encrypt(plain);

  cout << "\nCIPHERTEXT:\n";
  cout << cipher << "\n";

  frequency_analysis(cipher);

  word_frequency_analysis(cipher);

  pattern_analysis(cipher);

  cout << "\nCRYPTANALYSIS\n";

  while (true) {

    cout << "\nEnter substitution or DONE: ";

    getline(cin, line);

    if (line == "DONE")
      break;

    if (line.length() >= 3) {

      char c = line[0];
      char p = line[2];

      if (add_substitution(c, p)) {
        cout << c << " -> " << p << "\n";
        display_partial_plaintext(cipher);
      } else {
        cout << "Invalid or conflicting substitution\n";
      }
    }
  }

  cout << "\nFINAL PLAINTEXT:\n";
  cout << apply_substitution(cipher) << "\n";

  display_key();

  verify_solution(plain, cipher);

  return 0;
}
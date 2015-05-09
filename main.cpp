#include <iostream>
#include <cmath>
#include <cassert>
#include <set>
using namespace std;

// '.' -> 1, 'x' -> 0
#define CHAR_TO_BIT(x) ((x % 4) == 2)
#define THREE(x, y) ((x >> (y*3)) % 8)
#define AT(x, y) (x << (y*3))
#define FIRST_CUBE(x) (AT(THREE(x, 0), 0) | AT(THREE(x, 1), 1) | AT(THREE(x, 2), 2))
#define SECOND_CUBE(x) (AT(THREE(x, 1), 0) | AT(THREE(x, 2), 1) | AT(THREE(x, 3), 2))
#define THIRD_CUBE(x) (AT(THREE(x, 2), 0) | AT(THREE(x, 3), 1) | AT(THREE(x, 4), 2))

string three_str(int x) {
  string ret = "";
  for (int i = 14; i >= 0; --i) {
    ret += '0' + ((x >> i) % 2);
  }
  return ret;
}

int size, modulo;
set<int> forbidden_configurations;
void read_data() {
  int forbidden_configurations_size;
  cin >> size >> forbidden_configurations_size >> modulo;
  char line[10];
  /*
   * 0 1 2
   * 3 4 5
   * 6 7 8
   * ->
   *  0 3 6 | 1 4 7 | 2 5 8
   *
   */
  cin.getline(line, 9); //Trash..
  for (int i = 0; i < forbidden_configurations_size; ++i)
  {
    for (int j = 0; j < 3; ++j) {
      cin.getline(line + j*3, 4);
    }
    line[9] = 0;
    int forbidden_configuration = 0;
    forbidden_configuration += CHAR_TO_BIT(line[0]) << 8;
    forbidden_configuration += CHAR_TO_BIT(line[3]) << 7;
    forbidden_configuration += CHAR_TO_BIT(line[6]) << 6;
    forbidden_configuration += CHAR_TO_BIT(line[1]) << 5;
    forbidden_configuration += CHAR_TO_BIT(line[4]) << 4;
    forbidden_configuration += CHAR_TO_BIT(line[7]) << 3;
    forbidden_configuration += CHAR_TO_BIT(line[2]) << 2;
    forbidden_configuration += CHAR_TO_BIT(line[5]) << 1;
    forbidden_configuration += CHAR_TO_BIT(line[8]);
    forbidden_configurations.insert(forbidden_configuration);
    cout << forbidden_configuration << " is forbidden (" << line << ")" << endl;
    cout << three_str(forbidden_configuration) << endl;
  }
}

bool forbidden(int configuration) {
  int count_first = forbidden_configurations.count(FIRST_CUBE(configuration));
  int count_second = forbidden_configurations.count(SECOND_CUBE(configuration));
  int count_third = forbidden_configurations.count(THIRD_CUBE(configuration));
  int count = count_first + count_second + count_third;
  /*
  if(count != 0) {
    cout << "Forbidden: " << configuration << endl;
  }
  if(count_first != 0) {
    cout << "1st: " << FIRST_CUBE(configuration) << "(" << count_first << ")" << endl;
  }
  if(count_second != 0) {
    cout << "2nd: " << SECOND_CUBE(configuration) << "(" << count_second << ")" << endl;
  }
  if(count_third != 0) {
    cout << "3rd: " << THIRD_CUBE(configuration) << "(" << count_third << ")" << endl;
  }
  */
  return count != 0;
}

#define CONFIGURATION_COUNT (1024u)
int data0[CONFIGURATION_COUNT];
int data1[CONFIGURATION_COUNT];
int* datas[2] = { data0, data1 };

int* step_data(int step) {
  const int *source;
  int *target;
  step = step % 2;
  source = datas[step];
  target = datas[1 - step];

  for(unsigned int j=0; j < CONFIGURATION_COUNT; ++j) {
    target[j] = 0;
    for(unsigned int i=0; i < 32u; ++i) {
      // | i (5 bits) | j (10 bits) |
      // |    edcba   |  9876543210 |
      int configuration = (i << 10) | j;
      // | i (5 bits) | j (5 bits)  |
      // |    edcba   |   98765     |
      int count = source[(i << 5) | (j >> 5)];
      if( (count > 0) && (!forbidden(configuration))) {
        target[j] += count;
        target[j] %= modulo;
      }
//      cout << three_str(configuration) << endl;
    }
  }
  return target;
}

int sum_all(int* target) {
  int sum = 0;
  for (unsigned int i = 0; i < CONFIGURATION_COUNT; ++i) {
    sum += target[i];
    sum %= modulo;
  }
  return sum;
}

int crunch_data() {
  int *target = datas[0];
  for (unsigned int i = 0; i < CONFIGURATION_COUNT; ++i) {
    target[i] = 1;
  }
  for (int i = 2; i < size; ++i) {
    target = step_data(i);
    cout << "(" << i << "): " << sum_all(target) << endl;
  }
  return sum_all(target);
}

int main()
{
  ios_base::sync_with_stdio(false);
  read_data();
  cout << crunch_data() << endl;
}

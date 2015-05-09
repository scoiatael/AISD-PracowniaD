#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;

#define AT(x, y) (x << y)
// '.' -> 0, 'x' -> 1
#define CHAR_TO_BIT(x) ((x % 4) != 2)
#define THREE(x, y) ((x >> y) % 8)
#define TWO(x, y) ((x >> y) % 4)
#define ONE(x, y) ((x >> y) % 2)

// Offsets
// e 9 4
// d 8 3
// c 7 2
// b 6 1
// a 5 0

/* x = 876 543 210
 * y = 543 210
 * z = edc ba9 876 543 210
 */

/*
 * x8 x5 x2
 * x7 x4 x1
 * x6 x3 x0
 * y5 y3 y1
 * y4 y2 y0
 */
//                          e d c               b a                 9 8 7             6 5               4 3 2             1 0
// FIRST_CUBE(x, y) ->      x8x7x6              y5y4                x5x4x3            y3y2              x2x1x0            y1y0
#define FIRST_CUBE(x, y) (AT(THREE(x, 6), 0xC)|AT(TWO(y, 4), 0xA)|AT(THREE(x, 3), 7)|AT(TWO(y, 2), 5)|AT(THREE(x, 0), 2)|AT(TWO(y, 0), 0))

/*
 * y5 y3 y1
 * x8 x5 x2
 * x7 x4 x1
 * x6 x3 x0
 * y4 y2 y0
 */
//                            e                 d c b                 a 9             8 7 6               5 4             3 2 1               0
// SECOND_CUBE(x, y) ->       y5                x8x7x6                y4y3            x5x4x3              y2y1            x2x1x0              y0
#define SECOND_CUBE(x, y) (AT(ONE(y, 5), 0xE)|AT(THREE(x, 6), 0xB)|AT(TWO(y, 3), 9)|AT(THREE(x, 3), 6)|AT(TWO(y, 1), 4)|AT(THREE(x, 0), 1)|AT(ONE(y, 0), 0))

/*
 * y5 y3 y1
 * y4 y2 y0
 * x8 x5 x2
 * x7 x4 x1
 * x6 x3 x0
 */
//                          e d                 c b a               9 8             7 6 5               4 3               2 1 0
// THIRD_CUBE(x, y) ->      y5y4                x8x7x6              y3y2            x5x4x3              y1y0              x2x1x0
#define THIRD_CUBE(x, y) (AT(TWO(y, 4), 0xD)|AT(THREE(x, 6), 0xA)|AT(TWO(y, 2), 8)|AT(THREE(x, 3), 5)|AT(TWO(y, 0), 3)|AT(THREE(x, 0), 0))

string three_str(int x, bool break_lines) {
  string ret = "";
  for (int i = 14; i >= 0; --i) {
    ret += '0' + ((x >> i) % 2);
    if(break_lines && (i % 3 == 0)) {
      ret += "\n";
    }
  }
  return ret;
}

int size, modulo;
vector<bool> forbidden_configurations(1024u*32u, false);

void read_data() {
  int forbidden_configurations_size;
  cin >> size >> forbidden_configurations_size >> modulo;
  char line[10];
  /*
   * 0 1 2
   * 3 4 5
   * 6 7 8
   * -----
   * a b c
   * d e f
   * ->
   *  0 3 6 | 1 4 7 | 2 5 8
   */
  cin.getline(line, 9); //Trash..
  for (int i = 0; i < forbidden_configurations_size; ++i)
  {
    for (int j = 0; j < 3; ++j) {
      cin.getline(line + j*3, 4);
    }
    line[9] = 0;
    unsigned int forbidden_configuration = 0;
    forbidden_configuration += CHAR_TO_BIT(line[0]) << 8;
    forbidden_configuration += CHAR_TO_BIT(line[3]) << 7;
    forbidden_configuration += CHAR_TO_BIT(line[6]) << 6;
    forbidden_configuration += CHAR_TO_BIT(line[1]) << 5;
    forbidden_configuration += CHAR_TO_BIT(line[4]) << 4;
    forbidden_configuration += CHAR_TO_BIT(line[7]) << 3;
    forbidden_configuration += CHAR_TO_BIT(line[2]) << 2;
    forbidden_configuration += CHAR_TO_BIT(line[5]) << 1;
    forbidden_configuration += CHAR_TO_BIT(line[8]);
    for (unsigned int j = 0; j < 64u; ++j)
    {
      forbidden_configurations[FIRST_CUBE(forbidden_configuration, j)] = true;
      forbidden_configurations[SECOND_CUBE(forbidden_configuration, j)] = true;
      forbidden_configurations[THIRD_CUBE(forbidden_configuration, j)] = true;
    }
//    cout << forbidden_configuration << " is forbidden" << endl;
    /*
    for (int i = 8; i >= 0; --i) {
      cout << line[i];
      if((i % 3) == 0) {
        cout << endl;
      }
    }
    cout << three_str(forbidden_configuration, true) << endl;
    */
  }
}

bool forbidden(int configuration) {
  /*
  int count = forbidden_configurations.count(configuration);
  cout << "[" << configuration <<((count == 0) ? "✓" : "✕") << "]";
  if(count_first != 0) {
    cout << " 1st: " << FIRST_CUBE(configuration) << "(" << count_first << ")" << endl;
  }
  if(count_second != 0) {
    cout << " 2nd: " << SECOND_CUBE(configuration) << "(" << count_second << ")" << endl;
  }
  if(count_third != 0) {
    cout << " 3rd: " << THIRD_CUBE(configuration) << "(" << count_third << ")" << endl;
  }
  */
  return forbidden_configurations[configuration];
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
//    cout << j << " : ";
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
//      cout << three_str(configuration, false) << endl;
    }
//    cout << target[j] << endl;
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
 //   cout << "(" << i << "): " << sum_all(target) << endl;
  }
  return sum_all(target);
}

int main()
{
  ios_base::sync_with_stdio(false);
  read_data();
  cout << crunch_data() << endl;
}

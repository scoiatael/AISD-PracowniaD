#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int num, modulo;
// x/1 -> black, ./0 -> white
vector<string> wrong_patterns;
vector<string> list_of_all_patterns(32);
vector<vector< vector<int> > > list_of(32, vector<vector <int> >(32, vector<int>(2,1)));

char pos[3] = ".x";

// Define how looks every possible row
void define_patterns(){
  int iter = 0;
  for(int i=0; i<2; ++i){
    for(int j=0; j<2; ++j){
      for(int k=0; k<2; ++k){
        for(int l=0; l<2; ++l){
          for(int m=0; m<2; ++m){
            char permutation[6] = { pos[i], pos[j], pos[k], pos[l], pos[m] };
            list_of_all_patterns[iter] = permutation;
            ++iter;
          }
        }
      }
    }
  }
}

int binary(string str) {
  int s = 0;
  for (unsigned int i = 0; i < str.length(); ++i) {
    s = s << 1;
    s += (str[i] == 'x') ? 1 : 0;
  }
  return s;
}

//Generate any possible wrong pattern
void handle_pattern(){
  char buf[10] = "012345678";
  /* 0 3 6
   * 1 4 7
   * 2 5 8
   */
  scanf("%s%s%s", &buf[0], &buf[3], &buf[6]);
  char pat[10];
  pat[0] = buf[0];
  pat[1] = buf[3];
  pat[2] = buf[6];
  pat[3] = buf[1];
  pat[4] = buf[4];
  pat[5] = buf[7];
  pat[6] = buf[2];
  pat[7] = buf[5];
  pat[8] = buf[8];


  // create all permutation 5x3 with wrong pattern!
  for(int i=0; i<2; ++i){
    for(int j=0; j<2; ++j){
      for(int k=0; k<2; ++k){
        for(int l=0; l<2; ++l){
          for(int m=0; m<2; ++m){
            for(int n=0; n<2; ++n){
              char forbidden_pattern[3][16] = {
              { pat[0], pat[1], pat[2], pos[i], pos[j], pat[3], pat[4], pat[5], pos[k], pos[l], pat[6], pat[7], pat[8], pos[m], pos[n]},
              { pos[i], pat[0], pat[1], pat[2], pos[j], pos[k], pat[3], pat[4], pat[5], pos[l], pos[m], pat[6], pat[7], pat[8], pos[n]},
              { pos[i], pos[j], pat[0], pat[1], pat[2], pos[k], pos[l], pat[3], pat[4], pat[5], pos[m], pos[n], pat[6], pat[7], pat[8]}
              };
              for (int o = 0; o < 3; ++o) {
                wrong_patterns.push_back(forbidden_pattern[o]);
              }
            }
          }
        }
      }
    }
  }
  sort(wrong_patterns.begin(), wrong_patterns.end());
}

//Check how many is permutation which ends on rows drugi trzeci
int ends_with(int drugi, int trzeci, int n){
  printf("%d : ", (drugi * 32 + trzeci));
  int wynik = 0;
  for(int i=0; i<32; ++i){
    string merged_rows = list_of_all_patterns[i] + list_of_all_patterns[drugi] + list_of_all_patterns[trzeci];
    if(!binary_search(wrong_patterns.begin(), wrong_patterns.end(), merged_rows)){
      wynik += list_of[i][drugi][n];
      printf("[%d✓]", binary(merged_rows));
    } else {
      printf("[%d✕]", binary(merged_rows));
    }
  }
  printf("%d\n", wynik);
  return wynik;
}

void display_for(int num){
  int wynik = 0;
  int mods = num % 2;
  for(int i=0; i<32; ++i){
    for(int j=0; j<32; ++j){
      wynik += list_of[i][j][mods];
      wynik %= modulo;
    }
  }
  printf("%d\n", wynik);
}

void calculate_result(){
  for(int iter=3; iter<=num; ++iter){
    int modul = iter % 2;
    for(int drugi=0; drugi<32; ++drugi){
      for(int trzeci=0; trzeci<32; ++trzeci){
        list_of[drugi][trzeci][modul] = ends_with(drugi, trzeci, 1-modul) % modulo;
      }
    }
    printf("(%d): ", iter-1);
    display_for(iter);
  }
}

//Get input
void get_numbers_and_patterns(){
  int patterns;
  scanf("%d %d %d", &num, &patterns, &modulo);
  for(int i=0; i < patterns; ++i){
    handle_pattern();
  }
}

//main function
int main(){
  define_patterns();
  get_numbers_and_patterns();
  calculate_result();
  display_for(num);
  return 0;
}


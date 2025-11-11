#include <iostream>
using namespace std;

// void gaussjordaninverse(int row, int column, int matrix[row][column]){
//     int augmented[row][2*column];
//     for(int i = 0; i<row; i++){
//         for(int j = 0; j<column; j++){
//             augmented[i][j]=matrix[row][column];
//         }
//     }
//     for(int i=0; i<row; ++i){
//         for(int j = 0; j<2*column; ++j){
//             cout << augmented[i][j] << "\t";
//         }
//         cout << endl;
//     }
// }

// void swapper(int matrix[][]; int row1; int row2) {}

int main() {
  int n;
  cout << "Enter the number of row in matrix.";
  cin >> n;
  int matrix[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << "Enter element at row " << i + 1 << ", column " << j + 1 << endl;
      cin >> matrix[i][j];
    }
  }
  cout << "Is this the matrix you wanna invert?(Enter to confirm)\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << matrix[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl << endl;

  /* --------------------------------------------------------
                     CREATING AUGMENTED MATRIX
  ---------------------------------------------------------*/
  int augmented[n][2 * n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      augmented[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = n; j < 2 * n; ++j) {
      if (i - j + n) {
        augmented[i][j] = 0;
      } else {
        augmented[i][j] = 1;
      }
    }
  }
  cout << "Augmented matrix: " << endl;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 2 * n; ++j) {
      cout << augmented[i][j] << "\t";
    }
    cout << endl;
  }

  /* --------------------------------------------------------
                         MANIPULATING
  ---------------------------------------------------------*/
  /*
  goes through each column, looks for zero pivot element, if exists, it looks
  for next non zero element in the same column and swap the row with it
  */
  for (int i = 0; i < n; ++i) {
    if (!augmented[i][i]) { // if diagonal = 0
      cout << "diagonal element at (" << i << ", " << i << ") is zero\n";
      int swapper = 0;
      int swapper_row;
      for (int r = i; r < n; r++) {
        if (augmented[r][i]) {
          swapper_row = r;
          swapper = augmented[r][i];
          break;
        }
      }
      if (!swapper) {
        cout << "Singular matrix detected, no inverse exist\n";
      }
      cout << "Swapper= " << swapper;
      if (swapper) {
        for (int c = 0; c < 2 * n; ++c) {
          int tempo = augmented[swapper_row][c];
          augmented[swapper_row][c]=augmented[i][c];
          augmented[i][c]=tempo;
        }
      }
    }
  }
}

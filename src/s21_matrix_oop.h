#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(const S21Matrix& matrix);
  S21Matrix(S21Matrix&& matrix) noexcept;
  explicit S21Matrix(const int rows, const int cols);
  ~S21Matrix() noexcept;

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(const int rows);
  void set_cols(const int cols);
  void PrintMatrix() const noexcept;

  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();
  S21Matrix Transpose() const noexcept;
  void SumMatrix(const S21Matrix& matrix);
  void SubMatrix(const S21Matrix& matrix);
  void MulMatrix(const S21Matrix& matrix);
  void MulNumber(const double number) noexcept;
  bool EqMatrix(const S21Matrix& matrix) const noexcept;

  S21Matrix& operator*=(const double number) noexcept;
  S21Matrix operator+(const S21Matrix& matrix) noexcept;
  S21Matrix operator-(const S21Matrix& matrix) noexcept;
  S21Matrix operator*(const S21Matrix& matrix) noexcept;
  S21Matrix& operator=(const S21Matrix& matrix) noexcept;
  S21Matrix& operator+=(const S21Matrix& matrix) noexcept;
  S21Matrix& operator-=(const S21Matrix& matrix) noexcept;
  S21Matrix& operator*=(const S21Matrix& matrix) noexcept;
  bool operator==(const S21Matrix& matrix) const noexcept;
  bool operator!=(const S21Matrix& matrix) const noexcept;
  double& operator()(const int row, const int col) const;
  friend S21Matrix operator*(S21Matrix& matrix, const double number) noexcept;
  friend S21Matrix operator*(const double number, S21Matrix& matrix) noexcept;

 protected:
  void MoveMatrix(const S21Matrix& matrix) noexcept;
  void CreateMatrix(const int rows, const int cols) noexcept;
  double DeterminantSearch(S21Matrix* A, int size) const noexcept;
  void SubOrSum(const S21Matrix& matrix, const bool is_sum) noexcept;
  void MinorSearch(double** A, double** buffer, int skip_i, int skip_j, int size) const noexcept;

 private:
  int rows_;
  int cols_;
  double** matrix_;
};

#endif  // SRC_S21_MATRIX_OOP_H_

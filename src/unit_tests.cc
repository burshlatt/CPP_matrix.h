#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(test_class, basic_constructor) {
  S21Matrix m;
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
}

TEST(test_class, rc_constructor) {
  S21Matrix m(69, 420);
  EXPECT_EQ(m.get_rows(), 69);
  EXPECT_EQ(m.get_cols(), 420);
}

TEST(test_class, copy_constructor) {
  S21Matrix m(12, 12);
  S21Matrix copy(m);

  EXPECT_EQ(copy.get_cols(), 12);
  EXPECT_EQ(copy.get_rows(), 12);
}

TEST(test_class, copy_constructor_empty) {
  S21Matrix m;
  EXPECT_ANY_THROW(S21Matrix copy(m));
}

TEST(test_class, move_constructor) {
  S21Matrix m(12, 12);
  S21Matrix moved(std::move(m));

  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
  EXPECT_EQ(moved.get_cols(), 12);
  EXPECT_EQ(moved.get_rows(), 12);
}

TEST(test_class, brackets_operator) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 69;
  EXPECT_EQ(m(0, 1), 69);

  m(5, 8) = 69.420;
  EXPECT_EQ(m(5, 8), 69.420);
}

TEST(test_setters, set_rows_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.set_rows(5);
  EXPECT_EQ(m.get_rows(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_setters, set_rows_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.set_rows(1);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_setters, set_rows_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.set_rows(0));
}

TEST(test_setters, set_cols_up) {
  S21Matrix m(2, 2);
  m(1, 1) = 6.9;

  m.set_cols(5);
  EXPECT_EQ(m.get_cols(), 5);
  EXPECT_EQ(m(1, 1), 6.9);
}

TEST(test_setters, set_cols_down) {
  S21Matrix m(2, 2);
  m(0, 0) = 6.9;

  m.set_cols(1);
  EXPECT_EQ(m.get_cols(), 1);
  EXPECT_EQ(m(0, 0), 6.9);
}

TEST(test_setters, set_cols_zero) {
  S21Matrix m;

  EXPECT_ANY_THROW(m.set_cols(0));
}

TEST(test_overload, equal_lvalue) {
  S21Matrix m(3, 6);
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  m = x;

  EXPECT_EQ(m.get_rows(), 3);
  EXPECT_EQ(m.get_cols(), 6);
  EXPECT_EQ(m(1, 2), 3);
  EXPECT_EQ(m(2, 2), 3);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  n = std::move(m);

  EXPECT_EQ(n.get_cols(), 2);
  EXPECT_EQ(n.get_rows(), 2);
}

TEST(test_functional, eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  ASSERT_TRUE(m == n);
}

TEST(test_functional, eq_matrix1) {
  S21Matrix m(3, 2);
  S21Matrix n;

  m(0, 1) = 69;
  n = m;

  ASSERT_TRUE(m == n);
}

TEST(test_functional, eq_matrix2) {
  S21Matrix m(3, 2);
  S21Matrix n(2, 3);

  m(0, 1) = 69;
  n(0, 1) = 69;

  ASSERT_TRUE(m != n);
}

TEST(test_functional, eq_matrix3) {
  S21Matrix m(3, 2);
  S21Matrix n(3, 2);

  m(0, 1) = 69;
  n(0, 1) = 96;

  ASSERT_TRUE(m != n);
}

TEST(test_functional, not_eq_matrix) {
  S21Matrix m(3, 2);
  S21Matrix n(3, 2);

  m(0, 1) = 69;
  n(0, 1) = 69;

  ASSERT_FALSE(m != n);
}

TEST(test_functional, index_operator) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(1, 1) = 1;

  EXPECT_ANY_THROW(m(5, 5));
}

TEST(test_functional, sum_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, sum_no_eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(3, 3);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  EXPECT_ANY_THROW(m.SumMatrix(n));
}


TEST(test_functional, add_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m + n;

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(test_functional, eqadd_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m += m + n;

  EXPECT_EQ(m(0, 0), 3);
  EXPECT_EQ(m(1, 1), 3);
}

TEST(test_functional, sub_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_no_eq_matrix) {
  S21Matrix m(2, 2);
  S21Matrix n(3, 3);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  EXPECT_ANY_THROW(m.SubMatrix(n));
}

TEST(test_functional, eqsub_overloaded_operator) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, sub_operator_overload) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(test_functional, mul_matrices) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  for (int i = 0, c = 7; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      n(i, j) = c++;
    }
  }

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_matrices1) {
  S21Matrix m(1, 1);
  S21Matrix n(2, 2);

  EXPECT_ANY_THROW(m.MulMatrix(n));
}

TEST(test_functional, eqmul_operator) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  for (int i = 0, c = 7; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      n(i, j) = c++;
    }
  }

  m *= n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, eqmul_operator_num) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  m *= 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(test_functional, mul_operator) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  for (int i = 0, c = 7; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      n(i, j) = c++;
    }
  }

  m = m * n;

  S21Matrix res(2, 2);
  res(0, 0) = 58;
  res(0, 1) = 64;
  res(1, 0) = 139;
  res(1, 1) = 154;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_operator_num1) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  m = 2 * m;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, mul_operator_num2) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m(i, j) = c++;
    }
  }

  m = m * 2;

  S21Matrix res(2, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;

  ASSERT_TRUE(m == res);
}

TEST(test_functional, transpose) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix res(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++, c++) {
      m(i, j) = c;
      res(j, i) = c;
    }
  }

  S21Matrix res_2 = m.Transpose();
  ASSERT_TRUE(res_2 == res);
}

TEST(test_functional, determinant) {
  S21Matrix m(2, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(test_functional, determinant_zero) {
  const int size = 5;
  S21Matrix m(5, 5);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      m(i, j) = j;
    }
  }
  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(test_functional, determinant_5x5) {
  int size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(test_functional, determinant_3x3) {
  const int size = 3;
  S21Matrix m(size, size);

  m(0, 0) = 2;
  m(0, 1) = 3;
  m(0, 2) = 1;
  m(1, 0) = 7;
  m(1, 1) = 4;
  m(1, 2) = 1;
  m(2, 0) = 9;
  m(2, 1) = -2;
  m(2, 2) = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(test_functional, determinant_2x2) {
  const int size = 2;
  S21Matrix m(size, size);

  m(0, 0) = -5;
  m(0, 1) = -4;
  m(1, 0) = -2;
  m(1, 1) = -3;

  double res = m.Determinant();
  ASSERT_NEAR(res, 7, 1e-6);
}

TEST(test_functional, complements_1x1) {
  S21Matrix matrix_1(1, 1);

  matrix_1(0, 0) = 1;

  S21Matrix res = matrix_1.CalcComplements();

  ASSERT_TRUE(res(0, 0) == 1);
}

TEST(test_functional, complements_3x3) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);

  matrix_2(0, 0) = 0;
  matrix_2(0, 1) = 10;
  matrix_2(0, 2) = -20;
  matrix_2(1, 0) = 4;
  matrix_2(1, 1) = -14;
  matrix_2(1, 2) = 8;
  matrix_2(2, 0) = -8;
  matrix_2(2, 1) = -2;
  matrix_2(2, 2) = 4;

  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(0, 2) = 3;
  matrix_1(1, 0) = 0;
  matrix_1(1, 1) = 4;
  matrix_1(1, 2) = 2;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = 2;
  matrix_1(2, 2) = 1;

  S21Matrix res = matrix_1.CalcComplements();

  ASSERT_TRUE(res == matrix_2);
}

TEST(test_functional, CalcComplements_throw) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(test_functional, complements_3x3_1) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);

  matrix_1(0, 0) = 1.0;
  matrix_1(0, 1) = 2.0;
  matrix_1(0, 2) = 3.0;
  matrix_1(1, 0) = 0.0;
  matrix_1(1, 1) = 4.0;
  matrix_1(1, 2) = 2.0;
  matrix_1(2, 0) = 5.0;
  matrix_1(2, 1) = 2.0;
  matrix_1(2, 2) = 1.0;

  matrix_2(0, 0) = 0.0;
  matrix_2(0, 1) = 10.0;
  matrix_2(0, 2) = -20.0;
  matrix_2(1, 0) = 4.0;
  matrix_2(1, 1) = -14.0;
  matrix_2(1, 2) = 8.0;
  matrix_2(2, 0) = -8.0;
  matrix_2(2, 1) = -2.0;
  matrix_2(2, 2) = 4.0;

  S21Matrix res = matrix_1.CalcComplements();

  ASSERT_TRUE(res == matrix_2);
}

TEST(test_class, zero_size) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(test_functional, complements_3x3_2) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix matrix_1(rows, cols);
  S21Matrix matrix_2(rows, cols);

  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(0, 2) = 3;
  matrix_1(1, 1) = 4;
  matrix_1(1, 2) = 2;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = 2;
  matrix_1(2, 2) = 1;

  matrix_2(0, 1) = 10;
  matrix_2(0, 2) = -20;
  matrix_2(1, 0) = 4;
  matrix_2(1, 1) = -14;
  matrix_2(1, 2) = 8;
  matrix_2(2, 0) = -8;
  matrix_2(2, 1) = -2;
  matrix_2(2, 2) = 4;

  S21Matrix res = matrix_1.CalcComplements();
  ASSERT_TRUE(res == matrix_2);
}

TEST(test_functional, inverese_3x3) {
  const int size = 3;
  S21Matrix matrix_1(size, size);
  S21Matrix matrix_2(size, size);

  matrix_2(0, 0) = 44300.0 / 367429.0;
  matrix_2(0, 1) = -236300.0 / 367429.0;
  matrix_2(0, 2) = 200360.0 / 367429.0;
  matrix_2(1, 0) = 20600.0 / 367429.0;
  matrix_2(1, 1) = 56000.0 / 367429.0;
  matrix_2(1, 2) = -156483.0 / 367429.0;
  matrix_2(2, 0) = 30900.0 / 367429.0;
  matrix_2(2, 1) = 84000.0 / 367429.0;
  matrix_2(2, 2) = -51010.0 / 367429.0;

  matrix_1(0, 0) = 2.8;
  matrix_1(0, 1) = 1.3;
  matrix_1(0, 2) = 7.01;
  matrix_1(1, 0) = -1.03;
  matrix_1(1, 1) = -2.3;
  matrix_1(1, 2) = 3.01;
  matrix_1(2, 0) = 0;
  matrix_1(2, 1) = -3;
  matrix_1(2, 2) = 2;

  ASSERT_TRUE(matrix_1.InverseMatrix() == matrix_2);
}

TEST(test_functional, inverese_3x3_1) {
  const int size = 3;
  S21Matrix matrix_1(size, size);
  S21Matrix matrix_2(size, size);
  matrix_2(0, 0) = 1.0;
  matrix_2(0, 1) = -1.0;
  matrix_2(0, 2) = 1.0;
  matrix_2(1, 0) = -38.0;
  matrix_2(1, 1) = 41.0;
  matrix_2(1, 2) = -34.0;
  matrix_2(2, 0) = 27.0;
  matrix_2(2, 1) = -29.0;
  matrix_2(2, 2) = 24.0;

  matrix_1(0, 0) = 2.0;
  matrix_1(0, 1) = 5.0;
  matrix_1(0, 2) = 7.0;
  matrix_1(1, 0) = 6.0;
  matrix_1(1, 1) = 3.0;
  matrix_1(1, 2) = 4.0;
  matrix_1(2, 0) = 5.0;
  matrix_1(2, 1) = -2.0;
  matrix_1(2, 2) = -3.0;

  ASSERT_TRUE(matrix_1.InverseMatrix() == matrix_2);
}

TEST(test_functional, inverse_throw) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(test_functional, inverse_1x1) {
  S21Matrix m(1, 1);
  m(0, 0) = 69.420;
  double matrix_2 = 1 / m(0, 0);
  double result = m.InverseMatrix()(0, 0);
  ASSERT_NEAR(matrix_2, result, 1e-06);
}

TEST(test_functional, inverese_3x3_2) {
  const int size = 3;
  S21Matrix matrix_1(size, size);
  S21Matrix matrix_2(size, size);

  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 5;
  matrix_1(0, 2) = 7;
  matrix_1(1, 0) = 6;
  matrix_1(1, 1) = 3;
  matrix_1(1, 2) = 4;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = -2;
  matrix_1(2, 2) = -3;

  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = -1;
  matrix_2(0, 2) = 1;
  matrix_2(1, 0) = -38;
  matrix_2(1, 1) = 41;
  matrix_2(1, 2) = -34;
  matrix_2(2, 0) = 27;
  matrix_2(2, 1) = -29;
  matrix_2(2, 2) = 24;
  ASSERT_TRUE(matrix_1.InverseMatrix() == matrix_2);
}

TEST(test_functional, inverese_3x3_3) {
  const int size = 3;
  S21Matrix matrix_1(size, size);
  S21Matrix matrix_2(size, size);

  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 5;
  matrix_1(0, 2) = 7;
  matrix_1(1, 0) = 6;
  matrix_1(1, 1) = 3;
  matrix_1(1, 2) = 4;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = -2;
  matrix_1(2, 2) = -3;

  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = -1;
  matrix_2(0, 2) = 1;
  matrix_2(1, 0) = -38;
  matrix_2(1, 1) = 41;
  matrix_2(1, 2) = -34;
  matrix_2(2, 0) = 27;
  matrix_2(2, 1) = -29;
  matrix_2(2, 2) = 24;
  ASSERT_TRUE(matrix_1.InverseMatrix() == matrix_2);
}

TEST(test_functional, brackets_const) {
  const S21Matrix m(3, 3);

  ASSERT_EQ(m(0, 0), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#pragma once
#include "OBJ_Loader.h"
#include "Vector2.hpp"
#include <cassert>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <math.h>

namespace raytracer {
class Vector4;
class Vector {
private:
  double _x, _y, _z;

public:
  // constructors
  Vector();
  Vector(int x, int y, int z);
  Vector(double x, double y, double z);
  Vector(objl::Vector3 vec);
  Vector(Vector4 vec);

  // accessors
  double x() const;
  double y() const;
  double z() const;
  float x_f() const;
  float y_f() const;
  float z_f() const;

  double length() const;
  double angle(const Vector &vector) const;
  bool orthogonal(const Vector &vec) const;
  bool parallel(const Vector &vec) const;
  Vector normalize() const;
  Vector cross(const Vector &vec) const;
  Vector2 project(int dim) const;
  Vector projectOnto(const Vector &vec) const;
  Vector reflect(const Vector &normal) const;

  friend Vector operator+(const Vector &lhs, const Vector &rhs);
  friend Vector operator-(const Vector &lhs, const Vector &rhs);
  friend Vector operator-(const Vector &op);
  friend double operator*(const Vector &lhs, const Vector &rhs);
  friend Vector operator*(const Vector &lhs, int length);
  friend Vector operator*(const Vector &lhs, float length);
  friend Vector operator*(const Vector &lhs, double length);
  friend Vector operator*(int length, const Vector &lhs);
  friend Vector operator*(float length, const Vector &lhs);
  friend Vector operator*(double length, const Vector &lhs);
  friend Vector operator/(const Vector &lhs, const Vector &rhs);
  friend bool operator==(const Vector &lhs, const Vector &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Vector point);
};

class Vector4 {
private:
  double m_x, m_y, m_z, m_t;

public:
  Vector4() = default;
  Vector4(float x, float y, float z, float t)
      : m_x{x}, m_y{y}, m_z{z}, m_t{t} {};
  Vector4(double x, double y, double z, double t)
      : m_x{x}, m_y{y}, m_z{z}, m_t{t} {};
  Vector4(const Vector &vec3)
      : m_x{vec3.x()}, m_y{vec3.y()}, m_z{vec3.z()}, m_t{1.0} {};
  Vector4(const Vector &vec3, double t)
      : m_x{vec3.x()}, m_y{vec3.y()}, m_z{vec3.z()}, m_t{t} {};
  double x() const;
  double y() const;
  double z() const;
  double t() const;
  double operator[](std::size_t idx) {
    assert(idx >= 0 && idx <= 3);
    if (idx == 0)
      return m_x;
    if (idx == 1)
      return m_y;
    if (idx == 2)
      return m_z;
    return m_t;
  }
  friend double operator*(const Vector4 &lhs, const Vector4 &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Vector4 point);
};

class Matrix {
private:
  std::vector<Vector4> m_rows;
  Vector4 row(int rowIdx) const;
  Vector4 column(int colIdx) const;

public:
  Matrix() = default;
  Matrix(std::vector<Vector4> rows) : m_rows{rows} {
    if (rows.size() != 4)
      throw std::invalid_argument{"Matrix must have 4 rows"};
  };
  std::vector<Vector4> rows() const { return std::vector<Vector4>(m_rows); };
  std::vector<Vector4> cols() const {
    auto col0 =
        Vector4{m_rows[0].x(), m_rows[1].x(), m_rows[2].x(), m_rows[3].x()};
    auto col1 =
        Vector4{m_rows[0].y(), m_rows[1].y(), m_rows[2].y(), m_rows[3].y()};
    auto col2 =
        Vector4{m_rows[0].z(), m_rows[1].z(), m_rows[2].z(), m_rows[3].z()};
    auto col3 =
        Vector4{m_rows[0].t(), m_rows[1].t(), m_rows[2].t(), m_rows[3].t()};
    return {col0, col1, col2, col3};
  }
  Vector4 apply(Vector4 &vec) const;
  Matrix apply(Matrix &matrix) const;
  Vector4 operator[](std::size_t idx) { return cols().at(idx); }
  friend std::ostream &operator<<(std::ostream &out, const Matrix matrix);
};

inline static Matrix unitMatrix(){
	auto x = Vector4{1., 0., 0., 0.};
	auto y = Vector4{0., 1., 0., 0.};
	auto z = Vector4{0., 0., 1., 0.};
	auto t = Vector4{0., 0., 0., 1.};
	return Matrix{{x, y, z, t}};
};

inline static Matrix scaleMatrix(double x, double y, double z){
	auto xRow = Vector4{x, 0., 0., 0.};
	auto yRow = Vector4{0., y, 0., 0.};
	auto zRow = Vector4{0., 0., z, 0.};
	auto tRow = Vector4{0., 0., 0., 1};
	return Matrix{{xRow, yRow, zRow, tRow}};
};

inline static Matrix rotXMatrix(double angle){
	angle = (angle * M_PI / 180.);
	auto xRow = Vector4{1, 0., 0., 0.};
	auto yRow = Vector4{0., cos(angle), -sin(angle), 0.};
	auto zRow = Vector4{0., sin(angle), cos(angle), 0.};
	auto tRow = Vector4{0., 0., 0., 1};
	return Matrix{{xRow, yRow, zRow, tRow}};
};

inline static Matrix rotYMatrix(double angle){
	angle = (angle * M_PI / 180.);
	auto xRow = Vector4{cos(angle), 0., sin(angle), 0.};
	auto yRow = Vector4{0., 1., 0., 0.};
	auto zRow = Vector4{-sin(angle), 0, cos(angle), 0.};
	auto tRow = Vector4{0., 0., 0., 1.};
	return Matrix{{xRow, yRow, zRow, tRow}};
};

inline static Matrix rotZMatrix(double angle){
	angle = (angle * M_PI / 180.);
	auto xRow = Vector4{cos(angle), -sin(angle), 0., 0.};
	auto yRow = Vector4{sin(angle), cos(angle), 0., 0.};
	auto zRow = Vector4{0., 0, 1., 0.};
	auto tRow = Vector4{0., 0., 0., 1};
	return Matrix{{xRow, yRow, zRow, tRow}};
};


inline static Matrix translationMatrix(double x, double y, double z){
	auto xRow = Vector4{1., 0., 0., x};
	auto yRow = Vector4{0., 1., 0., y};
	auto zRow = Vector4{0., 0., 1., z};
	auto tRow = Vector4{0., 0., 0., 1};
	return Matrix{{xRow, yRow, zRow, tRow}};
};
} // namespace raytracer

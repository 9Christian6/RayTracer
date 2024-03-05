#include "Vector.hpp"
#include "Exception.hpp"
#include "OBJ_Loader.h"

namespace raytracer {
static double PI = 3.14159265359;

Vector::Vector() : _x{0}, _y{0}, _z{0} {};
Vector::Vector(int x, int y, int z)
    : _x{(double)x}, _y{(double)y}, _z{(double)z} {};
Vector::Vector(double x, double y, double z) : _x{x}, _y{y}, _z{z} {};
Vector::Vector(objl::Vector3 vec) : _x{vec.X}, _y{vec.Y}, _z{vec.Z} {};
Vector::Vector(Vector4 vec) : _x{vec.x()}, _y{vec.y()}, _z{vec.z()} {};

double Vector::x() const { return _x; }

double Vector::y() const { return _y; }

double Vector::z() const { return _z; }

float Vector::x_f() const { return (float)_x; }

float Vector::y_f() const { return (float)_y; }

float Vector::z_f() const { return (float)_z; }

Vector operator+(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

Vector operator-(const Vector &op) { return Vector(-1 * op); }

double operator*(const Vector &lhs, const Vector &rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

Vector operator*(const Vector &lhs, int length) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(const Vector &lhs, float length) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(const Vector &lhs, double length) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(int length, const Vector &lhs) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(float length, const Vector &lhs) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator*(double length, const Vector &lhs) {
  return Vector(lhs.x() * length, lhs.y() * length, lhs.z() * length);
}

Vector operator/(const Vector &lhs, const Vector &rhs) {
  return Vector(lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z());
}

bool operator==(const Vector &lhs, const Vector &rhs) {
  return (lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z());
}

double Vector::length() const { return std::sqrt(_x * _x + _y * _y + _z * _z); }

double Vector::angle(const Vector &vec) const {
  double dot = *this * vec;
  double length = this->length() * vec.length();
  return std::acos(dot / length) * 180 / PI;
}

bool Vector::orthogonal(const Vector &vec) const {
  return ((*this) * vec) == 0;
}

Vector Vector::normalize() const {
  double length = std::sqrt(_x * _x + _y * _y + _z * _z);
  Vector result{*this};
  return result * (1 / length);
}

Vector Vector::cross(const Vector &vec) const {
  double a1, a2, a3, b1, b2, b3;
  a1 = _x;
  a2 = _y;
  a3 = _z;
  b1 = vec.x();
  b2 = vec.y();
  b3 = vec.z();
  return Vector{a2 * b3 - a3 * b2, a3 * b1 - a1 * b3, a1 * b2 - a2 * b1};
}

Vector2 Vector::project(int dim) const {
  switch (dim) {
  case 0:
    return Vector2{_y, _z};

  case 1:
    return Vector2{_x, _z};

  case 2:
    return Vector2{_x, _y};

  default:
    throw Exception{"dimension to loose must lie between 0 and 2"};
    break;
  }
}

bool Vector::parallel(const Vector &vec) const {
  return (this->normalize() == vec.normalize());
}

Vector Vector::reflect(const Vector &normal) const {
  return *this - 2 * (*this * normal) * normal;
}

std::ostream &operator<<(std::ostream &stream, Vector point) {
  stream << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
  return stream;
}

double Vector4::x() const { return m_x; }

double Vector4::y() const { return m_y; }

double Vector4::z() const { return m_z; }

double Vector4::t() const { return m_t; }

double operator*(const Vector4 &lhs, const Vector4 &rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() +
         lhs.t() * rhs.t();
}

std::ostream &operator<<(std::ostream &out, const Vector4 vec4) {
  out << vec4.x() << "\n"
      << vec4.y() << "\n"
      << vec4.z() << "\n"
      << vec4.t() << "\n";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Matrix matrix) {
  for (auto row : matrix.rows()) {
    for (int i = 0; i < 4; ++i) {
      out << row[i];
      if (i < 3)
        out << "|";
    }
    out << "\n";
  }
  return out;
}

Vector4 Matrix::row(int rowIdx) const { return m_rows[rowIdx]; }

Vector4 Matrix::column(int collumnIdx) const {
  if (collumnIdx == 0)
    return Vector4{m_rows[0].x(), m_rows[1].x(), m_rows[2].x(), m_rows[3].x()};

  if (collumnIdx == 1)
    return Vector4{m_rows[0].y(), m_rows[1].y(), m_rows[2].y(), m_rows[3].y()};

  if (collumnIdx == 2)
    return Vector4{m_rows[0].z(), m_rows[1].z(), m_rows[2].z(), m_rows[3].z()};

  return Vector4{m_rows[0].t(), m_rows[1].t(), m_rows[2].t(), m_rows[3].t()};
}

Vector4 Matrix::apply(Vector4 &vec) const {
  auto x = m_rows[0] * vec;
  auto y = m_rows[1] * vec;
  auto z = m_rows[2] * vec;
  auto t = m_rows[3] * vec;
  return Vector4{x, y, z, t};
}

Matrix Matrix::apply(Matrix &matrix) const {
  auto mat = Matrix{};
  auto rows = std::vector<std::vector<double>>{4};
  auto rowVectors = std::vector<Vector4>{4};
  for (int row = 0; row < 4; ++row) {
    rows[row].reserve(4);
    for (int col = 0; col < 4; ++col) {
      rows[row][col] = m_rows[col] * matrix.cols()[col];
    }
    rowVectors[row] =
        Vector4{rows[row][0], rows[row][1], rows[row][2], rows[row][3]};
  }
  return Matrix{rowVectors};
}
} // namespace raytracer

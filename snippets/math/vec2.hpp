#include "../template.hpp"

struct Vec2 {
  double x, y;
  Vec2() : x(0), y(0) {}
  Vec2(double x, double y) : x(x), y(y) {}
  Vec2& operator+=(Vec2 that) { x += that.x, y += that.y; return *this; }
  Vec2& operator-=(Vec2 that) { x -= that.x, y -= that.y; return *this; }
  Vec2& operator*=(double s) { x *= s, y *= s; return *this; }
  Vec2& operator/=(double s) { x /= s, y /= s; return *this; }
  Vec2 operator+(Vec2 that) const { return Vec2(*this) += that; }
  Vec2 operator-(Vec2 that) const { return Vec2(*this) -= that; }
  Vec2 operator*(double that) const { return Vec2(*this) *= that; }
  Vec2 operator/(double that) const { return Vec2(*this) /= that; }
  double dot(Vec2 that) const { return x * that.x + y * that.y; }
  double cross(Vec2 that) const { return x * that.y - y * that.x; }
  double length() const { return hypot(x, y); }
  Vec2 normal() const { return Vec2(*this) / (*this).length(); }
  friend istream& operator>>(istream &is, Vec2 &v) { return is >> v.x >> v.y; }
  friend ostream& operator<<(ostream &os, Vec2 &v) { return os << "(" << v.x << ", " << v.y << ")"; }
};
#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Math {
	const double PI = 3.1415f;

	inline float ToRadians(float degrees) {
		return degrees / 180.0f * PI;
	}

	inline float ToDegrees(float radians) {
		return radians / PI * 180.0f;
	}

	inline float Sin(float x) {
		return sinf(ToRadians(x));
	}

	inline float Cos(float x) {
		return cosf(ToRadians(x));
	}

	inline float Tan(float x) {
		return tanf(ToRadians(x));
	}

	inline float Asin(float x) {
		return ToDegrees(asinf(x));
	}

	inline float Acos(float x) {
		return ToDegrees(acosf(x));
	}

	inline float Atan(float x) {
		return ToDegrees(atanf(x));
	}

	inline float Atan2(float x, float y) {
		return ToDegrees(atan2f(x, y));
	}
}

template< typename T >
struct Vector2_generic {
	T X, Y;
	Vector2_generic() { X = (T)0; Y = (T)0; }
	Vector2_generic(T tx, T ty) { X = tx; Y = ty; }
	Vector2_generic(const glm::vec2& vec) { X = vec.x; Y = vec.y; }

	T Length() {
		return sqrtf(X * X + Y * Y);
	}

	Vector2_generic Normalize() {
		T t = Length();
		return Vector2_generic(X / t, Y / t);
	}

	static T Dot(const Vector2_generic& a, const Vector2_generic& b) {
		return a.X * b.X + a.Y * b.Y;
	}

	static Vector2_generic Zero() {
		return Vector2_generic();
	}
	
	friend Vector2_generic operator+(const Vector2_generic& a, const Vector2_generic& b) {
		return Vector2_generic(a.X + b.X, a.Y + b.Y);
	}

	friend Vector2_generic operator-(const Vector2_generic& a, const Vector2_generic& b) {
		return Vector2_generic(a.X - b.X, a.Y - b.Y);
	}

	friend Vector2_generic operator-(const Vector2_generic& a) {
		return Vector2_generic(-a.X, -a.Y);
	}

	friend Vector2_generic operator*(const T& f, const Vector2_generic& v) {
		return Vector2_generic(f * v.X, f * v.Y);
	}

	friend Vector2_generic operator*(const Vector2_generic& v, const T& f) {
		return Vector2_generic(f * v.X, f * v.Y);
	}

	friend Vector2_generic operator/(const Vector2_generic& v, const T& f) {
		return Vector2_generic(v.X / f, v.Y / f);
	}

	Vector2_generic& operator+= (const Vector2_generic& b) {
		this->X += b.X;
		this->Y += b.Y;
		return *this;
	}

	Vector2_generic& operator-= (const Vector2_generic& b) {
		this->X -= b.X;
		this->Y -= b.Y;
		return *this;
	}

	Vector2_generic& operator*= (const T& b) {
		this->X *= b;
		this->Y *= b;
		return *this;
	}

	Vector2_generic& operator/=(const T& b) {
		this->X /= b;
		this->Y /= b;
		return *this;
	}

	friend bool operator==(const Vector2_generic& a, const Vector2_generic& b) {
		return a.X == b.X && a.Y == b.Y;
	}

	friend bool operator!=(const Vector2_generic& a, const Vector2_generic& b) {
		return a.X != b.X || a.Y != b.Y;
	}
};

typedef Vector2_generic< int > Vector2i;
typedef Vector2_generic< float > Vector2;
typedef Vector2_generic< double > Vector2d;

template< typename T >
struct Vector3_generic {
	T X, Y, Z;
	Vector3_generic() { X = (T)0; Y = (T)0; Z = (T)0; }
	Vector3_generic(T tx, T ty, T tz) { X = tx; Y = ty; Z = tz;  }
	Vector3_generic(const glm::vec3& vec) { X = vec.x; Y = vec.y; Z = vec.z; }

	T Length() {
		return sqrtf(X * X + Y * Y + Z * Z);
	}

	Vector3_generic Normalize() {
		T t = Length();
		return Vector3_generic(X / t, Y / t, Z / t);
	}

	static T Dot(const Vector3_generic& a, const Vector3_generic& b) {
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}
	
	static Vector3_generic Zero() {
		return Vector3_generic();
	}

	static Vector3_generic Cross(const Vector3_generic& a, const Vector3_generic& b) {
		return Vector3_generic(
			a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X
			);
	}

	friend Vector3_generic operator+(const Vector3_generic& a, const Vector3_generic& b) {
		return Vector3_generic(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
	}

	friend Vector3_generic operator-(const Vector3_generic& a, const Vector3_generic& b) {
		return Vector3_generic(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}

	friend Vector3_generic operator-(const Vector3_generic& a) {
		return Vector3_generic(-a.X, -a.Y, -a.Z);
	}

	friend Vector3_generic operator*(T f, const Vector3_generic& v) {
		return Vector3_generic(f * v.X, f * v.Y, f * v.Z);
	}

	friend Vector3_generic operator*(const Vector3_generic& v, T f) {
		return Vector3_generic(f * v.X, f * v.Y, f * v.Z);
	}

	friend Vector3_generic operator/(const Vector3_generic& v, const T& f) {
		return Vector3_generic(v.X / f, v.Y / f, v.Z / f);
	}

	Vector3_generic& operator+= (const Vector3_generic& b) {
		this->X += b.X;
		this->Y += b.Y;
		this->Z += b.Z;
		return *this;
	}

	Vector3_generic& operator-= (const Vector3_generic& b) {
		this->X -= b.X;
		this->Y -= b.Y;
		this->Z -= b.Z;
		return *this;
	}

	Vector3_generic& operator*= (const T& b) {
		this->X *= b;
		this->Y *= b;
		this->Z *= b;
		return *this;
	}

	Vector3_generic& operator/=(const T& b) {
		this->X /= b;
		this->Y /= b;
		this->Z /= b;
		return *this;
	}

	friend bool operator==(const Vector3_generic& a, const Vector3_generic& b) {
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
	}

	friend bool operator!=(const Vector3_generic& a, const Vector3_generic& b) {
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z; 
	}
};

typedef Vector3_generic< int > Vector3i;
typedef Vector3_generic< float > Vector3;
typedef Vector3_generic< double > Vector3d;

template< typename T >
struct Vector4_generic {
	T X, Y, Z, W;
	Vector4_generic() { X = (T)0; Y = (T)0; Z = (T)0; W = (T)0; }
	Vector4_generic(T tx, T ty, T tz, T tw) { X = tx; Y = ty; Z = tz; W = tw; }

	static Vector4_generic Zero() {
		return Vector4_generic();
	}

	friend Vector4_generic operator+(const Vector4_generic& a, const Vector4_generic& b) {
		return Vector4_generic(a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W);
	}

	friend Vector4_generic operator-(const Vector4_generic& a, const Vector4_generic& b) {
		return Vector4_generic(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);
	}

	friend Vector4_generic operator-(const Vector4_generic& a) {
		return Vector4_generic(-a.X, -a.Y, -a.Z, -a.W);
	}

	friend Vector4_generic operator*(T f, const Vector4_generic& v) {
		return Vector4_generic(f * v.X, f * v.Y, f * v.Z, f * v.W);
	}

	friend Vector4_generic operator*(const Vector4_generic& v, T f) {
		return Vector4_generic(f * v.X, f * v.Y, f * v.Z, f * v.W);
	}

	friend Vector4_generic operator/(const Vector4_generic& v, const T& f) {
		return Vector4_generic(v.X / f, v.Y / f, v.Z / f, v.W / f);
	}

	Vector4_generic& operator+= (const Vector4_generic& b) {
		this->X += b.X;
		this->Y += b.Y;
		this->Z += b.Z;
		this->W += b.W;
		return *this;
	}

	Vector4_generic& operator-= (const Vector4_generic& b) {
		this->X -= b.X;
		this->Y -= b.Y;
		this->Z -= b.Z;
		this->W -= b.W;
		return *this;
	}

	Vector4_generic& operator*= (const T& b) {
		this->X *= b;
		this->Y *= b;  
		this->Z *= b;
		this->W *= b;
		return *this;
	}

	Vector4_generic& operator/=(const T& b) {
		this->X /= b;
		this->Y /= b;
		this->Z /= b;
		this->W /= b;
		return *this;
	}

	friend bool operator==(const Vector4_generic& a, const Vector4_generic& b) {
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	friend bool operator!=(const Vector4_generic& a, const Vector4_generic& b) {
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W; 
	}
};

typedef Vector4_generic< int > Vector4i;
typedef Vector4_generic< float > Vector4;
typedef Vector4_generic< double > Vector4d;

template< typename T >
struct Matrix_generic {
	T M[4][4];
	Matrix_generic() {
		SetRow(0, Vector4_generic< T >((T)1, (T)0, (T)0, (T)0));
		SetRow(1, Vector4_generic< T >((T)0, (T)1, (T)0, (T)0));
		SetRow(2, Vector4_generic< T >((T)0, (T)0, (T)1, (T)0));
		SetRow(3, Vector4_generic< T >((T)0, (T)0, (T)0, (T)1));
	}

	Matrix_generic(const glm::mat4& mat) {
		SetColumn(0, Vector4_generic< T >(mat[0][0], mat[0][1], mat[0][2], mat[0][3]));
		SetColumn(1, Vector4_generic< T >(mat[1][0], mat[1][1], mat[1][2], mat[1][3]));
		SetColumn(2, Vector4_generic< T >(mat[2][0], mat[2][1], mat[2][2], mat[2][3]));
		SetColumn(3, Vector4_generic< T >(mat[3][0], mat[3][1], mat[3][2], mat[3][3]));
	}

	void SetColumn(int i, const Vector4_generic< T >& v) {
		M[0][i] = v.X;
		M[1][i] = v.Y;
		M[2][i] = v.Z;
		M[3][i] = v.W;
	}

	void SetRow(int i, const Vector4_generic< T >& v) {
		M[i][0] = v.X;
		M[i][1] = v.Y;
		M[i][2] = v.Z;
		M[i][3] = v.W;
	}

	Vector4_generic< T > GetColumn(int i) const {
		Vector4_generic< T > ret(M[0][i], M[1][i], M[2][i], M[3][i]);
		return ret;
	}
	
	Vector4_generic< T > GetRow(int i) const {
		Vector4_generic< T > ret(M[i][0], M[i][1], M[i][2], M[i][3]);
		return ret;
	}

	friend Vector4_generic< T > operator*(const Vector4_generic< T >& a, const Matrix_generic& m) {
		Vector4_generic< T > ret;
		ret.X = a.X * m.GetColumn(0).X + a.Y * m.GetColumn(0).Y + a.Z * m.GetColumn(0).Z + a.W * m.GetColumn(0).W;
		ret.Y = a.X * m.GetColumn(1).X + a.Y * m.GetColumn(1).Y + a.Z * m.GetColumn(1).Z + a.W * m.GetColumn(1).W;
		ret.Z = a.X * m.GetColumn(2).X + a.Y * m.GetColumn(2).Y + a.Z * m.GetColumn(2).Z + a.W * m.GetColumn(2).W;
		ret.W = a.X * m.GetColumn(3).X + a.Y * m.GetColumn(3).Y + a.Z * m.GetColumn(3).Z + a.W * m.GetColumn(3).W;
		return ret;
	}

	friend Matrix_generic operator*(const Matrix_generic& a, const Matrix_generic& b) {
		Matrix_generic ret;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.M[i][j] = 0;
				for (int k = 0; k < 4; k++) {
					ret.M[i][j] += a.M[i][k] * b.M[k][j];
				}
			}
		}

		return ret;
	}
	
	static Matrix_generic CreateOrthographic(T left, T right, T bottom, T top, T zNear, T zFar) {
		Matrix_generic m;
		m.SetColumn(0, Vector4_generic< T >(2.0 / (right - left), 0.0, 0.0, 0.0));
		m.SetColumn(1, Vector4_generic< T >(0.0, 2.0 / (top - bottom), 0.0, 0.0));
		m.SetColumn(2, Vector4_generic< T >(0.0, 0.0, -2.0 / (zFar - zNear), 0.0));
		m.SetColumn(3, Vector4_generic< T >(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), 1.0));
		return m;
	}


	static Matrix_generic CreateScale(Vector3_generic< T > sc) {
		Matrix_generic ret;
		ret.SetColumn(0, Vector4_generic< T >(sc.X, 0, 0, 0));
		ret.SetColumn(1, Vector4_generic< T >(0, sc.Y, 0, 0));
		ret.SetColumn(2, Vector4_generic< T >(0, 0, sc.Z, 0));
		ret.SetColumn(3, Vector4_generic< T >(0, 0, 0, 1));
		return ret;
	}

	static Matrix_generic CreateTranslation(Vector3_generic< T > vec) {
		Matrix_generic ret;
		ret.SetColumn(0, Vector4_generic< T >(1, 0, 0, 0));
		ret.SetColumn(1, Vector4_generic< T >(0, 1, 0, 0));
		ret.SetColumn(2, Vector4_generic< T >(0, 0, 1, 0));
		ret.SetColumn(3, Vector4_generic< T >(vec.X, vec.Y, vec.Z, 1));
		return ret;
	}

	static Matrix_generic CreatePerspective(T fov, T aspect, T zNear, T zFar) {
		T convert = (T)(3.14159265359 / 180.0);
		T y = 1.0 / tan(convert * fov / 2.0);
		T x = y / aspect;
		T nf = zNear - zFar;
		
		Matrix_generic ret;
		ret.SetRow(0, Vector4_generic< T >(x, 0, 0, 0));	  
		ret.SetRow(1, Vector4_generic< T >(0, y, 0, 0));	  
		ret.SetRow(2, Vector4_generic< T >(0, 0, (zFar + zNear) / nf, 2 * zFar * zNear / nf));	 
		ret.SetRow(3, Vector4_generic< T >(0, 0, -1, 0));

		return ret;
	}

	static Matrix_generic CreateFromAxisAngle(Vector3_generic< T > axis, T angle) {
		angle *= (T)(3.14159265359 / 180.0);

		axis = axis.Normalize();
		T rx = axis.X;
		T ry = axis.Y;
		T rz = axis.Z;
		T s = sin(angle);
		T c = cos(angle);

		Matrix_generic ret;
		ret.SetColumn(0, Vector4_generic< T >(c + rx * rx * (1 - c), ry * rx * (1 - c) + rz * s, rz * rx * (1 - c) - ry * s, 0));
		ret.SetColumn(1, Vector4_generic< T >(rx * ry * (1 - c) - rz * s, c + ry * ry * (1 - c), rz * ry * (1 - c) + rx * s, 0));
		ret.SetColumn(2, Vector4_generic< T >(rx * rz * (1 - c) + ry * s, ry * rz * (1 - c) - rx * s, c + rz * rz * (1 - c), 0));
		ret.SetColumn(3, Vector4_generic< T >(0, 0, 0, 1));

		return ret;
	}

	static Matrix_generic CreateLookAt(Vector3_generic< T > pos, Vector3_generic< T > target, Vector3_generic< T > up) {
		Vector3_generic< T > direction = (pos - target).Normalize();
		Vector3_generic< T > right = Vector3::Cross(up, direction).Normalize();
		Vector3_generic< T > u = Vector3::Cross(direction, right).Normalize();

		Matrix_generic ret;
		ret.SetRow(0, Vector4_generic< T >(right.X, right.Y, right.Z, Vector3_generic< T >::Dot(right, -pos)));
		ret.SetRow(1, Vector4_generic< T >(up.X, up.Y, up.Z, Vector3_generic< T >::Dot(up, -pos)));
		ret.SetRow(2, Vector4_generic< T >(direction.X, direction.Y, direction.Z, Vector3_generic< T >::Dot(direction,  -pos)));
		ret.SetRow(3, Vector4_generic< T >(0, 0, 0, 1));

		return ret;
	}
};

typedef Matrix_generic< int > Matrixi;
typedef Matrix_generic< float > Matrix;
typedef Matrix_generic< double > Matrixd;

template< typename T >
struct Rectangle_generic {
    Vector2_generic< T > position;
    Vector2_generic< T > size;

    Rectangle_generic() { }

    Rectangle_generic(const Vector2_generic< T >& _position, const Vector2_generic< T >& _size) {
        position = _position;
        size = _size;
    }
    
    Rectangle_generic(T _X, T _Y, T _width, T _height) {
        position = Vector2_generic< T >(_X, _Y);
        size = Vector2_generic< T >(_width, _height);
    }

	static bool CheckAABB(const Rectangle_generic& lhs, const Rectangle_generic& rhs) {
		return (lhs.position.X + lhs.size.X > rhs.position.X &&
				lhs.position.X < rhs.position.X + rhs.size.X &&
				lhs.position.Y + lhs.size.Y > rhs.position.Y &&
				lhs.position.Y < rhs.position.Y + rhs.size.Y);
	}

	static Vector2_generic< T > AABBDistance(const Rectangle_generic& lhs, const Rectangle_generic& rhs) {
		T dx, dy;
		if (lhs.position.X < rhs.position.X) {
			dx = rhs.position.X - (lhs.position.X + lhs.size.X);
		}
		else {
			dx = lhs.position.X - (rhs.position.X + rhs.size.X);
		}

		if (lhs.position.Y < rhs.position.Y) {
			dy = rhs.position.Y - (lhs.position.Y + lhs.size.Y);
		}
		else {
			dy = lhs.position.Y - (rhs.position.Y + rhs.size.Y);
		}

		return Vector2_generic< T >(-dx, -dy);	// we want them to be positive
	}
};

typedef Rectangle_generic< int > Rectanglei;
typedef Rectangle_generic< float > Rectangle;
typedef Rectangle_generic< double > Rectangled;

struct Box {
	Vector3 position;
	Vector3 size;

	Box() { }

	Box(const Vector3& _position, const Vector3& _size) {
		position = _position;
		size = _size;
	}

	Box(float X, float Y, float Z, float width, float height, float length) {
		position = Vector3(X, Y, Z);
		size = Vector3(width, height, length);
	}

	static bool IsInside(const Vector3& point, const Box& aabb) {
		return (point.X >= aabb.position.X && point.X <= aabb.position.X + aabb.size.X &&
				point.Y >= aabb.position.Y && point.Y <= aabb.position.Y + aabb.size.Y &&
				point.Z >= aabb.position.Z && point.Z <= aabb.position.Z + aabb.size.Z);
	}

	static bool CheckAABB(const Box& lhs, const Box& rhs) {
		return (lhs.position.X < rhs.position.X + rhs.size.X &&
				lhs.position.X + lhs.size.X > rhs.position.X &&
				lhs.position.Y < rhs.position.Y + rhs.size.Y &&
				lhs.position.Y + lhs.size.Y > rhs.position.Y &&
				lhs.position.Z < rhs.position.Z + rhs.size.Z &&
				lhs.position.Z + lhs.size.Z > rhs.position.Z);
	}

	static Vector3 AABBDistance(const Box& lhs, const Box& rhs) {
		float dx, dy, dz;
		if (lhs.position.X < rhs.position.X) {
			dx = rhs.position.X - (lhs.position.X + lhs.size.X);
		}
		else {
			dx = lhs.position.X - (rhs.position.X + rhs.size.X);
		}

		if (lhs.position.Y < rhs.position.Y) {
			dy = rhs.position.Y - (lhs.position.Y + lhs.size.Y);
		}
		else {
			dy = lhs.position.Y - (rhs.position.Y + rhs.size.Y);
		}

		if (lhs.position.Z < rhs.position.Z) {
			dz = rhs.position.Z - (lhs.position.Z + lhs.size.Z);
		}
		else {
			dz = lhs.position.Z - (rhs.position.Z + rhs.size.Z);
		}

		return Vector3(-dx, -dy, -dz);
	}
};

#endif
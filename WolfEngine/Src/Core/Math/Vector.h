#pragma once
#include "..\ResourceManagement\DataTypes\Typedefs.h"


/* Vectors used to be passed as data */
struct Vector4fData {
public:
	Vector4fData() :X(0.f), Y(0.f), Z(0.f), W(0.f) {}
	Vector4fData(const float& x, const float& y, const float& z, const float& w) :X(x), Y(y), Z(z), W(w) {}
	Vector4fData(const float& xyzw) :X(xyzw), Y(xyzw), Z(xyzw), W(xyzw) {}

	float X;
	float Y;
	float Z;
	float W;
};

struct Vector3fData {
public:
	Vector3fData() :X(0.f), Y(0.f), Z(0.f) {}
	Vector3fData(const float& x, const float& y, const float& z) :X(x), Y(y), Z(z) {}
	Vector3fData(const float& xyz) :X(xyz), Y(xyz), Z(xyz) {}

	float X;
	float Y;
	float Z;
};

struct Vector2fData {
public:
	Vector2fData() :X(0.f), Y(0.f) {}
	Vector2fData(const float& x, const float& y) :X(x), Y(y) {}
	Vector2fData(const float& xy) :X(xy), Y(xy) {}
	float X;
	float Y;
};



/* ============================================================================================ */
/* ============================================================================================ */


/* Vectors used for operations */
template<typename T, u8 N>
struct Vector {
public:
	Vector() {
		for (u8 i = 0; i < N; i++) {
			m_vec_data[i] = 0;
		}
	}
	const Vector<T, N>& operator=(const Vector<T, N>& rhs) {
		for (u8 i = 0; i < N; i++) {
			m_vec_data[i] = rhs.m_vec_data[i];
		}
		return *this;
	}

	const Vector<T, N> operator*(const Vector<T, N>& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] * rhs.m_vec_data[i];
		}
		return tmp_vec;
	}
	const Vector<T, N> operator*(const T& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] * rhs;
		}
		return tmp_vec;
	}

	const Vector<T, N> operator/(const Vector<T, N>& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] / rhs.m_vec_data[i];
		}
		return tmp_vec;
	}
	const Vector<T, N> operator/(const T& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] / rhs;
		}
		return tmp_vec;
	}

	const Vector<T, N> operator+(const Vector<T, N>& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] + rhs.m_vec_data[i];
		}
		return tmp_vec;
	}

	const Vector<T, N> operator-(const Vector<T, N>& rhs) {
		Vector<T, N> tmp_vec;
		for (u8 i = 0; i < N; i++) {
			tmp_vec.m_vec_data[i] = m_vec_data[i] - rhs.m_vec_data[i];
		}
		return tmp_vec;
	}

	T& operator[](const u8& index) {
		return m_vec_data[index];
	}
	T operator[](const u8& index) const {
		return m_vec_data[index];
	}

	const T* GetData() const {
		return m_vec_data;
	}

protected:
	T m_vec_data[N];
};




struct Vector4f :public Vector<float, 4> {
public:
	Vector4f() :Vector() {}
	Vector4f(const float& xyzw) {
		m_vec_data[3] = m_vec_data[2] = m_vec_data[1] = m_vec_data[0] = xyzw;
	}
	Vector4f(const float& x, const float& y, const float& z, const float& w) {
		m_vec_data[0] = x;
		m_vec_data[1] = y;
		m_vec_data[2] = z;
		m_vec_data[3] = w;
	}
	Vector4f(const Vector<float, 4>& rhs) {
		m_vec_data[0] = rhs[0];
		m_vec_data[1] = rhs[1];
		m_vec_data[2] = rhs[2];
		m_vec_data[3] = rhs[3];
	}
	Vector4f(const Vector4fData& rhs) {
		m_vec_data[0] = rhs.X;
		m_vec_data[1] = rhs.Y;
		m_vec_data[2] = rhs.Z;
		m_vec_data[4] = rhs.W;
	}

	Vector4fData ToVData() {
		Vector4fData vec;
		vec.X = m_vec_data[0];
		vec.Y = m_vec_data[1];
		vec.Z = m_vec_data[2];
		vec.W = m_vec_data[3];
		return vec;
	}

	void X(const float& x) {
		m_vec_data[0] = x;
	}
	float X() const {
		return m_vec_data[0];
	}
	void Y(const float& y) {
		m_vec_data[1] = y;
	}
	float Y() const {
		return m_vec_data[1];
	}
	void Z(const float& z) {
		m_vec_data[2] = z;
	}
	float Z() const {
		return m_vec_data[2];
	}
	void W(const float& w) {
		m_vec_data[3] = w;
	}
	float W() {
		return m_vec_data[3];
	}
};





struct Vector3f :public Vector<float, 3> {
public:
	Vector3f() :Vector() {}
	Vector3f(const float& xyz) {
		m_vec_data[2] = m_vec_data[1] = m_vec_data[0] = xyz;
	}
	Vector3f(const float& x, const float& y, const float& z) {
		m_vec_data[0] = x;
		m_vec_data[1] = y;
		m_vec_data[2] = z;
	}
	Vector3f(const Vector<float, 3>& rhs) {
		m_vec_data[0] = rhs[0];
		m_vec_data[1] = rhs[1];
		m_vec_data[2] = rhs[2];
	}
	Vector3f(const Vector3fData& rhs) {
		m_vec_data[0] = rhs.X;
		m_vec_data[1] = rhs.Y;
		m_vec_data[2] = rhs.Z;
	}

	Vector3fData ToVData() {
		Vector3fData vec;
		vec.X = m_vec_data[0];
		vec.Y = m_vec_data[1];
		vec.Z = m_vec_data[2];
		return vec;
	}

	void X(const float& x) {
		m_vec_data[0] = x;
	}
	float X() const {
		return m_vec_data[0];
	}
	void Y(const float& y) {
		m_vec_data[1] = y;
	}
	float Y() const {
		return m_vec_data[1];
	}
	void Z(const float& z) {
		m_vec_data[2] = z;
	}
	float Z() const {
		return m_vec_data[2];
	}
};




struct Vector2f :public Vector<float, 2> {
public:
	Vector2f() :Vector() {}
	Vector2f(const float& xy) {
		m_vec_data[1] = m_vec_data[0] = xy;
	}
	Vector2f(const float& x, const float& y) {
		m_vec_data[0] = x;
		m_vec_data[1] = y;
	}
	Vector2f(const Vector<float, 2>& rhs) {
		m_vec_data[0] = rhs[0];
		m_vec_data[1] = rhs[1];
	}
	Vector2f(const Vector2fData& rhs) {
		m_vec_data[0] = rhs.X;
		m_vec_data[1] = rhs.Y;
	}

	Vector2fData ToVData() {
		Vector2fData vec;
		vec.X = m_vec_data[0];
		vec.Y = m_vec_data[1];
		return vec;
	}

	void X(const float& x) {
		m_vec_data[0] = x;
	}
	float X() const {
		return m_vec_data[0];
	}
	void Y(const float& y) {
		m_vec_data[1] = y;
	}
	float Y() const {
		return m_vec_data[1];
	}
};
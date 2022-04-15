#pragma once
// template <class T> class �e���v���[�g�N���X��
template <class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x_;
	T y_;

	double Magnitude(void) const;
	double SQMagnitude(void) const;
	void Normalize(void);
	Vector2Template<T> Normalized(void);

	//������Z�q
	Vector2Template& operator=(const Vector2Template& vec);

	//�Y�������Z�q
	const int& operator[](int i);

	//�P�����Z�q
	Vector2Template& operator+=(const Vector2Template& vec);
	Vector2Template& operator-=(const Vector2Template& vec);
	Vector2Template& operator*=(const Vector2Template& vec);
	Vector2Template& operator/=(const Vector2Template& vec);
	Vector2Template& operator%=(const Vector2Template& vec);
	Vector2Template operator+()const;
	Vector2Template operator-()const;

	//2�����Z�q
	Vector2Template operator+(Vector2Template vec);
	Vector2Template operator-(Vector2Template vec);
	Vector2Template operator*(Vector2Template vec);
	Vector2Template operator/(Vector2Template vec);
	Vector2Template operator%(Vector2Template vec);
	//Vector2 operator*( float num);

	//��r���Z�q
	bool operator==(const Vector2Template& vec) const;
	bool operator!=(const Vector2Template& vec) const;
	bool operator<(const Vector2Template& vec) const;
	bool operator>(const Vector2Template& vec) const;
	bool operator<=(const Vector2Template& vec) const;
	bool operator>=(const Vector2Template& vec) const;
};
template <class T>
Vector2Template<T> operator*(const Vector2Template<T>& vec, T num);
template <class T>
Vector2Template<T> operator*(T num, const Vector2Template<T>& vec);

using Vector2 = Vector2Template<int>;
using Vector2Flt = Vector2Template<float>;
using Vector2Dbl = Vector2Template<double>;


#include "details/Vector2.h"

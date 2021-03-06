#include "Mat4x4.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

	const float DEG2RAD = 3.141593f / 180.0f;
	const float RAD2DEG = 180.0f / 3.141593f;
	const float EPSILON = 0.00001f;
	Mat4x4::Mat4x4() {
		m[0] = 1; m[4] = 0; m[8] = 0; m[12] = 0;
		m[1] = 0; m[5] = 1;	m[9] = 0; m[13] = 0;
		m[2] = 0; m[6] = 0;	m[10] = 1; m[14] = 0;
		m[3] = 0; m[7] = 0;	m[11] = 0; m[15] = 1;
	}
	Mat4x4::Mat4x4(const float src[16]) {
		m[0] = src[0]; m[4] = src[4];   m[8] = src[8];  m[12] = src[12];
		m[1] = src[1]; m[5] = src[5];	m[9] = src[9];  m[13] = src[13];
		m[2] = src[2]; m[6] = src[6];	m[10] = src[10]; m[14] = src[14];
		m[3] = src[3]; m[7] = src[7];	m[11] = src[11]; m[15] = src[15];
	}

	Mat4x4::Mat4x4(float m00, float m01, float m02, float m03,
		float m04, float m05, float m06, float m07,
		float m08, float m09, float m10, float m11,
		float m12, float m13, float m14, float m15) {
		m[0] = m00; m[4] = m04;   m[8] = m08;  m[12] = m12;
		m[1] = m01; m[5] = m05;	m[9] = m09;  m[13] = m13;
		m[2] = m02; m[6] = m06;	m[10] = m10; m[14] = m14;
		m[3] = m03; m[7] = m07;	m[11] = m11; m[15] = m15;
	}
	Mat4x4& Mat4x4::Identity() {
		m[0] = 1; m[4] = 0; m[8] = 0;  m[12] = 0;
		m[1] = 0; m[5] = 1;	m[9] = 0;  m[13] = 0;
		m[2] = 0; m[6] = 0;	m[10] = 1; m[14] = 0;
		m[3] = 0; m[7] = 0;	m[11] = 0; m[15] = 1;
		return *this;
	}
	tString Mat4x4::toString() {
		std::stringstream ss;
		ss << "[ " << m[0] << " , " << m[4] << " , " << m[8] << " , " << m[12] << " ]\n"
			<< "\t[ " << m[1] << " , " << m[5] << " , " << m[9] << " , " << m[13] << " ]\n"
			<< "\t[ " << m[2] << " , " << m[6] << " , " << m[10] << " , " << m[14] << " ]\n"
			<< "\t[ " << m[3] << " , " << m[7] << " , " << m[11] << " , " << m[15] << " ]\n";
		return ss.str();
	}
	Mat4x4& Mat4x4::Translate(const Vector3& v)
	{
		return Translate(v.x, v.y, v.z);
	}
	Mat4x4& Mat4x4::Translate(float x, float y, float z)
	{
		/*
		m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
		m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
		m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;
		*/
		m[3] = x; m[7] = y; m[11] = z;
		return *this;
	}
	Mat4x4& Mat4x4::Scale(const Vector3& v)
	{
		return Scale(v.x, v.y, v.z);
	}
	Mat4x4& Mat4x4::Scale(float s)
	{
		return Scale(s, s, s);
	}
	Mat4x4& Mat4x4::Scale(float x, float y, float z)
	{
		m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
		m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
		m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
		return *this;
	}


	Mat4x4& Mat4x4::setFrustum(float fovY, float aspect, float front, float back)
	{
		float tangent = tanf(fovY / 2 * DEG2RAD); // tangent of half fovY
		float height = front * tangent;         // half height of near plane
		float width = height * aspect;          // half width of near plane

		Mat4x4 mat;
		mat[0] = 2 * front / (width - -width);
		mat[5] = 2 * front / (height - -height);
		mat[8] = (width + -width) / (width - -width);
		mat[9] = (height + -height) / (height - -height);
		mat[10] = -(back + front) / (back - front);
		mat[11] = -1;
		mat[14] = -(2 * back * front) / (back - front);
		mat[15] = 0;
		return mat;								// params: left, right, bottom, top, near, far
	}
	Mat4x4& Mat4x4::Perspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		fov *= DEG2RAD;
		float tanHalfFOV = (float)tan(fov / 2);
		float zRange = zNear - zFar;

		m[0] = 1.0f / (tanHalfFOV * aspectRatio);	m[4] = 0;		m[8] = 0;	m[12] = 0;
		m[1] = 0;						m[5] = 1.0f / tanHalfFOV;	m[9] = 0;	m[13] = 0;
		m[2] = 0;						m[6] = 0;					m[10] = -(-zNear - zFar) / zRange;	m[14] = -1;
		m[3] = 0;						m[7] = 0;					m[11] = 2 * zFar * zNear / zRange;;	m[15] = 0;

		return *this;
	}
	Mat4x4& Mat4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;

		m[0] = 2 / width; m[4] = 0;			 m[8] = 0;			 m[12] = -(right + left) / width;
		m[1] = 0;		  m[5] = 2 / height; m[9] = 0;			 m[13] = -(top + bottom) / height;
		m[2] = 0;		  m[6] = 0;		 	 m[10] = -2 / depth; m[14] = -(far + near) / depth;
		m[3] = 0;		  m[7] = 0;			 m[11] = 0;			 m[15] = 1;

		return *this;
	}
	Mat4x4& Mat4x4::View(Vector3 eye, Vector3 target, Vector3 up)
	{
		Vector3 f =  ( eye-target);
		f.Normalize();
		Vector3 r = Vector3::Cross(up, f);
		r.Normalize();
		Vector3 u = Vector3::Cross(f, r);
		u.Normalize();

	
				m[0] = r.x;					  m[4] = u.x;					m[8] = f.x;					   m[12] = 0;
				m[1] = r.y;					  m[5] = u.y;					m[9] = f.y, m[13] = 0;
				m[2] = r.z;					  m[6] = u.z;					m[10] = f.z, m[14] = 0;
				m[3] = -Vector3::Dot(r, eye); m[7] = -Vector3::Dot(u, eye); m[11] = -Vector3::Dot(f, eye); m[15] = 1;
			
/*
		m[0] = r.x;
		m[4] = r.y;
		m[8] = r.z;
		m[1] = u.x;
		m[5] = u.y;
		m[9] = u.z;
		m[2] = f.x;
		m[6] = f.y;
		m[10] = f.z;
		m[12] = -Vector3::Dot(r, eye);
		m[13] = -Vector3::Dot(u, eye);
		m[14] = -Vector3::Dot(f, eye);
		*/
		return *this;
	}

	Mat4x4& Mat4x4::rotate(float angle, Vector3 axis)
	{
	return rotate(angle, axis.x, axis.y, axis.z);
	}

	Mat4x4& Mat4x4::rotate(float angle,float x, float y, float z)
	{
	float c = cosf(angle * DEG2RAD);
	float s = sinf(angle * DEG2RAD);
	float c1 = 1.0f - c;
	float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
	m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
	m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

	// build rotation matrix
	float r0 = x * x * c1 + c;
	float r1 = x * y * c1 + z * s;
	float r2 = x * z * c1 - y * s;
	float r4 = x * y * c1 - z * s;
	float r5 = y * y * c1 + c;
	float r6 = y * z * c1 + x * s;
	float r8 = x * z * c1 + y * s;
	float r9 = y * z * c1 - x * s;
	float r10 = z * z * c1 + c;

	// multiply rotation matrix
	m[0] = r0 * m0 + r4 * m1 + r8 * m2;
	m[1] = r1 * m0 + r5 * m1 + r9 * m2;
	m[2] = r2 * m0 + r6 * m1 + r10* m2;
	m[4] = r0 * m4 + r4 * m5 + r8 * m6;
	m[5] = r1 * m4 + r5 * m5 + r9 * m6;
	m[6] = r2 * m4 + r6 * m5 + r10* m6;
	m[8] = r0 * m8 + r4 * m9 + r8 * m10;
	m[9] = r1 * m8 + r5 * m9 + r9 * m10;
	m[10] = r2 * m8 + r6 * m9 + r10* m10;
	m[12] = r0 * m12 + r4 * m13 + r8 * m14;
	m[13] = r1 * m12 + r5 * m13 + r9 * m14;
	m[14] = r2 * m12 + r6 * m13 + r10* m14;

	return *this;
	}

	/*
	Vector3& Mat4x4::Rotate(Vector3 angle)
	{
		Vector3 f = Vector3::forward;
		Vector3 r = Vector3::right;
		Vector3 u = Vector3::up;

		f = Vector3::EulerToForwardVector(angle);
		r = Vector3::Cross(u, f).normalized();
		u = Vector3::Cross(f, r);

		//m[0] = cos(x) * -sin(y)
		return Vector3(0, 0, 0);
	}
	*/

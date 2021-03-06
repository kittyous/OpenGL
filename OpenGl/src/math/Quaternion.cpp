#include "Maths.h"
	const float DEG2RAD = M_PI / 180.0f;
	const float RAD2DEG = 180.0f / M_PI;
	const float EPSILON = 0.00001f;
	Quaternion::Quaternion() {
		x = 0; y = 0; z = 0; w = 0;
	}
	Quaternion::Quaternion(float X, float Y, float Z, float W) {
		x = X; y = Y; z = Z; w = W;
	}
	Quaternion& Quaternion::Rotate(Vector3 angle) {
		return Rotate(angle.x, angle.y, angle.z);
	}
	Quaternion& Quaternion::Rotate(float X, float Y, float Z) {
		X *= DEG2RAD;
		Y *= DEG2RAD;
		Z *= DEG2RAD;

		float cz = cos(Z * .5)
			, sz = sin(Z * .5)
			, cy = cos(Y * .5)
			, sy = sin(Y * .5)
			, cx = cos(X * .5)
			, sx = sin(X * .5);

		x = cy * cz * sx + sy * sz * cx;
		y = sy * cz * cx - cy * sz * sx;
		z = cy * sz * cx - sy * cz * sx;
		w = cy * cz * cx + sy * sz * sx;
		/*
		x = cos(Y/2) * cos(Z/2) * sin(X/2) + sin(Y/2) * sin(Z/2) * cos(X/2);
		y = sin(Y/2) * cos(Z/2) * cos(X/2) - cos(Y/2) * sin(Z/2) * sin(X/2);
		z = cos(Y/2) * sin(Z/2) * cos(X/2) - sin(Y/2) * cos(Z/2) * sin(X/2);
		w = cos(Y/2) * cos(Z/2) * cos(X/2) + sin(Y/2) * sin(Z/2) * sin(X/2);

		x = cos(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5) + sin(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5);
		y = sin(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) - cos(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
		z = cos(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) - sin(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
		w = cos(60 * (M_PI / 180) * .5) * cos(90 * (M_PI / 180) * .5) * cos(30 * (M_PI / 180) * .5) + sin(60 * (M_PI / 180) * .5) * sin(90 * (M_PI / 180) * .5) * sin(30 * (M_PI / 180) * .5);
		*/
		return *this;
	}
	void Quaternion::Normalize() {
		float magnitude = sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
		w = w / magnitude;
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
	Vector3 Quaternion::ToEuler() {
		/*
		///////
		//Method1
		///////
		this->Normalize();
		Vector3 e;
		Quaternion q = { this->x,this->y,this->z,this->w };
		e.x = atan2(2.0f * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
		e.y = asin(std::max(-1.0f, std::min(-2 * (q.x * q.z - q.w * q.y), 1.0f)));
		e.z = atan2(2.0f * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z);
		return e* RAD2DEG;
		*/
		///////
		//Method3
		///////
		/*
		Print();
		float sqw = w*w;
		float sqx = x*x;
		float sqy = y*y;
		float sqz = z*z;
		Vector3 e;
		float sx = 2 * (w * x + y * z);
		float cx = 1 - 2 * (sqx + sqy);
		e.x = atan2(sx, cx);

		float sy = 2 * (w * y - z * x);
		if (fabs(sy) >= 1) 
			e.y = copysign(M_PI / 2, sy);
		else 
			e.y = asin(sy);

		float sz = 2 * (w * z + x * y);
		float cz = 1 - 2 * (sqy + sqz);
		e.z = atan2(sz, cz);
		return e * RAD2DEG;
		
		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;
		Vector3 e;
		e.x = atan2(2 * (z*w + x * y), 2 * (sqz, sqw) - 1);
		e.y = atan2(-2 * (y*w-x-z),sqrt(pow(2 *(z*w + x*y),2)+ pow(2 * (sqz + sqw)-2, 2)));
		e.z = atan2(2 * (y*z + x * w), 2 * (sqx + sqy) - 1);
		return e * RAD2DEG;
		*/
		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;
		Vector3 e;
		e.x = atan2(2*(sqx + sqz) - 1, 2*(y*w + x * z));
		e.y = atan2(sqrt(pow(2 * (y*w + x * z), 2) + pow(2 * (z*w - x * y) - 2, 2)), 2 * (sqx + sqw) - 1);
		e.z = atan2(2 * (z*w + x * y), -2 * (y*w - x * z));
		return e * RAD2DEG;
		/*
		///////
		//Method4
		///////
		Vector3 e;
		double sqw = w*w;
		double sqx = x*x;
		double sqy = y*y;
		double sqz = z*z;
		double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		double test = x*y + z*w;
		if (test > 0.499*unit) { // singularity at north pole
			e.x = 2 * atan2(x,w);
			e.y = M_PI / 2;
			e.z = 0;
			return e* RAD2DEG;
		}
		if (test < -0.499*unit) { // singularity at south pole
			e.x = -2 * atan2(x,w);
			e.y = -M_PI / 2;
			e.z = 0;
			return e* RAD2DEG;
		}
		e.x = atan2(2 * y*w - 2 * x*z, sqx - sqy - sqz + sqw);
		e.y = asin(2 * test / unit);
		e.z = atan2(2 * x*w - 2 * y*z, -sqx + sqy - sqz + sqw);
		return e * RAD2DEG;
		*/
		//return Vector3::zero;
	}
	std::string Quaternion::ToString() {
		std::stringstream ss;
		ss << "{ x:" << x << " y:" << y << " z:" << z << " w:" << w << " }";
		return ss.str();
	}
	void Quaternion::Print(std::string title) {
		std::cout << title << this->ToString() << std::endl;
	}

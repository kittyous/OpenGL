#include "Debug.h"
#define _USE_MATH_DEFINES
	void Debug::DrawCardWireSphere(Vector3 p, float size, int verts, Vector3 angle) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		verts /= 2;
		glPushMatrix();
		glColor3f(0, 0, 1);
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x + cos(i) * size, p.y + sin(i) * size, p.z);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x + sin(i) * size, p.y, p.z + cos(i) * size);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1, 0, 0);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x, p.y + cos(i) * size, p.z + sin(i) * size);
		glEnd();
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void Debug::DrawWireSphere(Vector3 p, float size, Vector3 color, int verts) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		verts /= 2;
		glPushMatrix();
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x + cos(i) * size, p.y + sin(i) * size, p.z);
		glEnd();
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x + sin(i) * size, p.y, p.z + cos(i) * size);
		glEnd();
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x, p.y + cos(i) * size, p.z + sin(i) * size);
		glEnd();
		glPopMatrix();
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void Debug::DrawWireCircle(Vector3 p, float size, Vector3 color, int verts) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		verts /= 2;
		glPushMatrix();
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * M_PI; i += M_PI / verts) //<-- Change this Value
			glVertex3f(p.x + sin(i) * size, p.y, p.z + cos(i) * size);
		glEnd();
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void Debug::DrawGrid(int size, Vector3 color) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_LINES);
		for (int x = -size; x < size+1; x++) {
			glVertex3f(x, 0, -size);
			glVertex3f(x, 0, size);
			glVertex3f(-size, 0, x);
			glVertex3f(size, 0, x);
		}
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	void Debug::DrawAxes(Vector3 p, Vector3 angle) {
		glPushMatrix();
		DrawCardWireSphere(p);
		glBegin(GL_LINES);
		Vector3 f = Vector3::forward;
		Vector3 r = Vector3::right;
		Vector3 u = Vector3::up;
		glTranslatef(p.x, p.y, p.z);
		glColor3f(f.x, f.y, f.z);
		glVertex3f(p.x, p.y, p.z);
		f = Vector3::EulerToForwardVector2(angle);
		glVertex3f(p.x + f.x, p.y + f.y, p.z + f.z);
		glColor3f(r.x, r.y, r.z);
		glVertex3f(p.x, p.y, p.z);
		r = Vector3::Cross(u, f).normalized();
		glVertex3f(p.x + r.x, p.y + r.y, p.z + r.z);
		glColor3f(u.x, u.y, u.z);
		glVertex3f(p.x, p.y, p.z);
		u = Vector3::Cross(f, r);
		glVertex3f(p.x + u.x, p.y + u.y, p.z + u.z);
		glEnd();
	}
	void Debug::DrawWireBox(Vector3 p, Vector3 d, Vector3 color) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPushMatrix();
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_POLYGON);
		glVertex3f(p.x + d.x, p.y + d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + d.y, p.z + -d.z);
		glVertex3f(p.x + d.x, p.y + d.y, p.z + -d.z);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(p.x + d.x, p.y + -d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + -d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + -d.y, p.z + -d.z);
		glVertex3f(p.x + d.x, p.y + -d.y, p.z + -d.z);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(p.x + d.x, p.y + -d.y, p.z + d.z);
		glVertex3f(p.x + d.x, p.y + d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + -d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + d.y, p.z + d.z);
		glVertex3f(p.x + -d.x, p.y + -d.y, p.z + -d.z);
		glVertex3f(p.x + -d.x, p.y + d.y, p.z + -d.z);
		glVertex3f(p.x + d.x, p.y + -d.y, p.z + -d.z);
		glVertex3f(p.x + d.x, p.y + d.y, p.z + -d.z);

		glEnd();
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
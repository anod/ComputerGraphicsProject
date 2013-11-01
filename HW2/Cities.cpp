#include "Cities.h"


Cities::Cities(void)
{
}


Cities::~Cities(void)
{
}

void Cities::add(int x, int y) {
	CITY city;
	city.id = mCities.size() + 1;
	city.connectedTo = 0;
	city.x = x;
	city.y = y;
	city.type = rand() % 2;
	mCities.push_back(city);

	mTerrain->onCityAdd(x,y);

	if (mCities.size() > 1) {
		connectToNearestCity(city);
	}
}

void Cities::draw() {
	for (std::vector<CITY>::iterator it = mCities.begin(); it != mCities.end(); ++it) {
		CITY city = *it;
		//if (city.type == CITY_INDUSTRIAL) {
			drawIndustrialCity(city);
		//}
	}
}

void Cities::drawIndustrialCity(CITY city) {
	glPushMatrix();
		glTranslated(city.x-(GRID_SIZE/2), 0.2f, city.y-(GRID_SIZE/2));
		glBegin(GL_POLYGON);
			glColor3d(0.8f,0.8f,0.4f);
			glVertex3d(-16.0f, 0.6f, -16.0f);              // Top Left
			glVertex3d(-16.0f, 0.6f, 16.0f);              // Top Right
			glVertex3d(16.0f, 0.6f, 16.0f);              // Bottom Right
			glVertex3d(16.0f, 0.6f, -16.0f);              // Bottom Left
		glEnd();


		drawBuilding(-16.0f, -16.0f, 10.0f, 6.0f);

	glPopMatrix();
}

void Cities::drawBuilding(double leftTopX, double leftTopY, double height, double size) {
	// |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glVertex3d(leftTopX, height, leftTopY);              // Top Left
			glVertex3d(leftTopX, height, leftTopY + size);              // Top Right
			glVertex3d(leftTopX, 0.6f, leftTopY + size);              // Bottom Right
			glVertex3d(leftTopX, 0.6f, leftTopY);              // Bottom Left
		glEnd();

	//  ---
	// |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glVertex3d(leftTopX, height, leftTopY);              // Top Left
			glVertex3d(leftTopX+size, height, leftTopY);              // Top Right
			glVertex3d(leftTopX, 0.6f, leftTopY);              // Bottom Right
			glVertex3d(leftTopX+size, 0.6f, leftTopY);              // Bottom Left
		glEnd();

	//   ---
	//  |   |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glVertex3d(leftTopX+size, height, leftTopY);              // Top Left
			glVertex3d(leftTopX+size, height, leftTopY + size);              // Top Right
			glVertex3d(leftTopX+size, 0.6f, leftTopY + size);              // Bottom Right
			glVertex3d(leftTopX+size, 0.6f, leftTopY);              // Bottom Left
		glEnd();
	//  ---
	// |   |
	//  ---
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glVertex3d(leftTopX+size, height, leftTopY+size);              // Top Left
			glVertex3d(leftTopX, height, leftTopY + size);              // Top Right
			glVertex3d(leftTopX+size, 0.6f, leftTopY + size);              // Bottom Right
			glVertex3d(leftTopX, 0.6f, leftTopY + size);              // Bottom Left
		glEnd();

		/*
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glVertex3d(leftTopX, height, leftTopY);              // Top Left
			glVertex3d(leftTopX, height, leftTopY + size);              // Top Right
			glVertex3d(leftTopX, height, leftTopY + size);              // Bottom Right
			glVertex3d(leftTopX,height, leftTopY);              // Bottom Left
		glEnd();
		*/
}

void Cities::drawSleepCity(CITY city) {


}


void Cities::connectToNearestCity(CITY city) {
	CITY closest;
	int minDist = INT_MAX;
	for (std::vector<CITY>::iterator it = mCities.begin(); it != mCities.end(); ++it) {
		CITY other = *it;
		if (other.id != city.id) {
			int dist = sqrt ( pow(double(city.x-other.x), 2) + pow(double(city.y-other.y), 2) );
			if (dist < minDist) {
				minDist = dist;
				closest = other;
			}
		}
	}

	if (closest.id > 0) {
		mRoad->add(city.x,city.y,closest.x,closest.y);
	}

}
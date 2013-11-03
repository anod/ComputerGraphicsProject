#include "Cities.h"


Cities::Cities(void)
{
}


Cities::~Cities(void)
{
}

void Cities::init() {
	mBuilding1Texture = new BmpTexture(0);
	mBuilding2Texture = new BmpTexture(1);
	mRoof1Texture = new BmpTexture(2);
	mRoof2Texture = new BmpTexture(3);

	mBuilding1Texture->load("building1.bmp");
	mBuilding2Texture->load("building2.bmp");
	mRoof1Texture->load("roof1.bmp");
	mRoof2Texture->load("roof2.bmp");


	for(int i=0;i<GRID_SIZE;i++) {
		for(int j=0;j<GRID_SIZE;j++)
		{
			mCitiesOccupied[i][j] = false;
		}
	}
}

void Cities::add(int gridX, int gridY) {

	gridX = normalize(gridX);
	gridY = normalize(gridY);

	if (isOccupied(gridX,gridY)) {
		return;
	}

	CITY city;
	city.id = mCities.size() + 1;
	city.connectedTo = 0;
	city.x = gridX + (CITY_SIZE/2.0f);
	city.y = gridY + (CITY_SIZE/2.0f);
	city.type = rand() % 2;
	mCities.push_back(city);

	mCitiesOccupied[gridX][gridY] = true;
	mTerrain->onCityAdd(city.x,city.y,(CITY_SIZE/2.0f));

	mRoad->add(city.x-(CITY_SIZE/2.0f)+3.0f,city.y,city.x+(CITY_SIZE/2.0f)-3.0f,city.y);
	mRoad->add(city.x,city.y-(CITY_SIZE/2.0f)+3.0f,city.x,city.y+(CITY_SIZE/2.0f)-3.0f);

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
		glTranslated(city.x-GRID_OFFSET, 0.1f, city.y-GRID_OFFSET);

		drawBuilding(-12.0f, -12.0f, 20.0f, 6.0f, mBuilding1Texture, mRoof1Texture);
		drawBuilding(-12.0f,  6.0f,  6.0f, 6.0f, mBuilding2Texture, mRoof2Texture);
		drawBuilding( 6.0f, -12.0f, 12.0f, 6.0f, mBuilding2Texture, mRoof2Texture);
		drawBuilding( 6.0f,  6.0f, 15.0f, 6.0f, mBuilding1Texture, mRoof1Texture);

	glPopMatrix();
}


void Cities::drawBuilding(double leftTopX, double leftTopY, double height, double size, BmpTexture* building, BmpTexture* roof) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,building->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	// |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX, height, leftTopY);              // Top Left
			glTexCoord2d(0,3);    glVertex3d(leftTopX, height, leftTopY + size);              // Top Right
			glTexCoord2d(4,3);    glVertex3d(leftTopX,   0.0f, leftTopY + size);              // Bottom Right
			glTexCoord2d(4,0);    glVertex3d(leftTopX,   0.0f, leftTopY);              // Bottom Left
		glEnd();
	//  ---
	// |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX     , height, leftTopY);              // Top Left
			glTexCoord2d(0,3);   glVertex3d(leftTopX+size, height, leftTopY);              // Top Right
			glTexCoord2d(4,3);   glVertex3d(leftTopX+size,   0.0f, leftTopY);              // Bottom Left
			glTexCoord2d(4,0);   glVertex3d(leftTopX     ,   0.0f, leftTopY);              // Bottom Right
		glEnd();
	//   ---
	//  |   |
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX+size, height, leftTopY);              // Top Left
			glTexCoord2d(0,3);   glVertex3d(leftTopX+size, height, leftTopY + size);              // Top Right
			glTexCoord2d(4,3);   glVertex3d(leftTopX+size,   0.0f, leftTopY + size);              // Bottom Right
			glTexCoord2d(4,0);   glVertex3d(leftTopX+size,   0.0f, leftTopY);              // Bottom Left
		glEnd();
	//  ---
	// |   |
	//  ---
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX+size, height, leftTopY + size);              // Top Left
			glTexCoord2d(0,3);   glVertex3d(leftTopX     , height, leftTopY + size);              // Top Right
			glTexCoord2d(4,3);   glVertex3d(leftTopX     ,   0.0f, leftTopY + size);              // Bottom Left
			glTexCoord2d(4,0);   glVertex3d(leftTopX+size,   0.0f, leftTopY + size);              // Bottom Right
		glEnd();
		
	glBindTexture(GL_TEXTURE_2D,roof->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.2f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX     , height, leftTopY);              // Top Left
			glTexCoord2d(0,3);   glVertex3d(leftTopX     , height, leftTopY + size);              // Top Right
			glTexCoord2d(4,3);   glVertex3d(leftTopX+size, height, leftTopY + size);              // Bottom Right
			glTexCoord2d(4,0);   glVertex3d(leftTopX+size, height, leftTopY);              // Bottom Left
		glEnd();

	glDisable(GL_TEXTURE_2D);
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
		mRoad->addNotDirect(city.x,city.y,closest.x,closest.y);
	}

}
#include "Cities.h"
#include "SelfDrivenCarCollection.h"

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

	mHouse1Texture = new BmpTexture(4);
	mHouse2Texture = new BmpTexture(5);
	mHouse3Texture = new BmpTexture(6);
	mHouse4Texture = new BmpTexture(7);
	mHouseRoofTexture = new BmpTexture(8);


	mBuilding1Texture->load("resources/building1.bmp");
	mBuilding2Texture->load("resources/building2.bmp");
	mRoof1Texture->load("resources/roof1.bmp");
	mRoof2Texture->load("resources/roof2.bmp");

	mHouse1Texture->load("resources/house1.bmp");
	mHouse2Texture->load("resources/house2.bmp");
	mHouse3Texture->load("resources/house3.bmp");
	mHouse4Texture->load("resources/house4.bmp");
	mHouseRoofTexture->load("resources/houseroof1.bmp");


	for(int i=0;i<GRID_SIZE;i++) {
		for(int j=0;j<GRID_SIZE;j++)
		{
			mCitiesOccupied[i][j] = false;
		}
	}
}

int Cities::addSpecType(int gridX, int gridY, int type) {

	gridX = normalize(gridX);
	gridY = normalize(gridY);

	if (isOccupied(gridX,gridY)) {
		return 0;
	}

	CITY city;
	city.id = mCities.size() + 1;
	city.connectedTo = 0;
	city.x = gridX + (CITY_SIZE/2.0f);
	city.y = gridY + (CITY_SIZE/2.0f);
	city.type = type;
	mCities.push_back(city);

	mCitiesOccupied[gridX][gridY] = true;
	mTerrain->onCityAdd(city.x,city.y,(CITY_SIZE/2.0f));

	// Draw road between buildings
	mRoad->add(city.x-(CITY_SIZE/2.0f)+3.0f,city.y,city.x+(CITY_SIZE/2.0f)-3.0f,city.y);
	mRoad->add(city.x,city.y-(CITY_SIZE/2.0f)+3.0f,city.x,city.y+(CITY_SIZE/2.0f)-3.0f);

	if (mCities.size() > 1) {
		connectToNearestCity(city);
	}
	mCarCollection->add(city.id);
	return city.id;
}

int Cities::add(int gridX, int gridY) {
	int type = ((rand() % 100) < 60) ? CITY_SUBURB : CITY_INDUSTRIAL;
	return addSpecType(gridX, gridY, type);
}

void Cities::draw() {
	for (std::vector<CITY>::iterator it = mCities.begin(); it != mCities.end(); ++it) {
		CITY city = *it;
		if (city.type == CITY_INDUSTRIAL) {
			drawIndustrialCity(city);
		} else {
			drawSuburbCity(city);
		}
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


void Cities::drawSuburbCity(CITY city) {

	glPushMatrix();
		glTranslated(city.x-GRID_OFFSET, 0.1f, city.y-GRID_OFFSET);

		drawHouse(-12.0f, -12.0f,mHouse1Texture, mHouse2Texture, mHouseRoofTexture);
		drawHouse(-12.0f,  6.0f, mHouse3Texture, mHouse4Texture, mHouseRoofTexture);
		drawHouse( 6.0f, -12.0f, mHouse3Texture, mHouse4Texture, mHouseRoofTexture);
		drawHouse( 6.0f,  6.0f, mHouse1Texture, mHouse2Texture, mHouseRoofTexture);

	glPopMatrix();
}


void Cities::drawHouse(double leftTopX, double leftTopY, BmpTexture* tex1,  BmpTexture* tex2, BmpTexture* roof) {
	 double height = 6.0f;
	 double size = 6.0f;

	glEnable(GL_TEXTURE_2D);

	// |
	glBindTexture(GL_TEXTURE_2D,tex2->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX, height, leftTopY);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX, height, leftTopY + 2.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX,   0.0f, leftTopY + 2.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX,   0.0f, leftTopY);              // Bottom Left
		glEnd();

	glBindTexture(GL_TEXTURE_2D,tex1->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX, height, leftTopY + 2.0f);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX, height, leftTopY + 4.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX,   0.0f, leftTopY + 4.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX,   0.0f, leftTopY + 2.0f);              // Bottom Left
		glEnd();

	glBindTexture(GL_TEXTURE_2D,tex2->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX, height, leftTopY + 4.0f);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX, height, leftTopY + 6.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX,   0.0f, leftTopY + 6.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX,   0.0f, leftTopY + 4.0f);              // Bottom Left
		glEnd();
	
	//  ---
	// |
	glBindTexture(GL_TEXTURE_2D,tex1->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX     , height, leftTopY);              // Top Left
			glTexCoord2d(0,1);   glVertex3d(leftTopX+size, height, leftTopY);              // Top Right
			glTexCoord2d(1,1);   glVertex3d(leftTopX+size,   0.0f, leftTopY);              // Bottom Left
			glTexCoord2d(1,0);   glVertex3d(leftTopX     ,   0.0f, leftTopY);              // Bottom Right
		glEnd();

	//   ---
	//  |   |
	glBindTexture(GL_TEXTURE_2D,tex2->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX+size, height, leftTopY);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX+size, height, leftTopY + 2.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX+size,   0.0f, leftTopY + 2.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX+size,   0.0f, leftTopY);              // Bottom Left
		glEnd();

	glBindTexture(GL_TEXTURE_2D,tex1->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX+size, height, leftTopY + 2.0f);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX+size, height, leftTopY + 4.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX+size,   0.0f, leftTopY + 4.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX+size,   0.0f, leftTopY + 2.0f);              // Bottom Left
		glEnd();

	glBindTexture(GL_TEXTURE_2D,tex2->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);    glVertex3d(leftTopX+size, height, leftTopY + 4.0f);              // Top Left
			glTexCoord2d(0,1);    glVertex3d(leftTopX+size, height, leftTopY + 6.0f);              // Top Right
			glTexCoord2d(1,1);    glVertex3d(leftTopX+size,   0.0f, leftTopY + 6.0f);              // Bottom Right
			glTexCoord2d(1,0);    glVertex3d(leftTopX+size,   0.0f, leftTopY + 4.0f);              // Bottom Left
		glEnd();


	//  ---
	// |   |
	//  ---
	glBindTexture(GL_TEXTURE_2D,tex1->getId());
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glBegin(GL_POLYGON);
			glColor3d(0.0f,0.8f,0.0f);
			glTexCoord2d(0,0);   glVertex3d(leftTopX+size, height, leftTopY + size);              // Top Left
			glTexCoord2d(0,1);   glVertex3d(leftTopX     , height, leftTopY + size);              // Top Right
			glTexCoord2d(1,1);   glVertex3d(leftTopX     ,   0.0f, leftTopY + size);              // Bottom Left
			glTexCoord2d(1,0);   glVertex3d(leftTopX+size,   0.0f, leftTopY + size);              // Bottom Right
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
		// cities on the same line just add direct road
		if (abs(city.x-closest.x) < 6 || abs(city.y-closest.y) < 6) {
			mRoad->add(city.x,city.y,closest.x,closest.y);
			THREE waypoint1 = {closest.x,closest.y,0};
			THREE waypoint2 = {city.x,city.y,0};
			mCitiesWaypoints[city.id][closest.id].push_back(waypoint1);
			mCitiesWaypoints[closest.id][city.id].push_back(waypoint2);
		} else {
			mRoad->add(city.x,city.y,closest.x,city.y);
			mRoad->add(closest.x,city.y,closest.x,closest.y);

			// one way
			THREE waypoint3 = {closest.x,city.y,0};
			THREE waypoint4 = {closest.x,closest.y,0};
			mCitiesWaypoints[city.id][closest.id].push_back(waypoint4);
			mCitiesWaypoints[city.id][closest.id].push_back(waypoint3);


			// opposite way
			THREE waypoint5 = {closest.x,city.y,0};
			THREE waypoint6 = {city.x,city.y};
			mCitiesWaypoints[closest.id][city.id].push_back(waypoint6);
			mCitiesWaypoints[closest.id][city.id].push_back(waypoint5);
		}
		mCityMap[city.id].push_back(closest);
		mCityMap[closest.id].push_back(city);
	}

}
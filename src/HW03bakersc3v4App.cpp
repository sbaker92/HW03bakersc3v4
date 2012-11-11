#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "bakersc3Starbucks.h"
#include "Resources.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW03bakersc3v4App : public AppBasic {
  public:
    int count;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    Entry* createArray();

	void prepareSettings(Settings* settings);

  private:
	bool clicked;
	Vec2i mousePos;
	Surface* mySurface;
	uint8_t* dataArray;
	gl::Texture* texture;
	gl::Texture* image;
	void drawLocations(Entry* locations, int numLocations);

	bakersc3Starbucks* panda;
	Entry* arr1;
	void rectangle(uint8_t* pixels, double startx, double starty, double width, double height, Color8u fill);

	static const int appWidth = 800;
	static const int appHeight = 600;
	static const int textureSize = 1024;
};

//The lovely prepareSettings method.
void HW03bakersc3v4App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void HW03bakersc3v4App::setup(){
	//The surface!

	mySurface = new Surface(textureSize, textureSize, false);
	//image = new gl::Texture(loadImage(loadResource(RES_IMAGE)));
	*mySurface = Surface(loadImage(loadResource(RES_IMAGE)));
	//Surface mySurface(loadImage("usaMap"));
	texture = new gl::Texture(*mySurface);
	dataArray = mySurface->getData();



	//Array initialization.
	count = 0;
    arr1 = createArray();

	panda = new bakersc3Starbucks;
	panda->num = count;
	panda->arr = arr1;

	drawLocations(panda->arr, panda->num);
}

Entry* HW03bakersc3v4App::createArray(){
    string storeName;
    double xVal, yVal;
    ifstream in("Starbucks_2006.csv");
	if(!in.good()){
		console() << "Can't open file." << endl;
	}
    while(in.good()){
        getline(in, storeName, '\r');
        count++;
    }
    in.clear();
    in.seekg(0);
	
	Entry* stores = new Entry[count];
    int i = 0;
    
    while(in.good()){
        getline(in, storeName, ',');
        in >> xVal;
        in.get();
        in >> yVal;
        in.get();

        stores[i].identifier = storeName;
        stores[i].x = xVal;
        stores[i].y = yVal;

        i++;
    }
    in.close();
    
    return stores;
}

void HW03bakersc3v4App::drawLocations(Entry* locations, int numLocations) {
	Color color = Color(0,0,250);
	for (int i = 0; i < numLocations; i++) {
		double xd = (locations[i].x)*appWidth;
		int x = floor(xd);
		double yd = (locations[i].y)*appHeight;
		int y = floor(appHeight-yd);
		int index = 3 * (x + y * textureSize);
		dataArray[index] = color.r;
		dataArray[index+1] = color.g;
		dataArray[index+2] = color.b;
	}
}

void HW03bakersc3v4App::mouseDown( MouseEvent event ){
	if(event.isLeft()){
		//get the click location
		double x = mousePos.x;
		double y = mousePos.y;

		//convert to floats
		x = x/appWidth;
		y = y/appHeight;

		Entry* value = panda->getNearest(x, y);

		//color the nearest location differently
		Color c = Color(50,200,150);
		double xd = value->x*appWidth;
		int a = floor(xd);
		double yd = value->y*appHeight;
		int b = floor(600-yd);
		int index = 3 * (a + b * textureSize);
		dataArray[index] = c.r;
		dataArray[index+1] = c.g;
		dataArray[index+2] = c.b;


		console() << "clicked!" <<endl;
		console() << value->identifier << endl;
	}
}

void HW03bakersc3v4App::update(){
	(*texture).update(*mySurface, mySurface->getBounds());
	//(*image).update(*mySurface, mySurface->getBounds());
}

void HW03bakersc3v4App::draw(){
	//gl::color(Color(.1f, .8f, .6f));
	//gl::draw(*image, getWindowBounds());
	//gl::draw(*mySurface, getWindowBounds());
	//gl::draw(*mySurface);
	gl::draw(*texture, getWindowBounds());
}

CINDER_APP_BASIC( HW03bakersc3v4App, RendererGl )
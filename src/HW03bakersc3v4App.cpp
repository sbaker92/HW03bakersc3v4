#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "bakersc3Starbucks.h"
#include "Resources.h"
#include <iostream>
#include <fstream>

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
	bakersc3Starbucks* panda;
	Entry* arr;
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
	texture = new gl::Texture(*mySurface);
	image = new gl::Texture(loadImage(loadResource(RES_IMAGE)));

	//Array initialization.
	count = 0;
    arr = createArray();
	//console() << (arr+5)->identifier << endl;
	//panda = new bakersc3Starbucks;
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
        /*in >> xVal;
        in.get();
        in >> yVal;
        in.get();*/
        count++;
    }
    in.clear();
    in.seekg(0);
	
	Entry* stores = new Entry[count];
    //Entry* stores  = new Entry[7655];
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

void HW03bakersc3v4App::rectangle(uint8_t* pixels, double startx, double starty, double width, double height, Color8u fill){
	//double x;
	//double y;

	// to create the rectangle
	/*for (y = starty; y < (starty + height); y++){
		for(x = startx; x < (startx + width); x++){
			pixels[3*(x + y * textureSize)] = fill.r;
			pixels[3*(x + y * textureSize) + 1] = fill.g;
			pixels[3*(x + y * textureSize) + 2] = fill.b;
		}
	}*/
}

void HW03bakersc3v4App::mouseDown( MouseEvent event ){
	clicked = true;
	if(event.isLeft()){
		double x = mousePos.x;
		double y = mousePos.y;
		//panda->getNearest(x, y);
		console() << "clicked!" <<endl;
	}
}

void HW03bakersc3v4App::update(){
	(*texture).update(*mySurface, mySurface->getBounds());
	
}

void HW03bakersc3v4App::draw(){
	//gl::color(Color(.1f, .8f, .6f));
	//gl::draw(*texture);
	int xoffset = (getWindowWidth()-320)/2;
	int yoffset = (getWindowHeight()-240)/2;
	gl::draw(*image, getWindowBounds());
	Color c = Color(0, 0, 50);
	/*for(int i = 0; i < 7655; i++){
		//gl::drawSolidCircle( Vec2f( (arr[i].x)*appWidth, 1-((arr[i].y)*appHeight) ), 2.5f );
		//console() << arr[1].x << endl;
		rectangle(dataArray, arr[i].x*appWidth, arr[i].y*appHeight, .01 , .01, c);
	}*/
}

CINDER_APP_BASIC( HW03bakersc3v4App, RendererGl )
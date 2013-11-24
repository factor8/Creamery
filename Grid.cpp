#include "Adafruit_WS2801.h"
#include "Grid.h"
	
Grid::Grid(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY, int mode) {
	
	// === Static Grid vars === 	

	// Point to the LED strip.
	this->strip = strip;	
	
	// Set the grid sizes.
	this->panelsX = panelsX;
	this->panelsY = panelsY;
	this->pixelsX = pixelsX;
	this->pixelsY = pixelsY;	
		
	this->total = this->strip->numPixels();		
	
	// === Default Grid / Pattern vars === 	
	// These will get changed by the controller.
	
	this->mode = mode;
	this->orientation = vertical;
	this->brightness = 1; ///This belongs in the non-existent pixel class.
	
	
	// Break these out into Grid Classes! Override the Q method...
	// this->setupPanelQ();

}

void Grid::setupPanelQ() {
	
}

// "Queue" method to translate pixel positions based on orientation and mode.
void Grid::q(uint16_t pos, uint32_t c) {		
	
	
	if (this->mode == strand) {
		this->setPixelColor(pos,c);
	} else if (this->mode == mirrored) {
		// left/right mirror mode.
		// mirror(pos,c);
	}	
	if (this->mode == panel) { // Make each panel do the same thing.
		int p;	
		// Serial.println(this->orientation);
		// Serial.print("--- ");Serial.println(pos);
		if (this->orientation == horizontal) {
			for (int i=0;i<this->total/this->panelsX;i++) {				
				p = this->pixelsY*pos+i;
				
				// p = this->pixelsY*pos+i;
				this->setPixelColor(p, c);
				// Serial.println(p);
			}
		} else if (this->orientation == vertical) {
	
			for (int i=0;i<this->total/this->pixelsY;i++) {
				// p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
				// This one might be better....
				p = (i%2) ? (this->pixelsY*i)+(this->pixelsY-1)-(pos) : (i*this->pixelsY)+(pos);
				
				this->setPixelColor(p,c);		
				// Serial.println(p);
			}
			
		}
		
	} else {
		this->setPixelColor(pos,c);
	}
	
	
}

// // Translate pixel positions based on orientation and mode.
// uint16_t Grid::translate(uint16_t pos) {		
// 	if (this->mode == strand) {
// 		return pos;
// 	} else if (this->mode == mirrored) {
// 		// left/right mirror mode.
// 		// mirror(pos,c);
// 	}	
// 	if (this->mode == panel) { // Make each panel do the same thing.
// 		int p;		
// 		if (this->orientation == horizontal) {
// 			for (int i=0;i<this->total/this->panelsX;i++) {				
// 				p = this->pixelsY*pos+i;
// 				this->setPixelColor(p, c);
// 				Serial.println(p);
// 			}
// 			
// 		} else if (this->orientation == vertical) {
// 	
// 			for (int i=0;i<this->total/this->pixelsY;i++) {
// 				p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
// 				this->setPixelColor(p,c);		
// 			}
// 			
// 		}	
// 	}			 
// }

void Grid::show() {
	this->strip->show();
}
void Grid::setBrightness(double brightness) {
	/// As of yet developed brightness control.
	this->brightness = brightness;
}
void Grid::setGridMode(uint8_t modeid) {
	if (modeid == strand || modeid == panel || modeid == mirrored) {
		this->mode = modeid;
	}
}
void Grid::setPixelColor(uint16_t n, uint32_t c) {	
	/// Is this where we should apply brightness filter?
	// this->strip->setPixelColor(n,c);
	
	this->strip->setPixelColor(n,c);
}	
uint8_t Grid::getGridMode() {
	return this->mode;
}			
uint8_t Grid::getTotal() {
	// We need to add adjustments for orientation too...

	if (this->mode == panel) {
		return this->total/this->panelsX;
	} else if (this->mode == mirrored) {
		return this->total; ////
	} else {
		return this->total;
	}	
}			
// Returns Serial ID of XY position in grid.
uint8_t Grid::getXY(int x, int y){}

uint32_t Grid::getPixelColor(uint16_t n) {
	return(this->strip->getPixelColor(n));
}

uint32_t Grid::rgba(byte r, byte g, byte b, double a) {
	int rr = r*a;
	int gg = g*a;
	int bb = b*a;

	return this->Color(rr,gg,bb);
}
// Create a 24 bit color value from R,G,B
uint32_t Grid::Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;  
	c |= b;
	
  	return c;
}

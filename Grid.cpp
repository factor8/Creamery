#include "Adafruit_WS2801.h"
#include "Grid.h"
	
Grid::Grid(Adafruit_WS2801 *strip,int panelsX, int panelsY,int pixelsX,int pixelsY, int mode) {
	
	this->strip = strip;	
	
	// === Grid / Pattern vars === 
	// Division sets the strand mode. 1 is regular, 2 is Mirror, 3 is Triangle (not added yet), 4 is Radial.
	this->mode = mode;
	this->orientation = vertical;
	
	this->panelsX = panelsX;
	this->panelsY = panelsY;
	this->pixelsX = pixelsX;
	this->pixelsY = pixelsY;
	
	this->total = this->strip->numPixels();		

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
	
		if (this->orientation == horizontal) {
			for (int i=0;i<this->total/this->panelsX;i++) {				
				p = this->pixelsY*pos+i;
				this->setPixelColor(p, c);
				Serial.println(p);				
			}
		} else if (this->orientation == vertical) {
	
			for (int i=0;i<this->total/this->pixelsY;i++) {
				p = (i%2) ? (this->panelsX*i)+(this->pixelsY-1)-(pos) : (i*this->panelsX)+(pos);
				this->setPixelColor(p,c);		
			}
			
		}	
	}			 
}

// // "Queue" method to translate pixel positions based on orientation and mode.
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

void Grid::setGridMode(uint8_t modeid) {
	if (modeid == strand || modeid == panel || modeid == mirrored) {
		this->mode = modeid;
	}
}
void Grid::setPixelColor(uint16_t n, uint32_t c) {
	this->strip->setPixelColor(n,c);
}	
uint8_t Grid::getGridMode() {
	return this->mode;
}			
// Returns Serial ID of XY position in grid.
uint8_t Grid::getXY(int x, int y){}

uint32_t Grid::getPixelColor(uint16_t n) {
	return(this->strip->getPixelColor(n));
}
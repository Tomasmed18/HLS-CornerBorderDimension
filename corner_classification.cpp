#include "corner_classification.h"
#include "pixel_remapper.h"

int absolute_distance(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y){
	if (x > y)
		return x - y;
	else
		return y - x;
}

int corner_classification(xf::Mat<TYPE, HEIGHT, WIDTH, NPIX> & _src, ROI & roi)
{
	ap_uint<COORDINATE_BITS> corners[MAX_CORNERS][2];
	short int cornersCount = 0;

	ap_uint<COORDINATE_BITS> minX = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxX = MAX_VAL;
	ap_uint<COORDINATE_BITS> minY = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxY = MAX_VAL;

	for(short int j = 0; j < _src.rows ; j++ ){
			for(short int i = 0; i < (_src.cols>>XF_BITSHIFT(XF_NPPC1)); i++ ){
				//get the pixel brightness value
				unsigned char pix = _src.data[j*(_src.cols>>XF_BITSHIFT(XF_NPPC1))+i];

				//remap the coordinates, deleting radial lens distortion
				point remapped_intercept = pixel_remap(j, i);

				short int y, x;
				y = remapped_intercept.y;
				x = remapped_intercept.x;


				if ((j > 0) && ((int)pix > 200)){
					//add the coordinates to the array
					corners[cornersCount][0] = x;
					corners[cornersCount][1] = y;
					cornersCount++;

					//find max and min values
					if ((minX == MAX_VAL) || (minX > x))
						minX = x;
					if ((maxX == MAX_VAL) || (maxX < x))
						maxX = x;
					if ((minY == MAX_VAL) || (minY > y))
						minY = y;
					if ((maxY == MAX_VAL) || (maxY < y))
						maxY = y;

				}
			}
		}
	bool v1 = false;
	bool v2 = false;
	bool v3 = false;
	bool v4 = false;
	bool borderError = false;

	for(int i = 0; i < cornersCount; i++){

		if ((absolute_distance(minX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i][1]) < HANDICAP_CORNER)){
			v1 = true;
		}
		else if ((absolute_distance(maxX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i][1]) < HANDICAP_CORNER)){
			v2 = true;
		}
		else if ((absolute_distance(minX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i][1]) < HANDICAP_CORNER)){
			v3 = true;
		}
		else if ((absolute_distance(maxX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i][1]) < HANDICAP_CORNER)){
			v4 = true;
		}
		else{
			//verify if anyone of the corners if out of the "No error" bounds
			if (!((absolute_distance(minX, corners[i][0]) < HANDICAP_ERROR)
				|| (absolute_distance(maxX, corners[i][0]) < HANDICAP_ERROR)
				|| (absolute_distance(minY, corners[i][1]) < HANDICAP_ERROR)
				|| (absolute_distance(maxY, corners[i][1]) < HANDICAP_ERROR)))
				borderError = true;
		}
	}

	//to return the coordinates of the Region Of Interest
	roi.x1 = minX; roi.y1 = minY;
	roi.x2 = maxX; roi.y2 = minY;
	roi.x3 = minX; roi.y3 = maxY;
	roi.x4 = maxX; roi.y4 = maxY;



	if ((!v1) || (!v2) || (!v3) || (!v4)){
		//corner error
		return CORNER_ERROR;
	}
	else if (borderError){
		return BORDER_ERROR;
	}

	//compute dimension

	int s =  (minX * minY) - (maxX * minY);
		s += (maxX * maxY) - (maxX * minY);
		s += (maxX * maxY) - (minX * maxY);
		s += (minX * minY) - (minX * maxY);
	int dimension =  s / 2;

	if ((dimension < MIN_AREA) || (dimension > MAX_AREA)){
		//dimension error
		return DIMENSION_ERROR;
	}



	return NO_ERROR;
}

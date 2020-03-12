#include "corner_classification.h"
#include "pixel_remapper.h"


int absolute_distance(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y){
	if (x > y)
		return x - y;
	else
		return y - x;
}

void draw_corners(xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX_CORNER_CLASSIFICATION> & img,
		short int x1, short int y1, short int x4, short int y4){
	if (((x1-FIGURE_KERNEL_CENTER) > 0) && ((y1-FIGURE_KERNEL_CENTER) > 0) &&
			((x4-FIGURE_KERNEL_CENTER) > 0) && ((y4-FIGURE_KERNEL_CENTER) > 0) &&
			((x1+FIGURE_KERNEL_CENTER) < WIDTH) && ((y1+FIGURE_KERNEL_CENTER) < HEIGHT) &&
			((x4+FIGURE_KERNEL_CENTER) < WIDTH) && ((y4+FIGURE_KERNEL_CENTER) < HEIGHT))

		for(int i = 0; i < FIGURE_KERNEL_DIM; i++)

		#pragma HLS UNROLL
			for(int j = 0; j < FIGURE_KERNEL_DIM; j++){
				#pragma HLS UNROLL
							if (figure[i][j]){
								img.data[(y1+i-FIGURE_KERNEL_CENTER)*(img.cols>>XF_BITSHIFT(XF_NPPC1)) + (x1+j-FIGURE_KERNEL_CENTER)] = CORNER_COLOR;
								img.data[(y1+i-FIGURE_KERNEL_CENTER)*(img.cols>>XF_BITSHIFT(XF_NPPC1)) + (x4+j-FIGURE_KERNEL_CENTER)] = CORNER_COLOR;
								img.data[(y4+i-FIGURE_KERNEL_CENTER)*(img.cols>>XF_BITSHIFT(XF_NPPC1)) + (x1+j-FIGURE_KERNEL_CENTER)] = CORNER_COLOR;
								img.data[(y4+i-FIGURE_KERNEL_CENTER)*(img.cols>>XF_BITSHIFT(XF_NPPC1)) + (x4+j-FIGURE_KERNEL_CENTER)] = CORNER_COLOR;
							}
						}
}

int corner_classification(xf::Mat<TYPE, HEIGHT, WIDTH, NPIX_CORNER_CLASSIFICATION> & _src,
						  xf::Mat<XF_8UC3, HEIGHT, WIDTH, NPIX_CORNER_CLASSIFICATION> & _dst, ROI & roi)
{
	point corners[MAX_CORNERS];
	short int cornersCount = 0;

	ap_uint<COORDINATE_BITS> minX = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxX = MAX_VAL;
	ap_uint<COORDINATE_BITS> minY = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxY = MAX_VAL;

	for(short int j = 1; j < (_src.rows - 1); j++ ){
			corner_classification_label0:for(short int i = 10; i < ((_src.cols>>XF_BITSHIFT(XF_NPPC1)) - 10); i++ ){
				//get the pixel brightness value
				unsigned char pix = _src.data[j*(_src.cols>>XF_BITSHIFT(XF_NPPC1))+i];

				if ((int)pix > 200){ // if its a white pixel
					//remap the coordinates, deleting radial lens distortion
					point remapped_intercept = pixel_remap(j, i);

					//add the coordinates to the array
					corners[cornersCount++] = remapped_intercept;

					//find max and min values
					if ((minX == MAX_VAL) || (minX > remapped_intercept.x))
						minX = remapped_intercept.x;
					if ((maxX == MAX_VAL) || (maxX < remapped_intercept.x))
						maxX = remapped_intercept.x;
					if ((minY == MAX_VAL) || (minY > remapped_intercept.y))
						minY = remapped_intercept.y;
					if ((maxY == MAX_VAL) || (maxY < remapped_intercept.y))
						maxY = remapped_intercept.y;

				}
			}
		}
	bool v1 = false;
	bool v2 = false;
	bool v3 = false;
	bool v4 = false;
	bool borderError = false;

	for(int i = 0; i < cornersCount; i++){
		bool correct = false;

		if ((absolute_distance(minX, corners[i].x) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i].y) < HANDICAP_CORNER)){
			v1 = true;
			correct = true;
		}
		else if ((absolute_distance(maxX, corners[i].x) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i].y) < HANDICAP_CORNER)){
			v2 = true;
			correct = true;
		}
		else if ((absolute_distance(minX, corners[i].x) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i].y) < HANDICAP_CORNER)){
			v3 = true;
			correct = true;
		}
		else if ((absolute_distance(maxX, corners[i].x) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i].y) < HANDICAP_CORNER)){
			v4 = true;
			correct = true;
		}
		else{
			//verify if anyone of the corners if out of the "No error" bounds
			if (!((absolute_distance(minX, corners[i].x) < HANDICAP_ERROR)
				|| (absolute_distance(maxX, corners[i].x) < HANDICAP_ERROR)
				|| (absolute_distance(minY, corners[i].y) < HANDICAP_ERROR)
				|| (absolute_distance(maxY, corners[i].y) < HANDICAP_ERROR))){
				borderError = true;
				_dst.data[(corners[i].y)*(_dst.cols>>XF_BITSHIFT(XF_NPPC1)) + (corners[i].x)] = ERROR_BORDER_COLOR;
			} else
				_dst.data[(corners[i].y)*(_dst.cols>>XF_BITSHIFT(XF_NPPC1)) + (corners[i].x)] = CORRECT_BORDER_COLOR;

		}
		if (correct)
			_dst.data[(corners[i].y)*(_dst.cols>>XF_BITSHIFT(XF_NPPC1)) + (corners[i].x)] = CORRECT_CORNER_COLOR;
	}

	//to return the coordinates of the Region Of Interest
	roi.x1 = minX; roi.y1 = minY;
	roi.x2 = maxX; roi.y2 = minY;
	roi.x3 = minX; roi.y3 = maxY;
	roi.x4 = maxX; roi.y4 = maxY;

	//draw the supposed corner locations
	//draw_corners(_dst, minX, minY, maxX, maxY);


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

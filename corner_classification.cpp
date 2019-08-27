#include "corner_classification.h"

int absolute_distance(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y){
	if (x > y)
		return x - y;
	else
		return y - x;
}

int corner_classification(xf::Mat<TYPE, HEIGHT, WIDTH, XF_NPPC1> & _src, ROI & roi)
{
	ap_uint<COORDINATE_BITS> corners[MAX_CORNERS][2];
	short int cornersCount = 0;

	ap_uint<COORDINATE_BITS> minX = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxX = MAX_VAL;
	ap_uint<COORDINATE_BITS> minY = MAX_VAL;
	ap_uint<COORDINATE_BITS> maxY = MAX_VAL;

	for(short int j = 0; j < _src.rows ; j++ ){
			for(short int i = 0; i < (_src.cols>>XF_BITSHIFT(XF_NPPC1)); i++ ){
				unsigned char pix = _src.data[j*(_src.cols>>XF_BITSHIFT(XF_NPPC1))+i];

				short int y, x;
				y = j;
				x = i;


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
	ap_uint<COORDINATE_BITS> v1[MAX_CORNERS][2];
	ap_uint<COORDINATE_BITS> v2[MAX_CORNERS][2];
	ap_uint<COORDINATE_BITS> v3[MAX_CORNERS][2];
	ap_uint<COORDINATE_BITS> v4[MAX_CORNERS][2];
	ap_uint<COORDINATE_BITS> vError[MAX_CORNERS][2];
	short int c1 = 0;
	short int c2 = 0;
	short int c3 = 0;
	short int c4= 0;
	short int cError = 0;

	for(int i = 0; i < cornersCount; i++){

		if ((absolute_distance(minX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i][1]) < HANDICAP_CORNER)){
			v1[c1][0] = corners[i][0];
			v1[c1][1] = corners[i][1];
			c1++;
		}
		else if ((absolute_distance(maxX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(minY, corners[i][1]) < HANDICAP_CORNER)){
			v2[c2][0] = corners[i][0];
			v2[c2][1] = corners[i][1];
			c2++;
		}

		else if ((absolute_distance(minX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i][1]) < HANDICAP_CORNER)){
			v3[c3][0] = corners[i][0];
			v3[c3][1] = corners[i][1];
			c3++;
		}
		else if ((absolute_distance(maxX, corners[i][0]) < HANDICAP_CORNER) && (absolute_distance(maxY, corners[i][1]) < HANDICAP_CORNER)){
			v4[c4][0] = corners[i][0];
			v4[c4][1] = corners[i][1];
			c4++;
		}
		else{
			vError[cError][0] = corners[i][0];
			vError[cError][1] = corners[i][1];
			cError++;
		}
	}

	//to return the coordinates of the Region Of Interest
	roi.x1 = v1[0][0]; roi.y1 = v1[0][1];
	roi.x2 = v2[0][0]; roi.y2 = v2[0][1];
	roi.x3 = v3[0][0]; roi.y3 = v3[0][1];
	roi.x4 = v4[0][0]; roi.y4 = v4[0][1];



	if ((c1 == 0) || (c2 == 0) || (c3 == 0) || (c4 == 0)){
		//corner error
		return CORNER_ERROR;
	}

	ap_uint<COORDINATE_BITS> vNoError[MAX_CORNERS][2];
	ap_uint<COORDINATE_BITS> vErrorEdge[MAX_CORNERS][2];
	short int cNoError = 0;
	short int cErrorEdge = 0;

	for(short int i = 0; i < cError; i++)
		if ((absolute_distance(minX, vError[i][0]) < HANDICAP_ERROR)
				|| (absolute_distance(maxX, vError[i][0]) < HANDICAP_ERROR)
				|| (absolute_distance(minY, vError[i][1]) < HANDICAP_ERROR)
				|| (absolute_distance(maxY, vError[i][1]) < HANDICAP_ERROR))
		{
			vNoError[cNoError][0] = vError[i][0];
			vNoError[cNoError][1] = vError[i][1];
			cNoError++;
		}

		else
		{
			vErrorEdge[cErrorEdge][0] = vError[i][0];
			vErrorEdge[cErrorEdge][1] = vError[i][1];
			cErrorEdge++;
		}

	if (cErrorEdge > 0){
		//border error
		return BORDER_ERROR;
	}


	//compute dimension

	int s =  (v1[0][0] * v2[0][1]) - (v2[0][0] * v1[0][1]);
		s += (v2[0][0] * v4[0][1]) - (v4[0][0] * v2[0][1]);
		s += (v4[0][0] * v3[0][1]) - (v3[0][0] * v4[0][1]);
		s += (v3[0][0] * v1[0][1]) - (v1[0][0] * v3[0][1]);
	int dimension =  s / 2;

	if ((dimension < MIN_AREA) || (dimension > MAX_AREA)){
		//dimension error
		return DIMENSION_ERROR;
	}



	return NO_ERROR;
}

#include "corner_classification_test_code.h"
#include "pixel_remapper.h"

int distance_testing(ap_uint<COORDINATE_BITS> x, ap_uint<COORDINATE_BITS> y){
	if (x > y)
		return x - y;
	else
		return y - x;
}

ROI corner_classification_testing(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> & _src, cv::Mat & _image_to_draw){


			ap_uint<COORDINATE_BITS> corners[MAX_CORNERS][2];
			short int cornersCount = 0;

			ap_uint<COORDINATE_BITS> minX = MAX_VAL;
			ap_uint<COORDINATE_BITS> maxX = MAX_VAL;
			ap_uint<COORDINATE_BITS> minY = MAX_VAL;
			ap_uint<COORDINATE_BITS> maxY = MAX_VAL;


			for(short int j = 0; j < _src.rows ; j++ ){
					for( short int i = 0; i < (_src.cols>>XF_BITSHIFT(XF_NPPC1)); i++ ){
							unsigned char pix = _src.data[j*(_src.cols>>XF_BITSHIFT(XF_NPPC1))+i];

							point remapped_intercept = pixel_remap(j, i);

							short int y, x;
							y = remapped_intercept.y;
							x = remapped_intercept.x;

							if ((int)pix > 200){
								std::cout << "(" << i << ", " << j << ") ---> ("<< x << ", " << y << ")\n";
							}

								if ((j > 0) && ((int)pix > 200)
//										&& (x > 400) && (y > 200) //For testing purposes only
								){

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

									cv::circle(_image_to_draw, cv::Point(x, y), 20,  cv::Scalar(255,255,255), 6, 8, 0 );
								}


					}
				}

			std::cout << "\nCorners count: " << cornersCount << "\n\n";

			for (int i = 0; i < cornersCount; i++)
				std::cout << "x  " << corners[i][0] << "    y  " << corners[i][1] << "\n";

			std::cout << "\n\n minX: " << minX << "  minY: "<< minY << "  maxX: "<< maxX << "  maxY: "<< maxY << "\n";

			cv::imwrite("out_img_2.png", _image_to_draw);


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

				if ((distance_testing(minX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(minY, corners[i][1]) < HANDICAP_CORNER)){
					v1[c1][0] = corners[i][0];
					v1[c1][1] = corners[i][1];
					c1++;
				}
				else if ((distance_testing(maxX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(minY, corners[i][1]) < HANDICAP_CORNER)){
					v2[c2][0] = corners[i][0];
					v2[c2][1] = corners[i][1];
					c2++;
				}

				else if ((distance_testing(minX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(maxY, corners[i][1]) < HANDICAP_CORNER)){
					v3[c3][0] = corners[i][0];
					v3[c3][1] = corners[i][1];
					c3++;
				}
				else if ((distance_testing(maxX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(maxY, corners[i][1]) < HANDICAP_CORNER)){
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



			//print corner counts of each array
			std::cout << "\n v1: " << c1 << "  v2: "<< c2 << "  v3: "<< c3 << "  v4: "<< c4 << "  verror: " << cError << "\n";


			//print every point of each array
			std::cout << "\n v1 points: \n";
			for (int i = 0; i < c1; i++)
				std::cout << "x: " << v1[i][0] << "  y: " << v1[i][1] << "\n";

			std::cout << "\n v2 points: \n";
			for (int i = 0; i < c2; i++)
				std::cout << "x: " << v2[i][0] << "  y: " << v2[i][1] << "\n";

			std::cout << "\n v3 points: \n";
			for (int i = 0; i < c3; i++)
				std::cout << "x: " << v3[i][0] << "  y: " << v3[i][1] << "\n";

			std::cout << "\n v4 points: \n";
			for (int i = 0; i < c4; i++)
				std::cout << "x: " << v4[i][0] << "  y: " << v4[i][1] << "\n";

			std::cout << "\n verror points: \n";
			for (int i = 0; i < cError; i++)
				std::cout << "x: " << vError[i][0] << "  y: " << vError[i][1] << "\n";


			//verify if there is a corner error
			if ((c1 == 0) || (c2 == 0) || (c3 == 0) || (c4 == 0)){
				//corner error
				//return 1;
				std::cout << "CORNER ERROR\n\n";
			}



			//compute edge error

			ap_uint<COORDINATE_BITS> vNoError[MAX_CORNERS][2];
			ap_uint<COORDINATE_BITS> vErrorEdge[MAX_CORNERS][2];
			short int cNoError = 0;
			short int cErrorEdge = 0;

			for(short int i = 0; i < cError; i++)
				if ((distance_testing(minX, vError[i][0]) < HANDICAP_ERROR)
						|| (distance_testing(maxX, vError[i][0]) < HANDICAP_ERROR)
						|| (distance_testing(minY, vError[i][1]) < HANDICAP_ERROR)
						|| (distance_testing(maxY, vError[i][1]) < HANDICAP_ERROR))
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



			//print edge error results
			cv::Mat out_img_3;
			out_img_3 = cv::imread("cemva_images/remapped.png", CV_LOAD_IMAGE_COLOR);
			cv::Mat out_img_4;
			out_img_4 = cv::imread("cemva_images/remapped.png", CV_LOAD_IMAGE_COLOR);
			std::cout << "\n ************** \nvNoerror points: \n";
			for (int i = 0; i < cNoError; i++){
				std::cout << "x: " << vNoError[i][0] << "  y: " << vNoError[i][1] << "\n";
				cv::circle(out_img_3, cv::Point(vNoError[i][0], vNoError[i][1]), 8,  cv::Scalar(255,0,0), 6, 8, 0 );
			}

			std::cout << "\n vEdgeerror points: \n";
			for (int i = 0; i < cErrorEdge; i++){
				std::cout << "x: " << vErrorEdge[i][0] << "  y: " << vErrorEdge[i][1] << "\n";
				cv::circle(out_img_4, cv::Point(vErrorEdge[i][0], vErrorEdge[i][1]), 8,  cv::Scalar(0,0,255), 6, 8, 0 );
			}
			std::cout << "\n";
			cv::imwrite("out_img_no_error.png", out_img_3);
			cv::imwrite("out_img_error.png", out_img_4);

			if (cErrorEdge > 0){
				//border error

				//return 1;
				std::cout << "BORDER ERROR\n\n";
			}


			//compute dimension

			int s =  (v1[0][0] * v2[0][1]) - (v2[0][0] * v1[0][1]);
				s += (v2[0][0] * v4[0][1]) - (v4[0][0] * v2[0][1]);
				s += (v4[0][0] * v3[0][1]) - (v3[0][0] * v4[0][1]);
				s += (v3[0][0] * v1[0][1]) - (v1[0][0] * v3[0][1]);
			int dimension =  s / 2;

			std::cout << "Dimension: " << dimension << "\n\n";

			if ((dimension < MIN_AREA) || (dimension > MAX_AREA)){
				//dimension error

				//return 1;
				std::cout << "DIMENSION ERROR\n\n";
			}


			ROI roi;
			roi.x1 = v1[0][0]; roi.y1 = v1[0][1];
			roi.x2 = v2[0][0]; roi.y2 = v2[0][1];
			roi.x3 = v3[0][0]; roi.y3 = v3[0][1];
			roi.x4 = v4[0][0]; roi.y4 = v4[0][1];

			return roi;
}


ROI corner_classification_testing_2(xf::Mat<XF_8UC1, HEIGHT, WIDTH, XF_NPPC1> & _src, cv::Mat & _image_to_draw){


			ap_uint<COORDINATE_BITS> corners[MAX_CORNERS][2];
			short int cornersCount = 0;

			ap_uint<COORDINATE_BITS> minX = MAX_VAL;
			ap_uint<COORDINATE_BITS> maxX = MAX_VAL;
			ap_uint<COORDINATE_BITS> minY = MAX_VAL;
			ap_uint<COORDINATE_BITS> maxY = MAX_VAL;


			for(short int j = 0; j < _src.rows ; j++ ){
					for( short int i = 0; i < (_src.cols>>XF_BITSHIFT(XF_NPPC1)); i++ ){
							unsigned char pix = _src.data[j*(_src.cols>>XF_BITSHIFT(XF_NPPC1))+i];

								short int y, x;
								y = j;
								x = i;


								if ((j > 0) && ((int)pix > 200)
//										&& (x > 400) && (y > 200) //For testing purposes only
								){

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

									cv::circle(_image_to_draw, cv::Point(x, y), 20,  cv::Scalar(255,255,255), 6, 8, 0 );
								}


					}
				}

			std::cout << "\nCorners count: " << cornersCount << "\n\n";

			for (int i = 0; i < cornersCount; i++)
				std::cout << "x  " << corners[i][0] << "    y  " << corners[i][1] << "\n";

			std::cout << "\n\n minX: " << minX << "  minY: "<< minY << "  maxX: "<< maxX << "  maxY: "<< maxY << "\n";

			cv::imwrite("out_img_2.png", _image_to_draw);


			bool v1 = false;
			bool v2 = false;
			bool v3 = false;
			bool v4 = false;
			bool borderError = false;
			cv::Mat out_img_4;
			out_img_4 = cv::imread("Borders/border_4_resized_2.jpg", CV_LOAD_IMAGE_COLOR);

			for(int i = 0; i < cornersCount; i++){

				if ((distance_testing(minX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(minY, corners[i][1]) < HANDICAP_CORNER)){
					v1 = true;
				}
				else if ((distance_testing(maxX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(minY, corners[i][1]) < HANDICAP_CORNER)){
					v2 = true;
				}

				else if ((distance_testing(minX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(maxY, corners[i][1]) < HANDICAP_CORNER)){
					v3 = true;
				}
				else if ((distance_testing(maxX, corners[i][0]) < HANDICAP_CORNER) && (distance_testing(maxY, corners[i][1]) < HANDICAP_CORNER)){
					v4 = true;
				}
				else{
					if (!((distance_testing(minX, corners[i][0]) < HANDICAP_ERROR)
						|| (distance_testing(maxX, corners[i][0]) < HANDICAP_ERROR)
						|| (distance_testing(minY, corners[i][1]) < HANDICAP_ERROR)
						|| (distance_testing(maxY, corners[i][1]) < HANDICAP_ERROR)))
						borderError = true;
						cv::circle(out_img_4, cv::Point(corners[i][0], corners[i][1]), 8,  cv::Scalar(0,0,255), 6, 8, 0 );

				}
			}


			//verify if there is a corner error
			if ((!v1) || (!v2) || (!v3) || (!v4)){
				//corner error
				//return 1;
				std::cout << "CORNER ERROR\n\n";
			}

			std::cout << "\n";
			cv::imwrite("out_img_error_2.png", out_img_4);

			if (borderError){
				//border error
				//return 1;
				std::cout << "BORDER ERROR\n\n";
			}


			//compute dimension
			int s =  (minX * minY) - (maxX * minY);
				s += (maxX * maxY) - (maxX * minY);
				s += (maxX * maxY) - (minX * maxY);
				s += (minX * minY) - (minX * maxY);
			int dimension =  s / 2;

			std::cout << "Dimension: " << dimension << "\n\n";

			if ((dimension < MIN_AREA) || (dimension > MAX_AREA)){
				//dimension error

				//return 1;
				std::cout << "DIMENSION ERROR\n\n";
			}


			ROI roi;
			roi.x1 = minX; roi.y1 = minY;
			roi.x2 = maxX; roi.y2 = minY;
			roi.x3 = minX; roi.y3 = maxY;
			roi.x4 = maxX; roi.y4 = maxY;

			return roi;
}

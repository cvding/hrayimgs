#include <stdio.h>
#include "hrayimgs.h"
#include "basedebug.h"
#include "Matrix.h"
#include "Shape.h"
#include "qrbound.h"
#include "hrayalgs.h"
#include "Model.h"

#include <iostream>

#pragma comment(lib, "basedebug.lib")

void test()
{
	std::ifstream in("feature.txt");
	Feature feat(20);
	int32_t label;
	feat.load(in,&label);

	std::cout << typeid(feat).hash_code();
}


#include <cstring>
#include <sstream>
int main()
{
	test();

	void *image = mvLoad("3pyd0.jpg", 1);
	MvsSize imgSize = mvGetSize(image);



	uint8_t *pImgBuf = new uint8_t[imgSize.width*imgSize.height];
	mvGetGrayBuf(image, imgSize.width*imgSize.height, pImgBuf);

	HRAYGray gray(imgSize.width, imgSize.height, pImgBuf);
	HRAYGray out;

	
	std::cout << "gray mean : " << gray.mean() << std::endl;
	Point2D<float> point(500, 500);
	Size2D<int32_t> size(501, 501);
	float angle[2];
	const float pi = 3.1415926f;
	angle[0] = pi / 4;
	angle[1] = 0;
	gray.roi(point, size, angle, out);
	
	MvsSize dstSize;
	dstSize.width = size.width;
	dstSize.height = size.height;
	mvSave2(dstSize, 1, out.data(), "haha.jpg");

	MvsPt2D head, tail;
	head.x = point.x - size.width / 2;
	head.y = point.y - size.height / 2;
	tail.x = point.x + size.width / 2;
	tail.y = point.y + size.height / 2;

	Matrix2D<int16_t> grad;
	gray.sgradx(grad);
	grad.thres(-10, 10);

	HRAYGray sml(gray.width(),gray.height());
	gray.gsmooth5x5(sml);

	GammaTabel tabel(1.0f,1.5f);
	HRAYGray gamma;
	sml.gamma(tabel, gamma);

	std::ofstream file("grad.csv");
	grad.save(file);
	file.close();

	mvDrawRect2(image, head, tail, angle[0], angle[1], { 0, 255, 0 }, 1);
	mvDrawRect(image, head, tail, { 255, 0, 0 }, 1);

	mvSave(image, "orgin.jpg");

	mvSave2(imgSize, 1, sml.data(), "sml.jpg");

	mvSave2(imgSize, 1, gamma.data(), "gamma.jpg");

	mvRelease(&image);
	delete[] pImgBuf;
	return 0;
}
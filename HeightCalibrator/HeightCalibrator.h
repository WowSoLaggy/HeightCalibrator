#pragma once

#ifndef HEIGHTCALIBRATOR_H
#define HEIGHTCALIBRATOR_H


#include "ErrCodes.h"
#include "Structs.h"


class HeightCalibrator
{
public:

	ErrCode Initialize(std::vector<Post> &pPosts);
	ErrCode GetHeight(PostImage &pTestPost, float &pHeight);
	ErrCode Dispose();

private:

	std::vector<Post> m_posts;
	LineF m_skyline;

	ErrCode Intersect_line_line(LineF pLine1, LineF pLine2, PointF &pResPoint);
	ErrCode LeastSquares(std::vector<PointF> &pPoints, LineF &pResLine);
};


#endif // HEIGHTCALIBRATOR_H

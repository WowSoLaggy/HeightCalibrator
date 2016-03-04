#include "stdafx.h"
#include "HeightCalibrator.h"


ErrCode HeightCalibrator::Initialize(std::vector<Post> &pPosts)
{
	ErrCode err;

	// General checks and initialization

	if (pPosts.size() < 3)
		return err_notEnoughPosts;

	m_posts = pPosts;
	std::vector<PointF> interPoints;
	interPoints.reserve(m_posts.size() * (m_posts.size() - 1) / 2);

	// Find all line-line intersections
	
	PointF ptRes;
	
	for (unsigned int j = 0; j < m_posts.size() - 1; ++j)
	{
		for (unsigned int i = j + 1; i < m_posts.size(); ++i)
		{
			err = Intersect_line_line(
				LineF(											// First line (bottoms)
					PointF(m_posts[i].BaseX, m_posts[i].BaseY),	//		First point
					PointF(m_posts[j].BaseX, m_posts[j].BaseY)	//		Second point
					),
				LineF(											// Second line (tops)
					PointF(m_posts[i].BaseX, m_posts[i].TopY),	//		First point
					PointF(m_posts[j].BaseX, m_posts[j].TopY)	//		Second point
					),
				ptRes);											// Result point

			if (err != err_noErr)
			{
				// No intersection or some other error. We don't care
				continue;
			}

			interPoints.push_back(ptRes);
		}
	}

	// Find the skyline

	err = LeastSquares(interPoints, m_skyline);
	if (err != err_noErr) return err;

	return err_noErr;
}


ErrCode HeightCalibrator::GetHeight(PostImage &pTestPost, float &pHeight)
{
	// Find the furthest post from the test post. Compare only Y-coord (depth)

	int maxDiffInd = 0;
	int maxDiff = abs(m_posts[0].BaseY - pTestPost.BaseY);
	for (unsigned int i = 1; i < m_posts.size(); ++i)
	{
		if (abs(m_posts[i].BaseY - pTestPost.BaseY) > maxDiff)
		{
			maxDiffInd = i;
			maxDiff = abs(m_posts[i].BaseY - pTestPost.BaseY);
		}
	}

	// Intersect line
	//		i-th post bottom
	//		test post bottom
	// with skyline

	PointF interPoint;
	Intersect_line_line(m_skyline,
		LineF(
			PointF(m_posts[maxDiffInd].BaseX, m_posts[maxDiffInd].BaseY),
			PointF(pTestPost.BaseX, pTestPost.BaseY)
			),
		interPoint);

	// Now find the required height via the triangle similarity

	float distToTestPost = sqrt(
		(pTestPost.BaseX - interPoint.X) * (pTestPost.BaseX - interPoint.X) +
		(pTestPost.BaseY - interPoint.Y) * (pTestPost.BaseY - interPoint.Y));

	float distToAnchorPost = sqrt(
		(m_posts[maxDiffInd].BaseX - interPoint.X) * (m_posts[maxDiffInd].BaseX - interPoint.X) +
		(m_posts[maxDiffInd].BaseY - interPoint.Y) * (m_posts[maxDiffInd].BaseY - interPoint.Y));

	pHeight = distToTestPost * m_posts[maxDiffInd].Height / distToAnchorPost * ((float)(m_posts[maxDiffInd].TopY - m_posts[maxDiffInd].BaseY) / (pTestPost.TopY - pTestPost.BaseY));

	return err_noErr;
}


ErrCode HeightCalibrator::Dispose()
{
	std::vector<Post>().swap(m_posts);

	return err_noErr;
}


ErrCode HeightCalibrator::Intersect_line_line(LineF pLine1, LineF pLine2, PointF &pResPoint)
{
	float x1 = pLine1.Pt1.X;
	float x2 = pLine1.Pt2.X;
	float x3 = pLine2.Pt1.X;
	float x4 = pLine2.Pt2.X;

	float y1 = pLine1.Pt1.Y;
	float y2 = pLine1.Pt2.Y;
	float y3 = pLine2.Pt1.Y;
	float y4 = pLine2.Pt2.Y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (d == 0)
		return err_noIntersect;

	float pre = (x1 * y2 - y1 * x2);
	float post = (x3 * y4 - y3 * x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	pResPoint.X = x;
	pResPoint.Y = y;

	return err_noErr;
}

ErrCode HeightCalibrator::LeastSquares(std::vector<PointF> &pPoints, LineF &pResLine)
{
	float sumX = 0;
	float sumXX = 0;
	float sumXY = 0;
	float sumY = 0;
	float sumYY = 0;

	for (unsigned int i = 0; i < pPoints.size(); ++i)
	{
		sumX += pPoints[i].X;
		sumXX += pPoints[i].X * pPoints[i].X;
		sumXY += pPoints[i].X * pPoints[i].Y;
		sumY += pPoints[i].Y;
		sumYY += pPoints[i].Y * pPoints[i].Y;
	}

	float denom = (pPoints.size() * sumXX - sumX * sumX);
	if (abs(denom) < std::numeric_limits<float>::epsilon())
		return err_singularMatrix;

	float a = (pPoints.size() * sumXY - sumX * sumY) / denom;
	float b = (sumY * sumXX - sumX * sumXY) / denom;

	pResLine.Pt1.X = 0;
	pResLine.Pt1.Y = a * pResLine.Pt1.X + b;

	pResLine.Pt2.X = 1000;
	pResLine.Pt2.Y = a * pResLine.Pt2.X + b;

	return err_noErr;
}
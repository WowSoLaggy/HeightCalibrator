#pragma once

#ifndef STRUCTS_H
#define STRUCTS_H


struct PointF
{
	PointF()
	{
		X = 0;
		Y = 0;
	}
	PointF(float pX, float pY)
	{
		X = pX;
		Y = pY;
	}
	PointF(int pX, int pY)
	{
		X = (float)pX;
		Y = (float)pY;
	}

	float X;
	float Y;
};


struct LineF
{
	LineF() { }
	LineF(PointF pPt1, PointF pPt2)
	{
		Pt1 = pPt1;
		Pt2 = pPt2;
	}

	PointF Pt1;
	PointF Pt2;
};


struct PostImage
{
	PostImage()
	{
		BaseX = 0;
		BaseY = 0;
		TopY = 0;
	}
	PostImage(int pBaseX, int pBaseY, int pTopY)
	{
		BaseX = pBaseX;
		BaseY = pBaseY;
		TopY = pTopY;
	}

	int BaseX;		// Post base point x-coordinate (image space)
	int BaseY;		// Post base point y-coordinate (image space)
	int TopY;		// Post top point y-coordinate (image space)
};


struct Post
{
	Post()
	{
		BaseX = 0;
		BaseY = 0;
		TopY = 0;
		Height = 0;
	}
	Post(int pBaseX, int pBaseY, int pTopY, float pHeight)
	{
		BaseX = pBaseX;
		BaseY = pBaseY;
		TopY = pTopY;
		Height = pHeight;
	}

	int BaseX;		// Post base point x-coordinate (image space)
	int BaseY;		// Post base point y-coordinate (image space)
	int TopY;		// Post top point y-coordinate (image space)

	float Height;	// Real post height (in meters or whatever)
};


#endif // STRUCTS_H

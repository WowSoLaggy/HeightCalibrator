#pragma once

#ifndef SIMPLETEST_H
#define SIMPLETEST_H


#include "HeightCalibrator.h"


class SimpleTest
{
public:

	void Run(std::string pImagePath, std::vector<Post> &pPosts, PostImage pTestPost);
};


#endif // SIMPLETEST_H

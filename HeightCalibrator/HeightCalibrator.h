#pragma once

#ifndef HEIGHTCALIBRATOR_H
#define HEIGHTCALIBRATOR_H


#include "ErrCodes.h"


class HeightCalibrator
{
public:

	ErrCode Initialize();
	ErrCode Dispose();
};


#endif // HEIGHTCALIBRATOR_H

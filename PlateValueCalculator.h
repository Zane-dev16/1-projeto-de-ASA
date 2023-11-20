#ifndef PLATEVALUECALCULATOR_H
#define PLATEVALUECALCULATOR_H

#include <vector>
#include "Plate.h"
#include "Piece.h"

class PlateValueCalculator {
    Plate plate;
    std::vector<Piece> pieces;
    std::vector<std::vector<int>> maxSubPlateValues;
    int subPlateLength;
    int subPlateWidth;

    int calculateVerticalBisectionValue(int slicePosition);

    int calculateHorizontalBisectionValue(int slicePosition);

    int calculateMaxBisectionValue();

    int getPieceValueWithSubPlateDimensions();

    int calculateMaxSubPlateValue();

public:
    PlateValueCalculator(Plate plate, std::vector<Piece> pieces);

    int calculateValue();
};

#endif // PLATEVALUECALCULATOR_H

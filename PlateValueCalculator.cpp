#include "PlateValueCalculator.h"
#include <iostream>

PlateValueCalculator::PlateValueCalculator(Plate plate, std::vector<Piece> pieces) {
    this->plate = plate;
    this->pieces = pieces;
}

int PlateValueCalculator::calculateVerticalBisectionValue(int slicePosition) {
    return maxSubPlateValues[subPlateLength][slicePosition] + maxSubPlateValues[subPlateLength][subPlateWidth - slicePosition];
}

int PlateValueCalculator::calculateHorizontalBisectionValue(int slicePosition) {
    return maxSubPlateValues[slicePosition][subPlateWidth] + maxSubPlateValues[subPlateLength - slicePosition][subPlateWidth];
}

int PlateValueCalculator::calculateMaxBisectionValue() {
    int maxValue = 0;
    int currValue;
    for (int verticalSlice = 1; verticalSlice < subPlateWidth; verticalSlice++) {
        currValue = calculateVerticalBisectionValue(verticalSlice);
        if (currValue > maxValue) {
            maxValue = currValue;
        }
    }

    for (int horizontalSlice = 1; horizontalSlice < subPlateLength; horizontalSlice++) {
        currValue = calculateHorizontalBisectionValue(horizontalSlice);
        if (currValue > maxValue) {
            maxValue = currValue;
        }
    }

    return maxValue;
}

int PlateValueCalculator::getPieceValueWithSubPlateDimensions() {
    for (Piece piece : pieces) {
        if ((piece.width == subPlateWidth && piece.length == subPlateLength) || (piece.width == subPlateLength && piece.length == subPlateWidth)) {
            return piece.value;
        }
    }
    return 0;
}

int PlateValueCalculator::calculateMaxSubPlateValue() {
    return std::max(getPieceValueWithSubPlateDimensions(), calculateMaxBisectionValue());
}

int PlateValueCalculator::calculateValue() {
    maxSubPlateValues = std::vector<std::vector<int>>(plate.length + 1, std::vector<int>(plate.width + 1, 0));
    for (subPlateLength = 1; subPlateLength <= plate.length; subPlateLength++) {
        for (subPlateWidth = 1; subPlateWidth <= plate.width; subPlateWidth++) {
            maxSubPlateValues[subPlateLength][subPlateWidth] = calculateMaxSubPlateValue();
            std::cout << maxSubPlateValues[subPlateLength][subPlateWidth];
        }
        std::cout << std::endl;
    }
    return maxSubPlateValues[plate.length][plate.width];
}

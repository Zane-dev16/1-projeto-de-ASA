#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Piece {
    int length;
    int width;
    int value;
};

struct Plate {
    int width;
    int length;
};

class PlateValueCalculator {
    Plate plate;
    vector<Piece> pieces;
    vector<vector<int>> maxSubPlateValues;
    int subPlateLength;
    int subPlateWidth;

    int subPlateIsSquare() {
        return subPlateLength == subPlateWidth;
    }

    int calculateVerticalBisectionValue(int slicePosition) {
        return maxSubPlateValues[subPlateLength][slicePosition] + maxSubPlateValues[subPlateLength][subPlateWidth - slicePosition];
    }

    int calculateHorizontalBisectionValue(int slicePosition) {
        return maxSubPlateValues[slicePosition][subPlateWidth] + maxSubPlateValues[subPlateLength - slicePosition][subPlateWidth];
    }

    int calculateMaxDirectionalBisectionValue(int (PlateValueCalculator::*calculateBisectionValue)(int), int sliceLimit) {
        int maxValue = 0;
        int currValue;

        for (int slicePosition = 1; slicePosition < sliceLimit/2; slicePosition++) {
            currValue = (this->*calculateBisectionValue)(slicePosition);

            if (currValue > maxValue) {
                maxValue = currValue;
            }
        }

        return maxValue;
    }

    int calculateMaxBisectionValue() {
        int maxValue = calculateMaxDirectionalBisectionValue(&PlateValueCalculator::calculateVerticalBisectionValue, subPlateWidth);

        if (!subPlateIsSquare()) {
            maxValue = max(maxValue, calculateMaxDirectionalBisectionValue(&PlateValueCalculator::calculateHorizontalBisectionValue, subPlateLength));
        }

        return maxValue;
    }

    int getPieceValueWithSubPlateDimensions() {
        for (Piece piece : pieces) {
            if (
                (piece.width == subPlateWidth && piece.length == subPlateLength) || 
                (piece.width == subPlateLength && piece.length == subPlateWidth) // peças podem girar
                ) {
                return piece.value;
            }
        }
        return 0;
    }

    bool rotatedSubPlateHasBeenCalculated() {
        return subPlateLength <= plate.width
            && subPlateLength > subPlateWidth;
    }

    int calculateMaxSubPlateValue() {
        if (rotatedSubPlateHasBeenCalculated()) {
            return maxSubPlateValues[subPlateWidth][subPlateLength];
        } else {
            return max(getPieceValueWithSubPlateDimensions(), calculateMaxBisectionValue());
        }
    }

    public:
        PlateValueCalculator(Plate plate, vector<Piece> pieces) {
            this->plate = plate;
            this->pieces = pieces;
        }

        int calculateValue() {
            maxSubPlateValues = vector<vector<int>>(plate.length + 1, vector<int>(plate.width + 1, 0));
            for (subPlateLength = 1; subPlateLength <= plate.length; subPlateLength++) {
                for (subPlateWidth = 1; subPlateWidth <= plate.width; subPlateWidth++) {
                    maxSubPlateValues[subPlateLength][subPlateWidth] = calculateMaxSubPlateValue();
                }
            }
            return maxSubPlateValues[plate.length][plate.width];
        }
};



Plate readPlate() {
    Plate plate;
    cin >> plate.length;
    cin.ignore();
    cin >> plate.width;
    return plate;
}

Piece readPiece() {
    Piece piece;
    cin >> piece.length >> piece.width >> piece.value;
    return piece;
}

vector<Piece> readPieces(int numPieces) {
    vector<Piece> pieces;
    for (size_t i = 0; i < numPieces; i++) {
        pieces.push_back(readPiece());
    }

    return pieces;
}

int main() {    
    int numPieces;
    Plate plate = readPlate();
    cin >> numPieces;
    vector<Piece> pieces = readPieces(numPieces);
    PlateValueCalculator plateValueCalculator(plate, pieces);
    cout << plateValueCalculator.calculateValue() << endl;
}

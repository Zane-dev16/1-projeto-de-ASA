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

    public:
        PlateValueCalculator(Plate plate, vector<Piece> pieces) {
            this->plate = plate;
            this->pieces = pieces;
        }

        int calculateVerticalBisectionValue(int slicePosition) {
            return maxSubPlateValues[subPlateLength][slicePosition] + maxSubPlateValues[subPlateLength][subPlateWidth - slicePosition];
        }

        int calculateHorizontalBisectionValue(int slicePosition) {
            return maxSubPlateValues[slicePosition][subPlateWidth] + maxSubPlateValues[subPlateLength - slicePosition][subPlateWidth];
        }

        int calculateMaxBisectionValue() {
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
                /* cout << horizontalSlice << "," << subPlateWidth << ":" << maxSubPlateValues[horizontalSlice][subPlateWidth] << "+" << maxSubPlateValues[subPlateLength - horizontalSlice][subPlateWidth] << " "; */
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

        int calculateMaxSubPlateValue() {
            return max(getPieceValueWithSubPlateDimensions(), calculateMaxBisectionValue());
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
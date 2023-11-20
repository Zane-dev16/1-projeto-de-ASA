#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Plate.h"
#include "Piece.h"
#include "PlateValueCalculator.h"

using namespace std;

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
    return 0;
}

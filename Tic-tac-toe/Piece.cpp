#pragma once

enum class PieceType{
    X,
    O, 
    N // N represents null basically 
};


// playing piece class to set the type of piece
class PlayingPiece{
public:
    PieceType piece;

    PlayingPiece(PieceType piece){
        this->piece = piece;
    }

};

// piece of type O
class PlayingPieceO:public PlayingPiece{
    public:
    PlayingPieceO():PlayingPiece(PieceType::O){}
};

// piece of type X
class PlayingPieceX:public PlayingPiece{
    public:
    PlayingPieceX():PlayingPiece(PieceType::X){}
};


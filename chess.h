#ifndef CHESS_H_
#define CHESS_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

//handle declarations
typedef struct ch_game_s* ch_game_h;
typedef struct ch_board_s* ch_board_h;
typedef struct ch_piece_s* ch_piece_h;

//enum definitions
typedef enum ch_piece_type_e {
  CH_DUMMY, //dummy piece for initialization
  CH_PAWN,
  CH_KING,
  CH_PIECE_MAX
} ch_piece_type_t;

typedef enum ch_color_e {
  CH_BLACK,
  CH_WHITE,
  CH_COLOR_MAX
} ch_color_t;

//in-game API

//internal API exposed for testing
ch_board_h ch_createBoard(uint8_t num_ranks, uint8_t num_files, size_t num_pieces);
void ch_destroyBoard(ch_board_h* board);

//getters
size_t ch_getNumPieces(ch_board_h board);


ch_piece_h ch_getPieceFromBoard(ch_board_h board, size_t index);

uint8_t ch_getPieceRank(ch_piece_h piece);
uint8_t ch_getPieceFile(ch_piece_h piece);
uint8_t ch_getPieceId(ch_piece_h piece);

ch_piece_type_t ch_getPieceType(ch_piece_h piece);
ch_color_t ch_getPieceColor(ch_piece_h piece);

bool ch_setPiece(ch_board_h board,
    uint8_t id, uint8_t rank, uint8_t file,
    ch_piece_type_t type, ch_color_t color);

#ifdef __cplusplus
}
#endif
#endif

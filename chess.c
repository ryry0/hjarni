#include <stdlib.h>
typedef struct ch_piece_s* ch_piece_t;
typedef struct ch_board_s* ch_board_t;

typedef enum ch_piece_type_e {
  CH_PAWN,
  CH_KING,
  CH_PIECE_MAX
} ch_piece_type_t;

typedef enum ch_color_e {
  CH_BLACK_PLAYER,
  CH_WHITE_PLAYER,
  CH_COLOR_MAX
} ch_color_t;

//files are columns
//ranks are rows

struct ch_piece_s {
  uint8_t rank;
  uint8_t file;

  uint8_t id;
  ch_piece_type_t type;
  ch_color_t color;

  bool has_moved;
  bool captured;
};

struct ch_board_s {
  uint8_t num_ranks;
  uint8_t num_files;

  size_t num_pieces;
  ch_piece_t pieces;
};

struct ch_game_s {
  //black score
  //white score
  //active player
  //bool finished
  struct ch_board_s board;
};

ch_initBoard(size_t num_pieces) {
  board->num_pieces = num_pieces;
  board->pieces = (ch_piece_t) malloc(num_pieces * sizeof (struct ch_piece_s))
}

ch_destroyBoard() {
  free(board->pieces);
}

/*
ch_addPieceToBoard() {
}
*/

/**
 * \brief initialize a chess piece
 *
 * \param piece The piece structure
 * \param row the initial row
 * \param col the initial column
 * \param id the id of the piece
 * \param type the type of the piece
 * \param color the color of the piece
 */

ch_initPiece(ch_piece_t piece,
    uint8_t rank, uint8_t file, uint8_t id,
    ch_piece_type_t type, ch_color_t color) {
  piece->type = type;
}

//parseNotation : string -> (id, move)
//

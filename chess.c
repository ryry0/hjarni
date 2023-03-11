#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//files are columns
//ranks are rows



//handle declarations
typedef struct ch_piece_s* ch_piece_h;
typedef struct ch_board_s* ch_board_h;

//enums
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

//structure definitions
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
  ch_piece_h pieces;
};

struct ch_game_s {
  //black score
  //white score
  //active player
  //bool finished
  struct ch_board_s board;
};

//forward declarations
void ch_initPiece(ch_piece_h piece,
    uint8_t rank, uint8_t file, uint8_t id,
    ch_piece_type_t type, ch_color_t color);

//function implementations
void ch_initBoard(ch_board_h board, size_t num_pieces) {
  board->num_pieces = num_pieces;
  board->pieces = (ch_piece_h) malloc(num_pieces * sizeof (struct ch_piece_s));
  //add a bunch of zero
  for (size_t i = 0; i < num_pieces; ++i) {
    ch_initPiece(&board->pieces[i], 0, 0, i, CH_DUMMY, CH_WHITE);
  }
}

void ch_destroyBoard(ch_board_h board) {
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

void ch_initPiece(ch_piece_h piece,
    uint8_t rank, uint8_t file, uint8_t id,
    ch_piece_type_t type, ch_color_t color) {
  piece->type = type;
}

//parseNotation : string -> (id, move)
//

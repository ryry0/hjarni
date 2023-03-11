#include <stdlib.h>
#include <stdbool.h>

//files are columns
//ranks are rows

#include <chess.h>


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
  uint32_t black_score;
  uint32_t white_score;
  ch_color_t active_player;
  bool game_finished;
  struct ch_board_s board;
};

//function implementations
ch_board_h ch_createBoard(size_t num_pieces) {
  ch_board_h board = (ch_board_h) malloc(sizeof (struct ch_board_s));

  board->num_pieces = num_pieces;
  board->pieces = (ch_piece_h) malloc(num_pieces * sizeof (struct ch_piece_s));

  //add a bunch of dummy pieces
  for (uint8_t i = 0; i < num_pieces; ++i) {
    ch_initPiece(&board->pieces[i], 0, 0, i, CH_DUMMY, CH_WHITE);
  }

  return board;
}

void ch_destroyBoard(ch_board_h* board) {
  free((*board)->pieces);
  (*board)->pieces = NULL;
  free(*board);
  *board = NULL;
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
  piece->rank = rank;
  piece->file = file;
  piece->type = type;
  piece->id = id;
  piece->color = color;
  piece->has_moved = false;
  piece->captured = false;
}

//parseNotation : string -> (id, move)
//getters
size_t ch_getNumPieces(ch_board_h board) {
  return board->num_pieces;
}

ch_piece_h ch_getPieceFromBoard(ch_board_h board, size_t index) {

  return &board->pieces[index];
}

uint8_t ch_getPieceRank(ch_piece_h piece) {
  return piece->rank;
}

uint8_t ch_getPieceFile(ch_piece_h piece) {
  return piece->file;
}

ch_piece_type_t ch_getPieceType(ch_piece_h piece) {
  return piece->type;
}

ch_color_t ch_getPieceColor(ch_piece_h piece) {
  return piece->color;
}

uint8_t ch_getPieceId(ch_piece_h piece) {
  return piece->id;
}

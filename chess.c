#include <stdlib.h>
#include <stdbool.h>

//files are columns
//ranks are rows
//both are 1-indexed.

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

//forward declarations
void ch_initPiece(ch_piece_h piece,
    uint8_t id, uint8_t rank, uint8_t file,
    ch_piece_type_t type, ch_color_t color);

//function implementations
/** creates a board and fills it with num_pieces dummy pieces */
ch_board_h ch_createBoard(uint8_t num_ranks, uint8_t num_files, size_t num_pieces) {
  ch_board_h board = (ch_board_h) malloc(sizeof (struct ch_board_s));

  board->num_ranks = num_ranks;
  board->num_files = num_files;

  board->num_pieces = num_pieces;
  board->pieces = (ch_piece_h) malloc(num_pieces * sizeof (struct ch_piece_s));

  //add a bunch of dummy pieces
  for (uint8_t i = 0; i < num_pieces; ++i) {
    ch_initPiece(&board->pieces[i], i, 0, 0, CH_DUMMY, CH_WHITE);
    //purposefully put to 0,0, which doesn't exist on the board.
  }

  return board;
}

/** deallocates the board */
void ch_destroyBoard(ch_board_h* board) {
  free((*board)->pieces);
  (*board)->pieces = NULL;
  free(*board);
  *board = NULL;
}

/** sets characteristics of a piece. */
bool ch_setPiece(ch_board_h board,
    uint8_t id, uint8_t rank, uint8_t file,
    ch_piece_type_t type, ch_color_t color) {

  if (id > board->num_pieces)
    return false;
  if ((rank == 0) ||
      (rank > board->num_ranks))
    return false;
  if ((file == 0) ||
      (file > board->num_files))
    return false;

  ch_piece_h piece = &board->pieces[id];

  piece->rank = rank;
  piece->file = file;
  piece->type = type;
  piece->color = color;

  return true;
}

bool ch_movePiece(ch_board_h board,
    uint8_t source_rank,
    uint8_t source_file,
    uint8_t dest_rank,
    uint8_t dest_file) {
  //determine if there is a piece at source rank and file
  //get the piece
  //check destination
  //move it according to the rules
  return false;
}

void ch_drawBoard(ch_board_h board) {
}

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
    uint8_t id, uint8_t rank, uint8_t file,
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

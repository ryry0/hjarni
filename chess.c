#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
  size_t turn_number;

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

ch_move_t ch_checkValidMove(ch_board_h board,
    uint8_t source_rank,
    uint8_t source_file,
    uint8_t dest_rank,
    uint8_t dest_file,
    ch_color_t active_color) {

  //check if source rank/file and dest rank/file are out of bounds

  if ((source_rank == 0) || (source_rank > board->num_ranks))
    return CH_INVALID_SOURCE;

  if ((source_file == 0) || (source_file > board->num_files))
    return CH_INVALID_SOURCE;

  if ((dest_rank == 0) || (dest_rank > board->num_ranks))
    return CH_INVALID_DESTINATION;

  if ((dest_file == 0) || (dest_file > board->num_files))
    return CH_INVALID_DESTINATION;

  if ((dest_file == source_file) && (dest_rank == source_rank))
    return CH_INVALID_DESTINATION;

  //determine if there is a piece at source rank and file
  ch_piece_h piece = ch_getPieceAtLocation(board, source_rank, source_file);

  if (piece == NULL) //if the piece doesn't exist
    return CH_NO_PIECE_AT_SOURCE;

  //if active color tries to move a piece of the other color
  if (piece->color != active_color)
    return CH_WRONG_COLOR;


  ch_piece_h dest_piece = ch_getPieceAtLocation(board, dest_rank, dest_file);

  //if destination piece exists
  if (dest_piece != NULL) {
    //if the colors match
    if (piece->color == dest_piece->color)
      return CH_SAME_COLOR_PIECE_AT_DESTINATION;
  } //handle captures later

  //move it according to the rules

  int16_t rank_difference = (int16_t)dest_rank - (int16_t)source_rank;
  int16_t file_difference = (int16_t)dest_file - (int16_t)source_file;
  //variable that takes into account directionality of the board
  int16_t bw_mod = (piece->color == CH_WHITE) ? 1 : -1;
  bool valid_move = false;

  switch(piece->type) {
    //or capture diagonally
    case CH_PAWN:
      //pawns can move one rank
      if ((rank_difference == bw_mod*1) && (file_difference == 0))
          valid_move = true;

      //pawns can move two rank - take into account round?
      else if ((piece->has_moved == false) &&
               (rank_difference == bw_mod*2) &&
               (file_difference == 0))
        valid_move = true;

      //pawns can capture diagonally
      else if ((dest_piece != NULL) &&
               (rank_difference == bw_mod*1) &&
               (abs(file_difference) == 1))
        valid_move = true;

      //pawns can en-passant
      //pawns can get promoted, can also promote and capture at same time
      break;

    //kings can move one square in any direction
    case CH_KING:
      if ((abs(rank_difference) == 1) && (abs(file_difference) == 1))
        valid_move = true;
      break;

    case CH_QUEEN:
      //if (abs(rank_difference) == abs(file_difference))
      //else if (file_difference == 0)
      //else if (rank_difference == 0)
    case CH_BISHOP:
      //if (abs(rank_difference) == abs(file_difference))
    case CH_ROOK:
      //if (file_difference == 0)
      //else if (rank_difference == 0)
    case CH_KNIGHT:
      //uhhh abs file == 3, abs rank == 2
      //abs file == 2, abs rank == 3
    case CH_DUMMY:
    case CH_PIECE_MAX:
    default:
      break;
  }

  if ((valid_move) && (dest_piece != NULL))
      return CH_CAPTURE;

  return valid_move ? CH_VALID_MOVE : CH_INVALID_MOVE;
}

void ch_movePiece(ch_piece_h piece, uint8_t rank, uint8_t file) {
  piece->rank = rank;
  piece->file = file;
  piece->has_moved = true;
}

void ch_capturePiece(ch_piece_h piece) {
  piece->captured = true;
  piece->rank = 0; //move off board
  piece->file = 0;
}

void ch_promotePiece(ch_piece_h piece, ch_piece_type_t new_type) {
  piece->type = new_type;
}

ch_move_t ch_moveParseSimpleNotation(ch_board_h board, char *str, ch_color_t active_color) {
  //assume file rank file rank, e.g. e1b2

  uint8_t source_file = str[0] - 'a' + 1;
  uint8_t source_rank = str[1];

  uint8_t dest_file = str[2] - 'a' + 1;
  uint8_t dest_rank = str[3];

  return ch_checkValidMove(board, source_rank, source_file, dest_rank, dest_file,
      active_color);
}

ch_piece_h ch_getPieceAtLocation(ch_board_h board, uint8_t rank, uint8_t file) {
  ch_piece_h piece = NULL;

  if ((rank == 0) || (file == 0))
    return piece;

  for (uint8_t i = 0; i < board->num_pieces; ++i) {
    if ((board->pieces[i].rank == rank) &&
        (board->pieces[i].file == file))
      piece = &board->pieces[i];
  }
  return piece;
}

#define RED "\e[0;31m"
#define RST "\e[0m"

void ch_drawBoard(ch_board_h board) {
  //remember rank and file are one indexed
  printf("\n");
  for (uint8_t rank = board->num_ranks; rank >= 1; --rank) {
    //print a bar
    for(uint8_t i = 1; i <= 4*board->num_files; ++i) printf("-");
    printf("-\n");

    for (uint8_t file = 1; file <= board->num_files; ++file) {
      char character = ' ';
      ch_color_t color = CH_WHITE;
      ch_piece_h piece = ch_getPieceAtLocation(board, rank, file);
      if (piece != NULL) {
        if (piece->captured == false) {
          switch (piece->type) {
            case CH_PAWN: character = 'p';
              break;
            case CH_KING: character = 'K';
              break;
            case CH_QUEEN: character = 'Q';
              break;
            case CH_BISHOP: character = 'B';
              break;
            case CH_ROOK: character = 'R';
              break;
            case CH_KNIGHT: character = 'N';
              break;

            case CH_DUMMY:
            case CH_PIECE_MAX:
            default:
              break;
          }
          color = piece->color;
        }
      }
      if (color == CH_BLACK)
        printf("| " RED "%c" RST " ", character);
      else
        printf("| %c ", character);
    }
    printf("| %d\n", rank);
  }

  //print bottom bar
  for(uint8_t i = 1; i <= 4*board->num_files; ++i) printf("-");
  printf("-\n");

  //print the bottom legend
  char letter = 'a';
  for (uint8_t file = 1; file <= board->num_files; ++file) {
    printf("  %c ", letter++);
  }
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

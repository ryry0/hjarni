
#include "CppUTest/TestHarness.h"
#include "chess.h"


TEST_GROUP(ChessSetupTeardownGroup)
{
};

TEST(ChessSetupTeardownGroup, create_and_destroy)
{

  uint8_t num_ranks = 8;
  uint8_t num_files = 4;
  size_t num_pieces = 10;
  ch_board_h board = ch_createBoard(num_ranks, num_files, num_pieces);
  CHECK(NULL != board);
  ch_destroyBoard(&board);
  POINTERS_EQUAL(NULL, board);
}


TEST(ChessSetupTeardownGroup, check_dummy_pieces)
{

  uint8_t num_ranks = 8;
  uint8_t num_files = 4;
  size_t num_pieces = 10;
  ch_board_h board = ch_createBoard(num_ranks, num_files, num_pieces);
  ch_piece_h piece;
  for (size_t i = 0; i < num_pieces; ++i) {
    piece = ch_getPieceFromBoard(board, i);
    CHECK_EQUAL_TEXT(ch_getPieceRank(piece), 0, "piece rank");
    CHECK_EQUAL_TEXT(ch_getPieceFile(piece), 0, "piece file");
    CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_DUMMY, "piece type");
    CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_WHITE, "piece color");
    CHECK_EQUAL_TEXT(ch_getPieceId(piece), i, "piece id");
  }
  ch_destroyBoard(&board);
}

TEST_GROUP(ChessSetPieceGroup)
{
  ch_board_h board;
  uint8_t num_ranks = 8;
  uint8_t num_files = 4;
  size_t num_pieces = 10;
  void setup() {
    board = ch_createBoard(num_ranks, num_files, num_pieces);
  }

  void teardown() {
    ch_destroyBoard(&board);
  }
};

TEST(ChessSetPieceGroup, set_piece_fail_id_out_of_bounds)
{
  uint8_t id = 20;
  uint8_t rank = 2;
  uint8_t file = 3;
  ch_piece_type_t type = CH_KING;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  CHECK_EQUAL(false, result);
}

TEST(ChessSetPieceGroup, set_piece_fail_rank_out_of_bounds)
{
  uint8_t id = 2;
  uint8_t rank = 9;
  uint8_t file = 3;
  ch_piece_type_t type = CH_KING;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  CHECK_EQUAL(false, result);

  result = ch_setPiece(board, id, 0, file, type, color);
  CHECK_EQUAL(false, result);
}

TEST(ChessSetPieceGroup, set_piece_fail_file_out_of_bounds)
{
  uint8_t id = 1;
  uint8_t rank = 2;
  uint8_t file = 5;
  ch_piece_type_t type = CH_KING;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  CHECK_EQUAL(false, result);

  result = ch_setPiece(board, id, rank, 0, type, color);
  CHECK_EQUAL(false, result);
}

TEST(ChessSetPieceGroup, set_piece_success)
{
  uint8_t id = 3;
  uint8_t rank = 2;
  uint8_t file = 3;
  ch_piece_type_t type = CH_KING;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  ch_piece_h piece = ch_getPieceFromBoard(board, id);

  CHECK_EQUAL(true, result);
  CHECK_EQUAL_TEXT(ch_getPieceRank(piece), rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(piece), file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_KING, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_BLACK, "piece color");

  //check all the other pieces to see if they're dummies

  for (size_t i = 0; i < num_pieces; ++i) {
    if (i == id) continue;
    piece = ch_getPieceFromBoard(board, i);
    CHECK_EQUAL_TEXT(ch_getPieceRank(piece), 0, "piece rank");
    CHECK_EQUAL_TEXT(ch_getPieceFile(piece), 0, "piece file");
    CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_DUMMY, "piece type");
    CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_WHITE, "piece color");
    CHECK_EQUAL_TEXT(ch_getPieceId(piece), i, "piece id");
  }

}

TEST(ChessSetPieceGroup, set_piece_pawn)
{
  uint8_t id = 3;
  uint8_t rank = 2;
  uint8_t file = 3;
  ch_piece_type_t type = CH_PAWN;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  ch_piece_h piece = ch_getPieceFromBoard(board, id);

  CHECK_EQUAL(true, result);
  CHECK_EQUAL_TEXT(ch_getPieceRank(piece), rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(piece), file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_PAWN, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_BLACK, "piece color");

  //check all the other pieces to see if they're dummies

  for (size_t i = 0; i < num_pieces; ++i) {
    if (i == id) continue;
    piece = ch_getPieceFromBoard(board, i);
    CHECK_EQUAL_TEXT(ch_getPieceRank(piece), 0, "piece rank");
    CHECK_EQUAL_TEXT(ch_getPieceFile(piece), 0, "piece file");
    CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_DUMMY, "piece type");
    CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_WHITE, "piece color");
    CHECK_EQUAL_TEXT(ch_getPieceId(piece), i, "piece id");
  }

}

TEST(ChessSetPieceGroup, set_piece_two_kings)
{
  uint8_t id = 3;
  uint8_t rank = 2;
  uint8_t file = 3;
  ch_piece_type_t type = CH_KING;
  ch_color_t color = CH_BLACK;

  bool result = ch_setPiece(board, id, rank, file, type, color);
  ch_piece_h piece = ch_getPieceFromBoard(board, id);

  CHECK_EQUAL(true, result);
  CHECK_EQUAL_TEXT(ch_getPieceRank(piece), rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(piece), file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_KING, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_BLACK, "piece color");

  //set the white king
  uint8_t white_id = 5;
  uint8_t white_rank = 1;
  uint8_t white_file = 4;
  ch_piece_type_t white_type = CH_KING;
  ch_color_t white_color = CH_WHITE;

  bool white_result = ch_setPiece(board, white_id, white_rank,
      white_file, white_type, white_color);

  ch_piece_h white_piece = ch_getPieceFromBoard(board, white_id);

  CHECK_EQUAL(true, white_result);
  CHECK_EQUAL_TEXT(ch_getPieceRank(white_piece), white_rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(white_piece), white_file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(white_piece), CH_KING, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(white_piece), CH_WHITE, "piece color");

  //check all the others to see if they're dummies
  for (size_t i = 0; i < num_pieces; ++i) {
    if (i == id) continue;
    if (i == white_id) continue;
    piece = ch_getPieceFromBoard(board, i);
    CHECK_EQUAL_TEXT(ch_getPieceRank(piece), 0, "piece rank");
    CHECK_EQUAL_TEXT(ch_getPieceFile(piece), 0, "piece file");
    CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_DUMMY, "piece type");
    CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_WHITE, "piece color");
    CHECK_EQUAL_TEXT(ch_getPieceId(piece), i, "piece id");
  }
}

TEST_GROUP(ChessGetPieceAtLocationGroup)
{
  ch_board_h board;
  uint8_t num_ranks = 8;
  uint8_t num_files = 4;
  size_t num_pieces = 10;

  uint8_t id = 3;
  uint8_t rank = 2;
  uint8_t file = 3;

  uint8_t white_id = 5;
  uint8_t white_rank = 1;
  uint8_t white_file = 4;

  void setup() {
    board = ch_createBoard(num_ranks, num_files, num_pieces);

    ch_piece_type_t type = CH_KING;
    ch_color_t color = CH_BLACK;

    ch_setPiece(board, id, rank, file, type, color);

    //set the white king
    ch_piece_type_t white_type = CH_KING;
    ch_color_t white_color = CH_WHITE;

    ch_setPiece(board, white_id, white_rank,
        white_file, white_type, white_color);
  }

  void teardown() {
    ch_destroyBoard(&board);
  }
};

TEST(ChessGetPieceAtLocationGroup, get_black_king)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, rank, file);

  CHECK_EQUAL_TEXT(ch_getPieceRank(piece), rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(piece), file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_KING, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_BLACK, "piece color");
}


TEST(ChessGetPieceAtLocationGroup, get_white_king)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, white_rank, white_file);

  CHECK_EQUAL_TEXT(ch_getPieceRank(piece), white_rank, "piece rank");
  CHECK_EQUAL_TEXT(ch_getPieceFile(piece), white_file, "piece file");
  CHECK_EQUAL_TEXT(ch_getPieceType(piece), CH_KING, "piece type");
  CHECK_EQUAL_TEXT(ch_getPieceColor(piece), CH_WHITE, "piece color");
}

TEST(ChessGetPieceAtLocationGroup, get_at_rank_0)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, 0, white_file);
  POINTERS_EQUAL(NULL, piece);
}

TEST(ChessGetPieceAtLocationGroup, get_at_file_0)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, white_rank, 0);
  POINTERS_EQUAL(NULL, piece);
}

TEST(ChessGetPieceAtLocationGroup, get_at_0_0)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, 0, 0);
  POINTERS_EQUAL(NULL, piece);
}

TEST(ChessGetPieceAtLocationGroup, get_at_empty)
{
  ch_piece_h piece = ch_getPieceAtLocation(board, 1, 1);
  POINTERS_EQUAL(NULL, piece);
}

TEST_GROUP(ChessDrawBoardGroup)
{
  ch_board_h board;
  uint8_t num_ranks = 8;
  uint8_t num_files = 8;
  size_t num_pieces = 10;

  uint8_t id = 3;
  uint8_t rank = 4;
  uint8_t file = 2;

  uint8_t white_id = 5;
  uint8_t white_rank = 1;
  uint8_t white_file = 4;

  void setup() {
    board = ch_createBoard(num_ranks, num_files, num_pieces);

    ch_piece_type_t type = CH_KING;
    ch_color_t color = CH_BLACK;

    ch_setPiece(board, id, rank, file, type, color);

    //set the white king
    ch_piece_type_t white_type = CH_KING;
    ch_color_t white_color = CH_WHITE;

    ch_setPiece(board, white_id, white_rank,
        white_file, white_type, white_color);

    ch_setPiece(board, 2, 2,
        1, CH_PAWN, color);
  }

  void teardown() {
    ch_destroyBoard(&board);
  }
};

TEST(ChessDrawBoardGroup, draw_board)
{
  //ch_drawBoard(board);
}

//todo: test if captured don't draw
TEST(ChessDrawBoardGroup, dont_draw_captured)
{
}

TEST_GROUP(ChessMoveGroup)
{
  ch_board_h board;
  uint8_t num_ranks = 8;
  uint8_t num_files = 8;
  size_t num_pieces = 10;

  uint8_t black_king_id = 1;
  uint8_t black_king_rank = 8;
  uint8_t black_king_file = 5;

  uint8_t black_pawn_id = 2;
  uint8_t black_pawn_rank = 7;
  uint8_t black_pawn_file = 3;

  uint8_t white_king_id = 3;
  uint8_t white_king_rank = 1;
  uint8_t white_king_file = 5;

  uint8_t white_pawn_id = 4;
  uint8_t white_pawn_rank = 2;
  uint8_t white_pawn_file = 2;

  void setup() {
    board = ch_createBoard(num_ranks, num_files, num_pieces);

    //set black pieces
    ch_setPiece(board, black_king_id, black_king_rank,
        black_king_file, CH_KING, CH_BLACK);

    ch_setPiece(board, black_pawn_id, black_pawn_rank,
        black_pawn_file, CH_PAWN, CH_BLACK);

    //set the white pieces
    ch_setPiece(board, white_king_id, white_king_rank,
        white_king_file, CH_KING, CH_WHITE);

    ch_setPiece(board, white_pawn_id, white_pawn_rank,
        white_pawn_file, CH_PAWN, CH_WHITE);
  }

  void teardown() {
    ch_destroyBoard(&board);
  }
};

TEST(ChessMoveGroup, dummy_test_draw_board_once)
{
  ch_drawBoard(board);
}

TEST(ChessMoveGroup, source_out_of_bounds)
{
  CHECK_EQUAL(CH_INVALID_SOURCE, ch_move(board,
      0,
      0,
      8,
      8,
      CH_WHITE));

  CHECK_EQUAL(CH_INVALID_SOURCE, ch_move(board,
      9,
      9,
      1,
      1,
      CH_WHITE));
}


TEST(ChessMoveGroup, destination_out_of_bounds)
{
  CHECK_EQUAL(CH_INVALID_DESTINATION, ch_move(board,
      1,
      1,
      0,
      0,
      CH_WHITE));

  CHECK_EQUAL(CH_INVALID_DESTINATION, ch_move(board,
      1,
      1,
      9,
      9,
      CH_WHITE));

  CHECK_EQUAL(CH_INVALID_DESTINATION, ch_move(board,
      1,
      1,
      1,
      1,
      CH_WHITE));
}


TEST(ChessMoveGroup, no_piece_at_source)
{
  CHECK_EQUAL(CH_NO_PIECE_AT_SOURCE, ch_move(board,
      1,
      1,
      2,
      2,
      CH_WHITE));
}


TEST(ChessMoveGroup, wrong_color)
{
  CHECK_EQUAL(CH_WRONG_COLOR, ch_move(board,
      black_king_rank,
      black_king_file,
      2,
      2,
      CH_WHITE));

  CHECK_EQUAL(CH_WRONG_COLOR, ch_move(board,
      white_king_rank,
      white_king_file,
      2,
      2,
      CH_BLACK));
}


TEST(ChessMoveGroup, same_color_piece_at_destination)
{
  CHECK_EQUAL(CH_SAME_COLOR_PIECE_AT_DESTINATION, ch_move(board,
      black_king_rank,
      black_king_file,
      black_pawn_rank,
      black_pawn_file,
      CH_BLACK));
}

TEST(ChessMoveGroup, white_pawn_moves)
{
  for (size_t i = 1; i <= num_ranks; ++i) {
    for (size_t j = 1; j <= num_files; ++j) {
      if ((i == white_pawn_rank + 1) && (j == white_pawn_file))
          continue;

      if ((i == white_pawn_rank + 2) && (j == white_pawn_file))
          continue;

      CHECK_EQUAL(CH_INVALID_MOVE, ch_move(board,
          white_pawn_rank,
          white_pawn_file,
          i,
          j,
          CH_WHITE));
    }
  }
}


//test
//capture, make sure it's off board
//
//pawn move one rank
//pawn move two rank
//pawn capture diagonally
//king move anywhere once

/*
TEST(PIDTestGroup, SecondTest) {
  //STRCMP_EQUAL("hello", "world");
  //LONGS_EQUAL(1, 2);
  //CHECK(false);
  //FAIL("Fail me!");
}
*/

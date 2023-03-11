
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

/*
TEST(PIDTestGroup, SecondTest) {
  //STRCMP_EQUAL("hello", "world");
  //LONGS_EQUAL(1, 2);
  //CHECK(false);
  //FAIL("Fail me!");
}
*/



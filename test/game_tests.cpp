
#include "CppUTest/TestHarness.h"
#include "chess.h"


TEST_GROUP(ChessSetupTeardownGroup)
{
};

TEST(ChessSetupTeardownGroup, create_and_destroy)
{

  size_t num_pieces = 10;
  ch_board_h board = ch_createBoard(num_pieces);
  CHECK(NULL != board);
  ch_destroyBoard(&board);
  POINTERS_EQUAL(NULL, board);
}


TEST(ChessSetupTeardownGroup, check_dummy_pieces)
{

  size_t num_pieces = 10;
  ch_board_h board = ch_createBoard(num_pieces);
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

/*
TEST(PIDTestGroup, SecondTest) {
  //STRCMP_EQUAL("hello", "world");
  //LONGS_EQUAL(1, 2);
  //CHECK(false);
  //FAIL("Fail me!");
}
*/



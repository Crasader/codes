/**
 * XiangQi Wizard Light - A Very Simple Chinese Chess Program
 * Designed by Morning Yellow, Version: 0.2, Last Modified: Mar. 2008
 * Copyright (C) 2004-2008 www.xqbase.com
 *
 * ����С��ʦ 0.2 ��Ŀ�꣺
 * һ��ʵ���й��������
 */

#include "PositionStruct.h"
#include "cocos2d.h"
USING_NS_CC;

namespace SimplePosition {

// Zobrist��
static struct {
  ZobristStruct Player;
  ZobristStruct Table[14][256];
} Zobrist;

// ��ʼ��Zobrist��
static void InitZobrist(void) {
  int i, j;
  RC4Struct rc4;

  rc4.InitZero();
  Zobrist.Player.InitRC4(rc4);
  for (i = 0; i < 14; i ++) {
    for (j = 0; j < 256; j ++) {
      Zobrist.Table[i][j].InitRC4(rc4);
    }
  }
}

void PositionStruct::ChangeSide(void) {         // �������ӷ�
	sdPlayer = 1 - sdPlayer;
	zobr.Xor(Zobrist.Player);
}

void PositionStruct::AddPiece(int sq, int pc) { // �������Ϸ�һö����
	ucpcSquares[sq] = pc;
	if (pc < 16) {
		vlWhite += cucvlPiecePos[pc - 8][sq];
		zobr.Xor(Zobrist.Table[pc - 8][sq]);
	} else {
		vlBlack += cucvlPiecePos[pc - 16][SQUARE_FLIP(sq)];
		zobr.Xor(Zobrist.Table[pc - 9][sq]);
	}
}

void PositionStruct::DelPiece(int sq, int pc) {         // ������������һö����
	ucpcSquares[sq] = 0;
	if (pc < 16) {
		vlWhite -= cucvlPiecePos[pc - 8][sq];
		zobr.Xor(Zobrist.Table[pc - 8][sq]);
	} else {
		vlBlack -= cucvlPiecePos[pc - 16][SQUARE_FLIP(sq)];
		zobr.Xor(Zobrist.Table[pc - 9][sq]);
	}
}

int FenPiece(int nArg) {
  switch (nArg) {
  case 'K':
    return PIECE_KING;
  case 'A':
    return PIECE_ADVISOR;
  case 'B':
  case 'E':
    return PIECE_BISHOP;
  case 'N':
  case 'H':
    return PIECE_KNIGHT;
  case 'R':
    return PIECE_ROOK;
  case 'C':
    return PIECE_CANNON;
  case 'P':
    return PIECE_PAWN;
  default:
    return 7;
  }
}

void PositionStruct::FromFen(const char *szFen) {
  int i, j, k;
  int pcWhite[7];
  int pcBlack[7];
  const char *lpFen;
  const char *move, *moves;
  int mv;

  InitZobrist();

  // FEN����ʶ��������¼������裺
  // 1. ��ʼ�����������
  pcWhite[0] = SIDE_TAG(0) + PIECE_KING;
  pcWhite[1] = SIDE_TAG(0) + PIECE_ADVISOR;
  pcWhite[2] = SIDE_TAG(0) + PIECE_BISHOP;
  pcWhite[3] = SIDE_TAG(0) + PIECE_KNIGHT;
  pcWhite[4] = SIDE_TAG(0) + PIECE_ROOK;
  pcWhite[5] = SIDE_TAG(0) + PIECE_CANNON;
  pcWhite[6] = SIDE_TAG(0) + PIECE_PAWN;
  for (i = 0; i < 7; i ++) {
    pcBlack[i] = pcWhite[i] + 8;
  }

  sdPlayer = 0;
  vlWhite = vlBlack = nDistance = 0;
  memset(ucpcSquares, 0, 256);
  zobr.InitZero();

  lpFen = szFen;
  if (*lpFen == '\0') {
    return;
  }
  // 2. ��ȡ�����ϵ�����
  i = RANK_TOP;
  j = FILE_LEFT;
  while (*lpFen != ' ') {
    if (*lpFen == '/') {
      j = FILE_LEFT;
      i ++;
      if (i > RANK_BOTTOM) {
        break;
      }
    } else if (*lpFen >= '1' && *lpFen <= '9') {
      j += (*lpFen - '0');
    } else if (*lpFen >= 'A' && *lpFen <= 'Z') {
      if (j <= FILE_RIGHT) {
        k = FenPiece(*lpFen);
		if (k < 7) {
          if (ucpcSquares[COORD_XY(j, i)] == 0) {
            AddPiece(COORD_XY(j, i), pcWhite[k]);
          }
        }
        j ++;
      }
    } else if (*lpFen >= 'a' && *lpFen <= 'z') {
      if (j <= FILE_RIGHT) {
        k = FenPiece(*lpFen + 'A' - 'a');
        if (k < 7) {
          if (ucpcSquares[COORD_XY(j, i)] == 0) {
            AddPiece(COORD_XY(j, i), pcBlack[k]);
          }
        }
        j ++;
      }
    }
    lpFen ++;
    if (*lpFen == '\0') {
      return;
    }
  }
  lpFen ++;
  // 3. ȷ���ֵ��ķ���
  if (*lpFen == 'b') {
    ChangeSide();
  }

  SetIrrev();

  // 4. get moves
  moves = strcasestr(lpFen, " moves ");
  if (moves == NULL)
      return;

  moves += strlen(" moves ");
  move = strtok((char *)moves, " ");
  while (move != NULL) {
      if (strlen(move) != 4)
          break;
      mv = toArrayMv(move);
      if (MakeMove(mv) == FALSE)
		  break;
      move = strtok(NULL, " ");
  }
}

int PositionStruct::toArrayMv(const char *mv)
{
  int sqSrc, sqDst;
  sqSrc = COORD_XY(mv[0]-'a'+FILE_LEFT, '9'-mv[1]+RANK_TOP);
  sqDst = COORD_XY(mv[2]-'a'+FILE_LEFT, '9'-mv[3]+RANK_TOP);
  return (IN_BOARD(sqSrc) && IN_BOARD(sqDst) ? MOVE(sqSrc, sqDst) : 0);
}

// ��һ���������
int PositionStruct::MovePiece(int mv) {
  int sqSrc, sqDst, pc, pcCaptured;
  sqSrc = SRC(mv);
  sqDst = DST(mv);
  pcCaptured = ucpcSquares[sqDst];
  if (pcCaptured != 0) {
    DelPiece(sqDst, pcCaptured);
  }
  pc = ucpcSquares[sqSrc];
  DelPiece(sqSrc, pc);
  AddPiece(sqDst, pc);
  return pcCaptured;
}

// ������һ���������
void PositionStruct::UndoMovePiece(int mv, int pcCaptured) {
  int sqSrc, sqDst, pc;
  sqSrc = SRC(mv);
  sqDst = DST(mv);
  pc = ucpcSquares[sqDst];
  DelPiece(sqDst, pc);
  AddPiece(sqSrc, pc);
  if (pcCaptured != 0) {
	  AddPiece(sqDst, pcCaptured);
  }
}

// ��һ����
BOOL PositionStruct::MakeMove(int mv) {
	int pcCaptured;
	DWORD dwKey;

	dwKey = zobr.dwKey;
	pcCaptured = MovePiece(mv);
	if (Checked()) {
		UndoMovePiece(mv, pcCaptured);
		return FALSE;
	}
	ChangeSide();
	mvsList[nMoveNum].Set(mv, pcCaptured, Checked(), dwKey);
	nMoveNum ++;
	nDistance ++;
	return TRUE;
}

// ���������߷�
int PositionStruct::GenerateMoves(int *mvs) const {
  int i, j, nGenMoves, nDelta, sqSrc, sqDst;
  int pcSelfSide, pcOppSide, pcSrc, pcDst;
  // ���������߷�����Ҫ�������¼������裺

  nGenMoves = 0;
  pcSelfSide = SIDE_TAG(sdPlayer);
  pcOppSide = OPP_SIDE_TAG(sdPlayer);
  for (sqSrc = 0; sqSrc < 256; sqSrc ++) {

    // 1. �ҵ�һ���������ӣ����������жϣ�
    pcSrc = ucpcSquares[sqSrc];
    if ((pcSrc & pcSelfSide) == 0) {
      continue;
    }

    // 2. ��������ȷ���߷�
    switch (pcSrc - pcSelfSide) {
    case PIECE_KING:
      for (i = 0; i < 4; i ++) {
        sqDst = sqSrc + ccKingDelta[i];
        if (!IN_FORT(sqDst)) {
          continue;
        }
        pcDst = ucpcSquares[sqDst];
        if ((pcDst & pcSelfSide) == 0) {
          mvs[nGenMoves] = MOVE(sqSrc, sqDst);
          nGenMoves ++;
        }
      }
      break;
    case PIECE_ADVISOR:
      for (i = 0; i < 4; i ++) {
        sqDst = sqSrc + ccAdvisorDelta[i];
        if (!IN_FORT(sqDst)) {
          continue;
        }
        pcDst = ucpcSquares[sqDst];
        if ((pcDst & pcSelfSide) == 0) {
          mvs[nGenMoves] = MOVE(sqSrc, sqDst);
          nGenMoves ++;
        }
      }
      break;
    case PIECE_BISHOP:
      for (i = 0; i < 4; i ++) {
        sqDst = sqSrc + ccAdvisorDelta[i];
        if (!(IN_BOARD(sqDst) && HOME_HALF(sqDst, sdPlayer) && ucpcSquares[sqDst] == 0)) {
          continue;
        }
        sqDst += ccAdvisorDelta[i];
        pcDst = ucpcSquares[sqDst];
        if ((pcDst & pcSelfSide) == 0) {
          mvs[nGenMoves] = MOVE(sqSrc, sqDst);
          nGenMoves ++;
        }
      }
      break;
    case PIECE_KNIGHT:
      for (i = 0; i < 4; i ++) {
        sqDst = sqSrc + ccKingDelta[i];
        if (ucpcSquares[sqDst] != 0) {
          continue;
        }
        for (j = 0; j < 2; j ++) {
          sqDst = sqSrc + ccKnightDelta[i][j];
          if (!IN_BOARD(sqDst)) {
            continue;
          }
          pcDst = ucpcSquares[sqDst];
          if ((pcDst & pcSelfSide) == 0) {
            mvs[nGenMoves] = MOVE(sqSrc, sqDst);
            nGenMoves ++;
          }
        }
      }
      break;
    case PIECE_ROOK:
      for (i = 0; i < 4; i ++) {
        nDelta = ccKingDelta[i];
        sqDst = sqSrc + nDelta;
        while (IN_BOARD(sqDst)) {
          pcDst = ucpcSquares[sqDst];
          if (pcDst == 0) {
              mvs[nGenMoves] = MOVE(sqSrc, sqDst);
              nGenMoves ++;
          } else {
            if ((pcDst & pcOppSide) != 0) {
              mvs[nGenMoves] = MOVE(sqSrc, sqDst);
              nGenMoves ++;
            }
            break;
          }
          sqDst += nDelta;
        }
      }
      break;
    case PIECE_CANNON:
      for (i = 0; i < 4; i ++) {
        nDelta = ccKingDelta[i];
        sqDst = sqSrc + nDelta;
        while (IN_BOARD(sqDst)) {
          pcDst = ucpcSquares[sqDst];
          if (pcDst == 0) {
            mvs[nGenMoves] = MOVE(sqSrc, sqDst);
            nGenMoves ++;
          } else {
            break;
          }
          sqDst += nDelta;
        }
        sqDst += nDelta;
        while (IN_BOARD(sqDst)) {
          pcDst = ucpcSquares[sqDst];
          if (pcDst != 0) {
            if ((pcDst & pcOppSide) != 0) {
              mvs[nGenMoves] = MOVE(sqSrc, sqDst);
              nGenMoves ++;
            }
            break;
          }
          sqDst += nDelta;
        }
      }
      break;
    case PIECE_PAWN:
      sqDst = SQUARE_FORWARD(sqSrc, sdPlayer);
      if (IN_BOARD(sqDst)) {
        pcDst = ucpcSquares[sqDst];
        if ((pcDst & pcSelfSide) == 0) {
          mvs[nGenMoves] = MOVE(sqSrc, sqDst);
          nGenMoves ++;
        }
      }
      if (AWAY_HALF(sqSrc, sdPlayer)) {
        for (nDelta = -1; nDelta <= 1; nDelta += 2) {
          sqDst = sqSrc + nDelta;
          if (IN_BOARD(sqDst)) {
            pcDst = ucpcSquares[sqDst];
            if ((pcDst & pcSelfSide) == 0) {
              mvs[nGenMoves] = MOVE(sqSrc, sqDst);
              nGenMoves ++;
            }
          }
        }
      }
      break;
    }
  }
  return nGenMoves;
}

// �ж��߷��Ƿ����
BOOL PositionStruct::LegalMove(int mv) const {
  int sqSrc, sqDst, sqPin;
  int pcSelfSide, pcSrc, pcDst, nDelta;
  // �ж��߷��Ƿ�Ϸ�����Ҫ�������µ��жϹ��̣�

  // 1. �ж���ʼ���Ƿ����Լ�������
  sqSrc = SRC(mv);
  pcSrc = ucpcSquares[sqSrc];
  pcSelfSide = SIDE_TAG(sdPlayer);
  if ((pcSrc & pcSelfSide) == 0) {
    return FALSE;
  }

  // 2. �ж�Ŀ����Ƿ����Լ�������
  sqDst = DST(mv);
  pcDst = ucpcSquares[sqDst];
  if ((pcDst & pcSelfSide) != 0) {
    return FALSE;
  }

  // 3. �������ӵ����ͼ���߷��Ƿ����
  switch (pcSrc - pcSelfSide) {
  case PIECE_KING:
    return IN_FORT(sqDst) && KING_SPAN(sqSrc, sqDst);
  case PIECE_ADVISOR:
    return IN_FORT(sqDst) && ADVISOR_SPAN(sqSrc, sqDst);
  case PIECE_BISHOP:
    return SAME_HALF(sqSrc, sqDst) && BISHOP_SPAN(sqSrc, sqDst) &&
        ucpcSquares[BISHOP_PIN(sqSrc, sqDst)] == 0;
  case PIECE_KNIGHT:
    sqPin = KNIGHT_PIN(sqSrc, sqDst);
    return sqPin != sqSrc && ucpcSquares[sqPin] == 0;
  case PIECE_ROOK:
  case PIECE_CANNON:
    if (SAME_RANK(sqSrc, sqDst)) {
      nDelta = (sqDst < sqSrc ? -1 : 1);
    } else if (SAME_FILE(sqSrc, sqDst)) {
      nDelta = (sqDst < sqSrc ? -16 : 16);
    } else {
      return FALSE;
    }
    sqPin = sqSrc + nDelta;
    while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {
      sqPin += nDelta;
    }
    if (sqPin == sqDst) {
      return pcDst == 0 || pcSrc - pcSelfSide == PIECE_ROOK;
    } else if (pcDst != 0 && pcSrc - pcSelfSide == PIECE_CANNON) {
      sqPin += nDelta;
      while (sqPin != sqDst && ucpcSquares[sqPin] == 0) {
        sqPin += nDelta;
      }
      return sqPin == sqDst;
    } else {
      return FALSE;
    }
  case PIECE_PAWN:
    if (AWAY_HALF(sqDst, sdPlayer) && (sqDst == sqSrc - 1 || sqDst == sqSrc + 1)) {
      return TRUE;
    }
    return sqDst == SQUARE_FORWARD(sqSrc, sdPlayer);
  default:
    return FALSE;
  }
}

// �ж��Ƿ񱻽���
BOOL PositionStruct::Checked() const {
  int i, j, sqSrc, sqDst;
  int pcSelfSide, pcOppSide, pcDst, nDelta;
  pcSelfSide = SIDE_TAG(sdPlayer);
  pcOppSide = OPP_SIDE_TAG(sdPlayer);
  // �ҵ������ϵ�˧(��)�����������жϣ�

  for (sqSrc = 0; sqSrc < 256; sqSrc ++) {
    if (ucpcSquares[sqSrc] != pcSelfSide + PIECE_KING) {
      continue;
    }

    // 1. �ж��Ƿ񱻶Է��ı�(��)����
    if (ucpcSquares[SQUARE_FORWARD(sqSrc, sdPlayer)] == pcOppSide + PIECE_PAWN) {
      return TRUE;
    }
    for (nDelta = -1; nDelta <= 1; nDelta += 2) {
      if (ucpcSquares[sqSrc + nDelta] == pcOppSide + PIECE_PAWN) {
        return TRUE;
      }
    }

    // 2. �ж��Ƿ񱻶Է�������(����(ʿ)�Ĳ�����������)
    for (i = 0; i < 4; i ++) {
      if (ucpcSquares[sqSrc + ccAdvisorDelta[i]] != 0) {
        continue;
      }
      for (j = 0; j < 2; j ++) {
        pcDst = ucpcSquares[sqSrc + ccKnightCheckDelta[i][j]];
        if (pcDst == pcOppSide + PIECE_KNIGHT) {
          return TRUE;
        }
      }
    }

    // 3. �ж��Ƿ񱻶Է��ĳ����ڽ���(������˧����)
    for (i = 0; i < 4; i ++) {
      nDelta = ccKingDelta[i];
      sqDst = sqSrc + nDelta;
      while (IN_BOARD(sqDst)) {
        pcDst = ucpcSquares[sqDst];
        if (pcDst != 0) {
          if (pcDst == pcOppSide + PIECE_ROOK || pcDst == pcOppSide + PIECE_KING) {
            return TRUE;
          }
          break;
        }
        sqDst += nDelta;
      }
      sqDst += nDelta;
      while (IN_BOARD(sqDst)) {
        int pcDst = ucpcSquares[sqDst];
        if (pcDst != 0) {
          if (pcDst == pcOppSide + PIECE_CANNON) {
            return TRUE;
          }
          break;
        }
        sqDst += nDelta;
      }
    }
    return FALSE;
  }
  return FALSE;
}

// �ж��Ƿ�ɱ
BOOL PositionStruct::IsMate(void) {
  int i, nGenMoveNum, pcCaptured;
  int mvs[MAX_GEN_MOVES];

  nGenMoveNum = GenerateMoves(mvs);
  for (i = 0; i < nGenMoveNum; i ++) {
    pcCaptured = MovePiece(mvs[i]);
    if (!Checked()) {
      UndoMovePiece(mvs[i], pcCaptured);
      return FALSE;
    } else {
      UndoMovePiece(mvs[i], pcCaptured);
    }
  }
  return TRUE;
}

// ����ظ�����
int PositionStruct::RepStatus(int nRecur) const {
  BOOL bSelfSide, bPerpCheck, bOppPerpCheck;
  const MoveStruct *lpmvs;

  bSelfSide = FALSE;
  bPerpCheck = bOppPerpCheck = TRUE;
  lpmvs = mvsList + nMoveNum - 1;
  while (lpmvs->wmv != 0 && lpmvs->ucpcCaptured == 0) {
	  if (bSelfSide) {
		  bPerpCheck = bPerpCheck && lpmvs->ucbCheck;
		  if (lpmvs->dwKey == zobr.dwKey) {
			  nRecur --;
			  if (nRecur == 0) {
				  return 1 + (bPerpCheck ? 2 : 0) + (bOppPerpCheck ? 4 : 0);
			  }
		  }
	  } else {
		  bOppPerpCheck = bOppPerpCheck && lpmvs->ucbCheck;
	  }
	  bSelfSide = !bSelfSide;
	  lpmvs --;
  }
  return 0;
}

};

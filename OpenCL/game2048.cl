#pragma OPENCL EXTENSION cl_arm_printf : enable
// game2048.cl
//
// OpenCL kernels to play the 2048 tile-sliding/growing game on parallel compute
//
// 1. slide() with locked[] all zeroed will tilt-bias the board toward slide_dir
// 2. coalesce() with the same array in unlocked[] "reacts" matching adjacents
// 3. slide() with the same array in locked[] does the final tilt-bias of a move
//
// the board is stored as a linear representation in row-major order, with zero-
// valued cells being "empty" such that a gravitational tilt will allow non-zero
// uphill tiles to slide into/past them
//
// for a global size of 4, game cells are indexed as follows:
//  0  1  2  3
//  4  5  6  7
//  8  9 10 11
// 12 13 14 15
// ...within board[], in global (by default) memory that all running kernels
// share although each works only within its row or column
//
// respectively left/right slides are represented as a slide_dir of -1 and +1,
// and up/down slides are represented as a slide_dir of -border-1 and +border+1

/*inline*/ void setInitialFinal(int *initial, int *final, int id, int n, int dir)
{
  *initial = id;
  if ((dir-1==0) || (dir+1==0)) { // slide within an nElement row
    *initial *= n;
  }
  if (dir > 0) {
    *final = *initial;
    *initial += dir*(n-1); // start at far end of row/col instead
  } else {
    *final = *initial - dir*(n-1); // adds a positive integer
  }
// printf("workitem %d goes from %d to %d step %d", id, *initial, *final, -dir);
}

int slide(
  __global int* board, // 4x4 number grid etc.
  int nElements, // how many must be processed in the dimension of the slide
  int slide_dir) // direction of slide, one of: <-1(U), -1(L), +1(R), >+1(D)
{
  int iInitial, iFinal, i, j;
  int moves = 0;
  
  setInitialFinal(&iInitial, &iFinal, get_global_id(0), nElements, slide_dir);
  for (i = iInitial, j = iInitial; i != iFinal - slide_dir; i -= slide_dir)
    if (board[i]) {
      if (i != j) {
        board[j] = board[i];
	moves++;
      }
      j -= slide_dir;
    }
  for (; j != iFinal - slide_dir; j -= slide_dir)
    board[j] = 0;

  return moves;
}

int coalesce(
  __global int* board, // 4x4 number grid etc.
  int nElements, // how many must be processed in the dimension of the slide
  int slide_dir, // direction of slide, one of: <-1(U), -1(L), +1(R), >+1(D)
  int log_rep) // true if cell values stored as logarithms, false if linear
{
  int iInitial, iFinal, i, j;
  int repeatSlide = 0;
  
  setInitialFinal(&iInitial, &iFinal, get_global_id(0), nElements, slide_dir);
  
  j = iInitial+slide_dir; // move in lock step, always one behind i
  for (i = iInitial; i != iFinal - slide_dir; i -= slide_dir, j -= slide_dir)
    if (board[i]) {
      if ((i != iInitial) && (board[i] == board[j])) {
        board[j] = log_rep ? (board[j] + 1) : (board[j] << 1);
        board[i] = 0;
        repeatSlide++;
      }
    } else
      break; // reached end of nonzero values
      
  return repeatSlide;
}

__kernel void tilt(
  __global int* board, // 4x4 number grid etc.
  int nElements, // how many must be processed in the dimension of the slide
  int slide_dir, // direction of slide, one of: <-1(U), -1(L), +1(R), >+1(D)
  int log_rep, // true if cell values stored as logarithms, false if linear
  __global int* errarr) // zero if any change as a result of slide() or coalesce()
{
  int myError;

  myError = slide(board, nElements, slide_dir) ? 0 : 1; // >0 slid means no error

  if (coalesce(board, nElements, slide_dir, log_rep)) {
    myError = 0; // also not an error if any coalesced into a new tile
    slide(board, nElements, slide_dir);
  }

  errarr[get_global_id(0)] = myError;
}

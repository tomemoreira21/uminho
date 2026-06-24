let board = [
  [0,0,0],
  [0,0,0],
  [0,0,0]
]

let player = true; // true -> X, false -> O
let gameStatus;
let gameOver = false;


document.addEventListener('DOMContentLoaded',() => {
  gameStatus = document.getElementById('game-status');
  gameStatus.textContent = "Jogador X";
  const boardElement = document.getElementById('board');
  const button = document.getElementById('reset');

  for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
      const slot = document.createElement('div');
      slot.className = 'slot';
      slot.addEventListener('click',(event) => slotClickHandler(event,i,j));

      boardElement.appendChild(slot);
    }
  }

  button.addEventListener('click',() => reset());
}) 

function slotClickHandler(event,i,j) {
  if (gameOver) {
    alert('O JOGO JÁ TERMINOU DÁ RESET PARA RECOMEÇAR');
    return;
  }

  if (board[i][j] !== 0) {
    alert("CÉLULA JÁ ESTÁ PREENCHIDA!");
    return;
  }

  board[i][j] = player ? 1 : -1;
  event.target.textContent = player ? 'X' : 'O';
  player = !player;
  gameStatus.textContent = `Jogador ${player ? 'X' : 'O'}`;

  checkGame();
}

function reset() {
  board = [
    [0,0,0],
    [0,0,0],
    [0,0,0]
  ]

  const slots = document.getElementsByClassName('slot');
  for (let slot of slots) {
    slot.textContent = '';
  }

  player = true;
  gameOver = false;
  gameStatus.textContent = "Jogador X";
}

function checkGame() {
  let result = 0;
  // 0 -> continua, 1 -> x venceu, 2 -> o venceu, 3 -> empatou

  // Verificar linhas e colunas
  for (let i = 0; i < 3; i++) {
    const rowSum = board[i][0] + board[i][1] + board[i][2] ;
    const colSum = board[0][i] + board[1][i] + board[2][i]; 

    if (rowSum === 3 || colSum === 3) result = 1;
    if (rowSum === -3 || colSum === -3) result = 2;
  }


  const diag1 = board[0][0] + board[1][1] + board[2][2]; 
  const diag2 = board[0][2] + board[1][1] + board[2][0]; 

  if (diag1 === 3 || diag2 === 3) result = 1;
  if (diag1 === -3 || diag2 === -3) result = 2;

  // Verificar empate
  if (result === 0 && board.flat().every(cell => cell !== 0)) result = 3; 

  // flat: [[]] -> []

  if (result > 0) {
    gameOver = true;
    if (result !== 3) {
      gameStatus.textContent = `Jogo terminado! - 
                      Ganharam as ${result === 1 ? 'cruzes' : 'bolas'}`;
    } else {
      gameStatus.textContent = 'Jogo terminado! - ficou Empatado';
    }
  }


}



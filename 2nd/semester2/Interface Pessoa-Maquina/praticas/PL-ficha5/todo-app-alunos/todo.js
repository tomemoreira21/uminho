const todos = [
  'Learn a new course',
  'Read a book',
  'Go to the gym',
  'Go shopping'
];


/*
DOMContentLoaded -> evento que é disparado quando 
o HTML da página é completamente carregado/processado
pelo browser

addEventListener -> função que fica à espera que ocorra
um determinado evento na DOM execuntado o código quando 
tal coisa ocorrer
*/

/* Ex. 1: Add a event listener that triggers when the DOM is loaded here */
document.addEventListener('DOMContentLoaded', () => {
  const listDate = document.getElementById('list-date');
  const today = new Date().toLocaleDateString();
  listDate.textContent = today;

  renderTodoList();
});


/* Ex. 2: Complete todo rendering */
// complete function to remove all child nodes
// arg parent is the node to clean
function removeAllChildNodes(parent) {
  while (parent.firstChild) {
    parent.firstChild.querySelector('button').removeEventListener('click',removeTodoItem);
    parent.removeChild(parent.firstChild);
  }
}


// render todo array here
function renderTodoList() {
  const todoList = document.getElementById('todo-list');

  removeAllChildNodes(todoList);
  todos.forEach ((todo) => {
    const todoItem = document.createElement('li'); 
    const todoParagraph = document.createElement('p'); 
    const todoButton = document.createElement('button'); 

    todoParagraph.textContent = todo;
    todoButton.textContent = 'Delete';
    todoButton.addEventListener('click',removeTodoItem);

    todoItem.appendChild(todoParagraph);
    todoItem.appendChild(todoButton);
    todoItem.classList.add('todo-list-item');

    todoList.appendChild(todoItem);
  })
}


/* Ex. 3: Add a event listener to element 'todo-form'*/
document.getElementById('todo-form').addEventListener('submit', event => {
    event.preventDefault();// evita o refresh 
    console.log('>>>> 1',todos);

    const taskInput = document.getElementById('task-input');
    const todoValue = taskInput.value.trim(); // limpa os espaços
    taskInput.value = '';

    if (todoValue === '') {
      return; // não adiciona se for vazio
    }

    if (todos.includes(todoValue)) {
      alert('Erro: Task ' + todoValue + ' already exists!');
      return;
    }


    todos.push(todoValue);
    renderTodoList();
});




/* Ex. 4 and 5: complete delete button click logic */
// arg event is the triggered event (with event you can get the element clicked).
function removeTodoItem(event) {
  const target = event.target; // botão clicado
  const listItem = target.parentNode; // <li> pai
  const todo = listItem.getElementsByTagName('p')[0].textContent; // texto interno
  const todoIndex = todos.indexOf(todo);

  if (todoIndex > -1) {
    todos.splice(todoIndex,1); // remove 1 elem da lista
    renderTodoList();
  }

}
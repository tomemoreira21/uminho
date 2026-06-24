const app = Vue.createApp({
  // armazena variáveis/estado
  data() {
    return {
      todos: [
        'Learn a new course',
        'Read a book',
        'Go to the gym',
        'Go shopping'
      ],
      today: new Date().toLocaleDateString(),
      enteredTodo: ''
    }
  },
  // funções usadas para manipular os dados
  // ex: responder a eventos, clicks ...
  methods: {
    submitTodo() {
        const todo = this.enteredTodo.trim();

        if (todo === '') {
          alert("Tarefa Vazia");
          return;
        }

        const exists = this.todos.some(t => t.toLowerCase() === todo);

        if (exists) {
          alert(`Essa tarefa ${todo} já está na tua lista`);
          return;
        }

        this.todos.push(todo);
        this.enteredTodo = '';
    },

    deleteTodo(index) {  
      this.todos.splice(index,1); // remove 1 elemento da posição index
      
      if (this.todos.length === 0) {
          alert("Parabéns acabaste de finalizar a tua última tarefa");
          return;
      }  
    },



  },
  // valores calculados com base no data (com cache)
  computed: {
    isDisabled() {
      return this.enteredTodo.trim() === '';
    }

  }



});

// comando que liga a aplicação ao HTML
app.mount('#app');
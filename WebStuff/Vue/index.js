//message binding
var app = new Vue({
    el: '#app',
    data: {
        message: 'Hello Vue!'
    }
})

//onHoverData
var app2 = new Vue({
    el: '#app-2',
    data: {
        message: 'You loaded this page on ' + new Date().toLocaleString()
    }
})

//Toggle elements with boolean(if statement)
var app3 = new Vue({
    el: '#app-3',
    data: {
        seen: true
    }
})

//For each Loop
var app4 = new Vue({
    el: '#app-4',
    data: {
        todos: [
            {text: 'Learn JavaScript'},
            {text: 'Learn Vue'},
            {text: 'Build something awesome'}
    ]
    }
})

//User input Button calling a Method
var app5 = new Vue({
  el: '#app-5',
  data: {
    message: 'Hello Vue.js!'
  },
  methods: {
    reverseMessage: function () {
      this.message = this.message.split('').reverse().join('')
    }
  }
})

//Update onChange
var app6 = new Vue({
  el: '#app-6',
  data: {
    all3sameName: 'Hello Vue!'
  }
})

//
Vue.component('todo-item', {
  props: ['todo'],
  template: '<li>{{ todo.text }}</li>'
})

var app7 = new Vue({
  el: '#app-7',
  data: {
    groceryList: [
      { id: 0, text: 'Vegetables' },
      { id: 1, text: 'Cheese' },
      { id: 2, text: 'Whatever else humans are supposed to eat' }
    ]
  }
})
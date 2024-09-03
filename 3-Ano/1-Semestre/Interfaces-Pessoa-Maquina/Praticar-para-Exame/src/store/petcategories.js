 
  const petcategories = {
  namespaced: true,
  state: {
    categories: [
    // {
    //"id":"1",
    //"name":"Dogs",
    //"description":"NULL",
    //"image":"NULL",
    //}
    ]
  },
  getters: {
    getCategories (state) {
      return state.categories;
    },   
  }, 
  mutations: {
    addCategories(state, categories){
        state.categories = categories
    },

    },
  actions: {
    async getCategoriesFromDB({commit}) {
            try {
                const response = await fetch('http://daw.deei.fct.ualg.pt/~a64514/PRACTICE/api/petcategories.php')
                const data = await response.json()
                console.log('received data:', data)                
                commit('addCategories', data)
                return true
            } 
            catch (error) {
                console.log('error: ', error)
                return false
            }
        },
  },
  modules: {
  }
}
export default 
    petcategories
  
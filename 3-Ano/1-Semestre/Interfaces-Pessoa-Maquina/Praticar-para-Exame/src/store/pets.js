 
  const pets = {
  namespaced: true,
  state: {
    pets: [
//      {
//        "cat_id":"1",
//        "cat_name":"Dogs",
//        "id":"1","name":"Max",
//        "description":"So full of life",
//        "status":"NULL",      
//        "image":"dg1.jpg"
//      },
    ]
  },
  getters: {
    getpets (state) {
      return state.pets;
    },
    getPetsByCat: (state) => (id) => {
      const results = state.pets.filter(p => {
          return p.cat_id == id;
      })
      return results
    },    
  }, 
  mutations: {
    addpets(state, pets){
        state.pets = pets
    },

    },
  actions: {
    async getPetsFromDB({commit}) {
            try {
                const response = await fetch('http://daw.deei.fct.ualg.pt/~a64514/PRACTICE/api/pets.php')
                const data = await response.json()
                console.log('received data:', data)                
                commit('addpets', data)
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
    pets
  const adoptions = {
  namespaced: true,
  state: {
    adoptions: 
    [
    //{
    //"id":"11",
    //"created_at":"2021-12-03 18:20:31", 
     //"pet_name":"Doggy",
     //"pet_image":"dg1.jpg",     
    //}
    ]
  },
  getters: {
    getadoptions (state) {
      return state.adoptions
    },   
  }, 
  mutations: {
    addadoptions(state, adoptions){
        state.adoptions = adoptions
    },
    newAdoption(state, order){
      state.adoptions = [order, ...state.adoptions]
    },
  },
  actions: {
    async getMyadoptionsFromDB({commit},id) {
            try {
                const response = await fetch(`http://daw.deei.fct.ualg.pt/~a64514/PRACTICE/api/adoptions.php?petlover_id=${id}`)
                const data = await response.json()
                console.log('received data:', data)                
                commit('addadoptions', data)
                return true
            } 
            catch (error) {
              console.log('error: ', error)
              return false
            }
        },
    async newAdoption({commit}, newAdoption) {         
          try {
              const response = await fetch('http://daw.deei.fct.ualg.pt/~a64514/PRACTICE/api/adoptions.php', {
                  method: 'POST',
                  body: JSON.stringify(newAdoption),
                  headers: { 'Content-type': 'text/html; charset=UTF-8' },
              })
              const data = await response.json()
              console.log('received data:', data)
              commit('newAdoption', data)
              return true
          } 
          catch (error) {
              console.error(error)
              return false
          }
      },     
  },
  modules: {
  }
}
export default 
    adoptions
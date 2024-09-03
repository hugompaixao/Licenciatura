import Vue from 'vue'
import Vuex from 'vuex'
import pets from './pets'
import petcategories from './petcategories'
import user from './user'
import adoptions from './adoptions'

Vue.use(Vuex)

export default new Vuex.Store({
  modules: {
    pets,
    petcategories,    
    user,
    adoptions
  }
 })

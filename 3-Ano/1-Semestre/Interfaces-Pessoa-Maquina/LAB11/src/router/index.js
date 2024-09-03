import Vue from 'vue'
import VueRouter from 'vue-router'
import  Home from '@/views/Home.vue'
import  Menu from '@/views/Menu.vue'
import  Basket from '@/views/Basket.vue'
import  Register from '@/views/Register.vue'
import  Login from '@/views/Login.vue'
import  MyOrders from '@/views/MyOrders.vue'
import  Message from '@/views/Message.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/home',
    component: Home
  },
  {
    path: '/',//menu',
    component: Menu
  }, 
  {
    path: '/basket',
    component: Basket
  }, 
  {
    path: '/register',
    component: Register
  },
  {
    path: '/login',
    component: Login
  }, 
  {
    path: '/myorders',
    component: MyOrders
  }, 
  {
    path: '/message',
    component: Message
  },        
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router

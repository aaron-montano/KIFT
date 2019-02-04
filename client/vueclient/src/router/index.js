import Vue from 'vue'
import Router from 'vue-router'
import Kift from '@/components/Kift'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Home'
    },
    {
      path: '/kift',
      name: 'Kift',
      component: Kift
    }
  ]
})

<template>
    <nav class="navbar navbar-expand-sm bg-dark">
        <ul class="navbar-nav">
            <li class="nav-item alert-link"><router-link to="/"><h7 style="color: white">Home</h7></router-link></li>
        </ul>
        <ul class="navbar-nav ml-auto" v-if="!userLoggedIn">
            <li class="nav-item"><router-link class="nav-link" to="/register"><h7 style="color: white">Sign up</h7></router-link></li>
            <li class="nav-item"><router-link class="nav-link" to="/login"><h7 style="color: white">Sign in</h7></router-link></li>
        </ul>
        <ul class="navbar-nav ml-auto" v-else>
            <li class="nav-item" @click.prevent="handleLogout"><router-link class="nav-link" to="#" id="logout-button"><h7 style="color: white">Logout</h7></router-link></li>
            <li class="nav-item"><router-link class="nav-link" to="#"><h7 style="color: white"> {{ user }} </h7></router-link></li>
            <li clas="nav-item"><i class="fa fa-shopping-cart" style="font-size:30px;color:white"><router-link class="nav-link" to="/basket"></router-link></i></li>
        </ul>
    </nav>
</template>

<script>

export default {
    data() {
		return {
            user: '',
		}
	},
    mounted() {
        this.user = localStorage.getItem('name')
        this.id = localStorage.getItem('id')
    },
    methods: {	
        handleLogout: async function () {
            await this.$store.dispatch('user/logoutUser', this.id)
            localStorage.setItem('message', 'See you soon ' + this.user+'!');
            localStorage.setItem('path', '/login');
            this.$router.push('/message')
        }
    },
    computed: {
        userLoggedIn: function () {
            let user = this.$store.getters['user/getUser']
            for (var i in user) return true
            return false
        },
    },
}

</script>  

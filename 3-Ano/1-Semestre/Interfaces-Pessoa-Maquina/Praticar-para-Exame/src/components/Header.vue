 <template>
	<header id="header">
		<div class="container main-menu">
			<div class="row align-items-center justify-content-between d-flex">
				<div id="logo">
					<router-link class="nav-link" to="/"><a><img src="@/assets/logo.png" alt="" title="" /></a></router-link>
				</div>
				<nav id="nav-menu-container">
				<ul class="nav-menu" v-if="!userLoggedIn">
					<li v-for="cat in petcategories" :key="cat.id">
						<router-link class="nav-link" :to="`/pets/${cat.id}`"><a>{{ cat.name }}</a></router-link>
					</li>					 
					<li><router-link class="nav-link" to="/register"><a>REGISTER</a></router-link></li>
					<li><router-link class="nav-link" to="/login"><a>LOGIN</a></router-link></li>					  
				</ul>
				<ul class="nav-menu" v-else>
					<li v-for="cat in petcategories" :key="cat.id">
						<router-link class="nav-link" :to="`/pets/${cat.id}`" @click.prevent="changepets"><a>{{ cat.name }}</a></router-link>
					</li>						 
					<li @click.prevent="handleLogout"><router-link class="nav-link" to="#"><a>LOGOUT</a></router-link></li>
					<li><router-link class="nav-link" to="/mypets"><a>MY PETS</a></router-link></li>						  
					<li><router-link class="nav-link" to="#"><a>WELCOME {{ user }}</a></router-link></li>						  
				</ul>
				</nav>		    		
			</div>
		</div>
	</header>
</template>

<script>
export default {
	data() {
		return {
			petcategories: [],
            user: '',
		}
	},
	
	mounted() {
		this.getCats();
		this.user = localStorage.getItem('name');
        this.id = localStorage.getItem('id');
	},

    methods: {
		async getCats() {
			if (await this.$store.dispatch('petcategories/getCategoriesFromDB')) {
				this.petcategories = this.$store.getters[('petcategories/getCategories')]
			}
		},

		handleLogout: async function () {
			this.$store.commit('user/logoutUser')
            localStorage.setItem('message', 'See you soon ' + this.user+'!');
            localStorage.setItem('path', '/login');
            this.$router.push('/message')
        },
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

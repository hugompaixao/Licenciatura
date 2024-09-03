 <template>
	<header id="header">
		<div class="header-top">
			<div class="container">
				<div class="row align-items-center">
					<div class="col-lg-6 col-sm-6 col-4 header-top-left no-padding">
						<div class="menu-social-icons">
							<a href="#"><i class="fa fa-facebook"></i></a>
							<a href="#"><i class="fa fa-twitter"></i></a>
							<a href="#"><i class="fa fa-dribbble"></i></a>
							<a href="#"><i class="fa fa-behance"></i></a>
						</div>	    				  					
					</div>
					<div class="col-lg-6 col-sm-6 col-8 header-top-right no-padding">
						<a class="btns" href="tel:+953 012 3654 896">+953 012 3654 896</a>
						<a class="btns" href="mailto:support@colorlib.com">support@colorlib.com</a>		
						<a class="icons" href="tel:+953 012 3654 896">
							<span class="lnr lnr-phone-handset"></span>
						</a>
						<a class="icons" href="mailto:support@colorlib.com">
							<span class="lnr lnr-envelope"></span>
						</a>		
					</div>
				</div>			  					
			</div>
		</div>
		<div class="container main-menu">
			<div class="row align-items-center justify-content-between d-flex">
				<router-link class="nav-link" to="/"><a><img src="@/assets/logo.png" alt="" title="" /></a></router-link>		
				<nav id="nav-menu-container">
					<ul class="nav-menu" v-if="userIsEmpty">
						<li><router-link class="nav-link" to="/"><a>Menu</a></router-link></li>
						<li><router-link class="nav-link" to="/register"><a>Register</a></router-link></li>
						<li><router-link class="nav-link" to="/login"><a>Login</a></router-link></li>
					</ul>
					<ul class="nav-menu" v-else>
						<li><router-link class="nav-link" to="/menu"><a>Menu</a></router-link></li>
						<li><router-link class="nav-link" to="#"><a>Welcome {{userName }}!</a></router-link></li>
						<li><router-link class="nav-link" to="/orders"><a>My Orders</a></router-link></li>
						<li @click.prevent="logout"><router-link class="nav-link" to="#"><a>Logout</a></router-link></li>
					</ul>
				</nav>	
			</div>
		</div>
	</header>
</template>

<script>


export default {
    methods: {
        logout() {
            this.$store.commit('user/logoutUser')
            localStorage.setItem('message', 'Bye, see you back soon!');
            this.$router.push('/message')
        }
    },
    computed: {
        userIsEmpty: function() {
            let obj = this.$store.getters['user/getUser']
            return Object.keys(obj).length === 0;
        },

        userName: function() {
            return this.$store.getters['user/getUser'].name
        }
    },
}


</script>  

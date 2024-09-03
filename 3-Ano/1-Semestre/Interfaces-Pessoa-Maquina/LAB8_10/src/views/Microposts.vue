<template >
	<body style="background-color: lightgrey">
		<Header />
		<nav class="navbar navbar-expand-sm bg-dark">
        <ul class="navbar-nav">
            <li class="nav-item alert-link">
                <router-link class="nav-link" to="/"><h4>Home</h4></router-link>
            </li>
        </ul>
        <ul class="navbar-nav ml-auto">
            <li class="nav-item">
                <router-link class="nav-link" to="/register"><h4>Register</h4></router-link>
            </li>
            <li class="nav-item">
                <router-link class="nav-link" to="/login"><h4>Login</h4></router-link>
            </li>
        </ul>
        <!--ul class="navbar-nav ml-auto">
            <li class="nav-item">
                <a class="nav-link" href="{{ path('index') }}"><h9 style="color: #ffffff">Welcome {{ name }}</h9></a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="{{ path('post') }}"><h9 style="color: #ffffff">New Post</h9></a>
            </li>
            <li class="nav-item">
                <a class="nav-link" href="{{ path('logout') }}"><h9 style="color: #ffffff">Logout</h9></a>
            </li>
        </ul-->
    </nav>
		<div id="carouselExampleIndicators" class="carousel slide" data-ride="carousel">
			<ol class="carousel-indicators">
				<li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
				<li data-target="#carouselExampleIndicators" data-slide-to="1"></li>
				<li data-target="#carouselExampleIndicators" data-slide-to="2"></li>
			</ol>
			<div class="carousel-inner" align="center">
				<div class="carousel-item active">
					<img class="d-block" src="@/assets/images/1.jpeg" width="640" height="360" alt="First slide">
				</div>
				<div class="carousel-item">
					<img class="d-block" src="@/assets/images/2.jpeg" width="640" height="360" alt="Second slide">
				</div>
				<div class="carousel-item">
					<img class="d-block" src="@/assets/images/3.jpeg" width="640" height="360" alt="Third slide">
				</div>
			</div>
			<a class="carousel-control-prev" href="#carouselExampleIndicators" role="button" data-slide="prev">
				<span class="carousel-control-prev-icon" aria-hidden="true"></span>
				<span class="sr-only">Previous</span>
			</a>
			<a class="carousel-control-next" href="#carouselExampleIndicators" role="button" data-slide="next">
				<span class="carousel-control-next-icon" aria-hidden="true"></span>
				<span class="sr-only">Next</span>
			</a>
			<br><br>
		</div>
		<div class="col-md-auto">
			<div class="container">
				<table class="table">
					<thead style="background-color: #34383c">
						<tr> 
							<th style="color: #ffffff">Post</th>
							<th style="color: #ffffff">Actor</th>
							<th style="color: #ffffff">Created</th>
							<th style="color: #ffffff">Updated</th>
						</tr>
					</thead>
					<tr v-for="micropost in microposts" :key="micropost.id"> 
						<td><a class="garamond text-dark"> {{ micropost.content }} </a></td>
						<td> {{ micropost.name }} </td>
						<td> {{ micropost.created_at }} </td>
						<td> {{ micropost.updated_at }} </td>
					</tr>					
				</table>
			</div>
		</div>
		<br><br>
		<Footer />
	</body>
</template>

<script>
import Header from '@/components/Header.vue'
import Footer from '@/components/Footer.vue'

export default {
	components: {
		Header,
		Footer
	},
	data() {
		return {
			microposts: [],
			comments: [],
			user: {
				id: '', 
				name: '', 
				email: '', 
				session_id: ''
			},
			show: '',
		}
	},
	mounted() {
		this.getMicroposts();
	},
	methods: {
		async getMicroposts() {
			if (await this.$store.dispatch('microposts/getMicroposts')) {
				this.microposts = this.$store.getters[('microposts/getMicroposts')]
			}
		}
	},
	computed: {

	}
}
</script>

<style scoped>

</style>
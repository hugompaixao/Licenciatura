<template>
	<body style="background-color: lightgrey">
		<Header />
		<nav class="navbar navbar-expand-sm bg-dark">
			<ul class="navbar-nav">
				<li class="nav-item">
					<router-link class="nav-link" to="/"><h4>Home</h4></router-link>
				</li>
			</ul>
			<ul class="navbar-nav ml-auto">
				<li class="nav-item">
					<router-link class="nav-link" to="/register"><h4>Register</h4></router-link>
				</li>
				<li class="nav-item alert-link">
					<router-link class="nav-link" to="/login"><h4>Login</h4></router-link>
				</li>
			</ul>
		</nav>
		<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
		<div class="container">
			<form @submit="onSubmit" id="frmLogin" method="post" accept-charset="utf-8" novalidate="novalidate">
				<div class="form-group" style="text-align: left">
					<label for="email">Email:</label>
					<input type="email" class="form-control" name="email" v-model="email" maxlength="255" placeholder="Email" data-msg-required="This field is required." data-msg-email="Email is invalid." autocomplete="email">
				</div>
				<br>
				<div class="form-group" style="text-align: left">
					<label for="usr">Password:</label>
					<input type="password" class="form-control" id="pwd" name="pwd" placeholder="Enter Password">
				</div>
				<br>
				<div align = "center">
					<button type="submit" class="btn btn-default text-white" name="submit" style="background-color: #000000">Login</button>
					<br><br>
					<a class="link" href=""><h9 style="color: blue">Forgot password?</h9></a>
					<a class="arial text-white"><h7 style="color: #000000">Remenber me? </h7><input type="checkbox" name="autologin" value="1"></a>
				</div>
			</form>
		</div>
		<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
		<Footer />
	</body>
</template>

<script>
import Header from '@/components/Header.vue'
import Footer from '@/components/Footer.vue'

export default {
	name: 'login',
	components: {
		Header,
		Footer
	},   
	data() {
      return {	
        user: {
			email: '',
			password: '',
        },
		submitting: false,
		error: false,
      }
    },
	
	methods: {

	},
	
	computed: {

	},
	directives: {

	},
	created() {

	}
}
</script>

<style scoped>

</style>
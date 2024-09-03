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
				<li class="nav-item alert-link">
					<router-link class="nav-link" to="register"><h4>Register</h4></router-link>
				</li>
				<li class="nav-item">
					<router-link class="nav-link" to="login"><h4>Login</h4></router-link>
				</li>
			</ul>
		</nav>
		<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
		<div class="container">
			<div class="form-group" style="text-align: left">
			<label for="usr">Name:</label>
				<input type="text" class="form-control" id="name" placeholder="Enter Name" name="name" value="">
			</div>
			<br>
			<div class="form-group" style="text-align: left">
				<label for="usr">Email:</label>
					<input type="email" class="form-control" id="email" placeholder="Enter Email" name="email" value="">
			</div>
			<br>
			<div class="form-group" style="text-align: left">
				<label for="usr">Password:</label>
					<input type="password" class="form-control" id="password" name="pwd" placeholder="Enter Password">
			</div>
			<br>
			<div class="form-group" style="text-align: left">
				<label for="usr">Confirm Password:</label>
					<input type="password" class="form-control" id="passwordconfig" name="pwdConfirm" placeholder="Enter Password">
			</div>
			<br>
			<div style="align-content: center">
				<button type="submit" class="btn btn-default text-white" name="submit" style="background-color: #000000">Register</button>
				<button type="reset" class="btn btn-default text-white" name="submit" style="background-color: #000000">Clear</button>
				&nbsp;&nbsp;&nbsp;
				<h9>Already have account?</h9>
				<router-link class="link" to="/login"><h9>Login</h9></router-link>
			</div>
		</div>
		<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
		<Footer />
	</body>
</template>

<script>
import Header from '@/components/Header.vue'
import Footer from '@/components/Footer.vue'

export default {
	name: 'register',
	components: {
		Header,
		Footer
	},
	data() {
      return {	
        user: {
			name: '',
			email: '',
			password: '',
        },
		passwordConfirmation: '',
		submitting: true,
		error: true,	
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
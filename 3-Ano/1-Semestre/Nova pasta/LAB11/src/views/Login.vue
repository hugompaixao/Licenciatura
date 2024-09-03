<template>
	<div>
		<Header />
		<br><br><br><br>
		<div class="center-div" id="login-form">
			<form @submit.prevent="onSubmit" accept-charset="utf-8" id="frmLogin" novalidate="novalidate">
				<input type="hidden" name="do_login" value="1">
				<div style="width: 400px;">
					<label for="email"><span class="wc-editable" data-pk="front_email" data-type="text">Email</span>:</label>
					<input type="email" placeholder="Email" class="form-control required" name="email" v-model="email" data-msg-required="This field is required." aria-required="true">
				</div>
				<br>
				<div>
					<label for="password"><span class="wc-editable" data-pk="ws_password" data-type="text">Password</span>:</label>
					<input type="password" class="form-control required" id="pws" name="password" v-model="password" maxlength="255" placeholder="Password" data-msg-required="This field is required" data-msg-pwd="Confirm password is invalid." aria-required="true">
				</div>
				<br>
				<div class="center-div">
					<p>
						<span class="wc-editable" data-pk="ws_do_not_account" data-type="text">Don't have an account?</span>
						<router-link class="cl-link" to="/register"><span class="wc-editable" data-pk="ws_create_new_account" data-type="text">Sign up</span></router-link>
					</p>
				</div>
				<div class="center-div">
					<button class="btn btn-primary" type="submit">
						<span class="wc-editable" data-pk="ws_btn_register" data-type="text">Login</span>
					</button>
				</div>
			</form>			
		</div>
		<Footer />
	</div>
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
		onSubmit: async function () {
			this.submitting = true;

			if (this.InvalidEmail) {
                alert('Please add a valid email')
                return
            }           
            if (this.InvalidPassword) {
                alert('Please add a password with at least 4 characters')
                return
            }
  
			console.log('data valid')

			const login = {
				email: this.email,
				password: this.password,
			}

			if (await this.$store.dispatch('user/loginUser', login)) {
				localStorage.setItem('message', 'Welcome back ' + this.$store.getters['user/getUser'].name + '!')
				localStorage.setItem('id', this.$store.getters['user/getUser'].session_id)
				localStorage.setItem('name', this.$store.getters['user/getUser'].name)
				localStorage.setItem('path', '/');
				this.$router.push('/message')
			}
		},
	},
	
	computed: {
		InvalidEmail: function () {
			if (this.email === '' || this.email.search('@')===-1) return true
			else return false
		},
        InvalidPassword: function () {
			if (this.password.length < 4 ) return true
			else return false
		},
	},

	directives: {

	},

	created: function () {


	}
}
</script>

<style scoped>
	.center-div {
		display: flex;
		justify-content: center;
		align-item: center;
	}
</style>



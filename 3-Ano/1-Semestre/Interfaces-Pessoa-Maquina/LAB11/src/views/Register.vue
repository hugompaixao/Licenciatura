<template>
	<div>
		<Header />
		<br><br><br><br>
		<div class="center-div" v-if="!userLoggedIn" id="register-form">
			<form @submit.prevent="onSubmit" accept-charset="utf-8" id="frmRegister" novalidate="novalidate">
				<input type="hidden" name="do_register" value="1">
				<div style="width: 400px;">
					<label for="name"><span class="wc-editable" data-pk="front_name" data-type="text">Name</span>:</label>
					<input text="text" placeholder="Name" class="form-control required" name="name" v-model="name" data-msg-required="This field is required." aria-required="true">
				</div>
				<br>
				<div>
					<label for="email"><span class="wc-editable" data-pk="front_email" data-type="text">Email</span>:</label>
					<input type="email" placeholder="Email" class="form-control required" name="email" v-model="email" data-msg-required="This field is required." aria-required="true">
				</div>
				<br>
				<div>
					<label for="password"><span class="wc-editable" data-pk="ws_password" data-type="text">Password</span>:</label>
					<input type="password" class="form-control required" id="pws" name="password" v-model="password" maxlength="255" placeholder="Password" data-msg-required="This field is required" data-msg-pwd="Confirm password is invalid." aria-required="true">
				</div>
				<br>
				<div>
					<label for="confirm_pswd">Confirm Password<span class="wc-editable" data-pk="ws_confirm_password"></span>:</label>
					<input type="password" class="form-control required" id="confirm_pswd" name="passwordConfirm" v-model="passwordConfirm" maxlength=255 placeholder="Confirm Password" data-msg-required="This field is required" data-msg-pwd="Confirm password is invalid." data-msg-confirm-pswd="Passwords do not match." aria-required="true">
				</div>
				<br>
				<div class="center-div">
					<p>
						<span class="wc-editable" data-pk="ws_do_not_account" data-type="text">Already have an account?</span>
						<router-link class="cl-link" to="/login"><span class="wc-editable" data-pk="ws_create_new_account" data-type="text">Login</span></router-link>
					</p>
				</div>
				<div class="center-div">
					<button class="btn btn-primary" type="submit"><span class="wc-editable" data-pk="ws_btn_register" data-type="text">Register</span></button>
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

			if (this.InvalidName) {
                alert('Please add a name with up to 15 characters')
                return
            }
            if (this.InvalidEmail) {
                alert('Please add a valid email')
                return
            }           
            if (this.InvalidPassword) {
                alert('Please add a password with at least 4 characters')
                return
            }
            if (this.InvalidPasswordConfirm) {
                alert('Passwords do not match')
                return
            }
  
			console.log('data valid')

			const newUser = {
				name: this.name,
				email: this.email,
				password: this.password,
			}

			if (!await this.$store.dispatch('user/userExists', newUser)) {
				await this.$store.dispatch('user/addUser')
				localStorage.setItem('message', 'Welcome ' + this.name+'! You can now login.');
				localStorage.setItem('path', '/login');
				this.$router.push('/message')
			} else {
				alert('Email already registed.')
				return
			}
		},
	},
	
	computed: {
		InvalidName: function () {
			if (this.name === '' || this.name.length > 15 || this.name.match(/[0-9]/g)!=null ) return true
			else return false
		},
		InvalidEmail: function () {
			if (this.email === '' || this.email.search('@')===-1) return true
			else return false
		},
        InvalidPassword: function () {
			if (this.password.length < 4 ) return true
			else return false
		},
        InvalidPasswordConfirm: function () {
			if (this.passwordConfirm != this.password ) return true
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

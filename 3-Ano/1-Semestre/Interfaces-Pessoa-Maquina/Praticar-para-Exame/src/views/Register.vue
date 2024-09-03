<template>
    <div>
        <Header />
        <section class="banner-area relative" id="home">	
            <div class="overlay overlay-bg"></div>
            <div class="container">				
                <div class="row d-flex align-items-center justify-content-center">
                    <div class="about-content col-lg-12">
                        <h1 class="text-white">
                            Register			
                        </h1>	
                    </div>	
                </div>
            </div>
        </section>
        <section class="Volunteer-form-area section-gap">
            <div class="container">					
                <div class="row justify-content-center">
                    <form class="col-lg-9" @submit.prevent="onSubmit" accept-charset="utf-8" id="frmRegister">
                        <div class="form-group">
                            <label for="first-name">Name</label>
						    <input type="text" class="form-control" placeholder="Name" v-model="name" required autofocus>
                        </div>
                        <div class="form-group">
                            <label for="email">Email Address</label>
                            <input type="email" class="form-control" placeholder="Valid email Address" v-model="email" required>
                        </div>	
                        <div class="form-row"> 							  	
                          <div class="col-6 mb-30">
                              <label for="password1">Password</label>
						   		<input type="password" class="form-control" placeholder="Password" v-model="password" required>
						  	</div>
						  	<div class="col-6 mb-30">
						  		<label for="password2">Confirm Password</label>
						   		<input type="password" class="form-control" placeholder="Repeat Password" v-model="passwordConfirm" required>						  		
						  	</div>
                        </div>								  
                        <button type="submit" class="primary-btn float-right">Submit</button>
                    </form>
                </div>
            </div>	
        </section>
        <Footer />
    </div>
</template>
<script>
import Footer from '@/components/Footer.vue'
import Header from '@/components/Header.vue'

export default {
    name: 'register',
    components: {
        Footer,
        Header
    },

    data() {
        return {
            name: '',
            email: '',
            password: '',
            passwordConfirm: '',        
        }
    },

    mounted() {

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

}
</script>
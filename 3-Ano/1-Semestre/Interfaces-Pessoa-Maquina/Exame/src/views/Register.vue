<template>
    <div>
        <Header />
        <section class="banner-area relative about-banner" id="home">	
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
        <section class="contact-page-area section-gap">
            <div class="container">
                <div class="row">
                    <div class="col-lg-12">
                        <form class="form-area contact-form text-right" id="myForm" @submit.prevent="onSubmit">
                            <div class="row">	
                                <div class="col-lg-6 form-group">
                                    <input v-model="name" name="name" placeholder="Enter your name" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Enter your name'" class="common-input mb-20 form-control" required="" type="text">
                                
                                    <input v-model="email" name="email" placeholder="Enter email address" pattern="[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,63}$" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Enter email address'" class="common-input mb-20 form-control" required="" type="email">

                                    <input v-model="password" name="password1" placeholder="Enter password" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Enter password'" class="common-input mb-20 form-control" required="" type="password">
                                    
                                    <input v-model="passwordConfirm" name="password2" placeholder="Repeat password" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Repeat password'" class="common-input mb-20 form-control" required="" type="password">
                                </div>
                                <div class="col-lg-12">
                                    <div class="alert-msg" style="text-align: left;"></div>
                                    <button  class="genric-btn primary" style="float: left;">Register</button>
                                </div>
                            </div>
                        </form>	
                    </div>
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
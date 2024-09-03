<template>
    <div>
        <Header />
        <section class="banner-area relative" id="home">	
            <div class="overlay overlay-bg"></div>
            <div class="container">				
                <div class="row d-flex align-items-center justify-content-center">
                    <div class="about-content col-lg-12">
                        <h1 class="text-white">
                            Login			
                        </h1>	
                    </div>	
                </div>
            </div>
        </section>
        <section class="Volunteer-form-area section-gap">
            <div class="container">		
                <div class="row justify-content-center">
                    <form class="col-lg-9" @submit.prevent="onSubmit" accept-charset="utf-8">
                        <div class="form-row"> 							  	
                            <div class="col-6 mb-30">
                                <label for="email">Email</label>
                                <input type="email" class="form-control" placeholder="Enter a valid email" v-model="email" required>
                            </div>
                            <div class="col-6 mb-30">
                                <label for="password">Password</label>
                                <input type="password" class="form-control" placeholder="Enter Password" v-model="password" required>						  		
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
    name: 'login',
    components: {
        Footer,
        Header
    },
    data() {
        return {
            email: '',
            password: '', 
            alertMessageStyle: 'display:none;'      
        }
    },
    mounted() {

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
				localStorage.setItem('path', '/pets/1');
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
}
</script>
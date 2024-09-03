<template>
    <div>  
        <Header />
        <section class="banner-area relative about-banner" id="home">	
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
			<section class="contact-page-area section-gap">
				<div class="container">
					<div class="row">
						<div class="col-lg-12">
							<form class="form-area contact-form text-right" id="myForm" @submit.prevent="onSubmit">
								<div class="row">	
									<div class="col-lg-6 form-group">
										<input v-model="email" name="email" placeholder="Enter email address" pattern="[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,63}$" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Enter email address'" class="common-input mb-20 form-control" required="" type="email">
										<input v-model="password" name="password" placeholder="Enter password" onfocus="this.placeholder = ''" onblur="this.placeholder = 'Enter password'" class="common-input mb-20 form-control" required="" type="password">
									</div>
									<div class="col-lg-12">
										<div class="alert-msg" style="text-align: left;"></div>
										<button  class="genric-btn primary" style="float: left;">Login</button>
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
				localStorage.setItem('path', '/menu');
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
<template>
	<div>
		<header id="header">
			<div class="container main-menu">
				<div class="row align-items-center justify-content-between d-flex">
					<div id="logo">
						<router-link to="/"><a><img src="assets/logo.png" alt="" title="" /></a></router-link>
					</div>
					<nav id="nav-menu-container">
					</nav>		    		
				</div>
			</div>
		</header>
		<section class="banner-area relative about-banner" id="home">	
			<div class="container">				
				<div class="row d-flex align-items-center justify-content-center">
					<div class="about-content col-lg-12">
						<h1 class="text-white">
							{{ message }}		
						</h1>	
					</div>	
				</div>
			</div>
		</section>
		<Footer />
	</div>
</template>

<script>
import Footer from '@/components/Footer.vue'

export default {
    components: {
        Footer
    },

    data() {
		return {
            message: '',
		}
	},   
	
    mounted() {
		this.message = localStorage.getItem('message')
        let path = localStorage.getItem('path')
        var timeleft = 3;
        var downloadTimer = setInterval(() => {
			if(timeleft <= 0){
				clearInterval(downloadTimer);
				this.$router.push(path)
			}
			timeleft -= 1;
        }, 1000);
	},
}
</script>

<style scoped>
</style>




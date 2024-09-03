<template>
	<div> 
		<Header />
		<section class="banner-area relative" id="home">	
			<div class="overlay overlay-bg"></div>
			<div class="container">				
				<div class="row d-flex align-items-center justify-content-center">
					<div class="about-content col-lg-12">
						<h1 class="text-white">
							My pets !				
						</h1>
					</div>	
				</div>
			</div>
		</section>
		<section class="cat-list-area section-gap">
			<div class="container">
				<div class="media" v-for="adopt in adoptions" :key="adopt.id">
					<div class="media-left">
						<img :src="require(`@/assets/${adopt.pet_image}`)" alt="" class="img-fluid">
					</div>
					<div class="media-body">
						<h3 class="mb-30">&nbsp;I am {{ adopt.pet_name }}!</h3>
						<h4 class="media-heading">&nbsp;{{ adopt.pet_description }}</h4>
						<br><p>I was adopted {{ adopt.created_at }}</p>
					</div>
				</div>
				<br>
			</div>	
		</section>
		<Footer />
	</div>
</template>

<script>
import Footer from '@/components/Footer.vue'
import Header from '@/components/Header.vue'

export default {
	name: 'dishes',
    components: {
		Footer,
        Header
	},
	data() {
		return {
			adoptions: [],
		}
	},
	mounted() {
		this.getMyPets();
	},

	methods: {      
 		async getMyPets() {
			console.log(this.$store.getters['user/getUser'].id)
			console.log(await this.$store.dispatch('adoptions/getMyadoptionsFromDB', this.$store.getters['user/getUser'].id))
			if (await this.$store.dispatch('adoptions/getMyadoptionsFromDB', this.$store.getters['user/getUser'].id)) {
				this.adoptions = this.$store.getters[('adoptions/getadoptions')]
			}

		},
	},
	
    computed: {

    },
}
</script>

<style scoped>
</style>
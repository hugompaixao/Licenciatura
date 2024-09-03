<template>
<div>


  
<Header />








<Footer />

</div>
</template>

<script>
import Footer from '@/components/Footer.vue'
import Header from '@/components/Header.vue'

export default {
	name: 'products',
    components: {
		Footer,
        Header
	},
	data() {
		return {
		}
	},
	mounted() {
	},
	methods: {
	
	},
    computed: {

    },
}
</script>

<style scoped>
</style>
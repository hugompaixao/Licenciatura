<template>
    <div>
        <Header />
            <section class="banner-area relative about-banner" id="home">	
				<div class="overlay overlay-bg"></div>
				<div class="container">				
					<div class="row d-flex align-items-center justify-content-center">
						<div class="about-content col-lg-12">
							<h1 class="text-white">
								Menu List				
							</h1>	
						</div>	
					</div>
				</div>
			</section>
			<section class="menu-list-area section-gap">
				<div class="container">
					<div class="row">
						<div class="menu-cat mx-auto">
							<ul class="nav nav-pills" id="pills-tab" role="tablist">
                                <li class="nav-item" v-for="cat in categories" :key="cat.id">
                                    <router-link class="nav-link" to="#"><a class="nav-link active" id="pizza-tab" data-toggle="pill" role="tab" aria-controls="pizza" aria-selected="true">{{ cat.name }}</a></router-link>
                                </li>						  
							</ul>							
						</div>
					</div>
                    <div id="pills-tabContent" class="tab-content absolute" v-for="product in products" :key="product.id">
						<div class="tab-pane fade show active">
							<div class="single-menu-list row justify-content-between align-items-center">
								<div class="col-lg-9">
									<a href="#"><h4>{{ product.name }}</h4></a>
									<p>
										{{ product.description }}
									</p>
								</div>
								<div class="col-lg-3 flex-row d-flex price-size">
									<div class="s-price col">
										
										<span>${{ product.price }}</span> <br />
										<a v-if="userLoggedIn" @click.prevent="order(product.id, product.price)" class="genric-btn info-border circle arrow">Order<span class="lnr lnr-arrow-right"></span></a>
									</div>
																		
								</div>
							</div>	
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

    components: {
        Footer,
        Header
    },
  

    data() {
        return {
            products: [],
            categories: [],
        }
    },
    mounted() {
        this.getCategories();
        this.getProducts();
    },

    methods: {
        async getCategories() {
            if (await this.$store.dispatch('categories/getCategoriesFromDB')) {
                this.categories = this.$store.getters[('categories/getCategories')]
            }
        },

        async getProducts() {
            if (await this.$store.dispatch('products/getProductsFromDB')) {
                this.products = this.$store.getters[('products/getProducts')]
            }
        },

        order: async function(product, product_price) {

            const purches = {
                customer_id: this.$store.getters['user/getUser'].id,
                product_id: product,
                product_price: product_price,
            }

            console.log("User ID:" + this.$store.getters['user/getUser'].id)
            console.log("Product ID:" + product)
            console.log("Price:" + product_price)

            await this.$store.dispatch('orders/newOrder', purches)
            localStorage.setItem('message', 'Success!');
            localStorage.setItem('path', '/orders');
            this.$router.push('/message')
         },
    },
    computed: {
        userLoggedIn: function () {
            let user = this.$store.getters['user/getUser']
            for (var i in user) return true
            return false
        },
    },    
}
</script>

<style scoped>
.thumbwrap {
    position:relative;
}

.thumb span { 
    position:absolute;
    visibility:hidden;
}
.thumb:hover, .thumb:hover span { 
    visibility:visible;
    top:-30px;
    left:-35px; 
    z-index:1;
}
</style>
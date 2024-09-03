<template>
	<div>
		<Header />
		<div>
			<div class="center-div">
				<img class="d-block" src="@/assets/images/store.jpg" width="640" height="360">
			</div>
			<div class="center-div">
                <div class="d-flex flex-row flex-wrap my-flex-container" style="width: 890px; ">
                        <div class="p-2 my-flex-item" v-for="product in products" :key="product.id">
							<div class="card" style="width: 205px; height: 370px; padding-top: 10px;">
								<img :src="require(`@/assets/images/${product.image}`)" class="img-fluid" width="142px" height="205px" style="margin: auto;">
                                <div class="card-body">
                                    <div class="fixed-container-1">
                                        <h6 class="card-title mt-auto">{{product.name}} - {{product.description}}</h6>
                                    </div>
                                    <div class="fixed-container-2 center-div">
                                        <p class="card-text mt-auto">{{product.price}}€</p>
                                    </div>
									<div class="fixed-container-2 center-div" v-if="userLoggedIn">
										<button class="card-text mt-auto" style="width: 205px;">Add to Cart</button>
                                    </div>
                                </div>
                            </div>
                        </div>
					</div>
                </div>
            </div>
			<br><br>
		<Footer />
	</div>
</template>

<script>
import Header from '@/components/Header.vue'
import Footer from '@/components/Footer.vue'


export default {
    showModal: true,
    components: {
		Header,
		Footer
	},
	data() {
		return {
		products: [],
		}
	},
	mounted() {
		this.getProducts();
	},
	methods: {
		async getProducts() {
			if (await this.$store.dispatch('products/getProductsFromDB')) {
				this.products = this.$store.getters[('products/getProducts')]
			}
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
	.center-div {
		display: flex;
		justify-content: center;
		align-item: center;
	}
</style>

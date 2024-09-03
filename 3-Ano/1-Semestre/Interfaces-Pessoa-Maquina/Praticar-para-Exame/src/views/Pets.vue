<template>
    <div>
        <Header />
        <section class="banner-area relative" id="home">	
            <div class="overlay overlay-bg"></div>
            <div class="container">				
                <div class="row d-flex align-items-center justify-content-center">
                    <div class="about-content col-lg-12">
                        <h1 class="text-white" v-if="pet_category == 1">
                            Dogs				
                        </h1>
                        <h1 class="text-white" v-else>
                            Cats				
                        </h1>
                    </div>	
                </div>
            </div>
        </section>
        <section class="cat-list-area section-gap">
            <div class="container">
                <div class="row">
                    <div class="col-lg-3 col-md-6" v-for="pet in pets" :key="pet.id">
                        <div class="single-cat-list" v-if="pet.status != 1 && pet.cat_id == pet_category">
                            <img :src="require(`@/assets/${pet.image}`)" alt="" class="img-fluid">
                            <div class="overlay">
                                <div class="text">
                                <p>    I am {{ pet.name }}!</p>
                                <p v-if="userLoggedIn" @click.prevent="adopt(pet.id)"><router-link to="#"><a style="color: white"><u>Adopt me!</u></a></router-link></p>
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
            pets: [],
            pet_category: this.$route.params.id,
        }
    },

    created() {

    },

    mounted() {
        this.getPets();
    },

    methods: {       
         async getPets() {
            if (await this.$store.dispatch('pets/getPetsFromDB')) {
                this.pets = this.$store.getters[('pets/getpets')]
            }
         },

         adopt: async function(pet) {
            const adopt = {
                petlover_id: this.$store.getters['user/getUser'].id,
                pet_id: pet,
            }

            await this.$store.dispatch('adoptions/newAdoption', adopt)
            localStorage.setItem('message', 'Success! Pet adopted!');
            localStorage.setItem('path', '/mypets');
            this.$router.push('/message')
         },
    },

    computed: {
        userLoggedIn: function () {
            let user = this.$store.getters['user/getUser']
            for (var i in user) return true
            return false
        },
    }
}
</script>

<style scoped>


</style>
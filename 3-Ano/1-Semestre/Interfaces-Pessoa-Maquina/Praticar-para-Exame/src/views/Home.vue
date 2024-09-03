<template>
    <div>
        <header id="header">
            <div class="container main-menu">
                <div class="row align-items-center justify-content-between d-flex">
                    <div id="logo">
                        <router-link class="nav-link" to="/"><a><img src="@/assets/logo.png" alt="" title="" /></a></router-link>
                    </div>
                    <nav id="nav-menu-container">
                        <ul class="nav-menu">			              
				        </ul>
                    </nav>		    		
                </div>
            </div>
        </header>
        <section class="banner-area relative" id="home">
            <div class="container">
                <div class="overlay overlay-bg"></div>
                <div class="row fullscreen d-flex align-items-center justify-content-start">
                    <div class="banner-content col-lg-8 col-md-12">
                        <h1 class="text-uppercase">
                            Adopt Us. <br>
                            We need your help.		
                        </h1>
                        <router-link to="/pets/1"><a class="primary-btn header-btn text-uppercase">View our pets!</a></router-link>
                    </div>											
                </div>
            </div>
        </section>
        <section class="image-carusel-area">
            <div class="container">
                <div class="row">
                    <div class="active-image-carusel" >
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c1.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c2.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c3.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c4.jpg" alt="">
                        </div>	
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c1.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c2.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c3.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c4.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c1.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c2.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c3.jpg" alt="">
                        </div>
                        <div class="single-image-carusel">
                            <img class="img-fluid" src="img/c4.jpg" alt="">
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
    export default {
        components: {
            Footer
        },
    
        mounted() {

        },
    }
</script>

<style scoped>
</style>
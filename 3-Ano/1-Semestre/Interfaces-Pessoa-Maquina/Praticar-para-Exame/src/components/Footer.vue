<template>
	<footer class="footer-area">
		<div class="copyright-text">
			<div class="container">
				<div class="row footer-bottom d-flex justify-content-between">
					<p class="col-lg-8 col-sm-6 footer-text m-0 text-white">
						Copyright &copy;{{year}} All rights reserved | This template is made with 
						<i class="fa fa-heart-o" aria-hidden="true"></i> by 
						<a href="https://colorlib.com" target="_blank">Colorlib</a>
					</p>
					<div class="col-lg-4 col-sm-6 footer-social">
						<a href="#"><i class="fa fa-facebook"></i></a>
						<a href="#"><i class="fa fa-twitter"></i></a>
						<a href="#"><i class="fa fa-dribbble"></i></a>
						<a href="#"><i class="fa fa-behance"></i></a>
					</div>
				</div>						
			</div>
		</div>
	</footer>
</template>

<script>
    export default {
        computed: {
            year: function () {
                return new Date().getFullYear()
            },
        }
    }  

</script>

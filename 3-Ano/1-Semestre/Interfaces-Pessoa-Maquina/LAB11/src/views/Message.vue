<template>
	<div class="center-div">
		<div class="row justify-content-center">
			<div class="col-lg-10 col-md-12">
				<br><br><br><br><br><br><br><br><br><br>
				<h2 class="cms-e-element">{{message}}</h2>
			</div>
		</div>
	</div>
</template>

<script>
export default {
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
	.center-div {
		display: flex;
		justify-content: center;
		align-item: center;
	}
</style>




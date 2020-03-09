var c = document.getElementById("canvas");

function resizeCanvas() {
	c.style.width = window.innerWidth * 0.8 + "px";
	setTimeout(function() {
		c.style.height = window.innerHeight * 0.8 + "px";
	}, 0);

}
resizeCanvas();
var c = document.getElementById("canvas");
var ctx = c.getContext("2d");
/*
var c_width = window.innerWidth * 0.8;
var c_height = window.innerHeight * 0.8;
var H = 20;
var W = 20;
var Left =  window.innerWidth * 0.2;
var Right = window.innerWidth;
var Top = window.innerHeight;
var Button = window.innerHeight;

function resizeCanvas() {
	c.setAttribute(width, window.innerWidth * 0.8);
	c.setAttribute(height, window.innerHeight * 0.8);
	//c.style.width = window.innerWidth * 0.8 + "px";
	//c.style.height = window.innerHeight * 0.8 + "px";
	c.style.margin = window.innerHeight * 0.1 + "px " + window.innerWidth * 0.1 + "px";
	console.log(c.style.width * 0.2);
}

function init() {
	//window.addEventListener('resize', resizeCanvas, false);
	//resizeCanvas();

	console.log("width: "+ window.innerWidth);
	console.log("height: "+ window.innerHeight);
}

function drawGrid() {

	var grid_width = (Right - Left) / W;
	var grid_height = (Button - Top) / H;
	console.log(Right);
	for(i = 0; i < H; i++) {
		ctx.moveTo(Left, Top + grid_height * i);
		ctx.lineTo(Right, Top + grid_height * i);
		console.log("draw h: " + Top + grid_height * i);
	}	
	for(i = 0; i < W; i++) {
		ctx.moveTo(Left + grid_width * i, Top);
		ctx.lineTo(Left + grid_width * i, Button);
		console.log("draw w: " + Left + grid_width * i);
	}
}
*/
function draw() {
	//ctx.lineWidth = 2;
	//drawGrid();
	ctx.beginPath()
	ctx.moveTo(0, 0);
	ctx.lineTo(300,500);
	ctx.stroke();
}

//init()
draw()
